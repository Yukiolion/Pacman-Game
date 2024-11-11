#include <allegro.h>
#include "inicia.h"
#include <cstdlib>
#define ANCHO 880
#define ALTO  690
#define FILA 24
#define COLU 31
BITMAP *buffer;
BITMAP *muro;
BITMAP *food;
BITMAP *poder;
BITMAP *tin;
BITMAP *muerte;
BITMAP* ene;
BITMAP* enemif;
SAMPLE *muert;
SAMPLE *waka;
SAMPLE *power;
SAMPLE *muefant;
SAMPLE *intro;

char mapa[FILA][COLU]=
{   "                              ",
    "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXX",
    "XOooooooooooooXooooooooooooOXX",
    "XoXXXXoXXXXXXoXoXXXXXXoXXXXoXX",
    "XoXXXXoXXXXXXoXoXXXXXXoXXXXoXX",
    "XoooooooooooooooooooooooooooXX",
    "XoXXXXoXoXXXXXXXXXXXoXoXXXXoXX",
    "XooooooXooooooXooooooXooooooXX",
    "XXXXXXoXXXXXXoXoXXXXXXoXXXXXXX",
    "     XoX             XoX      ",
    "XXXXXXoX XXXXX XXXXX XoXXXXXXX",
    "      o  X         X  o       ",
    "XXXXXXoX X XXXXXXX X XoXXXXXXX",
    "     XoX             XoX      ",
    "XXXXXXoX XXXXXXXXXXX XoXXXXXXX",
    "XoooooooooooooXoooooooooooooXX",
    "XOXXXXoXXXXXXoXoXXXXXXoXXXXOXX",
    "XooooXoooooooo ooooooooXooooXX",
    "XXXXoXoXoXXXXXXXXXXXoXoXoXXXXX",
    "XooooooXooooooXooooooXooooooXX",
    "XoXXXXXXXXXXXoXoXXXXXXXXXXXoXX",
    "XoooooooooooooooooooooooooooXX",
    "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXX",
};

struct PERSONAJE
{
    int x, y;
    int dir;
    BITMAP *pac;

    void inicia();
    void carga(char* elpac);
    void dibuja_per(BITMAP* buffer,BITMAP* tin);
    void dibuja_per2(BITMAP* buffer,BITMAP* tin);
};
void PERSONAJE::inicia()
{
    x=30*14, y = 30*17;
    dir=0;
}
void PERSONAJE::carga(char* elpac)
{
    pac= load_bitmap(elpac,NULL);
}
void PERSONAJE::dibuja_per(BITMAP* buffer,BITMAP* tin)
{
    blit(pac,tin,dir*33,0,0,0,33,33);
    draw_sprite(buffer,tin,x,y);//respeta la tranferencia del buffer pequeño
}
void PERSONAJE::dibuja_per2(BITMAP* buffer,BITMAP* tin)
{
    clear(tin);
    blit(pac,tin,4*33,0,0,0,33,33);
    draw_sprite(buffer,tin,x,y);
}

void impri_mapa(PERSONAJE *P)
{
    int fil,col;

for(fil=0;fil<FILA;fil++)
    {
        for(col=0;col<COLU;col++)
    {
        if(mapa[fil][col]== 'X'){draw_sprite(buffer,muro,col*30,fil*30);}
        else if(mapa[fil][col]== 'o'){draw_sprite(buffer,food,col*30,fil*30);
        if(P->y/30==fil && P->x/30==col){//play_sample(waka,300,150,1000,0);
                mapa[fil][col] = ' ';}}
        else if(mapa[fil][col]== 'O'){draw_sprite(buffer,poder,col*30,fil*30);
        if(P->y/30==fil && P->x/30==col){ mapa[fil][col] = 'l';}}
    }
    }
}
void pantalla()
{
blit(buffer,screen,0,0,0,0,ANCHO,ALTO);
}

struct fantasma
{
    int fx, fy;
    int fdir;
    BITMAP* enemigo;
    BITMAP* enemigof;
    void iniciaf();
    void cargar(char* elfan);
    void cargar2(char* elfan2);
    void dibujar_fantasma(BITMAP* buffer,BITMAP* ene);
    void dibujar_fantasma2(BITMAP* buffer,BITMAP* ene);

};

