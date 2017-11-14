//
// Created by Alice on 2017.03.14.
//

#ifndef DIFFUSION_CIPHERLISENTER_H
#define DIFFUSION_CIPHERLISENTER_H

#include "items.h"

namespace lc{
    class CipherListener {
    public :
        virtual void begin(Item& item) = 0;

        virtual void end(Item& item) = 0;
    };

}
#endif //DIFFUSION_CIPHERLISENTER_H
