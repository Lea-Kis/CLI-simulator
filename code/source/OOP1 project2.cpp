#include "Interpreter.h"
#include"Parser.h"
#include <iostream>

int main()
{
    try {
        Interpreter::Instance()->run();
    }
    catch (const std::exception& e) {
        std::cerr << "Error:" << e.what() << '\n';
        return 1;
    }
    return 0;
}
