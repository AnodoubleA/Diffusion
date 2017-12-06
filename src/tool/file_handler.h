//
// Created by Angel on 2017/4/2.
//

#ifndef DIFFUSION_FILE_HANDLER_H
#define DIFFUSION_FILE_HANDLER_H

#include <vector>
#include <list>
#include <string>
#include <io.h>
#include <fstream>
#include <functional>
#include <iostream>
#include "../module/cmds/options.h"
#include "../cipher/structs.h"
#include "../core/DiffusionException.h"
#include "../module/config/Config.h"
#include "../cipher/filter.h"
#include "../module/cipher/FileCipher.h"
#include "../cipher/items.h"
#include "converter.h"
#include "tools.h"

namespace lc{

    typedef std::function<Item*(std::string& parent, _finddata_t& data)> ItemCallback;
    typedef std::function<bool(std::string& parent, _finddata_t& data)> FindCallback;
    typedef class FileHandler {
    public:
        static int64 find_file(std::string path, bool& isdir) {
            if (path.length() == 0) {
                return -1;
            }
            _finddata_t data;
            if (path.at(path.length() - 1) == FILE_SEPARATOR) {
                path.erase(path.length() - 1, 1);
            }
            int handle = _findfirst(path.c_str(), &data);
            if (handle == -1) {
                return -1;
            }
            isdir = data.attrib == _A_SUBDIR;
            return data.size;
        }

        static void
        find_files(std::string path, FindCallback& call, Filter<_finddata_t&>* filter = nullptr, bool recursion = true) {
            _finddata_t data;
            std::string current = path + "/*";
            int handle = _findfirst(current.c_str(), &data);
            bool isdir;
            do {
                if (-1 == handle) {
                    return;
                }
                isdir = data.attrib == _A_SUBDIR;
                if (isdir) {
                    if (recursion && strcmp(data.name, "..") != 0 && strcmp(data.name, ".") != 0) {
                        find_files(path + (char) FILE_SEPARATOR + data.name, call, filter, recursion);
                    }
                } else {
                    if (filter == nullptr || filter->accept(data)) {
                        if (!call(path, data)) {
                            return;
                        }
                    }
                }
            } while (!_findnext(handle, &data));
            _findclose(handle);
        }

        static void
        to_items(std::string path, std::list<Item*>& ls, ItemCallback& fn, Filter<_finddata_t&>* filter = nullptr,
                 bool recursion = true) {
            _finddata_t data;
            std::string current = path;
            int handle = _findfirst(current.c_str(), &data);
            if (-1 == handle) {
                return;
            };
            if (data.attrib == _A_SUBDIR) {
                FindCallback callback = [&](std::string& parent, _finddata_t& data) {
                    ls.push_back(fn(parent, data));
                    return true;
                };
                find_files(path, callback, filter, recursion);
            } else {
                ls.push_back(fn(path, data));
            }
            _findclose(handle);
        }


        static byte* read_key(int size, int& length, std::string& file) throw(DiffusionException) {
            std::ifstream in(file);
            if (!in.is_open()) {
                throw DiffusionException(I18N->gf(ERROR_FILE_OPEN, file.c_str()));
            }
            byte* buf = new byte[size];
            try {
                in.seekg(0, std::ios::end);
                int len = in.tellg();
                int min = std::min(size, len);
                in.seekg(0);
                in.read((char*) buf, min);
                in.close();
                length = min;
                return buf;
            } catch (...) {
                delete (buf);
                in.close();
                throw DiffusionException(I18N->gf(ERROR_FILE_READ, file.c_str()));
            }
        }

        static std::string
        new_name(const std::string& path, std::string& fullName, int options, const char* extend, bool use = true) {
            std::string::size_type npos = std::string::npos;
            bool enc = contains(options, CipherOption::ENCIPHER);
            bool have = Strings::endWith(fullName, extend);
            int64 index = npos;
            if (enc && !have && use) {
                index = fullName.length();
                fullName += extend;
            } else if (!enc && have) {
                fullName = fullName.substr(0, fullName.length() - strlen(extend));
            }
            std::string file = path + (char) FILE_SEPARATOR + fullName;
            if (contains(options, FO::COVER)) {
                return file;
            }
            std::string name = fullName;
            std::string suffix;
            if (index != npos) {
                suffix = fullName.substr(index);
                name = fullName.substr(0, index);
            }
            index = name.find_last_of(".");
            if (index != npos) {
                suffix = name.substr(index) + suffix;
                name = name.substr(0, index);
            }
            int i = 1;
            std::string rename = name;
            if (Strings::match(name, ".*\\([0-9]+\\)$")) {
                name = name.substr(0, name.find_last_of("("));
            }
            file = path + (char) FILE_SEPARATOR + rename + suffix;
            while (access(file.c_str(), 0) != -1) {
                rename.clear();
                rename += (name + "(" + std::to_string(i++) + ")");
                file.clear();
                file.append(path + (char) FILE_SEPARATOR + rename + suffix);
            }
            return file;
        }

        static void compute_io(Item& item) {
            FileOption& op = *item.option;
            std::string dir;
            bool makedir = true;
            if (!contains(op.options, FO::DO_SOURCE)) {
                if (!op.isdir_in && !op.isdir_out) {
                    item.in_file = op.input;
                    item.out_file = op.output;
                    makedir = false;
                } else if (!op.isdir_in && op.isdir_out) {
                    item.in_file = op.input;
                    dir = op.output;
                } else {
                    item.in_file = item.in_parent + (char) FILE_SEPARATOR + item.in_name;
                    dir = op.output + item.in_parent.substr(op.input.length());
                }
                if (makedir) {
                    T::erase_remend(dir, FILE_SEPARATOR);
                    item.out_file = new_name(dir, item.in_name, op.options, EXTEND_FILE_NAME, USE_FILE_EXNAME);
                }
                if (makedir && make_dirs(dir) != 0) {
                    throw DiffusionException(I18N->gf(ERROR_DIR_CREATE, dir.c_str()));
                }
            } else {
                if (op.isdir_in) {
                    item.in_file = item.in_parent + (char) FILE_SEPARATOR + item.in_name;
                    item.out_file = item.in_file;
                } else {
                    item.in_file = op.input;
                    item.out_file = op.input;
                }
            }
        }
    } FH;
}
#endif //DIFFUSION_FILE_HANDLER_H
