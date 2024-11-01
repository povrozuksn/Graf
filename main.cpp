#include "TXLib.h"
#include <fstream>

using namespace std;

struct Button
{
   int x;
   int y;
   int w;
   int h;
   const char* text;
   COLORREF color;
   string category;

   void draw()
   {
        txSetColor (TX_BLACK);
        txSetFillColor (TX_GREY);
        Win32::RoundRect (txDC(), x+3, y+3, x+w+3, y+h+3, 60, 60);
        txSetColor (TX_BLACK);
        txSetFillColor (color);
        Win32::RoundRect (txDC(), x, y, x+w, y+h, 60, 60);
        txSetColor (TX_BLACK);
        txSelectFont("Comic Sans MS", 25);
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
    string adress;
    HDC image;
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
            Win32::TransparentBlt (txDC(), x, y, w_scr, h_scr, image, 0, 0, w, h, TX_WHITE);
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

string DialogFile(bool isSave)
{
    string filename = "";

    OPENFILENAME ofn = {0};
    TCHAR szFile[260]={0};
    // Initialize remaining fields of OPENFILENAME structure
    ZeroMemory(&ofn, sizeof(ofn));
    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = txWindow();
    ofn.lpstrFile = szFile;
    ofn.nMaxFile = sizeof(szFile);
    ofn.lpstrFilter = ("Text\0*.TXT\0");
    ofn.nFilterIndex = 1;
    ofn.lpstrFileTitle = NULL;
    ofn.nMaxFileTitle = 0;
    ofn.lpstrInitialDir = NULL;
    ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

    if(isSave)
    {
        if(GetSaveFileName(&ofn) == TRUE)
        {
            filename = ofn.lpstrFile;
            filename = filename + ".txt";
        }
    }
    else
    {
        if(GetOpenFileName(&ofn) == TRUE)
        {
            filename = ofn.lpstrFile;
        }
    }


    return filename;
}

int main()
{
txCreateWindow (1300, 700);
txTextCursor (false);

    //количество кнопок
    int count_btn = 10;
    //кнопка сохранения
    int btn_save = count_btn-3;
    //кнопка загрузки
    int btn_load = count_btn-2;
    //кнопка справки
    int btn_help = count_btn-1;
    //количество картинок меню
    int count_pic = 16;
    //количество центральных картинок в рабочей области
    int nCentralPic = 0;

    char str[20];
    int vybor = -1;

    bool mouse_down = false;

    //создание массива кнопок
    Button btn[count_btn];
    btn[0] = {100, 10, 150, 30, "Фруктовницы", TX_YELLOW, "Фруктовницы"};
    btn[1] = {270, 10, 150, 30, "Фрукты", TX_YELLOW, "Фрукты"};
    btn[2] = {440, 10, 150, 30, "Овощи", TX_YELLOW, "Овощи"};
    btn[3] = {610, 10, 150, 30, "Ягоды", TX_YELLOW, "Ягоды"};
    btn[4] = {780, 10, 150, 30, "Грибы", TX_YELLOW, "Грибы"};
    btn[5] = {950, 10, 150, 30, "Цветы", TX_YELLOW, "Цветы"};
    btn[6] = {1120, 10, 150, 30, "Вазы", TX_YELLOW, "Вазы"};
    btn[7] = {300, 55, 150, 30, "Сохранить", TX_LIGHTGREEN, ""};
    btn[8] = {470, 55, 150, 30, "Загрузить", TX_LIGHTGREEN, ""};
    btn[9] = {1120, 55, 150, 30, "Справка", TX_LIGHTGREEN, ""};

    //создание массива картинок меню
    Picture menu_pic[count_pic];
    menu_pic[0] = {10, 100, "Pictures/Фруктовницы/Фруктовница1.bmp", txLoadImage("Pictures/Фруктовницы/Фруктовница1.bmp"), 80, 80, 400, 400, false, "Фруктовницы"};
    menu_pic[1] = {10, 200, "Pictures/Фруктовницы/Фруктовница2.bmp", txLoadImage("Pictures/Фруктовницы/Фруктовница2.bmp"), 80, 80, 400, 400, false, "Фруктовницы"};
    menu_pic[2] = {10, 100, "Pictures/Фрукты/Апельсин.bmp", txLoadImage("Pictures/Фрукты/Апельсин.bmp"), 50, 50, 100, 100, false, "Фрукты"};
    menu_pic[3] = {10, 200, "Pictures/Фрукты/Лимон.bmp", txLoadImage("Pictures/Фрукты/Лимон.bmp"), 50, 50, 100, 100, false, "Фрукты"};
    menu_pic[4] = {10, 100, "Pictures/Овощи/Огурец.bmp", txLoadImage("Pictures/Овощи/Огурец.bmp"), 50, 50, 100, 100, false, "Овощи"};
    menu_pic[5] = {10, 200, "Pictures/Овощи/Помидор.bmp", txLoadImage("Pictures/Овощи/Помидор.bmp"), 50, 50, 100, 100, false, "Овощи"};
    menu_pic[6] = {10, 100, "Pictures/Ягоды/Клубника.bmp", txLoadImage("Pictures/Ягоды/Клубника.bmp"), 50, 50, 100, 100, false, "Ягоды"};
    menu_pic[7] = {10, 200, "Pictures/Ягоды/Малина.bmp", txLoadImage("Pictures/Ягоды/Малина.bmp"), 50, 50, 100, 100, false, "Ягоды"};
    menu_pic[8] = {10, 300, "Pictures/Ягоды/Черника.bmp", txLoadImage("Pictures/Ягоды/Черника.bmp"), 50, 50, 100, 100, false, "Ягоды"};
    menu_pic[9] = {10, 100, "Pictures/Грибы/Грибы1.bmp", txLoadImage("Pictures/Грибы/Грибы1.bmp"), 50, 50, 100, 100, false, "Грибы"};
    menu_pic[10] = {10, 200, "Pictures/Грибы/Грибы2.bmp", txLoadImage("Pictures/Грибы/Грибы2.bmp"), 50, 50, 100, 100, false, "Грибы"};
    menu_pic[11] = {10, 300, "Pictures/Грибы/Грибы3.bmp", txLoadImage("Pictures/Грибы/Грибы3.bmp"), 50, 50, 100, 100, false, "Грибы"};
    menu_pic[12] = {10, 100, "Pictures/Цветы/Цветы1.bmp", txLoadImage("Pictures/Цветы/Цветы1.bmp"), 50, 50, 100, 100, false, "Цветы"};
    menu_pic[13] = {10, 200, "Pictures/Цветы/Цветы2.bmp", txLoadImage("Pictures/Цветы/Цветы2.bmp"), 50, 50, 100, 100, false, "Цветы"};
    menu_pic[14] = {10, 100, "Pictures/Вазы/Ваза1.bmp", txLoadImage("Pictures/Вазы/Ваза1.bmp"), 80, 80, 400, 400, false, "Вазы"};
    menu_pic[15] = {10, 200, "Pictures/Вазы/Ваза2.bmp", txLoadImage("Pictures/Вазы/Ваза2.bmp"), 80, 80, 400, 400, false, "Вазы"};

    //создание массива картинок на рабочей области для проекта с заменой центральных картиной в рабочей области
    /*
    Picture centr_pic[count_pic];
    centr_pic[0] = {350, 150, txLoadImage("Pictures/Ваза/Ваза1.bmp"), 400, 400, 400, 400, false, "Вазы"};
    centr_pic[1] = {350, 150, txLoadImage("Pictures/Ваза/Ваза2.bmp"), 400, 400, 400, 400, false, "Вазы"};
    centr_pic[2] = {350, 150, txLoadImage("Pictures/Фрукты/Апельсин.bmp"), 100, 100, 100, 100, false, "Фрукты"};
    centr_pic[3] = {350, 150, txLoadImage("Pictures/Фрукты/Лимон.bmp"), 100, 100, 100, 100, false, "Фрукты"};
    centr_pic[4] = {350, 150, txLoadImage("Pictures/Овощи/Огурец.bmp"), 100, 100, 100, 100, false, "Овощи"};
    centr_pic[5] = {350, 150, txLoadImage("Pictures/Овощи/Помидор.bmp"), 100, 100, 100, 100, false, "Овощи"};
    centr_pic[6] = {350, 150, txLoadImage("Pictures/Ягоды/Клубника.bmp"), 100, 100, 100, 100, false, "Ягоды"};
    centr_pic[7] = {350, 150, txLoadImage("Pictures/Ягоды/Малина.bmp"), 100, 100, 100, 100, false, "Ягоды"};
    centr_pic[8] = {350, 150, txLoadImage("Pictures/Ягоды/Черника.bmp"), 100, 100, 100, 100, false, "Ягоды"};
    */

    //создание массива картинок на рабочей области для проекта без замены центральных картиной в рабочей области
    Picture centr_pic[100];


    while(!GetAsyncKeyState (VK_ESCAPE))
    {
        txSetFillColor (TX_WHITE);
        txClear();

        txBegin();
        //рабочая область
        drawWorkSpace();
        //рисование кнопок
        for(int i=0; i<count_btn; i++)
        {
            btn[i].draw();
        }
        //рисование картинок меню
        for(int i=0; i<count_pic; i++)
        {
            menu_pic[i].draw();
        }
        //рисование картинок в центре
        for(int i=0; i<nCentralPic; i++)
        {
            centr_pic[i].draw();
        }
        //условие видимости картинок меню в зависимости от нажатой кнопки
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


        //условие видимости картинок в центре в зависимости от нажатой картинки меню

        //Для замены центральный картинок на рабочей области
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

        //Без замены центральный картинок на рабочей области
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
                                                menu_pic[npic].adress,
                                                menu_pic[npic].image,
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

        //Выбор объекта в рабочей области
        for(int npic=0; npic<nCentralPic; npic++)
        {
            if(centr_pic[npic].click() && centr_pic[npic].visible)
            {
                vybor = npic;
                mouse_down = false;
            }
        }

        sprintf(str, "Кол.цент.картинок = %d", nCentralPic);
        txTextOut(10, 600, str);
        sprintf(str, "Выбор = %d", vybor);
        txTextOut(10, 650, str);

        //Передвижение объекта мышкой
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

        //Перемещение объекта клавиатурой
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

        //Удаление объекта
        if(vybor>=0 && GetAsyncKeyState (VK_DELETE))
        {
            centr_pic[vybor] = centr_pic[nCentralPic-1];
            nCentralPic--;
            vybor = -1;
            mouse_down = true;
        }

        //Сохранение композиции в файл
        if(btn[btn_save].click())
        {
            string filename =  DialogFile(true);

            ofstream fileout;               // поток для записи
            fileout.open(filename);      // открываем файл для записи
            if (fileout.is_open())
            {
                for(int i=0; i<nCentralPic; i++)
                {
                    fileout << centr_pic[i].x << endl;
                    fileout << centr_pic[i].y << endl;
                    fileout << centr_pic[i].adress << endl;
                    fileout << centr_pic[i].w_scr << endl;
                    fileout << centr_pic[i].h_scr << endl;
                }
            }
            fileout.close();
        }

        //Загрузка композиции из файла
        if(btn[btn_load].click())
        {

            string filename =  DialogFile(false);

            while(txMouseButtons() == 1)
            {
                txSleep(10);
            }

            for(int i=nCentralPic; i>0; i--)
            {
                centr_pic[nCentralPic] = centr_pic[nCentralPic-1];
                nCentralPic--;
                vybor = -1;
                mouse_down = true;
            }

            char buff[50];
            ifstream filein(filename);      // открываем файл для записи
            while(filein.good())
            {
                filein.getline(buff, 50);
                int x = atoi(buff);
                filein.getline(buff, 50);
                int y = atoi(buff);
                filein.getline(buff, 50);
                string adress = buff;
                filein.getline(buff, 50);
                int w_scr = atoi(buff);
                filein.getline(buff, 50);
                int h_scr = atoi(buff);

                for(int i=0; i<count_pic; i++)
                {
                    if(menu_pic[i].adress == adress)
                    {
                        centr_pic[nCentralPic] =    {   x,
                                                        y,
                                                        adress,
                                                        menu_pic[i].image,
                                                        w_scr,
                                                        h_scr,
                                                        menu_pic[i].w,
                                                        menu_pic[i].h,
                                                        true,
                                                        menu_pic[i].category
                                                    };
                        nCentralPic ++;
                    }
                }


            }
            filein.close();

        }

        if(btn[btn_help].click())
        {
            txCircle(500, 500, 50);
        }


        txEnd();
        txSleep(10);

    }

    for(int i=0; i<count_pic; i++)
    {
        txDeleteDC(menu_pic[i].image);
    }
    for(int i=0; i<nCentralPic; i++)
    {
        txDeleteDC(centr_pic[i].image);
    }

txDisableAutoPause();
return 0;
}

