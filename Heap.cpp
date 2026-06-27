# include "Heap.hpp"
#include <stdexcept>

template <typename T>
void Heap<T>::removeAt(size_t idx) {

    if (idx >= items_.size()) {
        throw std::out_of_range("Index is out of bounds.");
    }

    if (idx == items_.size() - 1) {
        if (isMinHeap_) {
            items_.back()->minHeapIndex = -1;
        } else {
            items_.back()->maxHeapIndex = -1;
        }
        items_.pop_back();
        return;
    }

    std::swap(items_.at(idx), items_.back());

    int target_idx = static_cast<int>(idx);
    if (isMinHeap_) {
        items_.back()->minHeapIndex = -1;
        items_[idx]->minHeapIndex = target_idx;
    } else {
        items_.back()->maxHeapIndex = -1;
        items_[idx]->maxHeapIndex = target_idx;
    }

    items_.pop_back();

    bubbleDown(idx);

    bubbleUp(idx);
}

template <typename T>
bool Heap<T>::prioritize(size_t a, size_t b) const {

    if (isMinHeap_) {
        return items_[a]->priority < items_[b]->priority;
    }
    return items_[a]->priority > items_[b]->priority;
}

template <typename T>
void Heap<T>::bubbleUp(size_t idx) {

    if (idx == 0) {
        return;
    }
    size_t par = (idx - 1) / 2;

    if (prioritize(idx, par)) {
        std::swap(items_[idx], items_[par]);

        if (isMinHeap_) {
            items_[idx]->minHeapIndex = static_cast<int>(idx);
            items_[par]->minHeapIndex = static_cast<int>(par);
        } else {
            items_[idx]->maxHeapIndex = static_cast<int>(idx);
            items_[par]->maxHeapIndex = static_cast<int>(par);
        }
        bubbleUp(par);
    }
}

template <typename T>
void Heap<T>::bubbleDown(size_t idx) {
    size_t lft = 2 * idx + 1;
    size_t rgt = 2 * idx + 2;
    size_t bst = idx;

    if (lft < items_.size() && prioritize(lft, bst)) {
        bst = lft;
    }
    if (rgt < items_.size() && prioritize(rgt, bst)) {
        bst = rgt;
    }

    if (bst != idx) {
        std::swap(items_[idx], items_[bst]);
        if (isMinHeap_) {
            items_[idx]->minHeapIndex = static_cast<int>(idx);
            items_[bst]->minHeapIndex = static_cast<int>(bst);
        } else {
            items_[idx]->maxHeapIndex = static_cast<int>(idx);
            items_[bst]->maxHeapIndex = static_cast<int>(bst);
        }
        bubbleDown(bst);
    }
}

template <typename T>
Heap<T>::Heap(bool isMin) : isMinHeap_(isMin) {}

template <typename T>
Heap<T>::Heap(const Heap& other) : isMinHeap_(other.isMinHeap_) {

    for (const auto& node : other.items_) {
        items_.push_back(std::make_shared<HeapNode<T>>(*node));
    }
}

template <typename T>
Heap<T>& Heap<T>::operator=(const Heap& other) {
    if (this == &other) {
        return *this;
    }
    isMinHeap_ = other.isMinHeap_;
    items_.clear();

    for (const auto& node : other.items_) {
        items_.push_back(std::make_shared<HeapNode<T>>(*node));
    }
    return *this;
}

template <typename T>
bool Heap<T>::isEmpty() const {
    return items_.empty();
}

template <typename T>
size_t Heap<T>::size() const {
    return items_.size();
}

template <typename T>
void Heap<T>::clear() {
    items_.clear();
}

template <typename T>
std::shared_ptr<HeapNode<T>> Heap<T>::peek() const {
    if (items_.empty()) {
        throw std::out_of_range("Cannot peek an empty heap.");
    }
    return items_.front();
}

template <typename T>
void Heap<T>::push(std::shared_ptr<HeapNode<T>> node) {

    items_.push_back(node);
    size_t idx = items_.size() - 1;

    if (isMinHeap_) {
        node->minHeapIndex = static_cast<int>(idx);
    } else {
        node->maxHeapIndex = static_cast<int>(idx);
    }

    bubbleUp(idx);
}

template <typename T>
std::shared_ptr<HeapNode<T>> Heap<T>::pop() {
    if (items_.empty()) {
        throw std::out_of_range("Cannot pop an empty heap.");
    }
    std::shared_ptr<HeapNode<T>> tpn = items_.front();

    if (isMinHeap_) {
        tpn->minHeapIndex = -1;
    } else {
        tpn->maxHeapIndex = -1;
    }
    if (items_.size() == 1) {
        items_.pop_back();
        return tpn;
    }

    items_[0] = items_.back();
    if (isMinHeap_) {
        items_[0]->minHeapIndex = 0;
    } else {
        items_[0]->maxHeapIndex = 0;
    }
    items_.pop_back();
    bubbleDown(0);
    return tpn;
}