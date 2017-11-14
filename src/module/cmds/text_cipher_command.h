//
// Created by Alice on 2017.03.03.
//
#pragma once
#ifndef DIFFUSION_TEXT_CIPHER_COMMAND_H
#define DIFFUSION_TEXT_CIPHER_COMMAND_H

#include "../../mvc/cmd/Command.h"
#include "MvcCommand.h"
#include "options.h"
#include "../../cipher/Contact.h"
#include "../../cipher/file_encipher.h"
#include "../../cipher/schedulers.h"
#include "../../cipher/text_ciphers.h"
#include "../../cipher/filters.h"
#include "../../cipher/cipher_store.h"

namespace lc{
	class TextEncipherCommand : public MvcCommand {
	public:
		void execute(Option* option, Context* context) {
			notify("encipher.text.begin");
			TextOption& op = *(TextOption*) option;
			OutputContact contact;
			TextEncipher& cipher = npcmd::getTextEncipher();
			Init init;
			Info info;
			T::computeInit(init, info, op, EXTEND_ROUND);
			cipher.init(init, info);
			contact.buffer = cipher.run(op.input, op.input_size, (int&) contact.length);
			contact.options = op.options;
			notify("encipher.text.end", &contact);
		}
	};
	
	class TextDecipherCommand : public MvcCommand {
	public:
		void execute(Option* option, Context* context) {
			notify("decipher.text.begin");
			TextOption& op = *(TextOption*) option;
			OutputContact contact;
			TextDecipher& cipher = npcmd::getTextDecipher();
			Init init;
			Info info;
			T::computeInit(init, info, op, EXTEND_ROUND);
			cipher.init(init, info);
			contact.buffer = cipher.run(op.input, op.input_size, (int&) contact.length);
			contact.options = op.options;
			notify("decipher.text.end", &contact);
		}
	};
}
#endif //DIFFUSION_TEXT_CIPHER_COMMAND_H
