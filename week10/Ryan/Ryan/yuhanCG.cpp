#include <windows.h>
#include <cmath>
#include "yuhanCG.h"

HBRUSH hBackgroundBrush;
RECT rcClient;
RECT contentBox;
BOOL isBoxDrawing = FALSE;
BOOL isCircleDrawing = FALSE;
BOOL isBonobonoDrawing = FALSE;
BOOL isSpacebarPressed = FALSE;
BOOL isRyanDrawing = FALSE;
POINT startPoint, endPoint;


class MyButton {
public:
    HWND hWnd;

    int x, y, width, height;

    MyButton() : hWnd(NULL), x(0), y(0), width(0), height(0) {}

    MyButton(HWND parent, LPCWSTR text, int x, int y, int width, int height) : x(x), y(y), width(width), height(height) {
        hWnd = CreateWindow(L"BUTTON", text, WS_VISIBLE | WS_CHILD, x, y, width, height, parent, NULL, NULL, NULL);
    }
};

MyButton boxButton, circleButton, bonobonoButton, ryanButton, cubeButton;

BOOL IsInsideContentBox(POINT pt) {
    return (pt.x >= contentBox.left && pt.x <= contentBox.right &&
        pt.y >= contentBox.top && pt.y <= contentBox.bottom);
}

LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
    case WM_CREATE:
    {
        GetClientRect(hWnd, &rcClient);
        int buttonWidth = (rcClient.right - rcClient.left - 4 * 8) / 5;
        int buttonHeight = (buttonWidth * 2) / 5;
        int buttonSpacing = buttonWidth / 10;
        int totalButtonsWidth = 5 * buttonWidth + 4 * buttonSpacing;
        int startX = (rcClient.right - totalButtonsWidth) / 2;

        boxButton = MyButton(hWnd, L"Box", startX, rcClient.top + buttonSpacing, buttonWidth, buttonHeight);
        circleButton = MyButton(hWnd, L"Circle", boxButton.x + buttonWidth + buttonSpacing, rcClient.top + buttonSpacing, buttonWidth, buttonHeight);
        bonobonoButton = MyButton(hWnd, L"Bonobono", circleButton.x + buttonWidth + buttonSpacing, rcClient.top + buttonSpacing, buttonWidth, buttonHeight);
        ryanButton = MyButton(hWnd, L"Ryan", bonobonoButton.x + buttonWidth + buttonSpacing, rcClient.top + buttonSpacing, buttonWidth, buttonHeight);
        cubeButton = MyButton(hWnd, L"Cube", ryanButton.x + buttonWidth + buttonSpacing, rcClient.top + buttonSpacing, buttonWidth, buttonHeight);
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
        GetClientRect(hWnd, &rcClient);
        SetBkColor((HDC)wParam, RGB(255, 240, 200));
        if (!hBackgroundBrush) {
            hBackgroundBrush = CreateSolidBrush(RGB(255, 240, 200));
        }
        FillRect((HDC)wParam, &rcClient, hBackgroundBrush);
        return 1;
    }

    case WM_COMMAND:
        if ((HWND)lParam == boxButton.hWnd) {
            isBoxDrawing = TRUE;
            isCircleDrawing = FALSE;
            isBonobonoDrawing = FALSE;
            isRyanDrawing = FALSE;
            SetFocus(hWnd);
        }
        if ((HWND)lParam == circleButton.hWnd) {
            isCircleDrawing = TRUE;
            isBoxDrawing = FALSE;
            isBonobonoDrawing = FALSE;
            isRyanDrawing = FALSE;
            SetFocus(hWnd);
        }
        if ((HWND)lParam == bonobonoButton.hWnd) {
            isBonobonoDrawing = TRUE;
            isBoxDrawing = FALSE;
            isCircleDrawing = FALSE;  // »óÅÂ ÃÊ±âÈ­
            isRyanDrawing = FALSE;
            SetFocus(hWnd);
        }
        if ((HWND)lParam == ryanButton.hWnd) {
            isRyanDrawing = TRUE;
            isBoxDrawing = FALSE;
            isCircleDrawing = FALSE;
            isBonobonoDrawing = FALSE;
            SetFocus(hWnd);
        }

        break;

    case WM_LBUTTONDOWN:
    {
        startPoint.x = LOWORD(lParam);
        startPoint.y = HIWORD(lParam);
        SetCapture(hWnd);
        break;
    }

    case WM_MOUSEMOVE:
        if (wParam & MK_LBUTTON) {
            endPoint.x = LOWORD(lParam);
            endPoint.y = HIWORD(lParam);
            InvalidateRect(hWnd, &contentBox, FALSE);
        }
        break;

    case WM_LBUTTONUP:
        ReleaseCapture();
        break;

    case WM_KEYDOWN:
        if (wParam == VK_SPACE) {
            isSpacebarPressed = TRUE;
            InvalidateRect(hWnd, NULL, TRUE); // Redraw window to update eyes
        }
        break;

    case WM_KEYUP:
        if (wParam == VK_SPACE) {
            isSpacebarPressed = FALSE;
            InvalidateRect(hWnd, NULL, TRUE); // Redraw window to update eyes
        }
        break;



    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);

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
            HBRUSH bonobonoBrush = CreateSolidBrush(RGB(91, 155, 213));  // º¸³ëº¸³ë ¾ó±¼»ö
            SelectObject(hdc, bonobonoBrush);
            Ellipse(hdc, startPoint.x - radius, startPoint.y - radius, startPoint.x + radius, startPoint.y + radius);

            // º¸³ëº¸³ë ´«
            int eyeRadius = radius / 10;  // ´« Å©±â
            HBRUSH eyeBrush = CreateSolidBrush(RGB(0, 0, 0));  // ´« »ö
            SelectObject(hdc, eyeBrush);

            if (isSpacebarPressed) {
                // º¸³ëº¸³ë ´« Âô±ß
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
                // ¿ÞÂÊ ´«
                Ellipse(hdc, startPoint.x - radius * 2 / 3 - eyeRadius, startPoint.y - radius / 6 - eyeRadius, startPoint.x - radius * 2 / 3 + eyeRadius, startPoint.y - radius / 6 + eyeRadius);
                // ¿À¸¥ÂÊ ´«
                Ellipse(hdc, startPoint.x + radius * 2 / 3 - eyeRadius, startPoint.y - radius / 6 - eyeRadius, startPoint.x + radius * 2 / 3 + eyeRadius, startPoint.y - radius / 6 + eyeRadius);
            }

            // º¸³ëº¸³ë ÀÔ
            HBRUSH mouthBrush = CreateSolidBrush(RGB(217, 65, 197));
            HPEN mouthPen = CreatePen(PS_SOLID, 2, RGB(0, 0, 0));
            SelectObject(hdc, mouthBrush);
            SelectObject(hdc, mouthPen);
            BeginPath(hdc);
            Arc(hdc, startPoint.x - radius / 8, startPoint.y, startPoint.x + radius / 8, startPoint.y + 2 * radius / 3, startPoint.x, startPoint.y + radius / 3, startPoint.x, startPoint.y + radius / 3);  // Vertically
            EndPath(hdc);
            StrokeAndFillPath(hdc);

            // º¸³ëº¸³ë ¼ö¿°³ª´Â °÷
            int whiteCircleRadius = radius / 5;
            HBRUSH whiteCircleBrush = CreateSolidBrush(RGB(255, 255, 255));
            SelectObject(hdc, whiteCircleBrush);
            // ¿ÞÂÊ ¿øÀÇ Áß½É
            int leftCircleCenterX = startPoint.x - whiteCircleRadius;
            int leftCircleCenterY = startPoint.y;

            // ¿À¸¥ÂÊ ¿øÀÇ Áß½É
            int rightCircleCenterX = startPoint.x + whiteCircleRadius;
            int rightCircleCenterY = startPoint.y;

            Ellipse(hdc,
                leftCircleCenterX - whiteCircleRadius,
                leftCircleCenterY - whiteCircleRadius,
                leftCircleCenterX + whiteCircleRadius,
                leftCircleCenterY + whiteCircleRadius);  // ¿ÞÂÊ Èò»ö ¿ø

            Ellipse(hdc,
                rightCircleCenterX - whiteCircleRadius,
                rightCircleCenterY - whiteCircleRadius,
                rightCircleCenterX + whiteCircleRadius,
                rightCircleCenterY + whiteCircleRadius);  // ¿À¸¥ÂÊ Èò»ö ¿ø

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

            // º¸³ëº¸³ë ¼ö¿°
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
            HBRUSH ryanBrush = CreateSolidBrush(RGB(253, 170, 3));  // ¶óÀÌ¾ð ¾ó±¼»ö
            SelectObject(hdc, ryanBrush);
            Ellipse(hdc, startPoint.x - radius, startPoint.y - radius, startPoint.x + radius, startPoint.y + radius);

            // ¶óÀÌ¾ð ´«
            int eyeRadius = radius / 11;
            HBRUSH eyeBrush = CreateSolidBrush(RGB(0, 0, 0));
            SelectObject(hdc, eyeBrush);

            // Decrease this value to move the left eye closer to the center
            int eyeOffsetX = radius * 2 / 5; // was 2/3

            // Left eye
            Ellipse(hdc, startPoint.x - eyeOffsetX - eyeRadius, startPoint.y - radius / 10 - eyeRadius, startPoint.x - eyeOffsetX + eyeRadius, startPoint.y - radius / 10 + eyeRadius);

            // Right eye
            Ellipse(hdc, startPoint.x + eyeOffsetX - eyeRadius, startPoint.y - radius / 10 - eyeRadius, startPoint.x + eyeOffsetX + eyeRadius, startPoint.y - radius / 10 + eyeRadius);


            int whiteCircleRadius = radius / 9;
            HBRUSH whiteCircleBrush = CreateSolidBrush(RGB(255, 255, 255));
            SelectObject(hdc, whiteCircleBrush);

            // ¿ÞÂÊ ¿ø Áß½É
            int leftCircleCenterX = startPoint.x - whiteCircleRadius;
            int leftCircleCenterY = startPoint.y;
            // ¿À¸¥ÂÊ ¿ø Áß½É
            int rightCircleCenterX = startPoint.x + whiteCircleRadius;
            int rightCircleCenterY = startPoint.y;

            // ¿ÞÂÊ Èò»ö ¿ø
            Ellipse(hdc,
                leftCircleCenterX - whiteCircleRadius,
                leftCircleCenterY - whiteCircleRadius,
                leftCircleCenterX + whiteCircleRadius,
                leftCircleCenterY + whiteCircleRadius);
            // ¿À¸¥ÂÊ Èò»ö ¿ø
            Ellipse(hdc,
                rightCircleCenterX - whiteCircleRadius,
                rightCircleCenterY - whiteCircleRadius,
                rightCircleCenterX + whiteCircleRadius,
                rightCircleCenterY + whiteCircleRadius);

            DeleteObject(whiteCircleBrush);
            DeleteObject(ryanBrush);
            DeleteObject(eyeBrush);
        }

        DeleteObject(contentBrush);

        EndPaint(hWnd, &ps);
        return 0;
    }

    default:
        return DefWindowProc(hWnd, uMsg, wParam, lParam);
    }
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    WNDCLASSEX wc = { sizeof(WNDCLASSEX), CS_CLASSDC, WindowProc, 0L, 0L, GetModuleHandle(NULL), NULL, NULL, NULL, NULL, L"MyWindowClass", NULL };
    RegisterClassEx(&wc);

    HWND hWnd = CreateWindow(wc.lpszClassName, L"My Window", WS_OVERLAPPEDWINDOW & ~(WS_MAXIMIZEBOX | WS_SIZEBOX), 100, 100, 800, 480, NULL, NULL, hInstance, NULL);

    if (!hWnd) {
        return -1;
    }

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

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