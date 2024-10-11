#include "TXLib.h"

struct Button
{
   int x;
   int y;
   int w;
   int h;
   const char* text;
   string category;

   void draw()
   {
        txSetColor (TX_BLACK);
        txSetFillColor (TX_GREY);
        Win32::RoundRect (txDC(), x+3, y+3, x+w+3, y+h+3, 60, 60);
        txSetColor (TX_BLACK);
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
    string category;

    void draw()
    {
        if(visible)
        {
            Win32::TransparentBlt (txDC(), x, y, w_scr, h_scr, name, 0, 0, w, h, TX_WHITE);
        }
    }

    bool click()
    {
        return(   txMouseButtons() == 1 && txMouseX()>x &&  txMouseX()<x+w_scr &&
                 txMouseY()>y && txMouseY()<y+h_scr);
    }
};

void drawWorkSpace()
{
    txSetColor (TX_BLACK);
    txSetFillColor (TX_YELLOW);
    txRectangle (300, 100, 1290, 690);
}

int main()
{
txCreateWindow (1300, 700);
txTextCursor (false);

    //���������� ������
    int count_btn = 6;
    //���������� �������� ����
    int count_pic = 9;
    //���������� ������������ �������� � ������� �������
    int nCentralPic = 0;

    char str[20];
    int vybor = -1;

    bool mouse_down = false;

    //�������� ������� ������
    Button btn[count_btn];
    btn[0] = {100, 10, 150, 30, "����", "����"};
    btn[1] = {270, 10, 150, 30, "������", "������"};
    btn[2] = {440, 10, 150, 30, "�����", "�����"};
    btn[3] = {610, 10, 150, 30, "�����", "�����"};
    btn[4] = {780, 10, 150, 30, "�����", "�����"};
    btn[5] = {950, 10, 150, 30, "�����", "�����"};

    //�������� ������� �������� ����
    Picture menu_pic[count_pic];
    menu_pic[0] = {10, 100, txLoadImage("Pictures/����/����1.bmp"), 80, 80, 400, 400, false, "����"};
    menu_pic[1] = {10, 200, txLoadImage("Pictures/����/����2.bmp"), 80, 80, 400, 400, false, "����"};
    menu_pic[2] = {10, 100, txLoadImage("Pictures/������/��������.bmp"), 50, 50, 100, 100, false, "������"};
    menu_pic[3] = {10, 200, txLoadImage("Pictures/������/�����.bmp"), 50, 50, 100, 100, false, "������"};
    menu_pic[4] = {10, 100, txLoadImage("Pictures/�����/������.bmp"), 50, 50, 100, 100, false, "�����"};
    menu_pic[5] = {10, 200, txLoadImage("Pictures/�����/�������.bmp"), 50, 50, 100, 100, false, "�����"};
    menu_pic[6] = {10, 100, txLoadImage("Pictures/�����/��������.bmp"), 50, 50, 100, 100, false, "�����"};
    menu_pic[7] = {10, 200, txLoadImage("Pictures/�����/������.bmp"), 50, 50, 100, 100, false, "�����"};
    menu_pic[8] = {10, 300, txLoadImage("Pictures/�����/�������.bmp"), 50, 50, 100, 100, false, "�����"};

    //�������� ������� �������� �� ������� ������� ��� ������� � ������� ����������� �������� � ������� �������
    /*
    Picture centr_pic[count_pic];
    centr_pic[0] = {350, 150, txLoadImage("Pictures/����/����1.bmp"), 400, 400, 400, 400, false, "����"};
    centr_pic[1] = {350, 150, txLoadImage("Pictures/����/����2.bmp"), 400, 400, 400, 400, false, "����"};
    centr_pic[2] = {350, 150, txLoadImage("Pictures/������/��������.bmp"), 100, 100, 100, 100, false, "������"};
    centr_pic[3] = {350, 150, txLoadImage("Pictures/������/�����.bmp"), 100, 100, 100, 100, false, "������"};
    centr_pic[4] = {350, 150, txLoadImage("Pictures/�����/������.bmp"), 100, 100, 100, 100, false, "�����"};
    centr_pic[5] = {350, 150, txLoadImage("Pictures/�����/�������.bmp"), 100, 100, 100, 100, false, "�����"};
    centr_pic[6] = {350, 150, txLoadImage("Pictures/�����/��������.bmp"), 100, 100, 100, 100, false, "�����"};
    centr_pic[7] = {350, 150, txLoadImage("Pictures/�����/������.bmp"), 100, 100, 100, 100, false, "�����"};
    centr_pic[8] = {350, 150, txLoadImage("Pictures/�����/�������.bmp"), 100, 100, 100, 100, false, "�����"};
    */

    //�������� ������� �������� �� ������� ������� ��� ������� ��� ������ ����������� �������� � ������� �������
    Picture centr_pic[100];


    while(!GetAsyncKeyState (VK_ESCAPE))
    {
        txSetFillColor (TX_WHITE);
        txClear();

        txBegin();
        //������� �������
        drawWorkSpace();
        //��������� ������
        for(int i=0; i<count_btn; i++)
        {
            btn[i].draw();
        }
        //��������� �������� ����
        for(int i=0; i<count_pic; i++)
        {
            menu_pic[i].draw();
        }
        //��������� �������� � ������
        for(int i=0; i<nCentralPic; i++)
        {
            centr_pic[i].draw();
        }
        //������� ��������� �������� ���� � ����������� �� ������� ������
        for(int nbutton=0; nbutton<count_btn; nbutton++)
        {
            if(btn[nbutton].click())
            {
                for(int npic=0; npic<count_pic; npic++)
                {
                    menu_pic[npic].visible = false;
                    if(menu_pic[npic].category == btn[nbutton].category)
                    {
                        menu_pic[npic].visible = true;
                    }
                }

            }
        }


        //������� ��������� �������� � ������ � ����������� �� ������� �������� ����

        //��� ������ ����������� �������� �� ������� �������
/*
        for(int npic=0; npic<count_pic; npic++)
        {
            if(menu_pic[npic].click() && menu_pic[npic].visible)
            {
                for(int npic1=0; npic1<count_pic; npic1++)
                {
                    if(centr_pic[npic1].category==centr_pic[npic].category)
                    {
                        centr_pic[npic1].visible = false;
                    }
                }
                centr_pic[npic].visible = !centr_pic[npic].visible;
            }
        }
 */

        //��� ������ ����������� �������� �� ������� �������
        for(int npic=0; npic<count_pic; npic++)
        {
            if(menu_pic[npic].click() && menu_pic[npic].visible)
            {
                while(txMouseButtons() == 1)
                {
                    txSleep(10);
                }

                centr_pic[nCentralPic] =    {   350,
                                                150,
                                                menu_pic[npic].name,
                                                menu_pic[npic].w,
                                                menu_pic[npic].h,
                                                menu_pic[npic].w,
                                                menu_pic[npic].h,
                                                menu_pic[npic].visible,
                                                menu_pic[npic].category
                                            };

              nCentralPic ++;
            }
        }

        //����� ������� � ������� �������
        for(int npic=0; npic<nCentralPic; npic++)
        {
            if(centr_pic[npic].click() && centr_pic[npic].visible)
            {
                vybor = npic;
                mouse_down = false;
            }
        }
        /*
        sprintf(str, "���.����.�������� = %d", nCentralPic);
        txTextOut(10, 600, str);
        sprintf(str, "����� = %d", vybor);
        txTextOut(10, 650, str);
        */
        //������������ ������� ������
        if(vybor>=0)
        {
            if(txMouseButtons() == 1 && !mouse_down)
            {
               centr_pic[vybor].x = txMouseX() - centr_pic[vybor].w_scr/2;
               centr_pic[vybor].y = txMouseY() - centr_pic[vybor].h_scr/2;
            }
            else
            {
                if(txMouseButtons() != 1)
                {
                    mouse_down = true;
                }
            }
        }

        //����������� ������� �����������
        if(vybor>=0)
        {
             if(GetAsyncKeyState (VK_UP))
             {
                centr_pic[vybor].y -= 5;
             }
             if(GetAsyncKeyState (VK_DOWN))
             {
                centr_pic[vybor].y += 5;
             }
             if(GetAsyncKeyState (VK_RIGHT))
             {
                centr_pic[vybor].x += 5;
             }
             if(GetAsyncKeyState (VK_LEFT))
             {
                centr_pic[vybor].x -= 5;
             }
             if(GetAsyncKeyState (VK_OEM_PLUS))
             {
                centr_pic[vybor].w_scr = centr_pic[vybor].w_scr*1.05;
                centr_pic[vybor].h_scr = centr_pic[vybor].h_scr*1.05;
                if(centr_pic[vybor].w_scr>600)
                {
                    centr_pic[vybor].w_scr=600;
                    centr_pic[vybor].h_scr=600;
                }
             }
             if(GetAsyncKeyState (VK_OEM_MINUS))
             {
                centr_pic[vybor].w_scr = centr_pic[vybor].w_scr*0.95;
                centr_pic[vybor].h_scr = centr_pic[vybor].h_scr*0.95;
                if(centr_pic[vybor].w_scr<50)
                {
                    centr_pic[vybor].w_scr=50;
                    centr_pic[vybor].h_scr=50;
                }
             }
        }

        //�������� �������
        if(vybor>=0 && GetAsyncKeyState (VK_DELETE))
        {
            centr_pic[vybor] = centr_pic[nCentralPic-1];
            nCentralPic--;
            vybor = -1;
            mouse_down = true;
        }

        txEnd();
        txSleep(10);

    }

    for(int i=0; i<count_pic; i++)
    {
        txDeleteDC(menu_pic[i].name);
    }
    for(int i=0; i<nCentralPic; i++)
    {
        txDeleteDC(centr_pic[i].name);
    }

txDisableAutoPause();
return 0;
}

