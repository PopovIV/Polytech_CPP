#include "Engine.h"

void Engine::register_command(Wrapper* wrapper,const std::string& commandName) {

  //check wrapper for nullptr
  if (wrapper == nullptr)
    return;
  //check if that command is already in the map
  if (commands.find(commandName) != commands.end())
    return;
  //insert new command
  commands[commandName] = wrapper;

}

int Engine::execute(const std::string& commandName, const std::map<std::string, int>& args) {

  auto& argWithName = commands.find(commandName);
  if (argWithName == commands.end())
    throw std::exception("ERROR: No such command in Engine");

  int result;
  try {
    result = argWithName->second->execute(args);
  }
  catch (std::exception& exception) {
    throw exception;
  }

  return result;

}