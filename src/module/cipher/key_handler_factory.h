//
// Created by Alice on 2017.03.22.
//

#ifndef DIFFUSION_KEY_HANDLER_FACTORY_H
#define DIFFUSION_KEY_HANDLER_FACTORY_H

#include "KeyHandler.h"
#include "key_handlers.h"

namespace lc{
    class KeyHandlerFactory {
    public:
        virtual KeyHandler* make(int& level) = 0;
    };

    class CachedKeyHandlerFactory : public KeyHandlerFactory {
        std::vector<KeyHandler*> cache;
    public:
        KeyHandler* make(int& level) {
            int version = level >> 8 & 0xFF;
            int lv = level & 0xFF;
            version = version == 0 ? 1 : version;
            if (version > 1) {
                throw DiffusionException(I18N->gf(ERROR_KVS_USP, version));
            }
            KeyHandler* instance = nullptr;
            for (KeyHandler* item : cache) {
                if (item->level() == lv && item->version() == version && item->lock()) {
                    instance = item;
                }
            }
            if (instance == nullptr) {
                switch (lv) {
                    case 1:
                        instance = new FixedKeyHandler();
                        break;
                    case 2:
                        instance = new StreamKeyHandler();
                        break;
                    case 3:
                        instance = new HighKeyHandler();
                        break;
                    default:
                        throw DiffusionException(I18N->gf(ERROR_KLV_USP, lv));
                }
                cache.push_back(instance);
            }
            level |= instance->version() << 8;
            instance->lock();
            return instance;
        }
    };
}
#endif //DIFFUSION_KEY_HANDLER_FACTORY_H
