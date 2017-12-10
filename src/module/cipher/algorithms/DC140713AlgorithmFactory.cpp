//
// Created by Alice on 2017/12/9.
//
#include "DC140713AlgorithmFactory.h"
#include "DC140713Encipher_V1.h"
#include "DC140713Decipher_V1.h"

namespace lc {
    Algorithm* DC140713AlgorithmFactory::newAlgorithm(CipherInfo& info, int& algorithm) {
        switch (algorithm >> 8 & 0xFF) {
            case 0:
            case 1:
                if ((info.options & Consts::ENCIPHER) != 0) return new DC140713Encipher_V1();
                return new DC140713Decipher_V1();
        }
        return nullptr;
    }

}
