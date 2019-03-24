#include "FilterBase.h"




#ifndef _BOX_BLUR_FILTER_H__
#define _BOX_BLUR_FILTER_H__

namespace app
{
	class BoxBlurFilter :
		public FilterBase
	{
	public:
		BoxBlurFilter();
		BoxBlurFilter(Image* image, int radius);
		virtual ~BoxBlurFilter();

		Image* filter() const override;

	private:

		void horizontal_motion_blur(Image* new_image) const;
		void vertical_motion_blur(Image* new_image) const;

	private:
		int radius_;
	};
}

#endif // !_BOX_BLUR_FILTER_H__




