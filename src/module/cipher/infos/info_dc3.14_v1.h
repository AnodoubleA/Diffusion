//
// Created by Angel on 2017/3/27.
//

#ifndef DIFFUSION_DC314_V1_H
#define DIFFUSION_DC314_V1_H

#include "../info_handler.h"
#include "../InfoHeader.h"

namespace lc {

    class TextInfoHandler_DC314_V1 : public AbstractInfoHandler {
    public:
        void write(byte buf[], CipherInfo& info) throw(DiffusionException) {
            memset(buf, 0, length());
            int offset = IH::DC3_14().size();
            memcpy(buf, IH::DC3_14().header(), offset);
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
        }

        void read(byte buf[], CipherInfo& info) throw(DiffusionException) {
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
    class FileInfoHandler_DC314_V1 : public AbstractInfoHandler {
    public:
        FileInfoHandler_DC314_V1(InfoReader* reader = nullptr) : AbstractInfoHandler(reader) {

        }

        void write(byte buf[], CipherInfo& info) throw(DiffusionException) {
            memset(buf, 0, length());
            int offset = length() - IH::DC3_14().size();
            memcpy(buf + offset, IH::DC3_14().inHeader(), IH::DC3_14().size());
            offset--;
            buf[offset--] = version();
            buf[offset--] = info.log;
            buf[offset--] = info.diff >> 8 & 0xFF;
            buf[offset--] = info.diff >> 0 & 0xFF;
            buf[offset--] = info.algorithm >> 8 & 0xFF;
            buf[offset--] = info.algorithm >> 0 & 0xFF;
            buf[offset--] = info.level >> 8 & 0xFF;
            buf[offset--] = info.level >> 0 & 0xFF;
            buf[offset--] = info.cycle >> 0 & 0xFF;
            buf[offset] = contains(info.options, CO::PADDING);
        }

        void read(byte buf[], CipherInfo& info) throw(DiffusionException) {
            if (!memcmp(buf + (length() - IH::DC3_14().size()), IH::DC3_14().inHeader(), IH::DC3_14().size())) {
                if (reader != nullptr) {
                    reader->read(buf, info);
                }
                //TODO throw exception
                throw new DiffusionException("");
            }
            //@formatter:off
            info.options &= ~FO::PADDING;          //subtracting padding
            int offset = length() - IH::DC3_14().size() - 1;
            info.log        = buf[offset--];
            info.diff       = buf[offset--] << 8;
            info.diff      |= buf[offset--];
            info.algorithm  = buf[offset--] << 8;  // version
            info.algorithm |= buf[offset--];
            info.level      = buf[offset--] << 8;  // version
            info.level     |= buf[offset--];
            info.cycle      = buf[offset--];
            bool pad        = buf[offset--] & 0x1;
            info.options   |= pad ? CO::PADDING : 0;
            info.group      = 1 << info.log;
            //@formatter:on
        }
    };
}
#endif //DIFFUSION_DC314_V1_H
