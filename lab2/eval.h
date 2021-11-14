#ifndef EVAL_H_INCLUDED__
#define EVAL_H_INCLUDED__

#pragma once

#include "parser.h"

/**
* @brief evaluator class
* Main function of evaluator is to count expression in queue in RPN
*/
class evaluator {
private:
  /**
  * @brief stack of tokens that are used in counting the expression from tokens
  */
  std::stack<token*> countStack;
public:

  /**
  * @brief default constructor
  */
  evaluator(void) { };

  /**
  * @brief function to calculate expression from queue of tokens in Reverse Polish notation
  * @param[in] queueInRPN is a token queue that we want to evaluate
  * @return result of calculation
  */
  double evaluate(std::queue<token*>& queueInRPN);

  /**
  * @brief default destructor
  */
  ~evaluator(void);

};

#endif