//
// Created by Angel on 2017/12/7.
//
#include "info_handler.h"
#include "InfoHandlerFactory.h"

namespace lc {
    AbstractInfoHandler* getHandler(int type, int version);

    std::vector<InfoHandlerFactory*> vector;

    InfoReader* InfoHandlerFactory::getReader(int type, int version)throw(DiffusionException) {
        return getHandler(type, version);
    }

    InfoWriter* InfoHandlerFactory::getWriter(int type, int version)throw(DiffusionException) {
        return getHandler(type, version);
    }

    void InfoHandlerFactory::clear() {
        for (AbstractInfoHandler* element:handlers) {
            delete (element);
        }
        handlers.clear();
    }

    AbstractInfoHandler* getHandler(int type, int version) {
        for (AbstractInfoHandler* item : handlers) {
            if (item->version() == version && item->lock()) {
                return item;
            }
        }
        AbstractInfoHandler* handler = nullptr;
        switch (version) {
            case 0:
            case 1:
                if (type == CO::TEXT) {
                    handler = new TextInfoHandler_DC314_V1();
                }
                if (type == CO::FILE) {
                    handler = new FileInfoHandler_DC314_V1();
                }
                break;
        }
        if (handler != nullptr) {
            handler->lock();
            handlers.push_back(handler);
        }
        return handler;
    }
}

