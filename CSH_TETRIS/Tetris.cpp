#include <Windows.h>
#include <stdio.h> 
#include "resource.h"
#define _T(quote) __TEXT(quote)

//////�⺻���۹�///////
/*	�¿����Ű : �̵�
	�Ʒ�����Ű : ��� �������������ϱ�
	�����̽��� : ��� �߳�����
	������Ű : ���ȸ��
	����Ű : Ȧ�� */
/////////////////////////




#define WM_NewBlock WM_USER +1
#define WM_RenewalScore WM_USER +2
#define YES 1
#define NO 0
#define SUCCESS 1
#define FAIL 0
#define ON 1
#define OFF 0
#define ALIVE 1
#define DEAD 0

//��ü ����Ǹ��
int Block[7][4][4][4] = {
						 //������
						 {{ 0, 1, 0, 0,
							0, 1, 0, 0,
							0, 1, 0, 0,
							0, 1, 0, 0 },

						  { 0, 0, 0, 0,
							1, 1, 1, 1,
							0, 0, 0, 0,
							0, 0, 0, 0 },

						  { 0, 1, 0, 0,
							0, 1, 0, 0,
							0, 1, 0, 0,
							0, 1, 0, 0 },

						  { 0, 0, 0, 0,
							1, 1, 1, 1,
							0, 0, 0, 0,
							0, 0, 0, 0 }},
						 //����
						 {{ 0, 0, 1, 0,
							0, 0, 1, 0,
							0, 1, 1, 0,
							0, 0, 0, 0 },

						  { 1, 1, 1, 0,
							0, 0, 1, 0,
							0, 0, 0, 0,
							0, 0, 0, 0 },

						  { 1, 1, 0, 0,
							1, 0, 0, 0,
							1, 0, 0, 0,
							0, 0, 0, 0 },

						  { 0, 0, 0, 0,
							1, 0, 0, 0,
							1, 1, 1, 0,
							0, 0, 0, 0 }},
						  //L��
						 {{ 1, 0, 0, 0,
							1, 0, 0, 0,
							1, 1, 0, 0,
							0, 0, 0, 0 },

						  { 0, 0, 0, 0,
							0, 0, 1, 0,
							1, 1, 1, 0,
							0, 0, 0, 0 },

						  { 0, 1, 1, 0,
							0, 0, 1, 0,
							0, 0, 1, 0,
							0, 0, 0, 0 },

						  { 1, 1, 1, 0,
							1, 0, 0, 0,
							0, 0, 0, 0,
							0, 0, 0, 0 }},
						 //����
						 {{ 0, 0, 0, 0,
						    0, 1, 0, 0,
						    1, 1, 1, 0,
						    0, 0, 0, 0 },

						  { 0, 0, 1, 0,
						    0, 1, 1, 0,
						    0, 0, 1, 0,
						    0, 0, 0, 0 },

					      { 1, 1, 1, 0,
						    0, 1, 0, 0,
						    0, 0, 0, 0,
						    0, 0, 0, 0 },

   					      { 1, 0, 0, 0,
						    1, 1, 0, 0,
						    1, 0, 0, 0,
						    0, 0, 0, 0 }},

						//����1
						 {{ 1, 0, 0, 0,
							1, 1, 0, 0,
							0, 1, 0, 0,
							0, 0, 0, 0 },

						  { 0, 1, 1, 0,
							1, 1, 0, 0,
							0, 0, 0, 0,
							0, 0, 0, 0 },

						  { 1, 0, 0, 0,
							1, 1, 0, 0,
							0, 1, 0, 0,
							0, 0, 0, 0 },

						  { 0, 1, 1, 0,
							1, 1, 0, 0,
							0, 0, 0, 0,
							0, 0, 0, 0 }},

						//����2
						 {{ 0, 1, 0, 0,
							1, 1, 0, 0,
							1, 0, 0, 0,
							0, 0, 0, 0 },

						  { 1, 1, 0, 0,
							0, 1, 1, 0,
							0, 0, 0, 0,
							0, 0, 0, 0 },

						  { 0, 1, 0, 0,
							1, 1, 0, 0,
							1, 0, 0, 0,
							0, 0, 0, 0 },

						  { 1, 1, 0, 0,
							0, 1, 1, 0,
							0, 0, 0, 0,
							0, 0, 0, 0 }},

						//����
						 {{ 1, 1, 0, 0,
							1, 1, 0, 0,
							0, 0, 0, 0,
							0, 0, 0, 0 },

						  { 1, 1, 0, 0,
							1, 1, 0, 0,
							0, 0, 0, 0,
							0, 0, 0, 0 },

						  { 1, 1, 0, 0,
							1, 1, 0, 0,
							0, 0, 0, 0,
							0, 0, 0, 0 },

						  { 1, 1, 0, 0,
							1, 1, 0, 0,
							0, 0, 0, 0,
							0, 0, 0, 0 }}};


//���
int Background[21][12];

//Ÿ��
BOOL bTime = OFF;

//Ȧ�忩��
BOOL isHolding = FALSE;

//ȸ��
int Rotate;

//�����ǥ
int NowX;
int NowY;


int color;

//��Ʈ��ǥ
int GhostX;
int GhostY;

//�������
int Shape;

//���� ��
int NextShape;

int FullLineNum;

int PlayerState;

HWND hWnd;



//���
void InitBackGround(void);
void DrawBackGround(void);

//��ϱ׸���
void DrawBlock();
void EraseBlock(void);
void DrawNextBlock(void);

//��Ʈ
void DrawGhost();
void EraseGhost(void);

//�̵����ɿ���Ȯ��
BOOL BlockCanMove(int x, int y);

