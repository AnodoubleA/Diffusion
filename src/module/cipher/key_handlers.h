//
// Created by Angel on 2017/4/2.
//

#ifndef DIFFUSION_KEY_HANDLERS_H
#define DIFFUSION_KEY_HANDLERS_H

#include <cmath>
#include "KeyHandler.h"
#include "key_box.h"
#include "../../tool/funs.h"

namespace lc{
    class AbstractKeyHandler : public KeyHandler, public AbstractReusable {
    protected:
        int R = 0, H = 0, N = 0;
    public:
        void init(Init& init, Info& info) override {
            R = init.R;
            N = init.N;
            H = N >> 1;
        }

        int version() override {
            return 1;
        }

        bool lock() override {
            return AbstractReusable::lock();
        }

        void unlock() override {
            AbstractReusable::unlock();
        }
    };

    class MixKeyHandler : public AbstractKeyHandler {
    protected:
        int _N = 0, _R, _H, _P;
        byte** K = nullptr;
    public:
        ~MixKeyHandler() {
            delTable(K, R);
        }

        void init(Init& init, Info& info) override {
            AbstractKeyHandler::init(init, info);
            if (_N != R) {
                delTable(K, _R);
                alloc(init);
            }
        }

        byte** update() override {
            return K;
        }

    protected:
        virtual void alloc(Init& init) {
            _N = init.R;
            _R = (int) ceil(log2(R));
            _P = 1 << _R;
            _H = _N >> 1;
            _R++;
            K = new byte* [_N];
            for (int i = 0; i < _N; i++) {
                K[i] = new byte[N];
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


    class FixedKeyHandler : public MixKeyHandler {
    public:
        void init(Init& init, Info& info) override {
            MixKeyHandler::init(init, info);
            init_key(info.key, info.keySize);
            update_key();
            update_key();
            update_key();
        }

        int level() override {
            return 1;
        }
    };

    class StreamKeyHandler : public MixKeyHandler {
        int* indices = nullptr;
    public:
        void init(Init& init, Info& info) override {
            MixKeyHandler::init(init, info);
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
        void alloc(Init& init) override {
            MixKeyHandler::alloc(init);
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

    class HighKeyHandler : public MixKeyHandler {
    public:
        void init(Init& init, Info& info) override {
            MixKeyHandler::init(init, info);
            init_key(info.key, info.keySize);
            update_key();
            update_key();
        }

        byte** update() override {

            return update_key();
        }

        int level() override {
            return 3;
        }
    };
}
#endif //DIFFUSION_KEY_HANDLERS_H
