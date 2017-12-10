//
// Created by Alice on 2017/12/9.
//

#ifndef DIFFUSION_DC140713ALGORITHMFACTORY_H
#define DIFFUSION_DC140713ALGORITHMFACTORY_H

#include "AbstractAlgorithmFactory.h"

namespace lc {
    class DC140713AlgorithmFactory : public AbstractAlgorithmFactory {
    public:
        virtual int identity() {

            return Algorithms::DC140713;
        }

    protected:
        Algorithm* newAlgorithm(CipherInfo& info, int& algorithm) override ;
    };
}
#endif //DIFFUSION_DC140713ALGORITHMFACTORY_H
