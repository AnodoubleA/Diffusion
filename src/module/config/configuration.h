//
// Created by Alice on 2017.03.21.
//

#ifndef DIFFUSION_CONFIGURATION_H
#define DIFFUSION_CONFIGURATION_H

#include <string>
#include <map>
#include "../../core/chars.h"
#include "../../core/DiffusionException.h"

namespace lc{
    class Configuration {
    public:
        virtual void load(const std::string& path, Configuration* def = nullptr) throw(DiffusionException) = 0;

        virtual std::string get(const std::string& key) = 0;

        virtual std::string get(const std::string& key, const std::string& def) = 0;

        virtual std::string operator[](const std::string key) {
            return get(key);
        }
    };

    class AbstractConfiguration : public Configuration {
    protected:
        Configuration* def = nullptr;
        std::map<std::string, std::string> content;
        typedef std::map<std::string, std::string>::iterator Iterator;
    public:
        void load(const std::string& path, Configuration* def = nullptr) throw(DiffusionException) {
            this->def = def;
        }

        std::string get(const std::string& key) override {
            Iterator it = content.find(key);
            if (it != content.end()) {
                return it->second;
            }
            if (def != nullptr) {
                return def->get(key);
            }
            return EMPTY_STRING;
        }

        std::string get(const std::string& key, const std::string& def) override {
            Iterator it = content.find(key);
            std::string* value = nullptr;
            if (it != content.end()) {
                value = &it->second;
            }
            if (value == nullptr) {
                return def;
            }
            return *value == EMPTY_STRING ? def : *value;
        }
    };

}
#endif //DIFFUSION_CONFIGURATION_H
