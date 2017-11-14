//
// Created by Alice on 2017.02.23.
//
#pragma once
#ifndef DIFFUSION_NOTIFIER_H
#define DIFFUSION_NOTIFIER_H

#include <functional>
#include "NotifyEvent.h"
#include "../../core/Object.h"

namespace lc{
    typedef std::function<void(NotifyEvent& event)> Notifier;
//    class Notifier : public Object {
//
//    public:
//        virtual void action(NotifyEvent& event) = 0;
//    };
}
#endif //DIFFUSION_NOTIFIER_H
