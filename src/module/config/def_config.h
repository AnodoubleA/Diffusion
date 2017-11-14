//
// Created by Angel on 2017/3/30.
//

#ifndef DIFFUSION_DEF_CONFIG_H
#define DIFFUSION_DEF_CONFIG_H


#include "configuration.h"
#include "config_key.h"

namespace lc{
    class DefaultConfig : public AbstractConfiguration {

    public:
        void load(const std::string& path, Configuration* def = nullptr) throw(DiffusionException) {
            //@formatter:off
            content[KEY_START_CMD]          = "help";
            content[KEY_LANG]               = "zh_CN";
            content[KEY_BUFFER_MULTIPLE]    = "1024";
            content[DEF_CMD_TEXT]           = "-s 2048 -l 2";
            content[DEF_CMD_FILE]           = "-s 2048 -l 1";
        }
    };
}
#endif //DIFFUSION_DEF_CONFIG_H
