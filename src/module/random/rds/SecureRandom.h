//
// Created by Angel on 2017/12/10.
//

#ifndef DIFFUSION_SECURERANDOM_H
#define DIFFUSION_SECURERANDOM_H

#include "../Random.h"
#include "../RandomEngine.h"
#include "../engine/DARandomEngine.h"
#include "../SeedFactory.h"

namespace lc {
    class SecureRandom : public Random {
    protected:
        RandomEngine* engine;
        SeedFactory* factory;
    public:
        ~SecureRandom() {
            delete engine;
        }

        explicit SecureRandom(RandomEngine* engine = nullptr, SeedFactory* factory = nullptr) :
                engine(engine),
                factory(factory) {
            if (engine == nullptr) {
                engine = new DARandomEngine();
            }
            if (factory == nullptr) {

            }
            this->engine = engine;
            this->factory = factory;
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
    };
}
#endif //DIFFUSION_SECURERANDOM_H
