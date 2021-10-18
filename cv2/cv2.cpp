#include <iostream>
#include <windows.h>
#include <math.h>

int common_divisor(int x, int y) {
    int tmp;
    if (x <= y) {
        tmp = x;
    }
    else {
        tmp = y;
    }

    do {
        if (x % tmp == 0 && y % tmp == 0)
            break;
        tmp--;
    } while (true);


    return tmp;
}

void draw_and_raster(POINT start, POINT end, int krok_x, int krok_y, int znam_x, int znam_y, HDC hd) {
    COLORREF color_a = RGB(0, 0, 255);
    COLORREF color_b = RGB(0, 255, 0);

    int x = start.x;
    int y = start.y;

    do {
        if ((krok_x != 0 && krok_y != 0) && ((x >= start.x && x <= end.x) || (x <= start.x && x >= end.x))) {
            x += znam_x;
            if (x % abs(krok_x) == 0) {
                SetPixel(hd, x + 1, y, color_b);
                y += znam_y;
            }
        }
        else {
            if (krok_x != 0 && krok_y == 0 && ((x >= start.x && x <= end.x) || (x <= start.x && x >= end.x))) {
                x += znam_x;
            }
            if (krok_x == 0 && krok_y != 0 && ((x >= start.x && x <= end.x) || (x <= start.x && x >= end.x))) {
                y += znam_y;
            }
        }

        SetPixel(hd, x, y, color_a);
    } while (true);
}

void data_prepair(POINT pt_start, POINT pt_end, HDC hd) {
    int dx, dy, pomer_x, pomer_y, tau, tau_n, nasobitel_x, nasobitel_y;
    double d;

    if (pt_start.x >= pt_end.x) {
        dx = pt_start.x - pt_end.x;
        nasobitel_x = -1;
    }
    else {
        dx = pt_end.x - pt_start.x;
        nasobitel_x = 1;
    }

    if (pt_start.y >= pt_end.y) {
        dy = pt_start.y - pt_end.y;
        nasobitel_y = -1;
    }
    else {
        dy = pt_end.y - pt_start.y;
        nasobitel_y = 1;
    }

    d = tau = tau_n = 0;
    //d = sqrt(dy * dy + dx + dx);
    //tau = int(round((d / dx) * (180.0 / 3.141592653589793238463)));
    //tau_n = 90 - tau;

    int tmp, s = 1;
    //pomer_x = tau;
    //pomer_y = tau_n;
    pomer_x = dx;
    pomer_y = dy;
    if (pomer_x != 0 && pomer_y != 0) {
        do {
            tmp = common_divisor(pomer_x, pomer_y);
            if (tmp >= 1) {
                s = tmp;
                pomer_x /= s;
                pomer_y /= s;
            }
            else {
                break;
            }
        } while (tmp != 1);
    }

    draw_and_raster(pt_start, pt_end, pomer_x * nasobitel_x, pomer_y * nasobitel_y, nasobitel_x, nasobitel_y, hd);
}

void do_circle(HDC hd) {

}

void draw_anyline(HDC hd) {
    POINT pt_start;
    pt_start.x = rand() % 499 + 1;
    pt_start.y = rand() % 499 + 1;
    //pt_start.x = 0;
    //pt_start.y = 100;

    POINT pt_end;
    pt_end.x = rand() % 499 + 1;
    pt_end.y = rand() % 499 + 1;
    //pt_end.x = pt_start.x + rand() % 499 + 1;
    //pt_end.y = pt_start.y + rand() % 499 + 1;
    //pt_end.x = 0;
    //pt_end.y = 100;

    std::cout << "start x:" << pt_start.x << " y:" << pt_start.y << std::endl;
    std::cout << "end x:" << pt_end.x << " y:" << pt_end.y << std::endl;

    data_prepair(pt_start, pt_end, hd);
}

void draw_line_45deg(HDC hd) {
    COLORREF color_a = RGB(0, 0, 255);
    COLORREF color_b = RGB(0, 0, 255);

    POINT pt_start;
    pt_start.x = 0;
    pt_start.y = 0;

    POINT pt_end;
    pt_end.x = 500;
    pt_end.y = pt_end.x;

    std::cout << "start x:" << pt_start.x << " y:" << pt_start.y << std::endl;
    std::cout << "end x:" << pt_end.x << " y:" << pt_end.y << std::endl;

    int x = pt_start.x;
    int y = pt_start.y;
    do {
        if ((y >= pt_start.y && y <= pt_end.y) || (x >= pt_start.x && x <= pt_end.x)) {
            if (x != pt_end.x) {
                x++;
            }
            if (y != pt_end.y) {
                y++;
            }
        }
        SetPixel(hd, x, y, color_a);
        SetPixel(hd, x + 1, y, color_b);

    } while (true);
}

int main()
{

    HWND handle = GetConsoleWindow();
    if (handle == NULL)
        exit(0);
    HDC hdc = GetDC(handle);

    //draw_line_45deg(hdc);
    draw_anyline(hdc);
    //do_circle(hdc);
    
    return 0;
}
