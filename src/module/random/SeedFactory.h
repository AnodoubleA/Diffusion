//
// Created by Alice on 2017.03.13.
//

#ifndef DIFFUSION_SEEDFACTORY_H
#define DIFFUSION_SEEDFACTORY_H

#include <vector>
#include "SeedSource.h"

namespace lc{
    class SeedFactory {
    public:
        virtual void init() = 0;

        virtual void regist(SeedSource* source) = 0;

        virtual void pull(byte* accept, int length) = 0;
    };
}
#endif //DIFFUSION_SEEDFACTORY_H
