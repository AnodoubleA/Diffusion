//
// Created by Angel on 2017/12/10.
//

#ifndef DIFFUSION_DARANDOMENGINE_H
#define DIFFUSION_DARANDOMENGINE_H

#include <algorithm>
#include <memory.h>
#include <cmath>
#include "../RandomEngine.h"
#include "../rd_box.h"

namespace lc {
    class DARandomEngine : public RandomEngine {
        const int SIZE_BUF = 1024;
    protected:
        int N, H, R, n;
        int index = 0;
        byte* D;    // seed
        byte* B;    // buffer
    public:
        ~DARandomEngine() {
            delete[](B);
            delete[](D);
        }

        DARandomEngine() {
            init(SIZE_BUF);
        }

        void seed(byte seed[], int length) override {
            memcpy(D, seed, std::min(N, length));
        }

        void next(byte accept[], int length) override {
            int min = 0;
            while (length > 0) {
                min = std::min(length, N - index);
                memcpy(accept, B + index, min);
                length -= min;
                accept += min;
                index = (index + min) & n;
                if (index == 0) {
                    update();
                }
            }
        }

        byte next() override {
            byte rand = B[++index & n];
            if (index == 0) {
                update();
            }
            return rand;
        }

        int needSeed() override {
            return N;
        }

    protected:
        virtual void init(int size) {
            int lg = (int) log2(size);
            N = size;
            n = N - 1;
            B = new byte[N];
            D = new byte[N];
            H = N >> 1;
            R = lg;
        }

        void update() {
            int x = 0, r = R - 1, h = H - 1, X = H;
            for (int i = 0; i < r; i++) {
                for (int y = H; y < N;) {
                    B[y] = rd::S1[(B[y] ^ D[y])] ^ B[x];
                    B[x] = rd::S2[(B[x] ^ D[x])] ^ B[y];
                    x = (++x) & h, y++;
                    B[y] = rd::S1[(B[y] ^ D[y])] ^ B[x];
                    B[x] = rd::S2[(B[x] ^ D[x])] ^ B[y];
                    x = (++x) & h, y++;
                    B[y] = rd::S1[(B[y] ^ D[y])] ^ B[x];
                    B[x] = rd::S2[(B[x] ^ D[x])] ^ B[y];
                    x = (++x) & h, y++;
                    B[y] = rd::S1[(B[y] ^ D[y])] ^ B[x];
                    B[x] = rd::S2[(B[x] ^ D[x])] ^ B[y];
                    x = (++x) & h, y++;
                }
                x = X >> i;
            }
        }
    };
};
#endif //DIFFUSION_DCRANDOMENGINE_H
