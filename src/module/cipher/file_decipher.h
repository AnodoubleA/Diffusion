//
// Created by Alice on 2017.03.03.
//

#ifndef DIFFUSION_FILE_DECIPHERS_H
#define DIFFUSION_FILE_DECIPHERS_H

#include <list>
#include <istream>
#include <fstream>
#include <afxres.h>
#include "FileCipher.h"
#include "segments/serial_segment_cipher.h"
#include "streams/stream_cipher.h"
#include "../../cipher/Scheduler.h"
#include "../cmds/options.h"
#include "../../tool/tools.h"
#include "../fm/filemapping.h"
#include "AbstractFileCipher.h"
#include "CipConfig.h"
#include "infos/info_handler_help.h"

namespace lc{
    /**
     * A file decipher use file mapping, very fast, but only process source file.
     * So, this cannot support padding.
     */
    class MappedFileDecipher : public AbstractFileCipher {
    protected:
        int A_VSR = 0;
        DecipherBuffer* cipher = nullptr;
    public:
        void init(Init& init, Info& info, BufferMessenger* contact) override {
            if (handler == nullptr || io.level != info.level) {
                freeInstance(handler);
                handler = getKeyHandlerFactory().make(info.level);
            }
            if (algorithm == nullptr || A_VSR != info.algorithm) {
                freeInstance(algorithm);
                algorithm = getAlgorithmFactory().make(CO::DECIPHER, info.algorithm);
            }
            AbstractFileCipher::init(init, info, contact);
            handler->init(info, init);
            cipher = (DecipherBuffer*) BufferCipherFactory::make(info.options);
            cipher->setAlgorithm(*algorithm);
            cipher->setHandler(*handler);
            cipher->setPadding(padding);
            cipher->init(init, info);
            A_VSR = info.algorithm;
        }

        uint64 run(const std::string& in, const std::string& out)throw(DiffusionException) {
            FileMapping& map = *FMFactory::make();
            uint64 size_cip = 0;
            try {
                int64 size_file = map.init(in, FM::OPEN, FM::READ | FM::WRITE);
                map.make(0);
                uint64 cache = (uint64) (allocationGranularity * BUFFER_MULTIPLE * 2);
                size_cip = size_file - fileInfoHandler.length();
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
                    cipher->run(buf, remainder);
                    map.unmap(buf);
                    contact->addDone(remainder + fileInfoHandler.length());
                }
            } catch (DiffusionException& e) {
                map.deinit();
                throw e;
            }
            map.deinit(size_cip - io.diff);
            return size_cip - io.diff;
        }
    };

    //====================================================================================================================

    /**
     * Power-ed file decipher use file mapping. but not support padding.
     */
    class PowerMappedFileDecipher : public MappedFileDecipher {
    protected:
        uint64 run(const std::string& in, const std::string& out) throw(DiffusionException) {
            FileMapping& imap = *FMFactory::make();
            FileMapping& omap = *FMFactory::make();
            uint64 size_cip = 0;
            try {
                int64 size_in = imap.init(in, FM::OPEN, FM::READ);
                imap.make(0);
                size_cip = size_in - fileInfoHandler.length();
                omap.init(out, FM::CREATE, FM::READ | FM::WRITE);
                omap.make(size_cip);
                uint64 cache = allocationGranularity * BUFFER_MULTIPLE;
                uint64 round = size_cip / cache;
                uint64 remainder = size_cip % cache;
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
                    buf_in = imap.map(offset, remainder, FM::READ);
                    buf_out = omap.map(offset, remainder, FM::WRITE);
                    memcpy(buf_out, buf_in, remainder);
                    cipher->run(buf_out, remainder);
                    imap.unmap(buf_in);
                    omap.unmap(buf_out);
                    contact->addDone(remainder + fileInfoHandler.length());
                }
            } catch (DiffusionException& e) {
                imap.deinit();
                omap.deinit();
                throw e;
            }
            imap.deinit();
            omap.deinit(size_cip - io.diff);
            return size_cip - io.diff;
        }
    };

    //====================================================================================================================
    /**
     * Super file decipher, use io-stream, support all functions, but not fast.
     */
    class StreamFileDecipher : public AbstractFileCipher {
        StreamDecipher worker;
        int A_VSR = -1;
    public:
        StreamFileDecipher() {
            padding = PaddingFactory::make(CO::PADDING);
        }

        void init(Init& init, Info& info, BufferMessenger* contact) override {
            if (handler == nullptr || io.level != info.level) {
                freeInstance(handler);
                handler = getKeyHandlerFactory().make(info.level);
            }
            if (algorithm == nullptr || A_VSR != info.algorithm) {
                freeInstance(algorithm);
                algorithm = getAlgorithmFactory().make(CO::DECIPHER, info.algorithm);
            }
            AbstractFileCipher::init(init, info, contact);
            handler->init(info, init);
            worker.setAlgorithm(*algorithm);
            worker.setPadding(padding);
            worker.setHandler(*handler);
            worker.init(init, contact);
        }

        void deinit() override {
            AbstractFileCipher::deinit();
            worker.deinit();
        }

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
                size = worker.run(fin, fout, length - fileInfoHandler.length());
                contact->addDone(fileInfoHandler.length());
            } catch (DiffusionException& e) {
                fin.close();
                fout.close();
                throw e;
            }
            fin.close();
            fout.close();
            return size;
        }
    };
}
#endif //DIFFUSION_FILE_DECIPHERS_H
