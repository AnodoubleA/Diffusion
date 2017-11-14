//
// Created by Alice on 2017.03.01.
//
#pragma once
#ifndef DIFFUSION_BUFFERCIPHER_H
#define DIFFUSION_BUFFERCIPHER_H

#include "../core/Object.h"
#include "structs.h"
#include "Consts.h"
#include "Padding.h"
#include "../module/cmds/options.h"
#include "../core/types.h"
#include "Algorithm.h"

namespace lc{
    class BufferCipher : public Reusable {

    public:

        virtual void init(Init& init, Info& info) = 0;

        virtual void deinit() = 0;

        virtual bool support(int options) = 0;

        /**
         * Process a buffer, may have padding.
         * @param in
         * @param out
         * @param length input length
         * @return output length
         */
        virtual uint64 run(byte* in, byte* out, uint64 length) = 0;

        /**
         * Process a buffer.
         * run with no padding.
         * @param in
         * @param length input length
         * @return output length
         */
        virtual uint64 run(byte* in, uint64 length) = 0;
    };


    class AbstractBufferCipher : public BufferCipher, public AbstractReusable {
    protected:
        int N = 0, L = 0, fill = 0;
        //int options = CipherOption::PADDING;
        Padding* padding = nullptr;
        KeyHandler* handler = nullptr;
        Algorithm* algorithm = nullptr;
    public:

        void setPadding(Padding* padding) {
            this->padding = padding;
        }

        void setHandler(KeyHandler& handler) {
            this->handler = &handler;
        }

        void setAlgorithm(Algorithm& algorithm) {
            this->algorithm = &algorithm;
        }

        void init(Init& init, Info& info) override {
            N = init.N;
            L = init.L;
            fill = 0;
            if (padding != nullptr) {
                fill = padding->compute(init.N);
            }
        }

        void deinit() override {
            unlock();
        }

        bool lock() override {
            return AbstractReusable::lock();
        }

        void unlock() override {
            AbstractReusable::unlock();
        }
    };
}
#endif //DIFFUSION_BUFFERCIPHER_H
