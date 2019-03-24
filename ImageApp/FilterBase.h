#include "Image.h"

namespace app 
{
#ifndef _FILTER_BASE_H__
#define _FILTER_BASE_H__


	class FilterBase
	{
	public:
		FilterBase(Image* image);
		FilterBase();
		~FilterBase();

	public:

		virtual Image* filter()const = 0;

	protected:
		app::Image* image_;
	};

#endif // !_FILTER_BASE_H__
}


