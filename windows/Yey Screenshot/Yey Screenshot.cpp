// gyazowin.cpp : ƒAƒvƒŠƒP[ƒVƒ‡ƒ“‚ÌƒGƒ“ƒgƒŠ ƒ|ƒCƒ“ƒg‚ğ’è‹`‚µ‚Ü‚·B
//
// There aint many differens about this code then the original
// Pretty much only edited the where it post
#include "stdafx.h"
#include "Yey Screenshot.h"
#include <windows.h>
#include "stdlib.h"
#include <stdio.h>
#include <cstdlib>
#include <string.h>
#define __T(x)      L ## x
#include <Shellapi.h>
#include <process.h>
#include <iostream>
#using <mscorlib.dll>
#include <vcclr.h>

using namespace System;
using namespace System::IO;

#define DebugMessage(str)	OutputDebugString(str)
#undef GetCurrentDirectory

 using namespace std;

 /*sdauasdiugasdkgasidgasiudgasiduyasitdiusdtgaiysadtuydasu6yasdssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssss
 */
 struct Thread
{
    bool forts;
    int tal;
};





 /*sdauasdiugasdkgasidgasiudgasiduyasitdiusdtgaiysadtuydasu6yasdsssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssss*/

 void Thread1 (PVOID pvoid);
 

// ƒOƒ[ƒoƒ‹•Ï”:
HINSTANCE hInst;							// Œ»İ‚ÌƒCƒ“ƒ^[ƒtƒFƒCƒX
TCHAR *szTitle			= _T("Yey.nu - Desktop");		// ƒ^ƒCƒgƒ‹ ƒo[‚ÌƒeƒLƒXƒg
TCHAR *szWindowClass	= _T("YEYWIN");	// ƒƒCƒ“ ƒEƒBƒ“ƒhƒE ƒNƒ‰ƒX–¼
TCHAR *szWindowClassL	= _T("YEYWINL");	// ƒŒƒCƒ„[ ƒEƒBƒ“ƒhƒE ƒNƒ‰ƒX–¼
HWND hLayerWnd;

int ofX, ofY;	// ‰æ–ÊƒIƒtƒZƒbƒg

// ƒvƒƒgƒ^ƒCƒvéŒ¾
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK	LayerWndProc(HWND, UINT, WPARAM, LPARAM);

int					GetEncoderClsid(const WCHAR* format, CLSID* pClsid);

BOOL				isPng(LPCTSTR fileName);
VOID				drawRubberband(HDC hdc, LPRECT newRect, BOOL erase);
VOID				execUrl(const char* str);
VOID				setClipBoardText(const char* str);
BOOL				convertPNG(LPCTSTR destFile, LPCTSTR srcFile);
BOOL				savePNG(LPCTSTR fileName, HBITMAP newBMP);
BOOL				uploadFile(HWND hwnd, LPCTSTR fileName);
BOOL				saveId(const WCHAR* str);


bool To_CharStar( String^ source, char*& target )
{
    pin_ptr<const wchar_t> wch = PtrToStringChars( source );
    int len = (( source->Length+1) * 2);
    target = new char[ len ];
    return wcstombs( target, wch, len ) != -1;
}


bool To_string( String^ source, string &target )
{
    pin_ptr<const wchar_t> wch = PtrToStringChars( source );
    int len = (( source->Length+1) * 2);
    char *ch = new char[ len ];
    bool result = wcstombs( ch, wch, len ) != -1;
    target = ch;
    delete ch;
    return result;
}



