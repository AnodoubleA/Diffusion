//
// Created by Alice on 2017.03.17.
//

#ifndef DIFFUSION_FORMAT_H
#define DIFFUSION_FORMAT_H

#pragma once

#include <string>
#include <vector>
#include <iostream>
#include "content_handler.h"
#include "../config/values.h"

namespace lc{
    namespace mf{
        extern const char* OPEN;
        extern const char* CLOSE;
        extern MultiArgHandler handler;
    }

    class Format {
    public:
        std::string& format(const std::string& message, ...) {
            if (message.length() == 0) {
                return const_cast<std::string&>(message);
            }
            std::vector<void*> args;
            va_list start;
            va_start(start, message);
            void* get;
            while ((get = va_arg(start, void*)) != 0) {
                args.push_back(get);
            }
            va_end(start);
            return doformat(message, args);
        }

        std::string& doformat(const std::string& source, std::vector<void*>& args) {
            std::string& message = const_cast<std::string&>(source);
            std::string::size_type start(0), end(0);
            int index = 0;
            while (true) {
                while (true) {
                    start = message.find(mf::OPEN, start);
                    if (start == -1) {
                        return message;
                    }
                    if (start > 0 && message[start - 1] == '\\') {
                        start += 2;
                        continue;
                    }
                    break;
                }
                end = start;
                while (true) {
                    end = message.find(mf::CLOSE, end);
                    if (end > 0 && message[end - 1] == '\\') {
                        end++;
                        continue;
                    }
                    if (end == -1) {
                        return message;
                    }
                    break;
                }
                std::string body = message.substr(start + 2, (end - start - 2));
                const std::string& value = mf::handler.handle(body, index++, args);
                message.replace(start, (end - start + 1), value);
            }
        }
    };
}
#endif //DIFFUSION_FORMAT_H
