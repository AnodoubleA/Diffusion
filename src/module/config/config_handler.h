//
// Created by Angel on 2017/3/28.
//

#ifndef DIFFUSION_PROPERTIES_H
#define DIFFUSION_PROPERTIES_H

#include <fstream>
#include "configio.h"
#include "../../core/chars.h"
#include "Config.h"
#include "../i18n/lang.h"

namespace lc{

    class LineReader {
    public:
        static const int char_cache = 8192;
        static const int line_cache = 1024;
        char* inCharBuf = new char[char_cache];
        char* lineBuf = new char[line_cache];
        int inLimit = 0;
        int inOff = 0;
        std::istream* inStream;

        LineReader(std::istream& inStream) {
            this->inStream = &inStream;
        }

        int readLine()throw(DiffusionException) {
            int len = 0;
            char c = 0;
            bool skipWhiteSpace = true;
            bool isCommentLine = false;
            bool isNewLine = true;
            bool appendedLineBegin = false;
            bool precedingBackslash = false;
            bool skipLF = false;

            while (true) {
                if (inOff >= inLimit) {
                    inStream->read(inCharBuf, char_cache);
                    inLimit = inStream->gcount();
                    inOff = 0;
                    if (inLimit <= 0) {
                        if (len == 0 || isCommentLine) {
                            return -1;
                        }
                        if (precedingBackslash) {
                            len--;
                        }
                        return len;
                    }
                }

                c = inCharBuf[inOff++];

                if (skipLF) {
                    skipLF = false;
                    if (c == '\n') {
                        continue;
                    }
                }
                if (skipWhiteSpace) {
                    if (c == ' ' || c == '\t' || c == '\f') {
                        continue;
                    }
                    if (!appendedLineBegin && (c == '\r' || c == '\n')) {
                        continue;
                    }
                    skipWhiteSpace = false;
                    appendedLineBegin = false;
                }
                if (isNewLine) {
                    isNewLine = false;
                    if (c == '#' || c == '!') {
                        isCommentLine = true;
                        continue;
                    }
                }

                if (c != '\n' && c != '\r') {
                    lineBuf[len++] = c;
                    if (len == line_cache) {
                        int newLength = line_cache * 2;
                        if (newLength < 0) {
                            newLength = INT32_MAX;
                        }
                        char* buf = new char[newLength];
                        memcpy(buf, lineBuf, line_cache);
                        delete[]lineBuf;
                        lineBuf = buf;
                    }
                    //flip the preceding backslash flag
                    if (c == '\\') {
                        precedingBackslash = !precedingBackslash;
                    } else {
                        precedingBackslash = false;
                    }
                } else {
                    // reached EOL
                    if (isCommentLine || len == 0) {
                        isCommentLine = false;
                        isNewLine = true;
                        skipWhiteSpace = true;
                        len = 0;
                        continue;
                    }
                    if (inOff >= inLimit) {
                        inStream->read(inCharBuf, char_cache);
                        inLimit = inStream->gcount();
                        inOff = 0;
                        if (inLimit <= 0) {
                            if (precedingBackslash) {
                                len--;
                            }
                            return len;
                        }
                    }
                    if (precedingBackslash) {
                        len -= 1;
                        //skip the leading whitespace characters in following line
                        skipWhiteSpace = true;
                        appendedLineBegin = true;
                        precedingBackslash = false;
                        if (c == '\r') {
                            skipLF = true;
                        }
                    } else {
                        return len;
                    }
                }
            }
        }
    };


    class ConfigHandler : public ConfigReader, public ConfigWriter {
    protected:
    public :

        void read(const std::string& file, std::map<std::string, std::string>& M) throw(DiffusionException) {
            std::ifstream in(file);
            if (!in.is_open()) {
                throw DiffusionException(ERROR_FILE_OPEN);
            }
            read(in, M);
        }

        void read(std::istream& in, std::map<std::string, std::string>& M) throw(DiffusionException) {
            LineReader reader(in);
            load(reader, M);
        }

        void write(const std::string& file, std::map<std::string, std::string>& M) throw(DiffusionException) {
            std::ofstream in(file);
            write(in, M);
        }

