//
// Created by Angel on 2017/12/7.
//

#ifndef DIFFUSION_STREAMKEYHANDLER_V1_H
#define DIFFUSION_STREAMKEYHANDLER_V1_H

#include "MixKeyHandler.h"

namespace lc {
    class StreamKeyHandler_V1 : public MixKeyHandler {
        int* indices = nullptr;
    public:
        void init(CipherInfo& info, AlgorithmInfo& init) override {
            MixKeyHandler::init(info, init);
            init_key(info.key, info.keySize);
            update_key();
            update_key();
        }

        byte** update() {
            int x = 0, v = R - 1, h = H - 1;
            for (int i = 0; i < R; i++, v--) {
                x = indices[i] & h;
                byte* U = K[i];
                byte* V = K[v];
                for (int y = H; y < N;) {
                    U[y] = (byte) (key::S1[(U[y] ^ V[y])] ^ U[x]);
                    U[x] = (byte) (key::S2[(U[x] ^ V[x])] ^ U[y]);
                    x = (++x) & h, y++;
                    U[y] = (byte) (key::S1[(U[y] ^ V[y])] ^ U[x]);
                    U[x] = (byte) (key::S2[(U[x] ^ V[x])] ^ U[y]);
                    x = (++x) & h, y++;
                    U[y] = (byte) (key::S1[(U[y] ^ V[y])] ^ U[x]);
                    U[x] = (byte) (key::S2[(U[x] ^ V[x])] ^ U[y]);
                    x = (++x) & h, y++;
                    U[y] = (byte) (key::S1[(U[y] ^ V[y])] ^ U[x]);
                    U[x] = (byte) (key::S2[(U[x] ^ V[x])] ^ U[y]);
                    x = (++x) & h, y++;
                    U[y] = (byte) (key::S1[(U[y] ^ V[y])] ^ U[x]);
                    U[x] = (byte) (key::S2[(U[x] ^ V[x])] ^ U[y]);
                    x = (++x) & h, y++;
                    U[y] = (byte) (key::S1[(U[y] ^ V[y])] ^ U[x]);
                    U[x] = (byte) (key::S2[(U[x] ^ V[x])] ^ U[y]);
                    x = (++x) & h, y++;
                    U[y] = (byte) (key::S1[(U[y] ^ V[y])] ^ U[x]);
                    U[x] = (byte) (key::S2[(U[x] ^ V[x])] ^ U[y]);
                    x = (++x) & h, y++;
                    U[y] = (byte) (key::S1[(U[y] ^ V[y])] ^ U[x]);
                    U[x] = (byte) (key::S2[(U[x] ^ V[x])] ^ U[y]);
                    x = (++x) & h, y++;
                }
                indices[i] = (indices[i] << 1);
                indices[i] = (indices[i]) > H ? 1 : indices[i];
            }
            return K;
        }

        int level() override {
            return 2;
        }

    protected:
        void alloc(AlgorithmInfo& init) override {
            MixKeyHandler::alloc(init);
            if (indices)delete[](indices);
            indices = new int[init.R];
        }

        void init_key(byte* key, int length) override {
            MixKeyHandler::init_key(key, length);
            init_indices(R, N);
        }

        void init_indices(int round, int N) {
            indices[0] = N;
            for (int i = 1; i <= R; i++) {
                indices[i] = 1 << i - 1;
            }
        }
    };
}
#endif //DIFFUSION_STREAMKEYHANDLER_V1_H
