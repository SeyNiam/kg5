//
// Треугольная пирамида
//
// + Убрать лишние точки и линии из 4 для Макса
// + Залить на Гит
// - Научиться определять видимость
// - Сделать с пунктиром
// - Сделать с закраской
//  
//


#include <iostream>
#include <math.h>
#include "graphics.h"
#pragma comment(lib,"graphics.lib")

#define P 3.14
#define TEXTCOL 13
#define MAINCOL 11 
#define WHITE 15

using namespace std;

// отрисовка линии попиксельно
void line_DDA(float x1, float y1, float z1, float x2, float y2, float z2, COLORREF cColor) {
    // Учёт координаты z при отрисовке в двумерном пространстве
    x1 -= 0.5 * z1;
    y1 += 0.5 * z1;
    x2 -= 0.5 * z2;
    y2 += 0.5 * z2;

    // Целочисленные значения координат начала и конца отрезка, округлённые до ближайшего целого
    int iX1 = roundf(x1);
    int iY1 = roundf(y1);
    int iX2 = roundf(x2);
    int iY2 = roundf(y2);

    // Длина и высота линии
    int deltaX = abs(iX1 - iX2);
    int deltaY = abs(iY1 - iY2);

    // Считаем минимальное количество итераций, необходимое для отрисовки отрезка
    // Выбирая максимум из длины и высоты линии, обеспечиваем связность линии
    int length = max(deltaX, deltaY);

    // особый случай, на экране закрашивается ровно один пиксель
    if (length == 0) {
        putpixel(iX1, iY1, cColor);
        return;
    }
    // Вычисляем приращения на каждом шаге по осям абсцисс и ординат
    double dX = (x2 - x1) / length;
    double dY = (y2 - y1) / length;

    // Начальные значения
    double x = x1;
    double y = y1;

    // Основной цикл
    length++;
    while (length--) {
        x += dX;
        y += dY;
        putpixel(roundf(x), roundf(y), cColor);
    }
}

// класс для точек
class Point {
public:
    float x;
    float y;
    float z;
    char* name;
    void namePoint(char* name) {
        int tmpX = x - 0.5 * z;
        int tmpY = y + 0.5 * z;
        outtextxy(tmpX, tmpY, name);
    }
};

// класс фигуры
class Piramid {
public:
    Point A, B, C, D;
    char name_A[2] = "A";
    char name_B[2] = "B";
    char name_C[2] = "C";
    char name_D[2] = "D";
    int col = MAINCOL;

    // конструктор
    Piramid() {
        A.x = 10; A.y = 100; A.z = 0;
        A.name = name_A;
        B.x = 80; B.y = 100; B.z = 0;
        B.name = name_B;
        C.x = 40; C.y = 100; C.z = 40;
        C.name = name_C;
        D.x = 50; D.y = 50; D.z = 20;
        D.name = name_D;
        drawPiramid();
    }

    // отрисовка
    void drawPiramid() {
        // оси
        setcolor(WHITE);
        line(700, 350, 730, 350);
        line(700, 350, 700, 320);
        line(700, 350, 685, 365);

        char w[20] = "W - Up";
        char a[20] = "A - Left";
        char s[20] = "S - Down";
        char d[20] = "D - Right";
        char z[20] = "Z - Forward";
        char x[20] = "X - Backward";
        char qrf[30] = "Q, R, F - Counter clockwise";
        char etg[20] = "E, T, G - Clockwise";
        char plus[20] = "+ - Scale up";
        char minus[20] = "- - Scale down";
        char other[20] = "Any other - Exit";

        outtextxy(1140, 20, w);
        outtextxy(1140, 40, a);
        outtextxy(1140, 60, s);
        outtextxy(1140, 80, d);
        outtextxy(1140, 100, z);
        outtextxy(1140, 120, x);
        outtextxy(1140, 140, qrf);
        outtextxy(1140, 160, etg);
        outtextxy(1140, 180, plus);
        outtextxy(1140, 200, minus);
        outtextxy(1140, 220, other);

        setcolor(TEXTCOL);
        A.namePoint(A.name);
        B.namePoint(B.name);
        C.namePoint(C.name);
        D.namePoint(D.name);

        // Нижнее основание
        line_DDA(A.x, A.y, A.z, B.x, B.y, B.z, col); // линия 1
        line_DDA(B.x, B.y, B.z, C.x, C.y, C.z, col); // линия 2
        line_DDA(C.x, C.y, C.z, A.x, A.y, A.z, col); // линия 3
        
        // Боковые грани
        line_DDA(D.x, D.y, D.z, A.x, A.y, A.z, col); // линия 4
        line_DDA(D.x, D.y, D.z, B.x, B.y, B.z, col); // линия 5
        line_DDA(D.x, D.y, D.z, C.x, C.y, C.z, col); // линия 6

    }

