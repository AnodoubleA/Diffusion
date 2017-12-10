//
// Created by Alice on 2017.03.10.
//
#pragma once
#ifndef DIFFUSION_SCHEDULERS_H
#define DIFFUSION_SCHEDULERS_H

#include "JobCipherFactory.h"
#include "CipherLisenter.h"

namespace lc{
	class SchedulerOption : public Option {
	public:
		SchedulerContact contact;
		Notification* notification = nullptr;
	};
	
	class SchedulerListener;
	
	class SyncCipherScheduler : public AbstractScheduler<Item*> {
	protected:
		ListQueue<Item*> queue;
		JobCipherFactory* factory = nullptr;
		SchedulerOption* option = nullptr;
	public:
		~SyncCipherScheduler() {
			delete (factory);
			delete (option);
		}
		
		SyncCipherScheduler() {
			factory = new JobCipherFactory();
		}
		
		void init(Option* option) throw(DiffusionException) {
			delete (this->option);
			this->option = ((SchedulerOption*) option);
		}
		
		int size() override {
			return queue.size();
		}
		
		bool terminate() throw(DiffusionException) {
			return true;
		}
		
		void append(std::list<Item*>& jobs) {
			std::list<Item*>::iterator it = jobs.begin();
			while (it != jobs.end()) {
				queue.push(*it++);
			}
		}
		
		void remove(std::list<Item*>& jobs) override {
			for (Item* item:jobs) {
				//TODO remove
			}
		}
		
		int start() throw(DiffusionException) {
			option->contact.status = RUNNING;
			NotifyEvent event_start("scheduler.begin", &option->contact);
			option->notification->notify(event_start);
			while (true) {
				Item* item = queue.pull();
				try {
					execute(*item);
				} catch (std::exception& error) {
				
				}
			}
			option->contact.status = COMPLETED;
			NotifyEvent event_end("scheduler.end", &option->contact);
			option->notification->notify(event_end);
			return 0;
		}
		
		
		void clear() throw(DiffusionException) {
			if ((status() & RUNNING) == RUNNING) {
				throw DiffusionException("Scheduler still running, interrupt and try again.");
			}
			queue.clear();
		}
	
	protected:
		void execute(Item& item) throw(DiffusionException) {
			JobEncipher& cipher = (JobEncipher&) (factory->make(item.info->options));
			try {
				cipher.init(&scheduler_listener);
				cipher.run(item);
			} catch (DiffusionException& e) {
				cipher.deinit();
				throw e;
			}
			cipher.deinit();
		}
		
		void next(Item& item) throw(DiffusionException) {
			item.status(Item::COMPLETED);
			option->contact.addDone(1);
			option->contact.addTime(item.end - item.start);
		}
		
		ItemListener scheduler_listener = [this](Item& item) {
			std::string name;
			switch (item.status()) {
				case Item::CIPHER_BEGIN:
					name.append("CI.file.begin");
					break;
				case Item::CIPHER_END:
					name.append("CI.file.end");
					break;
				case Item::DEL_BEGIN:
					name.append("CI.del.begin");
					break;
				case Item::DEL_END:
					name.append("CI.del.end");
					break;
				case Item::COMPLETED:
					name.append("CI.item.completed");
					break;
			}
			void* ret;
			if (name.length() > 0) {
				NotifyEvent event(name, &item);
				getNotification().notify(event);
				ret = event.getAttachment();
			}
			if (item.status() == Item::COMPLETED) {
				next(item);
			}
			return ret;
		};
	};
};
#endif //DIFFUSION_SCHEDULERS_H
