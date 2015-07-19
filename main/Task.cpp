#include "stdafx.h"
#include "Task.h"

#define SECOND_TASK_ITERATIONS 20

void FirstTask(int numberOfPrints, double printValue)
{
    for (int i = 0; i < numberOfPrints; ++i)
    {
        std::cout << printValue << std::endl;
    Sleep(1);
    }
}

 void SecondTask()
{
    for (int i = 0; i < SECOND_TASK_ITERATIONS; ++i)
    {
        std::cout << "Second" << std::endl;
        Sleep(2);
    }
}

 void ThirdTask(int numberOfPrints, std::string printedString)
{
    for (int i = 0; i < numberOfPrints; ++i)
    {
        std::cout << printedString.c_str() << std::endl;
        Sleep(3);
    }
}
 void FouthTask(int numberOfPrints, std::string printedString)
{
    for (int i = 0; i < numberOfPrints; ++i)
    {
        std::cout << printedString.c_str() << std::endl;
        Sleep(1);
    }
}
