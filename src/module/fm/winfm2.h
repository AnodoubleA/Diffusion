////
//// Created by Angel on 2017/3/30.
////
//
//#ifndef DIFFUSION_FM_IMPL_H
//#define DIFFUSION_FM_IMPL_H
//
//#include <thread>
//#include <mutex>
//#include "filemapping.h"
//
//#include "../../cipher/reusable.h"
//
//namespace lc{
//
//    class WinFileMapping : public FileMapping, public AbstractReusable {
//        std::string file;
//        HANDLE h_file = NULL;
//        HANDLE h_map = NULL;
//        LARGE_INTEGER offset;
//        uint64 size_rel = 0;
//        uint64 size_map = 0;
//        int access = 0;
//        std::thread* worker = nullptr;
//        std::mutex metux;
//    public:
//
//
//        void* getHandle(const char* file, int access, int openMode) {
//            this->access = access;
//            int _access = 0;
//            _access |= contains(access, READ) ? GENERIC_READ : 0;
//            _access |= contains(access, WRITE) ? GENERIC_WRITE : 0;
//            int mode = 0;
//            mode |= contains(openMode, OPEN) ? OPEN_EXISTING : 0;
//            mode |= contains(openMode, CREATE) ? CREATE_ALWAYS : 0;
//            return CreateFile(file, _access, 0, NULL, mode, FILE_ATTRIBUTE_NORMAL, NULL);
//        }
//
//
//        uint64 init(const std::string& file, int openMode, int access) {
//            this->file = file;
//            h_file = getHandle(file.c_str(), access, openMode);
//            if (h_file == INVALID_HANDLE_VALUE) {
//                close();
//                throw DiffusionException(I18N->gf(ERROR_FILE_OPEN, file.c_str()));
//            }
//            return (size_rel = GetFileSize(h_file, NULL));
//        }
//
//        bool make(uint64 length = 0, void* handle = nullptr) {
//            size_map = length == 0 ? size_rel : length;
//            int _access = contains(access, WRITE) ? PAGE_READWRITE : PAGE_READONLY;
//            h_map = CreateFileMapping(h_file, NULL, _access, length >> 32 & _F8_, length & _F8_, NULL);
//            if (h_map == NULL) {
//                close(size_rel);
//                throw DiffusionException(I18N->gf(ERROR_FILE_READ, file.c_str()));
//            }
//            return h_map != NULL;
//        }
//
//
//        byte* map(uint64 start, uint64 length, int options, byte* accept = nullptr)throw(DiffusionException) {
//            int _access = 0;
//            _access |= contains(options, READ) ? FILE_MAP_READ : 0;
//            _access |= contains(options, WRITE) ? FILE_MAP_WRITE : 0;
//            PVOID last = MapViewOfFile(h_map, _access, start >> 32 & _F8_, start & _F8_, length);
//            if (last == NULL) {
//                close(size_rel);
//                throw DiffusionException(I18N->gf(ERROR_FILE_READ, file.c_str()));
//            }
//            offset.QuadPart = start;
//            return (byte*) last;
//        }
//
//        bool flush(byte* address, uint64 size) override {
//
//            return (bool) FlushViewOfFile(address, size);
//        }
//
//        void unmap(byte* address = nullptr) {
//
//            UnmapViewOfFile(address);
//        }
//
//        void close(int64 length = -1, const char* rename = nullptr) {
//            metux.lock();
//            unlock();
//            close0(length, rename);
//        }
//
//        void close0(int64& length, const char* rename = nullptr) {
//            worker = new std::thread([length, rename, this]() {
//                if (h_map != nullptr) {
//                    CloseHandle(h_map);
//                }
//                if (length > 0) {
//                    LARGE_INTEGER offset;
//                    offset.QuadPart = length;
//                    SetFilePointerEx(h_file, offset, NULL, FILE_BEGIN);
//                    SetEndOfFile(h_file);
//                }
//                if (h_file != nullptr) {
//                    CloseHandle(h_file);
//                }
//                if (rename != nullptr) {
//                    std::rename(file.c_str(), rename);
//                }
//                h_map = nullptr;
//                h_file = nullptr;
//                metux.unlock();
//            });
//            worker = nullptr;
//        }
//
//        bool lock() override {
//            return AbstractReusable::lock();
//        }
//
//        void unlock() override {
//            AbstractReusable::unlock();
//        }
//    };
//}
//#endif //DIFFUSION_FM_IMPL_H
