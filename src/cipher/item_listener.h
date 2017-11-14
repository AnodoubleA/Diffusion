//
// Created by Angel on 2017/3/24.
//

#ifndef DIFFUSION_JOB_LISTENER_H
#define DIFFUSION_JOB_LISTENER_H

#include <functional>
#include "items.h"
namespace lc{
    typedef std::function<void*(Item& item)> ItemListener;
}
#endif //DIFFUSION_JOB_LISTENER_H
