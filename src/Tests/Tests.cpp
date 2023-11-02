#define CATCH_CONFIG_MAIN

#include <string>
#include <sstream>
#include <catch2/catch.hpp>
#include "/home/maxfuls/Programs/Lab2/src/Terminal/Terminal.h"
#include "/home/maxfuls/Programs/Lab2/src/LogicElement/LogicElement.h"
#include "/home/maxfuls/Programs/Lab2/src/Vector/Vector.h"

TEST_CASE("TerminalConstructor"){
    SECTION("DefaultConstructor"){
        terminal::Terminal a;
        REQUIRE(a.getNumber() == 0);
        REQUIRE(a.getType() == terminal::Terminal::Type::INPUT);
        REQUIRE(a.getConnections() == 0);
        REQUIRE(a.getSignal() == terminal::Terminal::Signal::X);
    }
    SECTION("InitConstructors"){
        terminal::Terminal a1(terminal::Terminal::Type::INPUT, 1);
        REQUIRE(a1.getNumber() == 1);
        REQUIRE(a1.getType() == terminal::Terminal::Type::INPUT);
        REQUIRE(a1.getConnections() == 0);
        REQUIRE(a1.getSignal() == terminal::Terminal::Signal::X);

        terminal::Terminal a2(terminal::Terminal::Type::OUTPUT, 1);
        REQUIRE(a2.getNumber() == 1);
        REQUIRE(a2.getType() == terminal::Terminal::Type::OUTPUT);
        REQUIRE(a2.getConnections() == 0);
        REQUIRE(a2.getSignal() == terminal::Terminal::Signal::X);

        terminal::Terminal a3(terminal::Terminal::Type::INPUT, 1, terminal::Terminal::Signal::OFF,1);
        REQUIRE(a3.getNumber() == 1);
        REQUIRE(a3.getType() == terminal::Terminal::Type::INPUT);
        REQUIRE(a3.getConnections() == 1);
        REQUIRE(a3.getSignal() == terminal::Terminal::Signal::OFF);

        terminal::Terminal a4(terminal::Terminal::Type::INPUT, 1, terminal::Terminal::Signal::ON,1);
        REQUIRE(a4.getNumber() == 1);
        REQUIRE(a4.getType() == terminal::Terminal::Type::INPUT);
        REQUIRE(a4.getConnections() == 1);
        REQUIRE(a4.getSignal() == terminal::Terminal::Signal::ON);

        terminal::Terminal a5(terminal::Terminal::Type::INPUT, 1, terminal::Terminal::Signal::X,1);
        REQUIRE(a5.getNumber() == 1);
        REQUIRE(a5.getType() == terminal::Terminal::Type::INPUT);
        REQUIRE(a5.getConnections() == 1);
        REQUIRE(a5.getSignal() == terminal::Terminal::Signal::X);

        terminal::Terminal a6(terminal::Terminal::Type::INPUT, 0, terminal::Terminal::Signal::OFF,1);
        REQUIRE(a6.getNumber() == 1);
        REQUIRE(a6.getType() == terminal::Terminal::Type::INPUT);
        REQUIRE(a6.getConnections() == 0);
        REQUIRE(a6.getSignal() == terminal::Terminal::Signal::X);

        terminal::Terminal a7(terminal::Terminal::Type::INPUT, 0, terminal::Terminal::Signal::ON,1);
        REQUIRE(a7.getNumber() == 1);
        REQUIRE(a7.getType() == terminal::Terminal::Type::INPUT);
        REQUIRE(a7.getConnections() == 0);
        REQUIRE(a7.getSignal() == terminal::Terminal::Signal::X);

        terminal::Terminal a8(terminal::Terminal::Type::INPUT, 0, terminal::Terminal::Signal::X,1);
        REQUIRE(a8.getNumber() == 1);
        REQUIRE(a8.getType() == terminal::Terminal::Type::INPUT);
        REQUIRE(a8.getConnections() == 0);
        REQUIRE(a8.getSignal() == terminal::Terminal::Signal::X);

        terminal::Terminal a9(terminal::Terminal::Type::OUTPUT, 3, terminal::Terminal::Signal::OFF, 1);
        REQUIRE(a9.getNumber() == 1);
        REQUIRE(a9.getType() == terminal::Terminal::Type::OUTPUT);
        REQUIRE(a9.getConnections() == 3);
        REQUIRE(a9.getSignal() == terminal::Terminal::Signal::OFF);

        terminal::Terminal a10(terminal::Terminal::Type::OUTPUT, 3, terminal::Terminal::Signal::ON, 1);
        REQUIRE(a10.getNumber() == 1);
        REQUIRE(a10.getType() == terminal::Terminal::Type::OUTPUT);
        REQUIRE(a10.getConnections() == 3);
        REQUIRE(a10.getSignal() == terminal::Terminal::Signal::ON);

        terminal::Terminal a11(terminal::Terminal::Type::OUTPUT, 3, terminal::Terminal::Signal::X, 1);
        REQUIRE(a11.getNumber() == 1);
        REQUIRE(a11.getType() == terminal::Terminal::Type::OUTPUT);
        REQUIRE(a11.getConnections() == 3);
        REQUIRE(a11.getSignal() == terminal::Terminal::Signal::X);
    }
    SECTION("TestExceptions"){
        REQUIRE_THROWS(terminal::Terminal(terminal::Terminal::Type::INPUT,-1));
        REQUIRE_THROWS(terminal::Terminal(terminal::Terminal::Type::INPUT, 0, terminal::Terminal::Signal::X, -1));
        REQUIRE_THROWS(terminal::Terminal(terminal::Terminal::Type::INPUT, -1, terminal::Terminal::Signal::X, 1));
        REQUIRE_THROWS(terminal::Terminal(terminal::Terminal::Type::INPUT, 2, terminal::Terminal::Signal::X, 1));
        REQUIRE_THROWS(terminal::Terminal(terminal::Terminal::Type::OUTPUT, 1, terminal::Terminal::Signal::X, -1));
        REQUIRE_THROWS(terminal::Terminal(terminal::Terminal::Type::OUTPUT, -1, terminal::Terminal::Signal::X, 1));
        REQUIRE_THROWS(terminal::Terminal(terminal::Terminal::Type::OUTPUT, 4, terminal::Terminal::Signal::X, 1));

    }
}
TEST_CASE("TerminalMethods", "Setters"){
    SECTION("Setters") {
        terminal::Terminal a;
        a.setType(terminal::Terminal::Type::INPUT);
        REQUIRE(a.getType() == terminal::Terminal::Type::INPUT);
        a.setConnections(1);
        REQUIRE(a.getConnections() == 1);
        a.setSignal(terminal::Terminal::Signal::OFF);
        REQUIRE(a.getSignal() == terminal::Terminal::Signal::OFF);
        a.setSignal(terminal::Terminal::Signal::ON);
        REQUIRE(a.getSignal() == terminal::Terminal::Signal::ON);
        a.setSignal(terminal::Terminal::Signal::X);
        REQUIRE(a.getSignal() == terminal::Terminal::Signal::X);
        a.setSignal(terminal::Terminal::Signal::ON);
        a.setConnections(0);
        REQUIRE(a.getConnections() == 0);
        REQUIRE(a.getSignal() == terminal::Terminal::Signal::X);
        a.setSignal(terminal::Terminal::Signal::ON);
        REQUIRE(a.getSignal() == terminal::Terminal::Signal::X);
        a.setSignal(terminal::Terminal::Signal::OFF);
        REQUIRE(a.getSignal() == terminal::Terminal::Signal::X);
        a.setSignal(terminal::Terminal::Signal::X);
        REQUIRE(a.getSignal() == terminal::Terminal::Signal::X);
        a.setNumber(1);
        REQUIRE(a.getNumber() == 1);

        a.setType(terminal::Terminal::Type::OUTPUT);
        REQUIRE(a.getType() == terminal::Terminal::Type::OUTPUT);
        a.setConnections(1);
        REQUIRE(a.getConnections() == 1);
        a.setSignal(terminal::Terminal::Signal::ON);
        REQUIRE(a.getSignal() == terminal::Terminal::Signal::ON);

    }
    SECTION("SettersException"){
        terminal::Terminal a;
        REQUIRE_THROWS(a.setNumber(-1));
        a.setType(terminal::Terminal::Type::INPUT);
        REQUIRE_THROWS(a.setConnections(-1));
        REQUIRE_THROWS(a.setConnections(2));
        a.setType(terminal::Terminal::Type::OUTPUT);
        REQUIRE_THROWS(a.setConnections(-1));
        REQUIRE_THROWS(a.setConnections(4));
    }
}

