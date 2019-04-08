#ifndef _RGBA_H__
#define _RGBA_H__

namespace app 
{
	struct RGBA
	{
		static const int SIZE;
		static const int OFFSET[];
	};
	const int RGBA::OFFSET[] = { 2,1,0,3 };
	const int RGBA::SIZE = 4;
}

#endif // !_RGBA_H__

