//
// Created by Alice on 2017.03.21.
//

#ifndef DIFFUSION_INI_CONFIG_H
#define DIFFUSION_INI_CONFIG_H

#include <io.h>
#include "configuration.h"
#include "values.h"
#include "config_handler.h"
#include "type_config.h"

namespace lc{
    class IniConfig : public TypeConfig, public AbstractConfiguration {
    public:

        void load(const std::string& path, Configuration* def) throw(DiffusionException) {
            AbstractConfiguration::load(path, def);
            content.clear();
            ConfigHandler handler;
            handler.read(path, content);
        }

        std::string get(const std::string& key) override {
            return AbstractConfiguration::get(key);
        }

        std::string get(const std::string& key, const std::string& def) override {
            return AbstractConfiguration::get(key, def);
        }

        int64 getInt(const std::string& key, int64 def = 0) {
            std::string value = get(key);
            if (value == EMPTY_STRING) {
                return def;
            }
            return atoll(value.c_str());
        }

        double getFloat(const std::string& key, double def = 0) {
            std::string value = get(key);
            if (value == EMPTY_STRING) {
                return def;
            }
            return atof(value.c_str());
        }

        bool getBool(const std::string& key, bool def = false) {
            std::string value = get(key);
            if (value == EMPTY_STRING) {
                return def;
            }
            if (value == "TRUE" || value == "true") {
                return true;
            }
            return false;
        }
    };
}
#endif //DIFFUSION_INI_CONFIG_H
