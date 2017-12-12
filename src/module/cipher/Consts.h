//
// Created by Alice on 2017.03.02.
//
#pragma once
#ifndef DIFFUSION_BOX_H
#define DIFFUSION_BOX_H
namespace lc {
    class Consts {
    public:
        static const int ENCIPHER            = 1 << 0;
        static const int DECIPHER            = 1 << 1;
        static const int PADDING             = 1 << 2;
        static const int MULTICORE           = 1 << 3;
        static const int GPU                 = 1 << 4;
        static const int TEXT = 0;
        static const int FILE = 1;
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
