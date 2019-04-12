// ImageApp.cpp : Defines the entry point for the application.
//
#include <Windows.h>
#include "stdafx.h"
#include "ImageApp.h"
#include <ObjIdl.h>
#include <commctrl.h>
#include <commdlg.h>
#include <memory>
#include <string>
#include <gdiplus.h>
#include "Image.h"
#include "FilterBase.h"
#include "BWFilter.h"
#include "BoxBlurFilter.h"
#include "BoxBlurHelper.h"
#include "InvertFilter.h"


#pragma comment (lib,"Gdiplus.lib")

using namespace Gdiplus;

enum {ID_RUN_FILTER_ENUM};

namespace 
{
	HINSTANCE g_hInst;
	HWND btn_run_filter{};
	HWND dialog{};

	enum class Mode 
	{
		origin,
		processed
	};

	const int main_area_x = 30;
	const int main_area_y = 170;
	const int main_area_width = 890;
	const int main_area_height = 590;
	const int WM_PAINT_PARAM = 123;

	int real_x{};
	int real_y{};
	int real_width{};
	int real_height{};

	typedef app::Image<app::BGRA> Image;
	typedef app::FilterBase<app::BGRA> FilterBase;
	typedef app::BoxBlurFilter<app::BGRA> BoxBlurFilter;
	typedef app::BWFilter<app::BGRA> BWFilter;
	typedef app::InvertFilter<app::BGRA> InvertFilter;

	const RECT main_area{main_area_x,main_area_y,main_area_width + main_area_x,main_area_height + main_area_y};
	Mode mode = Mode::origin;
	INT iStride = 0;
	app::BoxBlurHelper* box_blur_helper = new app::BoxBlurHelper(1);
	std::unique_ptr<Image> main_image = nullptr;
	std::unique_ptr<Image> processed_image = nullptr;
	std::unique_ptr<FilterBase> filter = nullptr;

	LRESULT  CALLBACK DialogProc(HWND, UINT, WPARAM, LPARAM);
	Gdiplus::Bitmap* get_bitmap(Image* img);
}



