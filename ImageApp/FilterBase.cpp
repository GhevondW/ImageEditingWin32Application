#include "stdafx.h"
#include "FilterBase.h"
using namespace app;

FilterBase::FilterBase(Image* img) 
	:image_(img)
{
}

FilterBase::FilterBase()
	: image_(nullptr)
{
}


FilterBase::~FilterBase()
{
}
