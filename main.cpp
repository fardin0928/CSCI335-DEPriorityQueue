/**
 * @file main.cpp
 * @author Sadab Hafiz (sh3646@hunter.cuny.edu)
 * @brief Shows how to use the @c Heap class by implementing heapSort
 * @date 2026-06-07
 * @note The example test is just a single use example. You should write your own tests to make sure your code works.
 * @note This only shows how to test the Heap class. You should write your own tests for the DEPriorityQueue.
 * @copyright Copyright (c) 2026
 * 
 */

#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include "Heap.hpp"


/**
 * @brief Sorts a vector of any type in either ascending or descending order using the @c Heap class
 * 
 * @tparam T The data type of the items to be sorted
 * @param items The unsorted input vector
 * @param priority Priority of the items in @p items where priority[i] is the priority of items[i]
 * @param ascending True to sort in ascending order, false to sort in descending order
 * @return std::vector<T> The sorted vector
 */
template <typename T>
std::vector<T> heapSort(const std::vector<T>& items, const std::vector<int>& priority, bool ascending) {
    // Ensure both vectors match in size
    if (items.size() != priority.size()) {
        throw std::invalid_argument("The items and priority vectors must be of equal size.");
    }
    // To sort ascending, use min-heap (smallest comes out first)
    // To sort descending, use max-heap (largest comes out first)
    Heap<T> heap(ascending);
    // Pair each item with its corresponding priority, and push to the heap
    for (size_t i = 0; i < items.size(); i++) {
        auto node = std::make_shared<HeapNode<T>>();
        node->data = items[i];
        node->priority = priority[i];
        heap.push(node);
    }
    // Pop items out one by one into the sorted vector
    std::vector<T> sorted;
    while (!heap.isEmpty()) {
        auto topNode = heap.pop();
        sorted.push_back(topNode->data);
    }
    return sorted;
}


int main() {
    // Sorting tasks based on priority. Lower number denotes to higher priority. Thus, sorting ascending order.
    std::vector<std::string> tasks = {
        "Publish Project",
        "Prepare Slides",
        "Finish Project Instructions",
        "Research Future Topics",
        "World Cup!",
        "Make Quiz",
    };
    std::vector<int> priorities = { 2, 3, 1, 4, 6, 5 };

    // Print the unsorted vector
    std::cout << "Unsorted Tasks with Priorities:" << std::endl;
    for (size_t i = 0; i < tasks.size(); i++) {
        std::cout << " => " << tasks[i] << " (Priority: " << priorities[i] << ")" << std::endl;
    }
    std::cout << std::endl;

    // Sort ascending (lowest priority number comes out first)
    std::vector<std::string> sortedTasks = heapSort(tasks, priorities, true);

    std::cout << "Sorted Tasks (Ascending Priority):" << std::endl;
    for (const auto& task : sortedTasks) {
        std::cout << "  => " << task << std::endl;
    }

    /**
        ---------------------------------------------------------    
        Expected Output:
        ---------------------------------------------------------
        Unsorted Tasks with Priorities:
        => Publish Project (Priority: 2)
        => Prepare Slides (Priority: 3)
        => Finish Project Instructions (Priority: 1)
        => Research Future Topics (Priority: 4)
        => World Cup! (Priority: 6)
        => Make Quiz (Priority: 5)

        Sorted Tasks (Ascending Priority):
        => Finish Project Instructions
        => Publish Project
        => Prepare Slides
        => Research Future Topics
        => Make Quiz
        => World Cup!
    */
}