//�����󺯰�
void SetColor(int color, HPEN &hPen, HBRUSH &hBrush);

//�̵�
void LeftMove(void);

void RightMove(void);

void Rotation(void);

BOOL DownMove(void);
BOOL GhostDownMove(void);

void UpdateBackGround(void);

void CheckFullLine(void);

void EraseFullLine(int);

//����ǥ��
void ShowScore(int);
//���Ȧ��
void Hold();
void DrawHoldBlcok();
BOOL BlockCanHoldDraw(int,int,int);
int holdShape;
int holdColor;

void GroundUp();
void AddGround();

void GameOver();

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

HINSTANCE g_hInst;
HBITMAP hBmpAir, hBmpBack;

//���α׷��� ������
int WINAPI WinMain(HINSTANCE hInstance,
	HINSTANCE PreInstance,
	LPSTR lpCmdLIne,
	int nCmdShow)
{

	// �޽��� ����ü�� �����Ѵ�.
	MSG msg;

	// �������� ĸ���� �����Ѵ�.
	TCHAR szTitle[] = L"��Ʈ����";
	// �������� Ŭ������ �����Ѵ�.
	TCHAR szClass[] = L"Class";

	HICON hIcon1;
	HICON hIcon2;

	// �⺻ ������ ����
	hIcon1 = LoadIcon(NULL, IDI_QUESTION);
	// ����� ���� ������ ���� 
	hIcon2 = LoadIcon(hInstance, IDI_WINLOGO);
	//CALLBACK�Լ� = �̺�Ʈó����

	//����ü ���� â�� �ϳ��� ������Ŭ������ ������� ����
	WNDCLASSEX WndEx;

	//����ü ũ�� ����
	WndEx.cbSize = sizeof(WndEx);

	//�����콺Ÿ��
	WndEx.style = NULL;

	// �޽����� ó���� �Լ��� �����Ѵ�. �� �޽����� �߻��ϸ� �� �޽����� WndProc �Լ����� ó���Ѵ�.
	WndEx.lpfnWndProc = WndProc;

	//�߰� Ŭ���� ���� ���⶧���� NULL
	WndEx.cbClsExtra = 0;

	//�߰� ������ ���� ���⶧���� NULL
	WndEx.cbWndExtra = 0;

	//�ν��Ͻ��ڵ�
	WndEx.hInstance = hInstance;

	//�������Ͽ� ���� ������ ����
	WndEx.hIcon = LoadIcon(NULL, L"IDI_ICON");
	//WndEx.hIcon = LoadIcon(NULL, MAKEINTRESOURCE(IDI_ICON));

	//������ Ŀ������
	WndEx.hCursor = LoadCursor(NULL, IDC_ARROW);

	//������ ���
	WndEx.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);

	//������ �޴�
	WndEx.lpszMenuName = MAKEINTRESOURCE(IDR_MENU);
	//Ŭ��������
	WndEx.lpszClassName = szClass;

	//�������� ĸ���� ���� ������
	WndEx.hIconSm = hIcon2;
	//WndEx.hIconSm = LoadIcon(hInstance, /*L"IDI_ICON"*/MAKEINTRESOURCE(IDI_ICON));

	//WNDCLASSEX�� ������ ������ �������Ϳ� ����Ѵ�.
	RegisterClassEx(&WndEx);

	hWnd = CreateWindowEx(NULL, // �������� ��Ÿ���� �����Ѵ�.
		szClass,                // �������� Ŭ������ �����Ѵ�.
		szTitle,                // �������� ĸ���� �����Ѵ�.
		WS_OVERLAPPEDWINDOW,    // �������� ��Ÿ���� �����Ѵ�.
		CW_USEDEFAULT,          // �������� x��ǥ ��ġ�� �����Ѵ�. CW_USEDEFAULT ������ �����Ͽ����Ƿ� ��ǻ�Ͱ� �˾Ƽ� �����Ѵ�.
		CW_USEDEFAULT,          // �������� y��ǥ ��ġ�� �����Ѵ�. CW_USEDEFAULT ������ �����Ͽ����Ƿ� ��ǻ�Ͱ� �˾Ƽ� �����Ѵ�.
		1000,                    // �������� ���̸� 320���� �����Ͽ���.
		720,                    // �������� ���̸� 240���� �����Ͽ���.
		NULL,                   // �����츦 �����ϰ� �ִ� �ٸ� �����찡 �����Ƿ� NULL ������ �����Ͽ���.
		NULL,                   // �޴��� �����Ƿ� NULL ������ �����Ͽ���.
		hInstance,              // �ν��Ͻ� �ڵ��� �����Ѵ�.
		NULL);					// �� ������ �ʴ´�.

	// �����찡 ������ ������ ���¸� �����Ѵ�.
	ShowWindow(hWnd, nCmdShow);
	// �����츦 �����ϰ� WM_PAINT �޽����� ȣ���Ѵ�.
	UpdateWindow(hWnd);


	//�޽��� ó�������� �ݺ���
	while (TRUE)
	{
		//�޽��� ť�� ���� �޽��� Ȯ��
		if (PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE))
		{
			//������ msg����  �޽��� �о��
			if (!GetMessage(&msg, NULL, 0, 0))
				break;
			// ����Ű�� �߻��ϸ� �� �޽����� �޾ƿͼ� WM_CHAR�� �ش��ϴ� �ڵ带 
			//���� ���α׷��� �޽��� ť�� �־� �д�.
			TranslateMessage(&msg);
			// �� �޽������� ó���ϱ� ���� WndProc() �Լ��� ������.
			DispatchMessage(&msg);
		}
	}
	//��Ÿ �μ��� �޽��� ��ȯ
	return msg.wParam;

}

