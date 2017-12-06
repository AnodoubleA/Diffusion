//
// Created by Angel on 2017/3/27.
//

#ifndef DIFFUSION_INFO_FACTORY_H
#define DIFFUSION_INFO_FACTORY_H

#include "../../cipher/info.h"
#include "info_v1.h"
#include "../i18n/lang.h"

namespace lc{

    class InfoFactory {
    public:
        virtual InfoReader* getReader(int type, int version) = 0;

        virtual InfoWriter* getWriter(int type, int version) = 0;
    };

    class CachedInfoFactory : public InfoFactory {
        std::vector<AbstractInfoHandler*> texts;
        std::vector<AbstractInfoHandler*> files;
    public:
        InfoReader* getReader(int type, int version) override {
            return getHandler(type, version);
        }

        InfoWriter* getWriter(int type, int version) override {
            return getHandler(type, version);
        }

    protected:
        AbstractInfoHandler* getHandler(int type, int version) {
            std::vector<AbstractInfoHandler*>& content = type == CO::TEXT ? texts : files;
            for (AbstractInfoHandler* item : content) {
                if (item->version() == version && item->lock()) {
                    return item;
                }
            }
            AbstractInfoHandler* handler = nullptr;
            switch (version) {
                case 0:
                case 1:
                    if (type == CO::TEXT) {
                        handler = new TextInfoHandler_V1();
                    }
                    if (type == CO::FILE) {
                        handler = new FileInfoHandler_V1();
                    }
                    break;
            }
            if (handler != nullptr) {
                handler->lock();
                content.push_back(handler);
            }
            return handler;
        }
    };
}
#endif //DIFFUSION_INFO_FACTORY_H
