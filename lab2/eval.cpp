#include "eval.h"


evaluator::~evaluator(void) {

  while (!countStack.empty()) {
    auto* off = countStack.top();
    countStack.pop();
    delete off;
  }

}
double evaluator::evaluate(std::queue<token*>& queueInRPN) {

  token* tok;
  while (!queueInRPN.empty()) {
    //get element from queue
    tok = queueInRPN.front();
    queueInRPN.pop();
    token* token1, * token2 = nullptr;
    function* fun;
    switch (tok->type) {
      case tokenType::TOK_NUM:
        countStack.push(tok);//if number = > put it in stack
        break;
      case tokenType::TOK_FUNC:
      case tokenType::TOK_OP:
        if(tok->type == tokenType::TOK_FUNC)
          fun = ((tokenFunc*)tok)->func;
        else
          fun = ((tokenOp*)tok)->func;
        if (fun == nullptr) {
          delete tok;
          throw std::exception("Unknown function");
        }
        switch (fun->getType()) {
          case functionType::UNARY:
            token1 = countStack.top();
            countStack.pop();
            try {
              ((tokenNum*)token1)->number = fun->execute(((tokenNum*)token1)->number, 0);
            }
            catch (const std::exception& exception) {
              delete token1;
              delete tok;
              throw exception;
            }
            countStack.push(token1);
            break;
          case functionType::BINARY:
            token1 = countStack.top();
            countStack.pop();
            token2 = countStack.top();
            countStack.pop();
            try {
              ((tokenNum*)token1)->number = fun->execute(((tokenNum*)token1)->number, ((tokenNum*)token2)->number);
            }
            catch (const std::exception& exception) {
              delete token2;
              delete token1;
              delete tok;
              throw exception;
            }
            delete token2;
            countStack.push(token1);
            break;
        }
        delete tok;
        break;
    }

  }


  if (countStack.size() != 1 || countStack.top()->type != tokenType::TOK_NUM)
    throw std::exception("error in counting of expression");

  return ((tokenNum*)countStack.top())->number;

}