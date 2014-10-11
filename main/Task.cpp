#include "stdafx.h"
#include "Task.h"



void Task::FirstTask(int k, double s)
{
	std::cout << "Two different argument!" << std::endl;
	Sleep(3000);
	std::cout << "Two different argument is ended!" << std::endl;
}
 void Task::SecondTask()
{
	std::cout << "No arguments!" << std::endl;
	Sleep(8000);
	std::cout << "No arguments is ended!" << std::endl;

}

 void Task::ThirdTask(int k, std::string u)
{
	std::cout << "And more!" << std::endl;
	Sleep(8000);
	std::cout << "And more is ended!" << std::endl;
	return ;
}
 void Task::FiveTask(int k, std::string u)
 {
	 std::cout << "Five!" << std::endl;
	 Sleep(1000);
	 return;
 }


