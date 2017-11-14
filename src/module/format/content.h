//
// Created by Alice on 2017.03.17.
//

#ifndef DIFFUSION_CONTENT_H
#define DIFFUSION_CONTENT_H

#include <string>
#include <vector>

namespace lc{
    class ContentHandler {
    public:
        virtual const std::string& handle(std::string& body, int index, std::vector<void*>& ls) = 0;
    };
}
#endif //DIFFUSION_CONTENT_H
