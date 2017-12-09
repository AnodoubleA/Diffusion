//
// Created by Angel on 2017/12/7.
//

#ifndef DIFFUSION_MIXKEYHANDLER_H
#define DIFFUSION_MIXKEYHANDLER_H

#include <cmath>
#include "../AbstractKeyHandler.h"
#include "../../../core/types.h"
#include "key_box.h"

namespace lc {
    class MixKeyHandler : public AbstractKeyHandler {
    protected:
        int N, R, H;
        int _N = 0, _R, _H, _P;
        byte** K = nullptr;
    public:
        ~MixKeyHandler() {
            delete[] K;
        }

        void init(CipherInfo& info, AlgorithmInfo& init) override {
            AbstractKeyHandler::init(info, init);
            N = init.N;
            R = init.R;
            H = N >> 1;
            if (_N != R) {
                if (K != nullptr)delete[](K);
                alloc(init);
            }
        }

        byte** update() override {
            return K;
        }

    protected:
        virtual void alloc(AlgorithmInfo& init) {
            _N = init.R;
            _R = (int) ceil(log2(R));
            _P = 1 << _R;
            _H = _N >> 1;
            _R++;
            byte* T = new byte[_R * _N];
            K = new byte* [_R];
            for (int i = 0; i < _N; i++) {
                K[i] = T + (i * _N);
            }
        }

        virtual void init_key(byte* key, int length) {
            int index = 0, x = 0;
            for (int i = 0; i < R; i++) {
                for (int j = 0; j < N; j++) {
                    byte v = (byte) (x < length ? key[x] : index++);
                    K[i][j] = x & 1 ? key::S1[v] : key::S2[v];
                    x++;
                }
            }
        }

        virtual byte** update_key() {
            int x = 0, X = _P >> 1;
            for (int i = 1; i <= _R; i++) {
                for (int y = _H; y < _N; y++) {
                    byte* U = K[x];
                    byte* V = K[y];
                    update(U, V);
                    x = ++x == _H ? 0 : x;
                }
                x = X >> i;
            }
            return K;
        }

        virtual byte* update(byte* U, byte* V) {
            int x = 0, n = N - 1, X = N;
            for (int i = 1; i <= R; i++) {
                for (int y = 0; y < N;) {
                    U[y] = key::S1[U[y] ^ V[y]] ^ key::S2[V[x]];
                    V[x] = key::S2[V[x] ^ U[x]] ^ key::S1[U[y]];
                    x = ++x & n, y++;
                    U[y] = key::S1[U[y] ^ V[y]] ^ key::S2[V[x]];
                    V[x] = key::S2[V[x] ^ U[x]] ^ key::S1[U[y]];
                    x = ++x & n, y++;
                    U[y] = key::S1[U[y] ^ V[y]] ^ key::S2[V[x]];
                    V[x] = key::S2[V[x] ^ U[x]] ^ key::S1[U[y]];
                    x = ++x & n, y++;
                    U[y] = key::S1[U[y] ^ V[y]] ^ key::S2[V[x]];
                    V[x] = key::S2[V[x] ^ U[x]] ^ key::S1[U[y]];
                    x = ++x & n, y++;
                    U[y] = key::S1[U[y] ^ V[y]] ^ key::S2[V[x]];
                    V[x] = key::S2[V[x] ^ U[x]] ^ key::S1[U[y]];
                    x = ++x & n, y++;
                    U[y] = key::S1[U[y] ^ V[y]] ^ key::S2[V[x]];
                    V[x] = key::S2[V[x] ^ U[x]] ^ key::S1[U[y]];
                    x = ++x & n, y++;
                    U[y] = key::S1[U[y] ^ V[y]] ^ key::S2[V[x]];
                    V[x] = key::S2[V[x] ^ U[x]] ^ key::S1[U[y]];
                    x = ++x & n, y++;
                    U[y] = key::S1[U[y] ^ V[y]] ^ key::S2[V[x]];
                    V[x] = key::S2[V[x] ^ U[x]] ^ key::S1[U[y]];
                    x = ++x & n, y++;
                }
                x = X >> i;
            }
        }
    };

}
#endif //DIFFUSION_MIXKEYHANDLER_H
