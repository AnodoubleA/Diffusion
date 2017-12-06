//
// Created by Alice on 2017/12/2.
//

#ifndef DIFFUSION_ABSTRACTSEGMENTCIPHER_H
#define DIFFUSION_ABSTRACTSEGMENTCIPHER_H

#include "SegmentCipher.h"
#include "KeyHandler.h"
#include "Padding.h"
#include "Algorithm.h"

namespace lc {
    class AbstractSegmentCipher : public SegmentCipher{
    protected:
        int N = 0, L = 0, fill = 0;
        Padding* padding = nullptr;
        KeyHandler* handler = nullptr;
        Algorithm* algorithm = nullptr;
        Boollock locker;
    public:

        void setPadding(Padding* padding) {
            this->padding = padding;
        }

        void setHandler(KeyHandler& handler) {
            this->handler = &handler;
        }

        void setAlgorithm(Algorithm& algorithm) {
            this->algorithm = &algorithm;
        }

        void init(Init& init, Info& info) override {
            N = init.N;
            L = init.L;
            fill = 0;
            if (padding != nullptr) {
                fill = padding->compute(init.N);
            }
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