LRESULT CALLBACK WndProc(HWND hWnd,
	UINT uMsg,
	WPARAM wParam,
	LPARAM lParam)
{
	srand(GetTickCount());

	//WPRAM,LPARAM���� �ΰ������� ���� EX) ���콺Ŭ�� -> Ŭ���� ��ǥ�������
	//uMsg �������� DistpatchMessage �Լ����� ���� �޽����� ����
	switch (uMsg)
	{
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case FILE_START:
			if (PlayerState == DEAD)
			{
				isHolding = FALSE;
				//���׸�
				InitBackGround();
				DrawBackGround();
				DrawHoldBlcok();
				//���ھ�ǥ��
				ShowScore(FullLineNum);



				PlayerState = ALIVE;

				//������� ����
				NextShape = rand() % 7;

				FullLineNum = 0;

				SendMessage(hWnd, WM_NewBlock, 0, 0);
			}
			if (bTime == ON)
			{
				KillTimer(hWnd, 3);
				KillTimer(hWnd, 4);
				bTime = OFF;
			}
			else
			{
				SetTimer(hWnd, 3, 1000, NULL);
				SetTimer(hWnd, 4, 5000, NULL);//5�ʸ��� �ٴ��̿ö������
				bTime = ON;
			}
			break;
		case FILE_EXIT:
			DestroyWindow(hWnd);
			break;
		}
		return FALSE;
	case WM_NewBlock:
		NowX = 3;

		NowY = 0;

		Rotate = 0;

		Shape = NextShape;
		color = rand() % 7;
		NextShape = rand() % 7;


		if (BlockCanMove(NowX, NowY))
		{	//�����
			DrawBlock();

			//������ ���� ���;
			DrawNextBlock();
		}
		//������� ���ü�����, ����� �Ա����� ����
		else if (!BlockCanMove(NowX, NowY))
		{
			EraseGhost();
			PlayerState = DEAD;
		}
		return FALSE;

	case WM_RenewalScore:
		ShowScore(FullLineNum);
		return FALSE;
	case WM_KEYDOWN:
		switch (LOWORD(wParam))
		{
		case VK_LEFT:
			LeftMove();
			break;
		case VK_RIGHT:
			RightMove();
			break;
		case VK_UP:
			Rotation();
			break;
		case VK_DOWN:
			DownMove();
			break;
		case VK_SPACE:
			while (DownMove());
			break;
		case VK_RETURN:
			Hold();
			break;
		}
		return FALSE;

	case WM_TIMER:
		if (PlayerState == ALIVE)
		{
			if (wParam == 3)
			{
				DownMove();
			}
			if (wParam == 4)
			{
				GroundUp();
			}
		}
			
		else
		{
			if (bTime == ON)
			{
				bTime = OFF;
				KillTimer(hWnd, 3);
				KillTimer(hWnd, 4);
			}
		}
		return FALSE;

	case WM_DESTROY:
		if (bTime == ON)
		{
			KillTimer(hWnd, 3);
			KillTimer(hWnd, 4);
		}
		PostQuitMessage(0);//������ ����
		return FALSE;
	}
	//��ó ó������ ���� �޽����� WndProc �Լ��� ������ Ȯ���� ó��
	return DefWindowProc(hWnd, uMsg, wParam, lParam);

}

void InitBackGround()
{
	InvalidateRect(hWnd, NULL, TRUE);
	UpdateWindow(hWnd);
	//��� 0 �ʱ�ȭ
	for (int row = 0; row < 21; row++)
		for (int col = 0; col < 12; col++)
		{
			Background[row][col] = 0;
		}

	for (int row = 0; row < 21; row++)
	{
		for (int col = 0; col < 12; col++)
		{
			if (row == 20)//��� ����
			{
				Background[row][col] = 1;
			}

			else if (col == 0)//��� ������
			{
				Background[row][col] = 1;
			}

			else if (col == 11)//��� ��������
			{
				Background[row][col] = 1;
			}
			else
				Background[row][col] = 0;
		}
	}
	DrawBackGround();
}
void DrawBackGround()
{
	HDC hDC = GetDC(hWnd);

	HPEN hPen, hOldPen;

	HBRUSH hBrush, hOldBrush;

	//hPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
	//hBrush = CreateSolidBrush(RGB(255, 255, 255));

	//hOldPen = (HPEN)SelectObject(hDC, hPen);
	//hOldBrush = (HBRUSH)SelectObject(hDC, hBrush);

	int x, y;

	for (int row = 0; row < 21; ++row)
	{
		for (int col = 0; col < 12; ++col)
		{
			if (Background[row][col] == 1)
			{
				hPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
				hBrush = CreateSolidBrush(RGB(100, 100, 100));
				hOldPen = (HPEN)SelectObject(hDC, hPen);
				hOldBrush = (HBRUSH)SelectObject(hDC, hBrush);

				x = 100 + col * 30; //x������ 100��ŭ���������
				y = row * 30;
				Rectangle(hDC, x, y, x + 30, y + 30);
				SelectObject(hDC, hOldPen);
				SelectObject(hDC, hOldBrush);

				DeleteObject(hPen);
				DeleteObject(hBrush);
			}
			else
			{
				hPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
				hBrush = CreateSolidBrush(RGB(0, 0, 0));
				hOldPen = (HPEN)SelectObject(hDC, hPen);
				hOldBrush = (HBRUSH)SelectObject(hDC, hBrush);
				x = 100 + col * 30; //x������ 100��ŭ���������
				y = row * 30;
				Rectangle(hDC, x, y, x + 30, y + 30);

				SelectObject(hDC, hOldPen);
				SelectObject(hDC, hOldBrush);

				DeleteObject(hPen);
				DeleteObject(hBrush);
			}
		}
	}

	ReleaseDC(hWnd, hDC);
}
void DrawBlock()
{
	HDC hDC = GetDC(hWnd);

	HPEN hPen, hOldPen;

	HBRUSH hBrush, hOldBrush;
	int x, y;

	hPen = CreatePen(PS_SOLID, 1, RGB(255, 255, 255));
	hBrush = CreateSolidBrush(RGB(0, 0, 255));
	

	SetColor(color, hPen, hBrush);

	hOldPen = (HPEN)SelectObject(hDC, hPen);
	hOldBrush = (HBRUSH)SelectObject(hDC, hBrush);


	GhostX = NowX;
	GhostY = NowY;

	while (GhostDownMove());
	// �Ʒ� �� �ݺ����� ����� ���� �˻��Ѵ�.
	for (int row = 0; row < 4; row++) // ��
		for (int col = 0; col < 4; col++) // ��
			// ���� �迭�� ���� 1�̸�...
			if (Block[Shape][Rotate][row][col] == 1)
			{
				// ����� ��ġ�� ���� (�簢��� �ϳ��� ũ�Ⱑ 10�̴� *10 ���ش�)
				x = 130+ NowX*30 + col * 30;
				y = NowY*30 + row * 30;
				// �ش� ��ġ�� �ش� ũ���(10) �簢���� ����Ѵ�.
				Rectangle(hDC, x, y, x + 30, y + 30);
			}

	SelectObject(hDC, hOldPen);
	SelectObject(hDC, hOldBrush);

	DeleteObject(hPen);
	DeleteObject(hBrush);

	ReleaseDC(hWnd, hDC);
}