// ƒGƒ“ƒgƒŠ[ƒ|ƒCƒ“ƒg
int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	MSG msg;

	TCHAR	szThisPath[MAX_PATH];
	DWORD   sLen;

	// ©g‚ÌƒfƒBƒŒƒNƒgƒŠ‚ğæ“¾‚·‚é
	sLen = GetModuleFileName(NULL, szThisPath, MAX_PATH);
	for(unsigned int i = sLen; i >= 0; i--) {
		if(szThisPath[i] == _T('\\')) {
			szThisPath[i] = _T('\0');
			break;
		}
	}

	// ƒJƒŒƒ“ƒgƒfƒBƒŒƒNƒgƒŠ‚ğ exe ‚Æ“¯‚¶êŠ‚Éİ’è
	SetCurrentDirectory(szThisPath);

	// ˆø”‚Éƒtƒ@ƒCƒ‹‚ªw’è‚³‚ê‚Ä‚¢‚½‚ç
	if ( 2 == __argc )
	{
		// ƒtƒ@ƒCƒ‹‚ğƒAƒbƒvƒ[ƒh‚µ‚ÄI—¹
		if (isPng(__targv[1])) {
			// PNG ‚Í‚»‚Ì‚Ü‚Üupload
			uploadFile(NULL, __targv[1]);
		}else {
			// PNG Œ`®‚É•ÏŠ·
			TCHAR tmpDir[MAX_PATH], tmpFile[MAX_PATH];
			GetTempPath(MAX_PATH, tmpDir);
			GetTempFileName(tmpDir, _T("yeytmp"), 0, tmpFile);
			
			if (convertPNG(tmpFile, __targv[1])) {
				//ƒAƒbƒvƒ[ƒh
				uploadFile(NULL, tmpFile);
			} else {
				// PNG‚É•ÏŠ·‚Å‚«‚È‚©‚Á‚½...
				MessageBox(NULL, _T("Cannot convert this image"), szTitle, 
					MB_OK | MB_ICONERROR);
			}
			DeleteFile(tmpFile);
		}
		return TRUE;
	}

	// ƒEƒBƒ“ƒhƒEƒNƒ‰ƒX‚ğ“o˜^
	MyRegisterClass(hInstance);

	// ƒAƒvƒŠƒP[ƒVƒ‡ƒ“‚Ì‰Šú‰»‚ğÀs‚µ‚Ü‚·:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}
	
	// ƒƒCƒ“ ƒƒbƒZ[ƒW ƒ‹[ƒv:
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return (int) msg.wParam;
}

// ƒwƒbƒ_‚ğŒ©‚Ä PNG ‰æ‘œ‚©‚Ç‚¤‚©(ˆê‰)ƒ`ƒFƒbƒN
BOOL isPng(LPCTSTR fileName)
{
	unsigned char pngHead[] = { 0x89, 0x50, 0x4E, 0x47, 0x0D, 0x0A, 0x1A, 0x0A };
	unsigned char readHead[8];
	
	FILE *fp = NULL;
	
	if (0 != _tfopen_s(&fp, fileName, _T("rb")) ||
		8 != fread(readHead, 1, 8, fp)) {
		// ƒtƒ@ƒCƒ‹‚ª“Ç‚ß‚È‚¢	
		return FALSE;
	}
	fclose(fp);
	
	// compare
	for(unsigned int i=0;i<8;i++)
		if(pngHead[i] != readHead[i]) return FALSE;

	return TRUE;

}

// ƒEƒBƒ“ƒhƒEƒNƒ‰ƒX‚ğ“o˜^
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASS wc;

	// ƒƒCƒ“ƒEƒBƒ“ƒhƒE
	wc.style         = 0;							// WM_PAINT ‚ğ‘—‚ç‚È‚¢
	wc.lpfnWndProc   = WndProc;
	wc.cbClsExtra    = 0;
	wc.cbWndExtra    = 0;
	wc.hInstance     = hInstance;
	wc.hIcon         = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_GYAZOWIN));
	wc.hCursor       = LoadCursor(NULL, IDC_CROSS);	// + ‚ÌƒJ[ƒ\ƒ‹
	wc.hbrBackground = 0;							// ”wŒi‚àİ’è‚µ‚È‚¢
	wc.lpszMenuName  = 0;
	wc.lpszClassName = szWindowClass;

	RegisterClass(&wc);

	// ƒŒƒCƒ„[ƒEƒBƒ“ƒhƒE
	wc.style         = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc   = LayerWndProc;
	wc.cbClsExtra    = 0;
	wc.cbWndExtra    = 0;
	wc.hInstance     = hInstance;
	wc.hIcon         = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_GYAZOWIN));
	wc.hCursor       = LoadCursor(NULL, IDC_CROSS);	// + ‚ÌƒJ[ƒ\ƒ‹
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName  = 0;
	wc.lpszClassName = szWindowClassL;

	return RegisterClass(&wc);
}


