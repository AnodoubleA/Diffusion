//
// Created by Alice on 2017.03.08.
//
#pragma once
#ifndef DIFFUSION_FILTER_H
#define DIFFUSION_FILTER_H

#include "../tool/Strings.h"

namespace lc{
    template<typename T>
    class Filter {
    public :
        virtual bool accept(const T& value) =0;
    };
}

#endif //DIFFUSION_FILTER_H
