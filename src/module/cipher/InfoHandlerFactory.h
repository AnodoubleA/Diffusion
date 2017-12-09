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
        static InfoReader* getReader(int type, int version) throw(DiffusionException);

        static InfoWriter* getWriter(int type, int version)throw(DiffusionException);

        static void clear();
    };
}
#endif //DIFFUSION_INFOHANDLERFACTORY_H
