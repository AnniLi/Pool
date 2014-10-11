#include "stdafx.h"
#include "Task.h"
#include "ThreadPool.h"



int main(int argc, _TCHAR* argv[])
{
	Task Tasks;
	typedef void func_type;
	std::function<func_type()>ptr;
	ThreadsPool<func_type> Pool1;
	ptr = std::bind(&Task::FirstTask,Tasks,2, 0.5);
	Pool1 +=ptr;
	ptr = std::bind(&Task::SecondTask, Tasks);
	Pool1+=ptr;
	ptr = std::bind(&Task::ThirdTask, Tasks, 0, "Strangers");
	Pool1+=ptr;
	Pool1 + ptr;
	Pool1.Wait();
	Sleep(15000);

	return 0;
}

