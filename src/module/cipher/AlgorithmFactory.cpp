//
// Created by Alice on 2017/12/9.
//

#include "AlgorithmFactory.h"
#include "algorithms/DC140713AlgorithmFactory.h"

namespace lc {

    std::vector<AlgorithmFactory*> vector;

    AlgorithmFactory& AlgorithmFactory::factory(int algorithm) {
        int id = algorithm >> 8 & 0xFF;
        for (AlgorithmFactory* factory:vector) {
            if (factory->identity() == id) {
                return *factory;
            }
        }
        AlgorithmFactory* factory = nullptr;
        switch (id) {
            case 0:
            case Algorithms::DC140713 : {
                factory = new DC140713AlgorithmFactory();
                break;
            }
            default:
                throw new DiffusionException("No algorithm found!");
        }
        vector.push_back(factory);
        return *factory;
    }
}
