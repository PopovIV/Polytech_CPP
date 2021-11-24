#ifndef ENGINE_H_INCLUDED__
#define ENGINE_H_INCLUDED__

#pragma once

#include "Wrapper.h"
/**
 * @mainpage Introduction
  Implementation of encapsulation of methods of a class of arbitrary signature 
 * @see Wrapper, Engine
*/

/**
 * @brief Engine class
 * Main class that executes methods of other classes
 * @see Wrapper
 */
class Engine {
private:
  /**
  * @brief map of commands
  * Consists of pointers on Wrappers by name
  */
 std::map<std::string, Wrapper*> commands;

public:

  /**
  * @brief default constructor
  */
  Engine(void) = default;

  /**
  * @brief default destructor
  */
  ~Engine(void) = default;

  /**
  * @brief method to register command in Engine instance
  * @param[in] wrapper - pointer on wrapper instance
  * @param[in] commandName - name of command 
  */
  void register_command(Wrapper* wrapper, const std::string& commandName);

  /**
  * @brief method to execute method in Engine instance by its name
  * @param[in] commandName - name of command
  * @param[in] args - map of arguments and their names
  * @return int - result of command
  */
  int execute(const std::string& commandName, const std::map<std::string, int>& args);

};

#endif