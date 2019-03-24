#pragma once
#ifndef _PIXEL_H__
#define _PIXEL_H__

namespace app
{
	class Pixel
	{
	public:
		Pixel();
		Pixel(unsigned char R,unsigned char G, unsigned char B, unsigned char A = 255);
		Pixel(unsigned char avg, unsigned char A = 255);
		Pixel(const Pixel& other) = default;
		Pixel(Pixel&& other) = default;
		~Pixel();

	public:

		unsigned char get_R() const;
		unsigned char get_G() const;
		unsigned char get_B() const;
		unsigned char get_A() const;

		void set_R(const unsigned char R);
		void set_G(const unsigned char G);
		void set_B(const unsigned char B);
		void set_A(const unsigned char A);

		Pixel& operator=(const Pixel& other) = default;
		Pixel& operator=(Pixel&& other) = default;

	private:
		unsigned char R_;
		unsigned char G_;
		unsigned char B_;
		unsigned char A_;
	};
}



#endif // !_PIXEL_H__




