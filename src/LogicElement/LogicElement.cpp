#include "/home/maxfuls/Programs/Lab2/src/Terminal/Terminal.h"
#include "/home/maxfuls/Programs/Lab2/src/Dialog/Dialog.h"
#include "/home/maxfuls/Programs/Lab2/src/Vector/Vector.h"
#include "/home/maxfuls/Programs/Lab2/src/LogicElement/LogicElement.h"
#include <exception>
#include <iostream>
#include <limits>
#include <string>
#include <stdexcept>

namespace logicElement {

	DefStruct::DefStruct(int numTerminals): length(numTerminals), numInput(0), numOutput(0) {
	
		definitions = new Definitions[numTerminals];
	}
	DefStruct::~DefStruct() {

		delete[] definitions;
	}
	std::istream& DefStruct::scan(std::istream& c) {
		
		if (definitions != nullptr) {
			for (int i{ 0 }; i < length; ++i) {
				definitions[i].scan(c);
				if (definitions[i].getType() == terminal::Terminal::Type::INPUT)
					++numInput;
				else
					++numOutput;
			}
		}
	}

    terminal::Terminal::Type Definitions::getType() const {return type;}
    int Definitions::getConnections() const {return connections;}
    terminal::Terminal::Signal Definitions::getSignal() const {return signal;}

    int DefStruct::getLength() const {return length;}
    int DefStruct::getInput() const {return numInput;}
    int DefStruct::getOutput() const {return numOutput;}
    Definitions* DefStruct::getDefinitions() const {return definitions;}
	std::istream& Definitions::scan(std::istream& c) {

		std::cout << "Enter type of terminal"<<std::endl<<"0.Output"<<std::endl<<"1.Input"<<std::endl;
		type = static_cast<terminal::Terminal::Type>(terminal::Input(0, 1, c));
		std::cout << "Enter number of connections: 0 or 1 for input terminal, from 0 to 3 for output"<<std::endl;
		if (type == terminal::Terminal::Type::INPUT)
			connections = terminal::Input(0, 1, c);
		else
			connections = terminal::Input(0, 3, c);
		if (type == terminal::Terminal::Type::INPUT && !connections) {
			std::cout << "For input terminal with 0 connections state of signal is X"<<std::endl;
			signal = terminal::Terminal::Signal::X;
		}
		else {
			std::cout << "Enter state of signal"<<std::endl<<"0.Off"<<std::endl<<"1.On"<<std::endl<<"2.X"<<std::endl;
			signal = static_cast<terminal::Terminal::Signal>(terminal::Input(0, 2, c));
		}
        return c;
	}


	LogicElement::LogicElement(): number(0)	{	}
	LogicElement::LogicElement(int numInput, int numOutput, int number) : number(number)
                                                                        , inputTerminals(numInput)
                                                                        , outputTerminals(numOutput){

		int i{ 0 };
		for (i; i < numInput; ++i)
			inputTerminals.pushback(terminal::Terminal(terminal::Terminal::Type::INPUT, i+1));
		for (i = 0; i < numOutput; ++i)
			outputTerminals.pushback(terminal::Terminal(terminal::Terminal::Type::OUTPUT, i+1));
	}
	LogicElement::LogicElement(const DefStruct& defStruct, int number): number(number)
                                                                      , inputTerminals(defStruct.getInput())
                                                                      , outputTerminals(defStruct.getOutput()){

		int i{ 0 };
		int j{ 0 };
		int k{ 0 };
		for (i; i < defStruct.getLength(); ++i) {
			if (defStruct.getDefinitions()[i].getType() == terminal::Terminal::Type::INPUT)
				inputTerminals.pushback(terminal::Terminal(terminal::Terminal::Type::INPUT, defStruct.getDefinitions()[i].getConnections()
															, defStruct.getDefinitions()[i].getSignal(), ++j));
			else
				outputTerminals.pushback(terminal::Terminal(terminal::Terminal::Type::OUTPUT, defStruct.getDefinitions()[i].getConnections()
															, defStruct.getDefinitions()[i].getSignal(), ++k));
		}
	}	


    std::ostream& operator<<(std::ostream& c, const LogicElement& logicElement){

        int i{ 0 };
        c << "Number of logic element is "<<logicElement.number<<std::endl<<"Number of input terminals is "
                << logicElement.inputTerminals.getSize()<<std::endl;
        if (logicElement.inputTerminals.getSize()) c <<"Their states are"<<std::endl<<std::endl;
        for (i; i < logicElement.inputTerminals.getSize(); ++i)
            c<<logicElement.inputTerminals[i];
        c<<std::endl;
        c << "Number of output terminals is "<< logicElement.outputTerminals.getSize()<<std::endl;
        if (logicElement.outputTerminals.getSize()) c << "Their states are"<<std::endl<<std::endl;
        for (i = 0; i < logicElement.outputTerminals.getSize(); ++i)
            c<<logicElement.outputTerminals[i];
        c<<std::endl;
        return c;
    }
    std::istream& operator>>(std::istream& c, LogicElement& logicElement) {

        int numInput;
        int numOutput;
        int tmp_number;
        c>>logicElement.number>>numInput>>numOutput;
        while(c.good()) {
            if (numInput < 0 || numOutput<0 || logicElement.number < 0) {
                c.setstate(std::istream::failbit);
                break;
            }
            logicElement.inputTerminals = vector::Vector<terminal::Terminal>(numInput);
            logicElement.outputTerminals = vector::Vector<terminal::Terminal>(numOutput);
            return c;
        }
        logicElement.number = tmp_number;
        return c;
    }
    terminal::Terminal& LogicElement::operator[](int index) {

        int count = inputTerminals.getSize() + outputTerminals.getSize();
        if(index<0 || index>=count)
            throw std::invalid_argument("Incorrect index");
        if (index < inputTerminals.getSize())
            return inputTerminals[index];
        else
            return outputTerminals[index - inputTerminals.getSize()];
    }

    void LogicElement::operator>>(logicElement::LogicElement& logicElement) {

        connect(logicElement);
    }

    int LogicElement::getNumber() const{

        return number;
	}
	int LogicElement::getNumberOfInput() const{

		return inputTerminals.getSize();
	}
	int LogicElement::getNumberOfOutput() const {

		return outputTerminals.getSize();
	}
    int LogicElement::getNumberOfTerminals() const {

        return (inputTerminals.getSize() + outputTerminals.getSize());
    }
	void LogicElement::setNumber(int number) {

		if (number > 0)
			this->number = number;
		else
			throw std::invalid_argument("Number need pe positive");
	}

	std::ostream& LogicElement::print(std::ostream& c) const{
		
		int i{ 0 };
		c << "Number of logic element is "<<number<<std::endl<<"Number of input terminals is "<< inputTerminals.getSize()<<std::endl;
		if (inputTerminals.getSize()) c <<"Their states are"<<std::endl<<std::endl;
		for (i; i < inputTerminals.getSize(); ++i)
			inputTerminals[i].print(c);
        c<<std::endl;
		c << "Number of output terminals is "<< outputTerminals.getSize()<<std::endl;
		if (outputTerminals.getSize()) c << "Their states are"<<std::endl<<std::endl;
		for (i = 0; i < outputTerminals.getSize(); ++i)
			outputTerminals[i].print(c);
        c<<std::endl;
        return c;
	}
	std::istream& LogicElement::scan(std::istream& c) {

		std::cout << "Enter count of terminals you want to enter"<<std::endl;
		int numTerminals = terminal::Input(1, std::numeric_limits<int>::max(), c);
		DefStruct defStruct(numTerminals);
		defStruct.scan(c);
		inputTerminals.clear();
		outputTerminals.clear();
		int j{ 1 };
		int k{ 1 };
        for (int i{0}; i < numTerminals; ++i) {
            if (defStruct.getDefinitions()[i].getType() == terminal::Terminal::Type::INPUT)
                inputTerminals.pushback(
                        terminal::Terminal(terminal::Terminal::Type::INPUT, defStruct.getDefinitions()[i].getConnections(),
                                           defStruct.getDefinitions()[i].getSignal(), j++));
            else
                outputTerminals.pushback(
                        terminal::Terminal(terminal::Terminal::Type::OUTPUT, defStruct.getDefinitions()[i].getConnections(),
                                           defStruct.getDefinitions()[i].getSignal(), k++));
        }
	}

	void LogicElement::addTerminal(const terminal::Terminal& terminal) {

		if (terminal.getType() == terminal::Terminal::Type::INPUT)
			inputTerminals.pushback(terminal);
		else
			outputTerminals.pushback(terminal);
	}
	void LogicElement::connect(LogicElement& logicElement){
		
		if (this == &logicElement)
			throw std::invalid_argument("You try to connect the same logic element");
		if (!outputTerminals.getSize() || !logicElement.inputTerminals.getSize())
			throw std::invalid_argument("There no terminals to connect");
		int i{ 0 };
		int j{ 0 };
		for (i; i < outputTerminals.getSize(); ++i)
			if (outputTerminals[i].getConnections() < 3)
				break;
		for (j; j < logicElement.inputTerminals.getSize(); ++j)
			if (logicElement.inputTerminals[j].getConnections() < 1)
				break;
		if (j==logicElement.inputTerminals.getSize() || i==outputTerminals.getSize())
			throw std::invalid_argument("The first logic element need to have free output terminals, and the second - free input terminals");
		outputTerminals[i].connect(logicElement.inputTerminals[j]);

	}
	terminal::Terminal& LogicElement::getTerminal(terminal::Terminal::Type type, int number){

		if (type == terminal::Terminal::Type::INPUT)
			return inputTerminals[number-1];
		else
			return outputTerminals[number-1];
	}
}