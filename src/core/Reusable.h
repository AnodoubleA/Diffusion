//
// Created by Alice on 2017.03.22.
//

#ifndef DIFFUSION_REUSABLE_H
#define DIFFUSION_REUSABLE_H

namespace lc{
    class Reusable {
    public:
        virtual bool lock() = 0;

        virtual void unlock() = 0;
    };
}
#endif //DIFFUSION_REUSEFUL_H
