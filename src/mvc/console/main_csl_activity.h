//
// Created by Angel on 2017/3/25.
//

#ifndef DIFFUSION_MAIN_CONSOLE_H
#define DIFFUSION_MAIN_CONSOLE_H

#include "ConsoleActivity.h"

namespace lc{
    class MainConsoleActivity : public ConsoleActivity {
    public:
        MainConsoleActivity(Console& console) : ConsoleActivity(console) {}

        void initialize() throw(DiffusionException) {
            ConsoleActivity::initialize();
            addNotifier("*.error", &notifier_error);
            M["text"];
            M["file"];
            M["help"];
            M["exit"];
        }

    protected:
        std::string getTipLine() {
            return I18N->get(TIP_LINE_MAIN);
        }

        Notifier notifier_error = [this](NotifyEvent& event) {
            std::exception* e = (std::exception*) event.getAttachment();
            error(*e);
        };
    };
}
#endif //DIFFUSION_MAIN_CONSOLE_H
