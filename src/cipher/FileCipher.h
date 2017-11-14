//
// Created by Alice on 2017.03.03.
//
#pragma once
#ifndef DIFFUSION_FILECIPHER_H
#define DIFFUSION_FILECIPHER_H

#include "../core/DiffusionException.h"
#include "structs.h"
#include "version.h"

namespace lc{

    class FileCipher : public Version {
    public:
        virtual void init(Init& init, Info& info, BufferContact* contact)  = 0;

        virtual void deinit() = 0;

        virtual uint64 run(const std::string& in, const std::string& out) throw(DiffusionException) = 0;
    };
}

#endif //DIFFUSION_FILECIPHER_H
