//
// Created by Alice on 2017.03.14.
//

#ifndef DIFFUSION_CPUSEEDSOURCE_H
#define DIFFUSION_CPUSEEDSOURCE_H

#include <algorithm>
#include <fibersapi.h>
#include <winbase.h>
#include "../AbstractSeedSource.h"
#include "../../../core/types.h"

namespace lc {

    class CPUSeedSource : public AbstractSeedSource {
        FILETIME idle;
        FILETIME kernel;
        FILETIME user;
    public:
        int pull(byte* buf, int& offset, int max) override {
            GetSystemTimes(&idle, &kernel, &user);
            int min = std::min(max - offset, 4);
            offset += write(buf + offset, idle.dwLowDateTime, min);
            min = std::min(max - offset, 4);
            offset += write(buf + offset, kernel.dwLowDateTime, min);
            min = std::min(max - offset, 4);
            offset += write(buf + offset, user.dwLowDateTime, min);
        }

        float reliability() override {
            return 0.8;
        }
    };
}
#endif //DIFFUSION_CPUSEEDSOURCE_H
