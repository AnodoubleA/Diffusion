//
// Created by Angel on 2017/12/6.
//

#ifndef DIFFUSION_BOOLLOCK_H
#define DIFFUSION_BOOLLOCK_H

#include "../../core/Reusable.h"

namespace lc {
    class BoolLock : public Reusable {
    protected:
        bool idle = true;
    public:
        virtual bool lock() override {
            if (!idle) {
                return false;
            }
            return !(idle = false);
        }

        virtual void unlock() override {
            idle = true;
        }
    };
}
#endif //DIFFUSION_BOOLLOCK_H
