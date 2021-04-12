#include <thread>
#include <unistd.h>
#include <chrono>
#include <atomic>
#include "readerwriter.h"



using namespace std;

ReaderWriter::ReaderWriter()
{
	AW = 0; 
	WW = 0;
	AR = 0;
	WR = 0;
}
void ReaderWriter::writeProc()
{
	
	std::unique_lock<std::mutex> wrtLck(mlock);
	while(AR >0 || AW > 0)
	{
		WW++;
		cwrt.wait(wrtLck);
		WW--;
	}

	AW++;
	wrtLck.unlock();
}

void ReaderWriter::writeEndProc()
{

	std::unique_lock<std::mutex> wrtLck(mlock);
	AW--;

	///.................///

	if(WW > 0){
		wrtLck.unlock();
		cwrt.notify_one();
		
	}
	else if (WR > 0){
		
		wrtLck.unlock();
		cread.notify_all();
	}
}

void ReaderWriter::readerProc()
{
	std::unique_lock<std::mutex> readLck(mlock);

	while (AW > 0 || WW > 0)
	{
		WR++;
		cread.wait(readLck);
		WR--;
	}
	AR++;
	readLck.unlock();

	/////////

}

void ReaderWriter::readerEndProc()
{
	std::unique_lock<std::mutex> readLck(mlock);

	AR--;

	if( AR == 0 && WW > 0)
	{
		cwrt.notify_one();
	}

	readLck.unlock();
}