        void write(std::ostream& out, std::map<std::string, std::string>& M) throw(DiffusionException) {
            store(out, M, EMPTY_STRING, true);
        }

        void write(std::ostream& out, const std::string& comments) throw(DiffusionException) {
            writeComments(out, comments);
        }

    protected:
        //----------------------------------------------------------------------------------------------
        void writeComments(std::ostream& out, const std::string& comments)throw(DiffusionException) {
            out.put('#');
            int len = comments.length();
            int current = 0;
            int last = 0;
            char uu[6];
            uu[0] = '\\';
            uu[1] = 'u';
            while (current < len) {
                char c = comments.at(current);
                if (c > '\u00ff' || c == '\n' || c == '\r') {
                    if (last != current) {
                        const std::string& sub = comments.substr(last, current);
                        out.write(sub.c_str(), sub.size());
                    }
                    if (c > '\u00ff') {
                        uu[2] = toHex((c >> 12) & 0xf);
                        uu[3] = toHex((c >> 8) & 0xf);
                        uu[4] = toHex((c >> 4) & 0xf);
                        uu[5] = toHex(c & 0xf);
                        out.write(uu, 6);
                    } else {
                        write_str(out, NEW_LINE);
                        if (c == '\r' &&
                            current != len - 1 &&
                            comments.at(current + 1) == '\n') {
                            current++;
                        }
                        if (current == len - 1 ||
                            (comments.at(current + 1) != '#' &&
                             comments.at(current + 1) != '!'))
                            out.put('#');
                    }
                    last = current + 1;
                }
                current++;
            }
            if (last != current) {
                write_str(out, comments.substr(last, current));
            }
            write_str(out, NEW_LINE);
        }

        void load(LineReader& lr, std::map<std::string, std::string>& M) throw(DiffusionException) {
            const int buf_size = 1024;
            char* buf = new char[buf_size];
            int limit;
            int keyLen;
            int valueStart;
            char c;
            bool hasSep;
            bool precedingBackslash;

            while ((limit = lr.readLine()) >= 0) {
                c = 0;
                keyLen = 0;
                valueStart = limit;
                hasSep = false;

                precedingBackslash = false;
                while (keyLen < limit) {
                    c = lr.lineBuf[keyLen];
                    //need check if escaped.
                    if ((c == '=' || c == ':') && !precedingBackslash) {
                        valueStart = keyLen + 1;
                        hasSep = true;
                        break;
                    } else if ((c == ' ' || c == '\t' || c == '\f') && !precedingBackslash) {
                        valueStart = keyLen + 1;
                        break;
                    }
                    if (c == '\\') {
                        precedingBackslash = !precedingBackslash;
                    } else {
                        precedingBackslash = false;
                    }
                    keyLen++;
                }
                while (valueStart < limit) {
                    c = lr.lineBuf[valueStart];
                    if (c != ' ' && c != '\t' && c != '\f') {
                        if (!hasSep && (c == '=' || c == ':')) {
                            hasSep = true;
                        } else {
                            break;
                        }
                    }
                    valueStart++;
                }
                std::string key = loadConvert(lr.lineBuf, 0, keyLen, buf, buf_size);
                std::string value = loadConvert(lr.lineBuf, valueStart, limit - valueStart, buf, buf_size);
                M[key] = value;
            }
            delete[](buf);
        }

        void store(std::ostream& out, std::map<std::string, std::string>& M, const std::string& comments,
                   bool escUnicode)throw(DiffusionException) {
            if (comments != EMPTY_STRING) {
                writeComments(out, comments);
            }
            std::map<std::string, std::string>::iterator it = M.begin();
            while (it != M.end()) {
                std::string key = (it->first);
                std::string& val = (it->second);
                key = saveConvert(key, true, escUnicode);
                val = saveConvert(val, false, escUnicode);
                std::string buf = key + "=" + val;
                out.write(buf.c_str(), buf.length());
                out.put('#');
            }
        }


