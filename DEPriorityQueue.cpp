/**
 * @file DEPriorityQueue.cpp
 * @author Fardin Mahmud
 * @brief Implementation of the DEPriorityQueue class. It keeps a min-heap and a
 *        max-heap in sync so we can quickly get both the smallest and largest priority item.
 * @date 06/05/2026
 *
 * @copyright Copyright (c) 2026
 *
 */
#include "DEPriorityQueue.hpp"
#include <stdexcept>

// Default constructor: build the min-heap with true and the max-heap with false
template <typename T>
DEPriorityQueue<T>::DEPriorityQueue()
    : minHeap_(true), maxHeap_(false) {

}

// Copy constructor: make a deep copy by re-inserting every item from the other queue
template <typename T>
DEPriorityQueue<T>::DEPriorityQueue(const DEPriorityQueue& other)
    : minHeap_(true), maxHeap_(false) {

    // Copy the other queue's min-heap so we can read its items without changing the original
    Heap<T> tmp = other.minHeap_;
    // Take items out one by one and push each one into this queue (this makes brand new nodes)
    while (!tmp.isEmpty()) {
        auto node = tmp.peek();
        push(node->data, node->priority);
        tmp.pop();
    }
}

// Copy assignment: clear what we have, then deep copy the items from the other queue
template <typename T>
DEPriorityQueue<T>& DEPriorityQueue<T>::operator=(const DEPriorityQueue& other) {
    // If someone assigns the object to itself, do nothing and return
    if (this == &other) {
        return *this;
    } else {
        // Remove our current items first
        clear();
        // Copy the other queue's min-heap and re-insert each item into this queue
        Heap<T> tmp = other.minHeap_;
        while (!tmp.isEmpty()) {
            auto node = tmp.peek();
            push(node->data, node->priority);
            tmp.pop();
        }
        return *this;
    }
}

// Move constructor: take the other queue's heaps directly, then leave it empty
template <typename T>
DEPriorityQueue<T>::DEPriorityQueue(DEPriorityQueue&& other)
    : minHeap_(std::move(other.minHeap_)), maxHeap_(std::move(other.maxHeap_)) {

    // Make sure the moved-from queue is left in a valid empty state
    other.clear();
}

// Move assignment: take the other queue's heaps, then leave it empty
template <typename T>
DEPriorityQueue<T>& DEPriorityQueue<T>::operator=(DEPriorityQueue&& other) {
    // Guard against moving an object into itself
    if (this == &other) {
        return *this;
    } else {
        // Steal the internal heaps from the other queue
        minHeap_ = std::move(other.minHeap_);
        maxHeap_ = std::move(other.maxHeap_);
        // Leave the moved-from queue empty but usable
        other.clear();
        return *this;
    }
}

// push: add a new item with its priority to both heaps
template <typename T>
void DEPriorityQueue<T>::push(const T& item, int priority) {

    // Make one node that both heaps will share
    auto node = std::make_shared<HeapNode<T>>();
    node->data = item;
    node->priority = priority;
    node->minHeapIndex = -1;
    node->maxHeapIndex = -1;

    // Put the same node into both heaps so they stay in sync
    minHeap_.push(node);
    maxHeap_.push(node);
}

// peekMin: look at the smallest priority item without removing it
template <typename T>
const T& DEPriorityQueue<T>::peekMin() const {
    // Cannot peek if the queue is empty
    if (minHeap_.isEmpty()) {
        throw std::out_of_range("Priority queue is empty.");
    } else {
        // The smallest item is at the top of the min-heap
        return minHeap_.peek()->data;
    }
}

// peekMax: look at the largest priority item without removing it
template <typename T>
const T& DEPriorityQueue<T>::peekMax() const {
    // Cannot peek if the queue is empty
    if (maxHeap_.isEmpty()) {
        throw std::out_of_range("Priority queue is empty.");
    } else {
        // The largest item is at the top of the max-heap
        return maxHeap_.peek()->data;
    }
}
// popMin: remove and return the smallest priority item
template <typename T>
T DEPriorityQueue<T>::popMin() {
    // Cannot pop if the queue is empty
    if (minHeap_.isEmpty()) {
        throw std::out_of_range("Priority queue is empty.");
    } else {
        // Remove the top of the min-heap
        auto node = minHeap_.pop();
        // The same node is still in the max-heap, so remove it there using its tracked spot
        maxHeap_.removeAt(static_cast<size_t>(node->maxHeapIndex));
        return node->data;
    }
}

// popMax: remove and return the largest priority item
template <typename T>
T DEPriorityQueue<T>::popMax() {
    // Cannot pop if the queue is empty
    if (maxHeap_.isEmpty()) {
        throw std::out_of_range("Priority queue is empty.");
    } else {
        // Remove the top of the max-heap
        auto node = maxHeap_.pop();
        // The same node is still in the min-heap, so remove it there using its tracked spot
        minHeap_.removeAt(static_cast<size_t>(node->minHeapIndex));
        return node->data;
    }
}

// isEmpty: true when there are no items in the queue
template <typename T>
bool DEPriorityQueue<T>::isEmpty() const {
    return minHeap_.isEmpty();
}

// size: how many items are in the queue
template <typename T>
size_t DEPriorityQueue<T>::size() const {
    return minHeap_.size();
}

// clear: remove every item from both heaps
template <typename T>
void DEPriorityQueue<T>::clear() {
    minHeap_.clear();
    maxHeap_.clear();
}