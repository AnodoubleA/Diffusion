//
// Created by Alice on 2017.03.09.
//
#pragma once
#ifndef DIFFUSION_SCHEDULER_H
#define DIFFUSION_SCHEDULER_H

#include <list>
#include "../core/DiffusionException.h"
#include "../mvc/cmd/Option.h"
#include "../tool/queue.h"

namespace lc{
	template<class T>
	class Scheduler {
	public:
		static const int STANDARY = 1 << 0;
		static const int RUNNING = 1 << 1;
		static const int TERMINATED = 1 << 2;
		static const int ABORT = 1 << 3;
		static const int COMPLETED = 1 << 4;
		
		virtual int status() = 0;
		
		virtual int size()  = 0;
		
		virtual int remainder()  = 0;
		
		virtual void init(Option* option) throw(DiffusionException) = 0;
		
		virtual void append(std::list<T>& jobs) = 0;
		
		virtual void remove(std::list<T>& jobs) = 0;
		
		virtual int start() throw(DiffusionException) = 0;
		
		virtual bool terminate()throw(DiffusionException) = 0;
		
		virtual void clear()throw(DiffusionException) = 0;
		
	};
	
	template<class T>
	class AbstractScheduler : public Scheduler<T> {
	protected:
		int _status_ = 0;
	public:
		int remainder() override {
			return 0;
		}
		
		int status() override {
			return _status_;
		}
	};
	
	
}
#endif //DIFFUSION_SCHEDULER_H
