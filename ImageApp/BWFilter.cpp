#include "stdafx.h"
#include "BWFilter.h"
using namespace app;

BWFilter::BWFilter()
	:FilterBase()
{
}

BWFilter::BWFilter(Image* img) 
	:FilterBase(img)
{
}

BWFilter::~BWFilter()
{
}

Image* BWFilter::filter()const{
	Image* new_image = new Image(image_->get_width(),image_->get_height());

	for (size_t i = 0; i < new_image->get_height(); i++)
	{
		for (size_t j = 0; j < new_image->get_width(); j++)
		{
			int r = (int)image_->at(i, j).get_R();
			int g = (int)image_->at(i, j).get_G();
			int b =	(int)image_->at(i, j).get_B();

			int avg = (r + g + b) / 3;

			new_image->at(i, j) = std::move(Pixel(avg,avg,avg));
		}
	}
	return new_image;
}