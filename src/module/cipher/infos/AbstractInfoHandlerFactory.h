//
// Created by Alice on 2017/12/10.
//

#ifndef DIFFUSION_ABSTRACTINFOHANDLERFACTORY_H
#define DIFFUSION_ABSTRACTINFOHANDLERFACTORY_H

#include "../InfoHandlerFactory.h"

namespace lc {
    class AbstractInfoHandlerFactory : public InfoHandlerFactory {
    protected:
        std::vector<AbstractInfoHandler*> vector;
    public:
        virtual InfoReader* getReader(int type, int version) {
            return getHandler(type, version);
        }

        virtual InfoWriter* getWriter(int type, int version) {
            return getHandler(type, version);
        }

    private:
        AbstractInfoHandler* getHandler(int type, int version) {
            for (AbstractInfoHandler* item : vector) {
                if (item->version() == version && item->lock()) {
                    return item;
                }
            }
            AbstractInfoHandler* handler = type == CO::TEXT ? newTextHandler(version) : newFileHandler(version);
            if (handler == nullptr) {
                //TODO throw exception
                throw DiffusionException("");
            }
            handler->lock();
            vector.push_back(handler);
            return handler;
        }

    protected:
        virtual AbstractInfoHandler* newTextHandler(int version) = 0;

        virtual AbstractInfoHandler* newFileHandler(int version) = 0;
    };
}
#endif //DIFFUSION_ABSTRACTINFOHANDLERFACTORY_H
