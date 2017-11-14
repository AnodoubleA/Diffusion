//
// Created by Alice on 2017.04.20.
//

#ifndef DIFFUSION_CONFIGURE_H
#define DIFFUSION_CONFIGURE_H


#include <omp.h>
#include "type_config.h"
#include "values.h"
#include "config_key.h"
#include "../i18n/lang.h"
#include "../i18n/i18N.h"
#include "../i18n/def_i18n.h"
#include "../i18n/i18ns.h"

namespace lc{
    class Configure {
    public:
        static void config(TypeConfig& config) throw(DiffusionException) {
            int64 buf_size = config.getInt(KEY_BUFFER_MULTIPLE);
            if (buf_size < MIN_BUFMLT || buf_size > MAX_BUFMLT) {
                throw DiffusionException(I18N->gf(ERROR_CFG_BUFMLT_OOR, MIN_BUFMLT, MAX_BUFMLT, buf_size));
            }
            USE_FILE_EXNAME = config.getBool(KEY_USE_FILE_EXNAME);
            BUFFER_MULTIPLE = buf_size;
            int coreCount = omp_get_num_procs();
            std::string strCount = config.get(KEY_CORE_COUNT);
            int inCount = atol(strCount.c_str());
            if (strCount == "default")inCount = coreCount;
            coreCount = inCount > 1 ? inCount : 0;
            if (coreCount > 1) {
                int log = (int) std::floor(log2(std::min(coreCount, inCount)));
                CORE_COUNT_LOG = log;
                omp_set_num_threads(1 << log);
                omp_set_schedule(omp_sched_t::omp_sched_static, 1);
            }
            if (CORE_COUNT_LOG > 0) {
                std::string inCoreBuf = config.get(KEY_CORE_BUFFER);
                int64 len = inCoreBuf.length();
                if (len > 1) {
                    int num = atoi(inCoreBuf.substr(0, len - 1).c_str());
                    int unit = inCoreBuf.substr(len - 1)[0];
                    int buf = 1024 * 1024;
                    unit = toupper(unit);
                    if (unit == 'M') {
                        buf = num * (1 << 20);
                    } else if (unit == 'K') {
                        buf = num * 1024;
                    }
                    CORE_BUFFER_LOG = (int) std::floor(log2(buf));
                }
            }
            std::string lang = config.get(KEY_LANG);
            DefaultI18N* defI18N = new DefaultI18N();
            I18N = defI18N;
            defI18N->load(EMPTY_STRING);
            TextI18N* textI18N = new TextI18N();
            textI18N->load(lang, defI18N);
            I18N = textI18N;
        }
    };
}
#endif //DIFFUSION_CONFIGURE_H