// ƒCƒ“ƒXƒ^ƒ“ƒX‚Ì‰Šú‰»i‘S‰æ–Ê‚ğƒEƒBƒ“ƒhƒE‚Å•¢‚¤j
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	HWND hWnd;
//	HWND hLayerWnd;
	hInst = hInstance; // ƒOƒ[ƒoƒ‹•Ï”‚ÉƒCƒ“ƒXƒ^ƒ“ƒXˆ—‚ğŠi”[‚µ‚Ü‚·B

	int x, y, w, h;

	// ‰¼‘zƒXƒNƒŠ[ƒ“‘S‘Ì‚ğƒJƒo[
	x = GetSystemMetrics(SM_XVIRTUALSCREEN);
	y = GetSystemMetrics(SM_YVIRTUALSCREEN);
	w = GetSystemMetrics(SM_CXVIRTUALSCREEN);
	h = GetSystemMetrics(SM_CYVIRTUALSCREEN);

	// x, y ‚ÌƒIƒtƒZƒbƒg’l‚ğŠo‚¦‚Ä‚¨‚­
	ofX = x; ofY = y;

	// Š®‘S‚É“§‰ß‚µ‚½ƒEƒBƒ“ƒhƒE‚ğì‚é
	hWnd = CreateWindowEx(
		WS_EX_TRANSPARENT | WS_EX_TOOLWINDOW | WS_EX_TOPMOST
#if(_WIN32_WINNT >= 0x0500)
		| WS_EX_NOACTIVATE
#endif
		,
		szWindowClass, NULL, WS_POPUP,
		0, 0, 0, 0,
		NULL, NULL, hInstance, NULL);

	// ì‚ê‚È‚©‚Á‚½...?
	if (!hWnd) return FALSE;
	
	// ‘S‰æ–Ê‚ğ•¢‚¤
	MoveWindow(hWnd, x, y, w, h, FALSE);
	
	// nCmdShow ‚ğ–³‹ (SW_MAXIMIZE ‚Æ‚©‚³‚ê‚é‚Æ¢‚é)
	ShowWindow(hWnd, SW_SHOW);
	UpdateWindow(hWnd);

	// ESCƒL[ŒŸ’mƒ^ƒCƒ}[
	SetTimer(hWnd, 1, 100, NULL);


	// ƒŒƒCƒ„[ƒEƒBƒ“ƒhƒE‚Ìì¬
	hLayerWnd = CreateWindowEx(
	 WS_EX_TOOLWINDOW
#if(_WIN32_WINNT >= 0x0500)
		| WS_EX_LAYERED | WS_EX_NOACTIVATE
#endif
		,
		szWindowClassL, NULL, WS_POPUP,
		100, 100, 300, 300,
		hWnd, NULL, hInstance, NULL);

    SetLayeredWindowAttributes(hLayerWnd, RGB(255, 0, 0), 100, LWA_COLORKEY|LWA_ALPHA);

	


	
	return TRUE;
}

// w’è‚³‚ê‚½ƒtƒH[ƒ}ƒbƒg‚É‘Î‰‚·‚é Encoder ‚Ì CLSID ‚ğæ“¾‚·‚é
// Cited from MSDN Library: Retrieving the Class Identifier for an Encoder
int GetEncoderClsid(const WCHAR* format, CLSID* pClsid)
{
   UINT  num = 0;          // number of image encoders
   UINT  size = 0;         // size of the image encoder array in bytes

   ImageCodecInfo* pImageCodecInfo = NULL;

   GetImageEncodersSize(&num, &size);
   if(size == 0)
      return -1;  // Failure

   pImageCodecInfo = (ImageCodecInfo*)(malloc(size));
   if(pImageCodecInfo == NULL)
      return -1;  // Failure

   GetImageEncoders(num, size, pImageCodecInfo);

   for(UINT j = 0; j < num; ++j)
   {
      if( wcscmp(pImageCodecInfo[j].MimeType, format) == 0 )
      {
         *pClsid = pImageCodecInfo[j].Clsid;
         free(pImageCodecInfo);
         return j;  // Success
      }    
   }

   free(pImageCodecInfo);
   return -1;  // Failure
}

