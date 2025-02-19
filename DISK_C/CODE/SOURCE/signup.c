#include "signup.h"
#include "public.h"
#include "logfunc.h"

void signup_bkpaint(int language)
{
    setbkcolor(WHITE);
    cleardevice();
    clrmous(MouseX,MouseY);

    if(language == ENGLISH)
    {
        setcolor(BLUE);
        settextstyle(DEFAULT_FONT   , HORIZ_DIR,3);
        outtextxy(70, 100, "Please sign up here...");
    }
    else if(language == CHINESE)
    {
        puthz(80,75,"请在此处注册",48,48,BLUE);
    }

    if(language == ENGLISH)
    {
        setcolor(DARKGRAY);
        settextstyle(DEFAULT_FONT   , HORIZ_DIR,2);
        outtextxy(80, 170, "user     :");
        outtextxy(80, 240, "password :");
    }
    else if(language == CHINESE)
    {
        puthz(120,165,"用户名",32,32,DARKGRAY);
        puthz(135,235,"密码",32,32,DARKGRAY);
    }

    printbox(255,155,560,205,DARKGRAY,2,5,5);
    printbox(255,225,560,275,DARKGRAY,2,5,5);

    printbox(320-40,300,320+40,300+40,DARKGRAY,2,5,5);
    setcolor(DARKGRAY);
    settextstyle(DEFAULT_FONT   , HORIZ_DIR,2);
    outtextxy(306, 312, "OK");

    if(language == ENGLISH)
    {
        settextstyle(DEFAULT_FONT , HORIZ_DIR , 1);
        outtextxy(270,400,"---->RULE<----");
    }
    else if(language == CHINESE)
    {
        puthz(300,395,"注册规则",16,16,DARKGRAY);
    }

    back_button(PAINT);

    put_flower(105,425,5,CYAN);
    put_flower(155,425,5,GREEN);
    put_flower(515,425,10,BLUE);
}

int signup_page(int language)
{
    int place=0;
    int state1=0;//用户名
    int state2=0;//密码
    int num;
    INFO *user = (INFO *)malloc(sizeof(INFO));
    if(user != NULL) {
        memset(user,0,sizeof(INFO));
    }
    signup_bkpaint(language);
    mouseinit();

    while(1)
    {
        newmouse(&MouseX, &MouseY, &press);

        if( mouse_press(595,5,630,40)==2 )
        {
            MouseS = 1;
            if( place==0 ) 
            {
                place=2;
                back_button(LIGHT);
            }
        }
        else if( mouse_press(595,5,630,40)==1 )//跳转login页面
        {
            free(user);
            cleardevice();
            return LOGIN;
        }
        else if( mouse_press(285,315,350,340)==2 )//ok未按下
        {
            if(place == 0)
            {
                MouseS = 1;
                place = 2;
                ok_button_light();
            }
        }
        else if( mouse_press(285,315,350,340)==1 )//ok按下
        {
            if( user->name[0]=='\0' || user->password[0]=='\0') continue;
            
            if( userinfo_input(user, &state1, &state2,language) ) 
            {
                free(user);
                user=NULL;
                return LOGIN;
            }
        }
        else if( mouse_press(255,155,560,205)==2 )//用户名输入框未按
        {
            if(place==0)
            {
                MouseS = 2;
                place = 4;//用户名输入框(255,155,560,205)
            }
        }
        else if( mouse_press(255,155,560,205)==1 )//用户名输入框按下
        {
            temp_input(user->name , 266,170,17,16,20,WHITE,2);
        }
        else if( mouse_press(255,225,560,275)==2 )//密码输入框未按
        {
            if(place==0)
            {
                MouseS = 2;
                place = 5;//密码输入框(255,225,560,275)
            }
        }
        else if( mouse_press(255,225,560,275)==1 )//密码输入框按下
        {
            if( user->name[0] == '\0' ) continue;
            temp_input(user->password ,266,240,17,16,20,WHITE,2);
        }
        else if(mouse_press(270,390,380,410)==2)
        {
            if(place==0)
            {
                MouseS = 1;
                place = 6;
                num = 1;
                clrmous(MouseX,MouseY);
                if(language == ENGLISH)
                {       
                    setcolor(CYAN);
                    settextstyle(DEFAULT_FONT , HORIZ_DIR , 1);
                    outtextxy(270,400,"---->RULE<----");
                }
                else if(language == CHINESE)
                {
                    puthz(300,395,"注册规则",16,16,CYAN);
                }
            }
        }
        else if(mouse_press(270,390,380,410)==1)
        {
            clrmous(MouseX,MouseY);
            show_rule();
        }
        else {
            if(place!=0)
            {
                MouseS=0;
                place=0;
                ok_button_recover();
                back_button(RECOVER);
            }
        }

        if(place!=6&&num==1)
        {
            num = 0;
            clrmous(MouseX,MouseY);
            if(language == ENGLISH)
            {       
                setcolor(DARKGRAY);
                settextstyle(DEFAULT_FONT , HORIZ_DIR , 1);
                outtextxy(270,400,"---->RULE<----");
            }
            else if(language == CHINESE)
            {
                puthz(300,395,"注册规则",16,16,DARKGRAY);
            } 
        }

    }
}

void show_rule()
{
    int size;
    void *rule_buffer;
    int flag;

    size = imagesize(180,180,480,300);
    rule_buffer = malloc(size);
    if(rule_buffer!=NULL)
        getimage(180,180,480,300,rule_buffer);
    else
    {
        // perror("ERROR IN WARNING!");
        // delay(3000);
        // exit(1);
    }

    setfillstyle(SOLID_FILL,LIGHTBLUE);
    bar(180,180,480,300);
    setfillstyle(SOLID_FILL,BLUE);
    bar(180,180,190,300);
    bar(180,180,480,190);
    bar(180,290,480,300);
    bar(470,180,480,300);

    setcolor(RED);
    setlinestyle(SOLID_LINE,0,NORM_WIDTH);
    line(470,180,480,180);
    line(470,180,470,190);
    line(480,180,480,190);
    line(470,190,480,190);
    line(470,180,480,190);
    line(470,190,480,180);

    settextstyle(DEFAULT_FONT,HORIZ_DIR,1);
    outtextxy(195,215,"THE PASSWORD MUST INCLUDE:");
    outtextxy(195,225,"1.CAPITALIZED LETTER");
    outtextxy(195,235,"2.SHALL LETTER");
    outtextxy(195,245,"3.NUMBER");
    outtextxy(195,255,"4.AT LEAST 6 CHARACTERS ");
    mouseinit();
    while(1)
    {
        newmouse(&MouseX,&MouseY,&press);
        if(mouse_press(470,180,480,190)==2)
        {
            if(flag!=1)
            {
                MouseS = 1;
                flag = 1;
            }
        }
        else if(mouse_press(470,180,480,190)==1)
        {
            clrmous(MouseX,MouseY);
            putimage(180,180,rule_buffer,COPY_PUT);
            free(rule_buffer);
            delay(60);
            break;
        }
        else 
        {
            if(flag!=0)
            {
                flag = 0;
                MouseS = 0;
            }
        }
    }

}