void EraseBlock()
{

	HDC hDC = GetDC(hWnd);

	HPEN hPen, hOldPen;

	HBRUSH hBrush, hOldBrush;

	hPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
	hBrush = CreateSolidBrush(RGB(0, 0, 0));


	hOldPen = (HPEN)SelectObject(hDC, hPen);
	hOldBrush = (HBRUSH)SelectObject(hDC, hBrush);
	int x, y;

	for (int row = 0; row < 4; row++) // ��
		for (int col = 0; col < 4; col++) // ��
			// ���� �迭�� ���� 1�̸�...
			if (Block[Shape][Rotate][row][col] == 1)
			{
				// ����� ��ġ�� ���� (�簢��� �ϳ��� ũ�Ⱑ 10�̴� *10 ���ش�)
				x = 130 + NowX * 30 + col * 30;
				y = NowY * 30 + row * 30;
				// �ش� ��ġ�� �ش� ũ���(10) �簢���� ����Ѵ�.
				Rectangle(hDC, x, y, x + 30, y + 30);
			}
	SelectObject(hDC, hOldPen);
	SelectObject(hDC, hOldBrush);

	DeleteObject(hPen);
	DeleteObject(hBrush);

	ReleaseDC(hWnd, hDC);
}

void DrawNextBlock()
{

	HDC hDC = GetDC(hWnd);

	HPEN hPen, hOldPen;

	HBRUSH hBrush, hOldBrush;

	hPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
	hBrush = CreateSolidBrush(RGB(0, 0, 0));

	hOldPen = (HPEN)SelectObject(hDC, hPen);

	hOldBrush = (HBRUSH)SelectObject(hDC, hBrush);

	Rectangle(hDC, 500, 100, 660, 260);

	SelectObject(hDC, hOldPen);
	SelectObject(hDC, hOldBrush);

	DeleteObject(hPen);
	DeleteObject(hBrush);

	ReleaseDC(hWnd, hDC);


	hPen = CreatePen(PS_SOLID, 1, RGB(255, 255, 255));
	hBrush = CreateSolidBrush(RGB(0, 0, 255));
	hDC = GetDC(hWnd);

	SetColor(color, hPen, hBrush);
	hOldPen = (HPEN)SelectObject(hDC, hPen);

	hOldBrush = (HBRUSH)SelectObject(hDC, hBrush);

	
	int x, y;

	for (int row = 0; row < 4; row++) // ��
		for (int col = 0; col < 4; col++) // ��
			// ���� �迭�� ���� 1�̸�...
			if (Block[Shape][Rotate][row][col] == 1)
			{
				// ����� ��ġ�� ���� (�簢��� �ϳ��� ũ�Ⱑ 10�̴� *10 ���ش�)
				x = 545 + col * 30;
				y = 100 + row * 30;
				// �ش� ��ġ�� �ش� ũ���(10) �簢���� ����Ѵ�.
				Rectangle(hDC, x, y, x + 30, y + 30);
			}
	SelectObject(hDC, hOldPen);
	SelectObject(hDC, hOldBrush);

	DeleteObject(hPen);
	DeleteObject(hBrush);

	ReleaseDC(hWnd, hDC);

	TCHAR szText[100];
	hDC = GetDC(hWnd);
	SetTextColor(hDC, RGB(0, 0, 0));
	swprintf_s(szText, _T("Next Block"));
	TextOut(hDC, 500, 70, szText, lstrlen(szText));
	ReleaseDC(hWnd, hDC);
}

