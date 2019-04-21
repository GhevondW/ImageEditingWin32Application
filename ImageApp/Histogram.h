#include "Image.h"

#ifndef _HISTOGRAM_H__
#define _HISTOGRAM_H__

namespace app 
{
	template<class PIXEL_TYPE>
	class Histogram
	{
		typedef Image<PIXEL_TYPE> image;
	public:
		Histogram(image* image) {
			image_ = image;
		}
		~Histogram() {

		}

	public:

		image* get_hist(){
			image* hist = new image(550,450);
			const static int MAX_INTENCITY = 256;

			const static int HIST_HEIGHT = 150;

			int arr_blue[MAX_INTENCITY] = {0};
			int arr_green[MAX_INTENCITY] = {0};
			int arr_red[MAX_INTENCITY] = {0};

			auto calculator = [&](int c, int arr[],int k) {
			
				for (int i = 0; i < image_->get_height(); i++)
				{
					for (int j = 0; j < image_->get_width(); j++)
					{
						++arr[image_->at(i, j)[c]];
					}
				}
			
				for (int i = 0; i < MAX_INTENCITY; i++)
				{
					int count = arr[i] % 140;
					for (size_t j = 0; j < count; j++)
					{
						hist->at(149*k - j, i * 2 + 15)[c] = 255;
					}
				}

			};
			
			std::thread t1(calculator, 0, arr_blue,1);
			std::thread t2(calculator, 1, arr_green,2);
			std::thread t3(calculator, 2, arr_red,3);
			
			ThreadJoiner join1(t1);
			ThreadJoiner join2(t2);
			ThreadJoiner join3(t3);

			return hist;
		}

	private:
		image* image_;
	};

}

#endif // !_HISTOGRAM_H__

