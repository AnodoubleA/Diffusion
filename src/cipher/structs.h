//
// Created by Alice on 2017.03.02.
//
#pragma once
#ifndef DIFFUSION_STRUCTS_H
#define DIFFUSION_STRUCTS_H

#include "../module/cmds/options.h"
#include "../core/types.h"

namespace lc{
    struct Init {
        int N = 0;
        int L = 0;
        int R = 0;
    };

    class Info {
    public:
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
#endif //DIFFUSION_STRUCTS_H