void fantasma::cargar(char* elfan)
{
    enemigo= load_bitmap(elfan,NULL);
}
void fantasma::cargar2(char* elfan2)
{
    enemigof= load_bitmap(elfan2,NULL);
}
void fantasma::dibujar_fantasma(BITMAP* buffer,BITMAP* ene)
{
    blit(enemigo,ene,0,0,0,0,30,30);
    draw_sprite(buffer,ene,fx,fy);
}
void fantasma::dibujar_fantasma2(BITMAP* buffer,BITMAP* ene)
{
    blit(enemigof,ene,0,0,0,0,30,30);
    draw_sprite(buffer,ene,fx,fy);
}
void mover_fantasma1(fantasma *A)
{if(A->fdir== 0)
    {if(mapa[A->fy/30][(A->fx-30)/30]!='X')
        {A->fx-=30;}
        else {A->fdir = rand()%4;}
    }
     if(A->fdir== 1)
    {if(mapa[A->fy/30][(A->fx+30)/30]!='X')
        {A->fx+=30;}
        else {A->fdir = rand()%4;}
    }
     if(A->fdir== 2)
    {if(mapa[(A->fy-30)/30][(A->fx)/30]!='X')
        {A->fy-=30;}
        else {A->fdir = rand()%4;}
    }
    if(A->fdir== 3)
    {if(mapa[(A->fy+30)/30][(A->fx)/30]!='X')
        {A->fy+=30;}
        else {A->fdir = rand()%4;}
    }
    if(A->fx <= -30){A->fx=880;}//izquierda
    else if(A->fx >= 880){A->fx=-30;}//derecha
}
void mover_fantasma2(fantasma *B)
{if(B->fdir== 0)
    {if(mapa[B->fy/30][(B->fx-30)/30]!='X')
        {B->fx-=30;}
        else {B->fdir = rand()%4;}
    }
    if(B->fdir== 1)
    {if(mapa[B->fy/30][(B->fx+30)/30]!='X')
        {B->fx+=30;}
        else {B->fdir = rand()%4;}
    }
     if(B->fdir== 2)
    {if(mapa[(B->fy-30)/30][(B->fx)/30]!='X')
        {B->fy-=30;}
       else {B->fdir = rand()%4;}
    }
    if(B->fdir== 3)
    {if(mapa[(B->fy+30)/30][(B->fx)/30]!='X')
        {B->fy+=30;}
       else {B->fdir = rand()%4;}
    }
        if(B->fx <= -30){B->fx=880;}//izquierda
        else if(B->fx >= 880){B->fx=-30;}//derecha
}
void mover_fantasma3(fantasma *C)
{if(C->fdir== 0)
    {if(mapa[C->fy/30][(C->fx-30)/30]!='X')
        {C->fx-=30;}
        else {C->fdir = rand()%4;}
    }
     if(C->fdir== 1)
    {if(mapa[C->fy/30][(C->fx+30)/30]!='X')
        {C->fx+=30;}
        else {C->fdir = rand()%4;}
    }
     if(C->fdir== 2)
    {if(mapa[(C->fy-30)/30][(C->fx)/30]!='X')
        {C->fy-=30;}
        else {C->fdir = rand()%4;}
    }
    if(C->fdir== 3)
    {if(mapa[(C->fy+30)/30][(C->fx)/30]!='X')
        {C->fy+=30;}
        else {C->fdir = rand()%4;}
    }
    if(C->fx <= -30){C->fx=880;}//izquierda
    else if(C->fx >= 880){C->fx=-30;}//derecha
}
void mover_fantasma4(fantasma *D)
{if(D->fdir== 0)
    {if(mapa[D->fy/30][(D->fx-30)/30]!='X')
        {D->fx-=30;}
        else {D->fdir = rand()%4;}
    }
     if(D->fdir== 1)
    {if(mapa[D->fy/30][(D->fx+30)/30]!='X')
        {D->fx+=30;}
        else {D->fdir = rand()%4;}
    }
     if(D->fdir== 2)
    {if(mapa[(D->fy-30)/30][(D->fx)/30]!='X')
        {D->fy-=30;}
        else {D->fdir = rand()%4;}
    }
    if(D->fdir== 3)
    {if(mapa[(D->fy+30)/30][(D->fx)/30]!='X')
        {D->fy+=30;}
        else {D->fdir = rand()%4;}
    }
    if(D->fx <= -30){D->fx=880;}//izquierda
    else if(D->fx >= 880){D->fx=-30;}//derecha
}
void mover_fantasma5(fantasma *Z)
{if(Z   ->fdir== 0)
    {if(mapa[Z->fy/30][(Z->fx-30)/30]!='X')
        {Z->fx-=30;}
        else {Z->fdir = rand()%4;}
    }
     if(Z->fdir== 1)
    {if(mapa[Z->fy/30][(Z->fx+30)/30]!='X')
        {Z->fx+=30;}
        else {Z->fdir = rand()%4;}
    }
     if(Z->fdir== 2)
    {if(mapa[(Z->fy-30)/30][(Z->fx)/30]!='X')
        {Z->fy-=30;}
        else {Z->fdir = rand()%4;}
    }
    if(Z->fdir== 3)
    {if(mapa[(Z->fy+30)/30][(Z->fx)/30]!='X')
        {Z->fy+=30;}
        else {Z->fdir = rand()%4;}
    }
    if(Z->fx <= -30){Z->fx=880;}//izquierda
    else if(Z->fx >= 880){Z->fx=-30;}//derecha
}
void mover_fantasma6(fantasma *Y)
{if(Y->fdir== 0)
    {if(mapa[Y->fy/30][(Y->fx-30)/30]!='X')
        {Y->fx-=30;}
        else {Y->fdir = rand()%4;}
    }
     if(Y->fdir== 1)
    {if(mapa[Y->fy/30][(Y->fx+30)/30]!='X')
        {Y->fx+=30;}
        else {Y->fdir = rand()%4;}
    }
     if(Y->fdir== 2)
    {if(mapa[(Y->fy-30)/30][(Y->fx)/30]!='X')
        {Y->fy-=30;}
        else {Y->fdir = rand()%4;}
    }
    if(Y->fdir== 3)
    {if(mapa[(Y->fy+30)/30][(Y->fx)/30]!='X')
        {Y->fy+=30;}
        else {Y->fdir = rand()%4;}
    }
    if(Y->fx <= -30){Y->fx=880;}//izquierda
    else if(Y->fx >= 880){Y->fx=-30;}//derecha
}
void mover_fantasma7(fantasma *X)
{if(X->fdir== 0)
    {if(mapa[X->fy/30][(X->fx-30)/30]!='X')
        {X->fx-=30;}
        else {X->fdir = rand()%4;}
    }
     if(X->fdir== 1)
    {if(mapa[X->fy/30][(X->fx+30)/30]!='X')
        {X->fx+=30;}
        else {X->fdir = rand()%4;}
    }
     if(X->fdir== 2)
    {if(mapa[(X->fy-30)/30][(X->fx)/30]!='X')
        {X->fy-=30;}
        else {X->fdir = rand()%4;}
    }
    if(X->fdir== 3)
    {if(mapa[(X->fy+30)/30][(X->fx)/30]!='X')
        {X->fy+=30;}
        else {X->fdir = rand()%4;}
    }
    if(X->fx <= -30){X->fx=880;}//izquierda
    else if(X->fx >= 880){X->fx=-30;}//derecha
}
void mover_fantasma8(fantasma *W)
{if(W->fdir== 0)
    {if(mapa[W->fy/30][(W->fx-30)/30]!='X')
        {W->fx-=30;}
        else {W->fdir = rand()%4;}
    }
     if(W->fdir== 1)
    {if(mapa[W->fy/30][(W->fx+30)/30]!='X')
        {W->fx+=30;}
        else {W->fdir = rand()%4;}
    }
     if(W->fdir== 2)
    {if(mapa[(W->fy-30)/30][(W->fx)/30]!='X')
        {W->fy-=30;}
        else {W->fdir = rand()%4;}
    }
    if(W->fdir== 3)
    {if(mapa[(W->fy+30)/30][(W->fx)/30]!='X')
        {W->fy+=30;}
        else {W->fdir = rand()%4;}
    }
    if(W->fx <= -30){W->fx=880;}//izquierda
    else if(W->fx >= 880){W->fx=-30;}//derecha
}
bool game_over()
{int fil,col;
for(fil=0;fil<FILA;fil++)
    {for(col=0;col<COLU;col++)
    {if(mapa[fil][col]== 'o')
    {return true;}
    }}return false;
}


