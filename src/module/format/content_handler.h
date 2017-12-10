//
// Created by Angel on 2017/4/2.
//

#ifndef DIFFUSION_CONTENT_HANDLER_H
#define DIFFUSION_CONTENT_HANDLER_H

#include <regex>
#include "content.h"
#include "formatter.h"
#include "../../core/DiffusionException.h"

namespace lc{
    namespace mf{
        extern std::map<std::string, Formatter*> map_f;
        extern std::regex* reg_number;
        extern std::match_results<std::string::const_iterator> result;
        extern std::string DEF_FORMATTER;

        //@formatter:off
        extern  uint64 MILLISECOND;
        extern  uint64 SECOND;
        extern  uint64 MINUTE;
        extern  uint64 HOUR;
        extern  uint64 DAY;
        extern  uint64 MONTH;
        extern  uint64 YEAR;
        extern  uint64 CENTURY;
        extern  uint64 BT;
        extern  uint64 KB;
        extern  uint64 MB;
        extern  uint64 GB;
        extern  uint64 TB;
        extern  uint64 PB;
        extern  uint64 ZB;
        extern  uint64 EB;
        //@formatter:on
    }

    void init_formatter();

    class MultiArgHandler : public ContentHandler {

    public:
        static void regist(const std::string& name, Formatter* formatter) {
            mf::map_f[name] = formatter;
        }

        const std::string& handle(std::string& content, int index, std::vector<void*>& args) {
            std::vector<std::string> bodies;
            split(content, ",", bodies);
            std::string name = mf::DEF_FORMATTER;
            std::string options;
            char c;
            switch (bodies.size()) {
                case 0:
                    name = "%";
                    options = "%s";
                    break;
                case 1:
                    c = bodies[0][0];
                    if (c == '%') {
                        name = "%";
                        options = content;
                        break;
                    }
                    if (isNumber(bodies[0])) {
                        index = atoi(bodies[0].c_str());
                    } else {
                        name = bodies[0];
                    }
                    break;
                case 2:
                    c = bodies[1][0];
                    if (isNumber(bodies[0])) {
                        index = atoi(bodies[0].c_str());
                        if (c == '%') {
                            name = "%";
                            options = bodies[1].substr(1);
                        } else {
                            name = bodies[1];
                        }
                    } else {
                        name = bodies[0];
                        options = bodies[1];
                    }
                    break;
                case 3:
                    index = atoi(bodies[0].c_str());
                    name = bodies[1];
                    options = bodies[2];
                    break;
            }
            std::map<std::string, Formatter*>::iterator it = mf::map_f.find(name);
            if (it == mf::map_f.end()) {
                throw DiffusionException("Unknown format:" + name);
            }
            int size = args.size() - 1;
            const std::string& ret = it->second->format(options, index > size ? 0 : args[index]);
            content.clear();
            content.append(ret);
            return content;
        }

    protected:
        bool isNumber(const std::string& content) {
            return regex_match(content.c_str(), mf::result, *mf::reg_number);
        }

        void split(const std::string& s, const std::string& delim, std::vector<std::string>& ret) {
            size_t last = 0;
            size_t index = s.find_first_of(delim, last);
            while (index != std::string::npos) {
                ret.push_back(s.substr(last, index - last));
                last = index + 1;
                index = s.find_first_of(delim, last);
            }
            if (index - last > 0) {
                ret.push_back(s.substr(last, index - last));
            }
        }
    };
}
#endif //DIFFUSION_CONTENT_HANDLER_H
