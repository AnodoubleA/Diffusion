//
// Created by Alice on 2017.03.22.
//

#ifndef DIFFUSION_KEY_HANDLER_FACTORY_H
#define DIFFUSION_KEY_HANDLER_FACTORY_H

#include "KeyHandler.h"

namespace lc {
    class KeyHandlerFactory {
    public:
        static KeyHandler* make(int& level) throw(DiffusionException);

        static void clear();
    };
}
#endif //DIFFUSION_KEY_HANDLER_FACTORY_H