//��Ʈ�׸���
void DrawGhost()
{

	HDC hDC = GetDC(hWnd);

	HPEN hPen, hOldPen;

	HBRUSH hBrush, hOldBrush;

	hPen = CreatePen(PS_SOLID, 1, RGB(255, 255, 255));
	hBrush = CreateSolidBrush(RGB(0, 0, 0));

	hOldPen = (HPEN)SelectObject(hDC, hPen);

	hOldBrush = (HBRUSH)SelectObject(hDC, hBrush);

	int x, y;

	
	for (int row = 0; row < 4; row++) // ��
		for (int col = 0; col < 4; col++) // ��
			// ���� �迭�� ���� 1�̸�...
			if (Block[Shape][Rotate][row][col] == 1)
			{
				// ����� ��ġ�� ���� (�簢��� �ϳ��� ũ�Ⱑ 10�̴� *10 ���ش�)
				x = 130 + NowX * 30 + col * 30;
				y = GhostY * 30 + row * 30;
				// �ش� ��ġ�� �ش� ũ���(10) �簢���� ����Ѵ�.
				Rectangle(hDC, x, y, x + 30, y + 30);
			}
	
	SelectObject(hDC, hOldPen);
	SelectObject(hDC, hOldBrush);

	DeleteObject(hPen);
	DeleteObject(hBrush);

	ReleaseDC(hWnd, hDC);
}

void EraseGhost()
{
	HDC hDC = GetDC(hWnd);

	HPEN hPen, hOldPen;

	HBRUSH hBrush, hOldBrush;

	hPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
	hBrush = CreateSolidBrush(RGB(0, 0, 0));

	hOldPen = (HPEN)SelectObject(hDC, hPen);

	hOldBrush = (HBRUSH)SelectObject(hDC, hBrush);

	int x, y;
	GhostX = NowX;


	for (int row = 0; row < 4; row++) // ��
		for (int col = 0; col < 4; col++) // ��
			// ���� �迭�� ���� 1�̸�...
			if (Block[Shape][Rotate][row][col] == 1)
			{
				if (Background[GhostY + row][NowX + col + 1])//������̸� ����
					continue;
				x = 130 + NowX * 30 + col * 30;
				y = GhostY * 30 + row * 30;
				Rectangle(hDC, x, y, x + 30, y + 30);
			}

	SelectObject(hDC, hOldPen);
	SelectObject(hDC, hOldBrush);

	DeleteObject(hPen);
	DeleteObject(hBrush);

	ReleaseDC(hWnd, hDC);
}
//��� �̵� �����
BOOL BlockCanMove(int x, int y)
{
	int check = 0;

	for (int row = 0; row < 4; row++) // ��
		for (int col = 0; col < 4; col++) // ��
			// ���� �迭�� ���� 1�̸�...
			if (Block[Shape][Rotate][row][col])
			{
				check += Background[y + row][x + col + 1];//����� ����迡 �ɸ���
			}
	return check == 0 ? YES : NO;
}

BOOL BlockCanHoldDraw(int holdShape,int x, int y)//Ȧ������ ����� ����Ϸ��Ҷ� ��濡�ɸ����� �˻�
{
	int check = 0;

	for (int row = 0; row < 4; row++) // ��
		for (int col = 0; col < 4; col++) // ��
			// ���� �迭�� ���� 1�̸�...
			if (Block[holdShape][Rotate][row][col])
			{
				check += Background[y + row][x + col + 1];//����� ����迡 �ɸ���
			}
	return check == 0 ? YES : NO;
}

// ��� ���� �̵�.
void LeftMove()
{
	// �÷��̾ �׾�����
	if (PlayerState == DEAD)
		return;

	// �׷��� �ʴٸ� ��� ���� �̵�
	if (BlockCanMove(NowX - 1, NowY))
	{
		// ����� �����
		EraseBlock();
		EraseGhost();
		// ��� ��ġ �̵� ��Ű��
		NowX--;
		// ����� �ٽ� �׸���.
		DrawBlock();
	}
}
// ��� ���� �̵�.
void RightMove()
{
	// �÷��̾ �׾�����
	if (PlayerState == DEAD)
		return;

	// �׷��� �ʴٸ� ��� ���� �̵�
	if (BlockCanMove(NowX + 1, NowY))
	{
		// ����� �����
		EraseGhost();
		EraseBlock();

		// ��� ��ġ �̵� ��Ű��
		NowX++;
		// ����� �ٽ� �׸���.
		DrawBlock();
	}
}

void Rotation()
{
	// �÷��̾ �׾�����
	if (PlayerState == DEAD)
		return;

	// ���� �� 
	int temp = Rotate;
	Rotate++;
	// ������ �Ѱ� ���� 3������ ���� ����(if �Ƚᵵ �� ��ų�̴� ����صα�)
	Rotate %= 4;

	// ȸ���� ���� �ϸ�
	if (BlockCanMove(NowX, NowY))
	{
		// ����
		Rotate = temp;
		// ����� �����
		EraseBlock();
		EraseGhost();
		// RotateNum �� 1 ����
		Rotate++;
		// ������ �Ѱ� ���� 3������ ���� ����
		Rotate %= 4;
		// ȸ���� ��� �׸���
		DrawBlock();
	}
	// ȸ���� �Ұ��� �ϸ� ����

	else if (!BlockCanMove(NowX + 1, NowY))//�����ʺ��� �������
	{
		// ����
		Rotate = temp;
		// ����� �����
		EraseBlock();
		EraseGhost();
		// ��� ���� ��ĭ �̵�
		// 1���� ���ϰ�� ��ĭ���̵�
		if (Shape == 0)
			NowX--;
		NowX--;
		// RotateNum �� 1 ����
		Rotate++;
		// ������ �Ѱ� ���� 3������ ���� ����(if �Ƚᵵ �� ��ų�̴� ����صα�)
		Rotate %= 4;
		// ȸ���� ��� �׸���
		DrawBlock();
	}

	else if (!BlockCanMove(NowX - 1, NowY))//���ʺ��� �������
	{
		// ����
		Rotate = temp;
		// ����� �����
		EraseBlock();
		EraseGhost();
		// ��� ������ 1ĭ�̵�
		NowX++;
		// RotateNum �� 1 ����
		Rotate++;
		// ������ �Ѱ� ���� 3������ ���� ����(if �Ƚᵵ �� ��ų�̴� ����صα�)
		Rotate %= 4;
		// ȸ���� ��� �׸���
		DrawBlock();
	}

	//else
	//	Rotate = temp;  
}

