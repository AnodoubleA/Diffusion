//
// Created by Alice on 2017.03.09.
//
#pragma once
#ifndef DIFFUSION_FILEMAP_H
#define DIFFUSION_FILEMAP_H


#include <string>
#include "../../core/DiffusionException.h"
#include "../../core/types.h"
#include "../config/Config.h"
#include "../i18n/lang.h"
#include "../../cipher/reusable.h"


namespace lc{

    typedef class FileMapping : public Reusable {
    public:
        static const int OPEN = 1 << 0;
        static const int CREATE = 1 << 1;
        static const int READ = 1 << 16;
        static const int WRITE = 1 << 17;

        static int allocationGranularity() {
            SYSTEM_INFO info;
            GetSystemInfo(&info);
            return (int) info.dwAllocationGranularity;
        }

        virtual uint64 init(const std::string& file, int openMode, int access) = 0;

        virtual bool make(uint64 length = 0, void* handle = nullptr) = 0;

        virtual byte* map(uint64 start, uint64 length, int options, byte* address = nullptr) throw(DiffusionException)= 0;

        virtual void unmap(byte* pointer = nullptr)= 0;

        virtual bool flush(byte* address, uint64 size) = 0;

        virtual void deinit(int64 length = -1) = 0;
    } FM;
}
#endif //DIFFUSION_FILEMAP_H
