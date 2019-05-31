//
//  mset.h
//  SortedSetMedianXcode
//
//  Created by Mo DeJong on 5/31/19.
//  Copyright © 2019 HelpURock. All rights reserved.
//

#ifndef mset_h
#define mset_h

//#include <bits/stdc++.h>

#include <vector>
#include <string>
#include <set>
#include <sstream>

using namespace std;

vector<string> split_string(string);

// Determine median value given a set of int values
// 1. Even # elems, return ave of middle values
// 2. Odd # elems, return middle value

float median(const std::multiset<int> & values) {
  int halfi = (int) values.size() / 2;
  int isEven = (int) ((values.size() % 2) == 0);
  
  if (isEven) {
    // even
    //auto it = values.begin() + halfi - 1;
    auto it = values.begin();
    
    // For a container of size N, this iterator
    // will have to touch N/2 elements.

    for (int i = 0; i < (halfi - 1); i++) {
      it++;
    }
    int v1 = *it++;
    int v2 = *it;
    return (v1 + v2) / 2.0f;
  } else {
    // odd
    //auto it = values.begin() + halfi;
    auto it = values.begin();
    for (int i = 0; i < halfi; i++) {
      it++;
    }
    return float(*it);
  }
}

// return an integer representing the number of client notifications
// when a window of size d is used over expenditure values.

int activityNotifications(vector<int> expenditure, int d) {
  int numWindows = (int) expenditure.size() - d;
  int numNotifications = 0;
  
  // Init multiset which contains a balanced tree of int values,
  // note that duplicates can exist so use multiset instead of set.
  
  std::multiset<int> window;
  int windowRemoveIndex = 0;
  int windowInsertIndex = d;
  
  for ( int i = 0; i < d; i++ ) {
    int v = expenditure[i];
    window.insert(v);
  }
#if defined(DEBUG)
  assert(window.size() == d);
#endif // DEBUG
  
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
    
    // FIXME: if expenditureToRemove == expenditureToday then nop
    // Erase(v) can erase multiple matches! Use iterator erase instead
    //window.erase(expenditureToRemove);
    auto firstMatch = window.find(expenditureToRemove);
    window.erase(firstMatch);
    window.insert(expenditureToday);
#if defined(DEBUG)
    assert(window.size() == d);
#endif // DEBUG
    
    windowInsertIndex += 1;
    windowRemoveIndex += 1;
  }
  
  return numNotifications;
}

// Execute main logic using input inStr and returning the output

string mset_main(const string & inStr)
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

#endif /* mset_h */
