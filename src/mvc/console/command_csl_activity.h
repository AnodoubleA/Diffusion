//
// Created by Alice on 2017.04.14.
//

#ifndef DIFFUSION_COMMAND_CSL_ACTIVITY_H
#define DIFFUSION_COMMAND_CSL_ACTIVITY_H

#define OPTION '-'

#include "ConsoleActivity.h"

namespace lc{
    class CommandConsoleActivity : public ConsoleActivity {
    public:
        CommandConsoleActivity(Console& console) : ConsoleActivity(console) {
            M["show"] = EMPTY_STRING;
        }

    protected:
        virtual int directive(std::string direct, std::string& input, int& offset, int& length) {
            int code = ConsoleActivity::directive(direct, input, offset, length);
            if (direct == "show") {
                return show();
            }
            if (direct[0] == OPTION) {
                return setOption(direct, input, offset, length);
            }
            return code;
        }

        virtual bool show() {
            int color = console.getColor();
            console.setColor(titleColor);
            console << "\n";
            console << LINE_HEAD << I18N->get(TIP_LINE_SHOW_NAME);
            console << TABLE_GAP << I18N->get(TIP_LINE_SHOW_VALUE) << "\n";
            console.setColor(Color::THIN_GREEN);
            int width = console.getWindowSize(Console::WIDTH);
            Iterator it = M.begin();
            while (it != M.end()) {
                show(it, width);
                it++;
            }
            console.setColor(color);
            return true;
        }

        virtual bool show(Iterator it, int maxColumn) {
            if (it->first.at(0) == OPTION) {
                console << LINE_HEAD << it->first;
                console << TABLE_GAP << it->second;
                console << "\n";
            }
        }

        virtual int setOption(std::string& name, std::string& input, int& offset, int& length) {
            std::string value;
            Strings::split(input, value, offset, length, SPACE, csl::MM["-wp"][0]);
            return setOption(name, value);
        }

        virtual int setOption(std::string& name, std::string& value) {
            Iterator it = M.find(name);
            if (name.at(0) == OPTION) {
                if (it != M.end()) {
                    M[name] = value;
                } else {
                    it = MM.find(name);
                    if (it != MM.end()) {
                        MM[name] = value;
                    } else {
                        console.out(I18N->gf(TIP_OPS_UNKNOWN, name.c_str()), Color::THIN_YELLOW);
                        console << "\n";
                    }
                }
            }
            return true;
        }

        virtual Validator* validate(int code) {
            return new Validator();
        }
    };
}
#endif //DIFFUSION_COMMAND_CSL_ACTIVITY_H
