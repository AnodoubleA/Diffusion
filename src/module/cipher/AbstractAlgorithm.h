//
// Created by Alice on 2017.03.01.
//
#pragma once
#ifndef DIFFUSION_ABSTRACT_ALGORITHM_H
#define DIFFUSION_ABSTRACT_ALGORITHM_H

#include <math.h>
#include "AlgorithmInfo.h"
#include "Algorithm.h"
#include "Boollock.h"

namespace lc {
    class AbstractAlgorithm : public Algorithm{
    protected:
        int R;          //round
        int N;          //total length
        int H;          //number size
        byte* BOX = nullptr;
        Boollock locker;
    public:
        void init(AlgorithmInfo& init) override {
            R = init.R;
            N = init.N;
            H = N >> 1;
            BOX = init.BOX;
        }

        int version() override {
            return 1;
        }

        int identity() override {
            return 1;
        }

        bool lock() override {
            locker.lock();
        }

        void unlock() override {
            locker.unlock();
        }
    };
}
#endif //DIFFUSION_STANDARDUNIT_H
