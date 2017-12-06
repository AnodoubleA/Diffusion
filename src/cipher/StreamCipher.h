//
// Created by Alice on 2017.03.01.
//
#pragma once
#ifndef DIFFUSION_STREAMCIPHER_H
#define DIFFUSION_STREAMCIPHER_H

#include <istream>
#include "structs.h"
#include "../module/cipher/Padding.h"
#include "../module/cipher/paddings.h"
#include "../module/cipher/KeyHandler.h"
#include "../core/DiffusionException.h"

namespace lc{

    class StreamCipher {
    public:
        virtual void init(Init& init, Info& info, BufferContact* contact) = 0;

        virtual void deinit() = 0;

        virtual uint64 run(std::istream& in, std::ostream& out, uint64 length) throw(DiffusionException) = 0;
    };

    class AbstractStreamCrypto : public StreamCipher {
    protected:
        byte* buf_in = nullptr;
        byte* buf_out = nullptr;
        Padding* padding = nullptr;
        KeyHandler* handler = nullptr;
        Algorithm* algorithm = nullptr;
        BufferContact* contact = nullptr;
        Init it;
        Info io;
        int N = 0, fill = 0, cache;
        bool pad = false;
    public:
        virtual ~AbstractStreamCrypto() {
            delete[](buf_in);
            delete[](buf_out);
        }

        AbstractStreamCrypto() {
            cache = allocationGranularity * BUFFER_MULTIPLE;
            buf_in = new byte[cache];
            buf_out = new byte[cache];
        }

        void setPadding(Padding* padding) {
            this->padding = padding;
        }

        void setHandler(KeyHandler& handler) {
            this->handler = &handler;
        }

        void setAlgorithm(Algorithm& algorithm) {
            this->algorithm = &algorithm;
        }

        void init(Init& init, Info& info, BufferContact* contact) override {
            this->N = init.N;
            this->it = init;
            this->io = info;
            this->contact = contact;
            fill = padding == nullptr ? 0 : padding->compute(N);
            pad = contains(info.options, CO::PADDING);
        }
    };
}
#endif //DIFFUSION_STREAMCIPHER_H
