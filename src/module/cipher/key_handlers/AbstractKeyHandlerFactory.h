//
// Created by Alice on 2017/12/9.
//

#ifndef DIFFUSION_ABSTRACTKEYHANDLERFACTORY_H
#define DIFFUSION_ABSTRACTKEYHANDLERFACTORY_H

#include <vector>
#include "../KeyHandlerFactory.h"

namespace lc {
    class AbstractKeyHandlerFactory : public KeyHandlerFactory {
    protected:
        std::vector<KeyHandler*> vector;

    public:
        virtual KeyHandler* make(int& level)  throw(DiffusionException) {
            int L = level >> 8 & 0xFF;
            int V = level >> 0 & 0xFF;
            for (KeyHandler* e:vector) {
                if (e->level() == L && e->version() == V && e->lock()) {
                    return e;
                }
            }
            KeyHandler* handler = newHandler(level);
            if (handler == nullptr) {
                //TODO throw exception
            }
            vector.push_back(handler);
            return handler;
        }

        void clear() override {
            for (KeyHandler* handler:vector) {
                delete (handler);
            }
            vector.clear();
        }

    protected:
        virtual KeyHandler* newHandler(int level)= 0;
    };
}
#endif //DIFFUSION_ABSTRACTKEYHANDLERFACTORY_H
