//
// Created by Alice on 2017.02.23.
//
#pragma once
#ifndef DIFFUSION_COMMAND_H
#define DIFFUSION_COMMAND_H

#include "Context.h"
#include "../../module/cmds/options.h"

namespace lc{
    class Command {
    public:
        virtual void execute(Option* option = nullptr, Context* context = nullptr) = 0;
    };
}
#endif //DIFFUSION_COMMAND_H
