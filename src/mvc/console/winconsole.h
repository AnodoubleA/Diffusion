//
// Created by Angel on 2017/4/7.
//

#ifndef DIFFUSION_WINCONSOLE_H
#define DIFFUSION_WINCONSOLE_H

#include <ntdef.h>
#include <processenv.h>
#include <rpc.h>
#include <iostream>
#include <mutex>
#include "console.h"
#include "../../tool/Streams.h"
#include "../../core/types.h"

namespace lc{
    class WinConsole : public Console {
        HANDLE handle;
        int color = Color::WHILE;
        std::istream& _in = std::cin;
        std::ostream& _out = std::cout;
        std::mutex LOCK;
    public:
        WinConsole() {
            handle = GetStdHandle(STD_OUTPUT_HANDLE);
        }

        std::istream& in() override {
            return _in;
        }

        std::ostream& out() override {
            return _out;
        }

        bool lock() override {
            LOCK.lock();
            return true;
        }

        bool unlock() override {
            LOCK.unlock();
            return true;
        }

        void setColor(int color) override {
            SetConsoleTextAttribute(handle, color);
        }

        int getColor() override {
            return color;
        }

        Coord getCoord() override {
            CONSOLE_SCREEN_BUFFER_INFO info;
            GetConsoleScreenBufferInfo(handle, &info);
            return Coord(info.dwCursorPosition.X, info.dwCursorPosition.Y);
        }

        void setCoord(const Coord& coord) override {
            COORD point = {(SHORT) coord.x, (SHORT) coord.y};
            SetConsoleCursorPosition(handle, point);
        }

        uint64 getWindowSize(int witch) override {
            CONSOLE_SCREEN_BUFFER_INFO info;
            GetConsoleScreenBufferInfo(handle, &info);
            if (witch == WIDTH) {
                return info.srWindow.Right;
            }
            if (witch == HEIGHT) {
                return info.srWindow.Bottom;
            }
            return (uint64) info.srWindow.Right << 32 | info.srWindow.Bottom;
        }

        void setCursorVisible(bool visible) {
            CONSOLE_CURSOR_INFO info;
            GetConsoleCursorInfo(handle, &info);
            info.bVisible = visible;
            SetConsoleCursorInfo(handle, &info);
        }

//        void computeSize(const std::string& message, int& width, int& height) override {
//            SIZE size;
//            HDC dc = GetDC(NULL);
//            GetTextExtentPoint32(dc, message.c_str(), message.length(), &size);
//            width = size.cx;
//            height = size.cy;
//        }

        void setTitle(const std::string& title) {
            SetConsoleTitle(title.c_str());
        }

        Console& out(const std::string& message, int color, bool recover = true) override {
            int oldColor = getColor();
            setColor(color);
            Console::out(message);
            if (recover)setColor(oldColor);
            return *this;
        }

        void in(std::string& accept, char flag) override {
            Streams::read(_in, accept, flag);
        }
    };
}
#endif //DIFFUSION_WINCONSOLE_H
