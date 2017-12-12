//
// Created by Alice on 2017.03.02.
//
#pragma once
#ifndef DIFFUSION_RANDOM_H
#define DIFFUSION_RANDOM_H

#include "../../core/types.h"

namespace lc{

    class Random {

    public:
        virtual void seed(byte seed[], int length) = 0;

        virtual void next(byte accept[], int length) = 0;

        virtual byte next() = 0;
    };
}
#endif //DIFFUSION_RANDOM_H
