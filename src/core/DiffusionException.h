//
// Created by Alice on 2017.02.27.
//
#pragma once
#ifndef DIFFUSION_DIFFUSIONEXCEPTION_H
#define DIFFUSION_DIFFUSIONEXCEPTION_H


#include <exception>
#include <stdexcept>
#include <vector>
#include <cstdarg>
#include "types.h"

namespace lc {
    class DiffusionException : public std::runtime_error {
    private:
        const char* key;
        std::vector<void*> args;
    public:

        explicit DiffusionException(const char* key, ...) : runtime_error(nullptr) {
            this->key = key;
            std::vector<void*> args;
            va_list start;
            va_start(start, key);
            void* get;
            while ((get = va_arg(start, void*)) != 0) {
                args.push_back(get);
            }
            va_end(start);
        }

        const char* getKey() {
            return key;
        }

        std::vector<void*>& getArguments() {
            return args;
        }
    };
}

#endif //DIFFUSION_DIFFUSIONEXCEPTION_H
