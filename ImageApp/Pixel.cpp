#include "stdafx.h"
#include "Pixel.h"
using namespace app;

Pixel::Pixel()
	:R_(0),
	G_(0),
	B_(0),
	A_(0)
{}

Pixel::Pixel(unsigned char R, unsigned char G, unsigned char B, unsigned char A)
	:R_(R),
	G_(G),
	B_(B),
	A_(A)
{}

Pixel::Pixel(unsigned char avg, unsigned char A)
	:R_(avg),
	G_(avg),
	B_(avg),
	A_(A)
{

}

Pixel::~Pixel()
{
}


unsigned char Pixel::get_R() const {
	return R_;
}
unsigned char Pixel::get_G() const {
	return G_;
}
unsigned char Pixel::get_B() const {
	return B_;
}
unsigned char Pixel::get_A() const {
	return A_;
}

void Pixel::set_R(const unsigned char R) {
	R_ = R;
}
void Pixel::set_G(const unsigned char G) {
	G_ = G;
}
void Pixel::set_B(const unsigned char B) {
	B_ = B;
}
void Pixel::set_A(const unsigned char A) {
	A_ = A;
}