//
// Created by Alice on 2017.03.18.
//
#include "../cmd/StandardInvoker.h"
#include "console.h"
#include "winconsole.h"

namespace lc{
    namespace csl{
        Invoker* static_invoker = new StandardInvoker();
        std::map<std::string, std::string> MM;
    }

    void init_consoles() {
        csl::MM["-wp"] = "\"";
    }
}
