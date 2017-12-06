//
// Created by Alice on 2017.07.28.
//

#ifndef DIFFUSION_CIPHER_STORE_H
#define DIFFUSION_CIPHER_STORE_H


#include "filters.h"
#include "items.h"
#include "../module/cipher/text_ciphers.h"
#include "Scheduler.h"

namespace lc{
	namespace npcmd{
		extern int batch;
		
		extern FileFilter filter;
		
		extern Scheduler<Item*>& getScheduler();
		
		extern TextEncipher& getTextEncipher();
		
		extern TextDecipher& getTextDecipher();
	}
}

#endif //DIFFUSION_CIPHER_STORE_H
