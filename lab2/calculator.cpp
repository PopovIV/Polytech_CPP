#include "calculator.h"
#include<string>

void calculator::init(void) {

  try{ 
    loader.createFunctionVector();
  }
  catch (const std::exception& exception) {
    throw exception;
  }
  isInit = true;

}

double calculator::calculate(std::string expression) {

  if (!isInit)
    throw std::exception("Calculator wasn't initialized");

  double result = 0;
  tokenizer tokens;
  parser parsers;
  evaluator eval;

  //tokenize
  try{
    tokens.tokenize(expression, loader.getFunctionVector());
  }
  catch (const std::exception& exception) {
    throw exception;
  }
  //translate to reverse polish notation
  try {
    parsers.parseToRPN(tokens.getQueue(), loader.getFunctionVector());
  }
  catch (const std::exception& exception) {
    throw exception;
  }
  //calculate
  try {
    result = eval.evaluate(parsers.getQueue());
  }
  catch (const std::exception& exception) {
    throw exception;
  }

  return result;

}