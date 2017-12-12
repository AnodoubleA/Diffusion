//
// Created by Angel on 2017/12/10.
//

#ifndef DIFFUSION_FASTRANDOM_H
#define DIFFUSION_FASTRANDOM_H

#include <random>
#include <ctime>
#include "../Random.h"
#include "../SeedFactory.h"
#include "../engine/MersenneTwisterEngine.h"

namespace lc {
    class FastRandom : public Random {
        RandomEngine* engine;
        SeedFactory* factory;
    public:
        ~FastRandom() {
            delete (engine);
            delete (factory);
        }

        FastRandom(RandomEngine* engine = nullptr) {
            if (engine == nullptr) {
                engine = new MersenneTwisterEngine();
            }
            this->engine = engine;
            updateSeed();
        }

        void seed(byte* seed, int length) override {

            engine->seed(seed, length);
        }

        void next(byte* accept, int length) override {

            engine->next(accept, length);
        }

        byte next() override {

            return engine->next();
        }

    protected:
        void updateSeed() {
            time_t t;
            ctime(&t);
            byte buf[4];
            buf[0] = t >> 24 & 0xFF;
            buf[1] = t >> 16 & 0xFF;
            buf[2] = t >> 8 & 0xFF;
            buf[3] = t >> 0 & 0xFF;
            engine->seed(buf, 4);
        }
    };
}
#endif //DIFFUSION_FASTRANDOM_H
