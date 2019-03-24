#include "stdafx.h"
#include "BoxBlurFilter.h"
using namespace app;

BoxBlurFilter::BoxBlurFilter()
	:FilterBase(nullptr),
	radius_(1)
{
}

BoxBlurFilter::BoxBlurFilter(Image* image,int radius) 
	:FilterBase(image)
{
	if (radius > 0 && radius <= 15) {
		radius_ = radius*2 + 1;
	}
	else {
		radius_ = 3;
	}
}

BoxBlurFilter::~BoxBlurFilter()
{
}

void BoxBlurFilter::horizontal_motion_blur(Image* new_image)const {
	for (size_t i = 0; i < image_->get_height(); i++)
	{
		int sum_r = 0;
		int sum_g = 0;
		int sum_b = 0;

		int result_avg_r = 0;
		int result_avg_g = 0;
		int result_avg_b = 0;

		for (size_t x = 0; x < radius_; x++)
		{
			auto pixel = image_->at(i, x);
			sum_r += pixel.get_R();
			sum_g += pixel.get_G();
			sum_b += pixel.get_B();
		}

		result_avg_r = sum_r / radius_;
		result_avg_g = sum_g / radius_;
		result_avg_b = sum_b / radius_;

		for (int j = 0; j < image_->get_width(); j++)
		{
			if (j - radius_ / 2 >= 0 && j + 1 + radius_ / 2 < image_->get_width()) {
				auto temp_old_pixel = image_->at(i, j - radius_ / 2);

				sum_r -= temp_old_pixel.get_R();
				sum_g -= temp_old_pixel.get_G();
				sum_b -= temp_old_pixel.get_B();

				auto temp_new_pixel = image_->at(i, j + 1 + radius_ / 2);
				sum_r += temp_new_pixel.get_R();
				sum_g += temp_new_pixel.get_G();
				sum_b += temp_new_pixel.get_B();

				result_avg_r = sum_r / radius_;
				result_avg_g = sum_g / radius_;
				result_avg_b = sum_b / radius_;

			}
			new_image->at(i, j) = std::move(app::Pixel(result_avg_r,result_avg_g,result_avg_b));
		}

	}
}

void BoxBlurFilter::vertical_motion_blur(Image* new_image)const {
	for (size_t j = 0; j < image_->get_width(); j++)
	{
		int sum_r = 0;
		int sum_g = 0;
		int sum_b = 0;

		int result_avg_r = 0;
		int result_avg_g = 0;
		int result_avg_b = 0;

		for (size_t x = 0; x < radius_; x++)
		{
			auto pixel = image_->at(x, j);
			sum_r += pixel.get_R();
			sum_g += pixel.get_G();
			sum_b += pixel.get_B();
		}

		result_avg_r = sum_r / radius_;
		result_avg_g = sum_g / radius_;
		result_avg_b = sum_b / radius_;

		for (int i = 0; i < image_->get_height(); i++)
		{
			if (i - radius_ / 2 >= 0 && i + 1 + radius_ / 2 < image_->get_height()) {
				auto temp_old_pixel = image_->at(i - radius_ / 2, j);

				sum_r -= temp_old_pixel.get_R();
				sum_g -= temp_old_pixel.get_G();
				sum_b -= temp_old_pixel.get_B();

				auto temp_new_pixel = image_->at(i + 1 + radius_ / 2, j);
				sum_r += temp_new_pixel.get_R();
				sum_g += temp_new_pixel.get_G();
				sum_b += temp_new_pixel.get_B();

				result_avg_r = sum_r / radius_;
				result_avg_g = sum_g / radius_;
				result_avg_b = sum_b / radius_;

			}
			new_image->at(i, j) = std::move(app::Pixel(result_avg_r, result_avg_g, result_avg_b));
		}

	}
}

Image* BoxBlurFilter::filter() const{
	Image* new_image = new Image(image_->get_width(), image_->get_height());
	horizontal_motion_blur(new_image);
	vertical_motion_blur(new_image);
	return new_image;
}