TEST_CASE("ConnectAndDisconnectMethods"){
    SECTION("Connect"){
        terminal::Terminal a(terminal::Terminal::Type::OUTPUT, 0,terminal::Terminal::Signal::X, 1);
        terminal::Terminal b(terminal::Terminal::Type::INPUT, 0, terminal::Terminal::Signal::X, 2);
        a.connect(b);
        REQUIRE(a.getConnections() == 1);
        REQUIRE(b.getConnections() == 1);
    }
    SECTION("ConnectExceptions"){
        terminal::Terminal a(terminal::Terminal::Type::OUTPUT, 0,terminal::Terminal::Signal::X, 1);
        terminal::Terminal b(terminal::Terminal::Type::INPUT, 0, terminal::Terminal::Signal::X, 2);
        REQUIRE_THROWS(b.connect(a));
        REQUIRE_THROWS(a.connect(a));
        a.setConnections(3);
        REQUIRE_THROWS(a.connect(b));
        a.setConnections(0);
        b.setConnections(1);
        REQUIRE_THROWS(b.connect(a));
    }
    SECTION("Disconnect"){
        terminal::Terminal a(terminal::Terminal::Type::OUTPUT, 1,terminal::Terminal::Signal::X, 1);
        terminal::Terminal b(terminal::Terminal::Type::INPUT, 1, terminal::Terminal::Signal::X, 2);
        a.disconnect(b);
        REQUIRE(a.getConnections() == 0);
        REQUIRE(b.getConnections() == 0);
    }
    SECTION("DisconnectExcept"){
        terminal::Terminal a(terminal::Terminal::Type::OUTPUT, 1,terminal::Terminal::Signal::X, 1);
        terminal::Terminal b(terminal::Terminal::Type::INPUT, 1, terminal::Terminal::Signal::X, 2);
        REQUIRE_THROWS(b.disconnect(a));
        REQUIRE_THROWS(a.disconnect(a));
        a.setConnections(0);
        REQUIRE_THROWS(a.disconnect(b));
        a.setConnections(1);
        b.setConnections(0);
        REQUIRE_THROWS(a.disconnect(b));
    }
}

