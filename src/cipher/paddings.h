//
// Created by Alice on 2017.03.02.
//
#pragma once
#ifndef DIFFUSION_PADDINGS_H
#define DIFFUSION_PADDINGS_H

#include <cmath>
#include "Padding.h"
#include "../module/random/Random.h"
#include "Consts.h"
#include "../module/cmds/options.h"
#include "../module/random/randoms.h"

namespace lc{

    class RandomBlockPadding : public Padding {
    private:
        Random* random = new SecureRandom();
    public:
        int compute(int N) {
            return (int) log2(N);
        }

        void padding(byte* V, int count) override {
            random->next(V, count);
        }
    };

    class PaddingFactory {
    public:
        static Padding* make(int options) {
            if (options & CipherOption::PADDING) {
                return new RandomBlockPadding();
            }
            return nullptr;
        }
    };
}
#endif //DIFFUSION_PADDINGS_H
