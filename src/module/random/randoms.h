//
// Created by Angel on 2017/4/1.
//

#ifndef DIFFUSION_RANDOMS_H
#define DIFFUSION_RANDOMS_H

#include <cmath>
#include <memory.h>
#include "Random.h"
#include "rd_box.h"

namespace lc{
    extern SeedFactory& getSeedFactory();

    extern void init_seedFactory();

    class SecureRandom : public Random {
        const int SIZE_BUF = 128;
    protected:
        int round = 1024 * 1024 * 10;
        int counter = 0;
        int N, H, R, n;
        int index = 0;
        byte* D;
        byte* B;
    public:
        ~SecureRandom() {
            delete[](B);
            delete[](D);
        }

        SecureRandom() {
            init(SIZE_BUF);
        }

        void seed(byte* seed, int length) override {

        }

        void next(byte* accept, int length) override {
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


    protected:
        virtual void init(int size) {
            round = 1024 * 1024 * 10;
            N = size;
            n = N - 1;
            B = new byte[N];
            D = new byte[N];
            int lg = std::ceil(log2(N));
            H = N >> 2;
            R = lg;
            update();
        }

        void update() {
            if (counter++ > round) {
                getSeedFactory().pull(D, N);
                counter = 0;
            }
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

    class FastRandom : public SecureRandom {
    public:
    protected:
        void init(int size) override {
            SecureRandom::init(size);
            round *= 1024;
        }

    public:
        void next(byte* accept, int length) override {
            if (counter++ > round) {
                getSeedFactory().pull(D, N);
                counter = 0;
            }
            int x = 0, min = 0, h = H - 1, X = H;
            while (length > 0) {
                x = 0;
                for (int i = 1; i <= R; i++) {
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
                        x = (++x) & h, y++;;
                    }
                    x = X >> i;
                    if (length > 0) {
                        min = std::min(length, N);
                        memcpy(accept, B, min);
                        length -= min;
                        accept += min;
                    }
                }
            }
        }
    };

}
#endif //DIFFUSION_RANDOMS_H
