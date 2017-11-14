//
// Created by Alice on 2017.02.24.
//
#pragma once
#ifndef DIFFUSION_COMMANDEXCEPTION_H
#define DIFFUSION_COMMANDEXCEPTION_H

#include <exception>
#include <stdexcept>
#include "../core/Object.h"
#include "../core/DiffusionException.h"

namespace lc{
    class CommandException : public DiffusionException {
    public:
        CommandException(const std::string& message) : DiffusionException(message) {}
    };
}

#endif //DIFFUSION_COMMANDEXCEPTION_H
