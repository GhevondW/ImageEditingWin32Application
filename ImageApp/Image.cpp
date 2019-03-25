#include "stdafx.h"
#include "Image.h"
using namespace app;

Image::Image(const int width,const int height,const UINT* data,int stride)
	:width_(width),
	height_(height)
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

			
			data_[row][col] = std::move(Pixel(
				std::abs(r),
				std::abs(g),
				std::abs(b),
				std::abs(a)));
		}
}

Image::Image(const int width,const int height)
	:width_(width),
	height_(height)
{
	init_data();
}

Image::Image(const Image& other) 
	:width_(other.width_),
	height_(other.height_)
{
	
	init_data();
	copy_data(other);
}

Image::Image(Image&& other)
	:width_(std::move(other.width_)),
	height_(std::move(other.height_))
{
	init_data();

	for (size_t i = 0; i < height_; i++)
	{
		for (size_t j = 0; j < width_; j++)
		{
			data_[i][j] = std::move(other.data_[i][j]);
		}
	}

	for (size_t i = 0; i < height_; i++)
	{
		delete[] other.data_[i];
	}
	delete[] other.data_;
}

Image::Image()
	:width_(0),
	height_(0),
	data_(nullptr)
{
}


Image::~Image()
{
	for (size_t i = 0; i < height_; i++)
	{
		delete[] data_[i];
	}
	delete[] data_;
}

int Image::get_width() const {
	return width_;
}
int Image::get_height() const {
	return height_;
}

Pixel& Image::at(const int i, const int j) {
	if (i < height_ && i >= 0 && j < width_ && j>=0) {
		return data_[i][j];
	}
	throw "invalid operation";
}

Image& Image::operator=(const Image& other) {

	width_ = other.width_;
	height_ = other.height_;

	init_data();
	copy_data(other);

	return *this;
}

Image& Image::operator=(Image&& other) {

	width_ = std::move(other.width_);
	height_ = std::move(other.height_);

	init_data();
	for (size_t i = 0; i < height_; i++)
	{
		for (size_t j = 0; j < width_; j++)
		{
			data_[i][j] = std::move(other.data_[i][j]);
		}
	}

	return *this;
}

void Image::init_data() {
	data_ = new Pixel*[height_];
	for (size_t i = 0; i < height_; i++)
	{
		data_[i] = new Pixel[width_];
		for (size_t j = 0; j < width_; j++)
		{
			data_[i][j] = std::move(Pixel(0,0,0));
		}
	}
}

void Image::copy_data(const Image& other) {

	for (size_t i = 0; i < height_; i++)
	{
		for (size_t j = 0; j < width_; j++)
		{
			data_[i][j] = other.data_[i][j];
		}
	}

}