int APIENTRY wWinMain(HINSTANCE hInstance,
	 HINSTANCE hPrevInstance,
	 LPWSTR    lpCmdLine,
	 int       nCmdShow) {
	GdiplusStartupInput gdiplusStartupInput;
	ULONG_PTR           gdiplusToken;

	// Initialize GDI+.
	GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

	g_hInst = hInstance;

	dialog = CreateDialog(hInstance, MAKEINTRESOURCE(ID_MAIN_WINDOW), NULL, DialogProc);
	
	

	if (!dialog) {
		MessageBox(NULL, "Could not create dialog", "CreateDialgo", MB_ICONERROR);
		return 1;
	}
	ShowWindow(dialog, nCmdShow);
	UpdateWindow(dialog);


	MSG msg;

	while (GetMessage(&msg, 0, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	GdiplusShutdown(gdiplusToken);
	return (int)msg.wParam;
}

namespace
{
	std::string get_image_path(HWND hWnd) {

		OPENFILENAME ofn;


		char file_name[100];

		ZeroMemory(&ofn, sizeof(OPENFILENAME));

		ofn.lStructSize = sizeof(OPENFILENAME);
		ofn.hwndOwner = hWnd;
		ofn.lpstrFile = file_name;
		ofn.lpstrFile[0] = '\0';
		ofn.nMaxFile = 100;
		ofn.lpstrFilter = "Image files (*.jpg;*.png;*.bmp)\0*.jpg;*.png;*.bmp\0"
			"All files\0*.*\0";
		ofn.nFilterIndex = 1;

		GetOpenFileName(&ofn);

		return std::string(ofn.lpstrFile);
	}

	void DrawImage(HDC hDC, HWND& hWnd, Image* img)
	{

		Graphics graphics(hDC);
		if (img) {
			std::unique_ptr<Bitmap> img_result(get_bitmap(img));
			int x = main_area_x;
			int y = main_area_y;

			int width = img_result->GetWidth();
			int height = img_result->GetHeight();

			if (width > main_area_width && width >= height) {
				width = main_area_width;
				height = (main_area_width * img_result->GetHeight()) / (img_result->GetWidth());
			}
			else if (height > main_area_height) {
				height = main_area_height;
				width = (main_area_height * img_result->GetWidth()) / (img_result->GetHeight());
			}

			y = y + (main_area_height - height) / 2;
			x = x + (main_area_width - width) / 2;

			real_x =  x;
			real_y =  y;
			real_width = width;
			real_height = height;

			graphics.DrawImage(img_result.get(),
				x,
				y,
				width,
				height);

		}

	}

	LRESULT  CALLBACK DialogProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {


		if (message == WM_INITDIALOG) {
			HWND sliderConLo = GetDlgItem(hWnd, ID_SLIDER);
			SendMessage(sliderConLo, TBM_SETRANGE, (WPARAM)1, (LPARAM)MAKELONG(1, 15));
			SendMessage(sliderConLo, TBM_SETPOS, (WPARAM)1, 0);

			EnableWindow(GetDlgItem(hWnd, ID_BTN_RUN_FILTER), FALSE);
			EnableWindow(GetDlgItem(hWnd, ID_SLIDER), FALSE);
			
			return FALSE;
		}

		switch (message)
		{
		case WM_CLOSE:
		{
			DestroyWindow(hWnd);
			break;
		}
		case WM_COMMAND:
		{
			switch (LOWORD(wParam))
			{
			case ID_BTN_RUN_FILTER:
			{
				if (main_image == nullptr) {
					MessageBox(NULL, "Please select an image!!!", "Status", NULL);
					return TRUE;
				}

				if (filter != nullptr) {
					processed_image.reset(filter->filter());
					mode = Mode::processed;
					SendMessage(dialog, WM_PAINT, WM_PAINT_PARAM, 0);
				}
				else {
					MessageBox(NULL, "Please select the filter type!!!", "Status", NULL);
				}

				return TRUE;
			}
			case ID_BOX_BLUR:
			{
				if (main_image != nullptr) {
					filter.reset(new BoxBlurFilter(main_image.get(), box_blur_helper));
					EnableWindow(GetDlgItem(hWnd, ID_BTN_RUN_FILTER), TRUE);
					EnableWindow(GetDlgItem(hWnd, ID_SLIDER), TRUE);
				}
				return TRUE;
			}
			case ID_BLACK_WHITE:
			{
				if (main_image != nullptr) {
					filter.reset(new BWFilter(main_image.get()));
					EnableWindow(GetDlgItem(hWnd, ID_BTN_RUN_FILTER), TRUE);
					EnableWindow(GetDlgItem(hWnd, ID_SLIDER), FALSE);
				}

				return TRUE;
			}
			case ID_INVERT_FILTER:
			{
				if (main_image != nullptr) {
					filter.reset(new InvertFilter(main_image.get()));
					EnableWindow(GetDlgItem(hWnd, ID_BTN_RUN_FILTER), TRUE);
					EnableWindow(GetDlgItem(hWnd, ID_SLIDER), FALSE);
				}
				return TRUE;
			}
			case ID_OPEN:
			{
				std::string image_path = get_image_path(hWnd);

				if (!image_path.empty()) {

					HWND box_blur_button = GetDlgItem(hWnd, ID_BOX_BLUR);
					HWND black_white_button = GetDlgItem(hWnd, ID_BLACK_WHITE);
					HWND invert_filter_button = GetDlgItem(hWnd, ID_INVERT_FILTER);

					SendMessage(box_blur_button, BM_SETCHECK, 0, 0);
					SendMessage(black_white_button, BM_SETCHECK, 0, 0);
					SendMessage(invert_filter_button, BM_SETCHECK, 0, 0);

					EnableWindow(GetDlgItem(hWnd, ID_BTN_RUN_FILTER), FALSE);
					EnableWindow(GetDlgItem(hWnd, ID_SLIDER), FALSE);

					filter.reset(nullptr);

					std::wstring str(image_path.begin(), image_path.end());

					std::unique_ptr<Bitmap> bmp(new Bitmap(str.c_str(), FALSE));
					std::unique_ptr<BitmapData> bitmapData(new BitmapData);
					int h = bmp->GetHeight();
					int w = bmp->GetWidth();

					Rect rect(0, 0, w, h);

					bmp->LockBits(&rect, ImageLockModeRead, PixelFormat32bppARGB, bitmapData.get());

					UINT*  pixels = (UINT*)bitmapData->Scan0;
					iStride = abs(bitmapData->Stride);

					main_image.reset(new Image(w, h, pixels, iStride));

					mode = Mode::origin;
					SendMessage(dialog, WM_PAINT, WM_PAINT_PARAM, 0);
					
				}
				return TRUE;
			}
			}
			break;
		}
		case WM_LBUTTONDOWN:
		{
			int x = LOWORD(lParam);
			int y = HIWORD(lParam);

			if (x >= real_x && x <= real_x + real_width) {
				if (y >= real_y && y <= real_y + real_height) {
					mode = Mode::origin;
					SendMessage(dialog, WM_PAINT, WM_PAINT_PARAM, 0);
				}
			}

			break;
		}
		case WM_PAINT:
		{
			//except for the window moving case
			if (LOWORD(wParam) == WM_PAINT_PARAM) {
				InvalidateRect(hWnd, &main_area, TRUE);
			}

			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(hWnd, &ps);
			if (mode == Mode::origin) {
				DrawImage(hdc, hWnd, main_image.get());
			}
			else if (mode == Mode::processed) {
				DrawImage(hdc, hWnd, processed_image.get());
			}
			EndPaint(hWnd, &ps);
			break;
		}
		case WM_HSCROLL:
		{
			int radius = SendMessage(GetDlgItem(dialog, ID_SLIDER), TBM_GETPOS, 0, 0);;
			box_blur_helper->set_value(radius);
			break;
		}
		case WM_DESTROY:
		{
			PostQuitMessage(0);
			break;
		}
		}
		return FALSE;
	}


	Gdiplus::Bitmap* get_bitmap(Image* img) {
		Gdiplus::Bitmap* bmp = new Bitmap(img->get_width(), img->get_height(), iStride, PixelFormat32bppARGB, img->get_buffer());
		return bmp;
	}
}