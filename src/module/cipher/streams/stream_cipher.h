//
// Created by Alice on 2017.03.02.
//
#pragma once
#ifndef DIFFUSION_STREAM_CIPHER_H
#define DIFFUSION_STREAM_CIPHER_H

#include "../Padding.h"
#include "../Contact.h"
#include "../paddings/RandomBlockPadding.h"
#include "../segments/serial_segment_cipher.h"
#include "../InfoHeader.h"
#include "../infos/info_handler_help.h"
#include "../AbstractStreamCipher.h"

namespace lc {
    class StreamEncipher : public AbstractStreamCipher {
    protected:
        AbstractSegmentCipher worker;
    public:
        virtual void init(SessionInfo* config, BufferContact* contact) {
            AbstractStreamCipher::init(config, contact);
            worker.init(config);
        }

        virtual void deinit() {
            worker.deinit();
        }

        virtual uint64 run(std::istream& in, std::ostream& out, uint64 length)  throw(DiffusionException) {
            if (pad) {
                return run_fill(in, out, length);
            }
            return run_non_fill(in, out, length);
        }

        uint64 run_non_fill(std::istream& in, std::ostream& out, uint64 length)  throw(DiffusionException);

        uint64 run_fill(std::istream& in, std::ostream& out, uint64 length)  throw(DiffusionException);
    };

    //==================================================================================================
    //Decipher streams implement
    //==================================================================================================
    class StreamDecipher : public AbstractStreamCipher {
    protected:
        AbstractSegmentCipher worker;
    public:
        virtual void init(SessionInfo* config, BufferContact* contact) {
            AbstractStreamCipher::init(config, contact);
            worker.init(config);
        }

        virtual void deinit() {
            worker.deinit();
        }

        virtual uint64 run(std::istream& in, std::ostream& out, uint64 length)  throw(DiffusionException) {
            if (pad) {
                return run_fill(in, out, length);
            }
            return run_non_fill(in, out, length);
        }

        uint64 run_non_fill(std::istream& in, std::ostream& out, uint64 length) throw(DiffusionException);

        uint64 run_fill(std::istream& in, std::ostream& out, uint64 length)  throw(DiffusionException);
    };
}
#endif //DIFFUSION_STREAM_CIPHER_H
