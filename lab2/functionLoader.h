#ifndef FUNCTIONLOADER_H_INCLUDED__
#define FUNCTIONLOADER_H_INCLUDED__

#pragma once

#include "function.h"
#include <filesystem>
#include <Windows.h>

using functionPointer = std::vector<function*>& (*)(void);

/**
 * @brief function class
 * Class that load basic and dll function to calculator
 */
class functionLoader {
private:
  /**
  * @brief path to folder with dlls
  */
  const std::string pathToDLLs = "DLLs/";
  /**
  * @brief vector of functions from dll
  */
  std::vector<function*> functions;

  /**
  * @brief vector of dlls handlers
  */
  std::vector<HMODULE> dllsHandlers;

  /**
  * @brief private method to load basic functions
  */
  void loadBasic(void);
  /**
  * @brief private method to load dll functions
  */
  void loadDLL(void);
public:
  /**
  * @brief default constructor
  */
  functionLoader(void) {};

  /**
  * @brief method to create vector of loaded functions
  */
  void createFunctionVector(void);

  /**
  * @brief method to get vector of loaded functions
  * @return reference on function vector
  */
  std::vector<function*>& getFunctionVector(void) { return functions; };

  /**
  * @brief default destructor
  */
  ~functionLoader(void);

};

#endif