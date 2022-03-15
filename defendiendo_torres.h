#ifndef __DEFENDIENDO_TORRES_H__

#define __DEFENDIENDO_TORRES_H__

 

#include <stdlib.h>

#include <stdio.h>

 

#define MAX_FILAS 30

#define MAX_COLUMNAS 30

#define MAX_LONGITUD_CAMINO 200

#define MAX_ENEMIGOS 500

#define MAX_DEFENSORES 50

#define PRIMER_NIVEL 1 

#define SEGUNDO_NIVEL 2

#define TERCER_NIVEL 3

#define CUARTO_NIVEL 4

#define ELFOS 'L'

#define ENANOS 'G'

#define ORCOS 'O'

 

typedef struct coordenada {

              int fil;

              int col;

} coordenada_t;

 

typedef struct defensor {

              char tipo;

              int fuerza_ataque;

              coordenada_t posicion;

} defensor_t;

 

typedef struct torres {

              int resistencia_torre_1;

              int resistencia_torre_2;

              int enanos_extra;

              int elfos_extra;

} torres_t;

 

typedef struct enemigo {

              int camino;

              int pos_en_camino;

              int vida;

} enemigo_t;

 

typedef struct nivel {

              coordenada_t camino_1[MAX_LONGITUD_CAMINO];

              int tope_camino_1;

             

              coordenada_t camino_2[MAX_LONGITUD_CAMINO];

              int tope_camino_2;

 

              defensor_t defensores[MAX_DEFENSORES];

              int tope_defensores;

 

              enemigo_t enemigos[MAX_ENEMIGOS];

              int tope_enemigos;
              

              int max_enemigos_nivel;

} nivel_t;

 

typedef struct juego {

              nivel_t nivel;

              torres_t torres;

              int nivel_actual;

              int critico_legolas;

              int critico_gimli;

              int fallo_legolas;

              int fallo_gimli;

} juego_t;

 

/*

* Inicializara el juego, cargando la informacion de las torres y

* los ataques criticos y fallo de Legolas y Gimli.

* NO inicializara el primer nivel.

*/

void inicializar_juego(juego_t* juego, int viento, int humedad, char animo_legolas, char animo_gimli);

 

/*

* Recibe un juego con todas sus estructuras validas.

 * El juego se dara por ganado si el juego esta en el ultimo nivel y este ha sido terminado.

* El juego se dara por perdido, si alguna de las torres llega a 0 en su resistencia.

* Devolvera:

* >  0 si el estado es jugando.

* > -1 si el estado es perdido.

* >  1 si el estado es ganado.

*/

int estado_juego(juego_t juego);

 

/*

* Recibe un nivel con todas sus estructuras validas.

* El nivel se dara por ganado cuando esten TODOS 
* los orcos de este nivel muertos (es decir con vida menor o igual a 0).

* Devolvera:

* >  0 si el estado es jugando.

* >  1 si el estado es ganado.

*/

int estado_nivel(nivel_t nivel);

 

/*

 * Agregara un defensor en el nivel recibido como parametro.

* Devolvera:

* >  0 si pudo agregar el defensor correctamente.

* > -1 si no pudo (la coordenada es parte del camino de ese nivel, existe otro defensor, etc.)

*/

int agregar_defensor(nivel_t* nivel, coordenada_t posicion, char tipo);

 

/*

* Jugara un turno y dejara el juego en el estado correspondiente.

* Haran su jugada enanos, elfos y orcos en ese orden.

*/

void jugar_turno(juego_t* juego);

 

/*

* Mostrara el mapa dependiendo del nivel en que se encuentra el jugador.

*/

void mostrar_juego(juego_t juego);

 

#endif /* __DEFENDIENDO_TORRES_H__ */

 
