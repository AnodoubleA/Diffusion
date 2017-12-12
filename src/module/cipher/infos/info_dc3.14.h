//
// Created by Alice on 2017/12/9.
//

#ifndef DIFFUSION_INFO_DC3_14_H
#define DIFFUSION_INFO_DC3_14_H

#include <memory.h>
#include "../info_handler.h"
#include "../InfoHeader.h"
#include "HeaderInfoHandler.h"

namespace lc {
    class DC3_14TextInfoHandler : public HeaderInfoHandler {
    public:
        DC3_14TextInfoHandler(InfoReader* reader = nullptr) : HeaderInfoHandler(reader) {

        }

        int type() override {
            return CO::TEXT;
        }

    protected:
        InfoHeader& getInfoHeader() override {
            return IH::DC3_14();
        }
    };

    class DC3_14FileInfoHandler : public HeaderInfoHandler {
    public:
        DC3_14FileInfoHandler(InfoReader* reader = nullptr) : HeaderInfoHandler(reader) {

        }

        int type() override {
            return CO::FILE;
        }

    protected:
        InfoHeader& getInfoHeader() override {
            return IH::DC3_14();
        }
    };
}
#endif //DIFFUSION_INFO_DC3_14_H
