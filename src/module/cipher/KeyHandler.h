//
// Created by Alice on 2017.03.02.
//
#pragma once
#ifndef DIFFUSION_KEYHANDLER_H
#define DIFFUSION_KEYHANDLER_H

#include "../../cipher/structs.h"
#include "../../core/DiffusionException.h"
#include "../../cipher/version.h"

namespace lc{
    class KeyHandler : public Version, public Reusable {
    public:
        virtual void init(Init& init, Info& info) = 0;

        virtual byte** update()  = 0;

        virtual int version() = 0;

        virtual int level() = 0;
    };
}
#endif //DIFFUSION_KEYHANDLER_H
