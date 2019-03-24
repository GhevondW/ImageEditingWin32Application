#pragma once
#include "FilterBase.h"

#ifndef _BWFILTER_H__
#define _BWFILTER_H__
namespace app
{

	class BWFilter :
		public FilterBase
	{
	public:
		BWFilter();
		BWFilter(Image* image);
		virtual ~BWFilter();

		Image* filter()const override;
	};

}

#endif // !_BWFILTER_H__

