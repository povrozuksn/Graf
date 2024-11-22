#include "TXLib.h"
#include <fstream>
#include <dirent.h>

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
    string category;
    bool visible;

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

void drawWorkSpace(int x, int y)
{
    txSetColor (TX_BLACK);
    txSetFillColor (TX_YELLOW);
    txRectangle (x, y, x+1290-300, y+690-100);
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

int get_w(string adress)
{
    FILE *f1 = fopen(adress.c_str(), "rb");
    unsigned char header[54];
    fread(header, sizeof(unsigned char), 54, f1);
    int w = *(int *)&header[18];
    return w;
}

int get_h(string adress)
{
    FILE *f1 = fopen(adress.c_str(), "rb");
    unsigned char header[54];
    fread(header, sizeof(unsigned char), 54, f1);
    int h = *(int *)&header[22];
    return h;
}

int ReadFromDir(string adressDir, Picture menu_pic[], int countFiles)
{
    DIR *dir;
    struct dirent *ent;
    int x = 10;
    int y = 100;
    if ((dir = opendir (adressDir.c_str())) != NULL)
    {
        while ((ent = readdir (dir)) != NULL)
        {
            if((string)ent->d_name != "." && (string)ent->d_name != "..")
            {
                menu_pic[countFiles].x = x;
                menu_pic[countFiles].y = y;
                menu_pic[countFiles].adress = adressDir + (string)ent->d_name;
                countFiles++;
                y+=100;
            }
        }
        closedir(dir);
    }
    return countFiles;
}

int main()
{
txCreateWindow (1300, 700);
txTextCursor (false);

    //количество кнопок
    int count_btn = 11;
    //кнопка сохранения
    int btn_save = count_btn-4;
    //кнопка загрузки
    int btn_load = count_btn-3;
    //кнопка справки
    int btn_help = count_btn-2;
    //кнопка выхода
    int btn_exit = count_btn-1;
    //количество картинок меню
    int count_pic = 0;
    //количество центральных картинок в рабочей области
    int nCentralPic = 0;

    char str[20];
    int vybor = -1;

    bool mouse_down = false;

    string PAGE = "work";

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
    btn[9] = {950, 55, 150, 30, "Справка", TX_LIGHTGREEN, ""};
    btn[10] = {1120, 55, 150, 30, "Выход", TX_LIGHTGREEN, ""};

    //создание массива картинок меню
    Picture menu_pic[100];

    count_pic = ReadFromDir("Pictures/Фруктовницы/", menu_pic, count_pic);
    count_pic = ReadFromDir("Pictures/Фрукты/", menu_pic, count_pic);
    count_pic = ReadFromDir("Pictures/Овощи/", menu_pic, count_pic);
    count_pic = ReadFromDir("Pictures/Ягоды/", menu_pic, count_pic);
    count_pic = ReadFromDir("Pictures/Грибы/", menu_pic, count_pic);
    count_pic = ReadFromDir("Pictures/Цветы/", menu_pic, count_pic);
    count_pic = ReadFromDir("Pictures/Вазы/", menu_pic, count_pic);

    for (int i=0; i<count_pic; i++)
    {
        menu_pic[i].visible = false;

        int pos1 = menu_pic[i].adress.find("/");
        int pos2 = menu_pic[i].adress.find("/", pos1+1);
        menu_pic[i].category = menu_pic[i].adress.substr(pos1+1, pos2 - (pos1+1));

        menu_pic[i].w = get_w(menu_pic[i].adress);
        menu_pic[i].h = get_h(menu_pic[i].adress);

        if(menu_pic[i].category == "Фруктовницы" || menu_pic[i].category == "Вазы")
        {
            menu_pic[i].w_scr = menu_pic[i].w/5;
            menu_pic[i].h_scr = menu_pic[i].h/5;
        }
        else
        {
            menu_pic[i].w_scr = menu_pic[i].w/2;
            menu_pic[i].h_scr = menu_pic[i].h/2;
        }

        menu_pic[i].image = txLoadImage(menu_pic[i].adress.c_str());

    }





    //создание массива картинок на рабочей области для проекта без замены центральных картиной в рабочей области
    Picture centr_pic[100];


    while(!btn[btn_exit].click())
    {
        txSetFillColor (TX_WHITE);
        txClear();

        txBegin();

        if(PAGE == "work")
        {
            //рабочая область
            drawWorkSpace(300, 100);
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
                                                    menu_pic[npic].category,
                                                    menu_pic[npic].visible
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
/*
            sprintf(str, "Кол.цент.картинок = %d", nCentralPic);
            txTextOut(10, 600, str);
            sprintf(str, "Выбор = %d", vybor);
            txTextOut(10, 650, str);
*/

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
                                                            menu_pic[i].category,
                                                            true
                                                        };
                            nCentralPic ++;
                        }
                    }


                }
                filein.close();

            }

            if(btn[btn_help].click())
            {
                PAGE = "help";
            }

        }


        if(PAGE == "help")
        {
            drawWorkSpace(150, 50);
            txSelectFont("Comic Sans MS", 50);
            txDrawText(150, 50, 1140, 100, "Справка");
            txSelectFont("Comic Sans MS", 35, 15, FW_BOLD, false, true, false);
            txDrawText(150, 100, 1140, 250, "Программа композиции натюрморта");
            txSelectFont("Comic Sans MS", 25);
            txDrawText(150, 250, 1140, 590, "С помощью данной программы Вы можете \n"
                                            "создавать различные композиции из предметов представленных категорий.\n"
                                            "Выбор категории предметов осуществляется в главном меню.\n"
                                            "Выбор предметов из выбранной категории осуществляется в боковом меню.\n"
                                            "После выбова конкретного предмета его изображение появляется в рабочей области,\n"
                                            "в которой его можно передвигать на нужнюю позицию при помощи мышки и стрелок клавиатуры.\n"
                                            "При ошибочном выборе предмет можно удалить из рабочей области клавишей 'Del'.\n"
                                            "Созданную композицию можно сохранить в файл - кнопка 'Сохранить',\n"
                                            "а также загрузить из ранее сохраненного файла - кнопка 'Загрузить'.");
            txTextOut(155, 595, "Назад - клавиша 'Esc'");

            if(GetAsyncKeyState (VK_ESCAPE))
            {
                PAGE = "work";
            }
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

