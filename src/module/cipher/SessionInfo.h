//
// Created by Angel on 2017/12/7.
//

#ifndef DIFFUSION_SESSIONINFO_H
#define DIFFUSION_SESSIONINFO_H

#include "CipherInfo.h"
#include "AlgorithmInfo.h"
#include "KeyHandler.h"
#include "Padding.h"
#include "Algorithm.h"

namespace lc {
    class SessionInfo {
    public:
        ~SessionInfo() = default{
            delete init;
            delete keyHandler;
            delete padding;
            delete algorithm;
        }
        AlgorithmInfo* init = nullptr;
        KeyHandler* keyHandler  = nullptr;
        Padding* padding        = nullptr;
        Algorithm* algorithm    = nullptr;
        CipherInfo* info;
    };
}
#endif //DIFFUSION_SESSIONINFO_H