BOOL DownMove()
{
	// �÷��̾ �׾�����
	if (PlayerState == DEAD) return FAIL;

	// ����� �Ʒ��� ���� ���� �ִٸ�(�̸� üũ)
	if (BlockCanMove(NowX, NowY + 1))
	{
		// ����� �����
		EraseBlock();
		EraseGhost();
		// ��� ��ġ �̵� ��Ű��
		NowY++;
		// ����� �ٽ� �׸���.
		DrawBlock();
		return SUCCESS;
	}
	// ����� �Ʒ��� ���� �� �� ���ٸ�
	else
	{
		// �����ϼ� ���� ����� ������� ������Ʈ.
		UpdateBackGround();
		// ������ �� ���ִ��� �˻�.(�̼� �������� �˻�)
		CheckFullLine();
		// �޽����� �߻� ��Ų��.(���� ��� ����)
		SendMessage(hWnd, WM_NewBlock, 0, 0);
		return FAIL;
	}
}

BOOL GhostDownMove()
{
	// �÷��̾ �׾�����
	if (PlayerState == DEAD) return FAIL;

	// ����� �Ʒ��� ���� ���� �ִٸ�(�̸� üũ)
	if (BlockCanMove(GhostX, GhostY + 1))
	{
		// ����� �����
		EraseGhost();
		// ��� ��ġ �̵� ��Ű��
		GhostY++;
		// ����� �ٽ� �׸���.
		DrawGhost();
		return SUCCESS;
	}
	else
	{
		return FAIL;
	}
}

//���� �ٴڿ� ������ ������� ����
void UpdateBackGround()
{
	int element;
	for (int row = 0; row < 4; row++)
	{
		for (int col = 0; col < 4; col++)
		{
			//���� ����� ��Ұ� ����
			element = Block[Shape][Rotate][row][col];
			if (element)
				Background[NowY + row][NowX + col + 1] = element;
		}
	}
}

void CheckFullLine()
{
	int line,row,col;
	int elementNum;

	for (row = 19; row > 0; row--)
	{
		elementNum = 0;
		for (col = 1;col <= 10;col++)
		{
			elementNum += Background[row][col];
		}
		if (elementNum == 10)
		{
			for (line = row; line > 0; line--)
				for (col = 1;col <= 10;col++)
				{
					Background[line][col] = Background[line - 1][col];
				}

			//for (int col = 1;col <= 10;col++)
			//{
			//	Background[0][col] = 0;
			//}

			//����� ������ ���� ����
			EraseFullLine(row);

			FullLineNum++;
			SendMessage(hWnd, WM_RenewalScore,0,0);
			//2���̻�������� ���
			row++;
		}
	}
}

void EraseFullLine(int row)
{
	// ����̽� ���ؽ�Ʈ�� �����Ѵ�.
	HDC hDC, hMemDC;
	// ��Ʈ���� �ڵ��� �����ϱ� ����.
	HBITMAP hBmp;

	// �Ѹ���� 100
	int Xlen = 300;//209 - 110 + 1;

	/* ������ ������ Ylen�� ���� ������ ������ ���� �ٷ� ������
	�� �����̴�.
	row�� 0���� �����ϹǷ� row*10�� full line�� �ٷ� �������� ����
	�̴�.
	��! full line�� 10��° ���̶�� �� ������ y ������
	90~99�̴�. �̶� row=9�̰� ������ �κ��� y������ 0~89���� �̴�.*/

	// �Ѹ���� ù ���κ��� ���� ���� ������ �����̴�.
	int Ylen = row * 30;

	// ������ Ŭ���̾�Ʈ ������ ���÷��� ����̽� ���ؽ�Ʈ(DC) �ڵ��� ���ؼ� ��ȯ�Ѵ�.
	hDC = GetDC(hWnd);
	// �־��� ����̽��� ȣȯ�Ǵ� �޸� ����̽� ���ؽ�Ʈ�� �����Ѵ�.
	hMemDC = CreateCompatibleDC(hDC);
	// ��Ʈ���� �����Ѵ�. 
	hBmp = CreateCompatibleBitmap(hDC, 300, 600); // ����� ũ��� ��´�.
	// ��Ʈ���� �޸� ����̽� ���ؽ�Ʈ�� �ִ´�.
	SelectObject(hMemDC, hBmp);

	/*
	 �Լ� ����
	BOOL BitBlt(
	HDC hdcDest,
	int nXDest,
	int nYDest,
	int nWidth,
	int nHeight,
	HDC hdcSrc,
	int nXSrc,
	int nYSrc,
	DWORD dwRop);

	�μ�
	hdcDest
	�̹����� ����� ��ġ�� �ڵ�.

	nXDest, nYDest
	�̹����� ����� ��ġ�� x, y ��ǥ.

	nWidth, nHeight
	���� �̹����� �ʺ�, ���� �̴�.
	�� ũ�⸸ŭ ���� �̹������� �߶�� �׸���.

	hdcSrc
	�̹����� �ڵ�.

	nXSrc, nYSrc
	������ �̹����� ���������� x, y��ǥ�̴�.
	�� ��ġ���� nWidth, nHeight��ŭ �̹����� �߶�´�.

	dwRop
	�̹����� ��� ���

	*/

	// ȭ���� �Ϻθ� �޸𸮷� �����Ѵ�.
	BitBlt(hMemDC, 0, 0, Xlen, Ylen, hDC, 130, 0, SRCCOPY);

	// �޸𸮿��� ȭ���� �ٸ� �κ����� �����Ѵ�.0
	// ��! �ι�° �ٺ��� �����Ѵ�.
	BitBlt(hDC, 130, 30, Xlen, Ylen, hMemDC, 0, 0, SRCCOPY);

	// (�޸�)����̽� ���ؽ�Ʈ(DC)�� ���ش�
	DeleteDC(hMemDC);
	// ����̽� ���ؽ�Ʈ�� �ݳ��Ѵ�.
	ReleaseDC(hWnd, hDC);
	// ��ü�� �����Ѵ�.
	DeleteObject(hBmp);
}

