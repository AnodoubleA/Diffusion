//
// Created by Angel on 2017/12/7.
//

#ifndef DIFFUSION_FIXEDKEYHANDLER_V1_H
#define DIFFUSION_FIXEDKEYHANDLER_V1_H

#include "MixKeyHandler.h"
#include "../Consts.h"

namespace lc {
    class FixedKeyHandler_V1 : public MixKeyHandler {
    public:
        void init(CipherInfo& info, KeyInfo& keyInfo) override {
            MixKeyHandler::init(info, keyInfo);
            init_key(info.key, info.keySize);
            update_key();
            update_key();
            update_key();
        }

        int level() override {

            return KeyHandlers::LEVEL_1;
        }
    };
}
#endif //DIFFUSION_FIXEDKEYHANDLER_V1_H
