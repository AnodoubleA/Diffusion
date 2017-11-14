//
// Created by Alice on 2017.02.28.
//
#pragma once
#ifndef DIFFUSION_STREAMS_H
#define DIFFUSION_STREAMS_H

#include <string>
#include <iostream>
#include "../core/chars.h"

namespace lc{
    class Streams {
    public:
        inline static bool eof(char c) {
            return c == EOF || c == 26;
        }

        static void read(std::istream& in, std::string& accept, char flag = MULTI_LINE_SWITCH) {
            bool SWITCH = false;
            char c;
            int index = 0;
            while (true) {
                c = (char) in.get();
                if (index == 0 && c == flag && !SWITCH) {
                    SWITCH = true;
                    continue;
                }
                if (c == '\n' && !SWITCH) {
                    break;
                }
                if (SWITCH && eof(c)) {
                    break;
                }
                index++;
                accept.push_back(c);
            }
            in.clear();
            in.sync();
        }

    };
}
#endif //DIFFUSION_STREAMS_H
