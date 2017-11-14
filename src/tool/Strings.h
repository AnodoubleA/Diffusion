//
// Created by Alice on 2017.02.24.
//
#pragma once
#ifndef DIFFUSION_STRINGS_H
#define DIFFUSION_STRINGS_H

#include <string>
#include <regex>
#include "../core/chars.h"
#include "funs.h"

namespace lc{
    class Strings {
    public :
        inline static bool endWith(std::string& src, const char* end) {
            int64 sl = src.length();
            int64 el = strlen(end);
            if (sl < el) {
                return false;
            }
            return src.find(end, sl - el) != std::string::npos;
        }

        static std::string& replaceAll(std::string& str, const char* oldValue, const char* newValue) {
            int offset = 0;
            while (true) {
                std::string::size_type pos(0);
                pos = str.find(oldValue, offset);
                if (pos != std::string::npos) {
                    str.replace(pos, strlen(oldValue), newValue);
                    offset = pos + strlen(newValue);
                } else {
                    break;
                }
            }
            return str;
        }

        static bool match(const std::string& content, const std::string& reg) {
            std::regex pattern(reg, std::regex_constants::extended);
            std::match_results<std::string::const_iterator> result;
            return regex_match(content, result, pattern);
        }

        static bool test_reg(const std::string& reg) {
            try {
                std::regex pattern(reg, std::regex_constants::extended);
            } catch (std::exception& e) {
                return false;
            }
            return true;
        }

        template<class T>
        static std::basic_string<T>& trim(std::basic_string<T>& s) {
            if (s.empty()) {
                return s;
            }
            typename std::basic_string<T>::iterator c;
            for (c = s.begin(); c != s.end() && isBlank(*c++););
            s.erase(s.begin(), --c);

            for (c = s.end(); c != s.begin() && isBlank(*--c););
            s.erase(++c, s.end());
            return s;
        }

        std::vector<std::string> split(std::string& s, const std::string& delim) {
            std::vector<std::string> ret;
            split(s, delim, ret);
            return ret;
        }

        void split(std::string& s, const std::string& delim, std::vector<std::string>& ret) {
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

        static void
        split(const std::string& input, std::string& buf, int& offset, int& length, char end = '\0', char wrap = DEF_WRAP) {
            char c = 0;
            bool SWITCH = false;
            bool vc = false;
            while (offset < length) {
                c = input[offset];
                if (c == wrap && !SWITCH) {
                    if (offset == 0 && length > 2) {
                        SWITCH = true;
                    } else if (offset > 0 && length > 2 && input[offset - 1] != TRANS_MEAN) {
                        SWITCH = true;
                    }
                    if (SWITCH) {
                        offset++;
                        continue;
                    }
                } else if (SWITCH && c == wrap) {
                    if (offset > 1 && length > 2 && input[offset - 1] != TRANS_MEAN) {
                        offset++;
                        break;
                    }
                }
                if (!vc && isBlank(input[offset]) && !SWITCH) {
                    offset++;
                    continue;
                } else {
                    if (!vc) vc = true;
                }
                buf += c;
                if ((input[offset++] == end) && !SWITCH) {
                    break;
                }
            }
            Strings::trim(buf);
            if (SWITCH) {
                char trans[] = {TRANS_MEAN, wrap, '\0'};
                char wraps[] = {wrap, '\0'};
                Strings::replaceAll(buf, trans, wraps);
            }
        }
    };
}

#endif //DIFFUSION_STRINGS_H