    // пермещение
    void moveX(float amt) {
        A.x += amt;
        B.x += amt;
        C.x += amt;
        D.x += amt;
    }
    void moveY(float amt) {
        A.y += amt;
        B.y += amt;
        C.y += amt;
        D.y += amt;
    }
    void moveZ(float amt) {
        A.z += amt;
        B.z += amt;
        C.z += amt;
        D.z += amt;
    }

    // поворот одной точки вокруг z
    Point rotDotZ(int u, float ang, Point Cen, Point L) {
        L.x = L.x - Cen.x; // расстояние от а до центра по х
        L.y = L.y - Cen.y; // по у

        float tmpX = L.x * cos(ang) + L.y * sin(ang);
        float tmpY = -L.x * sin(ang) + L.y * cos(ang);
        L.x = tmpX + Cen.x;
        L.y = tmpY + Cen.y;

        return L;
    }
    // поворот фигуры вокруг z
    void rotateZ(int u) { // u = -1 по часовой, u = 1 против
        float ang = u * 0.05; // угол поворота

        Point Cen; // точка центра 
        Cen.x = (A.x + B.x + C.x + D.x) / 4;
        Cen.y = (A.y + B.y + C.y + D.y) / 4;
        Cen.z = (A.z + B.z + C.z + D.z) / 4;

        A = rotDotZ(u, ang, Cen, A);
        B = rotDotZ(u, ang, Cen, B);
        C = rotDotZ(u, ang, Cen, C);
        D = rotDotZ(u, ang, Cen, D);
    }

    // поворот одной точки вокруг y
    Point rotDotY(int u, float ang, Point Cen, Point L) {
        L.x = L.x - Cen.x; // расстояние от а до центра по y
        L.z = L.z - Cen.z; // по z

        float tmpX = L.x * cos(ang) + L.z * sin(ang);
        float tmpZ = -L.x * sin(ang) + L.z * cos(ang);
        L.x = tmpX + Cen.x;
        L.z = tmpZ + Cen.z;

        return L;
    }
    // поворот фигуры вокруг y
    void rotateY(int u) { // u = -1 по часовой, u = 1 против
        float ang = u * 0.05; // угол поворота

        Point Cen; // точка центра 
        Cen.x = (A.x + B.x + C.x + D.x) / 4;
        Cen.y = (A.y + B.y + C.y + D.y) / 4;
        Cen.z = (A.z + B.z + C.z + D.z) / 4;

        A = rotDotY(u, ang, Cen, A);
        B = rotDotY(u, ang, Cen, B);
        C = rotDotY(u, ang, Cen, C);
        D = rotDotY(u, ang, Cen, D);
    }

    // поворот одной точки вокруг x
    Point rotDotX(int u, float ang, Point Cen, Point L) {
        L.y = L.y - Cen.y; // расстояние от а до центра по y
        L.z = L.z - Cen.z; // по z

        float tmpY = L.y * cos(ang) + L.z * sin(ang);
        float tmpZ = -L.y * sin(ang) + L.z * cos(ang);
        L.y = tmpY + Cen.y;
        L.z = tmpZ + Cen.z;

        return L;
    }
    // поворот фигуры вокруг x
    void rotateX(int u) { // u = -1 по часовой, u = 1 против
        float ang = u * 0.05; // угол поворота

        Point Cen; // точка центра
        Cen.x = (A.x + B.x + C.x + D.x) / 4;
        Cen.y = (A.y + B.y + C.y + D.y) / 4;
        Cen.z = (A.z + B.z + C.z + D.z) / 4;

        A = rotDotX(u, ang, Cen, A);
        B = rotDotX(u, ang, Cen, B);
        C = rotDotX(u, ang, Cen, C);
        D = rotDotX(u, ang, Cen, D);
    }


