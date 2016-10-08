/*******************************************************************
程序：Keyboard
文件：Keyboard.c
功能：键盘输入演示程序
********************************************************************/
#include <windows.h>
#include <windowsx.h>
#include<time.h>
#include<stdlib.h>
#include<stdio.h>
#include<WinUser.h>
#define MB_OK                       0x00000000L

BOOL InitWindow (HINSTANCE hInstance, int nCmdShow);
LRESULT CALLBACK WinProc (HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
void random(void);
char string[17]="abcdefghigklmnop";//一行有16个字符
int count=0;
char chengji[3]="00";//成绩
int jiemian=1;//界面标志位
char sbuf[20]="";//坐标

int WINAPI WinMain (HINSTANCE hInstance, 
                    HINSTANCE hPrevInstance,
                    PSTR szCmdLine,
                    int iCmdShow)
{
	MSG msg;

	if (!InitWindow (hInstance, iCmdShow))
	return FALSE;

	while (GetMessage (&msg, NULL, 0, 0))
	{
		TranslateMessage (&msg);         //转换键盘击键消息，以获得字符消息
		DispatchMessage (&msg);
	}

	return msg.wParam;
}

static BOOL InitWindow (HINSTANCE hInstance, int iCmdShow)
{
	static TCHAR szAppName[] = TEXT ("Keyboard");
	HWND hwnd;
	WNDCLASS wc;

	wc.style = CS_VREDRAW | CS_HREDRAW;
	wc.lpfnWndProc = WinProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon (hInstance, IDI_APPLICATION);
	wc.hCursor = LoadCursor (NULL, IDC_ARROW);
	wc.hbrBackground = (struct HBRUSH__ *)GetStockObject (WHITE_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = szAppName;

	if (!RegisterClass (&wc))
	{
		MessageBox (NULL, TEXT ("注册窗口类失败！"), szAppName,
                    MB_ICONERROR);
		return 0;
	}

	hwnd = CreateWindow (szAppName,
	                    TEXT ("MADE BY jingtiangao！"),
                     	WS_OVERLAPPEDWINDOW,
                        CW_USEDEFAULT,
                        CW_USEDEFAULT,
                        CW_USEDEFAULT,
                        CW_USEDEFAULT,
                        NULL,
                        NULL,
                        hInstance,
                        NULL);

	if( !hwnd ) return FALSE;

	ShowWindow( hwnd, iCmdShow );
	UpdateWindow( hwnd );
	return TRUE;
}

//窗口函数
LRESULT CALLBACK WinProc (HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	HDC           hdc;
	PAINTSTRUCT  ps;
	RECT          rect;
	char          aChar;             //字符键
	int i;
		static TCHAR    szText[] = TEXT ("位图");
	static HDC      hdcMem;
	static HBITMAP  hBitmap;
	SIZE            size;
	HBITMAP         hOldBitmap;
	BITMAP          bm;
	int             nWidthSrc, nHeightSrc;
	int             nWidthDest, nHeightDest;
	HBRUSH          hPatternBrush, hOldBrush;
	

	//random();

	switch (message)
	{
	case WM_CREATE:         //创建内存设备描述表
		hdc = GetDC (hWnd);
		hdcMem = CreateCompatibleDC (hdc);			
		ReleaseDC (hWnd, hdc);
		return 0;
	case WM_SETFOCUS:
		CreateCaret (hWnd, NULL, 2, 15);	//创建8*15大小的插入符
		SetCaretPos (10, 10);               //设置插入符新位置为客户区左上角
		ShowCaret (hWnd);                   //显示插入符
		return 0;
	case WM_KILLFOCUS:
		HideCaret (hWnd);                    //隐藏插入符
		DestroyCaret ();                     //撤消插入符
		return 0;
	case WM_MOUSEMOVE:
	int x;
	int y;
    x=LOWORD(lParam);
    y=HIWORD(lParam);
	wsprintf(sbuf,"%04d,%04d",x,y);
	hdc = GetDC (hWnd);
	GetClientRect (hWnd, &rect);
	DrawText (hdc,sbuf , -1, &rect,DT_TOP| DT_RIGHT );	//显示鼠标坐标
	
	ReleaseDC (hWnd, hdc);

	return 0;
//	case WM_SYSKEYDOWN:
//		MessageBeep(MB_ICONHAND);
//		return 0;
	case WM_KEYDOWN:
		switch(wParam)
		{
		case VK_ESCAPE:
			MessageBox(hWnd,TEXT("游戏即将结束！"),TEXT("键盘"),MB_OK);
			
			jiemian=1;
			InvalidateRect(hWnd, NULL, true);
			break;
		case VK_RETURN:
			if(jiemian==1)
			{MessageBox(hWnd,TEXT("游戏即将开始"),TEXT("键盘"),MB_OK);
			jiemian=0;
			InvalidateRect(hWnd, NULL, true);}
			else
			MessageBox(hWnd,TEXT("游戏已经开始，请不要重复按键"),TEXT("键盘"),MB_OK);
			
			break;

		}


		return 0;

	case WM_CHAR:
		if ((lParam&0xffff) > 1 && (lParam&0xffff)<255)
		{
			i=lParam&0xffff;
			MessageBeep(0);
		}
		aChar = wParam;
						
		if(aChar==string[count])//当我按下一个键判断一下是不是等于下一个字符，如果是那么重绘，加分，如果不是，不管
								//当打完一行时马上RANDOM下一行
								//每打完一个字符串后奖励一定的分数
		{
				string[count]=' ';
		
				InvalidateRect(NULL,NULL,TRUE);
			
									if(chengji[1]=='9')//每按对一个字符，奖励一分
									{	
											chengji[0]++;
											chengji[1]='0';
									}
									else	
									{
										chengji[1]++;
									}
					if(count<15)
						count++;
					else
					{
									

						count=0;
						random();
					}	
					
		}

		return 0;
	case WM_PAINT://窗口重画消息,如果回车键按下了，就画游戏开始，如果ESC按下了就回到开始界面
			
		if(jiemian==0&&((chengji[1]!='9')||(chengji[0]!='9')))
		{
				 hdc=BeginPaint(hWnd,&ps);
				 GetClientRect (hWnd, &rect);
				 DrawText (hdc, TEXT("欢迎来到打字游戏"), -1, &rect, 
							DT_SINGLELINE | DT_CENTER| DT_TOP); //显示当前字符
				 DrawText (hdc, chengji, -1, &rect, 
							DT_SINGLELINE | DT_LEFT| DT_TOP); //左上角显示成绩
				 DrawText (hdc, string, -1, &rect, 	DT_SINGLELINE | DT_CENTER | DT_VCENTER); //将string字符串显示在中央
				 
				 EndPaint(hWnd,&ps);
				 return 0;
		}
		else if(jiemian==1)
		{
			hdc=BeginPaint(hWnd,&ps);
			GetClientRect (hWnd, &rect);
			//加载名为 MYBITMAP 的已知位图
			
			
			hBitmap = LoadBitmap ((HINSTANCE)GetWindowLong (hWnd, GWL_HINSTANCE), TEXT ("MYBITMAP"));
			GetObject (hBitmap, sizeof (BITMAP), &bm);
			nWidthSrc = bm.bmWidth;
			nHeightSrc = bm.bmHeight;
			/*hOldBitmap =(HBITMAP) SelectObject (hdcMem, hBitmap);
				
			BitBlt (hdc, (rect.right - nWidthSrc)/2, (rect.bottom - nHeightSrc)/2,
					nWidthSrc, nHeightSrc, hdcMem, 0, 0, SRCCOPY);
			
			SelectObject (hdcMem, hOldBitmap);  //此为bitbLT显示*/
			nWidthDest = rect.right;
			nHeightDest = rect.bottom;

			hOldBitmap = (HBITMAP)SelectObject (hdcMem, hBitmap);
			StretchBlt (hdc, 0, 0, nWidthDest, nHeightDest,
						hdcMem, 0, 0, nWidthSrc, nHeightSrc, SRCCOPY);
			SelectObject (hdcMem, hOldBitmap);
			DrawText (hdc, TEXT("这是一个有酒神式的毁灭力量，让你欲罢不能的游戏！"), -1, &rect, 
							  DT_CENTER| DT_TOP); //显示当前字符
			DrawText (hdc, TEXT("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n按下回车键开始游戏\n按下ESC键终止游戏并返回开始界面\n\n\n本游戏会自动保存进度，无须存档\n\n\n\n注：本游戏有隐藏福利，获得99分就会出现惊喜"), -1, &rect, 
							 DT_CENTER ); 
			EndPaint(hWnd,&ps);
			
			return 0;

		}
		else if((chengji[1]='9')&&(chengji[0]='9'))
		{
			hdc=BeginPaint(hWnd,&ps);
			GetClientRect (hWnd, &rect);
			//加载名为 MYBITMAP 的已知位图
			
			
			hBitmap = LoadBitmap ((HINSTANCE)GetWindowLong (hWnd, GWL_HINSTANCE), TEXT ("MYBITMAP1"));
			GetObject (hBitmap, sizeof (BITMAP), &bm);
			nWidthSrc = bm.bmWidth;
			nHeightSrc = bm.bmHeight;
			hOldBitmap =(HBITMAP) SelectObject (hdcMem, hBitmap);
				
			BitBlt (hdc, (rect.right - nWidthSrc)/2, (rect.bottom - nHeightSrc)/2,
					nWidthSrc, nHeightSrc, hdcMem, 0, 0, SRCCOPY);
			
			SelectObject (hdcMem, hOldBitmap);  //此为bitbLT显示
			/*nWidthDest = rect.right;
			nHeightDest = rect.bottom;

			hOldBitmap = (HBITMAP)SelectObject (hdcMem, hBitmap);
			StretchBlt (hdc, 0, 0, nWidthDest, nHeightDest,
						hdcMem, 0, 0, nWidthSrc, nHeightSrc, SRCCOPY);
			SelectObject (hdcMem, hOldBitmap);*///此为拉伸显示
			EndPaint(hWnd,&ps);
			
			return 0;
		}


	case WM_DESTROY:
			
		PostQuitMessage (0);
		return 0;
	}			  


	return DefWindowProc (hWnd, message, wParam, lParam);

} //函数 WinProc 结束

void random(void)
{
	srand((int)time(0));
	for(int j=0;j<16;j++)
	{
		string[j]='a' + rand()%('z'-'a'+1) ;
	}
}