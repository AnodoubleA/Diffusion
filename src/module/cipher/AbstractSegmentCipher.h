//
// Created by Alice on 2017/12/2.
//

#ifndef DIFFUSION_ABSTRACTSEGMENTCIPHER_H
#define DIFFUSION_ABSTRACTSEGMENTCIPHER_H

#include "SegmentCipher.h"
#include "KeyHandler.h"

namespace lc {
    class AbstractSegmentCipher : public SegmentCipher, public AbstractReusable {
    protected:
        int N = 0, L = 0, fill = 0;
        Padding* padding = nullptr;
        KeyHandler* handler = nullptr;
        Algorithm* algorithm = nullptr;
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
            return AbstractReusable::lock();
        }

        void unlock() override {
            AbstractReusable::unlock();
        }
    };
}
#endif //DIFFUSION_ABSTRACTSEGMENTCIPHER_H
