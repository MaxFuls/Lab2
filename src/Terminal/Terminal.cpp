#include "/home/maxfuls/Programs/Lab2/src/Terminal/Terminal.h"
#include "/home/maxfuls/Programs/Lab2/src/Dialog/Dialog.h"
#include <string>
#include <iostream>
#include <exception>
#include <limits>
#include <string>
#include <stdexcept>

namespace terminal {

    int Input(int min, int max, std::istream& c) {

        int a;
        while (true) {
            c >> a;
            if (c.eof()) {
                throw std::runtime_error("Error of input: EOF");
            }
            else if (c.bad())
                throw std::runtime_error("Error of input");
            else if (c.fail()) {
                c.clear();
                c.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Repeat please" << std::endl;
            } else {
                if (a >= min && a <= max)
                    return a;
                else {
                    c.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cout << "Repeat please" << std::endl;
                }
            }
        }
    }
	Terminal::Terminal() : number(0), type(Type::INPUT), connections(0), signal(Signal::X) {	}																	
	Terminal::Terminal(Type type, int connections, Signal signal, int number) :  type(type) {

        if(number<0)
            throw std::invalid_argument("Number need be positive");
        else
            this->number = number;
		if (type == Type::INPUT) {
			if (connections == 1) {
				this->connections = connections;
				this->signal = signal;
			}
			else if(connections == 0) {
				this->connections = 0;
				this->signal = Signal::X;
			}
			else {
				this->connections = 0;
				this->signal = Signal::X;
				throw std::invalid_argument("Incorrect number of connections for this type of terminal");
			}
		
		}
		else {
			if (connections >= 0 && connections <= 3) {
				this->connections = connections;
				this->signal = signal;
			}
			else {
				this->connections = 0;
				this->signal = Signal::X;
				throw std::invalid_argument("Incorrect number of connections for this type of terminal");
			}
		}
	}
	Terminal::Terminal(Type type, int number) : type(type), connections(0), signal(Signal::X) {

        if(number<0)
            throw std::invalid_argument("Number must be positive");
        else
            this->number = number;
    }

    std::ostream& operator<<(std::ostream& c, const Terminal& terminal) {

        std::string type;
        char signal;
        if (terminal.signal == Terminal::Signal::ON)
            signal = '1';
        else if (terminal.signal == Terminal::Signal::OFF)
            signal = '0';
        else
            signal = 'X';
        if (terminal.type == Terminal::Type::INPUT)
            type = "Input";
        else
            type = "Output";
        c<< "Terminal number is " << terminal.number << std::endl << "Type of terminal is " << type << std::endl
             << "Number of connections is " << terminal.connections << std::endl << "State of signal is " << signal
             << std::endl;
        return c;

    }
    std::istream& operator>>(std::istream& c, Terminal& terminal){

        int tmp_number = terminal.number;
        Terminal::Type tmp_type = terminal.type;
        int tmp_connections = terminal.connections;
        Terminal::Signal tmp_signal = terminal.signal;
        int type;
        int signal;
        c>>terminal.number>>type>>terminal.connections>>signal;
        while(c.good()) {
            if (terminal.number < 0) {
                c.setstate(std::ios::failbit);
                break;
            }
            if (type != 0 && type != 1) {
                c.setstate(std::ios::failbit);
                break;
            }
            terminal.type = static_cast<Terminal::Type>(type);
            if (terminal.connections < 0 || terminal.connections > 3) {
                c.setstate(std::ios::failbit);
                break;
            } else if (terminal.type == Terminal::Type::INPUT && terminal.connections > 1) {
                c.setstate(std::ios::failbit);
                break;
            }
            if (signal < 0 || signal > 3) {
                c.setstate(std::ios::failbit);
                break;
            } else if (terminal.type == Terminal::Type::INPUT && terminal.connections == 0 && signal != 2) {
                c.setstate(std::ios::failbit);
                break;
            } else
                terminal.signal = static_cast<Terminal::Signal>(signal);
            return  c;
        }
        terminal.number = tmp_number;
        terminal.type = tmp_type;
        terminal.connections = tmp_connections;
        terminal.signal = tmp_signal;
        return c;
    }
    void Terminal::operator>>(Terminal& terminal){

        connect(terminal);
    }
    Terminal& Terminal::operator++() {

        increaseConnections();
        return *this;
    }
    Terminal Terminal::operator++(int) {

        Terminal tmp(*this);
        increaseConnections();
        return tmp;
    }
    Terminal& Terminal::operator--() {

        decreaseConnections();
        return *this;
    }
    Terminal Terminal::operator--(int){

        Terminal tmp(*this);
        decreaseConnections();
        return tmp;
    }

