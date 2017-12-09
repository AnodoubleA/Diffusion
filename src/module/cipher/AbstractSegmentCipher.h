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
        SessionConfig* config = nullptr;
        Padding* padding = nullptr;
        KeyHandler* handler = nullptr;
        Algorithm* algorithm = nullptr;
        Boollock locker;
    public:

        virtual ~AbstractSegmentCipher() {
            delete config;
        }

        void init(SessionConfig* config) override {
            this->config = config;
            handler = config->keyHandler;
            padding = config->padding;
            algorithm = config->algorithm;
            N = config->init->N;
            L = config->init->L;
            fill = 0;
            if (padding != nullptr) {
                fill = padding->compute(N);
            }
            algorithm->init(*config->init);
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
