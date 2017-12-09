//
// Created by Alice on 2017.02.27.
//
#pragma once
#ifndef DIFFUSION_STANDARDINVOKER_H
#define DIFFUSION_STANDARDINVOKER_H

#include "Invoker.h"
#include "../../module/cipher/InfoHeader.h"

namespace lc{
    class StandardInvoker : public Invoker {
    public:
        void invoke(Command* command, Option* option = nullptr) {
            try {
                execution(command, option);
            } catch (std::exception& e) {
                NotifyEvent event("command.execute.error", &e);
                getNotification().notify(event);
            }
        }

    protected:
        void execution(Command* command, Option* option = nullptr) {
            command->execute(option);
            delete (command);
            delete (option);
        }
    };
}

#endif //DIFFUSION_STANDARDINVOKER_H