	void Terminal::increaseConnections() {
		if (type == Type::INPUT) {
			if (!connections)
				++connections;
			else
				throw std::logic_error("Max number of connections for input terminal is 1");
		}
		else {
			if (connections < 3)
				++connections;
			else
				throw std::logic_error("Max number of connections for input terminal is 3");
		}

	}
	void Terminal::decreaseConnections(){
		if (type == Type::INPUT) {

			if (connections)
				--connections;
			else
				throw std::logic_error("Amount of connections is already 0");
		}
		else {

			if (connections)
				--connections;
			else
				throw std::logic_error("Amount of connections is already 0");
		}
	}

    Terminal::Type Terminal::getType() const {

        return type;
	}
	int  Terminal::getConnections() const {

		return connections;
	}
    Terminal::Signal Terminal::getSignal() const {
        return signal;
	}
	int Terminal::getNumber() const{

		return number;
	}

	void Terminal::setType(Type type) {

		this->type = type;
	}
	void Terminal::setConnections(int connections) {

		if (type == Type::INPUT) {
			if (connections < 0 || connections>1) {
				throw std::invalid_argument("Number of connections for input terminal is 0 or 1");
			}
			else if (connections == 0) {
				this->connections = connections;
				signal = Signal::X;
			}
			else
				this->connections = connections;
		}
		else {
			if (connections < 0 || connections>3) {
				throw std::invalid_argument("Number of connections for output terminal is 0, 1, 2 or 3");
			}
			else
				this->connections = connections;
		}
		
	}
	void Terminal::setSignal(Signal signal) {

		if (type == Type::INPUT) {
			if (!connections)
				this->signal = Signal::X;
			else
				this->signal = signal;
		}
		else
			this->signal = signal;
	}
	void Terminal::setNumber(int number) {
			
		if (number > 0) 
			this->number = number;
		else
			throw std::invalid_argument("Number need be positive");
			
	}

	std::istream& Terminal::scan(std::istream& c) {

        std::cout << "Enter number of terminal"<<std::endl;
        number = Input(0,std::numeric_limits<int>::max(),c);
        std::cout << "Enter type of terminal" << std::endl << "0.Output" << std::endl << "1.Input" << std::endl;
        type = static_cast<Type>(Input(0,1,c));
        std::cout << "Enter number of connections: for input 0 or 1, for output: 0, 1, 2 or 3" << std::endl;
        connections = Input(0,3,c);
        std::cout << "Enter state of signal" << std::endl << "0.Off" << std::endl << "1.On" << std::endl << "2.X"<< std::endl;
        signal = static_cast<Signal>(Input(0,2,c));
        return c;

	}
	std::ostream& Terminal::print(std::ostream& c) const {

		std::string type;
		char signal;
		if (this->signal == Signal::ON)
			signal = '1';
		else if (this->signal == Signal::OFF)
			signal = '0';
		else
			signal = 'X';
		if (this->type == Type::INPUT)
			type = "Input";
		else
			type = "Output";
		c << "Terminal number is " <<number<<std::endl<<"Type of terminal is "<<type<<std::endl
		<< "Number of connections is "<<connections<<std::endl<< "State of signal is " << signal<<std::endl;
        return c;
	}

	void Terminal::connect(Terminal& terminal) {

		if (type != Type::OUTPUT || terminal.type != Type::INPUT)
			throw std::invalid_argument("Type of the first terminal need to output, the second is input");
		if (connections == 3 || terminal.connections == 1)
			throw std::invalid_argument("Incorrect number of connections for connect");
		++connections;
		++terminal.connections;
	}
	void Terminal::disconnect(Terminal& terminal) {
		
		if (type != Type::OUTPUT || terminal.type != Type::INPUT)
			throw std::invalid_argument("Type of the first terminal need to output, the second is input");
		if (!connections || !terminal.connections)
			throw std::invalid_argument("Incorrect number of connections for disconnect");
		--connections;
		--terminal.connections;
	}
}