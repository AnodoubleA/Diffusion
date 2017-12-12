//
// Created by Angel on 2017/12/7.
//
#include <vector>
#include <map>
#include "KeyHandlerFactory.h"
#include "key_handlers/FixedKeyHandler_V1.h"
#include "key_handlers/StreamKeyHandler_V1.h"
#include "../i18n/lang.h"
#include "key_handlers/FixedKeyHandlerFactory.h"
#include "key_handlers/StreamKeyHandlerFactory.h"

namespace lc {

    std::map<int, KeyHandlerFactory*> cache;

    KeyHandlerFactory& KeyHandlerFactory::factory(int level) {
        KeyHandlerFactory* factory = cache[level];
        if (factory != nullptr) {
            return *factory;
        }
        switch (level) {
            case KeyHandlers::LEVEL_1 :
                factory = new FixedKeyHandlerFactory();
                break;
            case KeyHandlers::LEVEL_2 :
                factory = new StreamKeyHandlerFactory();
                break;
            default:
                //TODO throw exception
                throw DiffusionException("");
        }
        cache[level] = factory;
        return *factory;
    }


    void KeyHandlerFactory::clearAll() {
        auto it = cache.begin();
        while (it++ != cache.end()) {
            it->second->clear();
        }
    }
}
