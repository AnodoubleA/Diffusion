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

    extern void init_seedFactory();




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
