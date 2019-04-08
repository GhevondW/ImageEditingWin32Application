#include "FilterBase.h"
#include <thread>
#include "ThreadJoiner.h"

#ifndef _BWFILTER_H__
#define _BWFILTER_H__
namespace app
{
	template<class TYPE = RGBA>
	class BWFilter : public FilterBase<TYPE>
	{
		typedef Image<TYPE> image;

	public:

		BWFilter() :FilterBase<TYPE>() {}
		BWFilter(image* image) :FilterBase<TYPE>(image) {}
		virtual ~BWFilter() {}

		image* filter()const override {
		
			image* new_image = new image(this->image_->get_width(), this->image_->get_height());

			int middle = new_image->get_height() / 2;

			auto func = [&](int begin, int end) {
				for (size_t i = begin; i < end; i++)
				{
					for (size_t j = 0; j < new_image->get_width(); j++)
					{
						int r = (int)this->image_->at(i, j)[0];
						int g = (int)this->image_->at(i, j)[1];
						int b = (int)this->image_->at(i, j)[2];
						int avg = (r + g + b) / 3;

						new_image->at(i, j) = std::move(Pixel<TYPE>(avg, avg, avg));
					}
				}
			};

			std::thread t1(func, 0, middle);
			ThreadJoiner join1(t1);

			std::thread t2(func, middle, new_image->get_height());
			ThreadJoiner join2(t2);

			return new_image;

		}
	};

}

#endif // !_BWFILTER_H__

