//
// Created by Angel on 2017/3/27.
//

#ifndef DIFFUSION_DC314_V1_H
#define DIFFUSION_DC314_V1_H

#include "../info_handler.h"
#include "../InfoHeader.h"
#include "info_dc3.14.h"

namespace lc {

    class TextInfoHandler_DC314_V1 : public AbstractInfoHandler {
    public:
        int write(byte buf[], CipherInfo& info) throw(DiffusionException) {
            int offset = 0;
            buf[offset++] = version();
            buf[offset++] = info.log;
            buf[offset++] = info.diff >> 8 & 0xFF;
            buf[offset++] = info.diff >> 0 & 0xFF;
            buf[offset++] = info.algorithm >> 8 & 0xFF;
            buf[offset++] = info.algorithm >> 0 & 0xFF;
            buf[offset++] = info.level >> 8 & 0xFF;
            buf[offset++] = info.level >> 0 & 0xFF;
            buf[offset++] = info.cycle >> 0 & 0xFF;
            buf[offset] = contains(info.options, CO::PADDING);
            return length();
        }

        int read(byte buf[], CipherInfo& info) throw(DiffusionException) {
            //@formatter:off
            info.options &= ~FO::PADDING;          //subtracting padding
            int offset = 0;
            info.log        = buf[offset++];
            info.diff       = buf[offset++] << 8;
            info.diff      |= buf[offset++];
            info.algorithm  = buf[offset++] << 8;  // version
            info.algorithm |= buf[offset++];
            info.level      = buf[offset++] << 8;  // version
            info.level     |= buf[offset++];
            info.cycle      = buf[offset++];
            bool pad        = buf[offset++] & 0x1;
            info.options   |= pad ? CO::PADDING : 0;
            info.group      = 1 << info.log;
            //@formatter:on
        }
    };

    //===================================================================================
    class FileInfoHandler_DC314_V1 : public TextInfoHandler_DC314_V1 {
    public:
        int write(byte buf[], CipherInfo& info) throw(DiffusionException) {
            TextInfoHandler_DC314_V1::write(buf, info);
            strrev((char*) buf);
        }

        int read(byte buf[], CipherInfo& info) throw(DiffusionException) {
            strrev((char*) buf);
            TextInfoHandler_DC314_V1::read(buf, info);
        }
    };
}
#endif //DIFFUSION_DC314_V1_H
