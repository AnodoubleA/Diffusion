//
// Created by Alice on 2017/12/10.
//

#ifndef DIFFUSION_HEADERINFOHANDLER_H
#define DIFFUSION_HEADERINFOHANDLER_H

#include <memory.h>
#include "../info_handler.h"
#include "../InfoHeader.h"
#include "../InfoHandlerFactory.h"

namespace lc {
    class HeaderInfoHandler : public InfoHandler {
    public:

        HeaderInfoHandler(InfoReader* reader = nullptr) : reader(reader) {

        }

        int write(byte* buf, CipherInfo& info) throw(DiffusionException) {
            InfoHeader IH = getInfoHeader();
            memset(buf, 0, length());
            memcpy(buf, IH.header(), IH.size());
            InfoHandler* handler = InfoHandlerFactory::defaultFactory().getHandler(IH.identity(), 1, type());
            handler->write(buf + IH.size(), info);
            delete handler;
            return length();
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
            InfoHandler* handler = InfoHandlerFactory::defaultFactory().getHandler(IH.identity(), version, type());
            handler->read(buf + IH.size(), info);
            delete handler;
            return length();
        }

    protected:
        virtual InfoHeader& getInfoHeader() = 0;
    };
}
#endif //DIFFUSION_HEADERINFOHANDLER_H
