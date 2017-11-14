//
// Created by Alice on 2017.02.23.
//
#pragma once
#ifndef DIFFUSION_NOTIFYEVENT_H
#define DIFFUSION_NOTIFYEVENT_H

#include <string>
#include <stdexcept>
#include "../../core/Object.h"
#include "../../core/DiffusionException.h"

namespace lc{
    class NotifyEvent : public Object {
    private:
        static const char LIMIT_CHAR = '$';
        bool consumed = false;
        bool stopImmediatePropagationed = false;
        bool stopPropagationed = false;
        std::string name;
        void* attachment = nullptr;
        bool limit = false;

    public:
        NotifyEvent(const std::string& name, void* attachment = nullptr) throw(DiffusionException) {
            if (name.length() == 0) {
                throw DiffusionException("Name cannot be empty");
            }
            limit = (name[0] == LIMIT_CHAR);
            if (limit) {
                this->name = name.substr(1);
            } else {
                this->name = name;
            }
            this->attachment = attachment;
        }

        /**
         * Test this event was {@link #consume()} called.
         *
         * @return
         */
        bool isConsumed() {
            return consumed;
        }

        /**
         * Prevent event default behaviour.
         */
        void consume() {
            consumed = true;
        }

        bool isStopImmediatePropagationed() {
            return stopImmediatePropagationed;
        }

        bool isStopPropagationed() {
            return stopPropagationed;
        }

        void stopImmediatePropagation() {
            stopImmediatePropagationed = true;
            stopPropagation();
        }

        void stopPropagation() {
            stopPropagationed = true;
        }

        const std::string& getName() {
            return name;
        }

        void setAttachment(void* attachment) {
            this->attachment = attachment;
        }

        void* getAttachment() {
            return attachment;
        }

        bool isLimited() {
            return limit;
        }
    };
}

#endif //DIFFUSION_NOTIFYEVENT_H
