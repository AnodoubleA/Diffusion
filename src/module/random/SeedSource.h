//
// Created by Alice on 2017.03.14.
//

#ifndef DIFFUSION_SEED_SOURCE_H
#define DIFFUSION_SEED_SOURCE_H

#include "../../core/types.h"

namespace lc {
    class SeedSource {
    public:
        virtual int pull(byte* buf, int& offset, int max) = 0;

        virtual float reliability() = 0;
    };
}
#endif //DIFFUSION_SEED_SOURCE_H
