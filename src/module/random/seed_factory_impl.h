//
// Created by Angel on 2017/4/2.
//

#ifndef DIFFUSION_SEED_FACTORY_IMPL_H
#define DIFFUSION_SEED_FACTORY_IMPL_H

#include "SeedFactory.h"

namespace lc{
    class SecureSeedFactory : public SeedFactory {
    private:
        std::vector<SeedSource*> sources;
        static const int N = 1024 * 1024 * 10;
        static const int n = N - 1;
        byte* buf;
        int index = 0;
    public:
        SecureSeedFactory() {
            regist(new TimeSeedSource());
            regist(new MemorySeedSource());
            regist(new CPUSeedSource());
            regist(new TempdirSeedSource());
        }

        void init() override {
            buf = new byte[N];
            update();
        }

        void regist(SeedSource* source) override {
            sources.push_back(source);
        }

        void pull(byte* accept, int length) override {
            int min = 0;
            while (length > 0) {
                min = std::min(length, N - index);
                memcpy(accept, buf + index, min);
                length -= min;
                accept += min;
                index = (index + min) & n;
                if (index == 0) {
                    update();
                }
            }
        }

    protected:
        void update() {
            int offset = 0;
            while (offset < N) {
                for (SeedSource* item : sources) {
                    item->pull(buf, offset, N);
                    if (offset >= N) {
                        break;
                    }
                }
            }
        }
    };
}
#endif //DIFFUSION_SEED_FACTORY_IMPL_H
