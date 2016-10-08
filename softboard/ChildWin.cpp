/*******************************************************************
����ChildWin
�ļ���ChildWin.c
���ܣ��Ӵ�����ʾ���򡪡����в���
********************************************************************/
#include <windows.h>
#include <windowsx.h>

#define ROW_NUM 4    //����
#define COL_NUM 12    //����

#define WM_CHILDWIN  WM_USER+1    //������֪ͨ�Ӵ��ڵ��Զ�����Ϣ
char soft[48]="1234567890-=qwertyuiop[]\\asdfghjkl;'zxcvbnm,./";//������������
	int suojin=0;//��ʾ����ʱ����������

BOOL InitWindow (HINSTANCE hInstance, int nCmdShow);

//�����ں���ԭ��
LRESULT CALLBACK MainWndProc (HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

//�Ӵ��ں���ԭ��
LRESULT CALLBACK ChildWndProc (HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

TCHAR szAppName[] = TEXT ("ChildWin");            //������������
TCHAR szChildName[] = TEXT ("ChildWin_Child");    //�Ӵ���������

HINSTANCE hInst;                                  //ȫ�̱�������ʵ�����

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
		MessageBox (NULL, TEXT ("ע����������ʧ�ܣ�"), szAppName,
                    MB_ICONERROR);
		return 0;
	}
	
	hInst = hInstance;

	hwnd = CreateWindow (szAppName, 
	                    TEXT ("ģ�������"),
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
    static HWND hChildWnd[COL_NUM][ROW_NUM];  //�Ӵ��ھ��
    static int  nXBox, nYBox;                 //�Ӵ��ڿ�Ⱥ͸߶�
    static WORD nChildWin_ID;                 //�����е��Ӵ��ڱ�ʶ
    static int  nRow, nCol;                   //�����е��Ӵ���λ�ã������кţ�
	int         x, y;
	WNDCLASS    wcChild;                      //�Ӵ�����
	   RECT        rect1;//ר����wm_sizeʹ�õı���
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
			MessageBox (NULL, TEXT ("ע���Ӵ�����ʧ�ܣ�"), szChildName,
				        MB_ICONERROR);
			return 0;
		}

        //�������ơ���ͼ�������л�ͼ�������ĸ������Ӵ���
		for (x=0; x<COL_NUM; x++)
		for (y=0; y<ROW_NUM; y++)
		{
			nChildWin_ID = x<<4|y;             //�Ӵ��ڱ�ʶֵ
			hChildWnd[x][y] = CreateWindow (szChildName, NULL,
											WS_CHILDWINDOW | WS_DLGFRAME |WS_VISIBLE,
											0,0,0,0,
											hWnd,
											(HMENU)(nChildWin_ID),
											//0,
											hInst, NULL);
		}
		
		//��0���Ӵ���Ϊ��ǰ���е��Ӵ���
		nChildWin_ID = 0;
		nRow = 0;
		nCol = 0;
		return 0;

    case WM_SIZE:
        nXBox = (LOWORD (lParam)/2)/COL_NUM;
        nYBox = (HIWORD (lParam)/3)/ROW_NUM;
		
		GetClientRect (hWnd, &rect1);
   		//�����ڴ�С�ı�ʱ������ȷ�����Ӵ����������ڿͻ�����λ��
		for (y=0; y<ROW_NUM; y++)
		{
			suojin=suojin+nXBox/2;
			for (x=0; x<COL_NUM; x++)
			{
				MoveWindow (hChildWnd[x][y], suojin+x*nXBox, (rect1.bottom-ROW_NUM*nYBox)+y*nYBox, nXBox,nYBox, TRUE);//��ƽ�ƹ�ʽ���������ʾ���·�
			}
		}
		return 0;
          
    case WM_COMMAND:                //�Ӵ��ڱ����е�֪ͨ��Ϣ
		//���Ӵ��ڱ�����ʱ���ʹ���Ϣ֪ͨ�����ڣ��Ա���������ȷ���Ƿ�������һ���Ӵ��ڣ�
		//���ǣ�������Ϣ֪ͨ�Ӵ��ں����ı�ǰһ�α������Ӵ��ڵ�״̬��
		if (!(LOWORD (wParam) == nChildWin_ID))
		{
			SendMessage ((HWND)hChildWnd[nCol][nRow], WM_CHILDWIN, 0, 0L);
			
			//��¼�µı����е��Ӵ���
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
		MessageBeep(-1);         //������׼������
		MessageBox (hWnd, TEXT ("������������!"), TEXT ("�����������Ϣ"), MB_OK);
		return 0;
	case WM_PAINT:
		//����������ʾ���е���ĸ
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

} //���� WinProc ����

LRESULT CALLBACK ChildWndProc (HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	HDC         hdc;
    PAINTSTRUCT ps;
    RECT        rect;
	HPEN hPen;
	LONG l=0;
	int a;
	static int xy;
	wchar_t buf[20];//ÿ���Ӵ���Ҫ�������Ϣ
	
	switch (message)
    {
    case WM_CREATE:
		xy ++;
		//�ø��Ӵ������б�־Ϊ0����0���Ӵ�����Ϊ1��
		if (GetWindowLong (hWnd, GWL_ID) == 0)
//		if (GetWindowWord (hWnd, GWL_ID) == 0)		  // 2004.03.11 Liangchenghui
			l=SetWindowLong (hWnd, 0, 1);
		else
			l=SetWindowLong (hWnd, 0, 0);

		return 0;
          
    case WM_LBUTTONDOWN:
		//�µ��Ӵ��ڱ�����
		if (GetWindowLong (hWnd, 0) == 0)
		{
			//�ø��Ӵ������б�־Ϊ1
			SetWindowLong (hWnd, 0, 1);

			//������Ϣ֪ͨ������
			SendMessage (GetParent (hWnd), WM_COMMAND, 
						//(WPARAM) MAKELONG ((WORD)GetWindowWord (hWnd, GWL_ID), (WORD)0),
						GetWindowLong (hWnd, GWL_ID),
						(LPARAM) hWnd);

			//�ػ��Ӵ��ڿͻ���
			GetClientRect (hWnd, &rect);
			InvalidateRect (hWnd, &rect, TRUE);
			UnderstandCallStack(rect.right);
		}
		return 0;

    case WM_CHILDWIN:          //�����ڷ��͵�֪ͨ��Ϣ���ı�ԭ�����Ӵ��ڵ�״̬
		//���Ӵ������б�־Ϊ0
		SetWindowLong (hWnd, 0, 0);

		//�ָ��Ӵ��ڳ�ʼ��ʾ��ʽ
		GetClientRect (hWnd, &rect);
		InvalidateRect (hWnd, &rect,TRUE);

		return 0;

    case WM_PAINT:
        hdc = BeginPaint (hWnd, &ps);
		GetClientRect (hWnd, &rect);
        //��ʾ�����е�����
		 a=((GetWindowLong (hWnd, GWL_ID)&(0x0f))*COL_NUM)+((GetWindowLong (hWnd, GWL_ID)&(0xf0))>>4);
		 SetBkMode(hdc,TRANSPARENT);
		DrawText (hdc, &soft[a],
			     1, &rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);

		

		//������Ʊ����е��Ӵ���
		if (GetWindowLong (hWnd, 0))
		{
			
			//��һ����Ŀ�
			/*hPen = CreatePen(PS_SOLID,3,RGB(255,0,0));
			SelectObject (hdc,hPen);
			Rectangle(hdc,rect.right/5,rect.bottom*1/5,rect.right*4/5,rect.bottom*4/5);*/

			//�ú�ɫ������rect������ߺ��ϱ���
			SelectObject (hdc, GetStockObject (BLACK_PEN));
			MoveToEx (hdc, 0, rect.bottom-1, NULL);
			LineTo (hdc, 0, 0);
			LineTo (hdc, rect.right-1, 0);
			//�����
			/*MoveToEx(hdc, 1,1, NULL);
			LineTo(hdc, rect.right-1, rect.bottom-1);
			MoveToEx(hdc, 1, rect.bottom-1, NULL);
			LineTo(hdc, rect.right-1, 1);*/

			//�ð�ɫ������rect���ұ��ߺͱ���
			SelectObject (hdc, GetStockObject (WHITE_PEN));
			MoveToEx (hdc, rect.right-1, 0, NULL);
			LineTo (hdc, rect.right-1, rect.bottom-1);
			LineTo (hdc, 0, rect.bottom-1);
			

			//
			SelectObject (hdc, GetStockObject (BLACK_PEN));
			wsprintf((LPSTR)buf,"ID%d",GetWindowLong (hWnd, GWL_ID));
			//DrawText (hdc, (char*)buf,
			//	      -1, &rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);//��ʾID��

		}
		
		EndPaint (hWnd, &ps);
        return 0;
               
	case WM_DESTROY: 
		PostQuitMessage (0);
		return 0;
	}

	return DefWindowProc (hWnd, message, wParam, lParam);

} //���� ChildWinProc ����

