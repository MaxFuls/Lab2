#include "/home/maxfuls/Programs/Lab2/src/Dialog/Dialog.h"
#include "/home/maxfuls/Programs/Lab2/src/LogicElement/LogicElement.h"
#include "/home/maxfuls/Programs/Lab2/src/Terminal/Terminal.h"
#include "/home/maxfuls/Programs/Lab2/src/Vector/Vector.h"
#include <iostream>
#include <string>
#include <exception>
#include <limits>
#include <string> 

namespace dialog {

int dialog(const char *msgs[], const int number_of_msgs) {

  for (int i{0}; i < number_of_msgs; i++) {

    std::puts(msgs[i]);
  }
  int alternative;

  alternative = NumInput<int>(0, number_of_msgs-1);
  return alternative;
}


// Terminals' dialog functions

int createFull(vector::Vector<terminal::Terminal> &terminals) {

  terminal::Terminal::Type type;
  int connections;
  terminal::Terminal::Signal signal;
  std::cout << "Enter type of terminal"<<std::endl<<"0.Output terminal"<<std::endl<<"1.Input terminal"<<std::endl;
  type = static_cast<terminal::Terminal::Type>(NumInput(0, 1));
  std::cout << "Enter number of connections"<<std::endl;
  if (type == terminal::Terminal::Type::INPUT) {
    std::cout << "Maximum number connections for this type is 1"<<std::endl;
    connections = NumInput<int>(0, 1);
  } else {
    std::cout << "Maximum number connections for this type is 3"<<std::endl;
    connections = NumInput<int>(0, 3);
  }
  if (type == terminal::Terminal::Type::INPUT && !connections) {
    std::cout << "For input terminal with 0 connections, type of signal is X"<<std::endl;
    signal = terminal::Terminal::Signal::X;
  } else {
    std::cout << "Enter state of signal"<<std::endl<<"0.Off"<<std::endl<<"1.On"<<std::endl<<"2.X"<<std::endl;
    signal = static_cast<terminal::Terminal::Signal>(NumInput<int>(0, 2));
  }
  try {
    terminals.pushback(terminal::Terminal(type, connections, signal, terminals.getSize() + 1));
    return 1;
  }
  catch (std::bad_alloc &ba) {
    std::cerr << "Not enough memory to create new terminal"<<std::endl;
    return 1;
  }
}
int createWithType(vector::Vector<terminal::Terminal> &terminals) {

  std::cout <<"Enter type of terminal"<<std::endl<<"0.Output terminal"<<std::endl<<"1.Input terminal"<<std::endl;
  terminal::Terminal::Type type = static_cast<terminal::Terminal::Type>(NumInput<int>(0, 1));
  try {
    terminals.pushback(terminal::Terminal(type, terminals.getSize() + 1));
    return 1;
  }
  catch (std::bad_alloc &ba) {
    std::cerr << "Not enough memory to create new terminal" << std::endl;
    return 1;
  }
}
int enter(vector::Vector<terminal::Terminal> &terminals) {

  if (terminals.getSize() == 0) {
    std::cout << "There are no terminals to enter" << std::endl;
    return 1;
  }
  std::cout << "Choose number of terminal you want to enter" << std::endl;
  for (int i{1}; i <= terminals.getSize(); ++i)
    std::cout << i<<" ";
  std::cout << std::endl;
  int number = dialog::NumInput<int>(1, terminals.getSize());
  terminals[number - 1].scan(std::cin);
  return 1;
}
int connect(vector::Vector<terminal::Terminal> &terminals) {

  if (!terminals.getSize() || terminals.getSize() == 1) {
    std::cout << "There are no terminals to connect"<<std::endl;
    return 1;
  }
  int firstTerminal;
  int secondTerminal;
  std::cout << "Choose terminals to connect" << std::endl;
  for (int i{1}; i <= terminals.getSize(); ++i)
    std::cout << i<<" ";
  std::cout << std::endl;
  std::cout << "Enter number of the first terminal" << std::endl;
  firstTerminal = NumInput<int>(0, terminals.getSize() + 1);
  std::cout << "Enter number of the second terminal" << std::endl;
  secondTerminal = NumInput<int>(0, terminals.getSize() + 1);
  try {
    terminals[firstTerminal - 1].connect(terminals[secondTerminal - 1]);
    return 1;
  }
  catch (const std::invalid_argument &ia) {
    std::cout << ia.what() << std::endl;
    return 1;
  }
}
int disconnect(vector::Vector<terminal::Terminal> &terminals) {

  if (!terminals.getSize() && terminals.getSize() == 1) {
    std::cout << "There are no terminals to disconnect"<<std::endl;
    return 1;
  }
  int firstTerminal;
  int secondTerminal;
  std::cout << "Choose terminals to disconnect" << std::endl;
  for (int i{1}; i <= terminals.getSize(); ++i)
    std::cout << i<<" ";
  std::cout << std::endl;
  std::cout << "Enter number of the first terminal" << std::endl;
  firstTerminal = NumInput<int>(0, terminals.getSize() + 1);
  std::cout << "Enter number of the second terminal" << std::endl;
  secondTerminal = NumInput<int>(0, terminals.getSize() + 1);
  try {
    terminals[firstTerminal - 1].disconnect(terminals[secondTerminal - 1]);
    return 1;
  }
  catch (const std::invalid_argument &ia) {
    std::cout << ia.what() << std::endl;
    return 1;
  }
}
int print(vector::Vector<terminal::Terminal> &terminals) {

  int i{0};
  if (terminals.getSize() == 0) {
    std::cout << "No terminals" << std::endl;
    return 1;
  }
  while (i < terminals.getSize()) {

    std::cout<<terminals[i];
    ++i;
  }
  return 1;
}

// Logic elements' dialog functions

int createWithNumber(vector::Vector<logicElement::LogicElement> &logicElements) {

  int numInput;
  int numOutput;
  std::cout << "Enter number of input terminals" << std::endl;
  numInput = NumInput<int>(0, std::numeric_limits<int>::max());
  std::cout << "Enter number of output terminals" << std::endl;
  numOutput = NumInput<int>(0, std::numeric_limits<int>::max());
  try{
      logicElements.pushback(logicElement::LogicElement(numInput, numOutput, logicElements.getSize() + 1));
      return  1;
  }
  catch(std::bad_alloc& ba){
      std::cerr<<"Not enough memory to create new logic element"<<std::endl;
      return 1;
  }
}
int createWithArray(vector::Vector<logicElement::LogicElement> &logicElements) {

  std::cout << "Enter number of terminals you want to create" << std::endl;
  int numTerminals = NumInput<int>(0, std::numeric_limits<int>::max());
  logicElement::DefStruct defStruct(numTerminals);
  defStruct.scan(std::cin);
  logicElements.pushback(
      logicElement::LogicElement(defStruct, logicElements.getSize() + 1));
  return 1;
}
int addTerminal(vector::Vector<logicElement::LogicElement>& logicElement){

    std::cout<<"Enter the number of logic element"<<std::endl;
    for(int i{0}; i < logicElement.getSize();++i)
        std::cout<<i+1<<" ";
    std::cout<<std::endl;
    int number = dialog::NumInput<int>(1, logicElement.getSize());
    terminal::Terminal terminal;
    terminal.scan(std::cin);
    try{
        logicElement[number-1].addTerminal(terminal);
    }
    catch(std::bad_alloc& ba){
        std::cerr<<"No enough memory to add"<<std::endl;
        return 1;
    }

}
int enter(vector::Vector<logicElement::LogicElement> &logicElements) {

  if (logicElements.getSize() == 0) {
    std::cout << "There are no logic element to reenter. Firstly create logic element"<<std::endl;
    return 1;
  }
  std::cout << "Choose the number of logic element you want to enter"<<std::endl;
  for (int i{0}; i < logicElements.getSize(); ++i)
    std::cout << i + 1<<" ";
  std::cout << std::endl;
  int numLogic = NumInput<int>(0, logicElements.getSize() + 1);
  logicElements[numLogic - 1].scan(std::cin);
  return 1;
}
int getTerminal(vector::Vector<logicElement::LogicElement> &logicElements) {

  std::cout << "Enter number of logic element which has terminal you want to get"<<std::endl;
  for (int i{0}; i < logicElements.getSize(); ++i)
    std::cout << i +1<<" ";
  std::cout << std::endl;
  int logicNumber = NumInput<int>(1, logicElements.getSize());
  std::cout << "Enter type of terminal you want to get"<<std::endl<<"0.Output"<<std::endl<<"1.Input"<<std::endl;
  terminal::Terminal::Type type = static_cast<terminal::Terminal::Type>(NumInput(0, 1));
  std::cout << "Enter number of terminal you want to get"<<std::endl;
  int terminalNumber;
  if (type == terminal::Terminal::Type::INPUT) {
    for (int i{0}; i < logicElements[logicNumber - 1].getNumberOfInput(); ++i)
      std::cout << i + 1<<" ";
    std::cout<<std::endl;
    terminalNumber =NumInput<int>(1, logicElements[logicNumber - 1].getNumberOfInput());
    std::cout << "Your terminal is"<<std::endl;
    logicElements[logicNumber - 1][terminalNumber-1].print(std::cout);
  }
  else {
    for (int i{0}; i < logicElements[logicNumber - 1].getNumberOfOutput(); ++i)
      std::cout << i + 1<<" ";
    std::cout<<std::endl;
    terminalNumber = NumInput<int>(1, logicElements[logicNumber - 1].getNumberOfOutput());
    std::cout << "Your terminal is"<<std::endl;
    int count = logicElements[logicNumber-1].getNumberOfTerminals();
    logicElements[logicNumber - 1][count + terminalNumber - 1].print(std::cout);
  }
  return 1;
}
int connect(vector::Vector<logicElement::LogicElement> &logicElements) {

  if (logicElements.getSize() == 0 || logicElements.getSize() == 1) {
    std::cout << "There are no terminals to connect"<<std::endl;
    return 1;
  }
  int i{0};
  std::cout << "Enter the first logic element"<<std::endl;
  for (i; i < logicElements.getSize(); ++i)
    std::cout << i + 1<<" ";
  std::cout << std::endl;
  int firstElement = NumInput<int>(1, logicElements.getSize() + 1);
  std::cout << "Enter the second logic element"<<std::endl;
  for (i = 0; i < logicElements.getSize(); ++i)
    std::cout << i + 1<<" ";
  std::cout << std::endl;
  int secondElement = NumInput<int>(1, logicElements.getSize() + 1);
  try {
      logicElements[firstElement - 1].connect(logicElements[secondElement - 1]);
      return 1;
  }
  catch(std::invalid_argument& ia){
      std::cout<<ia.what()<<std::endl;
      return 1;
  }
}
int print(vector::Vector<logicElement::LogicElement> &logicElements) {

  if (logicElements.getSize() == 0) {
    std::cout << "There are no logic elements to print" << std::endl;
    return 1;
  }
  for (int i{0}; i < logicElements.getSize(); ++i)
    std::cout<<logicElements[i];
  return 1;
}

}
