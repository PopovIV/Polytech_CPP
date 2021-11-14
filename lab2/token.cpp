#include "token.h"

//class tokenOp constructor
tokenOp::tokenOp(void) {

  func = nullptr;
  sign = ' ';
  type = tokenType::TOK_OP;

}

//class tokenFunc constructor
tokenFunc::tokenFunc(void) {

  func = nullptr;
  type = tokenType::TOK_FUNC;

}

//class tokenNum constructor
tokenNum::tokenNum(void) {

  number = 0;
  type = tokenType::TOK_NUM;

}

tokenizer::~tokenizer(void) {

  while (!queueOfTokens.empty()) {
    auto* off = queueOfTokens.front();
    queueOfTokens.pop();
    delete off;
  }

}

void tokenizer::printQueue(void) {

  std::queue<token*> tmpQueue;
  while (!queueOfTokens.empty()) {
    auto* off = queueOfTokens.front();
    tmpQueue.push(off);
    queueOfTokens.pop();
    switch (off->type) {
      case tokenType::TOK_FUNC:
        std::cout << "Function: " << ((tokenFunc*)(off))->func->getName() << std::endl;
        break;
      case tokenType::TOK_OP:
        std::cout << "Operation: " << ((tokenOp*)(off))->func->getName() << std::endl;
        break;
      case tokenType::TOK_NUM:
        std::cout << "Number: " << ((tokenNum*)(off))->number << std::endl;
        break;
    }
  }

  //push back to queue
  while (!tmpQueue.empty()) {
    queueOfTokens.push(tmpQueue.front());
    tmpQueue.pop();
  }

}

void tokenizer::tokenize(const std::string& expression, const std::vector<function*>& functions) {
  
  //iterate over all elements of the string
  int pos = 0;
  while (pos < (int)expression.length()) {

    //if it is a space
    if (isspace(expression[pos])) {
      pos++;
      continue;
    }
    //if it is something that looks like function
    std::string functionName = "";
    while ((expression[pos] >= 'A' && expression[pos] <= 'Z') || (expression[pos] >= 'a' && expression[pos] <= 'z') && pos < (int)expression.length())
      functionName += expression[pos++];
    if (functionName != "") {
      //check if our function is e or pi
      if (functionName == "pi") {
        tokenNum* tokNum;
        try {
          tokNum = new tokenNum;
        }
        catch (const std::bad_alloc) {
          throw std::exception("Not enough memory for allocation");
        }
        tokNum->number = PI;
        queueOfTokens.push(tokNum);
        continue;
      }
      if (functionName == "e") {
        tokenNum* tokNum;
        try {
          tokNum = new tokenNum;
        }
        catch (const std::bad_alloc) {
          throw std::exception("Not enough memory for allocation");
        }
        tokNum->number = E;
        queueOfTokens.push(tokNum);
        continue;
      }

      //check if that function is exsist in function vector
      function* fun = function::getFunctionByName(functions, functionName);
      if (fun == nullptr)
        throw std::exception("Unknown function");

      //if function
      tokenFunc* tokFunc;
      try {
        tokFunc = new tokenFunc;
      }
      catch (const std::bad_alloc) {
        throw std::exception("Not enough memory for allocation");
      }
      tokFunc->func = fun;
      queueOfTokens.push(tokFunc);
      continue;
    }

    char *startStr, *endStr;
    std::string cutStr;
    function* fun;
    switch (expression[pos]){
      case '+':
      case '-':
      case '/':
      case '*':
      case '^':
      case ')':
      case '(':
        //if it is a operation

        fun = function::getFunctionByName(functions, std::string{expression[pos]});
        if (fun == nullptr)
          throw std::exception("Unknown function");

        tokenOp* tokOp;
        try {
          tokOp = new tokenOp;
        }
        catch (const std::bad_alloc) {
          throw std::exception("Not enough memory for allocation");
        }

        tokOp->func = fun;
        tokOp->sign = expression[pos++];
        queueOfTokens.push(tokOp);
        break;
      case '1':
      case '2':
      case '3':
      case '4':
      case '5':
      case '6':
      case '7':
      case '8':
      case '9':
      case '0':
      case '.':
        //if it is a number
        tokenNum* tokNum;
        try {
          tokNum = new tokenNum;
        }
        catch (const std::bad_alloc) {
          throw std::exception("Not enough memory for allocation");
        }
        //convert number from string
        cutStr = expression.substr(pos);//to avoid warning we extend lifetime of object by giving it a name
        //fix problem with ,/.
        for (int i = 0; i < (int)cutStr.length(); i++) {
          if(cutStr[i] == '.'){
            cutStr[i] = ',';
            break;
          }
        }
        startStr = (char*)cutStr.c_str();



        tokNum->number = std::strtod(startStr, &endStr);
        //check if range error
        if(errno == ERANGE)
          throw std::exception("Range error");
        //if conversion wasn't performed
        if(tokNum->number ==0 && endStr == startStr)
          throw std::exception("Error with conversion into number from string");

        //find shift in str
        pos += endStr - startStr;
        startStr = nullptr;
        queueOfTokens.push(tokNum);
        break;
      
      default:
        throw std::exception("Unknown symbol in expression");
        break;
    }
  }

  //debug
  //printQueue()//

}