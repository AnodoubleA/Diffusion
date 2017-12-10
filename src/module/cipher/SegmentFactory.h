//
// Created by Alice on 2017.04.20.
//

#ifndef DIFFUSION_SEGMENTFACTORY_H
#define DIFFUSION_SEGMENTFACTORY_H

#include <vector>
#include "SegmentCipher.h"
#include "../../tool/funs.h"
#include "segments/serial_segment_cipher.h"
#include "segments/parallel_segment_cipher.h"

namespace lc {
    class SegmentFactory {
    public:
        static SegmentCipher* make(CipherInfo& info);

        static void clear();
    };
}
#endif //DIFFUSION_SEGMENTFACTORY_H
