#pragma once
#ifndef DIFFUSION_SERIALSEGMENTCIPHER_H
#define DIFFUSION_SERIALSEGMENTCIPHER_H


#include "../Padding.h"
#include "../paddings.h"
#include "../KeyHandler.h"
#include "../SegmentCipher.h"
#include "../AbstractSegmentCipher.h"

namespace lc {
    class SerialSegmentEncipher : public AbstractSegmentCipher {

    public:
        virtual void init(Init& init, Info& info) override {
            AbstractSegmentCipher::init(init, info);
            algorithm->init(init);
        }

        virtual uint64 run(byte* in, byte* out, uint64 length) override;

        virtual uint64 run(byte* in, uint64 length) override;

        virtual bool support(int options) override {
            return contains(options, CO::ENCIPHER, CO::MULTICORE);
        }
    };

    //==================================================================================================
    //Decipher implement
    //==================================================================================================
    class SerialSegmentDecipher : public AbstractSegmentCipher {
    public:
        virtual void init(Init& init, Info& info) override {
            AbstractSegmentCipher::init(init, info);
            algorithm->init(init);
        }

        virtual uint64 run(byte* in, byte* out, uint64 length) override;

        virtual uint64 run(byte* in, uint64 length) override;

        virtual bool support(int options) override {
            return contains(options, CO::DECIPHER, CO::MULTICORE);
        }

    };
}
#endif //DIFFUSION_SERIALSEGMENTCIPHER_H
