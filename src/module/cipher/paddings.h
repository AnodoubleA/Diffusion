//
// Created by Alice on 2017.03.02.
//
#pragma once
#ifndef DIFFUSION_PADDINGS_H
#define DIFFUSION_PADDINGS_H

#include <cmath>
#include "Padding.h"
#include "../random/Random.h"
#include "../../cipher/Consts.h"
#include "../cmds/options.h"
#include "../random/randoms.h"

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
