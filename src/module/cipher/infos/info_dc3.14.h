//
// Created by Angel on 2017/12/8.
//

#ifndef DIFFUSION_INFO_DC3_14_H
#define DIFFUSION_INFO_DC3_14_H

#include "../info_handler.h"
#include "../Info.h"

namespace lc {
    class InfoHandler_DC314 : public AbstractInfoHandler {

    public:
        void read(byte* buf, Info& info) override {
            AbstractInfoHandler::read(buf, info);
        }

        void write(byte* buf, Info& info) override {
            AbstractInfoHandler::write(buf, info);
        }
    };
}
#endif //DIFFUSION_INFO_DC3_14_H
