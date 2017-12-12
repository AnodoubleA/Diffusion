//
// Created by Angel on 2017/12/12.
//

#ifndef DIFFUSION_DEFAULTINFOHANDLERFACTORY_H
#define DIFFUSION_DEFAULTINFOHANDLERFACTORY_H

#include "AbstractInfoHandlerFactory.h"
#include "DC3_14InfoHandlerFactory.h"

namespace lc {
    class DefaultInfoHandlerFactory : public AbstractInfoHandlerFactory {
        std::map<int, InfoHandlerFactory*> factorys;
    public:
        DefaultInfoHandlerFactory() {
            factorys[IH::DC3_14().identity()] = new DC3_14InfoHandlerFactory();
        }

        InfoHandler* getHandler(int serial, int version, int type) override {
            InfoHandlerFactory* factory = factorys[serial];
            if (factory == nullptr) {
                //TODO throw exception
                throw DiffusionException("");
            }
            return factory->getHandler(serial, version, type);
        }
    };
}
#endif //DIFFUSION_DEFAULTINFOHANDLERFACTORY_H
