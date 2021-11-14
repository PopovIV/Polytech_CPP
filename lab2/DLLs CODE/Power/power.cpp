// power.cpp - Contains power function
#include "../../function.h"

#define POWER_API __declspec(dllexport)

std::vector<function*> functions;

// Get the position of the current value in the sequence.
extern "C" POWER_API std::vector<function*>&  getFunctions(void) {

  function* functionPower;

  functionPower = new function("^", functionType::BINARY,
    [](double n1, double n2) -> double {
      return std::pow(n2,n1); 
    });
  functions.push_back(functionPower);

  return functions;

};