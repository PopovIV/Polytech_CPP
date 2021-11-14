#ifndef _CRTDBG_MAP_ALLOC
#define _CRTDBG_MAP_ALLOC
#endif
#include <crtdbg.h>
#include<locale.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include "calculator.h"

//uncomment if want to run test 
//#define TEST

void work(void) {

  #ifdef TEST
  //open file with tests and output stream
  std::ifstream expressions("expressions.txt");
  if (!expressions.is_open()) {
    std::cout << "ERROR: can not open test file" << std::endl;
    return;
  }

  std::ofstream out("out.txt");
  if (!out.is_open()) {
    std::cout << "ERROR: can not open output file" << std::endl;
    return;
  }

  std::vector<std::string> ans;
  HANDLE hwnd = GetStdHandle(STD_OUTPUT_HANDLE);
  #endif

  std::string str;
  calculator calc;
  double result = 0;
  try {
    calc.init();
  }
  catch (const std::exception& exception) {
    #ifdef TEST
    out << "ERROR: " << exception.what() << std::endl;
    #else
    std::cout << "ERROR: " << exception.what() << std::endl;
    #endif
  }

  #ifdef TEST
  while (getline(expressions, str)) {
  #else
  while (getline(std::cin, str)) {
  #endif

    //count spaces
    int i = 0;
    for (i = 0; i < (int)str.length(); i++) {
      if (!isspace(str[i]))
        break;
    }
    //if empty string => send to output
    if (i == str.length()) {
      #ifdef TEST
      ans.push_back("");
      out << str << std::endl;
      #else
      std::cout << str << std::endl;
      #endif
      continue;
    }

    //if there is somithing to calculate => send to calculator class
    //realization of that
    try {
      result = calc.calculate(str);
    }
    catch (const std::exception& exception) {
      #ifdef TEST
      ans.push_back("ERROR:");
      out << str << " == " << "ERROR: " <<  exception.what() << std::endl;
      #else
      std::cout << str << " == " << "ERROR: " << exception.what() << std::endl;
      #endif
      continue;
    }
    #ifdef TEST
    //print result
    std::stringstream ss;
    ss << result;
    ans.push_back(ss.str());
    ss.clear();

    out << str << " == " << result << std::endl;
    #else
    std::cout << str << " == " << result << std::endl;
    #endif

  }
  
  #ifdef TEST
  //open file with answers
  std::ifstream answers("answers.txt");
  if (!answers.is_open()) {
    std::cout << "ERROR: can not open answers file" << std::endl;
    return;
  }
  int i = 0;
  while (std::getline(answers, str)) {
    if (str == ans[i++]) {
      SetConsoleTextAttribute(hwnd, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
      std::cout << "Test " << i << " OK!" << std::endl;
    }
    else {
      SetConsoleTextAttribute(hwnd, FOREGROUND_RED | FOREGROUND_INTENSITY);
      std::cout << "Test " << i << " NOT OK!" << std::endl;
    }
  }
  SetConsoleTextAttribute(hwnd, FOREGROUND_INTENSITY);

  //close files
  expressions.close();
  out.close();
  answers.close();
  #endif

}

int main(int arg, char* argv[]) {

  setlocale(LC_ALL, "Russian");

  work();

  _CrtDumpMemoryLeaks();
  return 0;

}