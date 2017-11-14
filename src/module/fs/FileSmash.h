//
// Created by Alice on 2017.03.03.
//
#pragma once
#ifndef DIFFUSION_FILESMASH_H
#define DIFFUSION_FILESMASH_H

#include "../random/Random.h"
#include "../config/Config.h"
#include "../fm/filemapping.h"
#include "../../cipher/reusable.h"
#include "../fm/fm_factory.h"
#include "../random/randoms.h"

namespace lc{
    class FileSmash : public Reusable {
    public:
        virtual bool smash(const std::string& src, int times) throw(DiffusionException)= 0;
    };
}
#endif //DIFFUSION_FILESMASH_H
