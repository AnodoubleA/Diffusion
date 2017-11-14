//
// Created by Alice on 2017.03.04.
//
#pragma once
#ifndef C_TEST_BASE64_H
#define C_TEST_BASE64_H

#include <algorithm>
#include <stdexcept>
#include "../core/types.h"
#include "../core/DiffusionException.h"

namespace lc{
    constexpr static const char base64[] = {
            'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M',
            'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z',
            'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm',
            'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
            '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '+', '/'
    };
    static const char fromBase64[] = {
            -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
            -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
            -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 62, -1, -1, -1, 63,
            52, 53, 54, 55, 56, 57, 58, 59, 60, 61, -1, -1, -1, -2, -1, -1,
            -1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14,
            15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, -1, -1, -1, -1, -1,
            -1, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40,
            41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, -1, -1, -1, -1, -1,
            -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
            -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
            -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
            -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
            -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
            -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
            -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
            -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    };

    class Encoder {
        std::string newline = "\r\n";
        int linemax = -1;
        bool doPadding = true;
    public:
        Encoder(const std::string newline = "\r\n", int linemax = -1, bool doPadding = true) {
            this->newline = newline;
            this->linemax = linemax;
            this->doPadding = doPadding;
        }

        int outLength(int srclen) {
            int len = 0;
            if (doPadding) {
                len = 4 * ((srclen + 2) / 3);
            } else {
                int n = srclen % 3;
                len = 4 * (srclen / 3) + (n == 0 ? 0 : n + 1);
            }
            if (linemax > 0)
                len += (len - 1) / linemax * (newline.length());
            return len;
        }

        byte* encode(byte in[], int length, int& outlen) {
            outlen = outLength(length);
            byte* dst = new byte[outlen];
            encode(in, dst, length);
            return dst;
        }

        int encode(byte in[], byte dst[], int length) {
            int sp = 0;
            int end = length;
            int slen = (end) / 3 * 3;
            int sl = 0 + slen;
            if (linemax > 0 && slen > linemax / 4 * 3)
                slen = linemax / 4 * 3;
            int dp = 0;
            while (sp < sl) {
                int sl0 = std::min(sp + slen, sl);
                for (int sp0 = sp, dp0 = dp; sp0 < sl0;) {
                    int bits = (in[sp0++] & 0xff) << 16 |
                               (in[sp0++] & 0xff) << 8 |
                               (in[sp0++] & 0xff);
                    dst[dp0++] = base64[(bits >> 18) & 0x3f];
                    dst[dp0++] = base64[(bits >> 12) & 0x3f];
                    dst[dp0++] = base64[(bits >> 6) & 0x3f];
                    dst[dp0++] = base64[bits & 0x3f];
                }
                int dlen = (sl0 - sp) / 3 * 4;
                dp += dlen;
                sp = sl0;
                if (dlen == linemax && sp < end) {
                    for (byte b : newline) {
                        dst[dp++] = b;
                    }
                }
            }
            if (sp < end) {               // 1 or 2 leftover bytes
                int b0 = in[sp++] & 0xff;
                dst[dp++] = base64[b0 >> 2];
                if (sp == end) {
                    dst[dp++] = base64[(b0 << 4) & 0x3f];
                    if (doPadding) {
                        dst[dp++] = '=';
                        dst[dp++] = '=';
                    }
                } else {
                    int b1 = in[sp++] & 0xff;
                    dst[dp++] = base64[(b0 << 4) & 0x3f | (b1 >> 4)];
                    dst[dp++] = base64[(b1 << 2) & 0x3f];
                    if (doPadding) {
                        dst[dp++] = '=';
                    }
                }
            }
            return dp;
        }
    };

