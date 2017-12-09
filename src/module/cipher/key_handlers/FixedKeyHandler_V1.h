//
// Created by Angel on 2017/12/7.
//

#ifndef DIFFUSION_FIXEDKEYHANDLER_V1_H
#define DIFFUSION_FIXEDKEYHANDLER_V1_H

#include "MixKeyHandler.h"

namespace lc{
    class FixedKeyHandler : public MixKeyHandler {
    public:
        void init(Info& info,Init& init ) override {
            MixKeyHandler::init(info, init);
            init_key(info.key, info.keySize);
            update_key();
            update_key();
            update_key();
        }

        int level() override {
            return 1;
        }
    };
}
#endif //DIFFUSION_FIXEDKEYHANDLER_V1_H
