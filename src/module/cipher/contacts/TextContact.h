//
// Created by Angel on 2017/12/6.
//

#ifndef DIFFUSION_TEXTCONTACT_H
#define DIFFUSION_TEXTCONTACT_H

#include "BufferContact.h"

namespace lc {
    class TextContact : public BufferContact {
    public:
        ~OutputContact() {
            delete[] (buffer);
        }
        uint64 options = 0;
        byte* buffer = nullptr;
    };

}
#endif //DIFFUSION_TEXTCONTACT_H