    class Decoder {
    protected:
        bool isMIME = false;
        char H[2];
    public:
        int outLength(byte in[], int length) {
            int off = 0;
            int paddings = 0;
            int len = length - off;
            if (len == 0)
                return 0;
            if (len < 2) {
                if (isMIME && fromBase64[0] == -1)
                    return 0;
                throw DiffusionException(
                        "Input byte[] should at least have 2 bytes for base64 bytes");
            }
            if (isMIME) {
                // scan all bytes to fill out all non-alphabet. a performance
                // trade-off of pre-scan or Arrays.copyOf
                int n = 0;
                while (off < length) {
                    int b = in[off++] & 0xff;
                    if (b == '=') {
                        len -= (length - off + 1);
                        break;
                    }
                    if ((b = fromBase64[b]) == -1)
                        n++;
                }
                len -= n;
            } else {
                if (in[length - 1] == '=') {
                    paddings++;
                    if (in[length - 2] == '=')
                        paddings++;
                }
            }
            if (paddings == 0 && (len & 0x3) != 0)
                paddings = 4 - (len & 0x3);
            return 3 * ((len + 3) / 4) - paddings;
        }

        byte* decode(const std::string& src, int& outlen) {
            return decode((byte*) const_cast<char*>(src.c_str()), src.length(), outlen);
        }

        /**
         * Remember release memory;
         * @param in
         * @return
         */
        byte* decode(byte in[], int length, int& outlen) {
            outlen = outLength(in, length);
            byte* dst = new byte[outlen];
            decode(in, dst, length);
            return dst;
        }

        int decode(byte in[], byte dst[], int length) {
            int inf = 0;
            int dp = 0;
            int bits = 0;
            int shiftto = 18;       // pos of first byte of 4-byte atom
            while (inf < length) {
                int b = in[inf++] & 0xff;
                if ((b = fromBase64[b]) < 0) {
                    if (b == -2) {         // padding byte '='
                        // =     shiftto==18 unnecessary padding
                        // x=    shiftto==12 a dangling single x
                        // x     to be handled together with non-padding case
                        // xx=   shiftto==6&&inf==length missing last =
                        // xx=y  shiftto==6 last is not =
                        if (shiftto == 6 && (inf == length || in[inf++] != '=') ||
                            shiftto == 18) {
                            throw DiffusionException(
                                    "Input byte array has wrong 4-byte ending unit");
                        }
                        break;
                    }
                    if (isMIME)    // skip if for rfc2045
                        continue;
                    else
                        ltoa(in[inf - 1], H, 16);
                    throw DiffusionException(
                            "Illegal base64 character " + std::string(H));
                }
                bits |= (b << shiftto);
                shiftto -= 6;
                if (shiftto < 0) {
                    dst[dp++] = (byte) (bits >> 16);
                    dst[dp++] = (byte) (bits >> 8);
                    dst[dp++] = (byte) (bits);
                    shiftto = 18;
                    bits = 0;
                }
            }
            // reached end of byte array or hit padding '=' characters.
            if (shiftto == 6) {
                dst[dp++] = (byte) (bits >> 16);
            } else if (shiftto == 0) {
                dst[dp++] = (byte) (bits >> 16);
                dst[dp++] = (byte) (bits >> 8);
            } else if (shiftto == 12) {
                // dangling single "x", incorrectly encoded.
                throw DiffusionException(
                        "Last unit does not have enough valid bits");
            }
            // anything left is invalid, if is not MIME.
            // if MIME, ignore all non-base64 character
            while (inf < length) {
                if (isMIME && fromBase64[in[inf++]] < 0)
                    continue;
                throw DiffusionException(
                        "Input byte array has incorrect ending byte at " + inf);
            }
            return dp;
        }

    };

    static Encoder* _encoder;
    static Decoder* _decoder;

    class Base64 {

    public:

        static Encoder& encoder() {
            if (_encoder == nullptr) {
                _encoder = new Encoder();
            }
            return *_encoder;
        }

        static Decoder& decoder() {
            if (_decoder == nullptr) {
                _decoder = new Decoder();
            }
            return *_decoder;
        }

    };


}
#endif //C_TEST_BASE64_H
