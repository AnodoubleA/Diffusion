//
// Created by Angel on 2017/4/1.
//

#ifndef DIFFUSION_SECURE_FILE_SMASH_H
#define DIFFUSION_SECURE_FILE_SMASH_H

#include "FileSmash.h"

namespace lc{
    class SecureFileSmash : public FileSmash, public AbstractReusable {
        const int cache = allocationGranularity * BUFFER_MULTIPLE * 2;
        FastRandom random;
    public:
        virtual bool smash(const std::string& src, int times)throw(DiffusionException) {
            FileMapping& map = *FMFactory::make();
            int64 size = map.init(src, FM::OPEN, FM::READ | FM::WRITE);
            map.make(0);
            uint64 round = size / cache;
            uint32_t remainder = size % cache;
            uint64 offset = 0;
            byte* buf = nullptr;
            for (int i = 0; i < round; i++) {
                buf = map.map(offset, cache, FM::WRITE);
                random_write(random, map, buf, cache, times);
                map.unmap(buf);
            }
            if (remainder > 0) {
                buf = map.map(offset, remainder, FM::WRITE);
                random_write(random, map, buf, remainder, times);
                map.unmap(buf);
            }
            map.deinit(0);
            remove(src.c_str());
            return true;
        }

        inline void random_write(Random& random, FileMapping& map, byte* buf, int length, int times) {
            times--;
            while (times > 0) {
                random.next(buf, length);
                map.flush(buf, length);
                times--;
            }
            memset(buf, 0, length);
            map.flush(buf, length);
        }

        bool lock() override {
            return AbstractReusable::lock();
        }

        void unlock() override {
            AbstractReusable::unlock();
        }
    };
}
#endif //DIFFUSION_SECURE_FILE_SMASH_H
