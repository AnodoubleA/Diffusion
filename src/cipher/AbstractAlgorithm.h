//
// Created by Alice on 2017.03.01.
//
#pragma once
#ifndef DIFFUSION_ABSTRACT_H
#define DIFFUSION_ABSTRACT_H

#include <math.h>
#include "Algorithm.h"
#include "a_box.h"
#include "structs.h"
#include "reusable.h"

namespace lc{
    class AbstractAlgorithm : public Algorithm, public AbstractReusable {
    protected:
        int R;          //round
        int N;          //total length
        int H;          //number size
    public:
        void init(Init init) override {
            R = init.R;
            N = init.N;
            H = N >> 1;
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
