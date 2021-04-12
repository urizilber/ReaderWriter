#include <thread>
#include <unistd.h>
#include <chrono>
#include <atomic>

#include <condition_variable>
#include <mutex>

class ReaderWriter
{
	public:

		ReaderWriter();
		void writeProc();
		void writeEndProc();
		void read();
		void readerProc();
		void readerEndProc();
		
	private:

		std::mutex mlock;
		
		std::condition_variable cwrt;
		std::condition_variable cread;
		int AW ;
		int WW;
		int AR;
		int WR;

};