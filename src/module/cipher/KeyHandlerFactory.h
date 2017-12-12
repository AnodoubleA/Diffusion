//
// Created by Alice on 2017.03.22.
//

#ifndef DIFFUSION_KEY_HANDLER_FACTORY_H
#define DIFFUSION_KEY_HANDLER_FACTORY_H

#include "KeyHandler.h"

namespace lc {
    class KeyHandlerFactory {
    public:
        virtual KeyHandler* make(int& level) throw(DiffusionException) = 0;

        virtual void level() = 0;

        static KeyHandlerFactory& factory(int level);

        static void clearAll();

        virtual void clear() = 0;
    };
}
#endif //DIFFUSION_KEY_HANDLER_FACTORY_H
