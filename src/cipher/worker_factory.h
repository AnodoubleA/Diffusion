//
// Created by Angel on 2017/3/24.
//

#ifndef DIFFUSION_WORKER_FACTORY_H
#define DIFFUSION_WORKER_FACTORY_H
namespace lc{
    template<class T>
    class WorkerFactory {
    public:
        virtual T& make(int options) = 0;
    };
}
#endif //DIFFUSION_WORKER_FACTORY_H
