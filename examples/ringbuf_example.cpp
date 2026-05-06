/*
 * ringbuf_example.cpp
 *
 * Just figuring out how Boost's ringbuffer implementation works.
 */

#include <boost/lockfree/spsc_queue.hpp>
#include <thread>
#include <iostream>

boost::lockfree::spsc_queue<int> queue(64);

void producer() {
    for (int i = 0; i < 100; i++) {
        while (!queue.push(i)) {
            std::cout << "Can't push; queue full" << std::endl;
        }
    }
}

void consumer() {
    int val;
    for (int i = 0; i < 100; i++) {
        while (!queue.pop(val)) {
            std::cout << "Can't pop; queue empty" << std::endl;
        }
        std::cout << "Consumer got: " << val << std::endl;
    }
}

int main() {
    std::thread producer_td(producer);
    std::thread consumer_td(consumer);
    producer_td.join();
    consumer_td.join();
}