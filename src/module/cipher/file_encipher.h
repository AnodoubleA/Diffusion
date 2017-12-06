//
// Created by Alice on 2017.03.03.
//

#pragma once
#ifndef DIFFUSION_FILE_ENCIPHERS_H
#define DIFFUSION_FILE_ENCIPHERS_H

#include <list>
#include <istream>
#include <fstream>
#include <afxres.h>
#include "FileCipher.h"
#include "buffer_ciphers.h"
#include "stream_ciphers.h"
#include "../../cipher/Scheduler.h"
#include "../cmds/options.h"
#include "../../tool/tools.h"
#include "../fm/filemapping.h"
#include "AbstractFileCipher.h"
#include "../../tool/funs.h"
#include "CipConfig.h"
#include "info_factory.h"
#include "info_handler.h"
#include "../fm/fm_factory.h"
#include "parallel_buffer_cipher.h"
#include "buffer_factory.h"

namespace lc{

    class MappedFileEncipher : public AbstractFileCipher {
    protected:
        FileInfoHandler infoHandler;
        EncipherBuffer* cipher;
    public:
        void init(Init& init, Info& info, BufferContact* contact) override {
            if (algorithm == nullptr) {
                algorithm = getAlgorithmFactory().make(CO::ENCIPHER, info.algorithm);
            }
            if (handler == nullptr || io.level != info.level) {
                freeInstance(handler);
                handler = getKeyHandlerFactory().make(info.level);
            }
            AbstractFileCipher::init(init, info, contact);
            handler->init(init, info);
            cipher = (EncipherBuffer*) BufferCipherFactory::make(info.options);
            cipher->setHandler(*handler);
            cipher->setPadding(padding);
            cipher->setAlgorithm(*algorithm);
            cipher->init(init, info);
        }

        void deinit() override {
            AbstractFileCipher::deinit();
            cipher->deinit();
        }

        uint64 run(const std::string& in, const std::string& out)throw(DiffusionException) {
            FileMapping& map = *FMFactory::make();
            uint64 size_new = 0;
            try {
                int N = it.N, info_len = infoHandler.length();
                int64 size_file = map.init(in, FM::OPEN, FM::READ | FM::WRITE);
                uint64 size_cip = (uint64) std::ceil(1.0 * size_file / N) * N;
                size_new = size_cip + info_len;
                io.diff = size_cip - size_file;
                map.make(size_new);
                uint64 cache = (uint64) (allocationGranularity * BUFFER_MULTIPLE * 2);
                uint64 round = size_cip / cache;
                uint64 remainder = size_cip % cache;
                uint64 offset = 0;
                byte* buf = nullptr;
                for (uint64 i = 0; i < round; i++) {
                    buf = map.map(offset, cache, FM::WRITE);
                    cipher->run(buf, cache);
                    map.unmap(buf);
                    offset += cache;
                    contact->addDone(cache);
                }
                if (remainder > 0) {
                    buf = map.map(offset, remainder, FM::WRITE);
                    padding->padding(buf + (remainder - io.diff), io.diff);
                    cipher->run(buf, remainder);
                    map.unmap(buf);
                    contact->addDone(remainder - io.diff);
                }
                round = size_new / allocationGranularity;
                remainder = size_new % allocationGranularity;
                if (remainder < info_len) {
                    round -= 1;
                    remainder += allocationGranularity;
                }
                buf = map.map(round * allocationGranularity, remainder, FM::WRITE);
                infoHandler.write(buf + (remainder - info_len), io);
                map.unmap(buf);
            } catch (DiffusionException& e) {
                map.deinit(0);
                throw e;
            }
            map.deinit(0);
            return size_new;
        }

    };

    //====================================================================================================================

    class PowerMappedFileEncipher : public MappedFileEncipher {
    public:
        void deinit() override {
            MappedFileEncipher::deinit();
            cipher->deinit();
        }

