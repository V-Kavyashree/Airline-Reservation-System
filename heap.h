#include "MinHeap.h"
#include <algorithm>

MinHeap::MinHeap() {}

void MinHeap::insert(const Flight& flight) {
    heap.push_back(flight);
    heapifyUp(heap.size() - 1);
}

std::vector<Flight> MinHeap::getSortedFlights() {
    std::vector<Flight> sortedFlights;
    while (!heap.empty()) {
        std::swap(heap.front(), heap.back());
        sortedFlights.push_back(heap.back());
        heap.pop_back();
        heapifyDown(0);
    }
    return sortedFlights;
}

void MinHeap::heapifyUp(int index) {
    while (index > 0 && heap[parent(index)].departure_time > heap[index].departure_time) {
        std::swap(heap[parent(index)], heap[index]);
        index = parent(index);
    }
}

void MinHeap::heapifyDown(int index) {
    int smallest = index;
    int left = leftChild(index);
    int right = rightChild(index);

    if (left < heap.size() && heap[left].departure_time < heap[smallest].departure_time) {
        smallest = left;
    }
    if (right < heap.size() && heap[right].departure_time < heap[smallest].departure_time) {
        smallest = right;
    }
    if (smallest != index) {
        std::swap(heap[index], heap[smallest]);
        heapifyDown(smallest);
    }
}

int MinHeap::parent(int index) {
    return (index - 1) / 2;
}

int MinHeap::leftChild(int index) {
    return 2 * index + 1;
}

int MinHeap::rightChild(int index) {
    return 2 * index + 2;
}