        std::string loadConvert(char in[], int off, int len, char buf[], int buf_len) {
            if (buf_len < len) {
                int newLen = len * 2;
                if (newLen < 0) {
                    newLen = INT32_MAX;
                }
                delete[](buf);
                buf = new char[newLen];
            }
            char aChar;
            char* out = buf;
            int outLen = 0;
            int end = off + len;

            while (off < end) {
                aChar = in[off++];
                if (aChar == '\\') {
                    aChar = in[off++];
                    if (aChar == 'u') {
                        // Read the xxxx
                        int value = 0;
                        for (int i = 0; i < 4; i++) {
                            aChar = in[off++];
                            switch (aChar) {
                                case '0':
                                case '1':
                                case '2':
                                case '3':
                                case '4':
                                case '5':
                                case '6':
                                case '7':
                                case '8':
                                case '9':
                                    value = (value << 4) + aChar - '0';
                                    break;
                                case 'a':
                                case 'b':
                                case 'c':
                                case 'd':
                                case 'e':
                                case 'f':
                                    value = (value << 4) + 10 + aChar - 'a';
                                    break;
                                case 'A':
                                case 'B':
                                case 'C':
                                case 'D':
                                case 'E':
                                case 'F':
                                    value = (value << 4) + 10 + aChar - 'A';
                                    break;
                                default:
                                    throw DiffusionException("Malformed \\uxxxx encoding.");
                            }
                        }
                        out[outLen++] = (char) value;
                    } else {
                        if (aChar == 't') aChar = '\t';
                        else if (aChar == 'r') aChar = '\r';
                        else if (aChar == 'n') aChar = '\n';
                        else if (aChar == 'f') aChar = '\f';
                        out[outLen++] = aChar;
                    }
                } else {
                    out[outLen++] = aChar;
                }
            }
            return std::string(out, outLen);
        }

        std::string saveConvert(const std::string& theString,
                                bool escapeSpace,
                                bool escapeUnicode) {
            int len = theString.length();
            std::string outBuffer;

            for (int x = 0; x < len; x++) {
                char aChar = theString.at(x);
                // Handle common case first, selecting largest block that
                // avoids the specials below
                if ((aChar > 61) && (aChar < 127)) {
                    if (aChar == '\\') {
                        outBuffer.push_back('\\');
                        outBuffer.push_back('\\');
                        continue;
                    }
                    outBuffer.push_back(aChar);
                    continue;
                }
                switch (aChar) {
                    case ' ':
                        if (x == 0 || escapeSpace)
                            outBuffer.push_back('\\');
                        outBuffer.push_back(' ');
                        break;
                    case '\t':
                        outBuffer.push_back('\\');
                        outBuffer.push_back('t');
                        break;
                    case '\n':
                        outBuffer.push_back('\\');
                        outBuffer.push_back('n');
                        break;
                    case '\r':
                        outBuffer.push_back('\\');
                        outBuffer.push_back('r');
                        break;
                    case '\f':
                        outBuffer.push_back('\\');
                        outBuffer.push_back('f');
                        break;
                    case '=': // Fall through
                    case ':': // Fall through
                    case '#': // Fall through
                    case '!':
                        outBuffer.push_back('\\');
                        outBuffer.push_back(aChar);
                        break;
                    default:
                        if (((aChar < 0x0020) || (aChar > 0x007e)) & escapeUnicode) {
                            outBuffer.push_back('\\');
                            outBuffer.push_back('u');
                            outBuffer.push_back(toHex((aChar >> 12) & 0xF));
                            outBuffer.push_back(toHex((aChar >> 8) & 0xF));
                            outBuffer.push_back(toHex((aChar >> 4) & 0xF));
                            outBuffer.push_back(toHex(aChar & 0xF));
                        } else {
                            outBuffer.push_back(aChar);
                        }
                }
            }
            return outBuffer;
        }

        constexpr static const char* hexDigit = "0123456789ABCDEF";

        static char toHex(int nibble) {
            return hexDigit[(nibble & 0xF)];
        }

        static void write_str(std::ostream& out, const std::string& value) {
            out.write(value.c_str(), value.length());
        }
    };
}

#endif //DIFFUSION_PROPERTIES_H
