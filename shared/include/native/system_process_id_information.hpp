#ifndef SPIDI_H
#define SPIDI_H

namespace nt
{
	struct SYSTEM_PROCESS_ID_INFORMATION
	{
		void *process_id;
		UNICODE_STRING image_name;
	};
}

#endif
