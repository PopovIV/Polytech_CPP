#include "Engine.h"

//class for tests
class Subject{
public:
  int f3(int a, int b) { return a - b; }

};

//function for tests
void test(void) {

  Subject subj;

  Wrapper wrap(&subj, &Subject::f3, { {"arg1", 0 }, {"arg2", 0 } });
  Engine engine;
  engine.register_command(&wrap, "command1");

  //example of work
  std::cout << "Example of normal work:" << std::endl;
  try{
    std::cout << engine.execute("command1", { {"arg1", 4}, {"arg2", 5}}) << std::endl;
  }
  catch (std::exception& ex){
    std::cout << ex.what() << std::endl;
  }
  //inverted arguments
  std::cout << "If inverted arguments:" << std::endl;
  try {
    std::cout << engine.execute("command1", { {"arg2", 5}, {"arg1", 4} }) << std::endl;
  }
  catch (std::exception& ex) {
    std::cout << ex.what() << std::endl;
  }
  //too many arguments
  std::cout << "If too many arguments:" << std::endl;
  try {
    std::cout << engine.execute("command1", { {"arg2", 5}, {"arg1", 4}, {"arg3", 5} }) << std::endl;
  }
  catch (std::exception& ex) {
    std::cout << ex.what() << std::endl;
  }
  //unknown argument
  std::cout << "If unknown argument:" << std::endl;
  try {
    std::cout << engine.execute("command1", { {"arg3", 5}, {"arg1", 4}}) << std::endl;
  }
  catch (std::exception& ex) {
    std::cout << ex.what() << std::endl;
  }
  //not enough arguments
  std::cout << "If not enough arguments:" << std::endl;
  try {
    std::cout << engine.execute("command1", { {"arg1", 4} }) << std::endl;
  }
  catch (std::exception& ex) {
    std::cout << ex.what() << std::endl;
  }
  //unknown command
  std::cout << "If unknown command:" << std::endl;
  try {
    std::cout << engine.execute("command", { {"arg1", 4} }) << std::endl;
  }
  catch (std::exception& ex) {
    std::cout << ex.what() << std::endl;
  }

}

int main(){

  test();

  return 0;

}