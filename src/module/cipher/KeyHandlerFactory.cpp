//
// Created by Angel on 2017/12/7.
//
#include <vector>
#include "KeyHandlerFactory.h"
#include "key_handlers/FixedKeyHandler_V1.h"
#include "key_handlers/StreamKeyHandler_V1.h"
#include "../i18n/lang.h"

namespace lc {

    std::vector<KeyHandler*> cache;

    KeyHandler* KeyHandlerFactory::make(int& level)throw(DiffusionException) {
        int version = level >> 8 & 0xFF;
        int lv = level & 0xFF;
        version = version == 0 ? 1 : version;
        if (version > 1) {
            throw DiffusionException(ERROR_KVS_USP, version);
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
                default:
                    throw DiffusionException(I18N->gf(ERROR_KLV_USP, lv));
            }
            cache.push_back(instance);
        }
        level |= instance->version() << 8;
        instance->lock();
        return instance;
    }

    void KeyHandlerFactory::clear() {
        for (KeyHandler* key:cache) {
            delete (key);
        }
        cache.clear();
    }
}
