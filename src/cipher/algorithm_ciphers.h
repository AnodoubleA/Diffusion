//
// Created by Alice on 2017.03.10.
//
#pragma once
#ifndef DIFFUSION_CIPHER_UINTS_H
#define DIFFUSION_CIPHER_UINTS_H

#include "AbstractAlgorithm.h"

namespace lc{

    class EncipherAlgorithm : public AbstractAlgorithm {

    public:
        inline void run(byte M[], byte* K[]) override {
            int x = 0, v = R - 1, h = H - 1, X = H;
            for (int i = 1; i <= R; i++) {
                byte* U = K[i - 1];
                byte* V = K[v--];	// remove v=R-1, and replace v-- to --v.
                for (int y = H; y < N;) {   // y += 8;
                    M[y] = unit::S[(M[y] ^ U[y])] ^ M[x];
                    M[x] = unit::S[(M[x] ^ V[x])] ^ M[y];
                    x = (++x) & h, y++; // TO: y+0 (like y+n)
                    M[y] = unit::S[(M[y] ^ U[y])] ^ M[x];
                    M[x] = unit::S[(M[x] ^ V[x])] ^ M[y];
                    x = (++x) & h, y++;
                    M[y] = unit::S[(M[y] ^ U[y])] ^ M[x];
                    M[x] = unit::S[(M[x] ^ V[x])] ^ M[y];
                    x = (++x) & h, y++;
                    M[y] = unit::S[(M[y] ^ U[y])] ^ M[x];
                    M[x] = unit::S[(M[x] ^ V[x])] ^ M[y];
                    x = (++x) & h, y++;
                    M[y] = unit::S[(M[y] ^ U[y])] ^ M[x];
                    M[x] = unit::S[(M[x] ^ V[x])] ^ M[y];
                    x = (++x) & h, y++;
                    M[y] = unit::S[(M[y] ^ U[y])] ^ M[x];
                    M[x] = unit::S[(M[x] ^ V[x])] ^ M[y];
                    x = (++x) & h, y++;
                    M[y] = unit::S[(M[y] ^ U[y])] ^ M[x];
                    M[x] = unit::S[(M[x] ^ V[x])] ^ M[y];
                    x = (++x) & h, y++;
                    M[y] = unit::S[(M[y] ^ U[y])] ^ M[x];
                    M[x] = unit::S[(M[x] ^ V[x])] ^ M[y];
                    x = (++x) & h, y++;
                }
                x = X >> i;
            }
        };
    };

    //============================================================================================================
    class DecipherAlgorithm : public AbstractAlgorithm {
    public:
        inline void run(byte C[], byte* K[]) override {
            int x = 0, v = R - 1, h = H - 1;
            for (int i = 0; i < R; i++, v--) {
                byte* U = K[i];
                byte* V = K[v];
                for (int y = H; y < N;) {
                    C[x] = unit::_S[(C[x] ^ C[y])] ^ U[x];
                    C[y] = unit::_S[(C[x] ^ C[y])] ^ V[y];
                    x = (++x) & h, y++;
                    C[x] = unit::_S[(C[x] ^ C[y])] ^ U[x];
                    C[y] = unit::_S[(C[x] ^ C[y])] ^ V[y];
                    x = (++x) & h, y++;
                    C[x] = unit::_S[(C[x] ^ C[y])] ^ U[x];
                    C[y] = unit::_S[(C[x] ^ C[y])] ^ V[y];
                    x = (++x) & h, y++;
                    C[x] = unit::_S[(C[x] ^ C[y])] ^ U[x];
                    C[y] = unit::_S[(C[x] ^ C[y])] ^ V[y];
                    x = (++x) & h, y++;
                    C[x] = unit::_S[(C[x] ^ C[y])] ^ U[x];
                    C[y] = unit::_S[(C[x] ^ C[y])] ^ V[y];
                    x = (++x) & h, y++;
                    C[x] = unit::_S[(C[x] ^ C[y])] ^ U[x];
                    C[y] = unit::_S[(C[x] ^ C[y])] ^ V[y];
                    x = (++x) & h, y++;
                    C[x] = unit::_S[(C[x] ^ C[y])] ^ U[x];
                    C[y] = unit::_S[(C[x] ^ C[y])] ^ V[y];
                    x = (++x) & h, y++;
                    C[x] = unit::_S[(C[x] ^ C[y])] ^ U[x];
                    C[y] = unit::_S[(C[x] ^ C[y])] ^ V[y];
                    x = (++x) & h, y++;
                }
                x = (1 << i) & h;
            }
        };
    };
}
#endif //DIFFUSION_CIPHER_UINTS_H
