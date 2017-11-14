//
// Created by Alice on 2017.02.23.
//
#pragma once
#ifndef DIFFUSION_CLASSIFYNOTIFICATION_H
#define DIFFUSION_CLASSIFYNOTIFICATION_H

#include "Notification.h"
#include "Notifier.h"

namespace lc{
    class ClassifyNotification : public Notification {

    public :
        virtual void addNotifier(const std::string& name, Notifier notifier) = 0;

        virtual void addNotifier(const std::string& name, Notifier* notifier) = 0;
    };
}

#endif //DIFFUSION_CLASSIFYNOTIFICATION_H