void ShowScore(int line)
{
	HDC hDC;
	RECT rec;
	rec.right = 600;
	rec.left = 500;
	rec.top = 0;
	rec.bottom = 20;

	TCHAR szText[100];
	InvalidateRect(hWnd, &rec, TRUE);
	UpdateWindow(hWnd);

	hDC = GetDC(hWnd);
	SetTextColor(hDC, RGB(0, 0, 0));
	swprintf_s(szText, _T("Total Score : %d"), FullLineNum*100);
	TextOut(hDC, 500, 20, szText, lstrlen(szText));
	ReleaseDC(hWnd, hDC);
}

void SetColor(int color ,HPEN& hPen, HBRUSH &hBrush)
{
	switch (color)
	{
	//����
	case 0:
		hPen = CreatePen(PS_SOLID, 1, RGB(255, 255, 255));
		hBrush = CreateSolidBrush(RGB(255, 0, 0));
		break;
	//��Ȳ
	case 1:
		hPen = CreatePen(PS_SOLID, 1, RGB(255, 255, 255));
		hBrush = CreateSolidBrush(RGB(255, 130, 0));
		break;
	//���
	case 2:
		hPen = CreatePen(PS_SOLID, 1, RGB(255, 255, 255));
		hBrush = CreateSolidBrush(RGB(237, 210, 0));
		break;
	//�ʷ�
	case 3:
		hPen = CreatePen(PS_SOLID, 1, RGB(255, 255, 255));
		hBrush = CreateSolidBrush(RGB(0, 183, 0));
		break;
	//�Ķ�
	case 4:
		hPen = CreatePen(PS_SOLID, 1, RGB(255, 255, 255));
		hBrush = CreateSolidBrush(RGB(0, 0, 255));
		break;
	//����
	case 5:
		hPen = CreatePen(PS_SOLID, 1, RGB(255, 255, 255));
		hBrush = CreateSolidBrush(RGB(5, 0, 153));
		break;
	//����
	case 6:
		hPen = CreatePen(PS_SOLID, 1, RGB(255, 255, 255));
		hBrush = CreateSolidBrush(RGB(131, 36, 255));
		break;
	}
}

void DrawHoldBlcok()
{
	HDC hDC = GetDC(hWnd);

	HPEN hPen, hOldPen;

	HBRUSH hBrush, hOldBrush;
	int x, y;
	hPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
	hBrush = CreateSolidBrush(RGB(0, 0, 0));

	hOldPen = (HPEN)SelectObject(hDC, hPen);

	hOldBrush = (HBRUSH)SelectObject(hDC, hBrush);

	Rectangle(hDC, 500, 300, 660, 460);

	SelectObject(hDC, hOldPen);
	SelectObject(hDC, hOldBrush);

	DeleteObject(hPen);
	DeleteObject(hBrush);

	ReleaseDC(hWnd, hDC);




	if (isHolding)
	{
		hPen = CreatePen(PS_SOLID, 1, RGB(255, 255, 255));
		hBrush = CreateSolidBrush(RGB(0, 0, 255));
		hDC = GetDC(hWnd);

		SetColor(holdColor, hPen, hBrush);
		hOldPen = (HPEN)SelectObject(hDC, hPen);
		hOldBrush = (HBRUSH)SelectObject(hDC, hBrush);

		for (int row = 0; row < 4; row++) // ��
			for (int col = 0; col < 4; col++) // ��
				// ���� �迭�� ���� 1�̸�...
				if (Block[holdShape][0][row][col] == 1)
				{
					// ����� ��ġ�� ���� (�簢��� �ϳ��� ũ�Ⱑ 10�̴� *10 ���ش�)
					x = 500 + col * 30;
					y = 300 + row * 30;
					// �ش� ��ġ�� �ش� ũ���(10) �簢���� ����Ѵ�.
					Rectangle(hDC, x, y, x + 30, y + 30);
				}
	}
	else
	{
		hPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
		hBrush = CreateSolidBrush(RGB(0, 0, 0));
		hDC = GetDC(hWnd);
		hOldPen = (HPEN)SelectObject(hDC, hPen);
		hOldBrush = (HBRUSH)SelectObject(hDC, hBrush);

		for (int row = 0; row < 4; row++) // ��
			for (int col = 0; col < 4; col++) // ��
				// ���� �迭�� ���� 1�̸�...
				if (Block[holdShape][0][row][col] == 1)
				{
					// ����� ��ġ�� ���� (�簢��� �ϳ��� ũ�Ⱑ 10�̴� *10 ���ش�)
					x = 500 + col * 30;
					y = 300 + row * 30;
					// �ش� ��ġ�� �ش� ũ���(10) �簢���� ����Ѵ�.
					Rectangle(hDC, x, y, x + 30, y + 30);
				}
	}
	SelectObject(hDC, hOldPen);
	SelectObject(hDC, hOldBrush);

	DeleteObject(hPen);
	DeleteObject(hBrush);

	ReleaseDC(hWnd, hDC);

	TCHAR szText[100];
	hDC = GetDC(hWnd);
	SetTextColor(hDC, RGB(0, 0, 0));
	swprintf_s(szText, _T("Hold"));
	TextOut(hDC, 500, 275, szText, lstrlen(szText));
	ReleaseDC(hWnd, hDC);
}

