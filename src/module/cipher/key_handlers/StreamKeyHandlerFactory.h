//
// Created by Alice on 2017/12/9.
//

#ifndef DIFFUSION_STREAMKEYHANDLERFACTORY_H
#define DIFFUSION_STREAMKEYHANDLERFACTORY_H

#include "AbstractKeyHandlerFactory.h"

namespace lc {
    class StreamKeyHandlerFactory : public AbstractKeyHandlerFactory {
    protected:
        KeyHandler* newHandler(int level) override;
    };
}
#endif //DIFFUSION_STREAMKEYHANDLERFACTORY_H
