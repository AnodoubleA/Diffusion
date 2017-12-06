//
// Created by Alice on 2017.03.01.
//
#pragma once
#ifndef DIFFUSION_ABSTRACT_ALGORITHM_H
#define DIFFUSION_ABSTRACT_ALGORITHM_H

#include <math.h>
#include "Init.h"
#include "Algorithm.h"
#include "../../core/reusable.h"

namespace lc {
    class AbstractAlgorithm : public Algorithm, public AbstractReusable {
    protected:
        int R;          //round
        int N;          //total length
        int H;          //number size
        byte* S_BOX = nullptr;
        byte* I_BOX = nullptr;
    public:
        void init(Init& init) override {
            R = init.R;
            N = init.N;
            H = N >> 1;
            S_BOX = init.BOX;
            I_BOX = init.BOS;
        }

        int version() override {
            return 1;
        }

        bool lock() override {
            return AbstractReusable::lock();
        }

        void unlock() override {
            AbstractReusable::unlock();
        }
    };
}
#endif //DIFFUSION_STANDARDUNIT_H
