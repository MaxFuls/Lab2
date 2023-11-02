#ifndef H_LOGICELEMENT
#define H_LOGICELEMENT

#include "/home/maxfuls/Programs/Lab2/src/Terminal/Terminal.h"
#include "/home/maxfuls/Programs/Lab2/src/Vector/Vector.h"

namespace logicElement {

class Definitions {
private:
    terminal::Terminal::Type type;
    int connections;
    terminal::Terminal::Signal signal;
public:
    /**
     *@brief Method required to get type of terminal written in definition
     * @return Enum value from enum class Type: OUTPUT(0) or INPUT(1)
     */
    terminal::Terminal::Type getType() const;
    /**
     * @brief Method required to get amount of connections written in definition
     * @return Amount of connections
     */
    int getConnections() const;
    /**
     * @brief Method required to get state of signal written in definition
     * @return Enum value from enum class Signal: OFF(0), ON(1) or X(2)
     */
    terminal::Terminal::Signal getSignal() const;
    /**
     * @brief Method required to get type, amount of connections and state of signal from input stream
     * @param c Reference to input stream
     * @return Reference to input stream
     */
    std::istream& scan(std::istream&);
};

class DefStruct {
private:
  int length;
  int numInput = 0;
  int numOutput = 0;
  Definitions *definitions;
public:
    /**
     *@brief Method required to get amount of definitions
     * @return Amount of definitions
     */
    int getLength() const;
    /**
     * @brief Method required to get amount of definitions corresponding to input terminals
     * @return Amount of definitions corresponding to input terminals
     */
    int getInput() const;
    /**
     * @brief Method required to get amount of definitions corresponding to output terminals
     * @return Amount of definitions corresponding to output terminals
     */
    int getOutput() const;
    /**
     * @brief Method required to get pointer to array of definitions
     * @return Definition pointer to array of definitions
     */
    Definitions* getDefinitions() const;
    /**
     * @brief Constructor with amount of definitions: construct DefStruct with array of definitions of given size
     * @param numTerminals Amount of definitions you want to enter
     */
    explicit DefStruct(int);
    /**
     * @brief Destructor: clears memory used for array of definitions
     */
    ~DefStruct();
    /**
     * @brief Method required to get amount of terminals, amount of input and output terminals and get their definitions
     * @param c Reference to input stream
     * @return Reference to input stream
     */
    std::istream& scan(std::istream&);
};
class LogicElement {

private:
  int number;
  vector::Vector<terminal::Terminal> inputTerminals;
  vector::Vector<terminal::Terminal> outputTerminals;

public:
 /**
  * @brief Default constructor: construct logic element with zero number, zero quantity of input and output terminals
  */
  LogicElement();
  /**
   * @brief Constructor with number of logic element, amount of input and output terminals
   * @param numInput Amount of input terminals
   * @param numOutput Amount of output terminals
   * @param number Number of logic element
   */
  LogicElement(int, int, int);
  /**
   * @brief Constructor with array of definitions an number: construct logic element according to definitions
   * @param defStruct struct including amount of input and output terminals and array of their definitions
   * @param number Number of logic element
   */
  LogicElement(const DefStruct &, int);
  /**
   *@brief Default copy constructor
   * @param logicElement Const reference to logic element
   */
  LogicElement(const LogicElement &) = default;
  /**
   *@brief Default move constructor
   * @param logicElement Rvalue reference to logic element
   */
  LogicElement(LogicElement&&) = default;
  /**
   * @brief Default copy assignment operator
   * @param logicElement Const reference to logic element
   */
  LogicElement& operator=(LogicElement&&) = default;
  /**
   * @brief Default move assignment operator
   * @param logicElement Rvalue reference to logic element
   */
  LogicElement &operator=(const LogicElement &) = default;
  /**
   * @brief Default destructor
   */
  ~LogicElement() = default;

  /**
   * @brief Reloaded << operator required to output state of logic element to output stream
   * @param c Reference to output stream
   * @param logicElement Const Reference to logic element
   * @return Reference to output stream
   */
  friend std::ostream& operator<<(std::ostream&, const LogicElement&);
  /**
   * @brief Reloaded >> operator required to input parameters of logic element: number, amount of input and output terminals
   * from input stream
   * @param c Reference to input stream
   * @param logicElement Reference to logic element
   * @details This operator may set failbit flag for input stream if you enter incorrect values of parameters: negative
   * number of logic element, negative amount of output or input terminals
   * @return Reference to input stream
   */
  friend std::istream& operator>>(std::istream&, LogicElement&);
  /**
   * @brief Reloaded [] operator required to get terminal from logic element: it works like array - index can change
   * from 0 to amount of terminals - 1. Call with index from "0" to "amount of input terminals - 1" you can get input
   * terminal, call with index "amount of input terminals" to "amount of terminals" you can get output terminal
   * @param index Index
   * @throw invalid_argument with "Incorrect index" if you try to call this method with negative index or with index
   * which bigger then "amount of terminals - 1"
   * @return Reference to terminal
   */
  terminal::Terminal& operator[](int);
  /**
   * @brief Reloaded operator >> required to connect output terminal from one logic element with input terminal from another
   * @param logicElement Reference to logic element containing input terminal
   */
  void operator>>(LogicElement&);

  /**
   * @brief Method required to get number of logic element
   * @return Number of logic element
   */
  int getNumber() const;
  /**
   * @brief Method required to get amount of input terminals
   * @return Amount of input terminals
   */
  int getNumberOfInput() const;
  /**
   * @brief Method required to get amount of output terminals
   * @return Amount of output terminals
   */
  int getNumberOfOutput() const;
  /**
   *@brief Method required to get amount of terminals
   * @return Amount of terminals
   */
  int getNumberOfTerminals() const;
  /**
   *@brief Method required to set number of logic element
   * @param number Number of logic element
   * @throw invalid_argument with "Number need be positive" if you call it with negative parameter
   */
  void setNumber(int);
  /**
   *@brief Method required to output state of logic element and states of terminals it contain to output stream
   * @param c Reference to output stream
   * @return Reference to output stream
   */
  std::ostream& print(std::ostream&) const;
  /**
   *@brief Method required to input state of logic element and states of terminals it contain from input stream
   * @param c Reference to input stream
   * @return c Reference to input stream
   */
  std::istream& scan(std::istream&);
  /**
   *@brief Method required to add new terminal to logic element
   * @param terminal Reference to terminal you want to add
   */
  void addTerminal(const terminal::Terminal &);
  /**
   *@brief Method required to connect output terminal from "this" logic element with input terminal for another logic element
   * @param logicElement Reference to terminal containing input terminal
   * @throw invalid_argument with "You try to connect the same logic element" if you do
   * @throw invalid_argument with "There no terminals to connect" if "this" logic element hasn't output terminals or
   * logicElement(parameter) hasn't input terminals
   * @throw invalid_argument with "The first logic element need to have free output terminals, and the second - free input terminals"
   * if "this" logic element hasn't free output terminals or logicElement(parameter) hasn't free input terminals
   */
  void connect(LogicElement &);
  /**
   *@brief Method required to get reference to terminal containing in logic element
   * @param type Enum value from enum class type: OUTPUT(0) or INPUT(1); type of terminal you want to get
   * @param number Number of terminal you want to get
   * return Reference to terminal
   */
  terminal::Terminal &getTerminal(terminal::Terminal::Type, int);
};
}
#endif
