//
// Created by Alice on 2017.03.01.
//
#pragma once
#ifndef DIFFUSION_BUFFERCIPHER_H
#define DIFFUSION_BUFFERCIPHER_H

#include "../../core/Object.h"
#include "../../cipher/structs.h"
#include "../../cipher/Consts.h"
#include "Padding.h"
#include "../cmds/options.h"
#include "../../core/types.h"
#include "Algorithm.h"

namespace lc{
    class SegmentCipher : public Reusable {

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
}
#endif //DIFFUSION_BUFFERCIPHER_H
