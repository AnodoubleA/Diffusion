//
// Created by Alice on 2017.03.10.
//
#pragma once
#ifndef DIFFUSION_DC140713ENCIPHER_V1_H
#define DIFFUSION_DC140713ENCIPHER_V1_H

#include "../AbstractAlgorithm.h"
#include "../Consts.h"

namespace lc {

    class DC140713Encipher_V1 : public AbstractAlgorithm {

    public:
        virtual void run(byte M[], byte* K[]) {
            int x = 0, v = R, h = H - 1, X = H;
            for (int i = 1; i <= R; i++) {
                byte* U = K[i - 1];
                byte* V = K[--v];
                for (int y = H; y < N;) {
                    M[y] = BOX[(M[y] ^ U[y])] ^ M[x];
                    M[x] = BOX[(M[x] ^ V[x])] ^ M[y];
                    x = (++x) & h, y++;
                    M[y] = BOX[(M[y] ^ U[y])] ^ M[x];
                    M[x] = BOX[(M[x] ^ V[x])] ^ M[y];
                    x = (++x) & h, y++;
                    M[y] = BOX[(M[y] ^ U[y])] ^ M[x];
                    M[x] = BOX[(M[x] ^ V[x])] ^ M[y];
                    x = (++x) & h, y++;
                    M[y] = BOX[(M[y] ^ U[y])] ^ M[x];
                    M[x] = BOX[(M[x] ^ V[x])] ^ M[y];
                    x = (++x) & h, y++;
                    M[y] = BOX[(M[y] ^ U[y])] ^ M[x];
                    M[x] = BOX[(M[x] ^ V[x])] ^ M[y];
                    x = (++x) & h, y++;
                    M[y] = BOX[(M[y] ^ U[y])] ^ M[x];
                    M[x] = BOX[(M[x] ^ V[x])] ^ M[y];
                    x = (++x) & h, y++;
                    M[y] = BOX[(M[y] ^ U[y])] ^ M[x];
                    M[x] = BOX[(M[x] ^ V[x])] ^ M[y];
                    x = (++x) & h, y++;
                    M[y] = BOX[(M[y] ^ U[y])] ^ M[x];
                    M[x] = BOX[(M[x] ^ V[x])] ^ M[y];
                    x = (++x) & h, y++;
                }
                x = X >> i;
            }
        };

        virtual int mode() {
            return Consts::ENCIPHER;
        }

    };
}
#endif //DIFFUSION_DC140713ENCIPHER_V1_H
