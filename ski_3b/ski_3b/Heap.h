//
//  Heap.h
//  ski_3b
//
//  Created by Taylor Skilling on 10/18/15.
//  Copyright (c) 2015 Taylor Skilling. All rights reserved.
//

#ifndef __ski_3b__Heap__
#define __ski_3b__Heap__

#include "d_except.h"
#include <vector>
#include <iostream>

using namespace std;

template <typename T>
class Heap
{
private:
    vector<T> list;
public:
    Heap(); // Constructor

    void InitializeMaxHeap(vector<T> list2); // Initializes a Max Heap with data from a vector
    void InitializeMinHeap(vector<T> list2); // Initializes a Min Heap with data from a vector
    
    void MaxHeapify(int i, int heapSize); // Max Heapifies node i (children must be Max Heaps)
    void BuildMaxHeap(int heapSize); // Transforms an unsorted vector into a Max Heap
    
    void MinHeapify(int i, int heapSize); // Min Heapifies node i (children must be Min Heaps)
    void BuildMinHeap(int heapSize); // Transforms an unsorted vector into a Min Heap
    
    void Heapsort(int heapSize); // Builds a max heap and sorts it when given an unsorted list
    
    int Parent(int i) {return (i+1)/2-1;}  // Given a node in a heap, return the index of the parent
    // Map vertex indices from 0-based to 1-based and back
    int Left(int i) {return 2*(i+1)-1;}    // Given a node in a heap, return the left child
    // Map vertex indices from 0-based to 1-based and back
    int Right(int i) {return 2*(i+1);}     // Given a node in a heap, return the right child
    
    T &GetItem(int i) {return list[i];}      // Return a reference to the ith item in the heap
    vector<T> GetHeap() {return list;};
    
    // Extra functions from heapV.h header file
    int GetIndex(T &key);
    int size() {return list.size();}
    
    T GetMaxHeapMaximum();
    T GetMinHeapMinimum();
};

template <typename T>
int Heap<T>::GetIndex(T &key)
// Return the index of the item key in the heap.  Assumes each item is unique.
{
    for (int i = 0; i < size(); i++)
        if (GetItem(i) == key)
            return i;
    throw rangeError("key not found in heap::getIndex");
}

template <typename T>
Heap<T>::Heap()
// Construct an empty heap.
{
}

template <typename T>
void Heap<T>::InitializeMaxHeap(vector<T> list2)
// Initialize a max heap from values in list2.
{
    for (int i = 0; i < list2.size(); i++)
        list.push_back(list2[i]);
    
    BuildMaxHeap(size());
}

template <typename T>
void Heap<T>::InitializeMinHeap(vector<T> list2)
// Initialize a min heap from values in list2.
{
    for (int i = 0; i < list2.size(); i++)
        list.push_back(list2[i]);
    
    BuildMinHeap(size());
}

template <typename T>
void Heap<T>::MaxHeapify(int i, int heapSize)
// Assumes the binary trees rooted at left(i) and right(i) are max heaps, but node i
// might be smaller than its children, violating the max-heap property.  The function
// lets the value at i float down so the subtree rooted at i obeys the max heap property.
{
    int l = Left(i);
    int r = Right(i);
    int largest;
    
    // Set largest = the largest of the two children and i (the root)
    
    if (l <= heapSize-1 && list.at(l) > list.at(i))
        largest = l;
    else
        largest = i;
    
    if (r <= heapSize-1 && list.at(r) > list.at(largest))
        largest = r;
    
    // If the root isn't the largest, swap the root with the largest child and recurse.
    if (largest != i)
    {
        swap(list[i],list[largest]);
        MaxHeapify(largest, heapSize);
    }
}

template <typename T>
void Heap<T>::MinHeapify(int i, int heapSize)
// Assumes the binary trees rooted at left(i) and right(i) are min heaps, but node i
// might be larger than its children, violating the min-heap property.  The function
// lets the value at i float down so the subtree rooted at i obeys the min heap property.
{
    int l = Left(i);
    int r = Right(i);
    int smallest;
    
    // Set smallest = the smallest of the two children and i (the root)
    
    if (l <= heapSize-1 && list.at(l) < list.at(i))
        smallest = l;
    else
        smallest = i;
    
    if (r <= heapSize-1 && list.at(r) < list.at(smallest))
        smallest = r;
    
    // If the root isn't the smallest, swap the root with the smallest child and recurse.
    if (smallest != i)
    {
        //cout << "Swapping " << list[i] << " and " << list[smallest] << endl;
        swap(list[i],list[smallest]);
        MinHeapify(smallest, heapSize);
    }
}

template <typename T>
void Heap<T>::BuildMaxHeap(int heapSize)
// Transforms an unordered list into a heap bottom-up.  The second half of a list
// represents leaves of the tree, so each element represents a one-element heap.
// This function builds a heap by running maxHeapify on the first non-leaf, and
// works up to the first element.  Max indices from starting at 0 to 1.
{
    for (int i = (size()+1)/2; i >= 0; i--)
        MaxHeapify(i, heapSize);
}

template <typename T>
void Heap<T>::BuildMinHeap(int heapSize)
// Transforms an unordered list into a heap bottom-up.  The second half of a list
// represents leaves of the tree, so each element represents a one-element heap.
// This function builds a heap by running minHeapify on the first non-leaf, and
// works up to the first element.  Max indices from starting at 0 to 1.
{
    for (int i = (size()+1)/2; i >= 0; i--)
        MinHeapify(i, heapSize);
}

template <typename T>
T Heap<T>::GetMinHeapMinimum()
// Return the smallest item in a min heap.
{
    return list[0];
}

template <typename T>
T Heap<T>::GetMaxHeapMaximum()
// Return the largest item in a max heap
{
    return list[0];
}

template <typename T>
void Heap<T>::Heapsort(int heapSize)
// Given an unordered list, first builds a max-heap.  The maximum
// element is now in the first position, and it is swapped into the
// last position.  The heap size is reduced by one, which might cause
// element 1 to violate the max-heap property.  The call to maxHeapify
// restores the max-heap property, and the functions repeats.
{
    BuildMaxHeap(heapSize);
    
    for (int i = size()-1; i >= 0; i--)
    {
        // cout << "Position: " << i << endl;
        // cout << "Swap" << endl;
        
        swap(list[0],list[i]);
        heapSize--;
        
        // cout << "maxHeapify" << endl;
        MaxHeapify(0,heapSize);
    }
}

template <typename T>
ostream &operator<<(ostream &ostr, Heap<T> &h)
// Print all information about the graph.
{
    cout << "------------------------------------------------" << endl;
    for (int i = 0; i < h.size(); i++)
    cout << h.getItem(i);
    
    cout << endl;
    
    return ostr;
    }

#endif /* defined(__ski_3b__Heap__) */
