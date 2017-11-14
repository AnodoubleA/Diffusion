//
// Created by Alice on 2017.07.28.
//

#ifndef DIFFUSION_STARTTASKCOMMAND_H
#define DIFFUSION_STARTTASKCOMMAND_H

#include "MvcCommand.h"
#include "../../cipher/cipher_store.h"

namespace lc{
	class AddItemCommand : public MvcCommand {
	
	public:
		void execute(Option* option, Context* context) override {
			FileOption* fo = (FileOption*) option;
			fo->model->add(*(fo->items));
			npcmd::getScheduler().append(*fo->items);
		}
	};
}
#endif //DIFFUSION_STARTTASKCOMMAND_H
