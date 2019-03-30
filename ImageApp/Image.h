#include "Pixel.h"
#include <iostream>
#include <memory>

#ifndef _IMAGE_H__
#define _IMAGE_H__

namespace app
{
	class Image
	{
	public:
		Image(const int width,const int height,const UINT* data,int stride);
		Image(const int width, const int height);
		Image(const Image& other);
		Image(Image&& other);
		Image();
		~Image();

	public:

		
		Pixel& at(const int i,const int j);
		Pixel& at(const int index);

	public:

		Image& operator=(const Image& other);
		Image& operator=(Image&& other);

	private:
		void init_data();
		void copy_data(const Image& other);
		
	public:

		int get_width() const;
		int get_height() const;
		BYTE* get_buffer() const;

	private:
		int width_;
		int height_;

		int data_size_;
		Pixel* data_;
	};

}


#endif // !_IMAGE_H__




