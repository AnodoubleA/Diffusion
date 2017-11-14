//
// Created by Alice on 2017.03.14.
//

#ifndef DIFFUSION_SEED_SOURCE_H
#define DIFFUSION_SEED_SOURCE_H

#include <stdint-gcc.h>
#include <afxres.h>
#include "../../tool/tools.h"
#include "rd_box.h"
#include "../../tool/file_handler.h"

namespace lc{
    class SeedSource {
    public:
        virtual int pull(byte* buf, int& offset, int max) = 0;

        virtual float reliability() = 0;
    };

    class AbstractSeedSource : public SeedSource {
    protected:
        int64 getCurrentTime() {
            LARGE_INTEGER time;
            if (QueryPerformanceFrequency(&time)) {
                QueryPerformanceCounter(&time);
                return time.QuadPart;
            }
            return 0;
        }

        int write(byte* buf, int64 value, int byteCount, bool zero = false) {
            int index = 0;
            for (int i = 0; i < byteCount; i++) {
                byte v = (byte) (value >> (i * 8));
                if (zero || v > 0) {
                    buf[index++] = rd::S1[v] ^ rd::S2[v];
                }
            }
            return byteCount;
        }
    };

    class TimeSeedSource : public AbstractSeedSource {

    public:
        int pull(byte* buf, int& offset, int max) override {
            int64 seed = getCurrentTime();
            int count = write(buf + offset, seed, std::min(max - offset, 8));
            offset += count;
            count += write(buf + offset, GetTickCount(), std::min(max - offset, 8));
            offset += count;
            return count;
        }

        float reliability() override {
            return 0.7;
        }
    };

    class MemorySeedSource : public AbstractSeedSource {
        MEMORYSTATUS m;
    public:
        int pull(byte* buf, int& offset, int max) override {
            GlobalMemoryStatus(&m);
            int min = std::min(max - offset, 8);
            offset += write(buf + offset, m.dwAvailPageFile, min);
            min = std::min(max - offset, 8);
            offset += write(buf + offset, m.dwAvailPhys, min);
        }

        float reliability() override {
            return 0.9;
        }
    };

    class CPUSeedSource : public AbstractSeedSource {
        FILETIME idle;
        FILETIME kernel;
        FILETIME user;
    public:
        int pull(byte* buf, int& offset, int max) override {
            GetSystemTimes(&idle, &kernel, &user);
            int min = std::min(max - offset, 4);
            offset += write(buf + offset, idle.dwLowDateTime, min);
            min = std::min(max - offset, 4);
            offset += write(buf + offset, kernel.dwLowDateTime, min);
            min = std::min(max - offset, 4);
            offset += write(buf + offset, user.dwLowDateTime, min);
        }

        float reliability() override {
            return 0.8;
        }
    };

    class TempdirSeedSource : public AbstractSeedSource {
        char path[MAX_PATH];
    public:
        TempdirSeedSource() {
            GetTempPath(MAX_PATH, path);
        }

        int pull(byte* buf, int& offset, int max) override {
            foreach(path, buf, offset, max);
        }

        void foreach(char* path, byte* buf, int& offset, int max) {
            if (max - offset < 8) {
                return;
            }
            uint64 size = 0;
            int count = 0;
            int min = std::max(0, offset - 100);
            int files = buf[min] > 5 ? buf[min] : 5;
            FindCallback fn = [&](const std::string& parent, _finddata_t& data) {
                count++;
                size += data.size;
                if (buf[min++] > 128 && offset < max) {
                    int len = std::min((int) strlen(data.name), (max - offset));
                    memccpy(buf + offset, data.name, 1, len);
                    offset += len;
                }
                return files--;
            };
            FH::find_files(path, fn, nullptr, false);
            offset += write(buf + offset, size, std::min(8, max - offset));
            offset += write(buf + offset, count, std::min(4, max - offset));
        }

        float reliability() override {
            return 0.7;
        }

    };
}
#endif //DIFFUSION_SEED_SOURCE_H
