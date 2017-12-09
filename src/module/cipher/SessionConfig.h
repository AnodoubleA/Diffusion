//
// Created by Angel on 2017/12/7.
//

#ifndef DIFFUSION_SESSIONCONFIG_H
#define DIFFUSION_SESSIONCONFIG_H

#include "Info.h"
#include "Init.h"
#include "KeyHandler.h"
#include "Padding.h"
#include "Algorithm.h"

namespace lc {
    class SessionConfig {
    public:
        ~SessionConfig() = default{
            delete init;
            delete keyHandler;
            delete padding;
            delete algorithm;
        }
        Init* init = nullptr;
        KeyHandler* keyHandler  = nullptr;
        Padding* padding        = nullptr;
        Algorithm* algorithm    = nullptr;
        uint64 options = 0;
    };
}
#endif //DIFFUSION_SESSIONCONFIG_H
