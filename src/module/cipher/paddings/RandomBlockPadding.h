//
// Created by Alice on 2017.03.02.
//
#pragma once
#ifndef DIFFUSION_RANDOMBLOCKPADDING_H
#define DIFFUSION_RANDOMBLOCKPADDING_H

#include <cmath>
#include "../Padding.h"
#include "../../random/Random.h"
#include "../../random/randoms.h"

namespace lc {

    class RandomBlockPadding : public Padding {
    private:
        Random* random = new SecureRandom();
    public:
        ~RandomBlockPadding() {
            delete random;
        }

        int compute(int N) {
            return (int) log2(N);
        }

        void padding(byte* V, int count) override {
            random->next(V, count);
        }
    };
}
#endif //DIFFUSION_RANDOMBLOCKPADDING_H
