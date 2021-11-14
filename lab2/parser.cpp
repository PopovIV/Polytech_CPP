#include "parser.h"


priority parser::getPriority(token* op) {

  tokenOp* tokOp;
  switch (op->type) {
    case tokenType::TOK_FUNC:
      return priority::TOP;
    case tokenType::TOK_OP:
      tokOp = (tokenOp*)op;
      switch (tokOp->sign) {
        case '(':
          return priority::SIXTH;
        case ')':
          return priority::FIFTH;
        case '+':
        case '-':
         return priority::FOURTH;
        case '*':
        case '/':
         return priority::THIRD;
        case '@'://unary minus
          return priority::SECOND;
        case '^':
          return priority::FIRST;
      }
  }

  return priority::IMPOSSIBLE;

}

bool parser::checkAssoc(token* tok1, token* tok2) {

  priority priorityToken1 = getPriority(tok1);
  priority priorityToken2 = getPriority(tok2);
  //check for error
  if (priorityToken1 == priority::IMPOSSIBLE || priorityToken2 == priority::IMPOSSIBLE)
    throw std::exception("Unknown operation in parser");
  //to support right assoc
  if (((tokenOp*)tok1)->sign == '^' && priorityToken1 == priorityToken2)
    return priorityToken1 > priorityToken2;
  return priorityToken1 >= priorityToken2;

}

void parser::dropOppers(token* tok) {

  bool check;
  token* tmpTok;

  while (!stack2.empty()) {
    try{
      check = checkAssoc(stack2.top(), tok);
    }
    catch (const std::exception& exception) {
      throw exception;
    }
    if (!check)
      return;
    tmpTok = stack2.top();
    stack2.pop();
    stack1.push(tmpTok);
  }

}

void parser::printQueue(void) {

  std::queue<token*> tmpQueue;
  while (!queueInRPN.empty()) {
    auto* off = queueInRPN.front();
    tmpQueue.push(off);
    queueInRPN.pop();
    switch (off->type) {
      case tokenType::TOK_FUNC:
        std::cout << ((tokenFunc*)(off))->func->getName() << " ";
        break;
      case tokenType::TOK_OP:
        std::cout << ((tokenOp*)(off))->func->getName() << " ";
        break;
      case tokenType::TOK_NUM:
        std::cout << ((tokenNum*)(off))->number << " ";
        break;
    }
  }
  std::cout << std::endl;

  //push back to queue
  while (!tmpQueue.empty()) {
    queueInRPN.push(tmpQueue.front());
    tmpQueue.pop();
  }

}

parser::~parser(void){

 //clear queue
  while (!queueInRPN.empty()) {
    auto* off = queueInRPN.front();
    queueInRPN.pop();
    delete off;
  }
  //clear stacks
  while (!stack1.empty()) {
    auto* off = stack1.top();
    stack1.pop();
    delete off;
  }
  while (!stack2.empty()) {
    auto* off = stack2.top();
    stack2.pop();
    delete off;
  }

}

void parser::parseToRPN(std::queue<token*>& queueOfTokens, const std::vector<function*>& functions) {

  token* tok = nullptr;
  /**
  * @brief state enum type for states of finite automata
  */
  enum class state {
    STATE_PREFIX,
    STATE_SUFFIX,
    STATE_DONE,
    STATE_END
  };

  state automataState = state::STATE_PREFIX;

  while (automataState != state::STATE_END) {
    if (automataState <= state::STATE_SUFFIX)
      if (queueOfTokens.empty())
        if (automataState == state::STATE_SUFFIX)
          automataState = state::STATE_DONE;
        else {
          throw std::exception("Unexpected end-of-expression");
        }
      else {
        tok = queueOfTokens.front();
        queueOfTokens.pop();
      }
    switch (automataState) {
      case state::STATE_PREFIX:
        switch (tok->type) {
          case tokenType::TOK_NUM:
            stack1.push(tok);
            automataState = state::STATE_SUFFIX;
            continue;
          case tokenType::TOK_OP:
            if (((tokenOp*)tok)->sign == '(') {
              stack2.push(tok);
              break;
            }
            if (((tokenOp*)tok)->sign == '-') {//if unary minus
              ((tokenOp*)tok)->sign = '@';
              ((tokenOp*)tok)->func = function::getFunctionByName(functions, "@");
              stack2.push(tok);
              break;
            }
            //if not prefix operation
            delete tok;
            throw std::exception("( or number was expected");
          case tokenType::TOK_FUNC:
            stack2.push(tok);
            break;
        }
        break;
      case state::STATE_SUFFIX:
        switch (tok->type) {
          case tokenType::TOK_OP:
            try {
              dropOppers(tok);
            }
            catch (const std::exception& exception) {
              delete tok;
              throw exception;
            }
            if (((tokenOp*)tok)->sign == ')') {
              if (stack2.empty()) {
                delete tok;
                throw std::exception("Error with brackets");
              }
              else {
                delete tok;
                tok = stack2.top();
                stack2.pop();
                delete tok;
              }
              break;
            }
            else {
              stack2.push(tok);
              automataState = state::STATE_PREFIX;
              break;
            }
          //if not postfix operation
          default:
            delete tok;
            throw std::exception(") or operation was expected");
        }
        break;
      case state::STATE_DONE:
        //create temporary variable
        tokenOp* tmpToken;
        try {
          tmpToken = new tokenOp;
        }
        catch (const std::bad_alloc) {
          delete tok;
          throw std::exception("Not enough memory for allocation");
        }
        tmpToken->sign = ')';
        try {
          dropOppers(tmpToken);
        }
        catch (std::exception& exception) {
          delete tok;
          throw exception;
        }
        if (!stack2.empty()) {
          delete tmpToken;
          throw std::exception("Error with brackets");
        }
        while (!stack1.empty()) {
          tok = stack1.top();
          stack1.pop();
          stack2.push(tok);
        }
        delete tmpToken;
        automataState = state::STATE_END;
    }
  }
  //send everything to queue
  while (!stack2.empty()) {
    tok = stack2.top();
    stack2.pop();
    queueInRPN.push(tok);
  }

  //debug 
  //printQueue();//

}