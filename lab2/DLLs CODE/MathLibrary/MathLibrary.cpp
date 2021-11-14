// MathLibrary.cpp - Contains math function
#include "../../function.h"

#define MATH_API __declspec(dllexport)


std::vector<function*> functions;

// Get the position of the current value in the sequence.
extern "C" MATH_API std::vector<function*> & getFunctions(void) {

  function* functionFloor, * functionCeil;

  functionFloor = new function("floor", functionType::UNARY,
    [](double n1, double n2) -> double {
      return floor(n1);
    });
  functions.push_back(functionFloor);

  functionCeil = new function("ceil", functionType::UNARY,
    [](double n1, double n2) -> double {
      return ceil(n1);
    });
  functions.push_back(functionCeil);

  return functions;

};