#include "stdafx.h"
#include "Image.h"
using namespace app;

Image::Image(const int width,const int height,const UINT* data,int stride)
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

			
			data_[row*width_ + col] = Pixel(
				std::abs(r),
				std::abs(g),
				std::abs(b),
				std::abs(a));
		}
}

Image::Image(const int width,const int height)
	:width_(width),
	height_(height),
	data_size_(width*height)
{
	init_data();
}

Image::Image(const Image& other)
	:width_(other.width_),
	height_(other.height_),
	data_size_(other.data_size_)
{
	
	delete[] data_;
	data_ = nullptr;

	init_data();
	copy_data(other);
}

Image::Image(Image&& other)
	:width_(std::move(other.width_)),
	height_(std::move(other.height_)),
	data_size_(std::move(other.data_size_))
{

	delete[] data_;
	data_ = nullptr;

	init_data();

	for (size_t i = 0; i < data_size_; i++)
	{
		data_[i] = std::move(other.data_[i]);
	}

	delete[] other.data_;
	other.data_ = nullptr;
}

Image::Image()
	:width_(0),
	height_(0),
	data_size_(0),
	data_(nullptr)
{
}

BYTE* Image::get_buffer() const {
	return (BYTE*)data_;
}

Image::~Image()
{
	delete[] data_;
	data_ = nullptr;
}

int Image::get_width() const {
	return width_;
}
int Image::get_height() const {
	return height_;
}

Pixel& Image::at(const int i, const int j) {
	if (i < height_ && i >= 0 && j < width_ && j>=0) {
		return data_[i*width_ + j];
	}
	throw "invalid operation";
}

Pixel& Image::at(const int index) {
	if (index >= 0 && index < data_size_) {
		return data_[index];
	}
	throw "invalid operation";
}

Image& Image::operator=(const Image& other) {

	width_ = other.width_;
	height_ = other.height_;
	data_size_ = other.data_size_;

	init_data();
	copy_data(other);

	return *this;
}

Image& Image::operator=(Image&& other) {

	width_ = std::move(other.width_);
	height_ = std::move(other.height_);
	data_size_ = std::move(other.data_size_);

	delete[] data_;
	data_ = nullptr;

	init_data();
	for (size_t i = 0; i < data_size_; i++)
	{
		data_[i] = std::move(other.data_[i]);
	}

	delete[] other.data_;
	other.data_ = nullptr;

	return *this;
}

void Image::init_data() {
	data_ = new Pixel[data_size_];
	for (size_t i = 0; i < data_size_; i++)
	{
		data_[i] = std::move(Pixel(0,0,0));
	}
}

void Image::copy_data(const Image& other) {

	if (!data_) {
		throw "invalid operation";
	}

	for (size_t i = 0; i < data_size_; i++)
	{
		data_[i] = other.data_[i];
	}

}