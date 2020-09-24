// Test1.cpp : Определяет точку входа для приложения.
//

#include "framework.h"
#include "Test1.h"

#define MAX_LOADSTRING 100

// Глобальные переменные:
HINSTANCE hInst;                                // текущий экземпляр
WCHAR szTitle[MAX_LOADSTRING];                  // Текст строки заголовка
WCHAR szWindowClass[MAX_LOADSTRING];     
       // имя класса главного окна
enum Figure
{
    RECTANGLE,
    LINE,
    OVAL,
    BROKEN,
    TRIANGLE

}wFigure;
HDC hdc;
static HDC secondHDC;
PAINTSTRUCT ps;
RECT r;
HPEN pen;
HBRUSH hBrush;
LOGFONT lf;
HFONT hFont;
HPEN hPen;

// Отправить объявления функций, включенных в этот модуль кода:
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

    // TODO: Разместите код здесь.

    // Инициализация глобальных строк
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_TEST1, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Выполнить инициализацию приложения:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_TEST1));

    MSG msg;

    // Цикл основного сообщения:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  ФУНКЦИЯ: MyRegisterClass()
//
//  ЦЕЛЬ: Регистрирует класс окна.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_TEST1));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_TEST1);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   ФУНКЦИЯ: InitInstance(HINSTANCE, int)
//
//   ЦЕЛЬ: Сохраняет маркер экземпляра и создает главное окно
//
//   КОММЕНТАРИИ:
//
//        В этой функции маркер экземпляра сохраняется в глобальной переменной, а также
//        создается и выводится главное окно программы.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Сохранить маркер экземпляра в глобальной переменной

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  ФУНКЦИЯ: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  ЦЕЛЬ: Обрабатывает сообщения в главном окне.
//
//  WM_COMMAND  - обработать меню приложения
//  WM_PAINT    - Отрисовка главного окна
//  WM_DESTROY  - отправить сообщение о выходе и вернуться
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {

    case WM_CREATE:
    {
        hdc = GetDC(hWnd);
        secondHDC = CreateCompatibleDC(hdc);
        HBITMAP bMap = CreateCompatibleBitmap(hdc, 1000, 1000);
        SelectObject(secondHDC, bMap);
    }
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Разобрать выбор в меню:
            switch (wmId)
            {
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
    case WM_PAINT:
        {
            
            HDC hdc = BeginPaint(hWnd, &ps);
           

            hBrush = CreateHatchBrush(HS_FDIAGONAL, RGB(255, 0, 0));
            SelectObject(hdc, hBrush);
           
            //текст
            lf.lfHeight = 20;
            lf.lfItalic = 1;
            lf.lfStrikeOut = 0;
            lf.lfUnderline = 0;
            lf.lfWidth = 10;
            lf.lfWeight = 40;
            lf.lfCharSet = DEFAULT_CHARSET;
            lf.lfPitchAndFamily = DEFAULT_PITCH; 
            lf.lfEscapement = 0;
            hFont = CreateFontIndirect(&lf);
            SelectObject(hdc, hFont);
            SetTextColor(hdc, RGB(255, 0, 255));
            TextOutW(hdc, 150, 270, L"Hello World", lstrlen(L"Hello World"));

            //ломаная
            MoveToEx(hdc, 500, 250, NULL);
            LineTo(hdc, 500, 300);
            MoveToEx(hdc, 450, 250, NULL);
            LineTo(hdc, 500, 300);
            MoveToEx(hdc, 450, 250, NULL);
            LineTo(hdc, 400, 250);
            MoveToEx(hdc, 400, 250, NULL);
            LineTo(hdc, 350, 300);
            
            //линия
            MoveToEx(hdc, 300, 250, NULL);
            LineTo(hdc, 300, 300);

            //эллипс
            hBrush = CreateSolidBrush(RGB(10, 200, 100));
            SelectObject(hdc, hBrush);
            Ellipse(hdc, 900, 250, 1000, 300);

            //прямоугольник
            hBrush = CreateSolidBrush(RGB(250, 200, 100));
            SelectObject(hdc, hBrush);
            hPen = CreatePen(2, 2, RGB(0, 0, 255));
            SelectObject(hdc, hPen);
            r.top = 250;
            r.left = 700;
            r.right = 850;
            r.bottom = 300;
            FillRect(hdc, &r, HBRUSH(CreateSolidBrush(RGB(255, 0, 0))));
    
            //многоугольник
            POINT poly[6];
            poly[0].x = 650;
            poly[0].y = 300;
            poly[1].x = 550;
            poly[1].y = 300;
            poly[2].x = 550;
            poly[2].y = 270;
            poly[3].x = 600;
            poly[3].y = 250;
            poly[4].x = 650;
            poly[4].y = 270;
            poly[5].x = 650;
            poly[5].y = 300;
            Polyline(hdc, poly, 6);

            ValidateRect(hWnd, NULL);
            EndPaint(hWnd, &ps);
        }
        break;

  
    case WM_KEYDOWN:
    {
        switch (wParam)
        {
        case VK_LEFT:
            wFigure = RECTANGLE;
            break;
        case VK_RIGHT:
            wFigure = OVAL;
            break;

        default:
            break;
        }
    }
    break;
    case WM_LBUTTONDOWN:
    {
        switch (wFigure) 
        {
        case RECTANGLE:
        {}
            
        }
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

// Обработчик сообщений для окна "О программе".
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
