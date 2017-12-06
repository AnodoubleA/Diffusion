//
// Created by Alice on 2017/12/2.
//

#ifndef DIFFUSION_INFO_H
#define DIFFUSION_INFO_H

#include "../../core/types.h"

namespace lc {
    struct Info {
        byte* key = nullptr;
        int algorithm = 1;     //Version A
        int level = 2;
        int diff = 0;
        int cycle = 1;
        int keySize = 0;
        int options = 0;
        int group = 0;
        int log = 0;
    };
}

#endif //DIFFUSION_INFO_H
