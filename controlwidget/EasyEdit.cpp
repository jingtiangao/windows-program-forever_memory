/*******************************************************************
程序：EasyEdit
文件：EasyEdit.c
功能：标准控件演示程序—文本编辑器
********************************************************************/
#include <windows.h>
#include <windowsx.h>
#include "exp0302\resource.h"
BOOL InitWindow (HINSTANCE hInstance, int nCmdShow);
LRESULT CALLBACK MainWndProc (HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
char mess1[20]="习老大";
char mess2[20]="李老二";
HINSTANCE hInst;                                  //全局变量——实例句柄
HMENU hPopMenu;
int count;
HWND hWnd1;
int WINAPI WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance,
                    PSTR szCmdLine, int iCmdShow)
{
	MSG msg;
	hInst = hInstance;
	HACCEL       hAccel;
	if (!InitWindow (hInstance, iCmdShow))
	return FALSE;
	
	hAccel = LoadAccelerators (hInstance,(LPCSTR)IDR_ACCELERATOR1);
	/*while (GetMessage (&msg, NULL, 0, 0))
	{
		TranslateMessage (&msg);
		DispatchMessage (&msg);
	}*/
	/*if(count)
	{*/
			while (GetMessage (&msg, NULL, 0, 0))//修改后的消息循环
			{
				if (!TranslateAccelerator (hWnd1, hAccel, &msg))
				{
					TranslateMessage (&msg);
					DispatchMessage (&msg);
				}
			}
	/*}
	else
	{
		GetMessage (&msg, NULL, 0, 0);
		TranslateMessage (&msg);
		DispatchMessage (&msg);
		count;
	}*/
	return msg.wParam;
}

static BOOL InitWindow (HINSTANCE hInstance, int iCmdShow)
{
	static TCHAR szAppName[] = TEXT ("EasyEdit");
	HWND hwnd;   
	WNDCLASS wc; 

	wc.style = CS_VREDRAW | CS_HREDRAW;
	wc.lpfnWndProc = MainWndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon (hInstance, MAKEINTRESOURCE(IDI_ICON1));
	wc.hCursor = LoadCursor (hInstance, MAKEINTRESOURCE(IDC_CURSOR1));
	wc.hbrBackground = (HBRUSH)GetStockObject (WHITE_BRUSH);
	wc.lpszMenuName = (LPCSTR)IDR_MENU1;
	wc.lpszClassName = szAppName;

	if (!RegisterClass (&wc))
	{
		MessageBox (NULL, TEXT ("注册窗口类失败！"), szAppName,
                    MB_ICONERROR);
		return 0;
	}

	hwnd = CreateWindow (szAppName, 
	                    TEXT ("标准控件演示程序—文本编辑器"),
                     	WS_OVERLAPPEDWINDOW,
                        CW_USEDEFAULT, 
                        CW_USEDEFAULT, 
                        CW_USEDEFAULT,
                        CW_USEDEFAULT,
                        NULL, 
                        NULL,
                        hInstance, 
                        NULL); 
	hWnd1=hwnd;
	if( !hwnd ) return FALSE;

	ShowWindow ( hwnd, iCmdShow );
	UpdateWindow ( hwnd );
	return TRUE;
}

