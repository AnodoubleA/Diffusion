//
// Created by Angel on 2017/3/31.
//

#ifndef DIFFUSION_TYPE_CONFIG_H
#define DIFFUSION_TYPE_CONFIG_H

#include "configuration.h"
#include "../../core/types.h"

namespace lc{
    class TypeConfig : public Configuration {
    public:
        virtual int64 getInt(const std::string& key, int64 def = 0) = 0;

        virtual double getFloat(const std::string& key, double def = 0) = 0;

        virtual bool getBool(const std::string& key, bool def = false) = 0;
    };
}
#endif //DIFFUSION_TYPE_CONFIG_H