TEST_CASE("IncreaseDecreaseMethods"){
    SECTION("Increase"){
        terminal::Terminal a(terminal::Terminal::Type::INPUT, 1);
        terminal::Terminal b(terminal::Terminal::Type::OUTPUT, 2);
        a.increaseConnections();
        b.increaseConnections();
        REQUIRE(a.getConnections() == 1);
        REQUIRE(b.getConnections() == 1);
    }
    SECTION("IncreaseExceptions"){
        terminal::Terminal a(terminal::Terminal::Type::INPUT, 1, terminal::Terminal::Signal::X, 1);
        terminal::Terminal b(terminal::Terminal::Type::OUTPUT, 3, terminal::Terminal::Signal::X, 2);
        REQUIRE_THROWS(a.increaseConnections());
        REQUIRE_THROWS(b.increaseConnections());
    }
    SECTION("Decrease"){
        terminal::Terminal a(terminal::Terminal::Type::INPUT, 1, terminal::Terminal::Signal::X, 1);
        terminal::Terminal b(terminal::Terminal::Type::OUTPUT, 1, terminal::Terminal::Signal::X, 2);
        a.decreaseConnections();
        b.decreaseConnections();
        REQUIRE(a.getConnections() == 0);
        REQUIRE(b.getConnections() == 0);
    }
    SECTION("DecreaseExceptions"){
        terminal::Terminal a(terminal::Terminal::Type::INPUT, 1);
        terminal::Terminal b(terminal::Terminal::Type::OUTPUT, 2);
        REQUIRE_THROWS(a.decreaseConnections());
        REQUIRE_THROWS(b.decreaseConnections());
    }
}

