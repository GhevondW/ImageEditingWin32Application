#include "FilterBase.h"
#include "BoxBlurHelper.h"
#include <thread>
#include "ThreadJoiner.h"


#ifndef _BOX_BLUR_FILTER_H__
#define _BOX_BLUR_FILTER_H__

namespace app
{
	template<class TYPE = RGBA>
	class BoxBlurFilter :
		public FilterBase<TYPE>
	{
		typedef Image<TYPE> image;
	public:
		BoxBlurFilter() :FilterBase<TYPE>() 
		{
			helper_ = nullptr;
		}
		BoxBlurFilter(image* image, BoxBlurHelper* helper) 
			:FilterBase<TYPE>(image)
		{
			helper_ = helper;
		}
		virtual ~BoxBlurFilter() {}

		image* filter() const override {
			image* new_image = new image(this->image_->get_width(), this->image_->get_height());
			horizontal_motion_blur(new_image);
			vertical_motion_blur(new_image);
			return new_image;
		}

	private:

		void horizontal_motion_blur(image* new_image) const {
		
			int radius_ = helper_->get_value() * 2 + 1;

			auto func = [&](int c) {
				for (size_t i = 0; i < this->image_->get_height(); i++)
				{
					int sum = 0;
					int result_avg = 0;

					for (size_t x = 0; x < radius_; x++)
					{
						auto pixel = this->image_->at(i, x);
						sum += pixel[c];
					}
					result_avg = sum / radius_;

					for (int j = 0; j < this->image_->get_width(); j++)
					{
						if (j - radius_ / 2 >= 0 && j + 1 + radius_ / 2 < this->image_->get_width()) {
							auto temp_old_pixel = this->image_->at(i, j - radius_ / 2);

							sum -= temp_old_pixel[c];


							auto temp_new_pixel = this->image_->at(i, j + 1 + radius_ / 2);
							sum += temp_new_pixel[c];

							result_avg = sum / radius_;

						}

						new_image->at(i, j)[c] = result_avg;
					}
				}
			};

			std::thread thread_red(func, 0);
			std::thread thread_green(func, 1);
			std::thread thread_blue(func, 2);

			ThreadJoiner join_red(thread_red);
			ThreadJoiner join_green(thread_green);
			ThreadJoiner join_blue(thread_blue);

		}
		void vertical_motion_blur(image* new_image) const {
			int radius_ = helper_->get_value() * 2 + 1;

			auto func = [&](int c) {
				for (size_t j = 0; j < this->image_->get_width(); j++) {

					int sum = 0;
					int result_avg = 0;
					for (size_t x = 0; x < radius_; x++)
					{
						auto pixel = this->image_->at(x, j);
						sum += pixel[c];

					}
					result_avg = sum / radius_;
					for (int i = 0; i < this->image_->get_height(); i++)
					{
						if (i - radius_ / 2 >= 0 && i + 1 + radius_ / 2 < this->image_->get_height()) {
							auto temp_old_pixel = this->image_->at(i - radius_ / 2, j);

							sum -= temp_old_pixel[c];

							auto temp_new_pixel = this->image_->at(i + 1 + radius_ / 2, j);
							sum += temp_new_pixel[c];

							result_avg = sum / radius_;

						}
						new_image->at(i, j)[c] = result_avg;
					}
				}
			};

			std::thread thread_red(func, 0);
			std::thread thread_green(func, 1);
			std::thread thread_blue(func, 2);

			ThreadJoiner join_red(thread_red);
			ThreadJoiner join_green(thread_green);
			ThreadJoiner join_blue(thread_blue);
		}

	private:
		BoxBlurHelper* helper_;
	};

}
#endif // !_BOX_BLUR_FILTER_H__



