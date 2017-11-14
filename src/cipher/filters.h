//
// Created by Angel on 2017/4/9.
//

#ifndef DIFFUSION_FILE_FILTER_H
#define DIFFUSION_FILE_FILTER_H

#include "../tool/Strings.h"
#include "filter.h"

namespace lc{
    class FileFilter : public Filter<_finddata_t&> {
        std::string regex;
        int size = 0;
    public:

        void setSize(int size) {
            this->size = size;
        }

        void setRegex(const std::string& regex) {
            this->regex = regex;
        }

        bool accept(_finddata_t& data) override {
            if (regex.length() > 0) {
                return Strings::match(data.name, regex);
            }
            return data.size > size;
        }
    };
}
#endif //DIFFUSION_FILE_FILTER_H
