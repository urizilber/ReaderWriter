#include "readerwriter.h"
#include <thread>
#include <unistd.h>
#include <iostream>
#include <stack>


ReaderWriter proc;
std::stack<int> mque;
void Thread1()
{
	int counter  = 0;
	while (true)
	{
		sleep(1);
		proc.writeProc();
		mque.push(counter);

		proc.writeEndProc();
		counter++;

	}
}


void Thread2()
{
	while(true){
	 usleep(500);
		 if(!mque.empty()){
		 proc.readerProc();
		 int a = mque.top();
		 std::cout << a <<std::endl;
		 proc.readerEndProc();
		}

	}
}

void Thread3()
{
	while(true){
	 usleep(500);
		 if(!mque.empty()){
		 proc.readerProc();
		 int a = mque.top();
		 std::cout << a <<std::endl;
		 proc.readerEndProc();
		}

	}
}
int main()
{

	std:: thread * th1 = new std::thread(&Thread1);
	
	std::cout << "here"<<std::endl;
	std:: thread * th2 = new std::thread(&Thread2);
	th2->join();
	return 0;
}