//
// Created by Angel on 2017/3/27.
//

#ifndef DIFFUSION_INFOHANDLE_H
#define DIFFUSION_INFOHANDLE_H

#include "../../cipher/version.h"
#include "../../core/types.h"
#include "../../core/DiffusionException.h"
#include "Boollock.h"
#include "CipherInfo.h"

namespace lc {
    class InfoSupport : public Version, public Reusable {
    public:
        virtual int length() = 0;

        virtual int type() = 0;
    };

    class InfoReader : public InfoSupport {
    public:

        virtual int read(byte* buf, CipherInfo& info)  throw(DiffusionException) = 0;

    };

    class InfoWriter : public InfoSupport {
    public:

        virtual int write(byte* buf, CipherInfo& info)  throw(DiffusionException) = 0;

    };

    class InfoHandler : public InfoReader, public InfoWriter {
    private:
        Boollock locker;
    protected:
        InfoReader* reader = nullptr;
    public:
        ~InfoHandler() {
            delete (reader);
        }

        InfoHandler(InfoReader* reader = nullptr) : reader(reader) {

        }

        virtual int write(byte* buf, CipherInfo& info) throw(DiffusionException) {

        }

        virtual bool lock() {
            return locker.lock();
        }

        virtual void unlock() {
            locker.unlock();
        }

        virtual int version() {
            return 1;
        }

        virtual int length() {
            return 32;
        }
    };
}
#endif //DIFFUSION_INFOHANDLE_H
