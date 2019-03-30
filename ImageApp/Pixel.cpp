#include "stdafx.h"
#include "Pixel.h"
using namespace app;

Pixel::Pixel()
{
	init(0,0,0,255);
}

Pixel::Pixel(unsigned char R, unsigned char G, unsigned char B, unsigned char A)
{
	init(R,G,B,A);
}

Pixel::Pixel(unsigned char avg, unsigned char A)
{
	init(avg,avg,avg,A);
}

Pixel::~Pixel()
{
}


unsigned char Pixel::get_R() const {
	return vect_[2];
}
unsigned char Pixel::get_G() const {
	return vect_[1];
}
unsigned char Pixel::get_B() const {
	return vect_[0];
}
unsigned char Pixel::get_A() const {
	return vect_[3];
}

void Pixel::set_R(const unsigned char R) {
	vect_[2] = R;
}
void Pixel::set_G(const unsigned char G) {
	vect_[1] = G;
}
void Pixel::set_B(const unsigned char B) {
	vect_[0] = B;
}
void Pixel::set_A(const unsigned char A) {
	vect_[3] = A;
}

void Pixel::init(unsigned char R, unsigned char G, unsigned char B, unsigned char A) {
	vect_[3] = A;
	vect_[2] = R;
	vect_[1] = G;
	vect_[0] = B;
}

unsigned char& Pixel::operator[](int index) {
	if (index < 0 || index >= SIZE) {
		throw "invalid operation";
	}
	return vect_[index];
}