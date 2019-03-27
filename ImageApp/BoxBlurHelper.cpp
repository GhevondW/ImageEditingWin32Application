#include "stdafx.h"
#include "BoxBlurHelper.h"
using namespace app;


BoxBlurHelper::BoxBlurHelper(int value)
{
	set_value(value);
}


BoxBlurHelper::~BoxBlurHelper()
{
}


void BoxBlurHelper::set_value(int value) {
	if (value < 1 || value > 15) {
		value_ = 1;
		return;
	}
	value_ = value;
}

int BoxBlurHelper::get_value()const {
	return value_;
}