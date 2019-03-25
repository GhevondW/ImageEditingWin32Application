#include "stdafx.h"
#include "BWFilter.h"
#include "ThreadJoiner.h"
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

	int middle = new_image->get_height()/2;

	auto func = [&](int begin,int end) {
		for (size_t i = begin; i < end; i++)
		{
			for (size_t j = 0; j < new_image->get_width(); j++)
			{
				int r = (int)image_->at(i, j).get_R();
				int g = (int)image_->at(i, j).get_G();
				int b = (int)image_->at(i, j).get_B();

				int avg = (r + g + b) / 3;

				new_image->at(i, j) = std::move(Pixel(avg, avg, avg));
			}
		}
	};

	std::thread t1(func,0,middle);
	ThreadJoiner join1(t1);

	std::thread t2(func,middle,new_image->get_height());
	ThreadJoiner join2(t2);

	return new_image;
}