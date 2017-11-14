//
// Created by Angel on 2017/3/30.
//

#ifndef DIFFUSION_I18NS_H
#define DIFFUSION_I18NS_H

#include "i18N.h"
#include "../config/config_handler.h"

namespace lc{
    class TextI18N : public AbstractI18N {
        constexpr static const char* LANG_EXNAME = ".lng";
    public:
        void load(const std::string& lang, Internationalization* def = nullptr) {
            std::string file = apppath + (char) FILE_SEPARATOR + "lang" + (char) FILE_SEPARATOR + lang + LANG_EXNAME;
            AbstractI18N::load(file, def);
            content.clear();
            std::ifstream in(file);
            if (in.is_open()) {
                ConfigHandler handler;
                handler.read(in, content);
            }

        }
    };

}
#endif //DIFFUSION_I18NS_H
