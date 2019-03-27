#include "FilterBase.h"
#include "BoxBlurHelper.h"

namespace app
{

#ifndef _BOX_BLUR_FILTER_H__
#define _BOX_BLUR_FILTER_H__
	class BoxBlurFilter :
		public FilterBase
	{
	public:
		BoxBlurFilter();
		BoxBlurFilter(Image* image, BoxBlurHelper* helper);
		virtual ~BoxBlurFilter();

		Image* filter() const override;

	private:

		void horizontal_motion_blur(Image* new_image) const;
		void vertical_motion_blur(Image* new_image) const;

	private:
		BoxBlurHelper* helper_;
	};
#endif // !_BOX_BLUR_FILTER_H__
}



