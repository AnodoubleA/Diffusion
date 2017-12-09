//
// Created by Alice on 2017/12/9.
//

#ifndef DIFFUSION_ABSTRACTALGORITHMFACTORY_H
#define DIFFUSION_ABSTRACTALGORITHMFACTORY_H

#include "../AlgorithmFactory.h"

namespace lc {
    class AbstractAlgorithmFactory : public AlgorithmFactory {
    protected:
        std::vector<Algorithm*> encs;
        std::vector<Algorithm*> decs;
    public:

        virtual Algorithm* make(int mode, int& algorithm) {

            return getAlgorithm(mode, algorithm);
        }

        virtual void clear() {
            for (Algorithm* e : encs) {
                delete e;
            }
            for (Algorithm* e : decs) {
                delete e;
            }
            encs.clear();
            decs.clear();
        }

    protected:

        virtual Algorithm* newAlgorithm(int mode, int& algorithm) = 0;

    private:
        virtual Algorithm* getAlgorithm(int mode, int& algorithm) {
            std::vector<Algorithm*> vector = mode == Consts::ENCIPHER ? encs : decs;
            int V = (algorithm >> 8) & 0xFF;
            int T = (algorithm) & 0xFF;
            for (Algorithm* e:vector) {
                if (e->identity() == T && e->version() == V && e->lock()) {
                    return e;
                }
            }
            Algorithm* instance = newAlgorithm(Consts::ENCIPHER, algorithm);
            if (instance == nullptr) {
                //TODO throw exception
                throw new DiffusionException("");
            }
            vector.push_back(instance);
            return instance;
        }
    };
}
#endif //DIFFUSION_ABSTRACTALGORITHMFACTORY_H
