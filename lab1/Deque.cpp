#include <iostream>

#define _CRTDBG_MAP_ALLOC
#include<Windows.h>
#include <crtdbg.h>
#include "Deque.h"

//Tests for deque
int main(void) {

  //test 1
  std::cout << "Test 1: default constructor" << std::endl;
  deque<std::string> dequeTest1;
  std::cout << "Expected output: deque:" << std::endl;
  std::cout << "Output: ";
  dequeTest1.print();
  std::cout << std::endl;

  //test 2
  std::cout << "Test 2: initializer_list constructor" << std::endl;
  deque<std::string> dequeTest2 = {"11", "22", "33", "44", "55"};
  std::cout << "Expected output: deque:11 22 33 44 55" << std::endl;
  std::cout << "Output: ";
  dequeTest2.print();
  std::cout << std::endl;

  //test 3
  std::cout << "Test 3: copy constructor" << std::endl;
  deque<std::string> dequeTest3(dequeTest2);
  std::cout << "Expected output: deque:11 22 33 44 55" << std::endl;
  std::cout << "Output: ";
  dequeTest3.print();
  std::cout << "Deque from which we copy data after copy(must be the same): ";
  dequeTest2.print();
  std::cout << std::endl;

  //test 4
  std::cout << "Test 4: move constructor" << std::endl;
  deque<std::string> dequeTest4(std::move(deque<std::string>({"11", "22", "33", "44", "55"})));
  std::cout << "Expected output: deque:11 22 33 44 55" << std::endl;
  std::cout << "Output: ";
  dequeTest4.print();
  std::cout << std::endl;

  //test 5
  std::cout << "Test 5: copy operator" << std::endl;
  deque<std::string> dequeTest5{ "1", "2" };
  dequeTest5 = dequeTest4;
  std::cout << "Expected output: deque:11 22 33 44 55" << std::endl;
  std::cout << "Output: ";
  dequeTest5.print();
  std::cout << "Deque from which we move data after move(must be the same): ";
  dequeTest4.print();
  std::cout << std::endl;

  //test 6
  std::cout << "Test 6: move operator" << std::endl;
  deque<std::string> dequeTest6{ "1", "2" };
  dequeTest6 = std::move(deque<std::string>{ "3", "4" });
  std::cout << "Expected output: deque:3 4" << std::endl;
  std::cout << "Output: ";
  dequeTest6.print();
  std::cout << std::endl;

  //test 7
  std::cout << "Test 7: push back with copy" << std::endl;
  std::string dataTest1 = "5";
  dequeTest6.pushBack(dataTest1);
  std::cout << "Expected output: deque:3 4 5" << std::endl;
  std::cout << "Output: ";
  dequeTest6.print();
  std::cout << std::endl;

  //test 8
  std::cout << "Test 8: push back with move" << std::endl;
  dequeTest6.pushBack(std::move(dataTest1));
  std::cout << "Expected output: deque:3 4 5 5" << std::endl;
  std::cout << "Output: ";
  dequeTest6.print();
  std::cout << "Data from variable that we moved(must be empty): ";
  std::cout << dataTest1;
  std::cout << std::endl;

  //test 9
  std::cout << "Test 9: push front with copy" << std::endl;
  std::string dataTest2 = "1";
  dequeTest6.pushFront(dataTest2);
  std::cout << "Expected output: deque:1 3 4 5 5" << std::endl;
  std::cout << "Output: ";
  dequeTest6.print();
  std::cout << std::endl;

  //test 10
  std::cout << "Test 10: push front with move" << std::endl;
  dequeTest6.pushFront(std::move(dataTest2));
  std::cout << "Expected output: deque:1 1 3 4 5 5" << std::endl;
  std::cout << "Output: ";
  dequeTest6.print();
  std::cout << "Data from variable that we moved(must be empty): ";
  std::cout << dataTest2;
  std::cout << std::endl << std::endl;

  //test 11
  std::cout << "Test 11: peek from back with pop" << std::endl;
  std::cout << "Expected output: 5" << std::endl;
  std::cout << "Output: " << dequeTest6.peekBack() << std::endl;
  dequeTest6.popBack();
  std::cout << "Expected deque after pop: deque:1 1 3 4 5" << std::endl;
  std::cout << "Output: ";
  dequeTest6.print();
  std::cout << std::endl;

  //test 12
  std::cout << "Test 12: peek from front with pop" << std::endl;
  std::cout << "Expected output: 1" << std::endl;
  std::cout << "Output: " << dequeTest6.peekFront() << std::endl;
  dequeTest6.popFront();
  std::cout << "Expected deque after pop: deque:1 3 4 5" << std::endl;
  std::cout << "Output: ";
  dequeTest6.print();
  std::cout << std::endl;

  //test 13
  std::cout << "Test 13: += with copy" << std::endl;
  dequeTest6 += dequeTest5;
  std::cout << "Expected output: deque:1 3 4 5 11 22 33 44 55" << std::endl;
  std::cout << "Output: ";
  dequeTest6.print();
  std::cout << std::endl;

  //test 14
  std::cout << "Test 14: += with move" << std::endl;
  dequeTest6 += std::move(dequeTest5);
  std::cout << "Expected output: deque:1 3 4 5 11 22 33 44 55 11 22 33 44 55" << std::endl;
  std::cout << "Output: ";
  dequeTest6.print();
  std::cout << "Data from variable that we moved(must be empty): ";
  dequeTest5.print();
  std::cout << std::endl << std::endl;

  //test 15
  std::cout << "Test 15: size of deque" << std::endl;
  std::cout << "Expected output:14" << std::endl;
  std::cout << "Output:";
  std::cout <<dequeTest6.size() << std::endl << std::endl;

  //test 16
  std::cout << "Test 16: isEmpty" << std::endl;
  std::cout << "Expected output:0" << std::endl;
  std::cout << "Output:";
  std::cout << dequeTest6.isEmpty() << std::endl << std::endl;

  //test 17
  std::cout << "Test 17: destroy" << std::endl;
  dequeTest6.destroy();
  std::cout << "Expected output:1" << std::endl;
  std::cout << "Output:";
  std::cout << dequeTest6.isEmpty() << std::endl << std::endl;

  return 0;

 _CrtDumpMemoryLeaks();
}