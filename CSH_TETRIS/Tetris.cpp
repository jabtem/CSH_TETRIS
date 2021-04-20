#include <Windows.h>
#include <stdio.h> 
#include "resource.h"
#define _T(quote) __TEXT(quote)

//////기본조작법///////
/*	좌우방향키 : 이동
	아래방향키 : 블록 빨리내려오게하기
	스페이스바 : 블록 쭉내리기
	위방향키 : 블록회전
	엔터키 : 홀드 */
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

//전체 블록의모양
int Block[7][4][4][4] = {
						 //일자형
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
						 //ㄱ자
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
						  //L자
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
						 //ㅗ자
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

						//ㄹ자1
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

						//ㄹ자2
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

						//ㅁ자
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


//배경
int Background[21][12];

//타임
BOOL bTime = OFF;

//홀드여부
BOOL isHolding = FALSE;

//회전
int Rotate;

//블록좌표
int NowX;
int NowY;


int color;

//고스트좌표
int GhostX;
int GhostY;

//블록종류
int Shape;

//다음 블럭
int NextShape;

int FullLineNum;

int PlayerState;

HWND hWnd;



//배경
void InitBackGround(void);
void DrawBackGround(void);

//블록그리기
void DrawBlock();
void EraseBlock(void);
void DrawNextBlock(void);

//고스트
void DrawGhost();
void EraseGhost(void);

//이동가능여부확인
BOOL BlockCanMove(int x, int y);

//블럭색상변경
void SetColor(int color, HPEN &hPen, HBRUSH &hBrush);

//이동
void LeftMove(void);

void RightMove(void);

void Rotation(void);

BOOL DownMove(void);
BOOL GhostDownMove(void);

void UpdateBackGround(void);

void CheckFullLine(void);

void EraseFullLine(int);

//점수표현
void ShowScore(int);
//블록홀드
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

//프로그램의 시작점
int WINAPI WinMain(HINSTANCE hInstance,
	HINSTANCE PreInstance,
	LPSTR lpCmdLIne,
	int nCmdShow)
{

	// 메시지 구조체를 선언한다.
	MSG msg;

	// 윈도우의 캡션을 지정한다.
	TCHAR szTitle[] = L"테트리스";
	// 윈도우의 클래스를 지정한다.
	TCHAR szClass[] = L"Class";

	HICON hIcon1;
	HICON hIcon2;

	// 기본 아이콘 생성
	hIcon1 = LoadIcon(NULL, IDI_QUESTION);
	// 사용자 정의 아이콘 생성 
	hIcon2 = LoadIcon(hInstance, IDI_WINLOGO);
	//CALLBACK함수 = 이벤트처리기

	//구조체 선언 창은 하나의 윈도우클래스를 기반으로 생성
	WNDCLASSEX WndEx;

	//구조체 크기 지정
	WndEx.cbSize = sizeof(WndEx);

	//윈도우스타일
	WndEx.style = NULL;

	// 메시지를 처리할 함수를 지정한다. 즉 메시지가 발생하면 그 메시지를 WndProc 함수에서 처리한다.
	WndEx.lpfnWndProc = WndProc;

	//추가 클래스 지정 없기때문에 NULL
	WndEx.cbClsExtra = 0;

	//추가 윈도우 지정 없기때문에 NULL
	WndEx.cbWndExtra = 0;

	//인스턴스핸들
	WndEx.hInstance = hInstance;

	//실행파일에 쓰일 아이콘 지정
	WndEx.hIcon = LoadIcon(NULL, L"IDI_ICON");
	//WndEx.hIcon = LoadIcon(NULL, MAKEINTRESOURCE(IDI_ICON));

	//윈도우 커서지정
	WndEx.hCursor = LoadCursor(NULL, IDC_ARROW);

	//윈도우 배경
	WndEx.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);

	//윈도우 메뉴
	WndEx.lpszMenuName = MAKEINTRESOURCE(IDR_MENU);
	//클래스지정
	WndEx.lpszClassName = szClass;

	//윈도우의 캡션이 쓰일 아이콘
	WndEx.hIconSm = hIcon2;
	//WndEx.hIconSm = LoadIcon(hInstance, /*L"IDI_ICON"*/MAKEINTRESOURCE(IDI_ICON));

	//WNDCLASSEX에 지정된 값들을 레지스터에 등록한다.
	RegisterClassEx(&WndEx);

	hWnd = CreateWindowEx(NULL, // 윈도우의 스타일을 지정한다.
		szClass,                // 윈도우의 클래스를 지정한다.
		szTitle,                // 윈도우의 캡션을 지정한다.
		WS_OVERLAPPEDWINDOW,    // 윈도우의 스타일을 지정한다.
		CW_USEDEFAULT,          // 윈도우의 x좌표 위치를 지정한다. CW_USEDEFAULT 값으로 지정하였으므로 컴퓨터가 알아서 지정한다.
		CW_USEDEFAULT,          // 윈도우의 y좌표 위치를 지정한다. CW_USEDEFAULT 값으로 지정하였으므로 컴퓨터가 알아서 지정한다.
		1000,                    // 윈도우의 넓이를 320으로 지정하였다.
		720,                    // 윈도우의 높이를 240으로 지정하였다.
		NULL,                   // 윈도우를 포함하고 있는 다른 윈도우가 없으므로 NULL 값으로 지정하였다.
		NULL,                   // 메뉴가 없으므로 NULL 값으로 지정하였다.
		hInstance,              // 인스턴스 핸들을 지정한다.
		NULL);					// 잘 쓰이지 않는다.

	// 윈도우가 실제로 보여질 형태를 지정한다.
	ShowWindow(hWnd, nCmdShow);
	// 윈도우를 갱신하고 WM_PAINT 메시지를 호출한다.
	UpdateWindow(hWnd);


	//메시지 처리를위한 반복문
	while (TRUE)
	{
		//메시지 큐에 들어온 메시지 확인
		if (PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE))
		{
			//있으면 msg에서  메시지 읽어옴
			if (!GetMessage(&msg, NULL, 0, 0))
				break;
			// 가상키가 발생하면 그 메시지를 받아와서 WM_CHAR에 해당하는 코드를 
			//응용 프로그램의 메시지 큐에 넣어 둔다.
			TranslateMessage(&msg);
			// 그 메시지들을 처리하기 위해 WndProc() 함수로 보낸다.
			DispatchMessage(&msg);
		}
	}
	//기타 부수적 메시지 반환
	return msg.wParam;

}

