#include "Image.h"

#ifndef _FILTER_BASE_H__
#define _FILTER_BASE_H__
namespace app 
{
	template<class TYPE = RGBA>
	class FilterBase
	{
	public:
		FilterBase(Image<TYPE>* img) {
			image_ = img;
		}
		FilterBase() {
			image_ = nullptr;
		}
		virtual ~FilterBase() {};

	public:

		virtual Image<TYPE>* filter()const = 0;

	protected:
		Image<TYPE>* image_;
	};

}
#endif // !_FILTER_BASE_H__

