#ifndef _RGB_H__
#define _RGB_H__

namespace app
{
	struct RGB
	{
		static const int SIZE;
		static const int OFFSET[];
	};
	const int RGB::OFFSET[] = { 2,1,0 };
	const int RGB::SIZE = 3;
}

#endif // !_RGBA_H__
