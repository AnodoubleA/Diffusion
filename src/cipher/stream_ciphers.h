//
// Created by Alice on 2017.03.02.
//
#pragma once
#ifndef DIFFUSION_STREAMCIPHERS_H
#define DIFFUSION_STREAMCIPHERS_H

#include "StreamCipher.h"
#include "Padding.h"
#include "Contact.h"
#include "paddings.h"
#include "buffer_ciphers.h"
#include "CipConfig.h"
#include "info_handler.h"

namespace lc{
    class EncipherStream : public AbstractStreamCrypto {
    protected:
        EncipherBuffer worker;
    public:
        void init(Init& init, Info& info, BufferContact* contact) override {
            AbstractStreamCrypto::init(init, info, contact);
            worker.setHandler(*handler);
            worker.setPadding(padding);
            worker.setAlgorithm(*algorithm);
            worker.init(init, info);
        }

        void deinit() override {
            worker.deinit();
        }

        uint64 run(std::istream& in, std::ostream& out, uint64 length)  throw(DiffusionException) {
            if (pad) {
                return run_fill(in, out, length);
            }
            return run_non_fill(in, out, length);
        }

    protected:

        uint64 run_non_fill(std::istream& in, std::ostream& out, uint64 length)  throw(DiffusionException) {
            if (length == -1) {
                length = get_length(in);
            }
            uint64 round = length / cache;
            uint64 remainder = length % cache;
            for (uint64 i = 0; i < round; i++) {
                in.read((char*) buf_in, cache);
                worker.run(buf_in, cache);
                out.write((char*) buf_in, cache);
                contact->addDone(cache);
            };
            if (remainder > 0) {
                in.read((char*) buf_in, remainder);
                uint64 count = worker.run(buf_in, remainder);
                padding->padding(buf_in + remainder - io.diff, io.diff);
                out.write((char*) buf_in, count);
                contact->addDone(remainder);
            }
            out.flush();
            return (uint64) ceil(1.0 * length / N) * N;
        }

        uint64 run_fill(std::istream& in, std::ostream& out, uint64 length)  throw(DiffusionException) {
            if (length == -1) {
                length = get_length(in);
            }
            int sin = (cache / N) * (N - fill);
            uint64 round = length / sin;
            uint64 remainder = length % sin;
            for (uint64 i = 0; i < round; i++) {
                in.read((char*) buf_in, sin);
                worker.run(buf_in, buf_out, sin);
                out.write((char*) buf_out, cache);
                contact->addDone(sin);
            }
            if (remainder > 0) {
                in.read((char*) buf_in, remainder);
                uint64 count = worker.run(buf_in, buf_out, remainder);
                out.write((char*) buf_out, count);
                contact->addDone(remainder);
            }
            out.flush();
            return (uint64) ceil(1.0 * length / (N - fill)) * N;
        }
    };

    //==================================================================================================
    //Decipher stream implement
    //==================================================================================================
    class DecipherStream : public AbstractStreamCrypto {
    protected:
        DecipherBuffer worker;
    public:
        void init(Init& init, Info& info, BufferContact* contact) override {
            AbstractStreamCrypto::init(init, info, contact);
            worker.setHandler(*handler);
            worker.setPadding(padding);
            worker.setAlgorithm(*algorithm);
            worker.init(init, info);
        }

        void deinit() override {
            worker.deinit();
        }

        uint64 run(std::istream& in, std::ostream& out, uint64 length)  throw(DiffusionException) {
            if (pad) {
                return run_fill(in, out, length);
            }
            return run_non_fill(in, out, length);
        }

    protected:
        uint64 run_non_fill(std::istream& in, std::ostream& out, uint64 length)  throw(DiffusionException) {
            if (length == -1) {
                length = get_length(in);
            }
            uint64 round = length / cache;
            uint64 remainder = length % cache;
            for (uint64 i = 0; i < round; i++) {
                in.read((char*) buf_in, cache);
                worker.run(buf_in, cache);
                out.write((char*) buf_in, cache);
                contact->addDone(cache);
            };
            uint64 count = 0;
            if (remainder > 0) {
                in.read((char*) buf_in, remainder);
                count = worker.run(buf_in, remainder);
                out.write((char*) buf_in, count - io.diff);
                contact->addDone(remainder);
            }
            return length - io.diff;
        }

        uint64 run_fill(std::istream& in, std::ostream& out, uint64 length)  throw(DiffusionException) {
            if (length == -1) {
                length = get_length(in);
            }
            int sin = (cache / N) * (N - fill);
            uint64 round = length / cache;
            uint64 remainder = length % cache;
            for (uint64 i = 0; i < round; i++) {
                in.read((char*) buf_in, cache);
                worker.run(buf_in, buf_out, cache);
                out.write((char*) buf_out, sin);
                contact->addDone(cache);
            }
            if (remainder > 0) {
                in.read((char*) buf_in, remainder);
                uint64 count = worker.run(buf_in, buf_out, remainder);
                out.write((char*) buf_out, count - io.diff);
                contact->addDone(remainder);
            }
            out.flush();
            return length - io.diff;
        }
    };
}
#endif //DIFFUSION_STREAMCIPHERS_H
