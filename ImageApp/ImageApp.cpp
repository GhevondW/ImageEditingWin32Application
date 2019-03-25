// ImageApp.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "ImageApp.h"
//#include <windows.h>
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

#pragma comment (lib,"Gdiplus.lib")


using namespace Gdiplus;

enum {ID_RUN_FILTER_ENUM};

namespace 
{
	HINSTANCE g_hInst;
	HWND btn_run_filter{};

	HWND dialog{};

	int radius = 1;

	std::unique_ptr<app::Image> main_image = nullptr;
	std::unique_ptr<app::FilterBase> filter = nullptr;
}

BOOL CALLBACK DialogProc(HWND, UINT, WPARAM, LPARAM);
Gdiplus::Bitmap* get_bitmap(app::Image* img);

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

BOOL CALLBACK DialogProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {


	

	if (message == WM_INITDIALOG) {
		HWND sliderConLo = GetDlgItem(hWnd, ID_SLIDER);
		SendMessage(sliderConLo, TBM_SETRANGE, (WPARAM)1, (LPARAM)MAKELONG(1, 15));
		SendMessage(sliderConLo, TBM_SETPOS, (WPARAM)1, 0);
		return FALSE;
	}

	if (message == WM_CLOSE) {
		DestroyWindow(hWnd);
		return TRUE;
	}
	else if(message == WM_COMMAND)
	{
		if(LOWORD(wParam) == ID_BTN_RUN_FILTER) {

			if (filter != nullptr) {
			
				std::unique_ptr<app::Image> new_image(filter->filter());
				
				std::unique_ptr<Gdiplus::Bitmap> bmp(get_bitmap(new_image.get()));

				HBITMAP img = NULL;

				bmp->GetHBITMAP(0, &img);

				SendDlgItemMessage(hWnd, ID_PICTURE_CONTROL, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)img);
			}

			return TRUE;
		}
		else if (LOWORD(wParam) == ID_BOX_BLUR) {			
			if (main_image != nullptr) {
				filter.release();
				filter.reset(new app::BoxBlurFilter(main_image.get(),radius));
			}
			return TRUE;
		}
		else if (LOWORD(wParam) == ID_BLACK_WHITE) {
			if (main_image != nullptr) {
				filter.release();
				filter.reset(new app::BWFilter(main_image.get()));
			}
			return TRUE;
		}
		else if (LOWORD(wParam) == ID_OPEN) {

			std::string image_path = get_image_path(hWnd);

			if (!image_path.empty()) {
				std::wstring str(image_path.begin(),image_path.end());
				
				std::unique_ptr<Bitmap> bmp(new Bitmap(str.c_str(),FALSE));
				std::unique_ptr<BitmapData> bitmapData(new BitmapData);


				int h = bmp->GetHeight();
				int w = bmp->GetWidth();

				Rect rect(0, 0, w, h);

				bmp->LockBits(&rect, ImageLockModeRead, PixelFormat32bppARGB, bitmapData.get());

				UINT*  pixels = (UINT*)bitmapData->Scan0;
				INT iStride = abs(bitmapData->Stride);

				main_image.release();
				main_image.reset(new app::Image(w,h,pixels,iStride));

				HBITMAP img = NULL;

				bmp->GetHBITMAP(0,&img);

				SendDlgItemMessage(hWnd, ID_PICTURE_CONTROL, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)img);
			}
			return TRUE;
		}
		return FALSE;
	}
	else if (message == WM_HSCROLL) {
		radius = SendMessage(GetDlgItem(dialog, ID_SLIDER), TBM_GETPOS, 0, 0);;
		return FALSE;
	}
	else if (message == WM_DESTROY) {
		PostQuitMessage(0);
		return TRUE;
	}

	return FALSE;
}


Gdiplus::Bitmap* get_bitmap(app::Image* img) {
	Gdiplus::Bitmap* bmp = new Bitmap(img->get_width(), img->get_height(), PixelFormat32bppARGB);

	for (size_t i = 0; i < img->get_height(); i++)
	{
		for (size_t j = 0; j < img->get_width(); j++)
		{
			bmp->SetPixel(j, i, Color(img->at(i, j).get_A(),
				img->at(i, j).get_R()
				, img->at(i, j).get_G()
				, img->at(i, j).get_B())
			);
		}
	}

	return bmp;
}