//
// Created by Angel on 2017/3/30.
//

#ifndef DIFFUSION_FM_IMPL_H
#define DIFFUSION_FM_IMPL_H

#include <thread>
#include <mutex>
#include <unistd.h>
#include <fcntl.h>
#include "filemapping.h"

#include "../../cipher/reusable.h"

namespace lc{

    class WinFileMapping : public FileMapping, public AbstractReusable {
        std::string file;
        HANDLE handle = NULL;
        uint64 size_rel = 0;
        uint64 size_map = 0;
        int access = 0;
        std::thread* worker = nullptr;
        std::mutex metux;
    public:


        void* getHandle(const char* file, int access, int openMode) {
            this->access = access;
            int _access = 0;
            _access |= contains(access, READ) ? GENERIC_READ : 0;
            _access |= contains(access, WRITE) ? GENERIC_WRITE : 0;
            int mode = 0;
            mode |= contains(openMode, OPEN) ? OPEN_EXISTING : 0;
            mode |= contains(openMode, CREATE) ? CREATE_ALWAYS : 0;
            return CreateFile(file, _access, 0, NULL, mode,
                              FILE_ATTRIBUTE_NORMAL | FILE_FLAG_NO_BUFFERING | FILE_FLAG_WRITE_THROUGH, NULL);
        }


        uint64 init(const std::string& file, int openMode, int access) {
            this->file = file;
            handle = getHandle(file.c_str(), access, openMode);
            if (handle == INVALID_HANDLE_VALUE) {
                deinit(0);
                throw DiffusionException(I18N->gf(ERROR_FILE_OPEN, file.c_str()));
            }
            return (size_rel = GetFileSize(handle, NULL));
        }

        bool make(uint64 length = 0, void* _handle = nullptr) {
            size_map = length == 0 ? size_rel : length;
            int _access = contains(access, WRITE) ? PAGE_READWRITE : PAGE_READONLY;
            HANDLE map = CreateFileMapping(handle, NULL, _access, length >> 32 & _F8_, length & _F8_, NULL);
            CloseHandle(handle);
            handle = map;
            if (handle == NULL) {
                deinit(size_rel);
                throw DiffusionException(I18N->gf(ERROR_FILE_READ, file.c_str()));
            }
            return handle != NULL;
        }


        byte* map(uint64 start, uint64 length, int options, byte* accept = nullptr)throw(DiffusionException) {
            int _access = 0;
            _access |= contains(options, READ) ? FILE_MAP_READ : 0;
            _access |= contains(options, WRITE) ? FILE_MAP_WRITE : 0;
            PVOID buf = MapViewOfFile(handle, _access, start >> 32 & _F8_, start & _F8_, length);
            if (buf == NULL) {
                deinit(size_rel);
                throw DiffusionException(I18N->gf(ERROR_FILE_READ, file.c_str()));
            }
            return (byte*) buf;
        }

        bool flush(byte* address, uint64 size) override {

            return (bool) FlushViewOfFile(address, size);
        }

        void unmap(byte* address = nullptr) {

            UnmapViewOfFile(address);
        }

        void deinit(int64 length = -1) {
            if (handle != nullptr) {
                CloseHandle(handle);
            }
            if (length > 0) {
                int fd = open(file.c_str(), O_WRONLY);
                ftruncate64(fd, length);
                close(fd);
            }
            handle = nullptr;
            unlock();
        }

        bool lock() override {
            return AbstractReusable::lock();
        }

        void unlock() override {
            AbstractReusable::unlock();
        }
    };
}
#endif //DIFFUSION_FM_IMPL_H
