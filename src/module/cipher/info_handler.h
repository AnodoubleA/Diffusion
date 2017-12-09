//
// Created by Angel on 2017/3/27.
//

#ifndef DIFFUSION_INFOHANDLE_H
#define DIFFUSION_INFOHANDLE_H

#include "../../cipher/version.h"
#include "../../core/types.h"
#include "../../core/DiffusionException.h"
#include "Boollock.h"

namespace lc {
    class InfoSupport : public Version, public Reusable {
    public:
        virtual int length() = 0;
    };

    class InfoReader : public InfoSupport {
    public:

        virtual void read(byte buf[], Info& info)  throw(DiffusionException) = 0;

    };

    class InfoWriter : public InfoSupport {
    public:

        virtual void write(byte buf[], Info& info)  throw(DiffusionException) = 0;

    };

    class AbstractInfoHandler : public InfoReader, public InfoWriter {
    private:
        Boollock locker;
        InfoReader* reader = nullptr;
        InfoWriter* writer = nullptr;
    public:

        virtual void read(byte* buf, Info& info) throw(DiffusionException) {

        }

        virtual void write(byte* buf, Info& info) throw(DiffusionException) {

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
