//
//  TestMedianSet.mm
//
//  Test medianset set with iterator to median value in set impl.

#import <XCTest/XCTest.h>

#import "medianset.hpp"

@interface TestMedianSet : XCTestCase

@end

@implementation TestMedianSet

- (void)testEmptyInsertDelete1 {
  // Create empty set, add and then remove element
  // [] -> [3] -> []
  
  medianset<int> mset;

  XCTAssert(mset.size() == 0, @"size != 0 : %d", (int)mset.size());

  XCTAssert(mset.medianDistance() == -1, @"medianDistance != -1 : %d", (int)mset.medianDistance());
  
  mset.insert(3);
  
  XCTAssert(mset.size() == 1, @"size != 1 : %d", (int)mset.size());

  // [3] has offset 0
  
  XCTAssert(mset.medianDistance() == 0, @"medianDistance != 0 : %d", (int)mset.medianDistance());
  
  // Remove the only element
  
  mset.remove(3);
  
  XCTAssert(mset.size() == 0, @"size != 0 : %d", (int)mset.size());
  
  XCTAssert(mset.medianDistance() == -1, @"medianDistance != -1 : %d", (int)mset.medianDistance());
}

// 3 element is odd case

- (void)testSizeOddRemoveLT {
  // Operate on set of 3 values, remove op
  // [1 2 3] -> [2 3]
  //    ^        ^
  
  medianset<int> mset;

  mset.insert(1);
  mset.insert(2);
  mset.insert(3);
  
  XCTAssert(mset.size() == 3, @"size != 3 : %d", (int)mset.size());
  
  XCTAssert(mset.medianDistance() == 1, @"medianDistance != 1 : %d", (int)mset.medianDistance());

  mset.remove(1);
  
  XCTAssert(mset.size() == 2, @"size != 2 : %d", (int)mset.size());
  
  XCTAssert(mset.medianDistance() == 0, @"medianDistance != 0 : %d", (int)mset.medianDistance());
  
  int medianVal = mset.medianVal();
  XCTAssert(medianVal == 2, @"medianVal != 2 : %d", medianVal);
}

- (void)testSizeOddRemoveGT {
  // Operate on set of 3 values, remove op
  // [1 2 3] -> [1 2]
  //    ^        ^
  
  medianset<int> mset;
  
  mset.insert(1);
  mset.insert(2);
  mset.insert(3);
  
  XCTAssert(mset.size() == 3, @"size != 3 : %d", (int)mset.size());
  
  XCTAssert(mset.medianDistance() == 1, @"medianDistance != 1 : %d", (int)mset.medianDistance());
  
  mset.remove(3);
  
  XCTAssert(mset.size() == 2, @"size != 2 : %d", (int)mset.size());
  
  XCTAssert(mset.medianDistance() == 0, @"medianDistance != 0 : %d", (int)mset.medianDistance());
  
  int medianVal = mset.medianVal();
  XCTAssert(medianVal == 1, @"medianVal != 1 : %d", medianVal);
}

- (void)testSizeOddRemoveEQ {
  // Operate on set of 3 values, remove op
  // [1 2 3] -> [1 3]
  //    ^        ^
  
  medianset<int> mset;
  
  mset.insert(1);
  mset.insert(2);
  mset.insert(3);
  
  XCTAssert(mset.size() == 3, @"size != 3 : %d", (int)mset.size());
  
  XCTAssert(mset.medianDistance() == 1, @"medianDistance != 1 : %d", (int)mset.medianDistance());
  
  mset.remove(2);
  
  XCTAssert(mset.size() == 2, @"size != 2 : %d", (int)mset.size());
  
  XCTAssert(mset.medianDistance() == 0, @"medianDistance != 0 : %d", (int)mset.medianDistance());
  
  int medianVal = mset.medianVal();
  XCTAssert(medianVal == 1, @"medianVal != 1 : %d", medianVal);
}

// 4 element even remove case

