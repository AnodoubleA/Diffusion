//
// Created by Alice on 2017.03.02.
//
#pragma once
#ifndef DIFFUSION_BLOCKCIPHERPADDING_H
#define DIFFUSION_BLOCKCIPHERPADDING_H

#include "../core/types.h"

namespace lc{
    class Padding {

    public:
        virtual int compute(int N) = 0;

        virtual void padding(byte* V, int count) = 0;
    };
}
#endif //DIFFUSION_BLOCKCIPHERPADDING_H