TEST_CASE("StreamMethods"){
    SECTION("StreamMethods"){
        SECTION("OutputMethods"){
            terminal::Terminal a1(terminal::Terminal::Type::INPUT, 1, terminal::Terminal::Signal::OFF, 1);
            terminal::Terminal a2(terminal::Terminal::Type::INPUT, 1, terminal::Terminal::Signal::ON, 1);
            terminal::Terminal a3(terminal::Terminal::Type::OUTPUT, 1, terminal::Terminal::Signal::X, 1);
            std::stringstream ss1, ss2, ss3;
            std::string s1("Terminal number is 1\nType of terminal is Input\nNumber of connections is 1\nState of signal is 0\n");
            std::string s2("Terminal number is 1\nType of terminal is Input\nNumber of connections is 1\nState of signal is 1\n");
            std::string s3("Terminal number is 1\nType of terminal is Output\nNumber of connections is 1\nState of signal is X\n");
            a1.print(ss1);
            a2.print(ss2);
            a3.print(ss3);
            REQUIRE(ss1.str() == s1);
            REQUIRE(ss2.str() == s2);
            REQUIRE(ss3.str() == s3);
        }
        SECTION("InputMethods"){
            std::stringstream ss1("0 0 0 0 ");
            terminal::Terminal a1(terminal::Terminal::Type::INPUT, 1, terminal::Terminal::Signal::ON, 1);
            a1.scan(ss1);
            REQUIRE(a1.getNumber() == 0);
            REQUIRE(a1.getType() == terminal::Terminal::Type::OUTPUT);
            REQUIRE(a1.getConnections() == 0);
            REQUIRE(a1.getSignal() == terminal::Terminal::Signal::OFF);
        }

    }
    SECTION("StreamOperators"){
        SECTION("OutputOperator") {
            std::string s1;
            std::stringstream ss1, ss2, ss3, ss4, ss5, ss6;
            terminal::Terminal a1(terminal::Terminal::Type::INPUT, 1, terminal::Terminal::Signal::OFF, 0);
            terminal::Terminal a2(terminal::Terminal::Type::INPUT, 1, terminal::Terminal::Signal::ON, 0);
            terminal::Terminal a3(terminal::Terminal::Type::INPUT, 1, terminal::Terminal::Signal::X, 0);
            terminal::Terminal a4(terminal::Terminal::Type::OUTPUT, 1, terminal::Terminal::Signal::OFF, 0);
            terminal::Terminal a5(terminal::Terminal::Type::OUTPUT, 1, terminal::Terminal::Signal::ON, 0);
            terminal::Terminal a6(terminal::Terminal::Type::OUTPUT, 1, terminal::Terminal::Signal::X, 0);
            s1 = "Terminal number is 0\nType of terminal is Input\nNumber of connections is 1\nState of signal is 0\n";
            ss1 << a1;
            REQUIRE(ss1.str() == s1);
            s1 = "Terminal number is 0\nType of terminal is Input\nNumber of connections is 1\nState of signal is 1\n";
            ss2 << a2;
            REQUIRE(ss2.str() == s1);
            s1 = "Terminal number is 0\nType of terminal is Input\nNumber of connections is 1\nState of signal is X\n";
            ss3 << a3;
            REQUIRE(ss3.str() == s1);
            s1 = "Terminal number is 0\nType of terminal is Output\nNumber of connections is 1\nState of signal is 0\n";
            ss4 << a4;
            REQUIRE(ss4.str() == s1);
            s1 = "Terminal number is 0\nType of terminal is Output\nNumber of connections is 1\nState of signal is 1\n";
            ss5 << a5;
            REQUIRE(ss5.str() == s1);
            s1 = "Terminal number is 0\nType of terminal is Output\nNumber of connections is 1\nState of signal is X\n";
            ss6 << a6;
            REQUIRE(ss6.str() == s1);
        }
        SECTION("InputOperator"){
            terminal::Terminal a1(terminal::Terminal::Type::INPUT, 1, terminal::Terminal::Signal::X, 1);
            terminal::Terminal a2(a1);
            std::stringstream ss1("0 0 0 0 "), ss2("-1 0 0 0 "), ss3("0 -1 0 0 "), ss4("0 0 -1 0 ")
                            , ss5("0 0  0 -1 "), ss6("0 1 3 2 "), ss7("0 1 0 0 ");

            ss1>>a1;
            REQUIRE(a1.getNumber() == 0);
            REQUIRE(a1.getType() == terminal::Terminal::Type::OUTPUT);
            REQUIRE(a1.getConnections() == 0);
            REQUIRE(a1.getSignal() == terminal::Terminal::Signal::OFF);
            ss2>>a2;
            REQUIRE(ss2.fail());
            REQUIRE(a2.getNumber() == 1);
            REQUIRE(a2.getType() == terminal::Terminal::Type::INPUT);
            REQUIRE(a2.getConnections() == 1);
            REQUIRE(a2.getSignal() == terminal::Terminal::Signal::X);
            ss3>>a2;
            REQUIRE(ss2.fail());
            REQUIRE(a2.getNumber() == 1);
            REQUIRE(a2.getType() == terminal::Terminal::Type::INPUT);
            REQUIRE(a2.getConnections() == 1);
            REQUIRE(a2.getSignal() == terminal::Terminal::Signal::X);
            ss4>>a2;
            REQUIRE(ss2.fail());
            REQUIRE(a2.getNumber() == 1);
            REQUIRE(a2.getType() == terminal::Terminal::Type::INPUT);
            REQUIRE(a2.getConnections() == 1);
            REQUIRE(a2.getSignal() == terminal::Terminal::Signal::X);
            ss5>>a2;
            REQUIRE(ss2.fail());
            REQUIRE(a2.getNumber() == 1);
            REQUIRE(a2.getType() == terminal::Terminal::Type::INPUT);
            REQUIRE(a2.getConnections() == 1);
            REQUIRE(a2.getSignal() == terminal::Terminal::Signal::X);
            ss6>>a2;
            REQUIRE(ss2.fail());
            REQUIRE(a2.getNumber() == 1);
            REQUIRE(a2.getType() == terminal::Terminal::Type::INPUT);
            REQUIRE(a2.getConnections() == 1);
            REQUIRE(a2.getSignal() == terminal::Terminal::Signal::X);
            ss7>>a2;
            REQUIRE(ss2.fail());
            REQUIRE(a2.getNumber() == 1);
            REQUIRE(a2.getType() == terminal::Terminal::Type::INPUT);
            REQUIRE(a2.getConnections() == 1);
            REQUIRE(a2.getSignal() == terminal::Terminal::Signal::X);
            
        }
    }

}