- (void)testSizeEvenRemoveLT {
  // Operate on set of values, remove op
  // [1 2 3 4] -> [2 3 4]
  //    ^            ^
  
  medianset<int> mset;
  
  mset.insert(1);
  mset.insert(2);
  mset.insert(3);
  mset.insert(4);
  
  XCTAssert(mset.size() == 4, @"size != 4 : %d", (int)mset.size());
  
  XCTAssert(mset.medianDistance() == 1, @"medianDistance != 1 : %d", (int)mset.medianDistance());
  
  mset.remove(1);
  
  XCTAssert(mset.size() == 3, @"size != 3 : %d", (int)mset.size());
  
  XCTAssert(mset.medianDistance() == 1, @"medianDistance != 1 : %d", (int)mset.medianDistance());
  
  int medianVal = mset.medianVal();
  XCTAssert(medianVal == 3, @"medianVal != 2 : %d", medianVal);
}

- (void)testSizeEvenRemoveGT {
  // Operate on set of values, remove op
  // [1 2 3 4] -> [1 2 4]
  //    ^            ^
  
  medianset<int> mset;
  
  mset.insert(1);
  mset.insert(2);
  mset.insert(3);
  mset.insert(4);
  
  XCTAssert(mset.size() == 4, @"size != 4 : %d", (int)mset.size());
  
  XCTAssert(mset.medianDistance() == 1, @"medianDistance != 1 : %d", (int)mset.medianDistance());
  
  mset.remove(3);
  
  XCTAssert(mset.size() == 3, @"size != 3 : %d", (int)mset.size());
  
  XCTAssert(mset.medianDistance() == 1, @"medianDistance != 1 : %d", (int)mset.medianDistance());
  
  int medianVal = mset.medianVal();
  XCTAssert(medianVal == 2, @"medianVal != 2 : %d", medianVal);
}

- (void)testSizeEvenRemoveEQ {
  // Operate on set of values, remove op
  // [1 2 3 4] -> [1 3 4]
  //    ^            ^
  
  medianset<int> mset;
  
  mset.insert(1);
  mset.insert(2);
  mset.insert(3);
  mset.insert(4);
  
  XCTAssert(mset.size() == 4, @"size != 4 : %d", (int)mset.size());
  
  XCTAssert(mset.medianDistance() == 1, @"medianDistance != 1 : %d", (int)mset.medianDistance());
  
  mset.remove(2);
  
  XCTAssert(mset.size() == 3, @"size != 3 : %d", (int)mset.size());
  
  XCTAssert(mset.medianDistance() == 1, @"medianDistance != 1 : %d", (int)mset.medianDistance());
  
  int medianVal = mset.medianVal();
  XCTAssert(medianVal == 3, @"medianVal != 2 : %d", medianVal);
}

- (void)testSizeTwoEvenRemoveLT {
  // Operate on set of values, remove op
  // [1 2] -> [2]
  //  ^        ^
  
  medianset<int> mset;
  
  mset.insert(1);
  mset.insert(2);
  
  XCTAssert(mset.size() == 2, @"size != 4 : %d", (int)mset.size());
  
  XCTAssert(mset.medianDistance() == 0, @"medianDistance != 0 : %d", (int)mset.medianDistance());
  
  mset.remove(1);
  
  XCTAssert(mset.size() == 1, @"size != 3 : %d", (int)mset.size());
  
  XCTAssert(mset.medianDistance() == 0, @"medianDistance != 0 : %d", (int)mset.medianDistance());
  
  int medianVal = mset.medianVal();
  XCTAssert(medianVal == 2, @"medianVal != 2 : %d", medianVal);
}

- (void)testSizeTwoEvenRemoveEQ {
  // Operate on set of values, remove op
  // [2 2] -> [2]
  //  ^        ^
  
  medianset<int> mset;
  
  mset.insert(2);
  mset.insert(2);
  
  XCTAssert(mset.size() == 2, @"size != 4 : %d", (int)mset.size());
  
  XCTAssert(mset.medianDistance() == 0, @"medianDistance != 0 : %d", (int)mset.medianDistance());
  
  mset.remove(2);
  
  XCTAssert(mset.size() == 1, @"size != 3 : %d", (int)mset.size());
  
  XCTAssert(mset.medianDistance() == 0, @"medianDistance != 0 : %d", (int)mset.medianDistance());
  
  int medianVal = mset.medianVal();
  XCTAssert(medianVal == 2, @"medianVal != 2 : %d", medianVal);
}


