/*******************************************************************
����Keyboard
�ļ���Keyboard.c
���ܣ�����������ʾ����
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
char string[17]="abcdefghigklmnop";//һ����16���ַ�
int count=0;
char chengji[3]="00";//�ɼ�
int jiemian=1;//�����־λ
char sbuf[20]="";//����

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
		TranslateMessage (&msg);         //ת�����̻�����Ϣ���Ի���ַ���Ϣ
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
		MessageBox (NULL, TEXT ("ע�ᴰ����ʧ�ܣ�"), szAppName,
                    MB_ICONERROR);
		return 0;
	}

	hwnd = CreateWindow (szAppName,
	                    TEXT ("MADE BY jingtiangao��"),
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

//���ں���
LRESULT CALLBACK WinProc (HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	HDC           hdc;
	PAINTSTRUCT  ps;
	RECT          rect;
	char          aChar;             //�ַ���
	int i;
		static TCHAR    szText[] = TEXT ("λͼ");
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
	case WM_CREATE:         //�����ڴ��豸������
		hdc = GetDC (hWnd);
		hdcMem = CreateCompatibleDC (hdc);			
		ReleaseDC (hWnd, hdc);
		return 0;
	case WM_SETFOCUS:
		CreateCaret (hWnd, NULL, 2, 15);	//����8*15��С�Ĳ����
		SetCaretPos (10, 10);               //���ò������λ��Ϊ�ͻ������Ͻ�
		ShowCaret (hWnd);                   //��ʾ�����
		return 0;
	case WM_KILLFOCUS:
		HideCaret (hWnd);                    //���ز����
		DestroyCaret ();                     //���������
		return 0;
	case WM_MOUSEMOVE:
	int x;
	int y;
    x=LOWORD(lParam);
    y=HIWORD(lParam);
	wsprintf(sbuf,"%04d,%04d",x,y);
	hdc = GetDC (hWnd);
	GetClientRect (hWnd, &rect);
	DrawText (hdc,sbuf , -1, &rect,DT_TOP| DT_RIGHT );	//��ʾ�������
	
	ReleaseDC (hWnd, hdc);

	return 0;
//	case WM_SYSKEYDOWN:
//		MessageBeep(MB_ICONHAND);
//		return 0;
	case WM_KEYDOWN:
		switch(wParam)
		{
		case VK_ESCAPE:
			MessageBox(hWnd,TEXT("��Ϸ����������"),TEXT("����"),MB_OK);
			
			jiemian=1;
			InvalidateRect(hWnd, NULL, true);
			break;
		case VK_RETURN:
			if(jiemian==1)
			{MessageBox(hWnd,TEXT("��Ϸ������ʼ"),TEXT("����"),MB_OK);
			jiemian=0;
			InvalidateRect(hWnd, NULL, true);}
			else
			MessageBox(hWnd,TEXT("��Ϸ�Ѿ���ʼ���벻Ҫ�ظ�����"),TEXT("����"),MB_OK);
			
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
						
		if(aChar==string[count])//���Ұ���һ�����ж�һ���ǲ��ǵ�����һ���ַ����������ô�ػ棬�ӷ֣�������ǣ�����
								//������һ��ʱ����RANDOM��һ��
								//ÿ����һ���ַ�������һ���ķ���
		{
				string[count]=' ';
		
				InvalidateRect(NULL,NULL,TRUE);
			
									if(chengji[1]=='9')//ÿ����һ���ַ�������һ��
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
	case WM_PAINT://�����ػ���Ϣ,����س��������ˣ��ͻ���Ϸ��ʼ�����ESC�����˾ͻص���ʼ����
			
		if(jiemian==0&&((chengji[1]!='9')||(chengji[0]!='9')))
		{
				 hdc=BeginPaint(hWnd,&ps);
				 GetClientRect (hWnd, &rect);
				 DrawText (hdc, TEXT("��ӭ����������Ϸ"), -1, &rect, 
							DT_SINGLELINE | DT_CENTER| DT_TOP); //��ʾ��ǰ�ַ�
				 DrawText (hdc, chengji, -1, &rect, 
							DT_SINGLELINE | DT_LEFT| DT_TOP); //���Ͻ���ʾ�ɼ�
				 DrawText (hdc, string, -1, &rect, 	DT_SINGLELINE | DT_CENTER | DT_VCENTER); //��string�ַ�����ʾ������
				 
				 EndPaint(hWnd,&ps);
				 return 0;
		}
		else if(jiemian==1)
		{
			hdc=BeginPaint(hWnd,&ps);
			GetClientRect (hWnd, &rect);
			//������Ϊ MYBITMAP ����֪λͼ
			
			
			hBitmap = LoadBitmap ((HINSTANCE)GetWindowLong (hWnd, GWL_HINSTANCE), TEXT ("MYBITMAP"));
			GetObject (hBitmap, sizeof (BITMAP), &bm);
			nWidthSrc = bm.bmWidth;
			nHeightSrc = bm.bmHeight;
			/*hOldBitmap =(HBITMAP) SelectObject (hdcMem, hBitmap);
				
			BitBlt (hdc, (rect.right - nWidthSrc)/2, (rect.bottom - nHeightSrc)/2,
					nWidthSrc, nHeightSrc, hdcMem, 0, 0, SRCCOPY);
			
			SelectObject (hdcMem, hOldBitmap);  //��ΪbitbLT��ʾ*/
			nWidthDest = rect.right;
			nHeightDest = rect.bottom;

			hOldBitmap = (HBITMAP)SelectObject (hdcMem, hBitmap);
			StretchBlt (hdc, 0, 0, nWidthDest, nHeightDest,
						hdcMem, 0, 0, nWidthSrc, nHeightSrc, SRCCOPY);
			SelectObject (hdcMem, hOldBitmap);
			DrawText (hdc, TEXT("����һ���о���ʽ�Ļ����������������ղ��ܵ���Ϸ��"), -1, &rect, 
							  DT_CENTER| DT_TOP); //��ʾ��ǰ�ַ�
			DrawText (hdc, TEXT("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n���»س�����ʼ��Ϸ\n����ESC����ֹ��Ϸ�����ؿ�ʼ����\n\n\n����Ϸ���Զ�������ȣ�����浵\n\n\n\nע������Ϸ�����ظ��������99�־ͻ���־�ϲ"), -1, &rect, 
							 DT_CENTER ); 
			EndPaint(hWnd,&ps);
			
			return 0;

		}
		else if((chengji[1]='9')&&(chengji[0]='9'))
		{
			hdc=BeginPaint(hWnd,&ps);
			GetClientRect (hWnd, &rect);
			//������Ϊ MYBITMAP ����֪λͼ
			
			
			hBitmap = LoadBitmap ((HINSTANCE)GetWindowLong (hWnd, GWL_HINSTANCE), TEXT ("MYBITMAP1"));
			GetObject (hBitmap, sizeof (BITMAP), &bm);
			nWidthSrc = bm.bmWidth;
			nHeightSrc = bm.bmHeight;
			hOldBitmap =(HBITMAP) SelectObject (hdcMem, hBitmap);
				
			BitBlt (hdc, (rect.right - nWidthSrc)/2, (rect.bottom - nHeightSrc)/2,
					nWidthSrc, nHeightSrc, hdcMem, 0, 0, SRCCOPY);
			
			SelectObject (hdcMem, hOldBitmap);  //��ΪbitbLT��ʾ
			/*nWidthDest = rect.right;
			nHeightDest = rect.bottom;

			hOldBitmap = (HBITMAP)SelectObject (hdcMem, hBitmap);
			StretchBlt (hdc, 0, 0, nWidthDest, nHeightDest,
						hdcMem, 0, 0, nWidthSrc, nHeightSrc, SRCCOPY);
			SelectObject (hdcMem, hOldBitmap);*///��Ϊ������ʾ
			EndPaint(hWnd,&ps);
			
			return 0;
		}


	case WM_DESTROY:
			
		PostQuitMessage (0);
		return 0;
	}			  


	return DefWindowProc (hWnd, message, wParam, lParam);

} //���� WinProc ����

void random(void)
{
	srand((int)time(0));
	for(int j=0;j<16;j++)
	{
		string[j]='a' + rand()%('z'-'a'+1) ;
	}
}