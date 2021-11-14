#include "function.h"

function::function(std::string functionName, functionType functionType, std::function<double(double, double)> func) {

  this->name = functionName;
  this->type = functionType;
  this->func = func;

}

double function::execute(double firstNumber, double secondNumber) {

  double result;
  try {
    result = this->func(firstNumber, secondNumber);
  }
  catch (const std::exception& exception) {
    throw exception;
  }
  return result;

}

function* function::getFunctionByName(const std::vector<function*>& functions, const std::string& functionName) {

  function* fun = nullptr;
  for (auto& func : functions)
    if (func->getName() == functionName) {
      fun = func;
      break;
    }
  return fun;

}