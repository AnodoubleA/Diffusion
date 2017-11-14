//
// Created by Alice on 2017.03.14.
//

#ifndef DIFFUSION_ITEMS_H
#define DIFFUSION_ITEMS_H

#include "Job.h"
#include "../module/cmds/options.h"
#include "structs.h"

namespace lc{
	class Item : public Job {
		int _status = STANDBY;
		int _flags = 0;
		int id = 0;
	public:
		static const int NOTIFIED = 1 << 16;
		static const int WITH_ERROR = 1 << 17;
		Init* init = nullptr;
		Info* info = nullptr;
		uint64 start = 0;
		uint64 end = 0;
		uint64 length = 0;
		FileOption* option = nullptr;
		std::string message;
		BufferContact contact;
		SchedulerContact* scheduler = nullptr;
		std::string in_file;
		std::string in_name;
		std::string in_parent;
		std::string out_file;
		
		int status() override {
			return _status;
		}
		
		void status(int value) {
			_status = value;
		}
		
		int flags() override {
			return _flags;
		}
		
		int flags(int flag) {
			_flags |= flag;
		}
	};
}
#endif //DIFFUSION_ITEMS_H