// ƒ‰ƒo[ƒoƒ“ƒh‚ğ•`‰æ.
VOID drawRubberband(HDC hdc, LPRECT newRect, BOOL erase)
{
	
	static BOOL firstDraw = TRUE;	// 1 ‰ñ–Ú‚Í‘O‚Ìƒoƒ“ƒh‚ÌÁ‹‚ğs‚í‚È‚¢
	static RECT lastRect  = {0};	// ÅŒã‚É•`‰æ‚µ‚½ƒoƒ“ƒh
	static RECT clipRect  = {0};	// ÅŒã‚É•`‰æ‚µ‚½ƒoƒ“ƒh
	
	if(firstDraw) {
		// ƒŒƒCƒ„[ƒEƒBƒ“ƒhƒE‚ğ•\¦
		ShowWindow(hLayerWnd, SW_SHOW);
		UpdateWindow(hLayerWnd);

		firstDraw = FALSE;
	}

	if (erase) {
		// ƒŒƒCƒ„[ƒEƒBƒ“ƒhƒE‚ğ‰B‚·
		ShowWindow(hLayerWnd, SW_HIDE);
		
	}

	// À•Wƒ`ƒFƒbƒN
	clipRect = *newRect;
	if ( clipRect.right  < clipRect.left ) {
		int tmp = clipRect.left;
		clipRect.left   = clipRect.right;
		clipRect.right  = tmp;
	}
	if ( clipRect.bottom < clipRect.top  ) {
		int tmp = clipRect.top;
		clipRect.top    = clipRect.bottom;
		clipRect.bottom = tmp;
	}
	MoveWindow(hLayerWnd,  clipRect.left, clipRect.top, 
			clipRect.right-  clipRect.left + 1, clipRect.bottom - clipRect.top + 1,true);

	
	return;

/* rakusai 2009/11/2

	// XOR ‚Å•`‰æ
	int hPreRop = SetROP2(hdc, R2_XORPEN);

	// “_ü
	HPEN hPen = CreatePen(PS_DOT , 1, 0);
	SelectObject(hdc, hPen);
	SelectObject(hdc, GetStockObject(NULL_BRUSH));

	if(!firstDraw) {
		// ‘O‚Ì‚ğÁ‚·
		Rectangle(hdc, lastRect.left, lastRect.top, 
			lastRect.right + 1, lastRect.bottom + 1);
	} else {
		firstDraw = FALSE;
	}
	
	// V‚µ‚¢À•W‚ğ‹L‰¯
	lastRect = *newRect;
	
	


	if (!erase) {

		// ˜g‚ğ•`‰æ
		Rectangle(hdc, lastRect.left, lastRect.top, 
			lastRect.right + 1, lastRect.bottom + 1);

	}


	// Œãˆ—
	SetROP2(hdc, hPreRop);
	DeleteObject(hPen);

*/

}

// PNG Œ`®‚É•ÏŠ·
BOOL convertPNG(LPCTSTR destFile, LPCTSTR srcFile)
{
	BOOL				res = FALSE;

	GdiplusStartupInput	gdiplusStartupInput;
	ULONG_PTR			gdiplusToken;
	CLSID				clsidEncoder;

	// GDI+ ‚Ì‰Šú‰»
	GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

	Image *b = new Image(srcFile, 0);

	if (0 == b->GetLastStatus()) {
		if (GetEncoderClsid(L"image/png", &clsidEncoder)) {
			// save!
			if (0 == b->Save(destFile, &clsidEncoder, 0) ) {
					// •Û‘¶‚Å‚«‚½
					res = TRUE;
			}
		}
	}

	// Œãn––
	delete b;
	GdiplusShutdown(gdiplusToken);

	return res;
}

// PNG Œ`®‚Å•Û‘¶ (GDI+ g—p)
BOOL savePNG(LPCTSTR fileName, HBITMAP newBMP)
{
	BOOL				res = FALSE;

	GdiplusStartupInput	gdiplusStartupInput;
	ULONG_PTR			gdiplusToken;
	CLSID				clsidEncoder;

	// GDI+ ‚Ì‰Šú‰»
	GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);
	
	// HBITMAP ‚©‚ç Bitmap ‚ğì¬
	Bitmap *b = new Bitmap(newBMP, NULL);
	
	if (GetEncoderClsid(L"image/png", &clsidEncoder)) {
		// save!
		if (0 ==
			b->Save(fileName, &clsidEncoder, 0) ) {
				// •Û‘¶‚Å‚«‚½
				res = TRUE;
		}
	}
	
	// Œãn––
	delete b;
	GdiplusShutdown(gdiplusToken);

	return res;
}