LRESULT CALLBACK MainWndProc (HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static HWND  hWndEdit;
	static HWND  hWndCom;
	static HWND  hWndBn;
	static HWND  hWndListbox;
	static HWND  sstatic;
	HCURSOR hNewCursor;
	HICON hIcon;
	HDC hdc;
	PAINTSTRUCT ps;
	RECT        rect;
	POINT pt;
	switch (message)
	{
	case WM_CREATE:
		hWndEdit=CreateWindow (TEXT ("edit"),			        //窗口类名
							  NULL,			                    //无标题
							  WS_CHILD|WS_VISIBLE|	//编辑控件风格
							  WS_BORDER|ES_LEFT|
							  ES_MULTILINE|ES_AUTOHSCROLL|
							  ES_AUTOVSCROLL,
							  0,0,0,0,	
							  hWnd,		                        //父窗口句柄
							  (HMENU)1,		                        //编辑控件子窗口标识
							  (HINSTANCE) GetWindowLong (hWnd, GWL_HINSTANCE),
							  NULL);
		hWndCom=CreateWindow (TEXT ("combobox"),			        //窗口类名
							  NULL,			                    //无标题
							  WS_CHILD|WS_VISIBLE|WS_HSCROLL|	//编辑控件风格
							  WS_VSCROLL|WS_BORDER|CBS_DROPDOWN|CBS_AUTOHSCROLL,
							  0,0,0,0,	
							  hWnd,		                        //父窗口句柄
							  (HMENU)2,		                        //编辑控件子窗口标识
							  (HINSTANCE) GetWindowLong (hWnd, GWL_HINSTANCE),
							  NULL);
		hWndBn=CreateWindow (TEXT ("button"),			        //窗口类名
							  TEXT("你没有看错，这是一个超级大的按钮"),			                    //无标题
							  WS_CHILD|WS_VISIBLE|BS_PUSHBUTTON,
							  0,0,0,0,	
							  hWnd,		                        //父窗口句柄
							  (HMENU)3,		                        //编辑控件子窗口标识
							  (HINSTANCE) GetWindowLong (hWnd, GWL_HINSTANCE),
							  NULL);
		
		hWndListbox=CreateWindow (TEXT ("listbox"),			        //窗口类名
							  NULL,			                    //无标题
							  WS_CHILD|WS_VISIBLE|WS_BORDER|LBS_STANDARD,
							  0,0,0,0,	
							  hWnd,		                        //父窗口句柄
							  (HMENU)3,		                        //编辑控件子窗口标识
							  (HINSTANCE) GetWindowLong (hWnd, GWL_HINSTANCE),
							  NULL);
		sstatic=CreateWindow (TEXT ("static"),			        //窗口类名
							  TEXT("这是一个标签"),			                    //无标题
							  WS_CHILD|WS_VISIBLE|SBS_HORZ,
							  0,0,0,0,	
							  hWnd,		                        //父窗口句柄
							  (HMENU)3,		                        //编辑控件子窗口标识
							  (HINSTANCE) GetWindowLong (hWnd, GWL_HINSTANCE),
							  NULL);
			SendMessage(hWndListbox, LB_ADDSTRING, 0, (LPARAM)mess1);
			SendMessage(hWndListbox, LB_ADDSTRING, 0, (LPARAM)mess2);
			SendMessage(hWndCom, CB_ADDSTRING, 0, (LPARAM)mess1);
			SendMessage(hWndCom, CB_ADDSTRING, 0, (LPARAM)mess2);
	
			hPopMenu = LoadMenu(hInst,(LPCSTR)IDR_MENU1);
			hPopMenu=GetSubMenu(hPopMenu,0);
			return 0;
	case WM_RBUTTONDOWN:
		pt.x=LOWORD(lParam);
		pt.y=HIWORD(lParam);
		ClientToScreen(hWnd,&pt);
		TrackPopupMenu(hPopMenu,TPM_LEFTALIGN|TPM_TOPALIGN|TPM_LEFTBUTTON,pt.x,pt.y,0,hWnd,NULL);
		return 0;

		

	case WM_SETFOCUS:
		SetFocus (hWndEdit);
		return 0;

	case WM_SIZE:
		MoveWindow (hWndEdit, 0, 0, LOWORD(lParam)/4, HIWORD(lParam)/4, TRUE);
		MoveWindow (hWndCom, LOWORD(lParam)/4, 0, LOWORD(lParam)/2, HIWORD(lParam)/4, TRUE);
		MoveWindow (hWndBn, 0, LOWORD(lParam)/4, LOWORD(lParam)/4, HIWORD(lParam)/2, TRUE);
		MoveWindow (hWndListbox, LOWORD(lParam)/4, LOWORD(lParam)/4, LOWORD(lParam)/2, HIWORD(lParam)/2, TRUE);
		MoveWindow (sstatic, LOWORD(lParam)*3/4, 0, LOWORD(lParam)*3/4, HIWORD(lParam)/4, TRUE);
		return 0;

	case WM_COMMAND:        	
			
			WORD w, W1, W2, W3;
			w = LOWORD (wParam);
			W1 = HIWORD(wParam);
			W2 = LOWORD (lParam);
			W3 = HIWORD(lParam);
		if (lParam)// 响应编辑控件通知消息
		{
			
			
			if ((LOWORD (wParam) == 1) &&
				(HIWORD(wParam) == EN_ERRSPACE || HIWORD (wParam) == EN_MAXTEXT))
				MessageBox (hWnd,TEXT ("编辑控件内存溢出"), 
							TEXT ("菜单示例程序"), MB_OK|MB_ICONSTOP);	
			//用swich来处理空间向父窗口发送的通知消息
			switch(W1)
			{
			
			case	BN_CLICKED:
				MessageBox (hWnd, TEXT ("按钮君被你按了一下"), TEXT ("BUTTON"), MB_OK);
				break;
			/*case	BN_DBLCLK:
				MessageBox (hWnd, TEXT ("你按了按钮君两下"), TEXT ("BUTTON"), MB_OK);
				break;*/
			case	CBN_DROPDOWN:
				MessageBox (hWnd, TEXT ("你已经拉下了组合框君"), TEXT ("组合框君"), MB_OK);
				break;
			case   LBN_DBLCLK :
				MessageBox (hWnd, TEXT ("你双击了列表框君"), TEXT ("列表框君"), MB_OK);
				break;



			}

		}
		else		//处理菜单的消息
		{
			 switch(w)
			 {
			 case ID_CHANGECURSOR:
				 hNewCursor = LoadCursor (hInst, MAKEINTRESOURCE(IDC_CURSOR3));
				SetClassLong (hWnd,  GCL_HCURSOR,
					(LONG)LoadCursor(hInst, 
			 					MAKEINTRESOURCE(IDC_CURSOR3) ) );
	
				break;
			 case ID_40002:
				 hNewCursor = LoadCursor (hInst, MAKEINTRESOURCE(IDC_CURSOR3));
				SetClassLong (hWnd,  GCL_HCURSOR,
					(LONG)LoadCursor(hInst, 
			 					MAKEINTRESOURCE(IDC_CURSOR1) ) );
				 break;
			 case 0:
				 MessageBox (hWnd, TEXT ("这程序是一个作业演示而已！"),
                 TEXT ("关于"), MB_OK | MB_ICONINFORMATION) ;
				 break;
			 }

		}

		return 0;
	case WM_PAINT:
		//取得设备环境句柄
		hdc = BeginPaint (hWnd, &ps); 
		GetClientRect (hWnd, &rect);
		hIcon=LoadIcon(hInst,MAKEINTRESOURCE(IDI_ICON1));
		DrawIcon(hdc,LOWORD(lParam)/2+100,LOWORD(lParam)/4+200,hIcon);
		EndPaint (hWnd, &ps);
		return 0;
	/*case WM_SETCURSOR:
		hNewCursor = LoadCursor (hInst, MAKEINTRESOURCE(IDC_CURSOR3));
		SetCursor(hNewCursor);	
	return 0;*/
	case WM_DESTROY: 
		PostQuitMessage (0);
		return 0;
	}

	return DefWindowProc (hWnd, message, wParam, lParam);

} //函数 MainWndProc 结束

