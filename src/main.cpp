#include <iostream>

#include "BreakAll.h"

int main()
{
    std::cout << "Hello World!" << std::endl;
    BreakAll::Initialize();
    BreakAll::Run();
    BreakAll::Terminate();
    return 0;
}
