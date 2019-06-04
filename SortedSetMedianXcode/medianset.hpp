//
//  medianset.hpp
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
  
  size_t size() const {
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
    
    int shiftAfter = 0;
    
    if ((s & 0x1) == 0) {
      // size is even
      
      if (val < medianVal) {
        // value is to the left of median, nop
      } else {
        // if val is equal to or larger than median, shift right
        shiftAfter += 1;
      }
    } else {
      // size is odd
      
      if (val < medianVal) {
        // value is to the left, shift left
        shiftAfter -= 1;
      } else {
        // if val is larger or equal to median, nop
      }
    }
    
    values.insert(val);
#if defined(DEBUG)
    assert(size() == (s+1));
#endif // DEBUG

    if (shiftAfter == -1) {
      median--;
    } else if (shiftAfter == 1) {
      median++;
    }
    
#if defined(DEBUG)
    validateMedian();
#endif // DEBUG
  }
  
  void remove(T val) {
    // If remove is invoked when there are no elements in the
    // set or with a val that is not in the set then nop.
    
    size_t s = size();
    
    if (s == 0) {
      return;
    }
    
    T medianVal = *median;
    typename multiset<T>::iterator removeIter;
    
    {
      if (val == medianVal) {
        // Avoid logn search when deleting median value
        removeIter = median;
      } else {
        removeIter = values.find(val);
        
        if (removeIter == values.end()) {
          return;
        }
      }
    }
    
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
    
    if (removeIter == median) {
      // Move median iterator back 1 before erase
      median--;
    }
    
    values.erase(removeIter);
#if defined(DEBUG)
    assert(size() == (s-1));
#endif // DEBUG
    
#if defined(DEBUG)
    validateMedian();
#endif // DEBUG
  }
  
  // Determine the "offset" of the median ref if all the values were
  // stored in a flat array. For example, when the set contains
  // [1 2 3] then the medianDistance returns 1. Note that this method
  // it not fast since it must iterate from the start of the container
  // up to the median ref value to determine the distance.
  
  size_t medianDistance() const {
    if (size() == 0) {
      return -1;
    }
    
    return distance(values.begin(), median);
  }

#if defined(DEBUG)
  // Debug method to validate that the median iterator is referencing
  // the correct element in the set.
  
  void validateMedian() const {
    int s = (int) size();
    if (s == 0) {
      return;
    }
    
    int dm = (int) medianDistance();

    if ((s % 2) == 0) {
      // even
      assert(dm == ((s / 2)-1));
    } else {
      // odd
      assert(dm == (s / 2));
    }
  }
#endif // DEBUG

  // Quickly return the median value in the sorted set of values.
  // Note that this method invocation is invalid when size() is zero.
  // With 3 values like [1 2 3] this returns 2.
  // With 4 values like [1 2 3 4] this returns 2.
  
  T medianVal() {
    return *median;
  }
  
  // When the count is odd like [1 2 3] this method returns [2 2]
  // but in the even case like [1 2 3 4] this method returns [2 3]
  
  pair<T, T> medianPair() const {
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
  
  typename multiset<T>::iterator begin() const {
    return values.begin();
  }

  typename multiset<T>::iterator end() const {
    return values.end();
  }
  
};

#endif // medianset_hpp