TEST_CASE("VectorConstructors"){
    SECTION("DefaultConstructor"){
        vector::Vector<int> a;
        REQUIRE(a.getSize() == 0);
        REQUIRE(a.getCapacity() == 5);
    }
    SECTION("ConstructorWithCapacity"){
        vector::Vector<int> a1(10);
        REQUIRE(a1.getSize() == 0);
        REQUIRE(a1.getCapacity() == 10);
        vector::Vector<int> a2(0);
        REQUIRE(a2.getSize() == 0);
        REQUIRE(a2.getCapacity() == 5);
    }
    SECTION("CopyConstructor"){
        vector::Vector<int> a1(10);
        for(int i{0}; i < 10; ++i)
            a1.pushback(1);
        vector::Vector<int> a2(a1);
        REQUIRE(a2.getSize() == 10);
        REQUIRE(a2.getCapacity() == 10);
        for(int i{0}; i < 10; ++i)
            REQUIRE(a2[i] == 1);
    }
    SECTION("MoveConstructor"){
        vector::Vector<int> a0(10);
        for(int i{0}; i < 10; ++i)
            a0.pushback(1);
        vector::Vector<int> a1(std::move(a0));
        REQUIRE(a1.getCapacity() == 10);
        REQUIRE(a1.getSize() == 10);
        for(int i{0}; i < 10; ++i)
            REQUIRE(a1[i] == 1);
    }
    SECTION("ConstructorsExceptions"){
        REQUIRE_THROWS(vector::Vector<int>(-1));
    }
}

TEST_CASE("VectorMethods"){
    SECTION("Pushback"){
        vector::Vector<int> a1;
        int i{0};
        for(i ; i <5; ++i)
            a1.pushback(i);
        for(i = 0; i < 5; ++i)
            REQUIRE(a1[i] == i);
        for(i; i<10; ++i)
            a1.pushback(i);
        for(i = 0; i < 10; ++i)
            REQUIRE(a1[i] == i);
    }SECTION("Clear"){
        vector::Vector<int> a1(10);
        a1.clear();
        REQUIRE(a1.getCapacity() == 5);
        REQUIRE(a1.getSize() == 0);
    }
}

TEST_CASE("VectorOperators"){
    SECTION("AssignmentOperators"){
        vector::Vector<int> a1(10), a2(10);
        vector::Vector<int> a3, a4;
        int i{0};
        for(i; i < 10; ++i){
            a1.pushback(i);
            a2.pushback(i);
        }
        for(i = 0; i < 5; ++i)
            a4.pushback(-i);
        a3 = a1;
        REQUIRE(a3.getSize() == 10);
        REQUIRE(a3.getCapacity() == 10);
        for(i = 0; i < 10; ++i)
            REQUIRE(a3[i] == i);
        a4 = std::move(a2);
        REQUIRE(a4.getCapacity() == 10);
        REQUIRE(a4.getSize() == 10);
        REQUIRE(a2.getSize() == 5);
        REQUIRE(a2.getCapacity() == 5);
        for(i = 0; i < 10; ++i)
            REQUIRE(a4[i] == i);
        for(i = 0; i < 5; ++i)
            REQUIRE(a2[i] == -i);
        REQUIRE_THROWS(a2[-1]);
    }
}

