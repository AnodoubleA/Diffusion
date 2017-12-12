//
// Created by Alice on 2017.02.27.
//
#pragma once
#ifndef DIFFUSION_OPTIONS_H
#define DIFFUSION_OPTIONS_H

#define C_DO_SOURCE '+'
#define C_DELETE_SOURCE 'x'
#define C_PADDING 'p'
#define C_RECURSION '*'
#define C_COVER 'c'
#define C_REG_SPT '>'

#include <string>
#include "../cipher/Consts.h"
#include "../cipher/Contact.h"
#include "../../mvc/cmd/Option.h"
#include "../../core/types.h"
#include "../../cipher/CipherModel.h"

namespace lc{
	
	typedef class CipherOption : public Option {
	
	public:
		int options = 0;
		int level = 1;
		int size = 128;
		byte* key = nullptr;
		int key_size = 0;
		std::string keyfile;
	} CO;
	
	typedef class TextOption : public CipherOption {
	public:
		~TextOption() {
			delete[](input);
		}
		
		static const int WRITE_IN_FILE = 1 << 16;
		byte* input = nullptr;
		int input_size = 0;
	} TO;
	
	typedef class FileOption : public CipherOption {
	
	public:
		FileOption() {};
		//@formatter:off
        static const int DO_SOURCE           = 1 << 16;
        static const int DEL_SOURCE          = 1 << 17;
        static const int COVER               = 1 << 18;
        static const int RECURSION           = 1 << 19;
        //@formatter:off

        CipherModel* model = nullptr;
		std::list<Item*>* items = nullptr;
        std::string input;
        std::string output;
        std::string filter;
        bool isdir_in = true;
        bool isdir_out = true;
        int fileSmashTimes = 49;
    } FO;

}

#endif //DIFFUSION_OPTIONS_H
