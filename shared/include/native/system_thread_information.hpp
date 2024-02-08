#ifndef STHREADI_H
#define STHREADI_H

namespace nt
{
	struct SYSTEM_THREAD_INFORMATION
	{
		LARGE_INTEGER KernelTime;
		LARGE_INTEGER UserTime;
		LARGE_INTEGER CreateTime;
		unsigned long WaitTime;
		void *StartAddress;
		CLIENT_ID ClientId;
		KPRIORITY Priority;
		long BasePriority;
		unsigned long ContextSwitches;
		unsigned long ThreadState;
		KWAIT_REASON WaitReason;
	};

	struct SYSTEM_EXTENDED_THREAD_INFORMATION
	{
		SYSTEM_THREAD_INFORMATION ThreadInfo;
		void *StackBase;
		void *StackLimit;
		void *Win32StartAddress;
		void *TebBase; // since VISTA
		unsigned long long Reserved2;
		unsigned long long Reserved3;
		unsigned long long Reserved4;
	};

	struct THREAD_TIMES_INFORMATION
	{
		LARGE_INTEGER CreationTime;
		LARGE_INTEGER ExitTime;
		LARGE_INTEGER KernelTime;
		LARGE_INTEGER UserTime;
	};
}

#endif
