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

    class AbstractReusable : public Reusable {
    protected:
        bool idle = true;
    public:
        virtual bool lock() override {
            if (!idle) {
                return false;
            }
            return !(idle = false);
        }

        virtual void unlock() override {
            idle = true;
        }
    };
}
#endif //DIFFUSION_REUSEFUL_H
