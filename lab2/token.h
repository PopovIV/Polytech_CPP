#ifndef TOKEN_H_INCLUDED__
#define TOKEN_H_INCLUDED__

#pragma once

#include "function.h"
#include<queue>
#include<cstdlib>

#define PI 3.141592653589793
#define E 2.718281828459045

/**
* @brief Token type enum represents what type of char we met in the string
*/
enum class tokenType {
  TOK_OP,    // operation
  TOK_NUM ,  // number
  TOK_FUNC , // function
};

/**
* @brief Token class that only stores type of current token
*/
class token {
public:
  tokenType type;// Token type
};

/**
* @brief Operation token class that is inherited from token
*/
class tokenOp : public token {
public:
  function* func;//function
  char sign;     //sign of function
  /**
  * @brief Default constructor
  */
  tokenOp(void);

};

/**
* @brief Number token class that is inherited from token
*/
class tokenNum : public token {
public:
  double number;//value of number

  /**
  * @brief Default constructor
  */
  tokenNum(void);

};

/**
* @brief Function token class that is inherited from token
*/
class tokenFunc : public token {
public:
  function* func;//function

  /**
  * @brief Default constructor
  */
  tokenFunc(void);

};

/**
* @brief Tokenizer class
* Main function of tokenizer is to turn a expression string into a token queue
*/
class tokenizer {
private:

  /**
  * @brief variable of token's queue
  */
  std::queue<token*> queueOfTokens;

  /**
  * @brief method for debug to see what tokens there are in the queue
  */
  void printQueue(void);
public:
  /**
  * @brief default constructor
  */
  tokenizer(void) { };

  /**
  * @brief method to turn a string expression into a token queue
  * @param[in] expression is a constant string that we turn into token queue
  * @param[in] functions is vector of loaded functions
  * @return result - token queue
  */
  void tokenize(const std::string& expression, const std::vector<function*>& functions);

  /**
  * @brief method to get resulting token queue
  * @return reference on token queue
  */
  std::queue<token*>& getQueue(void) { return queueOfTokens; };

  /**
  * @brief default destructor
  */
  ~tokenizer(void);

};
#endif