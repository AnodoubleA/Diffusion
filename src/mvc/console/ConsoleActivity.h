//
// Created by Alice on 2017.02.27.
//
#pragma once
#ifndef DIFFUSION_CONSOLEACTIVITY_H
#define DIFFUSION_CONSOLEACTIVITY_H

#include <iostream>
#include "../../core/DiffusionException.h"
#include "../activity/Activity.h"
#include "../../tool/Streams.h"
#include "../../core/chars.h"
#include "../cmd/StandardInvoker.h"
#include "../../module/i18n/i18N.h"
#include "../../tool/validator.h"
#include "../../tool/funs.h"
#include "console.h"

namespace lc{
    void init_consoles();

    namespace csl{
        extern std::map<std::string, std::string> MM;
        extern Invoker* static_invoker;
    }

    using namespace csl;

    class ConsoleActivity : public Activity {
    private:
        Invoker* invoker;
    protected:
        typedef std::map<std::string, std::string>::iterator Iterator;
        std::map<std::string, ConsoleActivity*> nodes;
        std::map<std::string, std::string> M;
        Console& console;
        int titleColor = Color::THIN_YELLOW;
    public:
        ConsoleActivity(Console& console) : console(console) {
            setNotification(getNotification());
            setInvoker(*csl::static_invoker);
        }

        virtual Option& handle(std::string& command) {
            int offset = 0, length = command.length();
            hendle(command, offset, length);
        }


        bool read(const std::string& command) {
            int offset = 0, length = command.length();
            read(const_cast<std::string&>(command), offset, length);
        }

        void regist(std::string name, ConsoleActivity& resolver) {
            nodes[name] = &resolver;
            Activity::regist(resolver);
        }

    protected:
        virtual void initialize() throw(DiffusionException) {

        }

        void setInvoker(Invoker& invoker) {
            this->invoker = &invoker;
        }

        void invoke(int code, Option* option) {
            invoke(getCommandFactory().make(code), option);
        }

        void invoke(Command* command, Option* option) {
            invoker->invoke(command, option);
        }

        virtual void error(std::exception& e) {
            console.lock();
            console << "\n";
            console.out(I18N->gf(TIP_ERROR, e.what()), Color::THIN_RED);
            console << "\n";
            console.unlock();
        }

        virtual bool tip(bool line) {
            if (line)console << "\n";
            console.out(getTipLine(), Color::THIN_VIOLET);
        }

        virtual Option& hendle(std::string& command, int& offset, int& length) {
            bool line = length > 0;
            while (true) {
                if (offset >= length) {
                    command.clear();
                    tip(line);
                    console.in(command);
                    offset = 0;
                    length = command.length();
                    line = length != 0;
                }
                if (!read(command, offset, length)) {
                    break;
                }
            }
        }

        bool read(std::string& command, int& offset, int& length) {
            std::string& buf = command;
            std::string get;
            while (offset < length) {
                try {
                    get.clear();
                    Strings::split(buf, get, offset, length, SPACE, csl::MM["-wp"][0]);
                    if (get == EMPTY_STRING) {
                        continue;
                    }
                    if (get == "exit") {
                        if (exit()) {
                            return false;
                        }
                        continue;
                    }
                    if (directive(get, buf, offset, length) > -1) {
                        continue;
                    }
                    ConsoleActivity* resolver = nodes[get];
                    if (resolver == nullptr) {
                        unknownCommand(get);
                        continue;
                    }
                    resolver->hendle(buf, offset, length);
                } catch (std::exception& e) {
                    error(e);
                }
            }
            return true;
        }

        virtual bool unknownCommand(std::string& cmd) {
            console.out(I18N->gf(TIP_CMD_UNKNOWN, cmd.c_str()), Color::THIN_YELLOW) << "\n";
        }

        virtual int directive(std::string direct, std::string& input, int& offset, int& length) {
            if (direct == "help") {
                return help();
            }
            return -1;
        }

        virtual bool help() {
            int color = console.getColor();
            console.setColor(titleColor);
            console << "\n";
            console << LINE_HEAD << I18N->get(TIP_LINE_HELP_NAME);
            console << TABLE_GAP << I18N->get(TIP_LINE_HELP_VALUE) << "\n";
            console.setColor(Color::THIN_GREEN);
            int width = console.getWindowSize(Console::WIDTH);
            Iterator it = M.begin();
            while (it != M.end()) {
                help(it, width);
                it++;
            }
            console.setColor(color);
            return true;
        }

        virtual bool help(Iterator it, int maxColumn) {
            console << LINE_HEAD << it->first;
            console << TABLE_GAP << I18N->get("help.ops." + it->first);
            console << "\n";
        }

        virtual bool exit()throw(DiffusionException) {
            return true;
        }

        virtual std::string getTipLine() = 0;
    };
}

#endif //DIFFUSION_CONSOLEACTIVITY_H
