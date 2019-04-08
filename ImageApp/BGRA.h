#ifndef _BGRA_H__
#define _BGRA_H__

namespace app
{
	struct BGRA
	{
		static const int SIZE;
		static const int OFFSET[];
	};
	const int BGRA::OFFSET[] = { 0,1,2,3 };
	const int BGRA::SIZE = 4;
}

#endif // !_RGBA_H__