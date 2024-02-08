#ifndef SPI_H
#define SPI_H

namespace nt
{
	struct SYSTEM_PERFORMANCE_INFORMATION
	{
		LARGE_INTEGER IdleProcessTime;
		LARGE_INTEGER IoReadTransferCount;
		LARGE_INTEGER IoWriteTransferCount;
		LARGE_INTEGER IoOtherTransferCount;
		unsigned long IoReadOperationCount;
		unsigned long IoWriteOperationCount;
		unsigned long IoOtherOperationCount;
		unsigned long AvailablePages;
		unsigned long CommittedPages;
		unsigned long CommitLimit;
		unsigned long PeakCommitment;
		unsigned long PageFaultCount;
		unsigned long CopyOnWriteCount;
		unsigned long TransitionCount;
		unsigned long CacheTransitionCount;
		unsigned long DemandZeroCount;
		unsigned long PageReadCount;
		unsigned long PageReadIoCount;
		unsigned long CacheReadCount;
		unsigned long CacheIoCount;
		unsigned long DirtyPagesWriteCount;
		unsigned long DirtyWriteIoCount;
		unsigned long MappedPagesWriteCount;
		unsigned long MappedWriteIoCount;
		unsigned long PagedPoolPages;
		unsigned long NonPagedPoolPages;
		unsigned long PagedPoolAllocs;
		unsigned long PagedPoolFrees;
		unsigned long NonPagedPoolAllocs;
		unsigned long NonPagedPoolFrees;
		unsigned long FreeSystemPtes;
		unsigned long ResidentSystemCodePage;
		unsigned long TotalSystemDriverPages;
		unsigned long TotalSystemCodePages;
		unsigned long NonPagedPoolLookasideHits;
		unsigned long PagedPoolLookasideHits;
		unsigned long AvailablePagedPoolPages;
		unsigned long ResidentSystemCachePage;
		unsigned long ResidentPagedPoolPage;
		unsigned long ResidentSystemDriverPage;
		unsigned long CcFastReadNoWait;
		unsigned long CcFastReadWait;
		unsigned long CcFastReadResourceMiss;
		unsigned long CcFastReadNotPossible;
		unsigned long CcFastMdlReadNoWait;
		unsigned long CcFastMdlReadWait;
		unsigned long CcFastMdlReadResourceMiss;
		unsigned long CcFastMdlReadNotPossible;
		unsigned long CcMapDataNoWait;
		unsigned long CcMapDataWait;
		unsigned long CcMapDataNoWaitMiss;
		unsigned long CcMapDataWaitMiss;
		unsigned long CcPinMappedDataCount;
		unsigned long CcPinReadNoWait;
		unsigned long CcPinReadWait;
		unsigned long CcPinReadNoWaitMiss;
		unsigned long CcPinReadWaitMiss;
		unsigned long CcCopyReadNoWait;
		unsigned long CcCopyReadWait;
		unsigned long CcCopyReadNoWaitMiss;
		unsigned long CcCopyReadWaitMiss;
		unsigned long CcMdlReadNoWait;
		unsigned long CcMdlReadWait;
		unsigned long CcMdlReadNoWaitMiss;
		unsigned long CcMdlReadWaitMiss;
		unsigned long CcReadAheadIos;
		unsigned long CcLazyWriteIos;
		unsigned long CcLazyWritePages;
		unsigned long CcDataFlushes;
		unsigned long CcDataPages;
		unsigned long ContextSwitches;
		unsigned long FirstLevelTbFills;
		unsigned long SecondLevelTbFills;
		unsigned long SystemCalls;
		unsigned long long CcTotalDirtyPages;	 // since THRESHOLD
		unsigned long long CcDirtyPageThreshold; // since THRESHOLD
		long long ResidentAvailablePages;		 // since THRESHOLD
		unsigned long long SharedCommittedPages; // since THRESHOLD
	};
}

#endif
