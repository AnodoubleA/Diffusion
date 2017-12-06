//
// Created by Alice on 2017.03.14.
//

#ifndef DIFFUSION_JOBCIPHERFACTORY_H
#define DIFFUSION_JOBCIPHERFACTORY_H

#include "../tool/converter.h"
#include "../tool/tools.h"
#include "../core/DiffusionException.h"
#include "../module/cipher/FileCipher.h"
#include "Worker.h"
#include "workers.h"
#include "worker_factory.h"

namespace lc{
    class JobCipherFactory : public WorkerFactory<Worker<Item>> {
        std::list<Worker<Item>*> ls;
    public:
        Worker<Item>& make(int options) {
            std::list<Worker<Item>*>::iterator it = ls.begin();
            while (it != ls.end()) {
                Worker<Item>* job = &(**it++);
                if (job->support(options) && job->lock()) {
                    return *job;
                }
            }
            Worker<Item>* job;
            if (contains(options, FO::ENCIPHER | FO::DO_SOURCE)) {
                job = new FastJobEncipher();
                goto end;
            }
            if (contains(options, FO::ENCIPHER | FO::PADDING)) {
                job = new SuperJobEncipher();
                goto end;
            }
            if (contains(options, FO::ENCIPHER, FO::PADDING)) {
                job = new PowerJobEncipher();
                goto end;
            }
            if (contains(options, FO::DECIPHER)) {
                job = new FullJobDecipher();
                goto end;
            }
            throw DiffusionException("No worker for options: " + Cvt::toString(options));
            end:
            job->lock();
            ls.push_back(job);
            return *job;
        }
    };
}
#endif //DIFFUSION_JOBCIPHERFACTORY_H
