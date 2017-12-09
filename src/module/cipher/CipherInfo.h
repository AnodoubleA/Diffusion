//
// Created by Alice on 2017/12/2.
//

#ifndef DIFFUSION_CIPHERINFO_H
#define DIFFUSION_CIPHERINFO_H

#include "../../core/types.h"

namespace lc {
    struct CipherInfo {
        byte* key = nullptr;
        int algorithm = 1;
        int level = 2;
        int diff = 0;
        int cycle = 1;
        int keySize = 0;
        int group = 0;
        int log = 0;
        uint64 options = 0;
    };
}

#endif //DIFFUSION_CIPHERINFO_H
