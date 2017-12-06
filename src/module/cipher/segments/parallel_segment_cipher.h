//
// Created by Alice on 2017.04.20.
//

#ifndef DIFFUSION_PARALLELSEGMENTCIPHER_H
#define DIFFUSION_PARALLELSEGMENTCIPHER_H

#include <omp.h>
#include "serial_segment_cipher.h"

extern int CORE_BUFFER_LOG;
extern int CORE_COUNT_LOG;

namespace lc {
    class ParallelSegmentEncipher : public SerialSegmentEncipher {

    public:

        virtual uint64 run(byte* in, byte* out, uint64 length);

        virtual uint64 run(byte* in, uint64 length) override;

        virtual bool support(int options) {
            return contains(options, CO::ENCIPHER | CO::MULTICORE);
        }
    };

    class ParallelSegmentDecipher : public SerialSegmentDecipher {
    public:

        virtual uint64 run(byte* in, byte* out, uint64 length) override;

        virtual uint64 run(byte* in, uint64 length) override;

        virtual bool support(int options) {
            return contains(options, CO::DECIPHER | CO::MULTICORE);
        }
    };
}
#endif //DIFFUSION_PARALLELSEGMENTCIPHER_H
