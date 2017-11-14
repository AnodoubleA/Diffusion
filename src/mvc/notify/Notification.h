//
// Created by Alice on 2017.02.23.
//
#pragma once
#ifndef DIFFUSION_NOTIFICATION_H
#define DIFFUSION_NOTIFICATION_H

#include "NotifyEvent.h"

namespace lc{
    class Notification : public Object {

    public:
        virtual void notify(NotifyEvent& event) = 0;
    };
}
#endif //DIFFUSION_NOTIFICATION_H
