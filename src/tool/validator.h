//
// Created by Alice on 2017.03.15.
//

#ifndef DIFFUSION_VALIDATOR_H
#define DIFFUSION_VALIDATOR_H

#include <string>
#include "../mvc/console/console.h"

namespace lc{
    typedef class Validator {
        int colorHighWarn = 206;
        int _code = VALID;
        std::string _message;
        Validator* _head = nullptr;
        Validator* _next = nullptr;
    public:
        ~Validator() {
            delete (_next);
        }

        static const int VALID = 1;
        static const int INVALID = 2;
        static const int WARNING = 4;
        static const int WARNING_HEIGH = 8;
        static const int WARNING_ANY = WARNING | WARNING_HEIGH;

        Validator() : Validator(VALID, EMPTY_STRING) {

        }

        Validator(const std::string& message) : Validator(INVALID, message) {

        };

        Validator(int code, const std::string& message) {
            this->_message = message;
            this->_code = code;
            this->_head = this;
        };

        const std::string& message() {
            return _message;
        }

        Validator* head() {
            return _head;
        }

        int code() {
            return _code;
        }

        int codes() {
            int code = _code;
            Validator* next = this->_next;
            while (next != nullptr) {
                code |= next->code();
                next = next->_next;
            }
            return code;
        }

        Validator* append(int mold, const std::string& message) {
            return append(new Validator(mold, message));
        }

        Validator* append(Validator* validator) {
            _next = validator;
            _next->_head = this->_head;
            return _next;
        }

        void print(Internationalization& i18N, Console& console) {
            bool beprint = contains_any(codes(), WARNING_ANY | INVALID);
            if (beprint) {
                Validator* next = this;
                while (next != nullptr) {
                    switch (next->code()) {
                        case INVALID:
                            console.out(i18N.get(VDR_TITLE_ERROR), Color::THIN_RED);
                            console.out(next->message(), Color::THIN_RED);
                            console.endl();
                            break;
                        case WARNING:
                            console.out(i18N.get(VDR_TITLE_WARNING), Color::THIN_YELLOW);
                            console.out(next->message(), Color::THIN_YELLOW);
                            console.endl();
                            break;
                        case WARNING_HEIGH:
                            console.out("\n");
                            console.out(i18N.get(VDR_TITLE_WARNING_IMP), colorHighWarn);
                            console.out(next->message(), colorHighWarn);
                            console.out("\n\n");
                            break;
                    }
                    next = next->_next;
                }
            }
        }

    } vdr;
}
#endif //DIFFUSION_VALIDATOR_H
