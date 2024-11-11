/*#include <allegro.h>
#ifndef PERSONAJES_H_INCLUDED
#define PERSONAJES_H_INCLUDED


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
void impri_mapa(PERSONAJE *P);
char mapa[][];
void pantalla();
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
void mover_fantasma1(fantasma *A);
void mover_fantasma2(fantasma *B);
void mover_fantasma3(fantasma *C);
void mover_fantasma4(fantasma *D);
void mover_fantasma5(fantasma *Z);
void mover_fantasma6(fantasma *Y);
void mover_fantasma7(fantasma *X);
void mover_fantasma8(fantasma *W);
bool game_over();

#endif // PERSONAJES_H_INCLUDED*/
