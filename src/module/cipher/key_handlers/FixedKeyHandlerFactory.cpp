//
// Created by Alice on 2017/12/9.
//
#include "../KeyHandler.h"
#include "FixedKeyHandlerFactory.h"
#include "../Consts.h"
#include "FixedKeyHandler_V1.h"

namespace lc {

    KeyHandler* FixedKeyHandlerFactory::newHandler(int level) {
        switch (level >> 8 & 0xFF) {
            case 0:
            case 1 :
                return new FixedKeyHandler_V1();
        }
        return nullptr;
    }
}
