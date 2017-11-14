//
// Created by Alice on 2017.02.23.
//
#pragma once
#ifndef DIFFUSION_EFFAIRS_H
#define DIFFUSION_EFFAIRS_H

#include <list>
#include "../../core/Object.h"
#include "../../core/DiffusionException.h"
#include "../notify/HashClassifyNotification.h"
#include "../cmd/Invoker.h"

namespace lc{
    /**
     * External affairs, affairs for UI, console.
     */
    class Activity : public Object {
    private:
        ClassifyNotification* Notification;

    protected:
        std::list<Activity*> content;

        virtual void initialize() throw(DiffusionException) = 0;

        void setNotification(ClassifyNotification& notification) {
            this->Notification = &notification;
        }


        void regist(Activity& element) {
            element.initialize();
            content.push_back(&element);
        }

        void addNotifier(const std::string& name, Notifier* notifier) {
            Notification->addNotifier(name, notifier);
        }

        void notify(NotifyEvent* event) {
            Notification->notify(*event);
            delete (event);
        }

        void notify(const std::string& name, Object* attachment = nullptr) {
            notify(new NotifyEvent(name, attachment));
        }

    };

}

#endif //DIFFUSION_EFFAIRS_H
