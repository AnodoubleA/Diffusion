//
// Created by Alice on 2017.03.05.
//
#pragma once
#ifndef C_TEST_INTEGER_H
#define C_TEST_INTEGER_H

#include <string>
#include <cstdlib>
#include <stdexcept>
#include "../core/types.h"
#include "base64.h"

namespace lc{
    typedef class Converter {
        static Base64 base64;
    public:

        static std::string i2h(byte code[], int length, int radix) {
            std::string buf;
            char H[16];
            int c, off = 0;
            while (off < length) {
                c = code[off++] & 0xFF;
                ltoa(c, (char*) H, radix);
                if (c < 16) {
                    buf.append("0");
                }
                buf.append(H);
            }
            return buf;
        }

        static std::string toString(int64 i, int radix = 16) {
            char H[16];
            ltoa(i, H, radix);
            return std::string(H);
        }

        static long h2i(const std::string& hex) {
            char* offset;
            if (hex.length() > 2) {
                if (hex[0] == '0' && hex[1] == 'x') {
                    return strtol(hex.c_str(), &offset, 0);
                }
            }
            return strtol(hex.c_str(), &offset, 16);
        };

        static byte* fromHex(const byte hex[], int length) {
            byte* out = new byte[length / 2];
            fromHex(hex, out, length);
            return out;
        }

        static int fromHex(const byte hex[], byte dest[], int length) {
            int off = 0;
            int count = off + length;
            if ((count & 1) != 0) {
                throw DiffusionException("Hex string's length not invalid: " + std::to_string(count));
            }
            if (length < (count / 2)) {
                throw DiffusionException("Output is to short, need: " + std::to_string(count / 2));
            }
            char buf[2];
            int i = 0;
            while (off < count) {
                buf[0] = hex[off++];
                buf[1] = hex[off++];
                dest[i++] = (byte) (strtol(buf, NULL, 16));
            }
            return count / 2;
        }

        static byte*
        from_input(std::string& src, const std::string& format, int& outlen) {
            int srclen = src.length();
            if (format == "base64") {
                return base64.decoder().decode(src, outlen);
            }
            if (format == "hex") {
                outlen = srclen / 2;
                return fromHex((byte*) src.c_str(), srclen);
            }
            outlen = src.length();
            return (byte*) const_cast<char*>(src.c_str());
        }

        static std::string
        to_output(byte* src, const std::string& format, int length) {
            if (format == "base64") {
                int outlen = base64.encoder().outLength(length);
                byte out[outlen];
                return std::string((char*) base64.encoder().encode(src, length, length), outlen);
            }
            if (format == "hex") {
                return i2h(src, length, 16);
            }
            return std::string((char*) src, length);
        }
    } Cvt;
}
#endif //C_TEST_INTEGER_H
