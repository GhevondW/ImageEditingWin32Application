#include "Pixel.h"
#include <iostream>
#include <memory>

#ifndef _IMAGE_H__
#define _IMAGE_H__

namespace app
{
	template <class TYPE = RGBA>
	class Image
	{
		typedef Pixel<TYPE> pixel;
	public:
		Image(const int width, const int height, const UINT* data, int stride) 
			:width_(width),
			height_(height),
			data_size_(width*height)
		{
			init_data();

			for (UINT row = 0; row < height; ++row)
				for (UINT col = 0; col < width; ++col)
				{


					unsigned int curColor = data[row * stride / 4 + col];
					int b = curColor & 0xff;
					int g = (curColor & 0xff00) >> 8;
					int r = (curColor & 0xff0000) >> 16;
					int a = (curColor & 0xff000000) >> 24;


					data_[row*width_ + col] = pixel(
						std::abs(b),
						std::abs(g),
						std::abs(r),
						std::abs(a));
				}
		}
		Image(const int width, const int height)
			:width_(width),
			height_(height),
			data_size_(width*height)
		{
			init_data();
		}
		Image(const Image& other) {
			copy_data(other);
		}
		Image() 
			:width_(0),
			height_(0),
			data_size_(0)
		{
			data_size_ = nullptr;
		}
		~Image() {
			if (data_) {
				delete[] data_;
			}
		}

	public:

		pixel& at(const int i, const int j) {
			if (i < height_ && i >= 0 && j < width_ && j >= 0) {
				return data_[i*width_ + j];
			}
			throw "invalid operation";
		}
		pixel& at(const int index) {
			if (index>= 0 && index < data_size_) {
				return data_[index];
			}
			throw "invalid operation";
		}

	public:

		Image& operator=(const Image& other) {
			copy_data(other);
		}

	private:
		void init_data() {
			
			if (data_) {
				delete[] data_;
			}

			data_ = new pixel[data_size_];
			for (size_t i = 0; i < data_size_; i++)
			{
				data_[i] = pixel(0,0,0);
			}

		}
		void copy_data(const Image& other) {
		
			this->width_ = other.width_;
			this->height_ = other.height_;
			this->data_size_ = width_ * height_;

			if (data_) {
				delete[] data_;
			}
			data_ = new pixel[data_size_];
			for (size_t i = 0; i < data_size_; i++)
			{
				data_[i] = other.data_[i];
			}
		}
		
	public:

		int get_width() const {
			return width_;
		}
		int get_height() const {
			return height_;
		}
		BYTE* get_buffer() const {
			return (BYTE*)data_;
		}

	private:
		int width_;
		int height_;

		int data_size_;
		pixel* data_;
	};

}


#endif // !_IMAGE_H__




