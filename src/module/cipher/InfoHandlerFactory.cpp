//
// Created by Angel on 2017/12/12.
//
#include "InfoHandlerFactory.h"
#include "infos/DefaultInfoHandlerFactory.h"

using namespace lc;

DefaultInfoHandlerFactory factory;

InfoHandlerFactory& InfoHandlerFactory::defaultFactory() {

    return factory;
}