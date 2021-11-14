#ifndef CALCULATOR_H_INCLUDED__
#define CALCULATOR_H_INCLUDED__

#pragma once

#include "eval.h"
#include "functionLoader.h"

/**
 * @mainpage Introduction
  Implementation of calculator built on Reverse Polish notation in C++.
* @see calculator
*/

/**
 * @brief calculator class
 * Main class that integrate tokenizer, parser and evaluator
 * @see token, parser, eval
 */
class calculator {
public:
  /**
  * @brief default constructor
  */
  calculator(void) { isInit = false; };

  /**
  * @brief loader of functions
  */
  functionLoader loader;

  /**
  * @brief initializer of calculator
  */
  void init(void);

  /**
  * @brief condition of calculator
  */
  bool isInit;

  /**
  * @brief main method that calculates expression in string 
  * @param[in] expression is a constant string that we want to calculate
  * @return result of expression
  */
  double calculate(std::string expression);

};

#endif