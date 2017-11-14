//
// Created by Alice on 2017.03.03.
//
#pragma once
#ifndef DIFFUSION_MVCCOMMAND_H
#define DIFFUSION_MVCCOMMAND_H

#include "../../mvc/cmd/Command.h"
#include "../../mvc/notify/HashClassifyNotification.h"
#include "../config/Config.h"

namespace lc{
    class MvcCommand : public Command {
    protected:
        void notify(NotifyEvent* event, bool free = true) {
            getNotification().notify(*event);
            if (free) { delete (event); }
        }

        void notify(const std::string& name, void* attachment = nullptr, bool free = true) {
            notify(new NotifyEvent(name, attachment), free);
        }
    };
}
#endif //DIFFUSION_MVCCOMMAND_H
