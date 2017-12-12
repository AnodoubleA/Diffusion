//
// Created by Angel on 2017/3/27.
//

#ifndef DIFFUSION_INFOHANDLERFACTORY_H
#define DIFFUSION_INFOHANDLERFACTORY_H

#include "info_handler.h"
#include "infos/info_dc3.14_v1.h"
#include "../i18n/lang.h"

namespace lc {

    class InfoHandlerFactory {
    public:
        virtual InfoHandler* getHandler(int serial, int version,int type) throw(DiffusionException) = 0;

        virtual void clear() = 0;

        static InfoHandlerFactory& defaultFactory();
    };
}
#endif //DIFFUSION_INFOHANDLERFACTORY_H
