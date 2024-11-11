/*#include "personajes.h"
#include <allegro.h>
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
}*/
