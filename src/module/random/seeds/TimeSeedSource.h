//
// Created by Alice on 2017/12/10.
//

#ifndef DIFFUSION_TIMESEEDSOURCE_H
#define DIFFUSION_TIMESEEDSOURCE_H

#include <sysinfoapi.h>
#include <algorithm>
#include <profileapi.h>
#include "../AbstractSeedSource.h"

namespace lc {
    class TimeSeedSource : public AbstractSeedSource {

    public:
        int pull(byte* buf, int& offset, int max) override {
            int64 seed = getCurrentTime();
            int count = write(buf + offset, seed, std::min(max - offset, 8));
            offset += count;
            count += write(buf + offset, GetTickCount(), std::min(max - offset, 8));
            offset += count;
            return count;
        }

        float reliability() override {
            return 0.7;
        }

    protected:
        int64 getCurrentTime() {
            LARGE_INTEGER time;
            if (QueryPerformanceFrequency(&time)) {
                QueryPerformanceCounter(&time);
                return time.QuadPart;
            }
            return 0;
        }
    };

}
#endif //DIFFUSION_TIMESEEDSOURCE_H
