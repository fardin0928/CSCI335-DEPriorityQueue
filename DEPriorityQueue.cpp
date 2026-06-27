#include "DEPriorityQueue.hpp"
#include <stdexcept>

template <typename T>
DEPriorityQueue<T>::DEPriorityQueue()
    : minHeap_(true), maxHeap_(false) {

}

template <typename T>
DEPriorityQueue<T>::DEPriorityQueue(const DEPriorityQueue& other)
    : minHeap_(true), maxHeap_(false) {

    Heap<T> tmp = other.minHeap_;
    while (!tmp.isEmpty()) {
        auto node = tmp.peek();
        push(node->data, node->priority);
        tmp.pop();
    }
}

template <typename T>
DEPriorityQueue<T>& DEPriorityQueue<T>::operator=(const DEPriorityQueue& other) {

    if (this == &other) {
        return *this;
    }

    clear();
    Heap<T> tmp = other.minHeap_;
    while (!tmp.isEmpty()) {
        auto node = tmp.peek();
        push(node->data, node->priority);
        tmp.pop();
    }
    return *this;
}

template <typename T>
DEPriorityQueue<T>::DEPriorityQueue(DEPriorityQueue&& other)
    : minHeap_(std::move(other.minHeap_)), maxHeap_(std::move(other.maxHeap_)) {

    other.clear();
}

template <typename T>
DEPriorityQueue<T>& DEPriorityQueue<T>::operator=(DEPriorityQueue&& other) {

    if (this == &other) {
        return *this;
    }

    minHeap_ = std::move(other.minHeap_);
    maxHeap_ = std::move(other.maxHeap_);
    other.clear();
    return *this;
}

template <typename T>
void DEPriorityQueue<T>::push(const T& item, int priority) {

    auto node = std::make_shared<HeapNode<T>>();
    node->data = item;
    node->priority = priority;
    node->minHeapIndex = -1;
    node->maxHeapIndex = -1;

    minHeap_.push(node);
    maxHeap_.push(node);
}

template <typename T>
const T& DEPriorityQueue<T>::peekMin() const {
    if (minHeap_.isEmpty()) {
        throw std::out_of_range("Priority queue is empty.");
    }
    return minHeap_.peek()->data;
}

template <typename T>
const T& DEPriorityQueue<T>::peekMax() const {
    if (maxHeap_.isEmpty()) {
        throw std::out_of_range("Priority queue is empty.");
    }
    return maxHeap_.peek()->data;
}

template <typename T>
T DEPriorityQueue<T>::popMin() {
    if (minHeap_.isEmpty()) {
        throw std::out_of_range("Priority queue is empty.");
    }

    auto node = minHeap_.pop();

    maxHeap_.removeAt(static_cast<size_t>(node->maxHeapIndex));
    return node->data;
}

template <typename T>
T DEPriorityQueue<T>::popMax() {
    if (maxHeap_.isEmpty()) {
        throw std::out_of_range("Priority queue is empty.");
    }

    auto node = maxHeap_.pop();

    minHeap_.removeAt(static_cast<size_t>(node->minHeapIndex));
    return node->data;
}

template <typename T>
bool DEPriorityQueue<T>::isEmpty() const {
    return minHeap_.isEmpty();
}

template <typename T>
size_t DEPriorityQueue<T>::size() const {
    return minHeap_.size();
}

template <typename T>
void DEPriorityQueue<T>::clear() {
    minHeap_.clear();
    maxHeap_.clear();
}