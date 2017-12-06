//
// Created by Alice on 2017.03.22.
//

#ifndef DIFFUSION_UNIT_FACTORY_H
#define DIFFUSION_UNIT_FACTORY_H

#include "Algorithm.h"
#include "../../tool/funs.h"
#include "../config/Config.h"
#include "../../tool/converter.h"

namespace lc {
    class AlgorithmFactory {
    public:
        static Algorithm* make(int algorithm);

        static void clear();
    };
}
#endif //DIFFUSION_UNIT_FACTORY_H
