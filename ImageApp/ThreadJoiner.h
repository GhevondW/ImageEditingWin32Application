#include <thread>
#ifndef _THREAD_JOINER_H__
#define _THREAD_JOINER_H__

namespace app
{

	class ThreadJoiner
	{
	public:
		ThreadJoiner(std::thread& thread)
			:thread_(thread)
		{
		}
		~ThreadJoiner() {
			if (thread_.joinable()) {
				thread_.join();
			}
		}

	private:
		std::thread& thread_;
	};
}

#endif // !_THREAD_JOINER_H__
