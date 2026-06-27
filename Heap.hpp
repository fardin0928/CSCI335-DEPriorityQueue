/**
 * @file Heap.hpp
 * @author your name (your student email)
 * @brief This file defines the interface for the templated Heap class which can be both min-heap and max-heap
 * @date 2026-06-07
 * 
 * @copyright Copyright (c) 2026
 * 
 */
# pragma once

# include <vector>
# include <memory>


/**
 * @brief Holds data items, priority, and their positions in the heap
 * 
 * @tparam T The type of data stored in the node
 */
template <typename T>
struct HeapNode {
    T data;                 /**< Item being stored in current node */
    int priority;           /**< Numeric priority used to position this node within the heap */
    
    int minHeapIndex;    /**< Position of the node if located in a min-heap. -1 if not located. */
    int maxHeapIndex;    /**< Position of the node if located in a max-heap. -1 if not located. */
};


/**
 * @brief Pointer-based binary heap that maintains structural positions for both max and min order
 * @tparam T 
 */
template <typename T>
class Heap {
    
    private:
        std::vector<std::shared_ptr<HeapNode<T>>> items_;   /**< Vector container holding shared pointers to the heap nodes */
        bool isMinHeap_;                                    /**< Keeps track of whether this is a min-heap (true) or a max-heap (false) */
        
        /**
         * @brief Determines if node at @p a takes precedence over @p b based on the heap type
         * 
         * @param a Vector index of the first node to compare
         * @param b Vector index of the second node to compare
         * @return true If node @p a should be higher in the heap than node @p b
         * @return false Otherwise
         * @note Since this is a helper function, indices are assumed to be within valid vector bounds
         */
        bool prioritize(size_t a, size_t b) const;
        /**
         * @brief Restores the heap property by moving an item up the binary tree
         * 
         * @param idx The starting vector index of the item to be bubbled up
         * @post The item at @p idx is moved to its correct structural position.
         *       All modified node indices are updated, and the heap property is maintained.
         * @note Since this is a helper function, the index is assumed to be within valid vector bounds
         * @note Hint: consider using recursion!
         */
        void bubbleUp(size_t idx);
        /**
         * @brief Restores the heap property by moving an item down the binary tree
         * 
         * @param idx The starting vector index of the item to be bubbled down
         * @post The item at @p idx is moved to its correct structural position.
         *       All modified node indices are updated, and the heap property is maintained.
         * @note Since this is a helper function, the index is assumed to be within valid vector bounds
         * @note Hint: consider using recursion!
         */
        void bubbleDown(size_t idx);

    public:
        /**
         * @brief Construct a new Heap object
         * 
         * @param isMin Set to true to create a min-heap, or false to create a max-heap
         */
        Heap(bool isMin);

        /**
         * @brief Copy Constructor (performs a deep copy of all internal nodes)
         * 
         * @param other An existing heap instance to copy from
         * @note Must allocate brand-new HeapNode blocks in memory to ensure 
         *       complete node isolation between heap copies.
         */
        Heap(const Heap& other);

        /**
         * @brief Copy Assignment Operator (performs a deep copy of all internal nodes)
         * 
         * @param other An existing heap instance to copy from
         * @return Heap& Reference to this updated instance
         * @post Clears current elements and recreates deep-copied independent nodes.
         */
        Heap& operator=(const Heap& other);

        /**
         * @brief Move Constructor (transfers ownership)
         * 
         * @param other An rvalue reference to a heap instance
         * @note Using `default` since std::vector and std::shared_ptr have native, optimized move constructors
         */
        Heap(Heap&& other) = default;

        /**
         * @brief Move Assignment Operator (transfers ownership of internal resources)
         * 
         * @param other An rvalue reference to a heap instance
         * @return Heap& Reference to this updated instance
         * @note Using `default` since std::vector and std::shared_ptr have native, optimized move constructors
         */
        Heap& operator=(Heap&& other) = default;

        /**
         * @brief Destroy the Heap
         * 
         * @note Dynamic memory cleanup is handled automatically by underlying smart pointers
         */
        ~Heap() = default;

        /**
         * @brief Checks if the heap is empty
         * 
         * @return true If there are no items in the heap
         * @return false Otherwise
         */
        bool isEmpty() const;
        
        /**
         * @brief Gets the current number of items in the heap
         * 
         * @return size_t The number of items in the heap
         */
        size_t size() const;

        /**
         * @brief 
         * @post 
         */

        /**
         * @brief Clears all items from the heap
         * 
         * @post The vector of shared pointers is empty
         */
        void clear();
        
        /**
         * @brief Returns a shared pointer to the top node of the heap without removing it
         * 
         * @return std::shared_ptr<HeapNode<T>> Shared pointer to the root node
         * @throw std::out_of_range If the heap is empty
         */
        std::shared_ptr<HeapNode<T>> peek() const;

        /**
         * @brief Adds an existing shared node into the heap
         * 
         * @param node A shared pointer to the HeapNode which is being inserted
         * @post The @p node is added to the vector, the node's internal indices are updated, and the heap property is maintained
         */
        void push(std::shared_ptr<HeapNode<T>> node);

        /**
         * @brief Removes and returns the shared pointer to the top node of the heap
         * 
         * @return std::shared_ptr<HeapNode<T>> The removed root node
         * @throw std::out_of_range If the heap is empty
         * @post The root node is removed and the heap maintains the min-heap/max-heap property
         */
        std::shared_ptr<HeapNode<T>> pop();

        /**
         * @brief Removes a node from an arbitrary position in the heap vector
         * 
         * @param idx The vector index of the node to be removed
         * @throw std::out_of_range If the index is out of bounds
         * @post The node at @p idx is removed and the heap property is maintained
         */
        void removeAt(size_t idx);
};

# include "Heap.cpp"
