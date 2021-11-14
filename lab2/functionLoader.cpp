#include "functionLoader.h"

functionLoader::~functionLoader(void) {

  while (!functions.empty()) {
    auto* off = functions.back();
    functions.pop_back();
    delete off;
  }

  for (auto off : dllsHandlers)
    FreeLibrary(off);

}

void functionLoader::loadBasic(void) {

  function* functionPlus, * functionMinus, * functionMul, * functionDiv;
  function* functionUnarMinus, * functionLeftBrackets, * functionRightBrackets;

  //plus
  try{
    functionPlus = new function("+", functionType::BINARY,
      [](double n1, double n2) -> double {
        return n1 + n2;
      });
  }
  catch (const std::bad_alloc) {
    throw std::exception("Not enough memory for allocation");
  }
  functions.push_back(functionPlus);

  //minus
  try {
    functionMinus = new function("-", functionType::BINARY,
      [](double n1, double n2) -> double {
        return n2 - n1;
      });
  }
  catch (const std::bad_alloc) {
    throw std::exception("Not enough memory for allocation");
  }
  functions.push_back(functionMinus);

  //mul
  try {
    functionMul = new function("*", functionType::BINARY,
      [](double n1, double n2) -> double {
        return n1 * n2;
      });
  }
  catch (const std::bad_alloc) {
    throw std::exception("Not enough memory for allocation");
  }
  functions.push_back(functionMul);

  //div
  try {
    functionDiv = new function("/", functionType::BINARY,
      [](double n1, double n2) -> double {
        if (n1 == 0)
          throw std::exception("Division by zero");
        return n2 / n1;
      });
  }
  catch (const std::bad_alloc) {
    throw std::exception("Not enough memory for allocation");
  }
  functions.push_back(functionDiv);

  //unary minus
  try {
    functionUnarMinus = new function("@", functionType::UNARY,
      [](double n1, double n2) -> double {
        return -n1;
      });
  }
  catch (const std::bad_alloc) {
    throw std::exception("Not enough memory for allocation");
  }
  functions.push_back(functionUnarMinus);

  //left brackets
  try {
    functionLeftBrackets = new function("(", functionType::UNARY, nullptr);
  }
  catch (const std::bad_alloc) {
    throw std::exception("Not enough memory for allocation");
  }
  functions.push_back(functionLeftBrackets);

  //right brackets
  try {
    functionRightBrackets = new function(")", functionType::UNARY, nullptr);
  }
  catch (const std::bad_alloc) {
    throw std::exception("Not enough memory for allocation");
  }
  functions.push_back(functionRightBrackets);

}

void functionLoader::loadDLL(void) {

  //fill vector with path to files
  std::vector<std::filesystem::path> filePaths;
  for (auto& file : std::filesystem::directory_iterator(pathToDLLs))
    filePaths.push_back(file.path());

  //for each dll from vector load functions to vector of functions
  std::vector<function*> tmpFunctions;
  for (auto& file : filePaths) {
    //if it isn't a dll
    if (file.extension() != ".dll")
      continue;
    //try to open dll
    HMODULE dllAdress = LoadLibrary((LPCSTR)file.string().c_str());
    dllsHandlers.push_back(dllAdress);
    if (dllAdress == nullptr)
      continue;
    //get function from dll
    functionPointer getFunctions  = (functionPointer)GetProcAddress(dllAdress, "getFunctions");
    tmpFunctions = getFunctions();
    while (tmpFunctions.size() != 0) {
      functions.push_back(tmpFunctions.back());
      tmpFunctions.pop_back();
    }
  }

}

void functionLoader::createFunctionVector(void) {

  try {
    loadBasic();
  }
  catch (const std::exception& exception) {
    throw exception;
  }

  try {
    loadDLL();
  }
  catch (const std::exception& exception) {
    throw exception;
  }

}