//
// Created by Alice on 2017/12/10.
//

#ifndef DIFFUSION_ABSTRACTINFOHANDLERFACTORY_H
#define DIFFUSION_ABSTRACTINFOHANDLERFACTORY_H

#include "../InfoHandlerFactory.h"

namespace lc {
    class AbstractInfoHandlerFactory : public InfoHandlerFactory {
    public:
        virtual void clear() {

        }
    };
}
#endif //DIFFUSION_ABSTRACTINFOHANDLERFACTORY_H
