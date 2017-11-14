//
// Created by Alice on 2017.03.22.
//

#ifndef DIFFUSION_UNIT_FACTORY_H
#define DIFFUSION_UNIT_FACTORY_H

#include "Algorithm.h"
#include "algorithm_ciphers.h"
#include "../tool/funs.h"
#include "../module/config/Config.h"
#include "../tool/converter.h"

namespace lc{

    class AlgorithmFactory {
    public:
        virtual Algorithm* make(int type, int& algorithm) = 0;
    };

    class VersionedAlgorithmFactory : public AlgorithmFactory {

    public:
        Algorithm* make(int type, int& algorithm) override {
            int version = algorithm >> 8 & 0xFF;
            version = version == 0 ? 1 : version;
            if (version > 1) {
                throw DiffusionException(I18N->gf(ERROR_AVS_USP, version));
            }
            algorithm |= version << 8;
            int name = algorithm & 0xFF;
            if (type == CO::ENCIPHER) {
                return new EncipherAlgorithm();
            }
            if (type == CO::DECIPHER) {
                return new DecipherAlgorithm();
            }
            throw DiffusionException("system error for make algorithm: " + type);
        }
    };
}
#endif //DIFFUSION_UNIT_FACTORY_H
