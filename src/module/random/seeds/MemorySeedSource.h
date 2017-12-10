//
// Created by Alice on 2017/12/10.
//

#ifndef DIFFUSION_MEMORYSEEDSOURCE_H
#define DIFFUSION_MEMORYSEEDSOURCE_H

#include <winbase.h>
#include <algorithm>
#include "../AbstractSeedSource.h"
#include "../../../core/types.h"

namespace lc {
    class MemorySeedSource : public AbstractSeedSource {
        MEMORYSTATUS m;
    public:
        int pull(byte* buf, int& offset, int max) override {
            GlobalMemoryStatus(&m);
            int min = std::min(max - offset, 8);
            offset += write(buf + offset, m.dwAvailPageFile, min);
            min = std::min(max - offset, 8);
            offset += write(buf + offset, m.dwAvailPhys, min);
        }

        float reliability() override {
            return 0.9;
        }
    };

}
#endif //DIFFUSION_MEMORYSEEDSOURCE_H