// ƒŒƒCƒ„[ƒEƒBƒ“ƒhƒEƒvƒƒV[ƒWƒƒ
LRESULT CALLBACK LayerWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	RECT clipRect	= {0, 0, 500, 500};
	HBRUSH hBrush;
	HPEN hPen;
	HFONT hFont;


	switch (message)
	{
	case WM_ERASEBKGND:
		 GetClientRect(hWnd, &clipRect);
		
		hdc = GetDC(hWnd);
        hBrush = CreateSolidBrush(RGB(100,100,100));
        SelectObject(hdc, hBrush);
		hPen = CreatePen(PS_DASH,1,RGB(255,255,255));
		SelectObject(hdc, hPen);
		Rectangle(hdc,0,0,clipRect.right,clipRect.bottom);

		//‹éŒ`‚ÌƒTƒCƒY‚ğo—Í
		int fHeight;
		fHeight = -MulDiv(8, GetDeviceCaps(hdc, LOGPIXELSY), 72);
		hFont = CreateFont(fHeight,    //ƒtƒHƒ“ƒg‚‚³
			0,                    //•¶š•
			0,                    //ƒeƒLƒXƒg‚ÌŠp“x
			0,                    //ƒx[ƒXƒ‰ƒCƒ“‚Æ‚˜²‚Æ‚ÌŠp“x
			FW_REGULAR,            //ƒtƒHƒ“ƒg‚Ìd‚³i‘¾‚³j
			FALSE,                //ƒCƒ^ƒŠƒbƒN‘Ì
			FALSE,                //ƒAƒ“ƒ_[ƒ‰ƒCƒ“
			FALSE,                //‘Å‚¿Á‚µü
			ANSI_CHARSET,    //•¶šƒZƒbƒg
			OUT_DEFAULT_PRECIS,    //o—Í¸“x
			CLIP_DEFAULT_PRECIS,//ƒNƒŠƒbƒsƒ“ƒO¸“x
			PROOF_QUALITY,        //o—Í•i¿
			FIXED_PITCH | FF_MODERN,//ƒsƒbƒ`‚Æƒtƒ@ƒ~ƒŠ[
			L"Tahoma");    //‘‘Ì–¼

		SelectObject(hdc, hFont);
		// show size
		int iWidth, iHeight;
		iWidth  = clipRect.right  - clipRect.left;
		iHeight = clipRect.bottom - clipRect.top;

		wchar_t sWidth[200], sHeight[200];
		swprintf_s(sWidth, L"%d", iWidth);
		swprintf_s(sHeight, L"%d", iHeight);

		int w,h,h2;
		w = -fHeight * 2.5 + 8;
		h = -fHeight * 2 + 8;
		h2 = h + fHeight;

		SetBkMode(hdc,TRANSPARENT);
		SetTextColor(hdc,RGB(0,0,0));
		TextOut(hdc, clipRect.right-w+1,clipRect.bottom-h+1,(LPCWSTR)sWidth,wcslen(sWidth));
		TextOut(hdc, clipRect.right-w+1,clipRect.bottom-h2+1,(LPCWSTR)sHeight,wcslen(sHeight));
		SetTextColor(hdc,RGB(255,255,255));
		TextOut(hdc, clipRect.right-w,clipRect.bottom-h,(LPCWSTR)sWidth,wcslen(sWidth));
		TextOut(hdc, clipRect.right-w,clipRect.bottom-h2,(LPCWSTR)sHeight,wcslen(sHeight));

		DeleteObject(hPen);
		DeleteObject(hBrush);
		DeleteObject(hFont);
		ReleaseDC(hWnd, hdc);

		return TRUE;

        break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;

}

