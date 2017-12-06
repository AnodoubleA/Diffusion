//
// Created by Alice on 2017/12/2.
//
#include "Algorithm.h"
#include "AlgorithmFactory.h"
#include "DefaultAlgorithm.h"

namespace lc {
    std::vector<Algorithm*> vector;

    Algorithm* AlgorithmFactory::make(int algorithm) {
        int V = (algorithm >> 16) & 0xFF;
        int T = (algorithm) & 0xFF;
        for (Algorithm* e:vector) {
            if (e->algorithm() == T && e->version() == V && e->lock()) {
                return e;
            }
        }
        Algorithm* def = new DefaultAlgorithm();
        vector.push_back(def);
        return def;
    }

    void AlgorithmFactory::clear() {
        vector.clear();
    }
}