void Hold()
{
	int tempShape = holdShape;//���� Ȧ�� ���ִ� ����� ����
	int tempColor = holdColor;//���� Ȧ�� ���ִ� ����� �÷�

	//���� Ȧ������ ����� �������
	if (isHolding)
	{
		if (BlockCanHoldDraw(tempShape, NowX, NowY))//���� Ȧ��Ⱥ���� �׷����� ��濡��ġ���ʴ��� �˻�
		{

			holdShape = Shape;//���� ��������� ����
			holdColor = color;
			EraseBlock();
			EraseGhost();
			DrawHoldBlcok();
			Shape = tempShape;
			color = tempColor;
			Rotate = 0;
			DrawBlock();
		}
	}
	else
	{
		holdShape = Shape;//���� ��������� ����
		holdColor = color;
		EraseBlock();
		EraseGhost();
		isHolding = TRUE;
		DrawHoldBlcok();
		SendMessage(hWnd, WM_NewBlock, 0, 0);
	}
}

void GroundUp()
{
	// ����̽� ���ؽ�Ʈ�� �����Ѵ�.
	HDC hDC, hMemDC;
	// ��Ʈ���� �ڵ��� �����ϱ� ����.
	HBITMAP hBmp;

	// �Ѹ���� 100
	int Xlen = 300;//209 - 110 + 1;

	// �Ѹ���� ù ���κ��� ���� ���� ������ �����̴�.
	int Ylen = 570;//������ �ٴڹٷ�������

	// ������ Ŭ���̾�Ʈ ������ ���÷��� ����̽� ���ؽ�Ʈ(DC) �ڵ��� ���ؼ� ��ȯ�Ѵ�.
	hDC = GetDC(hWnd);
	// �־��� ����̽��� ȣȯ�Ǵ� �޸� ����̽� ���ؽ�Ʈ�� �����Ѵ�.
	hMemDC = CreateCompatibleDC(hDC);
	// ��Ʈ���� �����Ѵ�. 
	hBmp = CreateCompatibleBitmap(hDC, 300, 600); // ����� ũ��� ��´�.
	// ��Ʈ���� �޸� ����̽� ���ؽ�Ʈ�� �ִ´�.
	SelectObject(hMemDC, hBmp);


	EraseBlock();
	EraseGhost();
	// ȭ���� �Ϻθ� �޸𸮷� �����Ѵ�.
	BitBlt(hMemDC, 0, 0, Xlen, Ylen, hDC, 130, 30, SRCCOPY);

	// �޸𸮿��� ȭ���� �ٸ� �κ����� �����Ѵ�.0
	// ��! �ι�° �ٺ��� �����Ѵ�.
	BitBlt(hDC, 130, 0, Xlen, Ylen, hMemDC, 0, 0, SRCCOPY);



	// (�޸�)����̽� ���ؽ�Ʈ(DC)�� ���ش�
	DeleteDC(hMemDC);
	// ����̽� ���ؽ�Ʈ�� �ݳ��Ѵ�.
	ReleaseDC(hWnd, hDC);
	// ��ü�� �����Ѵ�.
	DeleteObject(hBmp);

	AddGround();
	DrawBlock();
}

void AddGround()
{
	int addGroundNum = 0;
	for (int row = 0; row <19;row++)
	{
		for (int col = 1;col < 11;col++)
		{
			Background[row][col] = Background[row+1][col];
		}
	}

	srand(GetTickCount());
	for (int col = 1;col < 11;col++)
	{
		if (addGroundNum == 8)
		{
			break;
		}
		int row = 19;
		
		Background[row][col] = rand() % 2;
		addGroundNum += Background[row][col];
	}

	HDC hDC = GetDC(hWnd);

	HPEN hPen, hOldPen;

	HBRUSH hBrush, hOldBrush;

	int x;
	int y;
	for (int col = 1;col < 11;col++)
	{
		int row = 19;
		if (Background[row][col] == 1)
		{
			hPen = CreatePen(PS_SOLID, 1, RGB(255, 255, 255));
			hBrush = CreateSolidBrush(RGB(100, 100, 100));
			hOldPen = (HPEN)SelectObject(hDC, hPen);
			hOldBrush = (HBRUSH)SelectObject(hDC, hBrush);

			x = 100 + col * 30; //x������ 100��ŭ���������
			y = row * 30;
			Rectangle(hDC, x, y, x + 30, y + 30);
		}
		else
		{
			hPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
			hBrush = CreateSolidBrush(RGB(0, 0, 0));
			hOldPen = (HPEN)SelectObject(hDC, hPen);
			hOldBrush = (HBRUSH)SelectObject(hDC, hBrush);
			x = 100 + col * 30; //x������ 100��ŭ���������
			y = row * 30;
			Rectangle(hDC, x, y, x + 30, y + 30);

		}
	}


	SelectObject(hDC, hOldPen);
	SelectObject(hDC, hOldBrush);

	DeleteObject(hPen);
	DeleteObject(hBrush);

	ReleaseDC(hWnd, hDC);

}
