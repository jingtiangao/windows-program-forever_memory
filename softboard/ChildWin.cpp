/*******************************************************************
程序：ChildWin
文件：ChildWin.c
功能：子窗口演示程序——命中测试
********************************************************************/
#include <windows.h>
#include <windowsx.h>

#define ROW_NUM 4    //行数
#define COL_NUM 12    //列数

#define WM_CHILDWIN  WM_USER+1    //主窗口通知子窗口的自定义消息
char soft[48]="1234567890-=qwertyuiop[]\\asdfghjkl;'zxcvbnm,./";//软键盘里的内容
	int suojin=0;//显示网格时的缩进数据

BOOL InitWindow (HINSTANCE hInstance, int nCmdShow);

//主窗口函数原型
LRESULT CALLBACK MainWndProc (HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

//子窗口函数原型
LRESULT CALLBACK ChildWndProc (HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

TCHAR szAppName[] = TEXT ("ChildWin");            //主窗口类名称
TCHAR szChildName[] = TEXT ("ChildWin_Child");    //子窗口类名称

HINSTANCE hInst;                                  //全程变量——实例句柄

int BFunc(int *pLenB)
{
	(*pLenB) ++;
	*pLenB = 0;
	(*pLenB) ++;
	return *pLenB;
}

void AFunc(int *pLenA)
{
	BFunc(pLenA);
	if (*pLenA > 10000)
	{
		*pLenA = 100;
	}
}

void UnderstandCallStack(int len)
{
	len = 1000;
	AFunc(&len)	;
}










int WINAPI WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance,
                    PSTR szCmdLine, int iCmdShow)
{
	MSG msg;

	if (!InitWindow (hInstance, iCmdShow))
		return FALSE;

	while (GetMessage (&msg, NULL, 0, 0))
	{
		TranslateMessage (&msg);
		DispatchMessage (&msg);
	}

	return msg.wParam;
}

static BOOL InitWindow (HINSTANCE hInstance, int iCmdShow)
{
	HWND hwnd;   
	WNDCLASS wcMain; 

	wcMain.style         = CS_VREDRAW | CS_HREDRAW;
	wcMain.lpfnWndProc   = MainWndProc;
	wcMain.cbClsExtra    = 0;
	wcMain.cbWndExtra    = 0;
	wcMain.hInstance     = hInstance;
	wcMain.hIcon         = LoadIcon (hInstance, IDI_APPLICATION);
	wcMain.hCursor       = LoadCursor (NULL, IDC_ARROW);
	wcMain.hbrBackground = (HBRUSH)GetStockObject (WHITE_BRUSH);
							//GetStockObject (HOLLOW_BRUSH);
							//CreateSolidBrush(RGB(0,0,255));
	wcMain.lpszMenuName  = NULL;
	wcMain.lpszClassName = szAppName;

	if (!RegisterClass (&wcMain))
	{
		MessageBox (NULL, TEXT ("注册主窗口类失败！"), szAppName,
                    MB_ICONERROR);
		return 0;
	}
	
	hInst = hInstance;

	hwnd = CreateWindow (szAppName, 
	                    TEXT ("模拟软键盘"),
                     	WS_OVERLAPPEDWINDOW,
                        CW_USEDEFAULT, CW_USEDEFAULT, 
						CW_USEDEFAULT, CW_USEDEFAULT,
                        NULL, NULL, hInstance, NULL); 

	if( !hwnd ) return FALSE;

	ShowWindow( hwnd, iCmdShow );
	UpdateWindow( hwnd );
	return TRUE;
}

LRESULT CALLBACK MainWndProc (HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    static HWND hChildWnd[COL_NUM][ROW_NUM];  //子窗口句柄
    static int  nXBox, nYBox;                 //子窗口宽度和高度
    static WORD nChildWin_ID;                 //被命中的子窗口标识
    static int  nRow, nCol;                   //被命中的子窗口位置（即行列号）
	int         x, y;
	WNDCLASS    wcChild;                      //子窗口类
	   RECT        rect1;//专门在wm_size使用的变量
	   HDC         hdc; 
    RECT        rect;
	PAINTSTRUCT ps;
	int a;
    
    switch (message)
    {

    case WM_CREATE:
		wcChild.style         = CS_VREDRAW | CS_HREDRAW;
		wcChild.lpfnWndProc   = ChildWndProc;
		wcChild.cbClsExtra    = 0;
		wcChild.cbWndExtra    = sizeof (long);
		wcChild.hInstance     = hInst;
		wcChild.hIcon         = NULL;
		wcChild.hCursor       = LoadCursor (NULL, IDC_ARROW);
		wcChild.hbrBackground = (HBRUSH)GetStockObject (LTGRAY_BRUSH);
								//GetStockObject (HOLLOW_BRUSH);
		wcChild.lpszMenuName  = NULL;
		wcChild.lpszClassName = szChildName ;
		    
		if (!RegisterClass (&wcChild))
		{
			MessageBox (NULL, TEXT ("注册子窗口类失败！"), szChildName,
				        MB_ICONERROR);
			return 0;
		}

        //创建类似“画图”程序中绘图工具栏的各工具子窗口
		for (x=0; x<COL_NUM; x++)
		for (y=0; y<ROW_NUM; y++)
		{
			nChildWin_ID = x<<4|y;             //子窗口标识值
			hChildWnd[x][y] = CreateWindow (szChildName, NULL,
											WS_CHILDWINDOW | WS_DLGFRAME |WS_VISIBLE,
											0,0,0,0,
											hWnd,
											(HMENU)(nChildWin_ID),
											//0,
											hInst, NULL);
		}
		
		//令0号子窗口为当前命中的子窗口
		nChildWin_ID = 0;
		nRow = 0;
		nCol = 0;
		return 0;

    case WM_SIZE:
        nXBox = (LOWORD (lParam)/2)/COL_NUM;
        nYBox = (HIWORD (lParam)/3)/ROW_NUM;
		
		GetClientRect (hWnd, &rect1);
   		//主窗口大小改变时，重新确定各子窗口在主窗口客户区的位置
		for (y=0; y<ROW_NUM; y++)
		{
			suojin=suojin+nXBox/2;
			for (x=0; x<COL_NUM; x++)
			{
				MoveWindow (hChildWnd[x][y], suojin+x*nXBox, (rect1.bottom-ROW_NUM*nYBox)+y*nYBox, nXBox,nYBox, TRUE);//用平移公式将软键盘显示在下方
			}
		}
		return 0;
          
    case WM_COMMAND:                //子窗口被命中的通知消息
		//当子窗口被命中时发送此消息通知主窗口，以便由主窗口确定是否命中另一个子窗口，
		//若是，则发送消息通知子窗口函数改变前一次被命中子窗口的状态，
		if (!(LOWORD (wParam) == nChildWin_ID))
		{
			SendMessage ((HWND)hChildWnd[nCol][nRow], WM_CHILDWIN, 0, 0L);
			
			//记录新的被命中的子窗口
			nChildWin_ID = LOWORD (wParam);
			nCol = nChildWin_ID>>4;
			//nRow = (nChildWin_ID > 15)?(nChildWin_ID-16):nChildWin_ID;
			nRow = nChildWin_ID&(0x0f);
			GetClientRect (hWnd, &rect);
			rect.bottom=rect.bottom*2/3;
			
			InvalidateRect(hWnd,&rect,TRUE);
			
		}

		return 0;
          
    case WM_LBUTTONDOWN:
		MessageBeep(-1);         //发出标准蜂鸣声
		MessageBox (hWnd, TEXT ("鼠标左键按下了!"), TEXT ("主窗口鼠标消息"), MB_OK);
		return 0;
	case WM_PAINT:
		//在主窗口显示命中的字母
			hdc=BeginPaint(hWnd,&ps);
			GetClientRect (hWnd, &rect);
			a=(nRow*COL_NUM)+(nCol);
		 SetBkMode(hdc,TRANSPARENT);
	
		DrawText (hdc, &soft[a],
			     1, &rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);

			EndPaint(hWnd,&ps);
			return 0;
	case WM_DESTROY: 
		PostQuitMessage (0);
		return 0;
	}

	return DefWindowProc (hWnd, message, wParam, lParam);

} //函数 WinProc 结束

LRESULT CALLBACK ChildWndProc (HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	HDC         hdc;
    PAINTSTRUCT ps;
    RECT        rect;
	HPEN hPen;
	LONG l=0;
	int a;
	static int xy;
	wchar_t buf[20];//每个子窗口要输出的消息
	
	switch (message)
    {
    case WM_CREATE:
		xy ++;
		//置各子窗口命中标志为0，（0号子窗口则为1）
		if (GetWindowLong (hWnd, GWL_ID) == 0)
//		if (GetWindowWord (hWnd, GWL_ID) == 0)		  // 2004.03.11 Liangchenghui
			l=SetWindowLong (hWnd, 0, 1);
		else
			l=SetWindowLong (hWnd, 0, 0);

		return 0;
          
    case WM_LBUTTONDOWN:
		//新的子窗口被命中
		if (GetWindowLong (hWnd, 0) == 0)
		{
			//置该子窗口命中标志为1
			SetWindowLong (hWnd, 0, 1);

			//发送消息通知主窗口
			SendMessage (GetParent (hWnd), WM_COMMAND, 
						//(WPARAM) MAKELONG ((WORD)GetWindowWord (hWnd, GWL_ID), (WORD)0),
						GetWindowLong (hWnd, GWL_ID),
						(LPARAM) hWnd);

			//重绘子窗口客户区
			GetClientRect (hWnd, &rect);
			InvalidateRect (hWnd, &rect, TRUE);
			UnderstandCallStack(rect.right);
		}
		return 0;

    case WM_CHILDWIN:          //主窗口发送的通知消息，改变原命中子窗口的状态
		//置子窗口命中标志为0
		SetWindowLong (hWnd, 0, 0);

		//恢复子窗口初始显示方式
		GetClientRect (hWnd, &rect);
		InvalidateRect (hWnd, &rect,TRUE);

		return 0;

    case WM_PAINT:
        hdc = BeginPaint (hWnd, &ps);
		GetClientRect (hWnd, &rect);
        //显示数组中的内容
		 a=((GetWindowLong (hWnd, GWL_ID)&(0x0f))*COL_NUM)+((GetWindowLong (hWnd, GWL_ID)&(0xf0))>>4);
		 SetBkMode(hdc,TRANSPARENT);
		DrawText (hdc, &soft[a],
			     1, &rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);

		

		//反相绘制被命中的子窗口
		if (GetWindowLong (hWnd, 0))
		{
			
			//画一个红的框
			/*hPen = CreatePen(PS_SOLID,3,RGB(255,0,0));
			SelectObject (hdc,hPen);
			Rectangle(hdc,rect.right/5,rect.bottom*1/5,rect.right*4/5,rect.bottom*4/5);*/

			//用黑色画矩形rect的左边线和上边线
			SelectObject (hdc, GetStockObject (BLACK_PEN));
			MoveToEx (hdc, 0, rect.bottom-1, NULL);
			LineTo (hdc, 0, 0);
			LineTo (hdc, rect.right-1, 0);
			//画叉叉
			/*MoveToEx(hdc, 1,1, NULL);
			LineTo(hdc, rect.right-1, rect.bottom-1);
			MoveToEx(hdc, 1, rect.bottom-1, NULL);
			LineTo(hdc, rect.right-1, 1);*/

			//用白色画矩形rect的右边线和边线
			SelectObject (hdc, GetStockObject (WHITE_PEN));
			MoveToEx (hdc, rect.right-1, 0, NULL);
			LineTo (hdc, rect.right-1, rect.bottom-1);
			LineTo (hdc, 0, rect.bottom-1);
			

			//
			SelectObject (hdc, GetStockObject (BLACK_PEN));
			wsprintf((LPSTR)buf,"ID%d",GetWindowLong (hWnd, GWL_ID));
			//DrawText (hdc, (char*)buf,
			//	      -1, &rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);//显示ID号

		}
		
		EndPaint (hWnd, &ps);
        return 0;
               
	case WM_DESTROY: 
		PostQuitMessage (0);
		return 0;
	}

	return DefWindowProc (hWnd, message, wParam, lParam);

} //函数 ChildWinProc 结束

