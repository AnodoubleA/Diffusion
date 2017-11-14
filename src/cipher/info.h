//
// Created by Angel on 2017/3/27.
//

#ifndef DIFFUSION_INFO_H
#define DIFFUSION_INFO_H

#include "version.h"
#include "reusable.h"
#include "../core/types.h"
#include "structs.h"
#include "../core/DiffusionException.h"

namespace lc{
    class InfoSupport : public Version, public Reusable {
    public:
        virtual int length() = 0;
    };

    class InfoReader : public InfoSupport {
    public:

        virtual void read(byte buf[], Info& info)  throw(DiffusionException) = 0;

        virtual void read(std::istream& in, Info& info)  throw(DiffusionException) = 0;
    };

    class InfoWriter : public InfoSupport {
    public:

        virtual void write(byte buf[], Info& info)  throw(DiffusionException) = 0;

        virtual void write(std::ostream& out, Info& info)  throw(DiffusionException) = 0;
    };

    class AbstractInfoHandler : public InfoReader, public InfoWriter, public AbstractReusable {
    public:

        void read(byte* buf, Info& info) throw(DiffusionException) {

        }

        void write(byte* buf, Info& info) throw(DiffusionException) {

        }

        void write(std::ostream& out, Info& info) throw(DiffusionException) {
            byte buf[length()];
            write(buf, info);
            out.write((char*) buf, length());
        }

        void read(std::istream& in, Info& info) throw(DiffusionException) {
            int64 offset = in.tellg();
            int bufSize = length() - CCfg::HEADER_SIZE - 1;
            byte buf[bufSize];
            in.seekg(offset - length());
            in.read((char*) buf, bufSize);
            read(buf, info);
            in.seekg(offset);
        }

        bool lock() override {
            return AbstractReusable::lock();
        }

        void unlock() override {
            AbstractReusable::unlock();
        }

        virtual int version() {
            return 1;
        }

        int length() override {
            return 32;
        }
    };
}
#endif //DIFFUSION_INFO_H
