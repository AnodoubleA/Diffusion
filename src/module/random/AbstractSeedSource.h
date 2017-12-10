//
// Created by Alice on 2017/12/10.
//

#ifndef DIFFUSION_ABSTRACTSEEDSOURCE_H
#define DIFFUSION_ABSTRACTSEEDSOURCE_H


#include "SeedSource.h"
#include "rd_box.h"

namespace lc {
    class AbstractSeedSource : public SeedSource {
    public:
        virtual int pull(byte* buf, int& offset, int max) = 0;

        virtual float reliability() = 0;

    protected:
        int write(byte* buf, int64 value, int byteCount, bool zero = false) {
            int index = 0;
            for (int i = 0; i < byteCount; i++) {
                byte v = (byte) (value >> (i * 8));
                if (zero || v > 0) {
                    buf[index++] = rd::S1[v] ^ rd::S2[v];
                }
            }
            return byteCount;
        }
    };
}


#endif //DIFFUSION_ABSTRACTSEEDSOURCE_H