// Insert with even number of values

- (void)testSizeEvenInsertLT {
  // [1 2] -> [0 1 2]
  //  ^          ^
  
  medianset<int> mset;
  
  mset.insert(1);
  mset.insert(2);
  
  XCTAssert(mset.size() == 2, @"size != 4 : %d", (int)mset.size());
  
  XCTAssert(mset.medianDistance() == 0, @"medianDistance != 0 : %d", (int)mset.medianDistance());
  
  XCTAssert(mset.medianVal() == 1, @"medianVal != 1 : %d", mset.medianVal());
  
  mset.insert(0);
  
  XCTAssert(mset.size() == 3, @"size != 3 : %d", (int)mset.size());
  
  XCTAssert(mset.medianDistance() == 1, @"medianDistance != 1 : %d", (int)mset.medianDistance());
  
  XCTAssert(mset.medianVal() == 1, @"medianVal != 1 : %d", mset.medianVal());
}

- (void)testSizeEvenInsertGT {
  // [1 2] -> [1 2 3]
  //  ^          ^
  
  medianset<int> mset;
  
  mset.insert(1);
  mset.insert(2);
  
  XCTAssert(mset.size() == 2, @"size != 4 : %d", (int)mset.size());
  
  XCTAssert(mset.medianDistance() == 0, @"medianDistance != 0 : %d", (int)mset.medianDistance());
  
  XCTAssert(mset.medianVal() == 1, @"medianVal != 1 : %d", mset.medianVal());
  
  mset.insert(3);
  
  XCTAssert(mset.size() == 3, @"size != 3 : %d", (int)mset.size());
  
  XCTAssert(mset.medianDistance() == 1, @"medianDistance != 1 : %d", (int)mset.medianDistance());
  
  XCTAssert(mset.medianVal() == 2, @"medianVal != 2 : %d", mset.medianVal());
}

- (void)testSizeEvenInsertEQ {
  // [1 2] -> [1 1 2]
  //  ^          ^
  
  medianset<int> mset;
  
  mset.insert(1);
  mset.insert(2);
  
  XCTAssert(mset.size() == 2, @"size != 4 : %d", (int)mset.size());
  
  XCTAssert(mset.medianDistance() == 0, @"medianDistance != 0 : %d", (int)mset.medianDistance());
  
  XCTAssert(mset.medianVal() == 1, @"medianVal != 1 : %d", mset.medianVal());
  
  mset.insert(1);
  
  XCTAssert(mset.size() == 3, @"size != 3 : %d", (int)mset.size());
  
  XCTAssert(mset.medianDistance() == 1, @"medianDistance != 1 : %d", (int)mset.medianDistance());
  
  XCTAssert(mset.medianVal() == 1, @"medianVal != 1 : %d", mset.medianVal());
}

// Insert with an odd number of elements

- (void)testSizeOddInsertLT {
  // [2 3 4] -> [1 2 3 4]
  //    ^          ^
  
  medianset<int> mset;
  
  mset.insert(2);
  mset.insert(3);
  mset.insert(4);
  
  XCTAssert(mset.size() == 3, @"size != 3 : %d", (int)mset.size());
  
  XCTAssert(mset.medianDistance() == 1, @"medianDistance != 1 : %d", (int)mset.medianDistance());
  
  XCTAssert(mset.medianVal() == 3, @"medianVal != 3 : %d", mset.medianVal());
  
  mset.insert(1);
  
  XCTAssert(mset.size() == 4, @"size != 4 : %d", (int)mset.size());
  
  XCTAssert(mset.medianDistance() == 1, @"medianDistance != 1 : %d", (int)mset.medianDistance());
  
  XCTAssert(mset.medianVal() == 2, @"medianVal != 2 : %d", mset.medianVal());
}

