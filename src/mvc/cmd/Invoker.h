//
// Created by Alice on 2017.02.27.
//
#pragma once
#ifndef DIFFUSION_INVOKER_H
#define DIFFUSION_INVOKER_H

#include "../../core/Object.h"
#include "Command.h"

namespace lc{
    class Invoker : public Object {

    public:
        virtual void invoke(Command* command, Option* option = nullptr) = 0;
    };
}
#endif //DIFFUSION_INVOKER_H
