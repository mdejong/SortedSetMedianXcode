//
//  marr.h
//  SortedSetMedianXcode
//
//  Created by Mo DeJong on 5/31/19.
//  Copyright © 2019 HelpURock. All rights reserved.
//
//  Impl using sorted array for log(n) insert/delete
//  operations. This results in the ability to lookup
//  the middle elements in the sorted window without
//  having to iterate over 1/2 the window elements
//  to find the median.

#ifndef arr_h
#define arr_h

#include <vector>
#include <string>
#include <set>
#include <sstream>

using namespace std;

static
vector<string> split_string(string);

// Determine median value given a set of int values.
// Note that this method is O(1) since array access
// operations depend only on the container size and
// then direct access into the array.
//
// 1. Even # elems, return ave of middle values
// 2. Odd # elems, return middle value

static inline
float median(const vector<int> & values) {
  int halfi = (int) values.size() / 2;
  
  if ((values.size() % 2) == 0) {
    // even
    int v1 = values[halfi - 1];
    int v2 = values[halfi];
    return (v1 + v2) / 2.0;
  } else {
    // odd
    return float(values[halfi]);
  }
}

// return an integer representing the number of client notifications
// when a window of size d is used over expenditure values.

static inline
int activityNotifications(vector<int> expenditure, int d) {
  int numWindows = (int) expenditure.size() - d;
  int numNotifications = 0;
  
  // Init multiset which contains a balanced tree of int values,
  // note that duplicates can exist so use multiset instead of set.
  
  std::vector<int> window;
  int windowRemoveIndex = 0;
  int windowInsertIndex = d;
  
  for ( int i = 0; i < d; i++ ) {
    int v = expenditure[i];
    window.push_back(v);
  }
#if defined(DEBUG)
  assert(window.size() == d);
#endif // DEBUG
  sort(window.begin(), window.end());
  
  // window of values configured, grab today value,
  // run calculation logic, then update sorted set.
  
  for ( int i = 0; i < numWindows; i++ ) {
    // Execute median logic
    
    int expenditureToday = expenditure[windowInsertIndex];
    
    /*
     cout << "expenditureToday " << expenditureToday << endl;
     cout << "window ";
     for ( auto it = window.begin(); it != window.end(); it++ ) {
     cout << *it << " ";
     }
     cout << endl;
     */
    
    // Increment num notifications if a notification was delivered
    // over this window as indicated by the mean
    
    float dMedian = 2 * median(window);
    
    if (float(expenditureToday) >= dMedian) {
      numNotifications += 1;
    }
    
    // Update container
    
    int expenditureToRemove = expenditure[windowRemoveIndex];
    
    // Remove expenditureToRemove with log(N) time
    
    {
      auto firstMatch = lower_bound(window.begin(), window.end(), expenditureToRemove);
      window.erase(firstMatch);

#if defined(DEBUG)
      assert(window.size() == d-1);
#endif // DEBUG
    }
    
    // Insert expenditureToday with log(N) time
    
    {
      auto it = upper_bound(window.begin(), window.end(), expenditureToday);
      window.insert(it, expenditureToday);
    }
#if defined(DEBUG)
    assert(window.size() == d);
#endif // DEBUG
    
    windowInsertIndex += 1;
    windowRemoveIndex += 1;
  }
  
  return numNotifications;
}

// Execute main logic using input inStr and returning the output

static inline
string arr_main(const string & inStr)
{
  istringstream inStream;
  inStream.str(inStr);
  
  ostringstream outStream;
  
  string nd_temp;
  getline(inStream, nd_temp);
  
  vector<string> nd = split_string(nd_temp);
  
  int n = stoi(nd[0]);
  int d = stoi(nd[1]);
  
  string expenditure_temp_temp;
  getline(inStream, expenditure_temp_temp);
  
  vector<string> expenditure_temp = split_string(expenditure_temp_temp);
  
  vector<int> expenditure(n);
  
  for (int i = 0; i < n; i++) {
    int expenditure_item = stoi(expenditure_temp[i]);
    
    expenditure[i] = expenditure_item;
  }
  
  int result = activityNotifications(expenditure, d);
  
  outStream << result << "\n";
  
  return outStream.str();
}

static inline
vector<string> split_string(string input_string) {
  string::iterator new_end = unique(input_string.begin(), input_string.end(), [] (const char &x, const char &y) {
    return x == y and x == ' ';
  });
  
  input_string.erase(new_end, input_string.end());
  
  while (input_string[input_string.length() - 1] == ' ') {
    input_string.pop_back();
  }
  
  vector<string> splits;
  char delimiter = ' ';
  
  size_t i = 0;
  size_t pos = input_string.find(delimiter);
  
  while (pos != string::npos) {
    splits.push_back(input_string.substr(i, pos - i));
    
    i = pos + 1;
    pos = input_string.find(delimiter, i);
  }
  
  splits.push_back(input_string.substr(i, min(pos, input_string.length()) - i + 1));
  
  return splits;
}

#endif /* arr_h */
