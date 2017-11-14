//
// Created by Angel on 2017/4/13.
//

#ifndef DIFFUSION_CIPHER_ACTIVITY_H
#define DIFFUSION_CIPHER_ACTIVITY_H

#define ENCIP "enc"
#define DECIP "dec"

#include "ConsoleActivity.h"
#include "command_csl_activity.h"

namespace lc{
    class CipherConsoleActivity : public CommandConsoleActivity {
    public:
        CipherConsoleActivity(Console& console) : CommandConsoleActivity(console) {
            //@formatter:off
            M["-l"]         = "1";
            M["-s"]         = "1024";
            M["-i"]         = EMPTY_STRING;
            M["-k"]         = EMPTY_STRING;
            M["-kf"]        = "plain";
            M["-kfl"]       = NON;
            M[ENCIP]        = EMPTY_STRING;
            M[DECIP]        = EMPTY_STRING;
            M["vd"]         = EMPTY_STRING;
            //@formatter:on
        }

    protected:
        virtual int directive(std::string direct, std::string& command, int& offset, int& length) {
            int ret = CommandConsoleActivity::directive(direct, command, offset, length);
            if (direct == ENCIP) {
                return execute(nullptr, CO::ENCIPHER);
            }
            if (direct == DECIP) {
                return execute(nullptr, CO::DECIPHER);
            }
            if (Strings::match(direct, "vd[e|d]{0,1}")) {
                return direct_vd(direct, console);
            }
            return ret;
        }

        virtual bool direct_vd(std::string& direct, Console& console) {
            console << "\n";
            int code;
            if (direct.length() == 2) {
                code = CO::ENCIPHER;
            } else {
                code = direct.at(2) == 'e' ? CO::ENCIPHER : CO::DECIPHER;
            }
            int ret = T::checkValidator(console, validate(code));
            if (!contains_any(ret, vdr::INVALID | vdr::WARNING)) {
                console.out(I18N->get(VDR_GOOD), Color::THIN_GREEN);
                console << "\n";
            }
            return true;
        }

        virtual bool show() override {
            CommandConsoleActivity::show();
            int color = console.getColor();
            int width = console.getWindowSize(Console::WIDTH);
            console.setColor(Color::THIN_SH_GREEN);
            Iterator it = MM.begin();
            while (it != MM.end()) {
                CommandConsoleActivity::show(it, width);
                it++;
            }
            console.setColor(color);
        }

        virtual bool help() override {
            ConsoleActivity::help();
            int color = console.getColor();
            int width = console.getWindowSize(Console::WIDTH);
            console.setColor(Color::THIN_SH_GREEN);
            Iterator it = MM.begin();
            while (it != MM.end()) {
                CommandConsoleActivity::help(it, width);
                it++;
            }
            console.setColor(color);
        }

        virtual Validator* validate(int code) {
            Validator* vr = new Validator();
            bool encip = code == FO::ENCIPHER;
            std::string& s_lv = M["-l"];
            if (!(Strings::match(s_lv, "^[0-9]+$"))) {
                vr = vr->append(vdr::INVALID, I18N->gf(VDR_LEVEL_NAN, s_lv.c_str()));
            } else {
                int lv = atoi(s_lv.c_str());
                if (lv < MIN_KEY_LEVEL || lv > MAX_KEY_LEVEL) {
                    vr = vr->append(vdr::INVALID, I18N->gf(VDR_LEVEL_OOR, MIN_KEY_LEVEL, MAX_KEY_LEVEL, lv));
                }
            }
            if (!Strings::match(M["-kf"], "(hex|base64|plain)")) {
                vr = vr->append(vdr::INVALID, I18N->gf(VDR_KF_INC, M["-kf"].c_str()));
            }
            std::string keyfile = M["-kfl"];
            int64 key_len = M["-k"].length();
            if (keyfile != NON) {
                bool isDir = false;
                int64 len = FH::find_file(keyfile, isDir);
                if (len == -1) {
                    vr = vr->append(vdr::INVALID, I18N->gf(VDR_KFL_NFD, keyfile.c_str()));
                } else if (isDir) {
                    vr = vr->append(vdr::INVALID, I18N->gf(VDR_KFL_INC, keyfile.c_str()));
                }
            } else if (key_len == 0) {
                vr = vr->append(vdr::INVALID, I18N->get(VDR_K_MISS));
            } else if (encip && key_len < MIN_KEY_LENGTH) {
                vr = vr->append(vdr::WARNING, I18N->gf(VDR_K_SHORT, MIN_KEY_LENGTH, key_len));
            }
            std::string& s_size = M["-s"];
            if (!(Strings::match(s_size, "[0-9]+"))) {
                vr = vr->append(vdr::INVALID, I18N->gf(VDR_N_NAN, s_size.c_str()));
            } else {
                vr = vr->append(T::validate_size(s_size, MIN_SIZE, MAX_SIZE));
            }
            return vr;
        }

        virtual bool execute(CipherOption* option, int code) throw(DiffusionException) {
            console.out("\n");
            int ret = T::checkValidator(console, validate(code));
            if (contains(ret, vdr::INVALID)) {
                return false;
            }
            if (contains_any(ret, vdr::WARNING_ANY)) {
                bool high = contains(ret, vdr::WARNING_HEIGH);
                console.out(I18N->get(high ? TIP_LINE_VD_WARNING_IMP : TIP_LINE_VD_WARNING), Color::THIN_YELLOW);
                std::string get;
                console.in(get);
                console.endl();
                if ((high) ? (get != "YES" && get != "yes") : (get != "y" && get != "Y")) {
                    return false;
                }
            }
            std::string& s_level = M["-l"];
            option->level = atoi(s_level.c_str());
            option->options |= code;
            option->size = atoi(M["-s"].c_str()) >> 3;
            option->keyfile = M["-kfl"];
            if (option->keyfile == NON) {
                option->key = Cvt::from_input(M["-k"], M["-kf"], option->key_size);
            }
            return true;
        }
    };
}
#endif //DIFFUSION_CIPHER_ACTIVITY_H
