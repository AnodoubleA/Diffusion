//
// Created by Alice on 2017/12/10.
//

#ifndef DIFFUSION_DC3_14INFOHANDLERFACTORY_H
#define DIFFUSION_DC3_14INFOHANDLERFACTORY_H

#include "AbstractInfoHandlerFactory.h"

namespace lc {
    class DC3_14InfoHandlerFactory : public AbstractInfoHandlerFactory {
    public:
        InfoHandler* getHandler(int serial, int version, int type) override {
            if (version == -1) {
                if (type == CO::TEXT) {
                    return new DC3_14TextInfoHandler();
                }
                return new DC3_14FileInfoHandler();
            }
            switch (version) {
                case 0:
                case 1:
                    if (type == CO::TEXT) {
                        return new TextInfoHandler_DC314_V1();
                    }
                    return new FileInfoHandler_DC314_V1();
            }
            //TODO add exception
            throw DiffusionException("");
        }
    };
}
#endif //DIFFUSION_DC3_14INFOHANDLERFACTORY_H
