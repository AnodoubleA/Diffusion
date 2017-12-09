//
// Created by Alice on 2017.03.02.
//
#pragma once
#ifndef DIFFUSION_BOX_H
#define DIFFUSION_BOX_H
namespace lc {
    class Consts {
    public:
        static const int ENCIPHER = 1;
        static const int DECIPHER = 0;
    };

    class Algorithms {
    public:
        static const int DC140713 = 1;
    };

    class KeyHandlers {
    public:
        static const int LEVEL_1 = 1;
        static const int LEVEL_2 = 2;
    };
}
#endif //DIFFUSION_BOX_H
