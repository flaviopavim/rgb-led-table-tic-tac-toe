#include <windows.h>
#include <gl/gl.h>

char* title = "Mesa de LEDs RGB";
int width = 400; //largura da tela
int height = 600; //altura da tela
int squareSize = 40; //tamanho do bloco
int x = 20; //blocos em x
int y = 30; //blocos em y
int delay = 100; //tempo de refresh da tela

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
void EnableOpenGL(HWND hWnd, HDC *hDC, HGLRC *hRC);
void DisableOpenGL(HWND hWnd, HDC hDC, HGLRC hRC);

float map(float x, float in_min, float in_max, float out_min, float out_max) {
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

void pixel(int l, int t, char* hex) {
    glPointSize(1.0);
    glBegin(GL_POINTS);

    long number = (long) strtol(&hex[0], NULL, 16);
    int r = ((number >> 16) & 0xFF);
    int g = ((number >> 8) & 0xFF);
    int b = ((number) & 0xFF);

    glColor3f(map(r, 0, 255, 0, 1), map(g, 0, 255, 0, 1), map(b, 0, 255, 0, 1));
    glVertex3f(map(l, 1, width, -1, 1), map(t, 1, height, 1, -1), 0.0f);
    glEnd();
}

char* Cor[10][15]; //dar um jeito nesse array :/

void square(int xx, int yy, char* hex) {
    Cor[xx][yy] = hex;
    int x_ = (xx - 1) * squareSize;
    int y_ = (yy - 1) * squareSize;
    for (int a = 1 + x_; a <= squareSize + x_; a++) {
        for (int b = 1 + y_; b <= squareSize + y_; b++) {
            pixel(a, b, hex);
        }
    }
}

char* randColor() {
    int len = 6;
    char* s = new char[len];
    static const char alphanum[] =
            "0123456789"
            "abcdef";

    for (int i = 0; i < len; ++i) {
        s[i] = alphanum[rand() % (sizeof (alphanum) - 1)];
    }

    s[len] = 0;
    return s;
}

void randPixel() {
    int xx = rand() % x + 1; // Randomizing the number between 1-10.
    int yy = rand() % y + 1; // Randomizing the number between 1-15.
    square(xx, yy, randColor());
}


/****************************************************************************/
/****************************************************************************/
/****************************************************************************/

//tic tac toe

//controle
bool btq = false, btw = false, bte = false;
bool bta = false, bts = false, btd = false;
bool btz = false, btx = false, btc = false;

int player = 1;
int vencedor = 0;
char* color = "3300da";
char* colorCache[9] = {"", "", "", "", "", "", "", "", ""};
int count = 0;

void block(int n, char* c) {

    if (n == 1) {
        square(2, 4, c);
        square(2, 5, c);
        square(3, 4, c);
        square(3, 5, c);
    } else if (n == 2) {
        square(5, 4, c);
        square(5, 5, c);
        square(6, 4, c);
        square(6, 5, c);
    } else if (n == 3) {
        square(8, 4, c);
        square(8, 5, c);
        square(9, 4, c);
        square(9, 5, c);
    } else if (n == 4) {
        square(2, 7, c);
        square(2, 8, c);
        square(3, 7, c);
        square(3, 8, c);
    } else if (n == 5) {
        square(5, 7, c);
        square(5, 8, c);
        square(6, 7, c);
        square(6, 8, c);
    } else if (n == 6) {
        square(8, 7, c);
        square(8, 8, c);
        square(9, 7, c);
        square(9, 8, c);
    } else if (n == 7) {
        square(2, 10, c);
        square(2, 11, c);
        square(3, 10, c);
        square(3, 11, c);
    } else if (n == 8) {
        square(5, 10, c);
        square(5, 11, c);
        square(6, 10, c);
        square(6, 11, c);
    } else if (n == 9) {
        square(8, 10, c);
        square(8, 11, c);
        square(9, 10, c);
        square(9, 11, c);
    }

}

void ticTacToe() {
    //comanda o jogo

    if (vencedor == 0) {
        if (GetKeyState('Q') & 0x8000) {
            btq = true;
        }
        if (GetKeyState('W') & 0x8000) {
            btw = true;
        }
        if (GetKeyState('E') & 0x8000) {
            bte = true;
        }
        if (GetKeyState('A') & 0x8000) {
            bta = true;
        }
        if (GetKeyState('S') & 0x8000) {
            bts = true;
        }
        if (GetKeyState('D') & 0x8000) {
            btd = true;
        }
        if (GetKeyState('Z') & 0x8000) {
            btz = true;
        }
        if (GetKeyState('X') & 0x8000) {
            btx = true;
        }
        if (GetKeyState('C') & 0x8000) {
            btc = true;
        }

        //stage
        square(4, 4, "ffffff");
        square(4, 5, "ffffff");
        square(4, 6, "ffffff");
        square(4, 7, "ffffff");
        square(4, 8, "ffffff");
        square(4, 9, "ffffff");
        square(4, 10, "ffffff");
        square(4, 11, "ffffff");

        square(7, 4, "ffffff");
        square(7, 5, "ffffff");
        square(7, 6, "ffffff");
        square(7, 7, "ffffff");
        square(7, 8, "ffffff");
        square(7, 9, "ffffff");
        square(7, 10, "ffffff");
        square(7, 11, "ffffff");


        square(2, 6, "ffffff");
        square(3, 6, "ffffff");
        square(5, 6, "ffffff");
        square(6, 6, "ffffff");
        square(8, 6, "ffffff");
        square(9, 6, "ffffff");

        square(2, 9, "ffffff");
        square(3, 9, "ffffff");
        square(5, 9, "ffffff");
        square(6, 9, "ffffff");
        square(8, 9, "ffffff");
        square(9, 9, "ffffff");
        //stage

        if (btq && colorCache[0] == "") {
            if (player == 1) {
                player = 2;
                color = "da0000";
            } else {
                player = 1;
                color = "3300da";
            }
            colorCache[0] = color;
        }
        if (btw && colorCache[1] == "") {
            if (player == 1) {
                player = 2;
                color = "da0000";
            } else {
                player = 1;
                color = "3300da";
            }
            colorCache[1] = color;
        }
        if (bte && colorCache[2] == "") {
            if (player == 1) {
                player = 2;
                color = "da0000";
            } else {
                player = 1;
                color = "3300da";
            }
            colorCache[2] = color;
        }
        if (bta && colorCache[3] == "") {
            if (player == 1) {
                player = 2;
                color = "da0000";
            } else {
                player = 1;
                color = "3300da";
            }
            colorCache[3] = color;
        }
        if (bts && colorCache[4] == "") {
            if (player == 1) {
                player = 2;
                color = "da0000";
            } else {
                player = 1;
                color = "3300da";
            }
            colorCache[4] = color;
        }
        if (btd && colorCache[5] == "") {
            if (player == 1) {
                player = 2;
                color = "da0000";
            } else {
                player = 1;
                color = "3300da";
            }
            colorCache[5] = color;
        }
        if (btz && colorCache[6] == "") {
            if (player == 1) {
                player = 2;
                color = "da0000";
            } else {
                player = 1;
                color = "3300da";
            }
            colorCache[6] = color;
        }
        if (btx && colorCache[7] == "") {
            if (player == 1) {
                player = 2;
                color = "da0000";
            } else {
                player = 1;
                color = "3300da";
            }
            colorCache[7] = color;

        }
        if (btc && colorCache[8] == "") {
            if (player == 1) {
                player = 2;
                color = "da0000";
            } else {
                player = 1;
                color = "3300da";
            }
            colorCache[8] = color;
        }

        for (int i = 0; i <= 8; i++) {
            if (colorCache[i] != "") {
                block(i + 1, colorCache[i]);
            }
        }

        char* v = "da0000";
        if (
                (colorCache[0] == v && colorCache[1] == v && colorCache[2] == v) || //linha 1
                (colorCache[3] == v && colorCache[4] == v && colorCache[5] == v) || //linha 2
                (colorCache[6] == v && colorCache[7] == v && colorCache[8] == v) || //linha 3
                (colorCache[0] == v && colorCache[4] == v && colorCache[8] == v) || //diagonal 1
                (colorCache[2] == v && colorCache[4] == v && colorCache[6] == v) || //diagonal 2
                (colorCache[0] == v && colorCache[3] == v && colorCache[6] == v) || //coluna 1
                (colorCache[1] == v && colorCache[4] == v && colorCache[7] == v) || //coluna 2
                (colorCache[2] == v && colorCache[5] == v && colorCache[8] == v) //coluna 3
                ) {
            //vencedor 1
            vencedor = 1;
        }

        v = "3300da";
        if (
                (colorCache[0] == v && colorCache[1] == v && colorCache[2] == v) || //linha 1
                (colorCache[3] == v && colorCache[4] == v && colorCache[5] == v) || //linha 2
                (colorCache[6] == v && colorCache[7] == v && colorCache[8] == v) || //linha 3
                (colorCache[0] == v && colorCache[4] == v && colorCache[8] == v) || //diagonal 1
                (colorCache[2] == v && colorCache[4] == v && colorCache[6] == v) || //diagonal 2
                (colorCache[0] == v && colorCache[3] == v && colorCache[6] == v) || //coluna 1
                (colorCache[1] == v && colorCache[4] == v && colorCache[7] == v) || //coluna 2
                (colorCache[2] == v && colorCache[5] == v && colorCache[8] == v) //coluna 3
                ) {
            //vencedor 2
            vencedor = 2;
        }
        int countCache = 0;
        for (int i = 0; i <= 8; i++) {
            if (colorCache[i] != "") {
                countCache++;
            }
        }
        if (countCache == 9) {
            vencedor = 3;
        }
    } else {
        char* cl = "";
        if (vencedor == 1) {
            cl = "da0000";
        } else if (vencedor == 2) {
            cl = "3300da";
        } else if (vencedor == 3) {
            cl = "333333";
        }
        block(1, cl);
        block(2, cl);
        block(3, cl);
        block(4, cl);
        block(5, cl);
        block(6, cl);
        block(7, cl);
        block(8, cl);
        block(9, cl);
        count++;
        if (count > 10) {
            colorCache[0] = "";
            colorCache[1] = "";
            colorCache[2] = "";
            colorCache[3] = "";
            colorCache[4] = "";
            colorCache[5] = "";
            colorCache[6] = "";
            colorCache[7] = "";
            colorCache[8] = "";
            block(1, "000000");
            block(2, "000000");
            block(3, "000000");
            block(4, "000000");
            block(5, "000000");
            block(6, "000000");
            block(7, "000000");
            block(8, "000000");
            block(9, "000000");
            btq = false;
            btw = false;
            bte = false;
            bta = false;
            bts = false;
            btd = false;
            btz = false;
            btx = false;
            btc = false;
            vencedor = 0;
            count = 0;
        }
    }

}

/****************************************************************************/
/****************************************************************************/
/****************************************************************************/

//fun��o pra usar de forma interativa com a mesa de leds, aqui pode selecionar o que fazer na 'tela' 

void screen() {
    //for (int i=0; i<=150; i++) {
    //	randPixel();
    //}
    ticTacToe();
}

void refreshScreen(HDC hDC) {
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    screen();
    SwapBuffers(hDC);
    Sleep(delay);
}

int WINAPI WinMain(HINSTANCE hInstance,
        HINSTANCE hPrevInstance,
        LPSTR lpCmdLine,
        int iCmdShow) {
    WNDCLASS wc;
    HWND hWnd;
    HDC hDC;
    HGLRC hRC;
    MSG msg;
    BOOL bQuit = FALSE;
    float theta = 0.0f;
    wc.style = CS_OWNDC;
    wc.lpfnWndProc = WndProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = hInstance;
    wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH) GetStockObject(BLACK_BRUSH);
    wc.lpszMenuName = NULL;
    wc.lpszClassName = title;
    RegisterClass(&wc);
    hWnd = CreateWindow(
            title, title,
            WS_CAPTION | WS_POPUPWINDOW | WS_VISIBLE,
            400, 50, width, height,
            NULL, NULL, hInstance, NULL);
    EnableOpenGL(hWnd, &hDC, &hRC);
    while (!bQuit) {
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
            if (msg.message == WM_QUIT) {
                bQuit = TRUE;
            } else {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
        } else {
            refreshScreen(hDC);
        }
    }
    DisableOpenGL(hWnd, hDC, hRC);
    DestroyWindow(hWnd);
    return msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message,
        WPARAM wParam, LPARAM lParam) {
    switch (message) {
        case WM_CREATE:
            return 0;
        case WM_CLOSE:
            PostQuitMessage(0);
            return 0;
        case WM_DESTROY:
            return 0;
        case WM_KEYDOWN:
            switch (wParam) {
                case VK_ESCAPE:
                    PostQuitMessage(0);
                    return 0;
            }
            return 0;
        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
    }
}

void EnableOpenGL(HWND hWnd, HDC *hDC, HGLRC *hRC) {
    PIXELFORMATDESCRIPTOR pfd;
    int iFormat;
    *hDC = GetDC(hWnd);
    ZeroMemory(&pfd, sizeof (pfd));
    pfd.nSize = sizeof (pfd);
    pfd.nVersion = 1;
    pfd.dwFlags = PFD_DRAW_TO_WINDOW |
            PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
    pfd.iPixelType = PFD_TYPE_RGBA;
    pfd.cColorBits = 24;
    pfd.cDepthBits = 16;
    pfd.iLayerType = PFD_MAIN_PLANE;
    iFormat = ChoosePixelFormat(*hDC, &pfd);
    SetPixelFormat(*hDC, iFormat, &pfd);
    *hRC = wglCreateContext(*hDC);
    wglMakeCurrent(*hDC, *hRC);
}

void DisableOpenGL(HWND hWnd, HDC hDC, HGLRC hRC) {
    wglMakeCurrent(NULL, NULL);
    wglDeleteContext(hRC);
    ReleaseDC(hWnd, hDC);
}