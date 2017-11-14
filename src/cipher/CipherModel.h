//
// Created by Alice on 2017.07.28.
//

#ifndef DIFFUSION_CIPHERMODEL_H
#define DIFFUSION_CIPHERMODEL_H

#include <list>
#include "items.h"

namespace lc{
	class CipherModel {
	private:
		std::list<Item*> list;
	public:
		
		virtual void add(std::list<Item*>& items) {
			for (Item* item:items) {
				list.push_back(item);
			}
		}
		
		virtual void add(Item* item) {
			list.push_back(item);
		}
		
		virtual void remove(std::list<Item*>& items) {
			for (Item* item:items) {
				list.remove(item);
				delete (item);
			}
		}
		
		virtual void remove(Item* item) {
			list.remove(item);
		}
		
		virtual void clear() {
			for (Item* item:list) {
				delete item;
			}
			list.clear();
		}
		
		virtual std::list<Item*> getList() {
			return list;
		}
	};
	
}

#endif //DIFFUSION_CIPHERMODEL_H
