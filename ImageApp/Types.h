#include "Image.h"
#include "FilterBase.h"
#include "BWFilter.h"
#include "BoxBlurFilter.h"
#include "BoxBlurHelper.h"
#include "InvertFilter.h"
#include "Histogram.h"

#ifndef _TYPES_H__
#define _TYPES_H__

namespace
{
	typedef app::Image<app::BGRA> Image;
	typedef app::FilterBase<app::BGRA> FilterBase;
	typedef app::BoxBlurFilter<app::BGRA> BoxBlurFilter;
	typedef app::BWFilter<app::BGRA> BWFilter;
	typedef app::InvertFilter<app::BGRA> InvertFilter;
	typedef app::Histogram<app::BGRA> Histogram;
}



#endif // !_TYPES_H__