- (void)testSizeOddInsertGT {
  // [1 2 3] -> [1 2 3 4]
  //    ^          ^
  
  medianset<int> mset;
  
  mset.insert(1);
  mset.insert(2);
  mset.insert(3);
  
  XCTAssert(mset.size() == 3, @"size != 3 : %d", (int)mset.size());
  
  XCTAssert(mset.medianDistance() == 1, @"medianDistance != 1 : %d", (int)mset.medianDistance());
  
  XCTAssert(mset.medianVal() == 2, @"medianVal != 2 : %d", mset.medianVal());
  
  mset.insert(4);
  
  XCTAssert(mset.size() == 4, @"size != 4 : %d", (int)mset.size());
  
  XCTAssert(mset.medianDistance() == 1, @"medianDistance != 1 : %d", (int)mset.medianDistance());
  
  XCTAssert(mset.medianVal() == 2, @"medianVal != 2 : %d", mset.medianVal());
}

- (void)testSizeOddInsertEQ {
  // [1 2 3] -> [1 2 2 3]
  //    ^          ^
  
  medianset<int> mset;
  
  mset.insert(1);
  mset.insert(2);
  mset.insert(3);
  
  XCTAssert(mset.size() == 3, @"size != 3 : %d", (int)mset.size());
  
  XCTAssert(mset.medianDistance() == 1, @"medianDistance != 1 : %d", (int)mset.medianDistance());
  
  XCTAssert(mset.medianVal() == 2, @"medianVal != 2 : %d", mset.medianVal());
  
  mset.insert(2);
  
  XCTAssert(mset.size() == 4, @"size != 4 : %d", (int)mset.size());
  
  XCTAssert(mset.medianDistance() == 1, @"medianDistance != 1 : %d", (int)mset.medianDistance());
  
  XCTAssert(mset.medianVal() == 2, @"medianVal != 2 : %d", mset.medianVal());
}

- (void)testSizeOddInsertEQ2 {
  // [2 2 2] -> [2 2 2 2]
  //    ^          ^
  
  medianset<int> mset;
  
  mset.insert(2);
  mset.insert(2);
  mset.insert(2);
  
  XCTAssert(mset.size() == 3, @"size != 3 : %d", (int)mset.size());
  
  XCTAssert(mset.medianDistance() == 1, @"medianDistance != 1 : %d", (int)mset.medianDistance());
  
  XCTAssert(mset.medianVal() == 2, @"medianVal != 2 : %d", mset.medianVal());
  
  mset.insert(2);
  
  XCTAssert(mset.size() == 4, @"size != 4 : %d", (int)mset.size());
  
  XCTAssert(mset.medianDistance() == 1, @"medianDistance != 1 : %d", (int)mset.medianDistance());
  
  XCTAssert(mset.medianVal() == 2, @"medianVal != 2 : %d", mset.medianVal());
}


- (void)testSizeOddPair {
  // [1 2 3] returns [2 2]
  
  medianset<int> mset;
  
  mset.insert(1);
  mset.insert(2);
  mset.insert(3);
  
  auto p = mset.medianPair();
  
  XCTAssert(p.first == 2, @"pair.first %d", p.first);
  XCTAssert(p.second == 2, @"pair.second %d", p.second);
}

- (void)testSizeEvenPair {
  // [1 2 3 4] returns [2 3]
  
  medianset<int> mset;
  
  mset.insert(1);
  mset.insert(2);
  mset.insert(3);
  mset.insert(4);
  
  auto p = mset.medianPair();
  
  XCTAssert(p.first == 2, @"pair.first %d", p.first);
  XCTAssert(p.second == 3, @"pair.second %d", p.second);
}

- (void)testSizeEvenPairDup {
  // [2 2 3 3] returns [2 3]
  
  medianset<int> mset;
  
  mset.insert(2);
  mset.insert(2);
  mset.insert(3);
  mset.insert(3);
  
  auto p = mset.medianPair();
  
  XCTAssert(p.first == 2, @"pair.first %d", p.first);
  XCTAssert(p.second == 3, @"pair.second %d", p.second);
}

@end
