//
// Created by Alice on 2017.03.10.
//
#pragma once
#ifndef DIFFUSION_DC140713DECIPHER_V1_H
#define DIFFUSION_DC140713DECIPHER_V1_H

#include "../AbstractAlgorithm.h"
#include "../Consts.h"

namespace lc {

    class DC140713Decipher_V1 : public AbstractAlgorithm {

    public:
        virtual void run(byte C[], byte* K[]) {
            int x = 0, v = R - 1, h = H - 1;
            for (int i = 0; i < R; i++, v--) {
                byte* U = K[i];
                byte* V = K[v];
                for (int y = H; y < N;) {
                    C[x] = BOX[(C[x] ^ C[y])] ^ U[x];
                    C[y] = BOX[(C[x] ^ C[y])] ^ V[y];
                    x = (++x) & h, y++;
                    C[x] = BOX[(C[x] ^ C[y])] ^ U[x];
                    C[y] = BOX[(C[x] ^ C[y])] ^ V[y];
                    x = (++x) & h, y++;
                    C[x] = BOX[(C[x] ^ C[y])] ^ U[x];
                    C[y] = BOX[(C[x] ^ C[y])] ^ V[y];
                    x = (++x) & h, y++;
                    C[x] = BOX[(C[x] ^ C[y])] ^ U[x];
                    C[y] = BOX[(C[x] ^ C[y])] ^ V[y];
                    x = (++x) & h, y++;
                    C[x] = BOX[(C[x] ^ C[y])] ^ U[x];
                    C[y] = BOX[(C[x] ^ C[y])] ^ V[y];
                    x = (++x) & h, y++;
                    C[x] = BOX[(C[x] ^ C[y])] ^ U[x];
                    C[y] = BOX[(C[x] ^ C[y])] ^ V[y];
                    x = (++x) & h, y++;
                    C[x] = BOX[(C[x] ^ C[y])] ^ U[x];
                    C[y] = BOX[(C[x] ^ C[y])] ^ V[y];
                    x = (++x) & h, y++;
                    C[x] = BOX[(C[x] ^ C[y])] ^ U[x];
                    C[y] = BOX[(C[x] ^ C[y])] ^ V[y];
                    x = (++x) & h, y++;
                }
                x = (1 << i) & h;
            }
        };

        virtual int mode() {
            return Consts::DECIPHER;
        }
    };
}
#endif //DIFFUSION_DC140713DECIPHER_V1_H
