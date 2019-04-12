#include "FilterBase.h"
#include "ThreadJoiner.h"


#ifndef _INVERT_FILTER_H__
#define _INVERT_FILTER_H__

namespace app
{
	template<class TYPE = RGBA>
	class InvertFilter :public FilterBase<TYPE>
	{
		typedef Image<TYPE> image;
	public:
		InvertFilter() : FilterBase<TYPE>(){};
		InvertFilter(image* img) : FilterBase<TYPE>(img) {};
		~InvertFilter(){};

	public:

		image* filter()const override {
			image* new_image = new image(this->image_->get_width(), this->image_->get_height());

			auto func = [&](int c) {
				for (int i = 0; i < this->image_->get_height(); i++)
				{
					for (int j = 0; j < this->image_->get_width(); j++)
					{
						unsigned char new_value = 255 - this->image_->at(i, j)[c];
						new_image->at(i, j)[c] = new_value;
					}
				}
			};

			std::thread thread1(func,0);
			ThreadJoiner join1(thread1);
			std::thread thread2(func,1);
			ThreadJoiner join2(thread2);
			std::thread thread3(func,2);
			ThreadJoiner join3(thread3);

			return new_image;
		}

	};

}

#endif // !_INVERT_FILTER_H__

