//
// Created by Alice on 2017.04.20.
//

#ifndef DIFFUSION_BUFFER_FACTORY_H
#define DIFFUSION_BUFFER_FACTORY_H

#include <vector>
#include "BufferCipher.h"
#include "../tool/funs.h"
#include "buffer_ciphers.h"
#include "parallel_buffer_cipher.h"

namespace lc{
    extern std::vector<BufferCipher*> buffer_map;

    class BufferCipherFactory {
    public:
        static BufferCipher* make(int options) {
            for (BufferCipher* item:buffer_map) {
                if (item->support(options) && item->lock()) {
                    return item;
                }
            }
            BufferCipher* instance;
            if (contains(options, CO::ENCIPHER, CO::MULTICORE)) {
                instance = new EncipherBuffer();
                goto end;
            }
            if (contains(options, CO::DECIPHER, CO::MULTICORE)) {
                instance = new DecipherBuffer();
                goto end;
            }
            if (contains(options, CO::ENCIPHER | CO::MULTICORE)) {
                instance = new ParallelEncipherBuffer();
                goto end;
            }
            if (contains(options, CO::DECIPHER | CO::MULTICORE)) {
                instance = new ParallelDecipherBuffer();
                goto end;
            }
            end:
            instance->lock();
            buffer_map.push_back(instance);
            return instance;
        }
    };
}
#endif //DIFFUSION_BUFFER_FACTORY_H
