//
// Created by Alice on 2017.03.16.
//

#ifndef DIFFUSION_TEXT_CONSOLE_H
#define DIFFUSION_TEXT_CONSOLE_H

#include "ConsoleActivity.h"
#include "../../module/cmds/options.h"
#include "../../tool/converter.h"
#include "../../module/cmds/cmds.h"
#include "cipher_csl_activity.h"

namespace lc{
    class TextConsoleActivity : public CipherConsoleActivity {
        constexpr static const char* PLAIN = "plain";
        constexpr static const char* BASE64 = "base64";
    public:
        TextConsoleActivity(Console& console) : CipherConsoleActivity(console) {
            //@formatter:off
            M["-i"]         = EMPTY_STRING;
            //@formatter:on
        }

        void initialize() throw(DiffusionException) {
            CipherConsoleActivity::initialize();
            addNotifier("*.text.end", &notifier_text_cipher_end);
        }

    protected:
        std::string getTipLine() {
            return I18N->get(TIP_LINE_TEXT);
        }

        Validator* validate(int code) {
            Validator* vr = CipherConsoleActivity::validate(code);
            if (isBlank(M["-i"])) {
                vr = vr->append(vdr::INVALID, I18N->get(VDR_TIN_MISS));
            }
            return vr;
        }

        bool execute(CipherOption* option, int code) throw(DiffusionException) {
            TextOption* op = new TextOption();
            if (CipherConsoleActivity::execute(op, code)) {
                bool encip = code == CO::ENCIPHER;
                std::string in = M["-i"];
                in = encip ? in : Strings::replaceAll(in, "\n", "");
                op->input = Cvt::from_input(in, encip ? PLAIN : BASE64, op->input_size);
                if (M["-ofl"] != NON) {
                    op->options |= TO::WRITE_IN_FILE;
                }
                invoke(encip ? cmd::TEXT_ENCIPHER : cmd::TEXT_DECIPHER, op);
            }
        }

        Notifier notifier_text_cipher_end = [this](NotifyEvent& event) {
            tip(false);
            console.out(I18N->get(CIPHER_TEXT_END), Color::THIN_SH_GREEN) << "\n\n";
            OutputContact& contact = *(OutputContact*) event.getAttachment();
            bool encip = contains(contact.options, CO::ENCIPHER);
            console.out(Cvt::to_output(contact.buffer, encip ? BASE64 : PLAIN, contact.length), Color::THIN_SH_GREEN);
            console << "\n";
        };
    };

}
#endif //DIFFUSION_TEXT_CONSOLE_H
