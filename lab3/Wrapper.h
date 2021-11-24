#ifndef WRAPPER_H_INCLUDED__
#define WRAPPER_H_INCLUDED__

#pragma once
#include <iostream>
#include <map>
#include <string>
#include <functional>
#include <vector>

/**
 * @brief Wrapper class
 * Main class-wrapper over some other class method
 * @see Engine
 */
class Wrapper {
private:
 /**
 * @brief pair of two vectors of arguments and their name
 */
 std::pair<std::vector<std::string>, std::vector<int>> argumentsMap;
 /**
 * @brief variable to store method function
 */
 std::function<int(std::vector<int>& argumentsVector)> function;

 /**
 * @brief boolean variable that that is used to 
 * show if construction of Wrapper was succesful
 */
 bool isInit = false;

 /**
 * @brief default constructor is banned
 */
 Wrapper(void) = delete;

 /**
 * @brief template method to call some class method
 * @param[in] subject - pointer to some class
 * @param[in] function - some method of subject
 * @param[in] argumentsVector - vector of arguments for function
 * @param[in] std::index_sequence<Indexes...> - sequence of integers to know indexes of arguments 
 * @return int - result of method
 */
 template<typename Subject, typename Function, size_t... Indexes>
 static int callFunction(Subject* subject, Function function, const std::vector<int> argumentsVector, std::index_sequence<Indexes...>) {
   return (subject->*function)(argumentsVector[Indexes]...);
 }


public:

  /**
  * @brief default deconstructor
  */
  ~Wrapper(void) = default;

  /**
  * @brief temlate Wrapper constructor
  * @param[in] subject - pointer to some class
  * @param[in] int (Subject::* subjectMethod)(Args...) - pointer to some subject's method
  * @param[in] argumentsMap - arguments names and their initial values
  */
  template<typename Subject, typename... Args>
  Wrapper(Subject* subject, int (Subject::* subjectMethod)(Args...), const std::map<std::string, int>& argumentsMap) noexcept {

    if (subject == nullptr || subjectMethod == nullptr)
      return;

    //parse to our map
    for (auto& elem : argumentsMap) {
      this->argumentsMap.first.push_back(elem.first);
      this->argumentsMap.second.push_back(elem.second);
    }
    //initialize function
    function = [subject, subjectMethod](const std::vector<int>& argumentsVector) {
      if (sizeof...(Args) != argumentsVector.size())
        throw std::exception("ERROR: invalid number of arguments");
      return callFunction(subject, subjectMethod, argumentsVector, std::make_index_sequence<sizeof...(Args)>{});
    };

    //initialize Wrapper
    isInit = true;

  }

  /**
 * @brief method to execute command in Wrapper
 * @param[in] argumentsMap - map of arguments with new values and their names
 * @return int - result of command
 */
  int execute(const std::map<std::string, int>& argumentsMap);

};

#endif