//
// Created by Alice on 2017/12/10.
//

#ifndef DIFFUSION_DC3_14INFOHANDLERFACTORY_H
#define DIFFUSION_DC3_14INFOHANDLERFACTORY_H

#include "AbstractInfoHandlerFactory.h"

namespace lc {
    class DC3_14InfoHandlerFactory : public AbstractInfoHandlerFactory {
    protected:
        AbstractInfoHandler* newTextHandler(int version) override {
            switch (version) {
                case 0:
                case 1:
                    return new TextInfoHandler_DC314_V1();
            }
            return nullptr;
        }

        AbstractInfoHandler* newFileHandler(int version) override {
            switch (version) {
                case 0:
                case 1:
                    return new FileInfoHandler_DC314_V1();
            }
            return nullptr;
        }
    };
}
#endif //DIFFUSION_DC3_14INFOHANDLERFACTORY_H
