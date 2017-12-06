//
// Created by Alice on 2017.03.10.
//
#pragma once
#ifndef DIFFUSION_WORKERS_H
#define DIFFUSION_WORKERS_H

#include <thread>
#include "../module/cmds/options.h"
#include "../module/cipher/file_encipher.h"
#include "../module/cipher/file_decipher.h"
#include "Worker.h"
#include "CipherLisenter.h"
#include "../module/fs/FileSmash.h"
#include "../module/fs/file_smash_factory.h"
#include "item_listener.h"
#include "../module/cipher/info_factory.h"
#include "../tool/file_handler.h"

namespace lc{
    class JobEncipher : public Worker<Item>, public AbstractReusable {
    protected:
        FileCipher* cipher = nullptr;
        ItemListener* listener = nullptr;
        Item* item = nullptr;
        int mStatus;
    public:
        ~JobEncipher() {
            delete (cipher);
        }

        bool interrupt() throw(DiffusionException) {
            item->status(Item::INTERRUPTED);
            return true;
        }

        void init(ItemListener* listener) {
            this->listener = listener;
        }

        void deinit() {
            unlock();
            if (cipher != nullptr)cipher->deinit();
        }

        uint64 run(Item& item) throw(DiffusionException) {
            this->item = (&item);
            run_before(item);
            FileCipher& cipher = getCipher();
            cipher.init(*item.init, *item.info, &item.contact);
            uint64 length = cipher.run(item.in_file, item.out_file);
            run_after(item, length);
            return length;
        }

        bool lock() override {
            return AbstractReusable::lock();
        }

        void unlock() override {
            AbstractReusable::unlock();
        }

        int status() override {
            return mStatus;
        }

    protected:
        virtual void run_before(Item& item) throw(DiffusionException) {
            item.start = getSystemTime();
            item.contact.length = item.length;
            FH::compute_io(item);
            item.status(Item::CIPHER_BEGIN);
            (*listener)(item);
        }

        virtual void run_after(Item& item, uint64 length) throw(DiffusionException) {
            item.end = getSystemTime();
            item.length = length;
            item.status(Item::CIPHER_END);
            (*listener)(item);
            item.status(Item::COMPLETED);
            (*listener)(item);
        }

        virtual FileCipher& getCipher() = 0;
    };

    class JobDecipher : public JobEncipher {
        FileInfoHandler infoHandler;
    protected:
        void run_before(Item& item) throw(DiffusionException) {
            JobEncipher::run_before(item);
            infoHandler.read(item.in_file, *item.init, *item.info);
            if (contains(item.info->options, FO::DO_SOURCE | FO::PADDING)) {
                throw DiffusionException(I18N->gf(ERROR_FILE_DOS_PAD, item.in_file.c_str()));
            }
            if (contains(item.info->options, FO::PADDING)) {
                if (item.out_file == item.in_file) {
                    throw DiffusionException(I18N->gf(ERROR_FILE_OMISS_WPAD, item.in_file.c_str()));
                }
            }
            if (contains(item.info->options, FO::COVER, FO::DO_SOURCE)) {
                if (item.out_file == item.in_file) {
                    throw DiffusionException(I18N->gf(ERROR_FILE_OMISS_WCOV, item.out_file.c_str()));
                }
            }
        }

        void run_after(Item& item, uint64 length) throw(DiffusionException) {
            JobEncipher::run_after(item, length);
            std::string out = item.out_file;
            if (contains(item.info->options, FO::DO_SOURCE) && Strings::endWith(out, EXTEND_FILE_NAME)) {
                int64 index = out.find_last_of(FILE_SEPARATOR);
                std::string dir = out.substr(0, index);
                std::string name = out.substr(index + 1);
                out = FH::new_name(dir, name, item.info->options, EXTEND_FILE_NAME);
                std::rename(item.out_file.c_str(), out.c_str());
            }
        }
    };

    //==============================================================================================================
    class FastJobEncipher : public JobEncipher {
    protected:
        FileCipher& getCipher() override {
            if (cipher == nullptr) {
                cipher = new MappedFileEncipher();
            }
            return *cipher;
        }

    public:
        bool support(int options) override {
            return contains(options, FO::ENCIPHER | FO::DO_SOURCE);
        }
    };

    class PowerJobEncipher : public JobEncipher {
    protected:
        FileCipher& getCipher() override {
            if (cipher == nullptr) {
                cipher = new PowerMappedFileEncipher();
            }
            return *cipher;
        }

    public:
        bool support(int options) override {
            return contains(options, FO::ENCIPHER, FO::PADDING);
        }
    };

    class SuperJobEncipher : public JobEncipher {
    protected:
        FileCipher& getCipher() override {
            if (cipher == nullptr) {
                cipher = new StreamFileEncipher();
            }
            return *cipher;
        }

    public:
        bool support(int options) override {
            return contains(options, FO::ENCIPHER | FO::PADDING);
        }
    };

    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // decipher jobs
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    class FullJobDecipher : public JobDecipher {
        MappedFileDecipher fast;
        StreamFileDecipher stream;
        PowerMappedFileDecipher power;
    protected:
        FileCipher& getCipher() override {
            int& options = item->info->options;
            if (contains(options, FO::DO_SOURCE, FO::PADDING)) {
                return fast;
            }
            if (!contains(options, FO::PADDING)) {
                return power;
            }
            return stream;
        }

    public:
        bool support(int options) override {
            return contains(options, FO::DECIPHER);
        }
    };
}
#endif //DIFFUSION_WORKERS_H
