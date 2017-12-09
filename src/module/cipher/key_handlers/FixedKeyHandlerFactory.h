//
// Created by Alice on 2017/12/9.
//

#ifndef DIFFUSION_FIXEDKEYHANDLERFACTORY_H
#define DIFFUSION_FIXEDKEYHANDLERFACTORY_H

#include "AbstractKeyHandlerFactory.h"

namespace lc {
    class FixedKeyHandlerFactory : public AbstractKeyHandlerFactory {
    protected:
        KeyHandler* newHandler(int level) override;
    };
}
#endif //DIFFUSION_FIXEDKEYHANDLERFACTORY_H
