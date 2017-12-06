//
// Created by Alice on 2017.04.20.
//

#ifndef DIFFUSION_BUFFER_FACTORY_H
#define DIFFUSION_BUFFER_FACTORY_H

#include <vector>
#include "SegmentCipher.h"
#include "../../tool/funs.h"
#include "segments/serial_segment_cipher.h"
#include "segments/parallel_segment_cipher.h"

namespace lc{
    extern std::vector<SegmentCipher*> buffer_map;

    class BufferCipherFactory {
    public:
        static SegmentCipher* make(int options) {
            for (SegmentCipher* item:buffer_map) {
                if (item->support(options) && item->lock()) {
                    return item;
                }
            }
            SegmentCipher* instance;
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
