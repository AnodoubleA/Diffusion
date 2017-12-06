//
// Created by Alice on 2017.04.20.
//

#ifndef DIFFUSION_PARALLEL_BUFFER_CIPHER_H
#define DIFFUSION_PARALLEL_BUFFER_CIPHER_H

#include <omp.h>
#include "buffer_ciphers.h"

namespace lc{
    class ParallelEncipherBuffer : public EncipherBuffer {
        bool fixed = false;
    public:
        void init(Init& init, Info& info) override {
            EncipherBuffer::init(init, info);
            fixed = (info.level & 0xFF) == 1;
        }

        uint64 run(byte* in, uint64 length) override {
            return fixed ? run_parallel(in, length) : EncipherBuffer::run(in, length);
        }

        uint64 run_parallel(byte* in, uint64 length) {
            int k = 0;
            int s = 1 << CORE_BUFFER_LOG;
            int c = 1 << CORE_COUNT_LOG;
            int round = (length >> CORE_BUFFER_LOG >> CORE_COUNT_LOG) << CORE_COUNT_LOG;
            int done = (round << CORE_BUFFER_LOG);
#pragma omp parallel for firstprivate(s, c, k)
            for (int i = 0; i < round; i++) {
                int p = k++ * c + omp_get_thread_num();
                EncipherBuffer::run(in + (p * s), s);
            }
            if (done == length)return length;
            return EncipherBuffer::run(in + done, length - done) + done;
        }

        bool support(int options) override {
            return contains(options, CO::ENCIPHER | CO::MULTICORE);
        }
    };

    class ParallelDecipherBuffer : public DecipherBuffer {
        bool fixed = false;
    public:
        void init(Init& init, Info& info) override {
            DecipherBuffer::init(init, info);
            fixed = (info.level & 0xFF) == 1;
        }

        uint64 run(byte* in, uint64 length) override {
            return fixed ? run_parallel(in, length) : DecipherBuffer::run(in, length);
        }

        uint64 run_parallel(byte* in, uint64 length) {
            int k = 0;
            int s = 1 << CORE_BUFFER_LOG;
            int c = 1 << CORE_COUNT_LOG;
            int round = (length >> CORE_BUFFER_LOG >> CORE_COUNT_LOG) << CORE_COUNT_LOG;
            int done = round << CORE_BUFFER_LOG;
#pragma omp parallel for firstprivate(s, c, k)
            for (int i = 0; i < round; i++) {
                int p = k++ * c + omp_get_thread_num();
                DecipherBuffer::run(in + (p * s), s);
            }
            if (done == length)return length;
            return DecipherBuffer::run(in + done, length - done) + done;
        }

        bool support(int options) override {
            return contains(options, CO::DECIPHER | CO::MULTICORE);
        }
    };
}
#endif //DIFFUSION_PARALLEL_BUFFER_CIPHER_H
