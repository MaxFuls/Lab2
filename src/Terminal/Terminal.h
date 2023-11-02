#ifndef H_TERMINAL
#define H_TERMINAL


#include <string>

namespace terminal {

    class Terminal {
    public:
        enum class Type {
            OUTPUT ///<Type of terminal is output, output terminal can not have more then 3 connections
            , INPUT ///<Type of terminal is input, input terminal can not have more then 1 connection, also for input terminal with 0 connections state of signal is X
        };
        enum class Signal {
            OFF ///<Terminal is off, state of signal is 0
            , ON ///<Terminal is on, state of signal is 1
            , X ///<State of terminal is undefined, state of signal is X
        };
    private:
        int number;
        Type type;
        int connections;
        Signal signal;

    public:

        /**
         *@brief Default constructor : construct terminal with zero number, input type, 0 connections and X signal
         */
        Terminal();
        /**
         @brief Constructor with definition : construct terminal with parameters you enter
         @param type Enum value from enum class Type: OUTPUT(0) or INPUT(1)
         @param connections Amount of connections: from 0 to 1 for input terminal, from 0 to 3 for output terminal
         @param signal Enum value from Enum class Signal: OFF(0), ON(1) or X(2)
         @param number Number of terminal: positive integer
         @throw invalid_argument with "Number need be positive" if you enter negative number
         @throw invalid_argument with "Incorrect number of connections for this type of terminal" if you do
         */
        Terminal(Type, int, Signal, int);
        /**
         *@brief Constructor with type and number: construct terminal with type and number you enter, 0 connections and X signal
         * @param type Enum value from enum class Type: OUTPUT(0) or INPUT(1)
         * @param number Number of terminal: positive integer
         * @throw invalid_argument with "Number need be positive" if you enter negative number
         */
        Terminal(Type, int);
        /**
         *@brief Default copy constructor
         * @param terminal Const reference to terminal which parameters you want to use to create new terminal
         */
        Terminal(const Terminal&) = default;
        /**
         * @brief Default reloaded copy assignment operator
         * @param terminal Const reference to terminal which parameters you want to copy
         */
        Terminal& operator=(const Terminal&) = default;
        /**
         *@brief Default destructor
         */
        ~Terminal() = default;

        /**
         *@brief Method required to get amount of connections
         * @return Amount of connections
         */
        int getConnections() const;
        /**
         *@brief Method required to get state of signal
         * @return Enum value from Enum class Signal: OFF(0), ON(1) or X(2)
         */
        Signal getSignal() const;
        /**
         *@brief Method required to get number of terminal
         * @return Number of terminal
         */
        int getNumber() const;
        /**
         *@brief Method required to get type of terminal
         * @return Enum value from enum class Type: OUTPUT(0) or INPUT(1)
         */
        Type getType() const;

        /**
         *@brief Method required to set type of terminal
         * @param type Enum value from enum class Type: OUTPUT(0) or INPUT(1)
         */
        void setType(Type);
        /**
         *@brief Method required to set amount of connections
         * @param connections Integer value from 0 to 1 for input terminal and from 0 to 3 for output
         * @details If you call this method with 0 from input terminal with 1 connection and any state of signal, you
         * will set connections to 0 and state of signal to X
         * @throw invalid_argument with "Number of connections for input terminal is 0 or 1" if you call this method with
         * another value from input terminal
         * @throw invalid_argument with "Number of connections for output terminal is 0, 1, 2 or 3" if you call this
         * method with another value from output terminal
         */
        void setConnections(int);
        /**
         *@brief Method required to set state of signal
         * @param signal Enum value from Enum class Signal: OFF(0), ON(1) or X(2)
         * @details If you try to call this method with OFF or ON parameters from input terminal with 0 connections
         * its state of signal will stay X
         */
        void setSignal(Signal);
        /**
         *@brief Method required to set number of terminal
         * @param number Positive integer
         * @throw invalid_argument with "Number need be positive" if you call  this method with negative parameter
         */
        void setNumber(int);

        /**
         *@brief Method required to output your terminal to stream
         * @param c Reference to output stream
         * return Reference to output stream
         */
        std::ostream& print(std::ostream&) const;
        /**
         *@brief Method required to input your terminal from input stream
         * @param c Reference to input stream
         * return Reference to input stream
         */
        std::istream& scan(std::istream&);

        /**
         *@brief Method required to connect output terminal with input: if you call this method with right parameters
         * amount of connections of both terminals will increase
         * @param terminal Reference to input terminal
         * @throw invalid_argument with "Type of the first terminal need to output, the second is input" if you try to
         * call this method from input terminal or with output terminal
         * @throw invalid_argument with "Incorrect number of connections for connect" if you try to call this method
         * from output terminal with 3 connections or with input terminal with 1 connection
         */
        void connect(Terminal &);
        /**
         *@brief Method required to disconnect output and input terminals: if ypu call this method with right parameters
         * amount of connections of both terminals will decrease
         * @param terminal Reference to input terminal
         * @throw invalid_argument with "Type of the first terminal need to output, the second is input" if you try to
         * call this method from input terminal or with output terminal
         * @throw invalid_argument with "Incorrect number of connections for connect" if you try to call this method
         * from output terminal with 0 connections or with input terminal with 0 connection
         */
        void disconnect(Terminal &);

        /**
         *@brief Method required to increase amount of connections by one
         * @throw logic_error with "Max number of connections for input terminal is 1" if you try to call this method
         * from input terminal with 1 connection
         * @throw logic_error with "Max number of connections for output terminal is 3" if you try to call this method
         * from output terminal with 3 connection
         */
        void increaseConnections();
        /**
         *@brief Method required to decrease amount of connections by one
         * @throw logic_error with "Amount of connections is already 0" if you try to call this method
         * from input or output terminal with 0 connections
         */
        void decreaseConnections();
        /**
        * @brief Output operator
        * @param c Output stream reference
        * @param terminal Const reference to terminal for output to stream
        * @return Output stream reference
        * */
        friend std::ostream &operator<<(std::ostream &, const Terminal &);
        /**
         * @brief Input operator
         * @param c Input stream reference
         * @param terminal Reference to terminal for input from steam
         * @return Input stream reference
         * */
        friend std::istream &operator>>(std::istream &, Terminal &);
        /**
         *@brief Reloaded operator >> required to connect output terminal with input: calls method "connect"
         */
        void operator>>(Terminal &);
        /**
         *@brief Reloaded prefix increment required to increase amount of connections by one point: calls method "increase Connections"
         */
        Terminal &operator++();
        /**
         *@brief Reloaded postfix increment required to increase amount of connections by one point: calls method "increase Connections"
         */
        Terminal operator++(int);
        /**
         *@brief Reloaded prefix decrement required to decrease amount of connections by one point: calls method "decrease Connections"
         */
        Terminal &operator--();
        /**
         *@brief Reloaded postfix decrement required to decrease amount of connections by one point: calls method "decrease Connections"
         */
        Terminal operator--(int);
    };

    int Input(int min, int max,std::istream&);
}
#endif