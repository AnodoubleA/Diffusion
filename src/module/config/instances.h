//
// Created by Angel on 2017/4/2.
//

#ifndef DIFFUSION_INSTANCES_H
#define DIFFUSION_INSTANCES_H

#include "../../mvc/cmd/cmd_factory.h"
#include "../../mvc/notify/HashClassifyNotification.h"
#include "../i18n/i18N.h"

namespace lc{
    extern ClassifyNotification& getNotification();

    extern CommandFactory& getCommandFactory();
}
#endif //DIFFUSION_INSTANCES_H
