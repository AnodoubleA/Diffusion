//
// Created by Alice on 2017.03.17.
//

#ifndef DIFFUSION_STATIC_INIT_H
#define DIFFUSION_STATIC_INIT_H

#include <functional>
#include <vector>

namespace lc{
    typedef std::function<void()> InitFunction;
    namespace si{
        static std::vector<InitFunction*> inits;

        static void regist_init(InitFunction* fun) {
            inits.push_back(fun);
        }

        static void regist_init(InitFunction fun) {
            regist_init(&fun);
        }

        static void static_init() {
            for (InitFunction* item:inits) {
                (*item)();
            }
        }
    }
}
#endif //DIFFUSION_STATIC_INIT_H
