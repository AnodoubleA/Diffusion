//
// Created by Alice on 2017/12/10.
//

#ifndef DIFFUSION_HEADERINFOHANDLER_H
#define DIFFUSION_HEADERINFOHANDLER_H

#include <memory.h>
#include "../info_handler.h"
#include "../InfoHeader.h"

namespace lc {
    class HeaderInfoHandler : public AbstractInfoHandler {
    public:

        HeaderInfoHandler(InfoReader* reader) : reader(reader) {

        }

        int write(byte* buf, CipherInfo& info) throw(DiffusionException) {
            InfoHeader IH = getInfoHeader();
            memset(buf, 0, length());
            memcpy(buf, IH.header(), IH.size());
            return IH.size();
        }

        int read(byte* buf, CipherInfo& info) throw(DiffusionException) {
            InfoHeader IH = getInfoHeader();
            if (!memcmp(buf, IH.header(), IH.size())) {
                if (reader != nullptr) {
                    reader->read(buf, info);
                }
                //TODO add exception
                throw DiffusionException("");
            }
            int version = buf[IH.size()];
            //TODO get handler by version
            return IH.size() + 1;
        }

    protected:
        virtual InfoHeader& getInfoHeader() = 0;
    };
}
#endif //DIFFUSION_HEADERINFOHANDLER_H
