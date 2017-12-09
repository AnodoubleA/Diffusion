//
// Created by Alice on 2017.02.27.
//
#pragma once
#ifndef DIFFUSION_DIFFUSIONEXCEPTION_H
#define DIFFUSION_DIFFUSIONEXCEPTION_H


#include <exception>
#include <stdexcept>
#include "types.h"

namespace lc {
    class DiffusionException : public std::runtime_error {
        uint64 code;
    public:
        DiffusionException(const std::string& __arg) : runtime_error(__arg) {

        }

        DiffusionException(uint64 code, const std::string& __arg) : runtime_error(__arg) {
            this->code = code;
        }
    };
}

#endif //DIFFUSION_DIFFUSIONEXCEPTION_H
