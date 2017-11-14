//
// Created by Alice on 2017.03.02.
//
#pragma once
#ifndef DIFFUSION_BUFFERCIPHERS_H
#define DIFFUSION_BUFFERCIPHERS_H


#include <cstring>
#include "Padding.h"
#include "paddings.h"
#include "KeyHandler.h"
#include "Contact.h"
#include "BufferCipher.h"
#include "algorithm_ciphers.h"

namespace lc{
    class EncipherBuffer : public AbstractBufferCipher {

    public:
        void init(Init& init, Info& info) {
            AbstractBufferCipher::init(init, info);
            algorithm->init(init);
        }

        virtual uint64 run(byte* in, byte* out, uint64 length) {
            int H = N - fill, F = N;
            uint64 round = (length / H) >> 3;
            uint64 remainder = (length / H) & 7;
            for (uint64 i = 0; i < round; i++) {
                memcpy(out, in, H);
                padding->padding(out + H, fill);
                algorithm->run(out, handler->update());
                in += H;
                out += F;
                memcpy(out, in, H);
                padding->padding(out + H, fill);
                algorithm->run(out, handler->update());
                in += H;
                out += F;
                memcpy(out, in, H);
                padding->padding(out + H, fill);
                algorithm->run(out, handler->update());
                in += H;
                out += F;
                memcpy(out, in, H);
                padding->padding(out + H, fill);
                algorithm->run(out, handler->update());
                in += H;
                out += F;
                memcpy(out, in, H);
                padding->padding(out + H, fill);
                algorithm->run(out, handler->update());
                in += H;
                out += F;
                memcpy(out, in, H);
                padding->padding(out + H, fill);
                algorithm->run(out, handler->update());
                in += H;
                out += F;
                memcpy(out, in, H);
                padding->padding(out + H, fill);
                algorithm->run(out, handler->update());
                in += H;
                out += F;
                memcpy(out, in, H);
                padding->padding(out + H, fill);
                algorithm->run(out, handler->update());
                in += H;
                out += F;
            }
            for (uint64 i = 0; i < remainder; i++) {
                memcpy(out, in, H);
                padding->padding(out + H, fill);
                algorithm->run(out, handler->update());
                in += H;
                out += F;
            }
            uint64 lost = length % H;
            if (lost > 0) {
                memcpy(out, in, lost);
                padding->padding(out + lost, F - lost);
                algorithm->run(out, handler->update());
            }
            return (uint64) std::ceil(1.0 * length / H) * F;
        }

        virtual uint64 run(byte* in, uint64 length) {
            uint64 round = (length >> L) >> 3;
            uint64 remainder = (length >> L) & 7;
            for (uint64 i = 0; i < round; i++) {
                algorithm->run(in, handler->update());
                in += N;
                algorithm->run(in, handler->update());
                in += N;
                algorithm->run(in, handler->update());
                in += N;
                algorithm->run(in, handler->update());
                in += N;
                algorithm->run(in, handler->update());
                in += N;
                algorithm->run(in, handler->update());
                in += N;
                algorithm->run(in, handler->update());
                in += N;
                algorithm->run(in, handler->update());
                in += N;
            }
            for (uint64 i = 0; i < remainder; i++) {
                algorithm->run(in, handler->update());
                in += N;
            }
            return length;
        }

        bool support(int options) override {
            return contains(options, CO::ENCIPHER, CO::MULTICORE);
        }
    };

    //==================================================================================================
    //Decipher implement
    //==================================================================================================
    class DecipherBuffer : public AbstractBufferCipher {
    public:
        void init(Init& init, Info& info) override {
            AbstractBufferCipher::init(init, info);
            algorithm->init(init);
        }

        virtual uint64 run(byte* in, byte* out, uint64 length) {
            int H = N - fill, F = N;
            uint64 round = (length / F) >> 3;
            uint64 remainder = (length / F) & 7;
            for (uint64 i = 0; i < round; i++) {
                algorithm->run(in, handler->update());
                memcpy(out, in, H);
                in += F;
                out += H;
                algorithm->run(in, handler->update());
                memcpy(out, in, H);
                in += F;
                out += H;
                algorithm->run(in, handler->update());
                memcpy(out, in, H);
                in += F;
                out += H;
                algorithm->run(in, handler->update());
                memcpy(out, in, H);
                in += F;
                out += H;
                algorithm->run(in, handler->update());
                memcpy(out, in, H);
                in += F;
                out += H;
                algorithm->run(in, handler->update());
                memcpy(out, in, H);
                in += F;
                out += H;
                algorithm->run(in, handler->update());
                memcpy(out, in, H);
                in += F;
                out += H;
                algorithm->run(in, handler->update());
                memcpy(out, in, H);
                in += F;
                out += H;
            }
            for (uint64 i = 0; i < remainder; i++) {
                algorithm->run(in, handler->update());
                memcpy(out, in, H);
                in += F;
                out += H;
            }
            return (uint64) std::ceil(1.0 * length / F) * H;
        }

        virtual uint64 run(byte* in, uint64 length) {
            uint64 round = (length >> L) >> 3;
            uint64 remainder = (length >> L) & 7;
            for (uint64 i = 0; i < round; i++) {
                algorithm->run(in, handler->update());
                in += N;
                algorithm->run(in, handler->update());
                in += N;
                algorithm->run(in, handler->update());
                in += N;
                algorithm->run(in, handler->update());
                in += N;
                algorithm->run(in, handler->update());
                in += N;
                algorithm->run(in, handler->update());
                in += N;
                algorithm->run(in, handler->update());
                in += N;
                algorithm->run(in, handler->update());
                in += N;
            }
            for (uint64 i = 0; i < remainder; i++) {
                algorithm->run(in, handler->update());
                in += N;
            }
            return length;
        }

        bool support(int options) override {
            return contains(options, CO::DECIPHER, CO::MULTICORE);
        }

    };
}
#endif //DIFFUSION_BUFFERCIPHERS_H
