#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "defendiendo_torres.h"
#include "utiles.h"
#include "animos.h"

#define  ENANOS_1 5
#define  ELFOS_2 5
#define  ENANOS_Y_ELFOS_3 6
#define  ENANOS_Y_ELFOS_4 8
#define  FUERZA_ENANOS 60
#define  FUERZA_ELFOS 30
#define  CANTIDAD_DEFENSORES_1y2 5
#define  CANTIDAD_DEFENSORES_3 3
#define  CANTIDAD_DEFENSORES_4 4
#define  NIVEL_1 1
#define  NIVEL_2 2
#define  NIVEL_3 3
#define ORCOS_PRIMER_NIVEL 100
#define ORCOS_SEGUNDO_NIVEL 200
#define ORCOS_TERCER_NIVEL 10
#define ORCOS_CUARTO_NIVEL 500
const int MAX_MATRIZ_1= 15;
const int MAX_MATRIZ_2= 20;


/*
*  Guardara la posicion de los defensores el iniciar cada nivel.
*/
void ubicar_defensores_iniciales (nivel_t* nivel,  int cant_defensores, int tope_matriz, char tipo){
    coordenada_t posicion;
    while (nivel->tope_defensores < cant_defensores){
        posicion.fil= rand ()% tope_matriz;
        posicion.col= rand ()% tope_matriz;
    	while(agregar_defensor(nivel, posicion, tipo)== -1){
            posicion.fil= rand ()% tope_matriz;
            posicion.col= rand ()% tope_matriz;
     	}
	}
}

/*
* obtienen el camino y asignan el tipo de defensor y su fuerza para el nivel 1 y 2.
*/

void niveles_1y2(nivel_t* nivel, coordenada_t entrada, coordenada_t torre, int cant_defensores){
	obtener_camino(nivel->camino_1, &nivel->tope_camino_1, entrada, torre);
	nivel->tope_camino_2 = 0;
}
/*
* obtienen los dos caminos y asignan los tipos de defensores y su fuerza para el nivel 3 y 4.
*/
void niveles_3y4(nivel_t* nivel, coordenada_t entrada_1, coordenada_t entrada_2,coordenada_t torre_1,coordenada_t torre_2, int cant_defensores){
    obtener_camino(nivel->camino_1, &nivel->tope_camino_1, entrada_1, torre_1);
    obtener_camino(nivel->camino_2, &nivel->tope_camino_2, entrada_2, torre_2);
}

/* recibe una coordenada de tipo coordenada_t
* y le asignara fila y columna.
*/
coordenada_t inicializar_coor(int fil, int col){
    coordenada_t coordenada;
    coordenada.col=col;
    coordenada.fil=fil;
    return coordenada;
}

/*
* aux_nivel debe ser valido, con valores 1, 2 ,3 o 4 unicamente.
* inicializara cada nivel, cargando las coordenadas de las torres, las entradas, el tipo de defesor 
*y su fuerza de ataque,y generando uno/ o dos camino/s aleatoreo para cada uno
*
*/ 
void inicializar_nivel(nivel_t* nivel,int nivel_actual){ 
    nivel->tope_defensores=0;
    nivel->tope_enemigos=0;
    if (nivel_actual == NIVEL_1){
        niveles_1y2(nivel, inicializar_coor(8,0), inicializar_coor(3,14), CANTIDAD_DEFENSORES_1y2);
        nivel->max_enemigos_nivel= ORCOS_PRIMER_NIVEL;
        ubicar_defensores_iniciales (nivel, ENANOS_1,MAX_MATRIZ_1, ENANOS); 
    }
    else if (nivel_actual == NIVEL_2){
        niveles_1y2(nivel, inicializar_coor(8,14), inicializar_coor(9,0),  CANTIDAD_DEFENSORES_1y2);
        nivel->max_enemigos_nivel= ORCOS_SEGUNDO_NIVEL;
        ubicar_defensores_iniciales (nivel, ELFOS_2, MAX_MATRIZ_1, ELFOS); 
    }
    else if (nivel_actual == NIVEL_3){
        niveles_3y4(nivel, inicializar_coor(0,13), inicializar_coor(0,1),inicializar_coor(19,10),inicializar_coor(19,18), CANTIDAD_DEFENSORES_3); 
        nivel->max_enemigos_nivel= ORCOS_TERCER_NIVEL; 
        ubicar_defensores_iniciales (nivel, (ENANOS_Y_ELFOS_3 /2), MAX_MATRIZ_2, ELFOS); 
        ubicar_defensores_iniciales (nivel, ENANOS_Y_ELFOS_3, MAX_MATRIZ_2, ENANOS); 
    }
    else{
        niveles_3y4(nivel, inicializar_coor(19,13), inicializar_coor(19,12),inicializar_coor(0,10),inicializar_coor(0,19), CANTIDAD_DEFENSORES_4);
        nivel->max_enemigos_nivel= ORCOS_CUARTO_NIVEL;
        ubicar_defensores_iniciales (nivel,  ENANOS_Y_ELFOS_4/2, MAX_MATRIZ_2, ELFOS); 
        ubicar_defensores_iniciales (nivel,  ENANOS_Y_ELFOS_4, MAX_MATRIZ_2, ELFOS); 
    }
}

/*
* recibe el juego con la resistencia de las torres cargadas, devuelve true si tienen vida mayor que 0 y false en caso contrario.
*/
bool torres_vivas(juego_t juego){
    if (juego.torres.resistencia_torre_1 <= 0 || juego.torres.resistencia_torre_2 <=0){
        return false;
    }
    return true;
}
void jugar_nivel (juego_t juego){
    inicializar_nivel(&juego.nivel, juego.nivel_actual);
    while (estado_nivel( juego.nivel) == 0 && torres_vivas(juego)){
        jugar_turno(&juego);
        mostrar_juego(juego);
        detener_el_tiempo(1.5);
        system("clear");
    }
    if (estado_juego(juego)== -1){
        printf ("Lo lamento, has perdido \n");
    }
    else if (estado_nivel(juego.nivel)== 1 && juego.nivel_actual!= 4){
        printf ("FELICIDADES! has pasado de nivel \n");
        detener_el_tiempo(1);
        if (juego.nivel_actual< 4){
            juego.nivel_actual++;
            jugar_nivel (juego);
        }
    }
    else if (estado_juego(juego)== 1 ){
        printf ("FELICIDADES! HAS GANADO! \n");
    }

}

int main(){
	int viento, humedad;
	char animo_legolas, animo_gimli;
	juego_t juego;

    srand((unsigned)time(NULL));
	viento = 25;
    humedad = 25;
	animo_legolas = 'M';
	animo_gimli = 'B';
	/* animos(&viento,&humedad,&animo_legolas,&animo_gimli); */

    inicializar_juego( &juego, viento, humedad, animo_legolas, animo_gimli);
	
	juego.nivel_actual = 3;

    jugar_nivel (juego);

	return 0;
}
