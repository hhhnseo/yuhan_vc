#include <windows.h>
#include <cmath>


HBRUSH hBackgroundBrush;
RECT rcClient;
RECT contentBox;
BOOL isBoxDrawing = FALSE;
BOOL isCircleDrawing = FALSE;
BOOL isBonobonoDrawing = FALSE;
BOOL isSpacebarPressed = FALSE;
BOOL isRyanDrawing = FALSE;
BOOL isCubeDrawing = FALSE;
POINT startPoint, endPoint;


class MyButton {
public:
    HWND hwnd;

    int x, y, width, height;

    MyButton() : hwnd(NULL), x(0), y(0), width(0), height(0) {}

    MyButton(HWND parent, LPCWSTR text, int x, int y, int width, int height) : x(x), y(y), width(width), height(height) {
        hwnd = CreateWindow(L"BUTTON", text, WS_VISIBLE | WS_CHILD, x, y, width, height, parent, NULL, NULL, NULL);
    }
};

MyButton boxButton, circleButton, bonobonoButton, ryanButton, cubeButton;

BOOL IsInsideContentBox(POINT pt) {
    return (pt.x >= contentBox.left && pt.x <= contentBox.right &&
        pt.y >= contentBox.top && pt.y <= contentBox.bottom);
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
    case WM_CREATE:
    {
        GetClientRect(hwnd, &rcClient);
        int buttonWidth = (rcClient.right - rcClient.left - 4 * 8) / 5;
        int buttonHeight = (buttonWidth * 2) / 5;
        int buttonSpacing = buttonWidth / 10;
        int totalButtonsWidth = 5 * buttonWidth + 4 * buttonSpacing;
        int startX = (rcClient.right - totalButtonsWidth) / 2;

        boxButton = MyButton(hwnd, L"Box", startX, rcClient.top + buttonSpacing, buttonWidth, buttonHeight);
        circleButton = MyButton(hwnd, L"Circle", boxButton.x + buttonWidth + buttonSpacing, rcClient.top + buttonSpacing, buttonWidth, buttonHeight);
        bonobonoButton = MyButton(hwnd, L"Bonobono", circleButton.x + buttonWidth + buttonSpacing, rcClient.top + buttonSpacing, buttonWidth, buttonHeight);
        ryanButton = MyButton(hwnd, L"Ryan", bonobonoButton.x + buttonWidth + buttonSpacing, rcClient.top + buttonSpacing, buttonWidth, buttonHeight);
        cubeButton = MyButton(hwnd, L"Cube", ryanButton.x + buttonWidth + buttonSpacing, rcClient.top + buttonSpacing, buttonWidth, buttonHeight);
        return 0;
    }

    case WM_CLOSE:
        PostQuitMessage(0);
        return 0;

    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;

    case WM_ERASEBKGND:
    {
        GetClientRect(hwnd, &rcClient);
        SetBkColor((HDC)wParam, RGB(255, 240, 200));
        if (!hBackgroundBrush) {
            hBackgroundBrush = CreateSolidBrush(RGB(255, 240, 200));
        }
        FillRect((HDC)wParam, &rcClient, hBackgroundBrush);
        return 1;
    }

    case WM_COMMAND:
        if ((HWND)lParam == boxButton.hwnd) {
            isBoxDrawing = TRUE;
            isCircleDrawing = FALSE;
            isBonobonoDrawing = FALSE;
            isRyanDrawing = FALSE;
            isCubeDrawing = FALSE;
            SetFocus(hwnd);
        }
        if ((HWND)lParam == circleButton.hwnd) {
            isCircleDrawing = TRUE;
            isBoxDrawing = FALSE;
            isBonobonoDrawing = FALSE;
            isRyanDrawing = FALSE;
            isCubeDrawing = FALSE;
            SetFocus(hwnd);
        }
        if ((HWND)lParam == bonobonoButton.hwnd) {
            isBonobonoDrawing = TRUE;
            isBoxDrawing = FALSE;
            isCircleDrawing = FALSE;  // 상태 초기화
            isRyanDrawing = FALSE;
            isCubeDrawing = FALSE;
            SetFocus(hwnd);
        }
        if ((HWND)lParam == ryanButton.hwnd) {
            isRyanDrawing = TRUE;
            isBonobonoDrawing = FALSE;
            isBoxDrawing = FALSE;
            isCircleDrawing = FALSE;  // 상태 초기화
            isCubeDrawing = FALSE;
            SetFocus(hwnd);
        }
        if ((HWND)lParam == cubeButton.hwnd) {
            isCubeDrawing = TRUE;
            isRyanDrawing = FALSE;
            isBonobonoDrawing = FALSE;
            isBoxDrawing = FALSE;
            isCircleDrawing = FALSE;  // 상태 초기화
            SetFocus(hwnd);
        }

        break;

    case WM_LBUTTONDOWN:
    {
        startPoint.x = LOWORD(lParam);
        startPoint.y = HIWORD(lParam);
        SetCapture(hwnd);
        break;
    }

    case WM_MOUSEMOVE:
        if (wParam & MK_LBUTTON && isCubeDrawing) {
            endPoint.x = LOWORD(lParam);
            endPoint.y = HIWORD(lParam);
            InvalidateRect(hwnd, &contentBox, FALSE);
        }
        break;

    case WM_LBUTTONUP:
        if (isCubeDrawing) {
            endPoint.x = LOWORD(lParam);
            endPoint.y = HIWORD(lParam);
            InvalidateRect(hwnd, NULL, TRUE);
        }
        ReleaseCapture();
        break;

    case WM_KEYDOWN:
        if (wParam == VK_SPACE) {
            isSpacebarPressed = TRUE;
            InvalidateRect(hwnd, NULL, TRUE); // Redraw window to update eyes
        }
        break;

    case WM_KEYUP:
        if (wParam == VK_SPACE) {
            isSpacebarPressed = FALSE;
            InvalidateRect(hwnd, NULL, TRUE); // Redraw window to update eyes
        }
        break;



    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hwnd, &ps);

        contentBox = {
            rcClient.left + 8,
            boxButton.y + boxButton.height + 16,
            rcClient.right - 8,
            rcClient.bottom - 8
        };

        HBRUSH contentBrush = CreateSolidBrush(RGB(255, 255, 255));
        FillRect(hdc, &contentBox, contentBrush);

        if (isBoxDrawing && IsInsideContentBox(startPoint) && IsInsideContentBox(endPoint)) {
            HBRUSH boxBrush = CreateSolidBrush(RGB(0, 0, 255));
            SelectObject(hdc, boxBrush);
            Rectangle(hdc, startPoint.x, startPoint.y, endPoint.x, endPoint.y);
            DeleteObject(boxBrush);
        }

        if (isCircleDrawing && IsInsideContentBox(startPoint) && IsInsideContentBox(endPoint)) {
            int radius = (int)sqrt(pow(endPoint.x - startPoint.x, 2) + pow(endPoint.y - startPoint.y, 2));
            HBRUSH circleBrush = CreateSolidBrush(RGB(0, 255, 0));
            SelectObject(hdc, circleBrush);
            Ellipse(hdc, startPoint.x - radius, startPoint.y - radius, startPoint.x + radius, startPoint.y + radius);
            DeleteObject(circleBrush);
        }

        if (isBonobonoDrawing && IsInsideContentBox(startPoint) && IsInsideContentBox(endPoint)) {
            int radius = (int)sqrt(pow(endPoint.x - startPoint.x, 2) + pow(endPoint.y - startPoint.y, 2));
            HBRUSH bonobonoBrush = CreateSolidBrush(RGB(91, 155, 213));  // 보노보노 얼굴색
            SelectObject(hdc, bonobonoBrush);
            Ellipse(hdc, startPoint.x - radius, startPoint.y - radius, startPoint.x + radius, startPoint.y + radius);

            // 보노보노 눈
            int eyeRadius = radius / 10;  // 눈 크기
            HBRUSH eyeBrush = CreateSolidBrush(RGB(0, 0, 0));  // 눈 색
            SelectObject(hdc, eyeBrush);

            if (isSpacebarPressed) {
                // 보노보노 눈 찡긋
                HPEN linePen = CreatePen(PS_SOLID, 2, RGB(0, 0, 0));
                SelectObject(hdc, linePen);

                // Angles for the squinting effect
                int lineLength = eyeRadius * 2;  // Adjust this value to control the angle
                int angleOffset = eyeRadius;
                float eyePositionFactor = 0.6;
                int eyePosXOffset = (int)(radius * eyePositionFactor);

                // Left Eye - Upper line (creates the top of >)
                MoveToEx(hdc, startPoint.x - eyePosXOffset, startPoint.y - radius / 6, NULL);
                LineTo(hdc, startPoint.x - eyePosXOffset - lineLength, startPoint.y - radius / 6 - angleOffset);

                // Left Eye - Lower line (creates the bottom of >)
                MoveToEx(hdc, startPoint.x - eyePosXOffset, startPoint.y - radius / 6, NULL);
                LineTo(hdc, startPoint.x - eyePosXOffset - lineLength, startPoint.y - radius / 6 + angleOffset);

                // Right Eye - Upper line (creates the top of <)
                MoveToEx(hdc, startPoint.x + eyePosXOffset, startPoint.y - radius / 6, NULL);
                LineTo(hdc, startPoint.x + eyePosXOffset + lineLength, startPoint.y - radius / 6 - angleOffset);

                // Right Eye - Lower line (creates the bottom of <)
                MoveToEx(hdc, startPoint.x + eyePosXOffset, startPoint.y - radius / 6, NULL);
                LineTo(hdc, startPoint.x + eyePosXOffset + lineLength, startPoint.y - radius / 6 + angleOffset);

                DeleteObject(linePen);
            }
            else {
                // 왼쪽 눈
                Ellipse(hdc, startPoint.x - radius * 2 / 3 - eyeRadius, startPoint.y - radius / 6 - eyeRadius, startPoint.x - radius * 2 / 3 + eyeRadius, startPoint.y - radius / 6 + eyeRadius);
                // 오른쪽 눈
                Ellipse(hdc, startPoint.x + radius * 2 / 3 - eyeRadius, startPoint.y - radius / 6 - eyeRadius, startPoint.x + radius * 2 / 3 + eyeRadius, startPoint.y - radius / 6 + eyeRadius);
            }

            // 보노보노 입
            HBRUSH mouthBrush = CreateSolidBrush(RGB(217, 65, 197));
            HPEN mouthPen = CreatePen(PS_SOLID, 2, RGB(0, 0, 0));
            SelectObject(hdc, mouthBrush);
            SelectObject(hdc, mouthPen);
            BeginPath(hdc);
            Arc(hdc, startPoint.x - radius / 8, startPoint.y, startPoint.x + radius / 8, startPoint.y + 2 * radius / 3, startPoint.x, startPoint.y + radius / 3, startPoint.x, startPoint.y + radius / 3);  // Vertically
            EndPath(hdc);
            StrokeAndFillPath(hdc);

            // 보노보노 수염나는 곳
            int whiteCircleRadius = radius / 5;
            HBRUSH whiteCircleBrush = CreateSolidBrush(RGB(255, 255, 255));
            SelectObject(hdc, whiteCircleBrush);
            // 왼쪽 원의 중심
            int leftCircleCenterX = startPoint.x - whiteCircleRadius;
            int leftCircleCenterY = startPoint.y;

            // 오른쪽 원의 중심
            int rightCircleCenterX = startPoint.x + whiteCircleRadius;
            int rightCircleCenterY = startPoint.y;

            Ellipse(hdc,
                leftCircleCenterX - whiteCircleRadius,
                leftCircleCenterY - whiteCircleRadius,
                leftCircleCenterX + whiteCircleRadius,
                leftCircleCenterY + whiteCircleRadius);  // 왼쪽 흰색 원

            Ellipse(hdc,
                rightCircleCenterX - whiteCircleRadius,
                rightCircleCenterY - whiteCircleRadius,
                rightCircleCenterX + whiteCircleRadius,
                rightCircleCenterY + whiteCircleRadius);  // 오른쪽 흰색 원

            // Calculate the midpoint between the two white circles to position the nose
            int noseCenterX = (leftCircleCenterX + rightCircleCenterX) / 2;
            int noseCenterY = (leftCircleCenterY + rightCircleCenterY) / 2 - radius / 10;
            int noseRadius = radius / 7;  // Define the nose size. Adjust as needed.

            SelectObject(hdc, eyeBrush);  // Using the black brush for the eyes for the nose
            Ellipse(hdc,
                noseCenterX - noseRadius,
                noseCenterY - noseRadius,
                noseCenterX + noseRadius,
                noseCenterY + noseRadius);  // Nose

            // 보노보노 수염
            int whiskerLength = radius / 8;  // Length of the whisker
            int yOffset = whiskerLength / 2;  // Adjust this to change the angle, making it less will reduce the angle
            HPEN whiskerPen = CreatePen(PS_SOLID, 2, RGB(0, 0, 0));  // Creating a solid black pen for whisker
            SelectObject(hdc, whiskerPen);  // Selecting the whisker pen

            // Adjusting the starting point towards the center by a quarter of the white circle's radius
            int xOffset = whiteCircleRadius / 4;

            // Drawing adjusted diagonal whiskers on the left white circle
            MoveToEx(hdc, leftCircleCenterX - whiteCircleRadius + xOffset, leftCircleCenterY - whiteCircleRadius / 2, NULL);
            LineTo(hdc, leftCircleCenterX - whiteCircleRadius + xOffset - whiskerLength, leftCircleCenterY - whiteCircleRadius / 2 - yOffset);
            MoveToEx(hdc, leftCircleCenterX - whiteCircleRadius + xOffset, leftCircleCenterY + whiteCircleRadius / 2, NULL);
            LineTo(hdc, leftCircleCenterX - whiteCircleRadius + xOffset - whiskerLength, leftCircleCenterY + whiteCircleRadius / 2 + yOffset);

            // Drawing adjusted diagonal whiskers on the right white circle
            MoveToEx(hdc, rightCircleCenterX + whiteCircleRadius - xOffset, rightCircleCenterY - whiteCircleRadius / 2, NULL);
            LineTo(hdc, rightCircleCenterX + whiteCircleRadius - xOffset + whiskerLength, rightCircleCenterY - whiteCircleRadius / 2 - yOffset);
            MoveToEx(hdc, rightCircleCenterX + whiteCircleRadius - xOffset, rightCircleCenterY + whiteCircleRadius / 2, NULL);
            LineTo(hdc, rightCircleCenterX + whiteCircleRadius - xOffset + whiskerLength, rightCircleCenterY + whiteCircleRadius / 2 + yOffset);

            DeleteObject(whiskerPen);  // Deleting the whisker pen after drawing
            DeleteObject(whiteCircleBrush);
            DeleteObject(mouthBrush);
            DeleteObject(mouthPen);
            DeleteObject(bonobonoBrush);
            DeleteObject(eyeBrush);
        }

        if (isRyanDrawing && IsInsideContentBox(startPoint) && IsInsideContentBox(endPoint)) {
            int radius = (int)sqrt(pow(endPoint.x - startPoint.x, 2) + pow(endPoint.y - startPoint.y, 2));
            HBRUSH ryanBrush = CreateSolidBrush(RGB(253, 170, 3));  // 라이언 얼굴색
            SelectObject(hdc, ryanBrush);

            // 라이언 귀 위치 및 크기 조정
            int earRadius = radius / 1.5;
            int earVerticalOffset = radius / 3;
            int earHorizontalOffset = radius / 8; // 수평 위치 조정

            SelectObject(hdc, ryanBrush);

            // 왼쪽 귀 (오른쪽 귀와 동일한 모양과 대칭 위치로 조정)
            Ellipse(hdc,
                startPoint.x - radius - earHorizontalOffset,
                startPoint.y - earVerticalOffset - earRadius,
                startPoint.x - radius - earHorizontalOffset + earRadius,
                startPoint.y - earVerticalOffset);

            // 오른쪽 귀
            Ellipse(hdc,
                startPoint.x + radius - earRadius + earHorizontalOffset,
                startPoint.y - earVerticalOffset - earRadius,
                startPoint.x + radius + earHorizontalOffset,
                startPoint.y - earVerticalOffset);


            // 라이언 얼굴
            Ellipse(hdc, startPoint.x - radius, startPoint.y - radius, startPoint.x + radius, startPoint.y + radius);

            // 라이언 눈
            int eyeRadius = radius / 11;
            HBRUSH eyeBrush = CreateSolidBrush(RGB(0, 0, 0));
            SelectObject(hdc, eyeBrush);

            int eyeOffset = 4;

            // 왼쪽 눈
            Ellipse(hdc,
                startPoint.x - radius * 2 / 3 + 12 - eyeRadius,
                startPoint.y - radius / 6 - eyeRadius + eyeOffset,
                startPoint.x - radius * 2 / 3 + 12 + eyeRadius,
                startPoint.y - radius / 6 + eyeRadius + eyeOffset);

            // 오른쪽 눈
            Ellipse(hdc,
                startPoint.x + radius * 2 / 3 - 12 - eyeRadius,
                startPoint.y - radius / 6 - eyeRadius + eyeOffset,
                startPoint.x + radius * 2 / 3 - 12 + eyeRadius,
                startPoint.y - radius / 6 + eyeRadius + eyeOffset);

            int someOffset = 20;

            int whiteCircleRadius = radius / 7;
            HBRUSH whiteCircleBrush = CreateSolidBrush(RGB(255, 255, 255));
            SelectObject(hdc, whiteCircleBrush);

            // 왼쪽 및 오른쪽 흰색 원 중심 위치 조정
            int leftCircleCenterX = startPoint.x - whiteCircleRadius;
            int leftCircleCenterY = startPoint.y + someOffset;
            int rightCircleCenterX = startPoint.x + whiteCircleRadius;
            int rightCircleCenterY = startPoint.y + someOffset;

            // 왼쪽 흰색 원 위치 조정
            Ellipse(hdc,
                leftCircleCenterX - whiteCircleRadius,
                leftCircleCenterY - whiteCircleRadius,
                leftCircleCenterX + whiteCircleRadius,
                leftCircleCenterY + whiteCircleRadius);

            // 오른쪽 흰색 원 위치 조정
            Ellipse(hdc,
                rightCircleCenterX - whiteCircleRadius,
                rightCircleCenterY - whiteCircleRadius,
                rightCircleCenterX + whiteCircleRadius,
                rightCircleCenterY + whiteCircleRadius);

            // 눈썹
            HPEN eyebrowPen = CreatePen(PS_SOLID, 3, RGB(0, 0, 0)); // 눈썹 색상 및 두께 설정
            SelectObject(hdc, eyebrowPen);

            // 왼쪽 눈썹
            MoveToEx(hdc, startPoint.x - radius * 2 / 3 + 12 - eyeRadius - 5, startPoint.y - radius / 6 - eyeRadius + eyeOffset - 10, NULL);
            LineTo(hdc, startPoint.x - radius * 2 / 3 + 12 + eyeRadius + 5, startPoint.y - radius / 6 - eyeRadius + eyeOffset - 10);

            // 오른쪽 눈썹
            MoveToEx(hdc, startPoint.x + radius * 2 / 3 - 12 - eyeRadius - 5, startPoint.y - radius / 6 - eyeRadius + eyeOffset - 10, NULL);
            LineTo(hdc, startPoint.x + radius * 2 / 3 - 12 + eyeRadius + 5, startPoint.y - radius / 6 - eyeRadius + eyeOffset - 10);

            DeleteObject(eyebrowPen);
            DeleteObject(whiteCircleBrush);
            DeleteObject(ryanBrush);
            DeleteObject(eyeBrush);
        }

        if (isCubeDrawing && IsInsideContentBox(startPoint) && IsInsideContentBox(endPoint)) {
            // 큐브의 크기 및 방향 계산
            int cubeWidth = abs(endPoint.x - startPoint.x);
            int cubeHeight = abs(endPoint.y - startPoint.y);
            int cubeDepth = min(cubeWidth, cubeHeight) / 2; // 깊이는 너비와 높이의 절반으로 설정

            // 큐브의 전면 꼭지점 계산
            POINT frontTopLeft = { min(startPoint.x, endPoint.x), min(startPoint.y, endPoint.y) };
            POINT frontTopRight = { frontTopLeft.x + cubeWidth, frontTopLeft.y };
            POINT frontBottomLeft = { frontTopLeft.x, frontTopLeft.y + cubeHeight };
            POINT frontBottomRight = { frontTopLeft.x + cubeWidth, frontTopLeft.y + cubeHeight };

            // 큐브의 후면 꼭지점 계산
            POINT backTopLeft = { frontTopLeft.x + cubeDepth, frontTopLeft.y - cubeDepth };
            POINT backTopRight = { frontTopRight.x + cubeDepth, frontTopRight.y - cubeDepth };
            POINT backBottomLeft = { frontBottomLeft.x + cubeDepth, frontBottomLeft.y - cubeDepth };
            POINT backBottomRight = { frontBottomRight.x + cubeDepth, frontBottomRight.y - cubeDepth };

            // 큐브의 전면 그리기
            MoveToEx(hdc, frontTopLeft.x, frontTopLeft.y, NULL);
            LineTo(hdc, frontTopRight.x, frontTopRight.y);
            LineTo(hdc, frontBottomRight.x, frontBottomRight.y);
            LineTo(hdc, frontBottomLeft.x, frontBottomLeft.y);
            LineTo(hdc, frontTopLeft.x, frontTopLeft.y);

            // 큐브의 상단면 그리기
            MoveToEx(hdc, frontTopLeft.x, frontTopLeft.y, NULL);
            LineTo(hdc, backTopLeft.x, backTopLeft.y);
            LineTo(hdc, backTopRight.x, backTopRight.y);
            LineTo(hdc, frontTopRight.x, frontTopRight.y);

            // 큐브의 측면 그리기
            MoveToEx(hdc, frontTopRight.x, frontTopRight.y, NULL);
            LineTo(hdc, backTopRight.x, backTopRight.y);
            LineTo(hdc, backBottomRight.x, backBottomRight.y);
            LineTo(hdc, frontBottomRight.x, frontBottomRight.y);

            MoveToEx(hdc, backTopLeft.x, backTopLeft.y, NULL);
            LineTo(hdc, backTopRight.x, backTopRight.y);
            LineTo(hdc, backBottomRight.x, backBottomRight.y);
            LineTo(hdc, backBottomLeft.x, backBottomLeft.y);
            LineTo(hdc, backTopLeft.x, backTopLeft.y);

            MoveToEx(hdc, frontBottomLeft.x, frontBottomLeft.y, NULL);
            LineTo(hdc, backBottomLeft.x, backBottomLeft.y);


        }

        DeleteObject(contentBrush);

        EndPaint(hwnd, &ps);
        return 0;
    }

    default:
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    WNDCLASSEX wc = { sizeof(WNDCLASSEX), CS_CLASSDC, WindowProc, 0L, 0L, GetModuleHandle(NULL), NULL, NULL, NULL, NULL, L"MyWindowClass", NULL };
    RegisterClassEx(&wc);

    HWND hwnd = CreateWindow(wc.lpszClassName, L"My Window", WS_OVERLAPPEDWINDOW & ~(WS_MAXIMIZEBOX | WS_SIZEBOX), 100, 100, 800, 480, NULL, NULL, hInstance, NULL);

    if (!hwnd) {
        return -1;
    }

    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    if (hBackgroundBrush) {
        DeleteObject(hBackgroundBrush);
    }

    UnregisterClass(wc.lpszClassName, wc.hInstance);
    return (int)msg.wParam;
}