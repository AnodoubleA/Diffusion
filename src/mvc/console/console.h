//
// Created by Angel on 2017/4/6.
//

#ifndef DIFFUSION_CONSOLE_H
#define DIFFUSION_CONSOLE_H

#include <string>

namespace lc{
    class Coord {
    public:
        int x = 0;
        int y = 0;

        Coord() {}

        Coord(int x, int y) : x(x), y(y) {}
    };

    class Color {
    public:
        //@formatter:off
        static const int BLACK          = 0;
        static const int BLUE           = 1;
        static const int GREEN          = 2;
        static const int SH_GREEN       = 3;
        static const int RED            = 4;
        static const int VIOLET         = 5;
        static const int YELLOW         = 6;
        static const int WHILE          = 7;
        static const int GRAY           = 8;
        static const int THIN_BLUE      = 9;
        static const int THIN_GREEN     = 10;
        static const int THIN_SH_GREEN  = 11;
        static const int THIN_RED       = 12;
        static const int THIN_VIOLET    = 13;
        static const int THIN_YELLOW    = 14;
        static const int LIEGHT_WHILE   = 15;
        //@formatter:off
        int color = 0;
    };

    class Console {
    public:
        static const int SIN = 1;
        static const int SOUT = 2;
        static const int WIDTH = 1;
        static const int HEIGHT = 2;
    public:
        virtual std::istream& in() = 0;

        virtual std::ostream& out() = 0;

        virtual bool lock() = 0;

        virtual bool unlock() = 0;

        virtual void setColor(int color) = 0;

        virtual int getColor() = 0;

        virtual Coord getCoord() = 0;

        virtual void setCoord(const Coord& coord) = 0;

        virtual uint64 getWindowSize(int witch) = 0;

        virtual void setTitle(const std::string& title) = 0;

        virtual void setCursorVisible(bool visible) = 0;

        virtual Console& out(const std::string& message) {
            out() << message;
            return *this;
        }

        virtual Console& out(uint64 number) {
            out() << number;
            return *this;
        }

        virtual Console& out(double number) {
            out() << number;
            return *this;
        }

        virtual Console& out(const std::string& message, int color, bool recover = true) = 0;

        virtual void in(std::string& accept, char flag = '*') = 0;

        virtual Console& clear(int witch, std::ios::iostate state = std::ios::goodbit) {
            if ((witch & SIN) == SIN) {
                in().clear(state);
            }
            if ((witch & SOUT) == SOUT) {
                out().clear(state);
            }
            return *this;
        }

        virtual Console& sync(int witch) {
            if ((witch & SIN) == SIN) {
                in().sync();
            }
            if ((witch & SOUT) == SOUT) {
                out().flush();
            }
            return *this;
        }

        virtual void endl() {
            out() << "\n";
            sync(SOUT);
        }


        virtual Console& operator<<(uint64 number) {
            out(number);
            return *this;
        }

        virtual Console& operator<<(double number) {
            out(number);
            return *this;
        }

        virtual Console& operator<<(const std::string& message) {
            out(message);
            return *this;
        }

    };
}
#endif //DIFFUSION_CONSOLE_H