int main ()
{
    inicia_allegro(ANCHO,ALTO);
    inicia_audio(70,70);
    buffer= create_bitmap(ANCHO,ALTO);
    tin= create_bitmap(33,33);
    ene= create_bitmap(30,30);
    muro= load_bitmap("roca.bmp",NULL);
    food= load_bitmap("comida.bmp",NULL);
    poder= load_bitmap("power.bmp",NULL);
    muerte= load_bitmap("muerte.bmp",NULL);
    muert= load_wav("muerte.wav");
    muefant= load_wav("muerfant.wav");
    power= load_wav("power.wav");
    waka= load_wav("waka.wav");
    intro= load_wav("intro.wav");
    PERSONAJE P;
    fantasma A;
    fantasma B;
    fantasma C;
    fantasma D;
    fantasma Z;
    fantasma Y;
    fantasma X;
    fantasma W;
    A.cargar("rojo.bmp");
    B.cargar("rosa.bmp");
    C.cargar("amarillo.bmp");
    D.cargar("azul.bmp");
    Z.cargar2("fantasma1.bmp");
    Y.cargar2("fantasma2.bmp");
    X.cargar2("fantasma3.bmp");
    W.cargar2("fantasma4.bmp");
    P.inicia();
    P.carga("pacman.bmp");
    A.fx=30*10;
    A.fy=30*13;
    A.fdir=0;
    B.fx=30*18;
    B.fy=30*13;
    B.fdir=0;
    C.fx=30*10;
    C.fy=30*9;
    C.fdir=0;
    D.fx=30*18;
    D.fy=30*9;
    D.fdir=0;
    Z.fx=A.fx;
    Z.fy=A.fy;
    Z.fdir=0;
    Y.fx=B.fx;
    Y.fy=B.fy;
    Y.fdir=0;
    X.fx=C.fx;
    X.fy=C.fy;
    X.fdir=0;
    W.fx=D.fx;
    W.fy=D.fy;
    W.fdir=0;
    int modo=0;
    int bx,by;
    //play_sample(intro,300,150,1000,0);
     while(!key[KEY_ESC] && game_over())
    {   bx=P.x;
        by=P.y;
        P.dir = 4;
        if(key[KEY_RIGHT]){P.dir = 1;}
        else if(key[KEY_LEFT]){P.dir = 0;}
        else if(key[KEY_UP]){P.dir = 2;}
        else if(key[KEY_DOWN]){P.dir = 3;}
        if(P.dir==0)
        {if(mapa[P.y/30][(P.x-30)/30] != 'X')
        {P.x-=30;}
         else P.dir = 4;
        }
        if(P.dir==1)
        {if(mapa[P.y/30][(P.x+30)/30] != 'X')
        {P.x+=30;}
         else P.dir = 4;
        }
        if(P.dir==2)
        {if(mapa[(P.y-30)/30][(P.x)/30] != 'X')
        {P.y-=30;}
        else P.dir = 4;
        }
        if(P.dir==3)
        {if(mapa[(P.y+30)/30][(P.x)/30] != 'X')
        {P.y+=30;}
        else P.dir = 4;
        }
        if(P.x <= -30){P.x=870;}//izquierda
        else if(P.x >= 870){P.x=-30;}//derecha
        clear(buffer);
        impri_mapa(&P);
        P.dibuja_per(buffer,tin);

    if(modo==0)
    {
    A.dibujar_fantasma(buffer,ene);
    B.dibujar_fantasma(buffer,ene);
    C.dibujar_fantasma(buffer,ene);
    D.dibujar_fantasma(buffer,ene);
    pantalla();
    mover_fantasma1(&A);
    mover_fantasma2(&B);
    mover_fantasma3(&C);
    mover_fantasma4(&D);
    }
   if(mapa[P.y/30][P.x/30] =='l')
    {
        modo=1;
    }
    else if(modo==1)
    {       //play_sample(power,100,150,1000,0);
            for(int i=0; i<= 50; i++)
            {bx=P.x;
            by=P.y;
             P.dir = 4;
        if(key[KEY_RIGHT]){P.dir = 1;}
        else if(key[KEY_LEFT]){P.dir = 0;}
        else if(key[KEY_UP]){P.dir = 2;}
        else if(key[KEY_DOWN]){P.dir = 3;}
        if(P.dir==0){if(mapa[P.y/30][(P.x-30)/30] != 'X'){P.x-=30;}else P.dir = 4;}
        if(P.dir==1){if(mapa[P.y/30][(P.x+30)/30] != 'X'){P.x+=30;}else P.dir = 4;}
        if(P.dir==2){if(mapa[(P.y-30)/30][(P.x)/30] != 'X'){P.y-=30;}else P.dir = 4;}
        if(P.dir==3){if(mapa[(P.y+30)/30][(P.x)/30] != 'X'){P.y+=30;}else P.dir = 4;}
        if(P.x <= -30){P.x=870;}//izquierda
        else if(P.x >= 870){P.x=-30;}//derecha
            clear(ene);
            clear(buffer);
            impri_mapa(&P);
            Z.dibujar_fantasma2(buffer,ene);
            Y.dibujar_fantasma2(buffer,ene);
            X.dibujar_fantasma2(buffer,ene);
            W.dibujar_fantasma2(buffer,ene);
            mover_fantasma5(&Z);
            mover_fantasma6(&Y);
            mover_fantasma7(&X);
            mover_fantasma8(&W);
            P.dibuja_per(buffer,tin);
            pantalla();
            rest(50);
        //pacman come fantasmas
        if((P.y==Z.fy && P.x==Z.fx) || (Z.fy==by && Z.fx==bx ))
        { //play_sample(muefant,100,150,1000,0);
        for(int j=0; j<= 5; j++)
        {
        clear(ene);
        clear(buffer);
        impri_mapa(&P);
        pantalla();
        rest(50);
        }Z.fx=30*10;
         Z.fy=30*13;
         Z.fdir=rand()%5;
         }
        else if((P.y==Y.fy && P.x==Y.fx) || (Y.fy==by && Y.fx==bx ))
        {
        for(int j=0; j<= 5; j++)
        {
        clear(ene);
        clear(buffer);
        impri_mapa(&P);
        pantalla();
        rest(50);
        }Y.fx=30*18;
         Y.fy=30*13;
         Y.fdir=rand()%5;
         }
        else if((P.y==X.fy && P.x==X.fx) || (X.fy==by && X.fx==bx ))
        {
        for(int j=0; j<= 5; j++)
        {
        clear(ene);
        clear(buffer);
        impri_mapa(&P);
        pantalla();
        rest(50);
        }X.fx=30*10;
         X.fy=30*9;
         X.fdir=rand()%5;
         }
        else if((P.y==W.fy && P.x==W.fx) || (W.fy==by && W.fx==bx ))
        {
        for(int j=0; j<= 5; j++)
        {
        clear(ene);
        clear(buffer);
        impri_mapa(&P);
        pantalla();
        rest(50);
        }W.fx=30*18;
         W.fy=30*9;
         W.fdir=rand()%5;
         }

            P.dibuja_per2(buffer,tin);
            pantalla();
            rest(100);
            }
            modo=0;
            Z.fx=A.fx;
            Z.fy=A.fy;
            Y.fx=B.fx;
            Y.fy=B.fy;
            X.fx=C.fx;
            X.fy=C.fy;
            W.fx=D.fx;
            W.fy=D.fy;
    }
//fantasma toca a pacman
  if((P.y==A.fy && P.x==A.fx) || (P.y==B.fy && P.x==B.fx) || (P.y==C.fy && P.x==C.fx) || (P.y==D.fy && P.x==D.fx) || (A.fy==by && A.fx==bx ) || (B.fy==by && B.fx==bx )|| (C.fy==by && C.fx==bx ) || (D.fy==by && D.fx==bx))
    {   //play_sample(muert,100,150,1000,0);
        for(int j=0; j<= 5; j++)
        {
            clear(tin);
            clear(buffer);
            impri_mapa(&P);
            blit(muerte,tin,j*33,0,0,0,33,33);
            draw_sprite(buffer,tin,P.x,P.y);
            pantalla();
            rest(80);
        }
       P.x=30*14;
       P.y=30*17;
       P.dir=4;
    }
    rest(50);
    P.dibuja_per2(buffer,tin);
    pantalla();
    rest(100);

}   //readkey();

    //destroy_bitmap(buffer);

    return 0;
}
END_OF_MAIN ()


