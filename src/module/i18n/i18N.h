//
// Created by Alice on 2017.03.07.
//
#pragma once
#ifndef DIFFUSION_I18N_H
#define DIFFUSION_I18N_H


#include "../format/messages.h"

namespace lc{

    class Internationalization {
    public:
        virtual void load(const std::string& lang, Internationalization* def = nullptr)  = 0;

        virtual std::string get(const std::string& key) = 0;

        virtual std::string gf(const std::string& key, ...) = 0;

        virtual std::string operator[](const std::string key) {
            return get(key);
        }
    };

    class AbstractI18N : public Internationalization {
    protected:
        Internationalization* def = nullptr;
        std::map<std::string, std::string> content;
        typedef std::map<std::string, std::string>::iterator Iterator;
    public:
        void load(const std::string& lang, Internationalization* def) override {
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

        std::string gf(const std::string& key, ...) override {
            std::string value = get(key);
            if (value == EMPTY_STRING) {
                return EMPTY_STRING;
            }
            std::vector<void*> args;
            va_list start;
            va_start(start, key);
            void* get;
            while ((get = va_arg(start, void*)) != 0) {
                args.push_back(get);
            }
            va_end(start);
            return Messages::doformat(value, args);
        }
    };

    extern Internationalization* I18N;
}

#endif //DIFFUSION_I18N_H
