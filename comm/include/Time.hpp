#pragma once
#include "General.h"
#include <time.h>
namespace Time {
	 std::string ToString(time_t time_);
	time_t FileTimeToTime(const FILETIME &ft);
	namespace Now {
		std::string ToString(const std::string &format = "yyyy-MM-dd hh:mm:ss");
		template<class T>
		//统计函数耗时时间
		inline time_t StopWatch(const T&_func) {
			auto beg_t = std::chrono::system_clock::now();    //起始时间
			_func();
			auto end_t = std::chrono::system_clock::now();    //结束时间
			std::chrono::duration<double> diff = end_t - beg_t;//时间间隔s
			time_t total = std::chrono::duration_cast<std::chrono::milliseconds>(diff).count();//时间间隔ms
			printf("Elapsed :%d ms\n", total);
			return total;
		}
	}
};