        uint64 run(const std::string& in, const std::string& out) throw(DiffusionException) {
            FileMapping& imap = *FMFactory::make();
            FileMapping& omap = *FMFactory::make();
            uint64 size_out = 0;
            try {
                int N = it.N, info_len = infoHandler.length();
                int64 size_in = imap.init(in, FM::OPEN, FM::READ);
                imap.make(0);
                uint64 size_cip = (uint64) (std::ceil(1.0 * size_in / N) * N);
                size_out = size_cip + info_len;
                io.diff = size_cip - size_in;
                omap.init(out, FM::CREATE, FM::READ | FM::WRITE);
                omap.make(size_out);
                uint64 cache = (allocationGranularity * BUFFER_MULTIPLE);
                uint64 round = size_in / cache;
                uint64 remainder = size_in % cache;
                uint64 offset = 0;
                byte* buf_in = nullptr;
                byte* buf_out = nullptr;
                for (uint64 i = 0; i < round; i++) {
                    buf_in = imap.map(offset, cache, FM::READ);
                    buf_out = omap.map(offset, cache, FM::WRITE);
                    memcpy(buf_out, buf_in, cache);
                    cipher->run(buf_out, cache);
                    imap.unmap(buf_in);
                    omap.unmap(buf_out);
                    offset += cache;
                    contact->addDone(cache);
                }
                if (remainder > 0) {
                    uint64 len = size_cip % cache;
                    buf_in = imap.map(offset, remainder, FM::READ);
                    buf_out = omap.map(offset, len, FM::WRITE);
                    memcpy(buf_out, buf_in, remainder);
                    padding->padding(buf_out + (len - io.diff), io.diff);
                    cipher->run(buf_out, len);
                    imap.unmap(buf_in);
                    omap.unmap(buf_out);
                    contact->addDone(remainder);
                }
                round = size_out / allocationGranularity;
                remainder = size_out % allocationGranularity;
                if (remainder < info_len) {
                    round -= 1;
                    remainder += allocationGranularity;
                }
                buf_out = omap.map(round * allocationGranularity, remainder, FM::WRITE);
                infoHandler.write(buf_out + (remainder - info_len), io);
                imap.unmap(buf_in);
                omap.unmap(buf_out);
            } catch (DiffusionException& e) {
                imap.deinit();
                omap.deinit();
                throw e;
            }
            imap.deinit();
            omap.deinit();
            return size_out;
        }

    };

    class StreamFileEncipher : public AbstractFileCipher {
        EncipherStream worker;
        FileInfoHandler infoHandler;
    public:
        void init(Init& init, Info& info, BufferContact* contact) override {
            if (algorithm == nullptr) {
                algorithm = getAlgorithmFactory().make(CO::ENCIPHER, info.algorithm);
            }
            if (handler == nullptr || io.level != info.level) {
                freeInstance(handler);
                handler = getKeyHandlerFactory().make(info.level);
            }
            AbstractFileCipher::init(init, info, contact);
            handler->init(init, info);
            worker.setHandler(*handler);
            worker.setAlgorithm(*algorithm);
            worker.setPadding(padding);
            worker.init(init, info, contact);
        }

        void deinit() override {
            AbstractFileCipher::deinit();
            worker.deinit();
        }

    public:
        uint64 run(const std::string& in, const std::string& out) throw(DiffusionException) {
            std::ifstream fin(in, std::ios::in | std::ios::binary);
            std::ofstream fout(out, std::ios::out | std::ios::binary);
            uint64 size = 0;
            try {
                if (!fin.is_open()) {
                    throw DiffusionException(I18N->gf(ERROR_FILE_OPEN, in.c_str()));
                }
                if (!fout.is_open()) {
                    throw DiffusionException(I18N->gf(ERROR_FILE_CREATE, out.c_str()));
                }
                uint64 length = get_length(fin);
                int real = it.N - padding->compute(it.N);
                int remainder = length % real;
                io.diff = remainder == 0 ? 0 : (real - remainder);
                size = worker.run(fin, fout, length);
                int info_len = infoHandler.length();
                byte buf[info_len];
                infoHandler.write(buf, io);
                fout.write((char*) buf, info_len);
            } catch (DiffusionException& e) {
                fin.close();
                fout.close();
                throw e;
            }
            fin.close();
            fout.close();
            return size + fileInfoHandler.length();
        }


    };
}
#endif //DIFFUSION_FILE_CIPHERS_H