TEST_CASE("StructuresForLogicElement"){
    SECTION("Constructors"){
        logicElement::DefStruct a(10);
        REQUIRE(a.getLength() == 10);
        REQUIRE(a.getInput() == 0);
        REQUIRE(a.getOutput() == 0);
    }SECTION("Methods"){
        logicElement::DefStruct a(3);
        std::stringstream ss1("1 0 1 1 0 0 1 1 ");
        a.scan(ss1);
        REQUIRE(a.getInput() == 2);
        REQUIRE(a.getOutput() == 1);
        REQUIRE(a.getDefinitions()[0].getType() == terminal::Terminal::Type::INPUT);
        REQUIRE(a.getDefinitions()[0].getConnections() == 0);
        REQUIRE(a.getDefinitions()[0].getSignal() == terminal::Terminal::Signal::X);
        REQUIRE(a.getDefinitions()[1].getType() == terminal::Terminal::Type::INPUT);
        REQUIRE(a.getDefinitions()[1].getConnections() == 1);
        REQUIRE(a.getDefinitions()[1].getSignal() == terminal::Terminal::Signal::OFF);
        REQUIRE(a.getDefinitions()[2].getType() == terminal::Terminal::Type::OUTPUT);
        REQUIRE(a.getDefinitions()[2].getConnections() == 1);
        REQUIRE(a.getDefinitions()[2].getSignal() == terminal::Terminal::Signal::ON);
    }

}
TEST_CASE("LogicElementConstructors"){
    SECTION("DefaultConstructor"){
        logicElement::LogicElement a;
        REQUIRE(a.getNumber() == 0);
    }
    SECTION("ConstructorWithNumberOFTerminals"){
        logicElement::LogicElement a(10,10,1);
        REQUIRE(a.getNumber() == 1);
        REQUIRE(a.getNumberOfInput() == 10);
        REQUIRE(a.getNumberOfOutput() == 10);
    }
    SECTION("ConstructorWithDefinitions"){
        logicElement::DefStruct def(3);
        std::stringstream ss1("1 1 1 1 0 0 1 2 ");
        def.scan(ss1);
        logicElement::LogicElement a(def,1);
        REQUIRE(a.getNumber() == 1);
        REQUIRE(a.getNumberOfInput() == 2);
        REQUIRE(a.getNumberOfOutput() == 1);
        REQUIRE(a.getNumberOfTerminals() == 3);
        REQUIRE(a[0].getNumber() == 1);
        REQUIRE(a[0].getType() == terminal::Terminal::Type::INPUT);
        REQUIRE(a[0].getConnections() == 1);
        REQUIRE(a[0].getSignal() == terminal::Terminal::Signal::ON);
        REQUIRE(a[1].getNumber() == 2);
        REQUIRE(a[1].getType() == terminal::Terminal::Type::INPUT);
        REQUIRE(a[1].getConnections() == 0);
        REQUIRE(a[1].getSignal() == terminal::Terminal::Signal::X);
        REQUIRE(a[2].getNumber() == 1);
        REQUIRE(a[2].getType() == terminal::Terminal::Type::OUTPUT);
        REQUIRE(a[2].getConnections() == 1);
        REQUIRE(a[2].getSignal() == terminal::Terminal::Signal::X);
    }
}

