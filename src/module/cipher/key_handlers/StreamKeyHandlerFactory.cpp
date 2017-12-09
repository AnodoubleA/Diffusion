//
// Created by Alice on 2017/12/9.
//
#include "../KeyHandler.h"
#include "FixedKeyHandlerFactory.h"
#include "StreamKeyHandlerFactory.h"
#include "StreamKeyHandler_V1.h"

namespace lc {

    KeyHandler* StreamKeyHandlerFactory::newHandler(int level) {
        switch (level >> 8 & 0xFF) {
            case 0:
            case 1 :
                return new StreamKeyHandler_V1();
        }
        return nullptr;
    }
}
