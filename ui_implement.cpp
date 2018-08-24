#include "ui.h"
#include <fstream>
#include <iostream>
#include <termios.h>
#include <sys/ioctl.h>

using namespace std;

void Go_Backwards(){
    cout<<"Have to go to previous directory\n";
}

void Go_Forwards(){
    cout<<"Have to go to next directory\n";
}

void Goto_Home(){
    cout<<"Have to go back home\n";

}

void Goto_Up_Level(){
    cout<<"Have to go one level up\n";

}

void Move_Cursor_Up(){
    cout<<"\033[A";

}

void Move_Cursor_Down(){
    cout<<"\033[B";

}

void Command_Mode(FILE *file_descriptor){
    struct winsize window_size;
    ioctl(fileno(file_descriptor),TIOCGWINSZ, &window_size);        //gives the size of terminal window
    int rows = window_size.ws_col;          //number of rows in terminal
    cout<<"\033["<<rows<<";"<<1<<"H:";
    cout<<"\033[1;37m";
    string str;
    char ch1;
    ifstream instr;
   do {
        ch1 = getchar();
       /* if(ch1=='\033'){
            char ch2, ch3;
            ch2 = getchar();
            if(ch2==0)
                continue;
            ch3 = getchar();
            if(ch2==91){
                    if(ch3==65)
                        ch1 = ' ';
                    else if(ch3==66)
                        ch1 = ' ';
                    else if(ch3==67){
                        cout<<"\033[C";
                        ch1 = ' ';
                    }
                    else if(ch3==68){
                        cout<<"\033[C";
                        ch1 = ' ';
                    }
            }
        }*/
        if(ch1=='\n'){
            cout<<"\033[2K";
            cout<<"\033["<<rows<<";"<<1<<"H:";
            cout<<"\033[1;37m";
        }
        else{
            str+=ch1;
            cout<<ch1;       //outputting character as echo is off
        }
            
    }while(ch1!='\033');  

}

void Normal_Mode(){
     struct termios term_i, term_n;
    const char* trem_tty = "/dev/tty";
    FILE *file_descriptor;
    file_descriptor = fopen(trem_tty,"rw");

    if(!file_descriptor){
        cout<<"Error Opening Terminal";
    }
    cout<<"\033c";
    cout<<"\033[3J";
    tcgetattr(fileno(file_descriptor),&term_i);
    term_n = term_i;
    term_n.c_lflag &= ~ICANON;
    term_n.c_lflag &= ~ECHO;
    term_n.c_cc[VMIN] = 1;
    term_n.c_cc[VTIME] = 0;
    tcsetattr(fileno(file_descriptor),TCSANOW,&term_n);
    struct winsize window_size;
    ioctl(fileno(file_descriptor),TIOCGWINSZ, &window_size);
    int rows = window_size.ws_col;
    cout<<"\033["<<rows<<";"<<1<<"H:";
    cout<<"\033[1;1H";
    cout<<"\t\t\tTrailblazer File Explorer\n";
    cout<<">Press : to go to command mode\t>Press Esc to go back to Normal Mode\t>Press q to quit\n";
    char ch, ch2, ch3;
    ch = ' ';
    while(ch!='q'){
        ch = getchar();
        if(ch==58){
            Command_Mode(file_descriptor);
            cout<<"\033[0m";
            cout<<"\33[2K";
            cout<<"\033["<<rows<<";"<<1<<"H:";
            cout<<"\033[3;1H";
            continue;
        }
        else if(ch==8){
            Goto_Up_Level();
        }
        else if(ch=='h'){
            Goto_Home();
        }
        else if (ch=='\033') {
            ch2 = getchar();
            ch3 = getchar();
            if(ch2==91){
                 //Up Arrow 65, Down Arrow 66, Left Arrow 67, Right Arrow 68
                if(ch3==65)
                    Move_Cursor_Up();
                else if(ch3==66)
                    Move_Cursor_Down();
                else if(ch3==67)
                    Go_Forwards();
                else if(ch3==68)
                    Go_Backwards();
            }
        }
    }
    tcsetattr(fileno(file_descriptor),TCSANOW,&term_i);
    cout<<"\033[0m";
    cout<<"\033[60;1H";
    cout<<"\033c";
    cout<<"\033[3J";
}