LRESULT CALLBACK WndProc(HWND hWnd,
	UINT uMsg,
	WPARAM wParam,
	LPARAM lParam)
{
	srand(GetTickCount());

	//WPRAM,LPARAM에는 부가정보가 들어옴 EX) 마우스클릭 -> 클릭한 좌표가저장됨
	//uMsg 변수에는 DistpatchMessage 함수에서 보낸 메시지가 저장
	switch (uMsg)
	{
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case FILE_START:
			if (PlayerState == DEAD)
			{
				isHolding = FALSE;
				//배경그림
				InitBackGround();
				DrawBackGround();
				DrawHoldBlcok();
				//스코어표기
				ShowScore(FullLineNum);



				PlayerState = ALIVE;

				//다음블록 세팅
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
				SetTimer(hWnd, 4, 5000, NULL);//5초마다 바닥이올라오게함
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
		{	//새블록
			DrawBlock();

			//다음에 나올 블록;
			DrawNextBlock();
		}
		//새블록이 나올수없음, 블록이 입구까지 꽉참
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
		PostQuitMessage(0);//윈도우 종료
		return FALSE;
	}
	//미처 처리하지 못한 메시지를 WndProc 함수로 보내어 확실히 처리
	return DefWindowProc(hWnd, uMsg, wParam, lParam);

}

void InitBackGround()
{
	InvalidateRect(hWnd, NULL, TRUE);
	UpdateWindow(hWnd);
	//배경 0 초기화
	for (int row = 0; row < 21; row++)
		for (int col = 0; col < 12; col++)
		{
			Background[row][col] = 0;
		}

	for (int row = 0; row < 21; row++)
	{
		for (int col = 0; col < 12; col++)
		{
			if (row == 20)//배경 밑줄
			{
				Background[row][col] = 1;
			}

			else if (col == 0)//배경 왼쪽줄
			{
				Background[row][col] = 1;
			}

			else if (col == 11)//배경 오른쪽줄
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

				x = 100 + col * 30; //x축으로 100만큼띄워서생성
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
				x = 100 + col * 30; //x축으로 100만큼띄워서생성
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
	// 아래 두 반복문은 블록의 값을 검사한다.
	for (int row = 0; row < 4; row++) // 열
		for (int col = 0; col < 4; col++) // 행
			// 만약 배열의 값이 1이면...
			if (Block[Shape][Rotate][row][col] == 1)
			{
				// 블록의 위치를 셋팅 (사각블록 하나의 크기가 10이니 *10 해준다)
				x = 130+ NowX*30 + col * 30;
				y = NowY*30 + row * 30;
				// 해당 위치에 해당 크기로(10) 사각형을 출력한다.
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

	for (int row = 0; row < 4; row++) // 열
		for (int col = 0; col < 4; col++) // 행
			// 만약 배열의 값이 1이면...
			if (Block[Shape][Rotate][row][col] == 1)
			{
				// 블록의 위치를 셋팅 (사각블록 하나의 크기가 10이니 *10 해준다)
				x = 130 + NowX * 30 + col * 30;
				y = NowY * 30 + row * 30;
				// 해당 위치에 해당 크기로(10) 사각형을 출력한다.
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

	for (int row = 0; row < 4; row++) // 열
		for (int col = 0; col < 4; col++) // 행
			// 만약 배열의 값이 1이면...
			if (Block[Shape][Rotate][row][col] == 1)
			{
				// 블록의 위치를 셋팅 (사각블록 하나의 크기가 10이니 *10 해준다)
				x = 545 + col * 30;
				y = 100 + row * 30;
				// 해당 위치에 해당 크기로(10) 사각형을 출력한다.
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

//고스트그리기
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

	
	for (int row = 0; row < 4; row++) // 열
		for (int col = 0; col < 4; col++) // 행
			// 만약 배열의 값이 1이면...
			if (Block[Shape][Rotate][row][col] == 1)
			{
				// 블록의 위치를 셋팅 (사각블록 하나의 크기가 10이니 *10 해준다)
				x = 130 + NowX * 30 + col * 30;
				y = GhostY * 30 + row * 30;
				// 해당 위치에 해당 크기로(10) 사각형을 출력한다.
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


	for (int row = 0; row < 4; row++) // 열
		for (int col = 0; col < 4; col++) // 행
			// 만약 배열의 값이 1이면...
			if (Block[Shape][Rotate][row][col] == 1)
			{
				if (Background[GhostY + row][NowX + col + 1])//배경경계이면 제외
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
//블록 이동 가등여부
BOOL BlockCanMove(int x, int y)
{
	int check = 0;

	for (int row = 0; row < 4; row++) // 열
		for (int col = 0; col < 4; col++) // 행
			// 만약 배열의 값이 1이면...
			if (Block[Shape][Rotate][row][col])
			{
				check += Background[y + row][x + col + 1];//블록이 배경경계에 걸릴때
			}
	return check == 0 ? YES : NO;
}

BOOL BlockCanHoldDraw(int holdShape,int x, int y)//홀드중인 블록을 사용하려할때 배경에걸리는지 검사
{
	int check = 0;

	for (int row = 0; row < 4; row++) // 열
		for (int col = 0; col < 4; col++) // 행
			// 만약 배열의 값이 1이면...
			if (Block[holdShape][Rotate][row][col])
			{
				check += Background[y + row][x + col + 1];//블록이 배경경계에 걸릴때
			}
	return check == 0 ? YES : NO;
}

// 블록 좌측 이동.
void LeftMove()
{
	// 플레이어가 죽었을때
	if (PlayerState == DEAD)
		return;

	// 그렇지 않다면 블록 좌측 이동
	if (BlockCanMove(NowX - 1, NowY))
	{
		// 블록을 지우고
		EraseBlock();
		EraseGhost();
		// 블록 위치 이동 시키고
		NowX--;
		// 블록을 다시 그린다.
		DrawBlock();
	}
}
// 블록 우측 이동.
void RightMove()
{
	// 플레이어가 죽었을때
	if (PlayerState == DEAD)
		return;

	// 그렇지 않다면 블록 좌측 이동
	if (BlockCanMove(NowX + 1, NowY))
	{
		// 블록을 지우고
		EraseGhost();
		EraseBlock();

		// 블록 위치 이동 시키고
		NowX++;
		// 블록을 다시 그린다.
		DrawBlock();
	}
}

void Rotation()
{
	// 플레이어가 죽었을때
	if (PlayerState == DEAD)
		return;

	// 현재 값 
	int temp = Rotate;
	Rotate++;
	// 변수의 한계 값을 3까지만 갖기 위함(if 안써도 됨 스킬이니 기억해두길)
	Rotate %= 4;

	// 회전이 가능 하면
	if (BlockCanMove(NowX, NowY))
	{
		// 복구
		Rotate = temp;
		// 블록을 지우고
		EraseBlock();
		EraseGhost();
		// RotateNum 값 1 증가
		Rotate++;
		// 변수의 한계 값을 3까지만 갖기 위함
		Rotate %= 4;
		// 회전한 블록 그리기
		DrawBlock();
	}
	// 회전이 불가능 하면 복구

	else if (!BlockCanMove(NowX + 1, NowY))//오른쪽벽에 막힌경우
	{
		// 복구
		Rotate = temp;
		// 블록을 지우고
		EraseBlock();
		EraseGhost();
		// 블록 왼쪽 한칸 이동
		// 1자형 블럭일경우 한칸더이동
		if (Shape == 0)
			NowX--;
		NowX--;
		// RotateNum 값 1 증가
		Rotate++;
		// 변수의 한계 값을 3까지만 갖기 위함(if 안써도 됨 스킬이니 기억해두길)
		Rotate %= 4;
		// 회전한 블록 그리기
		DrawBlock();
	}

	else if (!BlockCanMove(NowX - 1, NowY))//왼쪽벽에 막힌경우
	{
		// 복구
		Rotate = temp;
		// 블록을 지우고
		EraseBlock();
		EraseGhost();
		// 블록 오른쪽 1칸이동
		NowX++;
		// RotateNum 값 1 증가
		Rotate++;
		// 변수의 한계 값을 3까지만 갖기 위함(if 안써도 됨 스킬이니 기억해두길)
		Rotate %= 4;
		// 회전한 블록 그리기
		DrawBlock();
	}

	//else
	//	Rotate = temp;  
}

BOOL DownMove()
{
	// 플레이어가 죽었을때
	if (PlayerState == DEAD) return FAIL;

	// 블록이 아래로 내려 갈수 있다면(미리 체크)
	if (BlockCanMove(NowX, NowY + 1))
	{
		// 블록을 지우고
		EraseBlock();
		EraseGhost();
		// 블록 위치 이동 시키고
		NowY++;
		// 블록을 다시 그린다.
		DrawBlock();
		return SUCCESS;
	}
	// 블록이 아래로 내려 갈 수 없다면
	else
	{
		// 움직일수 없는 블록을 배경으로 업데이트.
		UpdateBackGround();
		// 라인이 꽉 차있는지 검사.(미션 성공인지 검사)
		CheckFullLine();
		// 메시지를 발생 시킨다.(다음 블록 진행)
		SendMessage(hWnd, WM_NewBlock, 0, 0);
		return FAIL;
	}
}

BOOL GhostDownMove()
{
	// 플레이어가 죽었을때
	if (PlayerState == DEAD) return FAIL;

	// 블록이 아래로 내려 갈수 있다면(미리 체크)
	if (BlockCanMove(GhostX, GhostY + 1))
	{
		// 블록을 지우고
		EraseGhost();
		// 블록 위치 이동 시키고
		GhostY++;
		// 블록을 다시 그린다.
		DrawGhost();
		return SUCCESS;
	}
	else
	{
		return FAIL;
	}
}

//블럭이 바닥에 닿으면 배경으로 변경
void UpdateBackGround()
{
	int element;
	for (int row = 0; row < 4; row++)
	{
		for (int col = 0; col < 4; col++)
		{
			//현재 블록의 요소값 저장
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

			//블록이 가득찬 줄을 삭제
			EraseFullLine(row);

			FullLineNum++;
			SendMessage(hWnd, WM_RenewalScore,0,0);
			//2줄이상있을경우 대비
			row++;
		}
	}
}

void EraseFullLine(int row)
{
	// 디바이스 컨텍스트를 정의한다.
	HDC hDC, hMemDC;
	// 비트맵의 핸들을 지정하기 위함.
	HBITMAP hBmp;

	// 한마디로 100
	int Xlen = 300;//209 - 110 + 1;

	/* 복사할 영역의 Ylen은 제일 위에서 가득찬 라인 바로 위까지
	의 길이이다.
	row는 0부터 시작하므로 row*10은 full line의 바로 위까지의 길이
	이다.
	즉! full line이 10번째 줄이라면 이 라인의 y 영역은
	90~99이다. 이때 row=9이고 복사할 부분의 y영역은 0~89까지 이다.*/

	// 한마디로 첫 라인부터 삭제 라인 전까지 라인이다.
	int Ylen = row * 30;

	// 윈도우 클라이언트 영역의 디스플레이 디바이스 컨텍스트(DC) 핸들을 구해서 반환한다.
	hDC = GetDC(hWnd);
	// 주어진 디바이스와 호환되는 메모리 디바이스 컨텍스트를 생성한다.
	hMemDC = CreateCompatibleDC(hDC);
	// 비트맵을 생성한다. 
	hBmp = CreateCompatibleBitmap(hDC, 300, 600); // 충분한 크기로 잡는다.
	// 비트맵을 메모리 디바이스 컨텍스트에 넣는다.
	SelectObject(hMemDC, hBmp);

	/*
	 함수 원형
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

	인수
	hdcDest
	이미지를 출력할 위치의 핸들.

	nXDest, nYDest
	이미지를 출력할 위치인 x, y 좌표.

	nWidth, nHeight
	원본 이미지의 너비, 높이 이다.
	이 크기만큼 원본 이미지에서 잘라와 그린다.

	hdcSrc
	이미지의 핸들.

	nXSrc, nYSrc
	가져올 이미지의 시작지점인 x, y좌표이다.
	이 위치부터 nWidth, nHeight만큼 이미지를 잘라온다.

	dwRop
	이미지의 출력 방법

	*/

	// 화면의 일부를 메모리로 복사한다.
	BitBlt(hMemDC, 0, 0, Xlen, Ylen, hDC, 130, 0, SRCCOPY);

	// 메모리에서 화면의 다른 부분으로 복사한다.0
	// 즉! 두번째 줄부터 복사한다.
	BitBlt(hDC, 130, 30, Xlen, Ylen, hMemDC, 0, 0, SRCCOPY);

	// (메모리)디바이스 컨텍스트(DC)를 없앤다
	DeleteDC(hMemDC);
	// 디바이스 컨텍스트를 반납한다.
	ReleaseDC(hWnd, hDC);
	// 객체를 삭제한다.
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
	//빨강
	case 0:
		hPen = CreatePen(PS_SOLID, 1, RGB(255, 255, 255));
		hBrush = CreateSolidBrush(RGB(255, 0, 0));
		break;
	//주황
	case 1:
		hPen = CreatePen(PS_SOLID, 1, RGB(255, 255, 255));
		hBrush = CreateSolidBrush(RGB(255, 130, 0));
		break;
	//노랑
	case 2:
		hPen = CreatePen(PS_SOLID, 1, RGB(255, 255, 255));
		hBrush = CreateSolidBrush(RGB(237, 210, 0));
		break;
	//초록
	case 3:
		hPen = CreatePen(PS_SOLID, 1, RGB(255, 255, 255));
		hBrush = CreateSolidBrush(RGB(0, 183, 0));
		break;
	//파랑
	case 4:
		hPen = CreatePen(PS_SOLID, 1, RGB(255, 255, 255));
		hBrush = CreateSolidBrush(RGB(0, 0, 255));
		break;
	//남색
	case 5:
		hPen = CreatePen(PS_SOLID, 1, RGB(255, 255, 255));
		hBrush = CreateSolidBrush(RGB(5, 0, 153));
		break;
	//보라
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

		for (int row = 0; row < 4; row++) // 열
			for (int col = 0; col < 4; col++) // 행
				// 만약 배열의 값이 1이면...
				if (Block[holdShape][0][row][col] == 1)
				{
					// 블록의 위치를 셋팅 (사각블록 하나의 크기가 10이니 *10 해준다)
					x = 500 + col * 30;
					y = 300 + row * 30;
					// 해당 위치에 해당 크기로(10) 사각형을 출력한다.
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

		for (int row = 0; row < 4; row++) // 열
			for (int col = 0; col < 4; col++) // 행
				// 만약 배열의 값이 1이면...
				if (Block[holdShape][0][row][col] == 1)
				{
					// 블록의 위치를 셋팅 (사각블록 하나의 크기가 10이니 *10 해준다)
					x = 500 + col * 30;
					y = 300 + row * 30;
					// 해당 위치에 해당 크기로(10) 사각형을 출력한다.
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
	int tempShape = holdShape;//현재 홀드 되있는 블록의 종류
	int tempColor = holdColor;//현재 홀드 되있는 블록의 컬러

	//현재 홀드중인 블록이 있을경우
	if (isHolding)
	{
		if (BlockCanHoldDraw(tempShape, NowX, NowY))//현재 홀드된블록을 그렸을때 배경에겹치지않는지 검사
		{

			holdShape = Shape;//현재 블록종류를 저장
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
		holdShape = Shape;//현재 블록종류를 저장
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
	// 디바이스 컨텍스트를 정의한다.
	HDC hDC, hMemDC;
	// 비트맵의 핸들을 지정하기 위함.
	HBITMAP hBmp;

	// 한마디로 100
	int Xlen = 300;//209 - 110 + 1;

	// 한마디로 첫 라인부터 삭제 라인 전까지 라인이다.
	int Ylen = 570;//위부터 바닥바로위까지

	// 윈도우 클라이언트 영역의 디스플레이 디바이스 컨텍스트(DC) 핸들을 구해서 반환한다.
	hDC = GetDC(hWnd);
	// 주어진 디바이스와 호환되는 메모리 디바이스 컨텍스트를 생성한다.
	hMemDC = CreateCompatibleDC(hDC);
	// 비트맵을 생성한다. 
	hBmp = CreateCompatibleBitmap(hDC, 300, 600); // 충분한 크기로 잡는다.
	// 비트맵을 메모리 디바이스 컨텍스트에 넣는다.
	SelectObject(hMemDC, hBmp);


	EraseBlock();
	EraseGhost();
	// 화면의 일부를 메모리로 복사한다.
	BitBlt(hMemDC, 0, 0, Xlen, Ylen, hDC, 130, 30, SRCCOPY);

	// 메모리에서 화면의 다른 부분으로 복사한다.0
	// 즉! 두번째 줄부터 복사한다.
	BitBlt(hDC, 130, 0, Xlen, Ylen, hMemDC, 0, 0, SRCCOPY);



	// (메모리)디바이스 컨텍스트(DC)를 없앤다
	DeleteDC(hMemDC);
	// 디바이스 컨텍스트를 반납한다.
	ReleaseDC(hWnd, hDC);
	// 객체를 삭제한다.
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

			x = 100 + col * 30; //x축으로 100만큼띄워서생성
			y = row * 30;
			Rectangle(hDC, x, y, x + 30, y + 30);
		}
		else
		{
			hPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
			hBrush = CreateSolidBrush(RGB(0, 0, 0));
			hOldPen = (HPEN)SelectObject(hDC, hPen);
			hOldBrush = (HBRUSH)SelectObject(hDC, hBrush);
			x = 100 + col * 30; //x축으로 100만큼띄워서생성
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
