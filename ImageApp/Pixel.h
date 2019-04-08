#include "RGBA.h"
#include "BGRA.h"
#include "BGR.h"
#include "RGB.h"

#ifndef _PIXEL_H__
#define _PIXEL_H__

namespace app
{
	template<class TYPE = RGBA>
	class Pixel
	{
	public:
		Pixel() :Pixel(0,0,0) {};
		Pixel(unsigned char B, unsigned char G, unsigned char R, unsigned char A = 255) {
			vect_[0] = B;
			vect_[1] = G;
			vect_[2] = R;
			if (type_.SIZE == 3) {
				vect_[3] = 255;
			}
			else {
				vect_[3] = A;
			}
		}
		Pixel(unsigned char avg, unsigned char A = 255) :Pixel(avg, avg, avg, A) {}
		Pixel(const Pixel& other) = default;
		Pixel(Pixel&& other) = default;
		~Pixel() {}

	public:

		Pixel& operator=(const Pixel& other) = default;
		Pixel& operator=(Pixel&& other) = default;
		unsigned char& operator[](int index) {
			if (index >= 0 && index < type_.SIZE) {
				return vect_[type_.OFFSET[index]];
			}
			throw "invalid operation";
		}

	private:
		static const TYPE type_;
		unsigned char vect_[4];
	};

}



#endif // !_PIXEL_H__




