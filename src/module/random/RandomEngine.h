//
// Created by Alice on 2017/12/10.
//

#ifndef DIFFUSION_RANDOMENGINE_H
#define DIFFUSION_RANDOMENGINE_H

#include "../../core/types.h"

namespace lc {
    class RandomEngine {
    public:
        virtual void seed(byte seed[], int length) = 0;

        virtual void next(byte accept[], int length) = 0;

        virtual byte next() = 0;

        /**
         * Get a size of this engine's seed need.
         * @return Need's seed size.
         */
        virtual int needSeed() = 0;
    };
};


#endif //DIFFUSION_RANDOMENGINE_H
