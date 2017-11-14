//
// Created by Alice on 2017.03.14.
//

#ifndef DIFFUSION_FUNS_H
#define DIFFUSION_FUNS_H

#include <string>
#include <io.h>
#include <afxres.h>
#include <regex>
#include "../core/types.h"
#include "../core/chars.h"

namespace lc{
    namespace fn{
        static std::regex* reg_blank = new std::regex("^\\s*$", std::regex_constants::extended);
        static std::match_results<std::string::const_iterator> result;
    }
    typedef std::function<void(void*)> Runnable;

    static void delTable(byte** V, int row = -1) {
        if (V == nullptr) {
            return;
        }
        if (row == -1) {
            row = sizeof(V) / sizeof(V[0]);
        }
        for (int i = 0; i < row; i++) {
            delete[] V[i];
            V[i] = nullptr;
        }
        delete[] V;
        V = nullptr;
    }

    static int make_dirs(std::string& dir) {
        int64 len = dir.length();
        if (len > MAX_PATH) {
            return -1;
        }
        if (len > 0 && (dir.at(len - 1) != FILE_SEPARATOR)) {
            dir.push_back(FILE_SEPARATOR);
        }
        char temp[MAX_PATH] = {0};
        int64 last = dir.find_last_of(FILE_SEPARATOR);
        for (int i = 0; i < last; ++i) {
            temp[i] = dir[i];
            if (temp[i] == FILE_SEPARATOR) {
                if (access(temp, 0) != 0) {
                    int ret = mkdir(temp);
                    if (ret != 0) {
                        return ret;
                    }
                }
            }
        }
        return 0;
    }

    inline static bool contains(int64 options, int64 include) {
        return (options & include) == include;
    }

    inline static bool contains_any(int64 options, int64 include) {
        return (options & include) != 0;
    }

    inline static bool contains(int64 options, int64 include, int64 unclude) {
        return (options & include) == include && (options & unclude) != unclude;
    }

    inline static uint64 getSystemTime() {
        return GetTickCount();
    }

    inline static uint64 get_length(std::istream& in) {
        int64 offset = in.tellg();
        in.seekg(0, std::ios::end);
        uint64 length = (uint64) in.tellg();
        in.seekg(offset);
        return length;
    }


    static inline bool isBlank(int s) {
        return s == ' ' || s == '\t' || s == '\r' || s == '\n';
    }

    static inline bool isBlank(std::string& content) {
        return content == EMPTY_STRING || regex_match(content, fn::result, *fn::reg_blank);
    }

    static inline void sub(int& value, int be) {
        value &= ~be;
    }

    static std::string subif(const std::string& value, int max, int start = -1) {
        int64 length = value.length();
        if (length < max) {
            return value;
        }
        if (start > max) {
            start = 2;
        }
        int64 half = max / 2;
        start = start == -1 ? half : start;
        int64 after = length - (max - (start == -1 ? half : start) - 3);
        std::string sub = value.substr(0, start) + "..." + value.substr(after);
        return sub;
    }

    static void fill(std::string& value, int width, int keep, char fc = '.') {
        int64 count = (width - value.length() % width);
        count = (count > keep ? count : count + width + 1) - keep;
        for (int i = 0; i < count; i++) {
            value.push_back(fc);
        }
    }
}
#endif //DIFFUSION_FUNS_H
