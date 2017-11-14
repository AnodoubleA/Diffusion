//
// Created by Angel on 2017/4/2.
//

#ifndef DIFFUSION_MESSAGES_H
#define DIFFUSION_MESSAGES_H

#include <vector>
#include <string>
#include "format.h"

namespace lc{
    namespace mf{
        extern Format format;
    }
    class Messages {
    public:
        static std::string format0(const std::string& message, ...) {
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
        static std::string& format(const std::string& message, ...) {
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

        static std::string& doformat(const std::string& message, std::vector<void*>& args) {
            return mf::format.doformat(message, args);
        }
    };
}
#endif //DIFFUSION_MESSAGES_H
