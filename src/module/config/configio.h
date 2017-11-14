//
// Created by Angel on 2017/3/29.
//

#ifndef DIFFUSION_CONFIGRW_H
#define DIFFUSION_CONFIGRW_H

#include <exception>
#include <iostream>
#include <map>
#include "../../core/DiffusionException.h"

namespace lc{

    class ConfigReader {
    public:
        virtual void read(const std::string& file, std::map<std::string, std::string>& M) throw(DiffusionException) = 0;

        virtual void read(std::istream& in, std::map<std::string, std::string>& M) throw(DiffusionException) = 0;
    };

    class ConfigWriter {
    public:
        virtual void write(const std::string& file, std::map<std::string, std::string>& M) throw(DiffusionException) = 0;

        virtual void write(std::ostream& out, std::map<std::string, std::string>& M) throw(DiffusionException) = 0;

        virtual void write(std::ostream& out, const std::string& comments) throw(DiffusionException) = 0;

    };
}
#endif //DIFFUSION_CONFIGRW_H
