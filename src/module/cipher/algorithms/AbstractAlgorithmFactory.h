//
// Created by Alice on 2017/12/9.
//

#ifndef DIFFUSION_ABSTRACTALGORITHMFACTORY_H
#define DIFFUSION_ABSTRACTALGORITHMFACTORY_H

#include "../AlgorithmFactory.h"
#include "../CipherInfo.h"

namespace lc {
    class AbstractAlgorithmFactory : public AlgorithmFactory {
    protected:
        std::vector<Algorithm*> encs;
        std::vector<Algorithm*> decs;
    public:

        virtual Algorithm* make(CipherInfo& info, int& algorithm) {

            return getAlgorithm(info, algorithm);
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

        virtual Algorithm* newAlgorithm(CipherInfo& info, int& algorithm) = 0;

    private:
        virtual Algorithm* getAlgorithm(CipherInfo& info, int& algorithm) {
            std::vector<Algorithm*> vector = (info.options & Consts::ENCIPHER) != 0 ? encs : decs;
            int V = (algorithm >> 8) & 0xFF;
            int T = (algorithm) & 0xFF;
            for (Algorithm* e:vector) {
                if (e->identity() == T && e->version() == V && e->lock()) {
                    return e;
                }
            }
            Algorithm* instance = newAlgorithm(info, algorithm);
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