// ƒEƒBƒ“ƒhƒEƒvƒƒV[ƒWƒƒ
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	
	static BOOL onClip		= FALSE;
	static BOOL firstDraw	= TRUE;
	static RECT clipRect	= {0, 0, 0, 0};
	
	switch (message)
	{
	case WM_RBUTTONDOWN:
		// ƒLƒƒƒ“ƒZƒ‹
		DestroyWindow(hWnd);
		return DefWindowProc(hWnd, message, wParam, lParam);
		break;

	case WM_TIMER:
		// ESCƒL[‰Ÿ‰º‚ÌŒŸ’m
		if (GetKeyState(VK_ESCAPE) & 0x8000){
			DestroyWindow(hWnd);
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;

	case WM_MOUSEMOVE:
		if (onClip) {
			// V‚µ‚¢À•W‚ğƒZƒbƒg
			clipRect.right  = LOWORD(lParam) + ofX;
			clipRect.bottom = HIWORD(lParam) + ofY;
			
			hdc = GetDC(NULL);
			drawRubberband(hdc, &clipRect, FALSE);

			ReleaseDC(NULL, hdc);
		}
		break;
	

	case WM_LBUTTONDOWN:
		{
			// ƒNƒŠƒbƒvŠJn
			onClip = TRUE;
			
			// ‰ŠúˆÊ’u‚ğƒZƒbƒg
			clipRect.left = LOWORD(lParam) + ofX;
			clipRect.top  = HIWORD(lParam) + ofY;
			


			// ƒ}ƒEƒX‚ğƒLƒƒƒvƒ`ƒƒ
			SetCapture(hWnd);
		}
		break;

	case WM_LBUTTONUP:
		{
			// ƒNƒŠƒbƒvI—¹
			onClip = FALSE;
			
			// ƒ}ƒEƒX‚ÌƒLƒƒƒvƒ`ƒƒ‚ğ‰ğœ
			ReleaseCapture();
		
			// V‚µ‚¢À•W‚ğƒZƒbƒg
			clipRect.right  = LOWORD(lParam) + ofX;
			clipRect.bottom = HIWORD(lParam) + ofY;

			// ‰æ–Ê‚É’¼Ú•`‰æC‚Á‚ÄŒ`
			HDC hdc = GetDC(NULL);

			// ü‚ğÁ‚·
			drawRubberband(hdc, &clipRect, TRUE);

			// À•Wƒ`ƒFƒbƒN
			if ( clipRect.right  < clipRect.left ) {
				int tmp = clipRect.left;
				clipRect.left   = clipRect.right;
				clipRect.right  = tmp;
			}
			if ( clipRect.bottom < clipRect.top  ) {
				int tmp = clipRect.top;
				clipRect.top    = clipRect.bottom;
				clipRect.bottom = tmp;
			}
			
			// ‰æ‘œ‚ÌƒLƒƒƒvƒ`ƒƒ
			int iWidth, iHeight;
			iWidth  = clipRect.right  - clipRect.left + 1;
			iHeight = clipRect.bottom - clipRect.top  + 1;

			if(iWidth == 0 || iHeight == 0) {
				// ‰æ‘œ‚É‚È‚Á‚Ä‚È‚¢, ‚È‚É‚à‚µ‚È‚¢
				ReleaseDC(NULL, hdc);
				DestroyWindow(hWnd);
				break;
			}

			// ƒrƒbƒgƒ}ƒbƒvƒoƒbƒtƒ@‚ğì¬
			HBITMAP newBMP = CreateCompatibleBitmap(hdc, iWidth, iHeight);
			HDC	    newDC  = CreateCompatibleDC(hdc);
			
			// ŠÖ˜A‚Ã‚¯
			SelectObject(newDC, newBMP);

			// ‰æ‘œ‚ğæ“¾
			BitBlt(newDC, 0, 0, iWidth, iHeight, 
				hdc, clipRect.left, clipRect.top, SRCCOPY);
			
			// ƒEƒBƒ“ƒhƒE‚ğ‰B‚·!
			ShowWindow(hWnd, SW_HIDE);
			/*
			// ‰æ‘œ‚ğƒNƒŠƒbƒvƒ{[ƒh‚ÉƒRƒs[
			if ( OpenClipboard(hWnd) ) {
				// Á‹
				EmptyClipboard();
				// ƒZƒbƒg
				SetClipboardData(CF_BITMAP, newBMP);
				// •Â‚¶‚é
				CloseClipboard();
			}
			*/
			
			// ƒeƒ“ƒ|ƒ‰ƒŠƒtƒ@ƒCƒ‹–¼‚ğŒˆ’è
			TCHAR tmpDir[MAX_PATH], tmpFile[MAX_PATH];
			GetTempPath(MAX_PATH, tmpDir);
			GetTempFileName(tmpDir, _T("yeytmp"), 0, tmpFile);
			
			if (savePNG(tmpFile, newBMP)) {

				// ‚¤‚
				if (!uploadFile(hWnd, tmpFile)) {
					// ƒAƒbƒvƒ[ƒh‚É¸”s...
					// ƒGƒ‰[ƒƒbƒZ[ƒW‚ÍŠù‚É•\¦‚³‚ê‚Ä‚¢‚é

					/*
					TCHAR sysDir[MAX_PATH];
					if (SUCCEEDED(StringCchCopy(sysDir, MAX_PATH, tmpFile)) &&
						SUCCEEDED(StringCchCat(sysDir, MAX_PATH, _T(".png")))) {
						
						MoveFile(tmpFile, sysDir);
						SHELLEXECUTEINFO lsw = {0};
						
						lsw.hwnd	= hWnd;
						lsw.cbSize	= sizeof(SHELLEXECUTEINFO);
						lsw.lpVerb	= _T("open");
						lsw.lpFile	= sysDir;

						ShellExecuteEx(&lsw);
					}
					*/
				}
			} else {
				// PNG•Û‘¶¸”s...
				MessageBox(hWnd, _T("Cannot save png image"), szTitle, 
					MB_OK | MB_ICONERROR);
			}

			// Œãn––
			DeleteFile(tmpFile);
			
			DeleteDC(newDC);
			DeleteObject(newBMP);

			ReleaseDC(NULL, hdc);
			DestroyWindow(hWnd);
			PostQuitMessage(0);
		}
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// ƒNƒŠƒbƒvƒ{[ƒh‚É•¶š—ñ‚ğƒRƒs[
VOID setClipBoardText(const char* str)
{

	HGLOBAL hText;
	char    *pText;
	size_t  slen;

	slen  = strlen(str) + 1; // NULL

	hText = GlobalAlloc(GMEM_DDESHARE | GMEM_MOVEABLE, slen * sizeof(TCHAR));

	pText = (char *)GlobalLock(hText);
	strncpy_s(pText, slen, str, slen);
	GlobalUnlock(hText);
	
	// ƒNƒŠƒbƒvƒ{[ƒh‚ğŠJ‚­
	OpenClipboard(NULL);
	EmptyClipboard();
	SetClipboardData(CF_TEXT, hText);
	CloseClipboard();

	// ‰ğ•ú
	GlobalFree(hText);
}

// w’è‚³‚ê‚½ URL (char*) ‚ğƒuƒ‰ƒEƒU‚ÅŠJ‚­
VOID execUrl(const char* str)
{
	size_t  slen;
	size_t  dcount;
	slen  = strlen(str) + 1; // NULL

	TCHAR *wcUrl = (TCHAR *)malloc(slen * sizeof(TCHAR));
	
	// ƒƒCƒh•¶š‚É•ÏŠ·
	mbstowcs_s(&dcount, wcUrl, slen, str, slen);
	
	// open ƒRƒ}ƒ“ƒh‚ğÀs
	SHELLEXECUTEINFO lsw = {0};
	lsw.cbSize = sizeof(SHELLEXECUTEINFO);
	lsw.lpVerb = _T("open");
	lsw.lpFile = wcUrl;

	ShellExecuteEx(&lsw);

	free(wcUrl);
}

// ID ‚ğ¶¬Eƒ[ƒh‚·‚é


// PNG ƒtƒ@ƒCƒ‹‚ğƒAƒbƒvƒ[ƒh‚·‚é.
BOOL uploadFile(HWND hwnd, LPCTSTR fileName)
{
	const TCHAR* UPLOAD_SERVER	= _T("yey.nu");
	const TCHAR* UPLOAD_PATH	= _T("/desktop.php");

	const char*  sBoundary = "----BOUNDARYBOUNDARY----";		// boundary
	const char   sCrLf[]   = { 0xd, 0xa, 0x0 };					// ‰üs(CR+LF)
	const TCHAR* szHeader  = 
		_T("Content-type: multipart/form-data; boundary=----BOUNDARYBOUNDARY----");

	std::ostringstream	buf;	// ‘—MƒƒbƒZ[ƒW
	std::string			idStr;	// ID
	
	// ID ‚ğæ“¾


	// ƒƒbƒZ[ƒW‚Ì\¬
	// -- "id" part
	buf << "--";
	buf << sBoundary;
	buf << sCrLf;
	buf << "content-disposition: form-data; name=\"id\"";
	buf << sCrLf;
	buf << sCrLf;
	buf << idStr;
	buf << sCrLf;

	// -- "imagedata" part
	buf << "--";
	buf << sBoundary;
	buf << sCrLf;
	buf << "content-disposition: form-data; name=\"imagedata\"; filename=\"filedata\"";
	buf << sCrLf;
	//buf << "Content-type: image/png";	// ˆê‰
	//buf << sCrLf;
	buf << sCrLf;

	// –{•¶: PNG ƒtƒ@ƒCƒ‹‚ğ“Ç‚İ‚Ş
	std::ifstream png;
	png.open(fileName, std::ios::binary);
	if (png.fail()) {
		MessageBox(hwnd, _T("PNG open failed"), szTitle, MB_ICONERROR | MB_OK);
		png.close();
		return FALSE;
	}
	buf << png.rdbuf();		// read all & append to buffer
	png.close();

	// ÅŒã
	buf << sCrLf;
	buf << "--";
	buf << sBoundary;
	buf << "--";
	buf << sCrLf;

	// ƒƒbƒZ[ƒWŠ®¬
	std::string oMsg(buf.str());

	// WinInet ‚ğ€”õ (proxy ‚Í ‹K’è‚Ìİ’è‚ğ—˜—p)
	HINTERNET hSession    = InternetOpen(szTitle, 
		INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, 0);
	if(NULL == hSession) {
		MessageBox(hwnd, _T("Cannot configure wininet"),
			szTitle, MB_ICONERROR | MB_OK);
		return FALSE;
	}
	
	// Ú‘±æ
	HINTERNET hConnection = InternetConnect(hSession, 
		UPLOAD_SERVER, INTERNET_DEFAULT_HTTP_PORT,
		NULL, NULL, INTERNET_SERVICE_HTTP, 0, NULL);
	if(NULL == hSession) {
		MessageBox(hwnd, _T("Cannot initiate connection"),
			szTitle, MB_ICONERROR | MB_OK);
		return FALSE;
	}

	// —v‹æ‚Ìİ’è
	HINTERNET hRequest    = HttpOpenRequest(hConnection,
		_T("POST"), UPLOAD_PATH, NULL,
		NULL, NULL, INTERNET_FLAG_DONT_CACHE | INTERNET_FLAG_RELOAD, NULL);
	if(NULL == hSession) {
		MessageBox(hwnd, _T("Cannot compose post request"),
			szTitle, MB_ICONERROR | MB_OK);
		return FALSE;
	}

	// User-Agent‚ğw’è
	const TCHAR* ua = _T("User-Agent: Yey-Desktop/1.0\r\n");
	BOOL bResult = HttpAddRequestHeaders(
		hRequest, ua, _tcslen(ua), 
		HTTP_ADDREQ_FLAG_ADD | HTTP_ADDREQ_FLAG_REPLACE);
	if (FALSE == bResult) {
		MessageBox(hwnd, _T("Cannot set user agent"),
			szTitle, MB_ICONERROR | MB_OK);
		return FALSE;
	}
	
    Thread th;
    th.forts = true;
    th.tal = 0;
	_beginthread (Thread1, 0, &th);

	//MessageBox(hwnd, _T("Din fil håller nu på att laddas upp! \nVar god vänta...\nOm du stänger denna ruta kommer uppladdning forsättas."), szTitle, MB_ICONINFORMATION | MB_OK);

	// —v‹‚ğ‘—M
	if (HttpSendRequest(hRequest,
                    szHeader,
					lstrlen(szHeader),
                    (LPVOID)oMsg.c_str(),
					(DWORD) oMsg.length()))
	{
	
		// —v‹‚Í¬Œ÷
		
		DWORD resLen = 8;
		TCHAR resCode[8];

		// status code ‚ğæ“¾
		HttpQueryInfo(hRequest, HTTP_QUERY_STATUS_CODE, resCode, &resLen, 0);

		

		if( _ttoi(resCode) != 200 ) {
			// upload ¸”s (status error)
			MessageBox(hwnd, _T("Failed to upload (unexpected result code, under maintainance?)"),
				szTitle, MB_ICONERROR | MB_OK);
		} else {
			// upload succeeded


			// Œ‹‰Ê (URL) ‚ğ“Çæ‚é
			DWORD len;
			char  resbuf[1024];
			std::string result;
			
			// ‚»‚ñ‚È‚É’·‚¢‚±‚Æ‚Í‚È‚¢‚¯‚Ç‚Ü‚ ˆê‰
			while(InternetReadFile(hRequest, (LPVOID) resbuf, 1024, &len) 
				&& len != 0)
			{
				result.append(resbuf, len);
			}

			// æ“¾Œ‹‰Ê‚Í NULL terminate ‚³‚ê‚Ä‚¢‚È‚¢‚Ì‚Å
			result += '\0';


		string str;

		str ="yey-browser.exe";

		string str2;
		str2 = " ";
		str2 = result.c_str();
		std::wstring widestr = std::wstring(str.begin(), str.end());
		std::wstring widestr2 = std::wstring(str2.begin(), str2.end());

		const wchar_t* majs = (const wchar_t*)(widestr.c_str());
		const wchar_t* linksis = (const wchar_t*)(widestr2.c_str());	

		ShellExecute(
		NULL,
		_T("open"),                     
		majs,
		linksis, // params                            
		NULL, 
		SW_SHOW);

			return TRUE;
		}
	} else {
		// ƒAƒbƒvƒ[ƒh¸”s...
		MessageBox(hwnd, _T("Failed to upload"), szTitle, MB_ICONERROR | MB_OK);
	}

	return FALSE;

}

void Thread1 (PVOID pvoid)
{
	MessageBox(NULL, _T("Your screenshot is getting uploaded! \nPlease wait...\nThis window will close itself when it's finished."), szTitle, MB_ICONINFORMATION);          
}
