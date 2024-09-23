#include "TXLib.h"

struct Button
{
   int x;
   int y;
   int w;
   int h;
   const char* text;

   void draw()
   {
        txSetColor (TX_WHITE);
        txSetFillColor (TX_GREY);
        Win32::RoundRect (txDC(), x+3, y+3, x+w+3, y+h+3, 60, 60);
        txSetColor (TX_WHITE);
        txSetFillColor (TX_YELLOW);
        Win32::RoundRect (txDC(), x, y, x+w, y+h, 60, 60);
        txSetColor (TX_BLACK);
        txSelectFont("Comic Sans MS", 30);
        txDrawText(x, y, x+w, y+h, text);
   }

   bool click()
   {
      return(   txMouseButtons() == 1 && txMouseX()>x &&  txMouseX()<x+w &&
                 txMouseY()>y && txMouseY()<y+h);
   }


};

void drawWorkSpace()
{
    txSetColor (TX_WHITE);
    txSetFillColor (TX_YELLOW);
    txRectangle (300, 100, 1290, 690);
}

int main()
{
txCreateWindow (1300, 700);
txTextCursor (false);

    Button btn1 = {100, 10, 150, 40, "Вазы"};
    Button btn2 = {300, 10, 150, 40, "Фрукты"};
    Button btn3 = {500, 10, 150, 40, "Овощи"};
    Button btn4 = {700, 10, 150, 40, "Ягоды"};

    HDC vaza1 = txLoadImage("Pictures/Ваза/Ваза1.bmp");
    HDC vaza2 = txLoadImage("Pictures/Ваза/Ваза2.bmp");

    HDC frukt1 = txLoadImage("Pictures/Фрукты/Апельсин.bmp");
    HDC frukt2 = txLoadImage("Pictures/Фрукты/Лимон.bmp");

    HDC ovosch1 = txLoadImage("Pictures/Овощи/Огурец.bmp");
    HDC ovosch2 = txLoadImage("Pictures/Овощи/Помидор.bmp");

    bool visibleVaza = false;
    bool visibleFrukt = false;
    bool visibleOvosch = false;


    while(!GetAsyncKeyState (VK_ESCAPE))
    {
        txSetFillColor (TX_BLACK);
        txClear();

        txBegin();

        drawWorkSpace();

        btn1.draw();
        btn2.draw();
        btn3.draw();
        btn4.draw();

        if(visibleVaza)
        {
            Win32::TransparentBlt (txDC(), 10, 100, 80, 80, vaza1, 0, 0, 400, 400, TX_WHITE);
            Win32::TransparentBlt (txDC(), 10, 200, 80, 80, vaza2, 0, 0, 400, 400, TX_WHITE);
        }

        if(visibleFrukt)
        {
            Win32::TransparentBlt (txDC(), 10, 100, 50, 50, frukt1, 0, 0, 100, 100, TX_WHITE);
            Win32::TransparentBlt (txDC(), 10, 200, 50, 50, frukt2, 0, 0, 100, 100, TX_WHITE);
        }

        if(visibleOvosch)
        {
            Win32::TransparentBlt (txDC(), 10, 100, 50, 50, ovosch1, 0, 0, 100, 100, TX_WHITE);
            Win32::TransparentBlt (txDC(), 10, 200, 50, 50, ovosch2, 0, 0, 100, 100, TX_WHITE);
        }


        if(btn1.click())
        {
            visibleVaza = true;
            visibleFrukt = false;
            visibleOvosch = false;
        }

        if(btn2.click())
        {
            visibleFrukt = true;
            visibleVaza = false;
            visibleOvosch = false;
        }

        if(btn3.click())
        {
            visibleFrukt = false;
            visibleVaza = false;
            visibleOvosch = true;
        }





        txEnd();
        txSleep(10);

    }

    txDeleteDC(vaza1);
    txDeleteDC(vaza2);

    txDeleteDC(frukt1);


txDisableAutoPause();
return 0;
}

