// FoorBlueWitch.cpp : 애플리케이션에 대한 진입점을 정의합니다.

#include "framework.h"
#include "FoorBlueWitch.h"
#include "D2d.h"
#include "GameObject.h"
#include "Movable.h"

#define MAX_LOADSTRING 100

// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
HWND  hWnd;                                     // 현재 게임창입니다.
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.

DWORD lastUpdateTime;                           // 마지막 업데이트 시간입니다.
float deltaTime;                                // 업데이트에 걸린 시간입니다.
bool gameRunning;                               // 게임 진행 여부입니다.

// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);



int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: 여기에 코드를 입력.

    // 전역 문자열을 초기화.
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_FOORBLUEWITCH, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 애플리케이션 초기화를 수행 :
    if (!InitInstance (hInstance, nCmdShow)) {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_FOORBLUEWITCH));

    MSG msg;

    // 그래픽 초기화
    Initialize();
    // 게임 구동 중
    gameRunning = true;
    // 게임 시작
    GameStart();
    // 시간의 기준점 
    lastUpdateTime = timeGetTime();

    // 게임 끝날 때까지 무한 반복 (게임의 본체)
    // GetMessage : 메시지 받을 때까지 기다린다. (게임이 진행 불가)
    // PeekMessage: 메시지를 못 받으면 다음 코드로 바로 넘어간다. (게임 진행)
    while (gameRunning) {
        // 메시지를 받고 사용한 메시지는 삭제
        PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE);

        if (msg.message == WM_QUIT) break;

        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg)) {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        };

        // 현재 시간
        DWORD currentTime = timeGetTime();

        // deltaTime   : 초
        // timeGetTime : 밀리초 (1000배!) 
        deltaTime = (currentTime - lastUpdateTime) / 1000.0f;

        if (deltaTime >= FRAMETIME) {
            GameUpdate();

            lastUpdateTime = currentTime;
        };
    };

    // 게임 종료
    GameEnd();
    Release();

    return (int) msg.wParam;
}

//  함수: MyRegisterClass()
//
//  용도: 창 클래스를 등록.

ATOM MyRegisterClass(HINSTANCE hInstance) {
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;


    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON2));
    wcex.hCursor        = LoadCursor(hInstance, MAKEINTRESOURCE(IDC_DEFAULT));
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = nullptr; //상단바 메뉴
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_ICON2));

    return RegisterClassExW(&wcex);
}

//   함수: InitInstance(HINSTANCE, int)
//
//   용도: 인스턴스 핸들을 저장하고 주 창을 만든다..
//
//   주석:
//
//        이 함수를 통해 인스턴스 핸들을 전역 변수에 저장하고
//        주 프로그램 창을 만든 다음 표시.

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow) {
   hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장.

   //전역변수로 변경
   hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//  함수: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  용도: 주 창의 메시지를 처리.
//
//  WM_COMMAND  - 애플리케이션 메뉴를 처리.
//  WM_PAINT    - 주 창을 그린다.
//  WM_DESTROY  - 종료 메시지를 게시하고 반환.

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    switch (message) {
    case WM_LBUTTONDOWN:
        POINT cursor;
        
        GetCursorPos(&cursor);

        break;
    case WM_COMMAND: {
            int wmId = LOWORD(wParam);
            // 메뉴 선택을 구문 분석
            switch (wmId) {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT: {
            Draw();
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

// 정보 대화 상자의 메시지 처리기
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam) {
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL) {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
