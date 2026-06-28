/**
 * @file Heap.cpp
 * @author Fardin Mahmud
 * @brief This file implements the templated Heap class which can be both min-heap and max-heap
 * @date 06/05/2026
 *
 * @copyright Copyright (c) 2026
 *
 */
#include "Heap.hpp"
#include <stdexcept>


// The function below will work as intended after you implement the helper functions
// DO NOT MODIFY THE FUNCTION BELOW!
template <typename T>
void Heap<T>::removeAt(size_t idx) {
    // Check if `idx` is valid
    if (idx >= items_.size()) {
        throw std::out_of_range("Index is out of bounds.");
    }
    // If it's already the last item, pop it and clear its index
    if (idx == items_.size() - 1) {
        if (isMinHeap_) {
            items_.back()->minHeapIndex = -1;
        } else {
            items_.back()->maxHeapIndex = -1;
        }
        items_.pop_back();
        return;
    }
    // Swap the target with the last item
    std::swap(items_.at(idx), items_.back());
    // Update the indices for both items after swap
    // Use `static_cast` to avoid compiler warnings (size_t to int conversion)
    int target_idx = static_cast<int>(idx);
    if (isMinHeap_) {
        items_.back()->minHeapIndex = -1;
        items_[idx]->minHeapIndex = target_idx;
    } else {
        items_.back()->maxHeapIndex = -1;
        items_[idx]->maxHeapIndex = target_idx;
    }
    // Erase the old node from the back of the vector
    items_.pop_back();
    // Restore the heap property for the element now sitting at `idx` by trying to bubble it down
    bubbleDown(idx);
    // Bubble it up in case if wasn't moved down and belongs higher in the tree
    bubbleUp(idx);
}

// prioritize: decides if node a should sit higher in the heap than node b
template <typename T>
bool Heap<T>::prioritize(size_t a, size_t b) const {

    // In a min-heap, a smaller priority number wins; in a max-heap, a bigger one wins
    if (isMinHeap_) {
        return items_[a]->priority < items_[b]->priority;
    } else {
        return items_[a]->priority > items_[b]->priority;
    }
}

// bubbleUp: move a node up until the heap order is correct
template <typename T>
void Heap<T>::bubbleUp(size_t idx) {

    // The root has no parent, so there is nothing to move up
    if (idx == 0) {
        return;
    }
    // Find the parent's index in the array
    size_t par = (idx - 1) / 2;

    // If this node outranks its parent, swap them and keep going up
    if (prioritize(idx, par)) {
        std::swap(items_[idx], items_[par]);

        // After swapping, update both nodes' tracked positions
        if (isMinHeap_) {
            items_[idx]->minHeapIndex = static_cast<int>(idx);
            items_[par]->minHeapIndex = static_cast<int>(par);
        } else {
            items_[idx]->maxHeapIndex = static_cast<int>(idx);
            items_[par]->maxHeapIndex = static_cast<int>(par);
        }
        // Repeat the check from the parent's spot
        bubbleUp(par);
    }
}

// bubbleDown: move a node down until the heap order is correct
template <typename T>
void Heap<T>::bubbleDown(size_t idx) {
    // Work out the two children's indices and assume this node is best for now
    size_t lft = 2 * idx + 1;
    size_t rgt = 2 * idx + 2;
    size_t bst = idx;

    // Pick the left child if it exists and outranks the current best
    if (lft < items_.size() && prioritize(lft, bst)) {
        bst = lft;
    }
    // Pick the right child if it exists and outranks the current best
    if (rgt < items_.size() && prioritize(rgt, bst)) {
        bst = rgt;
    }

    // If a child won, swap down and keep going
    if (bst != idx) {
        std::swap(items_[idx], items_[bst]);
        // Update both nodes' tracked positions after the swap
        if (isMinHeap_) {
            items_[idx]->minHeapIndex = static_cast<int>(idx);
            items_[bst]->minHeapIndex = static_cast<int>(bst);
        } else {
            items_[idx]->maxHeapIndex = static_cast<int>(idx);
            items_[bst]->maxHeapIndex = static_cast<int>(bst);
        }
        // Repeat the check from the child's spot
        bubbleDown(bst);
    }
}

// Constructor: set whether this heap is a min-heap or a max-heap
template <typename T>
Heap<T>::Heap(bool isMin) : isMinHeap_(isMin) {}

// Copy constructor: make a deep copy so the new heap has its own nodes
template <typename T>
Heap<T>::Heap(const Heap& other) : isMinHeap_(other.isMinHeap_) {

    // Build a brand new node for each node in the other heap
    for (const auto& node : other.items_) {
        items_.push_back(std::make_shared<HeapNode<T>>(*node));
    }
}

// Copy assignment: clear this heap, then deep copy the other heap's nodes
template <typename T>
Heap<T>& Heap<T>::operator=(const Heap& other) {
    // Do nothing if assigning to itself
    if (this == &other) {
        return *this;
    } else {
        isMinHeap_ = other.isMinHeap_;
        items_.clear();

        // Make a fresh copy of every node from the other heap
        for (const auto& node : other.items_) {
            items_.push_back(std::make_shared<HeapNode<T>>(*node));
        }
        return *this;
    }
}

// isEmpty: true when the heap has no items
template <typename T>
bool Heap<T>::isEmpty() const {
    return items_.empty();
}

// size: number of items in the heap
template <typename T>
size_t Heap<T>::size() const {
    return items_.size();
}

// clear: remove all items from the heap
template <typename T>
void Heap<T>::clear() {
    items_.clear();
}

// peek: return the top node without removing it
template <typename T>
std::shared_ptr<HeapNode<T>> Heap<T>::peek() const {
    if (items_.empty()) {
        throw std::out_of_range("Cannot peek an empty heap.");
    } else {
        return items_.front();
    }
}

// push: add a node to the heap and move it to the right spot
template <typename T>
void Heap<T>::push(std::shared_ptr<HeapNode<T>> node) {

    // Put the node at the end of the array first
    items_.push_back(node);
    size_t idx = items_.size() - 1;

    // Record its position right away, before any bubbling
    if (isMinHeap_) {
        node->minHeapIndex = static_cast<int>(idx);
    } else {
        node->maxHeapIndex = static_cast<int>(idx);
    }

    // Move it up until the heap order is correct
    bubbleUp(idx);
}

// pop: remove and return the top node of the heap
template <typename T>
std::shared_ptr<HeapNode<T>> Heap<T>::pop() {
    if (items_.empty()) {
        throw std::out_of_range("Cannot pop an empty heap.");
    } else {
        // Remember the top node so we can return it later
        std::shared_ptr<HeapNode<T>> tpn = items_.front();

        // The node is leaving this heap, so reset its tracked index to -1
        if (isMinHeap_) {
            tpn->minHeapIndex = -1;
        } else {
            tpn->maxHeapIndex = -1;
        }
        // If it was the only item, just remove it and return
        if (items_.size() == 1) {
            items_.pop_back();
            return tpn;
        } else {
            // Move the last node to the top, fix its index, drop the old last slot
            items_[0] = items_.back();
            if (isMinHeap_) {
                items_[0]->minHeapIndex = 0;
            } else {
                items_[0]->maxHeapIndex = 0;
            }
            items_.pop_back();
            // Move the new top down until the heap order is correct
            bubbleDown(0);
            return tpn;
        }
    }
}