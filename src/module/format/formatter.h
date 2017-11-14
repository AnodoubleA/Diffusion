//
// Created by Alice on 2017.03.17.
//

#ifndef DIFFUSION_FORMATTER_H
#define DIFFUSION_FORMATTER_H

#include <string>
#include <iostream>
#include "level.h"
#include "../../core/chars.h"

namespace lc{
    class Formatter {
    public:
        virtual const std::string& format(std::string& options, void* argument) = 0;
    };


    class CFormatter : public Formatter {
    public:
        const std::string& format(std::string& options, void* argument) override {
            char buf[128];
            if (options == EMPTY_STRING)options = "%s";
            snprintf(buf, 128, options.c_str(), argument == nullptr ? 0 : argument);
            options.clear();
            options.append(buf);
            return options;
        }
    };

    class SelfFormatter : public Formatter {
    public:
        const std::string& format(std::string& options, void* argument) override {
            Formatter* formatter = (Formatter*) argument;
            formatter->format(options, argument);
        }
    };

    class LevelFormatter : public Formatter {
        Level* level = nullptr;
    public:
        LevelFormatter(Level* level) : level(level) {}

        const std::string& format(std::string& options, void* argument) override {
            char buf[30];
            sprintf(buf, "%llu", argument == nullptr ? 0LL : *(uint64*) argument);
            uint64 number = (uint64) atoll(buf);
            LevelContext context = {number, options};
            Level* next = level->init(context);
            while (next != nullptr) {
                if (!next->format(context)) {
                    break;
                }
                next = next->next();
            }
            return context.options;
        }
    };
}
#endif //DIFFUSION_FORMATTER_H
