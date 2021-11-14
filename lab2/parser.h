#ifndef PARSER_H_INCLUDED__
#define PARSER_H_INCLUDED__

#pragma once
#include"token.h"
#include <stack>

/**
* @brief Priority type enum for priority of operations
* Smaller number in name => higher the priority
*/
enum class priority {
  TOP = 6,
  FIRST = 5,
  SECOND = 4,
  THIRD = 3,
  FOURTH = 2,
  FIFTH = 1,
  SIXTH = 0,
  IMPOSSIBLE = 1984
};

/**
* @brief parser class
* Main function of parser is to turn a token queue into token stack in Reverse Polish notation
*/
class parser {
private:
  /**
  * @brief two global stacks of tokens for parsering
  */
  std::stack<token*> stack1, stack2;
  /**
  * @brief variable of token's queue in reverse polish notation
  */
  std::queue<token*> queueInRPN;

  /**
  * @brief method to get priority of operation
  * @param[in] token of operation of function
  * @return priority of operation
  */
  priority getPriority(token* op);

  /**
  * @brief method to compare priority of operations or functions
  * @param[in] tok1 - first token to compare
  * @param[in] tok2 - second token to compare
  * @return true if tok1's priority > tok2's priority
  */
  bool checkAssoc(token* tok1, token* tok2);

  /**
  * @brief method to send operator to different stack
  * @param[in] tok - token to compare to
  */
  void dropOppers(token* tok);

  /**
  * @brief method for debug to see what tokens there are in the queue
  */
  void printQueue(void);
public:

  /**
  * @brief default constructor
  */
  parser(void) { };

  /**
  * @brief function to turn a token queue into token stack in Reverse Polish notation
  * @param[in] expression is a token queue that we turn into token stack in Reverse Polish notation
  * @param[in] functions is vector of loaded functions(needed here to change - to @)
  * @return token queue in Reverse Polish notation
  */
  void parseToRPN(std::queue<token*>& queueOfTokens, const std::vector<function*>& functions);

  /**
  * @brief method to get resulting queue in Reverse Polish notation
  * @return reference on token queue in Reverse Polish notation
  */
  std::queue<token*>& getQueue(void) { return queueInRPN; };

  /**
  * @brief default destructor
  */
  ~parser(void);

};

#endif