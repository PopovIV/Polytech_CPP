#ifndef FUNCTION_H_INCLUDED__
#define FUNCTION_H_INCLUDED__

#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <functional>

/**
* @brief Function type enum to know hum many input arguments in function
*/
enum class functionType {
  UNARY, //one argument
  BINARY //two argument
};

/**
 * @brief function class
 * Class wrapper over functions for calculator
 */
class function {
private:
  /**
  * @brief function name
  */
  std::string name;
  /**
  * @brief function type
  */
  functionType type;
  /**
  * @brief function itself
  */
  std::function<double(double, double)> func;
public:

  /**
  * @brief static method to find function in vector
  * @param[in] functions is vector of functions
  * @param[in] functionName is the name of function to find
  * @return function if it exists in the vector or nullptr otherwise
  */
  static function* getFunctionByName(const std::vector<function*>& functions, const std::string& functionName);

  /**
  * @brief constructor
  * @param[in] functionName is the name of function
  * @param[in] functionType is the function type
  * @param[in] func is function itself
  */
  function(std::string functionName, functionType functionType, std::function<double(double, double)> func);

  /**
  * @brief method execute function
  * @param[in] firstNumber is first argument of function
  * @param[in] secondNumber is second argument of function(may be put to zero, if function type is UNARY)
  * @return result of function
  */
  double execute(double firstNumber, double secondNumber);

  /**
  * @brief getter of function type
  * @return function type
  */
  functionType getType(void) { return type; };

  /**
  * @brief getter of function name
  * @return function name
  */
  const std::string& getName(void) { return name; };

};


#endif