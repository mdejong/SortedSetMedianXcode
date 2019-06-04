//
//  msedianset.hpp
//
//  Created by Mo DeJong on 5/31/19.
//
//  multiset that maintains an iterator to the middle
//  value in the set. This logic handles inserting
//  and element in logn time, deleting an element in
//  logn time, and checking the value of the median
//  element in o1 time via use of the iterator.

#ifndef medianset_hpp
#define medianset_hpp

#include <vector>
#include <string>
#include <set>
#include <sstream>

#include <iostream>

using namespace std;

template<typename T>
class medianset {
protected:
  multiset<T> values;
  typename multiset<T>::iterator median;
  
public:
  medianset() : values(), median(values.begin()) {
  };
  
  size_t size() {
    return values.size();
  }
  
  void insert(T val) {
    size_t s = size();
    
    if (s == 0) {
      // Special case for empty set, insert the value and update
      // the median iterator to the first value
      
      values.insert(val);
      median = values.begin();
      return;
    }
    
    T medianVal = *median;
    
    bool isPostShift = false;
    
    if ((s & 0x1) == 0) {
      // size is even
      
      if (val < medianVal) {
        // value is to the left of median, nop
      } else {
        // if val is equal to or larger than median, shift right
        isPostShift = true;
      }
    } else {
      // size is odd
      
      if (val < medianVal) {
        // value is to the left, shift left
        median--;
      } else {
        // if val is larger or equal to median, nop
      }
    }
    
    values.insert(val);
#if defined(DEBUG)
    assert(size() == (s+1));
#endif // DEBUG
    
    if (isPostShift) {
      median++;
    }
  }
  
  void remove(T val) {
    // If remove is invoked when there are no elements in the
    // set or with a val that is not in the set then nop.
    
    size_t s = size();
    
    auto removeIter = values.find(val);
    
    if (s == 0) {
      return;
    } else if (removeIter == values.end()) {
      return;
    }
    
    T medianVal = *median;
    
    if ((s & 0x1) == 0) {
      // size is even
      
      if (val <= medianVal) {
        // value to remove is to the left of median or it is the median
        median++;
      } else {
        // if val is larger than median then nop
      }
    } else {
      // size is odd
      
      if (val <= medianVal) {
        // value to remove is to the left of median or it is the median, nop
      } else {
        // if val is larger than median then move media to the left
        median--;
      }
    }
    
    values.erase(removeIter);
#if defined(DEBUG)
    assert(size() == (s-1));
#endif // DEBUG
  }
  
  // Determine the "offset" of the median ref if all the values were
  // stored in a flat array. For example, when the set contains
  // [1 2 3] then the medianDistance returns 1. Note that this method
  // it not fast since it must iterate from the start of the container
  // up to the median ref value to determine the distance.
  
  size_t medianDistance() {
    if (size() == 0) {
      return -1;
    }
    
    return distance(values.begin(), median);
  }

  // Quickly return the median value in the sorted set of values.
  // Note that this method invocation is invalid when size() is zero.
  // With 3 values like [1 2 3] this returns 2.
  // With 4 values like [1 2 3 4] this returns 2.
  
  T medianVal() {
    return *median;
  }
  
  // When the count is odd like [1 2 3] this method returns [2 2]
  // but in the even case like [1 2 3 4] this method returns [2 3]
  
  pair<T, T> medianPair() {
    auto i2 = median;
    size_t s = size();
    
    if ((s & 0x1) == 0) {
      // even
      auto i2 = median;
      i2++;
      return pair<T, T>(*median, *i2);
    } else {
      // odd
      T val = *median;
      return pair<T, T>(val, val);
    }
  }
};

#endif // medianset_hpp
