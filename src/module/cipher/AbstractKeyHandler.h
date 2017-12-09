//
// Created by Angel on 2017/12/7.
//

#ifndef DIFFUSION_ABSTRACTKEYHANDLER_H
#define DIFFUSION_ABSTRACTKEYHANDLER_H

#include "KeyHandler.h"
#include "AlgorithmInfo.h"
#include "CipherInfo.h"
#include "Boollock.h"

namespace lc {
    class AbstractKeyHandler : public KeyHandler {
    private:
        Boollock locker;
    public:

        int version() override {
            return 1;
        }

        bool lock() override {
            return locker.lock();
        }

        void unlock() override {
            locker.unlock();
        }
    };
}
#endif //DIFFUSION_ABSTRACTKEYHANDLER_H
