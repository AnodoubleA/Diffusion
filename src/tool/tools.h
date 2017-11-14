//
// Created by Alice on 2017.03.02.
//
#pragma once
#ifndef DIFFUSION_TOOLS_H
#define DIFFUSION_TOOLS_H

#include <cmath>
#include "../module/cmds/options.h"
#include "../cipher/structs.h"
#include "../core/DiffusionException.h"
#include "../module/config/Config.h"
#include "validator.h"
#include "converter.h"
#include "funs.h"

namespace lc{
    typedef class Tool {
    public:
        inline static void computeInit(Init& init, Info& info, CipherOption& op, int e = 0) {
            computeInit(init, op.size, e);
            info.key = op.key;
            info.keySize = op.key_size;
            info.level = op.level;
            info.group = op.size;
            info.options = op.options;
            info.log = init.L;
        }

        inline static void computeInit(Init& init, int N, int e = 0) {
            int lg = (int) ceil(log2(N));
            init.L = lg;
            init.N = N;
            init.R = init.L + e;
        }


        static Validator* validate_size(std::string& size, int min, int max) {
            return validate_size(atoi(const_cast<char*>(size.c_str())), min, max);
        }

        static Validator* validate_size(int size, int min, int max) {
            if ((size & (size - 1)) != 0) {
                return new Validator(I18N->gf(VDR_N_INC, size));
            }
            if (size < min || size > max) {
                return new Validator(I18N->gf(VDR_N_OOR, MIN_SIZE, MAX_SIZE, size));
            }
            return new Validator(vdr::VALID, EMPTY_STRING);
        }

        static void print(const byte c[], int size, bool enter = true) {
            std::cout << "[";
            for (int i = 0; i < size; i++) {
                const std::string& s = Cvt::toString(c[i] & 0xff, 16);
                std::cout << "0x" << ((c[i] & 0xFF) > 15 ? s : "0" + s) << (i != size - 1 ? "," : "");
            }
            std::cout << "]" << (enter ? '\n' : ' ');
        }

        static void write_options(std::string& ops, int& options) {
            if (ops.find(C_RECURSION) != -1) {
                options |= FO::RECURSION;
            }
            if (ops.find(C_DO_SOURCE) != -1) {
                options |= FO::DO_SOURCE;
            }
//            if (ops.find(C_DELETE_SOURCE) != -1) {
//                options |= FO::DEL_SOURCE;
//            }
            if (ops.find(C_PADDING) != -1) {
                options |= FO::PADDING;
            }
            if (ops.find(C_COVER) != -1) {
                options |= FO::COVER;
            }
        }

        static std::string cvt_regex(std::string pattern) {
            if (pattern.length() == 0) {
                return pattern;
            }
            if (pattern.at(0) == C_REG_SPT) {
                return pattern.erase(0, 1);
            }
            Strings::replaceAll(pattern, ".", "\\.");
            Strings::replaceAll(pattern, "*", ".*");
            return pattern;
        }

        static void read_key(CipherOption& option, std::map<std::string, std::string>& M) {
            if (M["-kfl"] == NON) {
                option.key = Cvt::from_input(M["-k"], M["-kf"], option.key_size);
            }
        }

        static std::string& erase_remend(std::string& value, char c = FILE_SEPARATOR) {
            int i = value.length();
            if (i < 1) {
                return value;
            }
            i--;
            while (value.at(i) == c) {
                value.erase(i--);
            }
            return value;
        }

        static std::string get_output(std::string out, bool& isdir_out) {
            if (out.length() < 1) {
                return out;
            }
            if (out.at(0) == '>') {
                isdir_out = false;
                out.erase(0, 1);
            }
            return erase_remend(out);
        }

        static int get_fileSmashTimes(std::string& ops) {
            int index = ops.find(C_DELETE_SOURCE);
            if (index == -1) {
                return DEFAULT_SMASH_TIMES;
            }
            int length = ops.length();
            std::string count;
            char c = 0;
            while (index < length) {
                c = ops[++index];
                if (c >= 48 && c <= 57) {
                    count.push_back(c);
                } else {
                    break;
                }
            }
            if (count.length() > 0) {
                return atoi(count.c_str());
            }
            return DEFAULT_SMASH_TIMES;
        }

        static int checkValidator(Console& console, Validator* validator) {
            Validator* head = validator->head();
            head->print(*I18N, console);
            int code = head->codes();
            delete (head);
            return code;
        }
    } T;
}
#endif //DIFFUSION_TOOLS_H
