#include <iostream>
#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <stdlib.h>

#define ARRIBA 72//marcando las flechas con codigo ascii
#define IZQUIERDA 75
#define DERECHA 77
#define ABAJO 80

using namespace std;


void gotoxy(int x, int y){//Se han dado los parametros para mover la pieza

    HANDLE hCon;
    hCon = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD dwPos;
    dwPos.X = x;
    dwPos.Y = y;

    SetConsoleCursorPosition(hCon, dwPos);
}


void OcultarCursor(){
    HANDLE hCon;
    hCon = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cci; //Una estructura con varias funcions incorporadas
    cci.dwSize = 2;
    cci.bVisible = false;

    SetConsoleCursorInfo(hCon,&cci);


}

void pintar_limites(){
for(int i=2; i<78; i++){
    gotoxy(i, 3); printf ("%c", 205);
    gotoxy(i,33); printf ("%c", 205);
}
for(int i=4; i<33; i++){
    gotoxy(2, i); printf ("%c", 186);
    gotoxy(77, i); printf ("%c", 186);
}
gotoxy(2,3); printf("%c", 201);
gotoxy(2,33); printf("%c", 200);
gotoxy(77,3); printf("%c", 187);
gotoxy(77,33); printf("%c", 188);
}


class NAVE{
    int x, y;
    int corazones;
    int vidas;
public:
    NAVE(int _x, int _y, int _corazones, int _vidas): x(_x), y(_y), corazones(_corazones), vidas(_vidas){}
    int X(){return x;}
    int Y(){return y;}
    void COR () { corazones--;}
    void pintar();
    void borrar();
    void mover ();
    void pintar_corazones();
    void morir();
};


void NAVE::pintar(){
    gotoxy(x, y); printf("  %c", 30);
    gotoxy(x, y+1); printf(" %c%c%c", 40, 207, 41);
    gotoxy(x, y+2); printf ("%c%c %c%c",30,190,190,30);
}

 void NAVE::borrar(){
    gotoxy(x, y); printf("        ");
    gotoxy(x, y+1); printf("        ");
    gotoxy(x, y+2); printf("        ");
 }



 void NAVE::mover(){
    if(kbhit()){//parte de la libreria <conio.h>
            char tecla = getch();
            borrar();
            if (tecla == IZQUIERDA && x>3) x-=2;
            if (tecla == DERECHA && x+6 < 77) x+=2;
            if (tecla == ARRIBA && y>5) y-=2;
            if (tecla == ABAJO && y+4 < 33) y+=2;
            if (tecla == 'e')corazones--;
            pintar();
            pintar_corazones();
          }
 }


 void NAVE::pintar_corazones(){
    gotoxy(50,2); printf("VIDAS %d ", vidas );
    gotoxy(64,2); printf("SALUD: ");
    gotoxy(70,2); printf("       ");
    for (int i=0; i< corazones; i++){
        gotoxy(70+i,2);printf ("%c", 3);
    }
 }

 void NAVE::morir(){
    if (corazones == 0){
        borrar();
        gotoxy(x,y); printf   ("   **   ");
        gotoxy(x,y+1); printf ("  ****  ");
        gotoxy(x,y+2); printf ("   **   ");
        Sleep(200);



        borrar();
        gotoxy(x,y); printf   (" * ** *");
        gotoxy(x,y+1); printf ("  ****  ");
        gotoxy(x,y+2); printf (" * ** *");
        Sleep(200);
        borrar();

        vidas--;
        vidas--;
        corazones = 3;
        pintar_corazones();
        pintar();

    }


 }

class AST{
int x, y;
public:
    AST( int _x, int _y): x(_x), y(_y){}
    void pintar();
    void mover ();
    void choque ( class NAVE &N);
};

void AST::pintar(){
    gotoxy(x,y); printf("%c", 184);
}

void AST :: mover(){
    gotoxy(x,y); printf(" ");
    y++;
    if (y>32){
        x = rand()%71+4;
        y = 4;

    }
    pintar();
}

void AST::choque(class NAVE &N){
    if (x >= N.X() && x< N.X()+6 && y >= N.Y() &&  y < N.Y()+2){
        N.COR();
        N.borrar();
        N.pintar();
        N.pintar_corazones();
        x = rand()%71+4;
        y = 4;

    }
}


int main()
{

    OcultarCursor();
    pintar_limites();
    NAVE N(7,7,3,3);
    N.pintar();
    N.pintar_corazones();

    AST ast1(10,4), ast2(4,8), ast3(15, 10) ;


    bool game_over = false;
    while(!game_over){

          ast1.mover(); ast1.choque(N);
          ast2.mover(); ast2.choque(N);
          ast3.mover(); ast3.choque(N);
          N.morir();
          N.mover();
          Sleep(30);
    }
    return 0;
}
