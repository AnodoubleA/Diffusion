//
// Created by Alice on 2017.03.22.
//

#ifndef DIFFUSION_UNIT_FACTORY_H
#define DIFFUSION_UNIT_FACTORY_H

#include "Algorithm.h"
#include "../../tool/funs.h"
#include "../config/Config.h"
#include "../../tool/converter.h"
#include "CipherInfo.h"

namespace lc {
    class AlgorithmFactory {
    public:
        virtual Algorithm* make(CipherInfo& info, int& algorithm) = 0;

        virtual int identity() = 0;

        virtual void clear() = 0;

        static AlgorithmFactory& factory(int algorithm);
    };
}
#endif //DIFFUSION_UNIT_FACTORY_H
