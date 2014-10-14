#include "stdafx.h"

#include "Task.h"
#include "ThreadPool.h"

int main()
{
    typedef void func_type;
    std::function<func_type()>ptr;
    ThreadPool<func_type> exPool;
    ptr = std::bind(&FirstTask, 10, 1.0);
    exPool += ptr;
    ptr = &SecondTask;
    exPool += ptr;
    ptr = std::bind(&ThirdTask, 30, "3");
    exPool += ptr;
    ptr = std::bind(&ThirdTask, 20, "4");
    exPool + ptr;
    ptr = std::bind(&FouthTask, 50, "Five");
    exPool.PushBack(ptr, 10);
    Sleep(10000);
    return 0;
}
