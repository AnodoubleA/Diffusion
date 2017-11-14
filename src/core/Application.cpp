//
// Created by Alice on 2017.03.07.
//


#include <string>
#include <thread>
#include "../mvc/console/ConsoleActivity.h"
#include "../mvc/console/text_csl_activity.h"
#include "../mvc/console/file_csl_activity.h"
#include "../mvc/console/main_csl_activity.h"
#include "../module/i18n/i18ns.h"
#include "Application.h"
#include "../module/config/def_config.h"
#include "../module/config/ini_config.h"
#include "static_init.h"
#include "../mvc/console/winconsole.h"
#include "../module/config/configure.h"

using namespace std;
namespace lc{
    static const string version = "1.2.1";
    static const string title = "Diffusion cipher [" + version + "] - by Nodouble";
    static const string ini_name = "diffusion.ini";
    static MainConsoleActivity* main;
    static TextConsoleActivity* textConsole;
    static FileConsoleActivity* fileConsole;
    Internationalization* I18N;
    TypeConfig* config = new IniConfig();
    Console* console = new WinConsole();

    static const string copyright = "Diffusion cipher [" + version + "]\n(c) 2017 All right reserved.";


    void Application::initialize() {
        char buf[MAX_PATH];
        getcwd(buf, MAX_PATH);
        apppath = buf;
        main = new MainConsoleActivity(*console);
        main->initialize();
        textConsole = new TextConsoleActivity(*console);
        fileConsole = new FileConsoleActivity(*console);
        main->regist("text", *textConsole);
        main->regist("file", *fileConsole);
        DefaultConfig* dc = new DefaultConfig();
        dc->load(EMPTY_STRING);
        config->load(apppath + (char) FILE_SEPARATOR + ini_name, dc);
        Configure::config(*config);
        textConsole->read(config->get(DEF_CMD_TEXT));
        fileConsole->read(config->get(DEF_CMD_FILE));
        console->setTitle(title);
    }

    void Application::startup() {
        new std::thread([]() {
            init_consoles();
            init_formatter();
            init_seedFactory();
        });
        *console << (copyright);
        *console << "\n\n";
        string hello = config->get(KEY_START_HELLO);
        hello.append(hello.length() > 0 ? "\n" : "");
        console->out(hello, Color::THIN_SH_GREEN);
        string command = config->get(KEY_START_CMD);
        main->handle(command);
    }
}
