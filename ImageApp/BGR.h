#ifndef _BGR_H__
#define _BGR_H__

namespace app
{
	struct BGR
	{
		static const int SIZE;
		static const int OFFSET[];
	};
	const int BGR::OFFSET[] = { 0,1,2 };
	const int BGR::SIZE = 3;
}

#endif // !_BGR_H__
