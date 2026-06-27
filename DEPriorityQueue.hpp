/**
 * @file DEPriorityQueue.hpp
 * @author your name (your student email)
 * @brief This file defines the interface for the DEPriorityQueue (Double-Ended Priority Queue) 
 *        which maintains synchronized min and max heaps for dual-ended priority access
 * @date 2026-06-07
 * 
 * @copyright Copyright (c) 2026
 * 
 */
#pragma once

#include "Heap.hpp"


template <typename T>
class DEPriorityQueue {
    
    private:
        Heap<T> minHeap_;   /**< Internal min-heap tracking items with lower priority numbers at the root */
        Heap<T> maxHeap_;   /**< Internal max-heap tracking items with higher priority numbers at the root */

    public:
        /**
         * @brief Construct a new DEPriorityQueue object
         * 
         * @post minHeap_ and maxHeap_ are initialized
         */
        DEPriorityQueue();

        /**
         * @brief Destroy the DEPriorityQueue object
         *
         * @note Dynamic memory cleanup is handled automatically by underlying smart pointers
         */
        ~DEPriorityQueue() = default;

        /**
         * @brief Copy Constructor (performs a deep copy of all internal nodes)
         * 
         * @param other An existing queue instance to copy from
         */
        DEPriorityQueue(const DEPriorityQueue& other);
        
        /**
         * @brief Copy Assignment Operator (performs a deep copy of all internal nodes)
         * 
         * @param other An existing queue instance to copy from
         * @return DEPriorityQueue& Reference to this updated instance
         */
        DEPriorityQueue& operator=(const DEPriorityQueue& other);

        /**
         * @brief Move Constructor
         * 
         * @param other An rvalue reference to a queue instance
         * @note You must implement this yourself without using `default`
         */
        DEPriorityQueue(DEPriorityQueue&& other);

        /**
         * @brief Move Assignment Operator
         * 
         * @param other An rvalue reference to a queue instance
         * @return DEPriorityQueue& Reference to this updated instance
         * @note You must implement this yourself without using `default`
         */
        DEPriorityQueue& operator=(DEPriorityQueue&& other);

        /**
         * @brief Inserts a new item with a numerical priority value
         * 
         * @param item The item being stored
         * @param priority Numeric priority of the item
         * @post The @p item and the @p priority are packed into a @c HeapNode and added to both heaps.
         *       Both heaps maintain position of the items accurately based on heap property.
         */
        void push(const T& item, int priority);
        
        /**
         * @brief Returns an immutable reference to the item with the minimum priority
         * 
         * @return const T& The minimum priority item which is the root of the min-heap
         * @throw std::out_of_range If the priority queue is empty
         */
        const T& peekMin() const;

        /**
         * @brief Returns an immutable reference to the item with the maximum priority
         * 
         * @return const T& The maximum priority item which is the root of the max-heap
         * @throw std::out_of_range If the priority queue is empty
         */
        const T& peekMax() const;

        /**
         * @brief Removes and returns the item with the minimum priority
         * 
         * @return T The data element of the removed minimum priority item
         * @throw std::out_of_range If the priority queue is empty
         * @post The item is popped from the min-heap and removed from the max-heap. 
         *       Both heaps maintain heap property and correct indices.
         */        
        T popMin();

        /**
         * @brief Removes and returns the item with the maximum priority
         * 
         * @return T The data element of the removed maximum priority item
         * @throw std::out_of_range If the priority queue is empty
         * @post The item is popped from the max-heap and removed from the min-heap. 
         *       Both heaps maintain heap property and correct indices.
         */
        T popMax();
        
        /**
         * @brief Checks if the priority queue contains no items
         * 
         * @return true If the priority queue is empty
         * @return false Otherwise
         */
        bool isEmpty() const;

        /**
         * @brief Returns the total number of items stored in the priority queue
         * 
         * @return size_t Total item count
         */
        size_t size() const;

        /**
         * @brief Clears all items from the priority queue
         * 
         * @post Both min-heap and max-heap are empty and their sizes are 0
         */
        void clear();
};

#include "DEPriorityQueue.cpp"
