//
// Created by Alice on 2017.02.27.
//
#pragma once
#ifndef DIFFUSION_DIFFUSIONEXCEPTION_H
#define DIFFUSION_DIFFUSIONEXCEPTION_H


#include <exception>
#include <stdexcept>

namespace lc{
    class DiffusionException : public std::runtime_error {
    public:
        DiffusionException(const std::string& __arg) : runtime_error(__arg) {}
    };
}

#endif //DIFFUSION_DIFFUSIONEXCEPTION_H
