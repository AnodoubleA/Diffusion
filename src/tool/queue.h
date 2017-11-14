//
// Created by Alice on 2017.03.08.
//
#pragma once
#ifndef DIFFUSION_QUEUE_H
#define DIFFUSION_QUEUE_H

#include <list>
#include <mutex>
#include <condition_variable>
#include <cassert>

namespace lc{
    template<typename T>
    class Queue {
    public:

        virtual void push(const T& element) = 0;

        virtual T pull() = 0;

        virtual int size() = 0;

        virtual void clear() = 0;
    };

    template<class T>
    class ListQueue : public Queue<T> {
        std::list<T> queue;
    public:
        inline void push(const T& element) override {
            queue.push_back(element);
        }

        T pull() override {
            T element = queue.front();
            queue.pop_front();
            return element;
        }

        int size() override {
            return queue.size();
        }

        void clear() {
            typename std::list<T>::iterator it = queue.begin();
            while (it != queue.end()) {
                delete (*it++);
            }
            queue.clear();
        }
    };

    template<typename T>
    class BlockingQueue : public Queue<T> {
    public:
        BlockingQueue() : mutex(), condition(), queue() {

        }

        void push(const T& task) {
            {
                std::lock_guard<std::mutex> lock(mutex);
                queue.push_back(task);
            }
            condition.notify_all();
        }

        T pull() {
            std::unique_lock<std::mutex> lock(mutex);
            condition.wait(lock, [this] { return !queue.empty(); });
            assert (!queue.empty());
            T front(queue.front());
            queue.pop_front();
            return front;
        }

        int size() {
            std::lock_guard<std::mutex> lock(mutex);
            return queue.size();
        }


        void clear() {
            typename std::list<T>::iterator it = queue.begin();
            while (it != queue.end()) {
                delete (*it++);
            }
            queue.clear();
        }

    private:
        BlockingQueue(const BlockingQueue& rhs);

        BlockingQueue& operator=(const BlockingQueue& rhs);

    private:
        mutable std::mutex mutex;
        std::condition_variable condition;
        std::list<T> queue;
    };
}
#endif //DIFFUSION_QUEUE_H
