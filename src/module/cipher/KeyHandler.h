//
// Created by Alice on 2017.03.02.
//
#pragma once
#ifndef DIFFUSION_KEYHANDLER_H
#define DIFFUSION_KEYHANDLER_H

#include "../../core/DiffusionException.h"
#include "../../cipher/version.h"
#include "AlgorithmInfo.h"
#include "../../core/Reusable.h"
#include "CipherInfo.h"

namespace lc{
    class KeyHandler : public Version, public Reusable {
    public:
        
        virtual void init(CipherInfo& info, AlgorithmInfo& init) = 0;

        virtual byte** update()  = 0;

        virtual int level() = 0;
    };
}
#endif //DIFFUSION_KEYHANDLER_H
