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

struct Picture
{
    int x;
    int y;
    HDC name;
    int w_scr;
    int h_scr;
    int w;
    int h;
    bool visible;

    void draw()
    {
        if(visible)
        {
            Win32::TransparentBlt (txDC(), x, y, w_scr, h_scr, name, 0, 0, w, h, TX_WHITE);
        }
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

    Button btn[5];
    btn[0] = {100, 10, 150, 40, "Вазы"};
    btn[1] = {300, 10, 150, 40, "Фрукты"};
    btn[2] = {500, 10, 150, 40, "Овощи"};
    btn[3] = {700, 10, 150, 40, "Ягоды"};
    btn[4] = {900, 10, 150, 40, "Грибы"};

    Picture pic[6];
    pic[0] = {10, 100, txLoadImage("Pictures/Ваза/Ваза1.bmp"), 80, 80, 400, 400, false};
    pic[1] = {10, 200, txLoadImage("Pictures/Ваза/Ваза2.bmp"), 80, 80, 400, 400, false};
    pic[2] = {10, 100, txLoadImage("Pictures/Фрукты/Апельсин.bmp"), 50, 50, 100, 100, false};
    pic[3] = {10, 200, txLoadImage("Pictures/Фрукты/Лимон.bmp"), 50, 50, 100, 100, false};
    pic[4] = {10, 100, txLoadImage("Pictures/Овощи/Огурец.bmp"), 50, 50, 100, 100, false};
    pic[5] = {10, 200, txLoadImage("Pictures/Овощи/Помидор.bmp"), 50, 50, 100, 100, false};


    while(!GetAsyncKeyState (VK_ESCAPE))
    {
        txSetFillColor (TX_BLACK);
        txClear();

        txBegin();

        drawWorkSpace();

        for(int i=0; i<5; i++)
        {
            btn[i].draw();
        }

        for(int i=0; i<6; i++)
        {
            pic[i].draw();
        }



        if(btn[0].click())
        {
            pic[0].visible = true;
            pic[1].visible = true;
            pic[2].visible = false;
            pic[3].visible = false;
            pic[4].visible = false;
            pic[5].visible = false;
        }

        if(btn[1].click())
        {
            pic[0].visible = false;
            pic[1].visible = false;
            pic[2].visible = true;
            pic[3].visible = true;
            pic[4].visible = false;
            pic[5].visible = false;
        }

        if(btn[2].click())
        {
            pic[0].visible = false;
            pic[1].visible = false;
            pic[2].visible = false;
            pic[3].visible = false;
            pic[4].visible = true;
            pic[5].visible = true;
        }




        txEnd();
        txSleep(10);

    }

    for(int i=0; i<6; i++)
    {
        txDeleteDC(pic[i].name);
    }

txDisableAutoPause();
return 0;
}

