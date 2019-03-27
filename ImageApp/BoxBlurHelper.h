
namespace app
{

#ifndef _BOX_BLUR_HELPER_H__
#define _BOX_BLUR_HELPER_H__
	class BoxBlurHelper
	{
	public:
		BoxBlurHelper(int value = 1);
		~BoxBlurHelper();

	public:

		void set_value(int value);

		int get_value()const;

	private:
		int value_;
	};
#endif // !_BOX_BLUR_HELPER_H__

}






