//
// Created by Angel on 2017/3/31.
//

#ifndef DIFFUSION_CMD_FACTORY_H
#define DIFFUSION_CMD_FACTORY_H


#include "Command.h"

namespace lc{
    class CommandFactory {
    public:
        virtual Command* make(int code) = 0;
    };
}
#endif //DIFFUSION_CMD_FACTORY_H
