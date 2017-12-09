//
// Created by Alice on 2017/12/2.
//

#ifndef DIFFUSION_ABSTRACTSEGMENTCIPHER_H
#define DIFFUSION_ABSTRACTSEGMENTCIPHER_H

#include "SegmentCipher.h"
#include "KeyHandler.h"
#include "Padding.h"
#include "Algorithm.h"
#include "Boollock.h"

namespace lc {
    class AbstractSegmentCipher : public SegmentCipher {
    protected:
        int N = 0, L = 0, fill = 0;
        SessionInfo* info = nullptr;
        Padding* padding = nullptr;
        KeyHandler* handler = nullptr;
        Algorithm* algorithm = nullptr;
        Boollock locker;
    public:

        virtual ~AbstractSegmentCipher() {
            delete info;
        }

        void init(SessionInfo* info) override {
            this->info = info;
            handler = info->keyHandler;
            padding = info->padding;
            algorithm = info->algorithm;
            N = info->init->N;
            L = info->init->L;
            fill = 0;
            if (padding != nullptr) {
                fill = padding->compute(N);
            }
            handler->init(info->info);
            algorithm->init(*info->init);
        }

        void deinit() override {
            unlock();
        }

        bool lock() override {
            return locker.lock();
        }

        void unlock() override {
            locker.unlock();
        }
    };
}
#endif //DIFFUSION_ABSTRACTSEGMENTCIPHER_H
