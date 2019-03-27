#include "stdafx.h"
#include "BoxBlurFilter.h"
#include "ThreadJoiner.h"
#include <mutex>
#include "BoxBlurHelper.h"

using namespace app;

BoxBlurFilter::BoxBlurFilter()
	:FilterBase(nullptr),
	helper_(new BoxBlurHelper(1))
{
}

BoxBlurFilter::BoxBlurFilter(Image* image,BoxBlurHelper* helper)
	:FilterBase(image),
	helper_(helper)
{
	
}

BoxBlurFilter::~BoxBlurFilter()
{
}

void BoxBlurFilter::horizontal_motion_blur(Image* new_image)const {
	
	int radius_ = helper_->get_value()*2 + 1;

	auto func = [&](int c) {
		for (size_t i = 0; i < image_->get_height(); i++)
		{
			int sum = 0;
			int result_avg = 0;

			for (size_t x = 0; x < radius_; x++)
			{
				auto pixel = image_->at(i, x);
				sum += pixel[c];
			}
			result_avg = sum / radius_;

			for (int j = 0; j < image_->get_width(); j++)
			{
				if (j - radius_ / 2 >= 0 && j + 1 + radius_ / 2 < image_->get_width()) {
					auto temp_old_pixel = image_->at(i, j - radius_ / 2);

					sum -= temp_old_pixel[c];
					

					auto temp_new_pixel = image_->at(i, j + 1 + radius_ / 2);
					sum += temp_new_pixel[c];
					
					result_avg = sum / radius_;					

				}
				
				new_image->at(i, j)[c] = result_avg;
			}
		}
	};
	
	std::thread thread_red(func,0);
	std::thread thread_green(func,1);
	std::thread thread_blue(func,2);

	ThreadJoiner join_red(thread_red);
	ThreadJoiner join_green(thread_green);
	ThreadJoiner join_blue(thread_blue);

}

void BoxBlurFilter::vertical_motion_blur(Image* new_image)const {

	int radius_ = helper_->get_value()*2 + 1;

	auto func = [&](int c) {
		for (size_t j = 0; j < image_->get_width(); j++) {
			
			int sum = 0;
			int result_avg = 0;
			for (size_t x = 0; x < radius_; x++)
			{
				auto pixel = image_->at(x, j);
				sum += pixel[c];
				
			}
			result_avg = sum / radius_;
			for (int i = 0; i < image_->get_height(); i++)
			{
				if (i - radius_ / 2 >= 0 && i + 1 + radius_ / 2 < image_->get_height()) {
					auto temp_old_pixel = image_->at(i - radius_ / 2, j);

					sum -= temp_old_pixel[c];

					auto temp_new_pixel = image_->at(i + 1 + radius_ / 2, j);
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

Image* BoxBlurFilter::filter() const{
	Image* new_image = new Image(image_->get_width(), image_->get_height());
	horizontal_motion_blur(new_image);
	vertical_motion_blur(new_image);
	return new_image;
}

