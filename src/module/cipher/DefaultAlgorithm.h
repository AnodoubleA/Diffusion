//
// Created by Alice on 2017.03.10.
//
#pragma once
#ifndef DIFFUSION_DEFAULTALGORITHM_H
#define DIFFUSION_DEFAULTALGORITHM_H

#include "AbstractAlgorithm.h"

namespace lc{

    class DefaultAlgorithm : public AbstractAlgorithm {

    public:
        void enc(byte M[], byte* K[]) override {
            int x = 0, v = R, h = H - 1, X = H;
            for (int i = 1; i <= R; i++) {
                byte* U = K[i - 1];
                byte* V = K[--v];
                for (int y = H; y < N;) {
                    M[y] = S_BOX[(M[y] ^ U[y])] ^ M[x];
                    M[x] = S_BOX[(M[x] ^ V[x])] ^ M[y];
                    x = (++x) & h, y++;
                    M[y] = S_BOX[(M[y] ^ U[y])] ^ M[x];
                    M[x] = S_BOX[(M[x] ^ V[x])] ^ M[y];
                    x = (++x) & h, y++;
                    M[y] = S_BOX[(M[y] ^ U[y])] ^ M[x];
                    M[x] = S_BOX[(M[x] ^ V[x])] ^ M[y];
                    x = (++x) & h, y++;
                    M[y] = S_BOX[(M[y] ^ U[y])] ^ M[x];
                    M[x] = S_BOX[(M[x] ^ V[x])] ^ M[y];
                    x = (++x) & h, y++;
                    M[y] = S_BOX[(M[y] ^ U[y])] ^ M[x];
                    M[x] = S_BOX[(M[x] ^ V[x])] ^ M[y];
                    x = (++x) & h, y++;
                    M[y] = S_BOX[(M[y] ^ U[y])] ^ M[x];
                    M[x] = S_BOX[(M[x] ^ V[x])] ^ M[y];
                    x = (++x) & h, y++;
                    M[y] = S_BOX[(M[y] ^ U[y])] ^ M[x];
                    M[x] = S_BOX[(M[x] ^ V[x])] ^ M[y];
                    x = (++x) & h, y++;
                    M[y] = S_BOX[(M[y] ^ U[y])] ^ M[x];
                    M[x] = S_BOX[(M[x] ^ V[x])] ^ M[y];
                    x = (++x) & h, y++;
                }
                x = X >> i;
            }
        };

        void dec(byte C[], byte* K[]) override {
            int x = 0, v = R - 1, h = H - 1;
            for (int i = 0; i < R; i++, v--) {
                byte* U = K[i];
                byte* V = K[v];
                for (int y = H; y < N;) {
                    C[x] = I_BOX[(C[x] ^ C[y])] ^ U[x];
                    C[y] = I_BOX[(C[x] ^ C[y])] ^ V[y];
                    x = (++x) & h, y++;
                    C[x] = I_BOX[(C[x] ^ C[y])] ^ U[x];
                    C[y] = I_BOX[(C[x] ^ C[y])] ^ V[y];
                    x = (++x) & h, y++;
                    C[x] = I_BOX[(C[x] ^ C[y])] ^ U[x];
                    C[y] = I_BOX[(C[x] ^ C[y])] ^ V[y];
                    x = (++x) & h, y++;
                    C[x] = I_BOX[(C[x] ^ C[y])] ^ U[x];
                    C[y] = I_BOX[(C[x] ^ C[y])] ^ V[y];
                    x = (++x) & h, y++;
                    C[x] = I_BOX[(C[x] ^ C[y])] ^ U[x];
                    C[y] = I_BOX[(C[x] ^ C[y])] ^ V[y];
                    x = (++x) & h, y++;
                    C[x] = I_BOX[(C[x] ^ C[y])] ^ U[x];
                    C[y] = I_BOX[(C[x] ^ C[y])] ^ V[y];
                    x = (++x) & h, y++;
                    C[x] = I_BOX[(C[x] ^ C[y])] ^ U[x];
                    C[y] = I_BOX[(C[x] ^ C[y])] ^ V[y];
                    x = (++x) & h, y++;
                    C[x] = I_BOX[(C[x] ^ C[y])] ^ U[x];
                    C[y] = I_BOX[(C[x] ^ C[y])] ^ V[y];
                    x = (++x) & h, y++;
                }
                x = (1 << i) & h;
            }
        };
    };
}
#endif //DIFFUSION_DEFAULTALGORITHM_H