    // масштабирование одной точки
    Point dotScale(float e, Point Cen, Point L) {
        // L.x
        float xe = (Cen.x + L.x) / 2;
        float lx = Cen.x - L.x;
        lx = lx * e;
        L.x = xe - lx / 2;
        // L.y
        float ye = (Cen.y + L.y) / 2;
        float ly = Cen.y - L.y;
        ly = ly * e;
        L.y = ye - ly / 2;
        // L.z
        float ze = (Cen.z + L.z) / 2;
        float lz = Cen.z - L.z;
        lz = lz * e;
        L.z = ze - lz / 2;

        return L;
    }
    // масштабирование всей фигуры
    void scale(float e) {
        Point Cen; // точка центра 
        Cen.x = (A.x + B.x + C.x + D.x) / 4;
        Cen.y = (A.y + B.y + C.y + D.y) / 4;
        Cen.z = (A.z + B.z + C.z + D.z) / 4;

        if (((abs(A.x - Cen.x) >= 1 && abs(A.y - Cen.y) >= 1 && abs(A.z - Cen.z) >= 1) &&
            (abs(B.x - Cen.x) >= 1 && abs(B.y - Cen.y) >= 1 && abs(B.z - Cen.z) >= 1) &&
            (abs(C.x - Cen.x) >= 1 && abs(C.y - Cen.y) >= 1 && abs(C.z - Cen.z) >= 1) &&
            (abs(D.x - Cen.x) >= 1 && abs(D.y - Cen.y) >= 1 && abs(D.z - Cen.z) >= 1)
            ) || e > 1) { // предотвращение сжатия в точку

            A = dotScale(e, Cen, A);
            B = dotScale(e, Cen, B);
            C = dotScale(e, Cen, C);
            D = dotScale(e, Cen, D);
        }

    }
};

int main() {
    initwindow(1400, 700); // создаём консольное окно 1400 на 700
    Piramid Tri; // создание фигуры

    // управление
    int i = 1; // условие выхода
    while (i) {
        switch (getch()) {
        case 'w':
            cout << 'w' << endl;
            Tri.moveY(-10); // вверх
            break;
        case 'a':
            cout << 'a' << endl;
            Tri.moveX(-10); // влево
            break;
        case 's':
            cout << 's' << endl;
            Tri.moveY(10); // вниз
            break;
        case 'd':
            cout << 'd' << endl;
            Tri.moveX(10); // вправо
            break;
        case 'x':
            cout << 'x' << endl;
            Tri.moveZ(-10); // назад
            Tri.scale(0.9);
            break;
        case 'z':
            cout << 'z' << endl;
            Tri.moveZ(10); // вперёд
            Tri.scale(1.1);
            break;

            // вокруг z
        case 'q':
            cout << 'q' << endl;
            Tri.rotateZ(1); // против часовой
            break;
        case 'e':
            cout << 'e' << endl;
            Tri.rotateZ(-1); // по часовой
            break;
            // вокруг y
        case 'r':
            cout << 'r' << endl;
            Tri.rotateY(1); // против часовой
            break;
        case 't':
            cout << 't' << endl;
            Tri.rotateY(-1); // по часовой
            break;
            // вокруг x
        case 'f':
            cout << 'f' << endl;
            Tri.rotateX(1); // против часовой
            break;
        case 'g':
            cout << 'g' << endl;
            Tri.rotateX(-1); // по часовой
            break;

        case '=':
            cout << '+' << endl;
            Tri.scale(1.5); // увеличение
            break;
        case '-':
            cout << '-' << endl;
            Tri.scale(0.5); // уменьшение
            break;
        default:
            cout << "default -> exit" << endl;
            i = 0;
            break;
        }
        cleardevice(); // отичстка экрана
        Tri.drawPiramid(); // перерисовка фигуры
    }

    getch(); // чтение одного символа с клавиатуры
    closegraph(); // освобождает всю память, выделенную под графическую систему, затем восстанавливает экран в режим, который был до вызова initwindow

    return 0;
}
