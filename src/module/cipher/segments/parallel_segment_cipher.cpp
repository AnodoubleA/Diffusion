//
// Created by Angel on 2017/12/6.
//
#include <omp.h>
#include "../../../core/types.h"
#include "parallel_segment_cipher.h"

extern int CORE_BUFFER_LOG;
extern int CORE_COUNT_LOG;

namespace lc {
    uint64 ParallelSegmentEncipher::run(byte* in, uint64 length) {
        int k = 0;
        int s = 1 << CORE_BUFFER_LOG;
        int c = 1 << CORE_COUNT_LOG;
        uint64 round = (length >> CORE_BUFFER_LOG >> CORE_COUNT_LOG) << CORE_COUNT_LOG;
        uint64 done = (round << CORE_BUFFER_LOG);

#pragma omp parallel for firstprivate(s, c, k)

        for (int i = 0; i < round; i++) {
            int p = k++ * c + omp_get_thread_num();
            ParallelSegmentEncipher::run(in + (p * s), s);
        }
        if (done == length)return length;
        return SerialSegmentEncipher::run(in + done, length - done) + done;
    }


    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // ParallelSegmentDecipher code
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    uint64 ParallelSegmentDecipher::run(byte* in, uint64 length) {
        int k = 0;
        int s = 1 << CORE_BUFFER_LOG;
        int c = 1 << CORE_COUNT_LOG;
        uint64 round = (length >> CORE_BUFFER_LOG >> CORE_COUNT_LOG) << CORE_COUNT_LOG;
        uint64 done = round << CORE_BUFFER_LOG;

#pragma omp parallel for firstprivate(s, c, k)

        for (int i = 0; i < round; i++) {
            int p = k++ * c + omp_get_thread_num();
            SerialSegmentDecipher::run(in + (p * s), s);
        }
        if (done == length)return length;
        return SerialSegmentDecipher::run(in + done, length - done) + done;
    }
}
