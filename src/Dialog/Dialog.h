#ifndef H_DIALOG
#define H_DIALOG

#include "/home/maxfuls/Programs/Lab2/src/LogicElement/LogicElement.h"
#include "/home/maxfuls/Programs/Lab2/src/Terminal/Terminal.h"
#include "/home/maxfuls/Programs/Lab2/src/Vector/Vector.h"
#include <iostream>
#include <exception>
#include <limits>
#include <stdexcept>

namespace dialog {

template <class T> T NumInput(T min, T max) {
  T a;
  while (true) {
    std::cin >> a;
    if (std::cin.eof())
      throw std::runtime_error("Error of input: EOF");
    else if (std::cin.bad())
      throw std::runtime_error("Error of input");
    else if (std::cin.fail()) {
      std::cout << "Repeat please" << std::endl;
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    } else if (a >= min && a <= max)
      return a;
    else {
      std::cout << "Repeat please" << std::endl;
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
  }
}

int dialog(const char *[], const int);

// Terminals' dialog functions

int createFull(vector::Vector<terminal::Terminal> &);
int createWithType(vector::Vector<terminal::Terminal> &);
int connect(vector::Vector<terminal::Terminal> &);
int disconnect(vector::Vector<terminal::Terminal> &);
int print(vector::Vector<terminal::Terminal> &);
int enter(vector::Vector<terminal::Terminal> &);

// Logic Elements' dialog functions

int createWithNumber(vector::Vector<logicElement::LogicElement> &);
int createWithArray(vector::Vector<logicElement::LogicElement> &);
int addTerminal(vector::Vector<logicElement::LogicElement>&);
int enter(vector::Vector<logicElement::LogicElement> &);
int getTerminal(vector::Vector<logicElement::LogicElement> &);
int connect(vector::Vector<logicElement::LogicElement> &);
int print(vector::Vector<logicElement::LogicElement> &);

} // namespace dialog
#endif