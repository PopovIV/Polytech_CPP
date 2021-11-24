#include "Wrapper.h"

int Wrapper::execute(const std::map<std::string, int>& argumentsMap) {

  if (isInit == false)
    throw std::exception("ERROR: function with that wrapper is invalid");

  //create vector from map
  std::vector<int> argumentsVector;
  if(this->argumentsMap.first.size() != argumentsMap.size())
    throw std::exception("ERROR: invalid arguments");
  for (auto& elem : this->argumentsMap.first) {
    auto& arg = argumentsMap.find(elem);
    if (arg == argumentsMap.end())
       throw std::exception("ERROR: unknown argument");
    argumentsVector.push_back(arg->second);
  }


  int result;
  try {
    result = function(argumentsVector);
  }
  catch (std::exception& exception) {
    throw exception;
  }

  return result;

}