TEST_CASE("LogicElementMethods"){
    SECTION("Input"){
        logicElement::LogicElement a;
        std::stringstream ss1("2 1 1 1 0 1 1 ");
        a.scan(ss1);
        REQUIRE(a.getNumberOfInput() == 1);
        REQUIRE(a.getNumberOfOutput() == 1);
        REQUIRE(a[0].getNumber() == 1);
        REQUIRE(a[0].getType() == terminal::Terminal::Type::INPUT);
        REQUIRE(a[0].getConnections() == 1);
        REQUIRE(a[0].getSignal() == terminal::Terminal::Signal::ON);
        REQUIRE(a[1].getNumber() == 1);
        REQUIRE(a[1].getType() == terminal::Terminal::Type::OUTPUT);
        REQUIRE(a[1].getConnections() == 1);
        REQUIRE(a[1].getSignal() == terminal::Terminal::Signal::ON);
    }SECTION("Output"){
        logicElement::LogicElement a(1,1,1);
        std::stringstream ss1;
        std::string s("Number of logic element is 1\nNumber of input terminals is 1\nTheir states are\n\n"
                      "Terminal number is 1\nType of terminal is Input\nNumber of connections is 0\nState of signal is X\n\n"
                      "Number of output terminals is 1\nTheir states are\n\n"
                      "Terminal number is 1\nType of terminal is Output\nNumber of connections is 0\nState of signal is X\n\n");
        a.print(ss1);
        REQUIRE(ss1.str() == s);
    }SECTION("AddTerminal"){
        logicElement::LogicElement a;
        terminal::Terminal b(terminal::Terminal::Type::INPUT, 1, terminal::Terminal::Signal::ON, 1);
        terminal::Terminal c(terminal::Terminal::Type::OUTPUT, 1, terminal::Terminal::Signal::X, 1);
        a.addTerminal(b);
        REQUIRE(a.getNumberOfInput() == 1);
        REQUIRE(a.getNumberOfOutput() == 0);
        REQUIRE(a[0].getNumber() ==1);
        REQUIRE(a[0].getType() == terminal::Terminal::Type::INPUT);
        REQUIRE(a[0].getConnections() == 1);
        REQUIRE(a[0].getSignal() == terminal::Terminal::Signal::ON);
        a.addTerminal(c);
        REQUIRE(a.getNumberOfInput() == 1);
        REQUIRE(a.getNumberOfOutput() == 1);
        REQUIRE(a[1].getNumber() ==1);
        REQUIRE(a[1].getType() == terminal::Terminal::Type::OUTPUT);
        REQUIRE(a[1].getConnections() == 1);
        REQUIRE(a[1].getSignal() == terminal::Terminal::Signal::X);
    }SECTION("Connect"){
        logicElement::LogicElement a(1,1,1), b(1,1,1);
        REQUIRE(a[1].getConnections() == 0);
        REQUIRE(b[0].getConnections() == 0);
        a.connect(b);
        REQUIRE(a[1].getConnections() == 1);
        REQUIRE(b[0].getConnections() == 1);
        REQUIRE_THROWS(a.connect(b));
        REQUIRE_THROWS(a.connect(a));
        logicElement::LogicElement c;
        REQUIRE_THROWS(c.connect(b));
    }SECTION("GetTerminal"){
        logicElement::LogicElement a(2,2,1);
        REQUIRE(a.getTerminal(terminal::Terminal::Type::INPUT,2).getType() == terminal::Terminal::Type::INPUT);
        REQUIRE(a.getTerminal(terminal::Terminal::Type::INPUT,2).getNumber() == 2);
        REQUIRE(a.getTerminal(terminal::Terminal::Type::OUTPUT,1).getType() == terminal::Terminal::Type::OUTPUT);
        REQUIRE(a.getTerminal(terminal::Terminal::Type::OUTPUT,1).getNumber() == 1);
    }
}

TEST_CASE("LogicElementOperators"){
    SECTION("OutputOperator"){
        logicElement::LogicElement a(1,1,1);
        std::stringstream ss1;
        std::string s1("Number of logic element is 1\nNumber of input terminals is 1\nTheir states are\n\n"
                       "Terminal number is 1\nType of terminal is Input\nNumber of connections is 0\nState of signal is X\n\n"
                       "Number of output terminals is 1\nTheir states are\n\n"
                       "Terminal number is 1\nType of terminal is Output\nNumber of connections is 0\nState of signal is X\n\n");
        ss1<<a;
        REQUIRE(ss1.str() == s1);
    }SECTION("AssignmentOperators"){
        logicElement::LogicElement a;
        a = logicElement::LogicElement(1,1,1);
        REQUIRE(a.getNumber() == 1);
        REQUIRE(a.getNumberOfInput() == 1);
        REQUIRE(a.getNumberOfOutput() == 1);
        logicElement::LogicElement b;
        b = a;
        REQUIRE(b.getNumber() == 1);
        REQUIRE(b.getNumberOfInput() == 1);
        REQUIRE(b.getNumberOfOutput() == 1);
    }SECTION("InputOperator"){


    }
}