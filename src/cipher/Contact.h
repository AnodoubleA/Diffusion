//
// Created by Alice on 2017.03.03.
//
#pragma once
#ifndef DIFFUSION_MESSAGER_H
#define DIFFUSION_MESSAGER_H

#include <string>
#include "../core/types.h"

namespace lc{
    class Contact {

    };

    class SchedulerContact : public Contact {
    public:
        int fileCount = 0;
        int done = 0;
        int options = 0;
        int status = 0;
        uint64 time = 0;

        void addDone(int count) {
            this->done += count;
        }

        void addTime(uint64 time) {
            this->time += time;
        }
    };

    class BufferContact : public Contact {
    public:
        uint64 length = 0;
        uint64 done = 0;

        inline void addDone(uint64 size) {
            this->done += size;
        }
    };

    class OutputContact : public BufferContact {
    public:
        ~OutputContact() {
            delete[] (buffer);
        }

        int options = 0;
        byte* buffer = nullptr;
    };


}
#endif //DIFFUSION_MESSAGER_H
