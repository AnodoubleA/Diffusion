//
// Created by Alice on 2017.07.28.
//

#ifndef DIFFUSION_REMOVEITEMCOMMAND_H
#define DIFFUSION_REMOVEITEMCOMMAND_H

#include "MvcCommand.h"
#include "../../cipher/cipher_store.h"

namespace lc{
	class RemoveItemCommand : public MvcCommand {
	
	public:
		void execute(Option* option, Context* context) override {
			FileOption* fo = (FileOption*) option;
			fo->model->remove(*(fo->items));
			npcmd::getScheduler().remove(*fo->items);
		}
	};
}
#endif //DIFFUSION_REMOVEITEMCOMMAND_H
