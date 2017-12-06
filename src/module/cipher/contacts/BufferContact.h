//
// Created by Angel on 2017/12/6.
//

#ifndef DIFFUSION_BUFFERCONTACT_H
#define DIFFUSION_BUFFERCONTACT_H

#include "../Contact.h"
#include "../../../core/types.h"

namespace lc{
    class BufferContact : public Contact {
    public:
        uint64 length = 0;
        uint64 done = 0;

        inline void addDone(uint64 size) {
            this->done += size;
        }
    };
}
#endif //DIFFUSION_BUFFERCONTACT_H
