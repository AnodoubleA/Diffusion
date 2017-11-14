//
// Created by Angel on 2017/4/2.
//

#ifndef TEST_LEVELS_H
#define TEST_LEVELS_H

#include "level.h"
#include "../../core/chars.h"

namespace lc{
    class LinkLevel : public Level {
    protected:
        uint64 value = 0;
        LinkLevel* _next_ = nullptr;
        std::string flag;
    public:
        LinkLevel(uint64 value, const std::string& flag) : value(value), flag(flag) {}

        virtual Level* link(uint64 value, const std::string& flag) {
            LinkLevel* _next_ = new LinkLevel(value, flag);
            _next_->_next_ = this;
            return _next_;
        }

        Level* next() {
            return _next_;
        }

        virtual bool format(LevelContext& context) {
            uint64& number = context.number;
            std::string& options = context.options;
            uint64 div = number / value;
            int pos = options.find(flag);
            if (pos != -1) {
                char buf[16];
                std::string format = "%0" + std::to_string(flag.length()) + "llu";
                sprintf(buf, format.c_str(), div);
                options.replace(pos, flag.length(), buf);
                number %= value;
            }
            return true;
        }

        static Level* find(LinkLevel* start, LevelContext& context) {
            LinkLevel* next = start;
            while (next != nullptr) {
                if (context.options.find(next->flag) != -1) {
                    return next;
                }
                next = (LinkLevel*) next->next();
            }
            return nullptr;
        }
    };

    class SimpleLevel : public LinkLevel {
    protected:
        std::string unit;
    public:
        SimpleLevel(uint64 value, const std::string& flag, const std::string& unit) : LinkLevel(value, flag), unit(unit) {}

        virtual SimpleLevel* link(uint64 value, const std::string& flag, const std::string& unit) {
            SimpleLevel* _next_ = new SimpleLevel(value, flag, unit);
            _next_->_next_ = this;
            return _next_;
        }

        virtual Level* init(LevelContext& context) override {
            if (context.options == EMPTY_STRING) return this;
            Level* target = SimpleLevel::find(this, context);
            if (target) {
                context.target = target;
                return target;
            }
            return this;
        }

        virtual bool format(LevelContext& context) {
            uint64& number = context.number;
            std::string options = context.options;
            double ret = 1.0 * number / value;
            int pos = (int) options.find(flag);
            if ((context.target == this) || (ret >= 1 && _next_ == nullptr)) {
                if (options == EMPTY_STRING) {
                    options = "%.1f(" + unit + ")";
                } else if (pos == -1) {
                    options += "(" + unit + ")";
                } else {
                    options.replace(pos, flag.length(), EMPTY_STRING);
                }
                char buf[options.size() + 30];
                sprintf(buf, options.c_str(), ret);
                options.clear();
                options.append(buf);
                return false;
            }
            return true;
        }
    };
}
#endif //TEST_LEVELS_H
