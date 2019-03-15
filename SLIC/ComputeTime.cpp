
#include "ComputeTime.h"
#include <iostream>
#include <Windows.h>   //QueryPerformanceFrequency函数需要Windows头文件

ComputeTime::ComputeTime()
{
	Initialized = QueryPerformanceFrequency((LARGE_INTEGER   *)&Frequency);
}

ComputeTime::~ComputeTime()
{

}

bool   ComputeTime::Begin()
{
	if (!Initialized)
		return 0;

	return   QueryPerformanceCounter((LARGE_INTEGER   *)&BeginTime);
}

double   ComputeTime::End()
{
	if (!Initialized)
		return 0;


	__int64   endtime;

	QueryPerformanceCounter((LARGE_INTEGER   *)&endtime);


	__int64   elapsed = endtime - BeginTime;


	return   ((double)elapsed / (double)Frequency)*1000.0;  //单位毫秒
}

bool   ComputeTime::Avaliable()
{
	return Initialized;
}
