#include "defendiendo_torres.h"
#include "utiles.h"
#include "animos.h"
#include <strings.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

#define COLOR_MAGENTA "\x1b[35m\x1b[1m"
#define COLOR_CYAN "\x1b[36m\x1b[1m"
#define COLOR_AMARILLO "\x1b[33m\x1b[1m"
#define COLOR_ROJO "\x1b[31m\x1b[1m"
#define COLOR_VERDE "\x1b[32m\x1b[1m"
#define COLOR_NORMAL "\x1b[0m"
#define BUEN_HUMOR 'B'
#define REGULAR_HUMOR 'R'
#define MAL_HUMOR 'M'
#define CLIMA_MIN 25
#define CLIMA_MED 50
#define CLIMA_MAX 75
#define MAX_MATRIZ_1 15
#define MAX_MATRIZ_2 20
#define PRIMER_NIVEL 1 
#define SEGUNDO_NIVEL 2
#define TERCER_NIVEL 3
#define CUARTO_NIVEL 4
#define ELFOS 'L'
#define ENANOS 'G'
#define ORCOS 'O'

const int VIDA_BASE_ORCOS =200;
const int SEGUNDO_CAMINO= 2;
const int PRIMER_CAMINO =1;
const int EXTRA_ORCOS= 100;
const int CANTIDAD_EXTRA=10;
const int RESISTENCIA_TORRES= 600;
const int MAX_HUMOR= 25;
const int MED_HUMOR= 10;
const int MIN_HUMOR=0;
const int NULO =0;
const char SI='S';
const char NO='N';
const char CAMINO='^';
const char ENEMIGO='O';
const char TERRENO='.';
const char TORRE ='T';
const char ENTRADA ='E';
const int VIDA_QUITADA_TORRE =50;
const int NIVEL_1=1;
const int NIVEL_2=2;
const int NIVEL_3=3;
const int NIVEL_4=4;
const int FUERZA_ENANOS= 60;
const int FUERZA_ELFOS= 30;
const int DIST_MANHATTAN= 3;
const int CANTIDAD_DEFENSORES_1y2= 5;
const int CANTIDAD_DEFENSORES_3=3;
const int CANTIDAD_DEFENSORES_4=4;
const int MAX_ATAQUE= 10;
const int TORRE_UNO =1;
const int TORRE_DOS =2;
const float TIEMPO_DETENIDO= 0.5 ;
const int CANTIDAD_PARA_EXTRA= 50;
const int CANTIDAD_PARA_EXTRA_1= 25;
const int ATAQUE_LETAL_ENANOS =100;
const int ATAQUE_LETAL_ELFOS= 70;
const int PORCENTAJE= 100;



/*
* animo es un dato de tipo char que debe tener valor igual a B, R o M y por ende es valido.
* se calcula el valor de ataque critico segun el humor (para legolas o gimli segun se utilize la funcion), 0 si su humor es malo, 10 si es regular y 25 si es bueno.
*/ 
int calcular_critico(char animo){
    int critico;
    if (animo== BUEN_HUMOR){
       (critico = MAX_HUMOR);
    }
    else if (animo == REGULAR_HUMOR){
         (critico = MED_HUMOR);
    }
    else {
        (critico = MIN_HUMOR);
    }
    return critico;
}

/* Recibe dos caminos y una coordenada.
* Devuelve true si la coordenada esta en alguno de los dos caminos, o false si no lo esta o esta fuera del terreno.
*/
bool posicion_invalida(coordenada_t camino_1[MAX_LONGITUD_CAMINO], coordenada_t camino_2[MAX_LONGITUD_CAMINO], int tope_camino_1, int tope_camino_2, coordenada_t posicion){
    bool esta_en_camino = false;
    int i=0;
    while(!esta_en_camino && i < tope_camino_1){
        if(camino_1[i].fil == posicion.fil && camino_1[i].col == posicion.col)
            esta_en_camino = true;
        i++;
    }
    i = 0;
    while(!esta_en_camino && i < tope_camino_2){
        if(camino_2[i].fil == posicion.fil && camino_2[i].col == posicion.col)
            esta_en_camino = true;
        i++;
    }
    return esta_en_camino;
}

/* recibe un vector de defensores y una posicion. 
*  devuelve true si la posicion es igual a algun defensor, o false si no lo es.
*/
bool chequear_vector_defensores(defensor_t defensores[MAX_DEFENSORES], int tope_defensores, coordenada_t posicion){
    bool se_pisa = false;
    int i=0;
    while(!se_pisa && i < tope_defensores){
        if(defensores[i].posicion.fil == posicion.fil && defensores[i].posicion.col == posicion.col)
            se_pisa = true;
        i++;
    }
    return se_pisa;
}
/* Recibe un nivel con los caminos cargados, una posicion cargada y un nivel_actual (1 , 2 , 3 o 4) 
* devuelve false si la coordenada ingresada no esta en un camino, no se pise con otro defensor ni este fuera del mapa, o true en caso contrario.
*/
bool coordenada_invalida(coordenada_t posicion, nivel_t* nivel){
    bool se_pisa = chequear_vector_defensores(nivel->defensores, nivel->tope_defensores, posicion);
    return posicion_invalida(nivel->camino_1, nivel->camino_2, nivel->tope_camino_1, nivel->tope_camino_2, posicion) || se_pisa;
}

/* recibe una coordenada de tipo coordenada_t
* y le asignara fila y columna.
*/
coordenada_t inicializar_coordenada(int fil, int col){
    coordenada_t coordenada;
    coordenada.col=col;
    coordenada.fil=fil;
    return coordenada;
}

void inicializar_juego (juego_t *juego, int viento, int humedad, char animo_legolas, char animo_gimli){
	juego->torres.resistencia_torre_1= RESISTENCIA_TORRES;
	juego->torres.resistencia_torre_2= RESISTENCIA_TORRES;
	juego->torres.enanos_extra= CANTIDAD_EXTRA;
	juego->torres.elfos_extra=CANTIDAD_EXTRA;
	juego->critico_legolas = calcular_critico(animo_legolas); 
	juego->critico_gimli = calcular_critico(animo_gimli);
	juego->fallo_legolas= (viento * 1/2);
	juego->fallo_gimli = (humedad * 1/2);
    juego->nivel.tope_defensores=0;
    juego->nivel.tope_enemigos=0;
}

int estado_nivel(nivel_t nivel){
    int i=0;
    bool esta_muerto= true;
    while(i< nivel.tope_enemigos && esta_muerto ){
        if (nivel.enemigos[i].vida > 0){
            esta_muerto= false;
        }
        i++;
    }
    if (esta_muerto && nivel.tope_enemigos== nivel.max_enemigos_nivel){
        return 1;
    }
    return 0;
}

int estado_juego(juego_t juego){
    if ((juego.torres.resistencia_torre_1)>0 && (juego.torres.resistencia_torre_2)>0 && ((estado_nivel(juego.nivel)==0) || (estado_nivel(juego.nivel)== 1 && juego.nivel_actual !=CUARTO_NIVEL))){
        return 0;
    }
    else if((juego.torres.resistencia_torre_1)>0 && (juego.torres.resistencia_torre_2)>0 && juego.nivel_actual==CUARTO_NIVEL && estado_nivel(juego.nivel) == 1) {
        return 1;
    }
    else{
        return -1;
    }
}

int agregar_defensor(nivel_t* nivel, coordenada_t posicion, char tipo){
    if( !coordenada_invalida( posicion, nivel)){
        nivel->defensores[nivel->tope_defensores].posicion.fil =posicion.fil;
        nivel->defensores[nivel->tope_defensores].posicion.col = posicion.col;
        nivel->defensores[nivel->tope_defensores].tipo= tipo;
        if (tipo == ELFOS)
            nivel->defensores[nivel->tope_defensores].fuerza_ataque =  FUERZA_ELFOS;
        else 
            nivel->defensores[nivel->tope_defensores].fuerza_ataque =  FUERZA_ENANOS;
        nivel->tope_defensores++;
        return 0;
    }
    return -1;     
}
/*
* preguntara al ususario que tipo de defensor desea agregar, validara la respuesta y restara un defensor extra (enano o elfo segun elija) en caso de que la respuesta sea si.
*/
void que_defensor(juego_t* juego){
    printf("que tipo de defensor deseas agregar? ELFO (L) O ENANO (G)");
    scanf(" %c", &juego->nivel.defensores[juego->nivel.tope_defensores].tipo);
    while (juego->nivel.defensores[juego->nivel.tope_defensores].tipo != ENANOS && juego->nivel.defensores[juego->nivel.tope_defensores].tipo != ELFOS){
        printf("incorrecto!, escribelo en mayusculas  ");
        scanf(" %c", &juego->nivel.defensores[juego->nivel.tope_defensores].tipo);
    }
    if (juego->nivel.defensores[juego->nivel.tope_defensores].tipo== ENANOS){
        if(juego->torres.enanos_extra > 0){
            juego->torres.enanos_extra --;
        }
        else {
            printf("lo lamento no tienes mas enanos disponibles para agregar \n");
        }
    }
    else if(juego->nivel.defensores[juego->nivel.tope_defensores].tipo== ELFOS){
        if(juego->torres.elfos_extra > 0){
            juego->torres.elfos_extra --;
        }
        else{
            printf(" lo lamento no tienes mas elfos disponibles para agregar \n");
        }
    }
}
/*
* En caso de que el ususario lo desee guardara la posicion de un nuevo defensor, sustrera un defensor del stock de defensores extras y restara 50 puntos de vida a la torre correspondiente.
*/
void  agregar_nuevo_defensor(juego_t* juego, defensor_t defensores[MAX_DEFENSORES], int* tope_defensores, int tope_matriz, char tipo, int* resistencia_torre ){
    char respuesta;
    coordenada_t posicion;
    printf("Atencion! tenes la oportunidad de agregar a un personaje defensor! desea hacerlo? presione S para si o N para no \n");
    scanf(" %c", &respuesta);
    while (respuesta != SI && respuesta != NO ){
        printf("INCORRECTO! si desea agregar un defensor presione S de lo contrario presione N \n");
        scanf(" %c", &respuesta);
    }
    if (respuesta== SI ){
        printf("ingrese fila y luego columna (");
        scanf("%i", &posicion.fil);
        printf(", ");
        scanf("%i", &posicion.col);
        while (agregar_defensor(&juego->nivel, posicion, tipo)== -1 || juego->nivel.defensores[juego->nivel.tope_defensores].posicion.fil > tope_matriz || juego->nivel.defensores[juego->nivel.tope_defensores].posicion.col > tope_matriz){
            printf("No puedes ubicar tu defensor alli, debes ingresar una nueva coordenada ingrese fila y luego columna (");
            scanf("%i", &posicion.fil);
            printf(", ");
            scanf("%i", &posicion.col);
        }
        if (juego->nivel_actual == 3 || juego->nivel_actual ==4){
            que_defensor(juego);
        }
        else if (juego->nivel_actual ==1 ){
            juego->torres.enanos_extra --;
        }  
        else if(juego->nivel_actual ==2){
            juego->torres.elfos_extra --;
        } 
        *resistencia_torre= *resistencia_torre - VIDA_QUITADA_TORRE;
    }
    else{
        printf("De acuerdo! \n");
    }  
}


/* recibe un vector de defensores y una posicion
* devuelve true si la posicion esta ocupada por un defensor o false si no lo esta.
*/
bool es_defensor(defensor_t defensores[MAX_DEFENSORES], int tope_defensor, coordenada_t posicion, int* ubicacion){
    bool es_un_elfo = false;
    bool es_un_enano = false;
    int i = 0;
    while(!es_un_elfo && i < tope_defensor && defensores[i].tipo== ELFOS){
        if(defensores[i].posicion.fil == posicion.fil && defensores[i].posicion.col == posicion.col){
            es_un_elfo = true;
            *ubicacion= i;
        }
        i++;
    }
    while(!es_un_enano && i < tope_defensor && defensores[i].tipo== ENANOS){
        if(defensores[i].posicion.fil == posicion.fil && defensores[i].posicion.col == posicion.col){
            es_un_enano = true;
            *ubicacion=i;
        }
        i++;
    }
    return es_un_elfo || es_un_enano;  
}
/* recibe un vector de enemigos y una posicion
* devuelve true si la posicion esta ocupada por un enemigo o false si no lo esta.
*/
bool es_enemigo(enemigo_t enemigos[MAX_ENEMIGOS], int tope_enemigos, coordenada_t camino[MAX_LONGITUD_CAMINO], coordenada_t posicion){
    bool es_un_enemigo = false;
    int i = 0;
    while(!es_un_enemigo && i < tope_enemigos){
        coordenada_t coordenada_camino = camino[enemigos[i].pos_en_camino];
        if(coordenada_camino.fil == posicion.fil && coordenada_camino.col == posicion.col && enemigos[i].vida >0)
            es_un_enemigo = true;
        i++;
    }
    return es_un_enemigo;   
}
/* recibe dos caminos y dos posiciones
* devuelve true si alguna posicion esta ocupada por una torre o false si no lo esta.
*/
bool es_torre(coordenada_t camino[MAX_LONGITUD_CAMINO], coordenada_t torre, int tope_camino){
    if (camino[tope_camino-1 ].col == torre.col && camino[tope_camino -1].fil == torre.fil) 
        return true;
    return false;
}
/* recibe dos caminos y dos posiciones
* devuelve true si alguna posicion esta ocupada por una entrada o false si no lo esta.
*/
bool es_entrada(coordenada_t camino[MAX_LONGITUD_CAMINO], coordenada_t entrada){
    if (camino[0].col == entrada.col && camino[0].fil == entrada.fil) 
        return true;
    return false;
}


/* recibe la ubicacion de los enemigos y verifica si es igual a las torres,
* si son iguales y la vida del enemigo es mayor a 0 se le resta a la torre la vida que tenga el enemigo, y el enemigo queda con vida 0.
*/
void torre_atacada_por_orcos(juego_t* juego){
    if(juego->torres.resistencia_torre_1 > 0 ){
        for(int i=0; i<juego->nivel.tope_enemigos; i++){
            if(juego->nivel.enemigos[i].pos_en_camino == juego->nivel.tope_camino_1-1 && juego->nivel.enemigos[i].vida>=0 && juego->nivel.enemigos[i].camino==1){
                juego->torres.resistencia_torre_1= juego->torres.resistencia_torre_1 - (juego->nivel.enemigos[i].vida); 
                juego->nivel.enemigos[i].vida= 0;
            }
        }
    }
    if(juego->torres.resistencia_torre_2 >0){
         for(int i=0; i<juego->nivel.tope_enemigos; i++){
            if(juego->nivel.enemigos[i].pos_en_camino == juego->nivel.tope_camino_2-1 && juego->nivel.enemigos[i].vida>=0  && juego->nivel.enemigos[i].camino==2){
                juego->torres.resistencia_torre_2= juego->torres.resistencia_torre_2 - (juego->nivel.enemigos[i].vida); 
                juego->nivel.enemigos[i].vida= 0;
            }
        }
    } 
}

/* 
* mueve cada orco una posicion mas adelante en su camino si no se encuentran en el tope del camino y su vida es mayor a 0.
*/
void avance_orcos(juego_t* juego){
    for(int i= 0; i < juego->nivel.tope_enemigos; i++){ 
        if (juego->nivel.enemigos[i].pos_en_camino < juego->nivel.tope_camino_1  && juego->nivel.enemigos[i].camino ==1 && juego->nivel.enemigos[i].vida > 0){
            juego->nivel.enemigos[i].pos_en_camino ++;
        }
        else if (juego->nivel.enemigos[i].pos_en_camino < juego->nivel.tope_camino_2 && juego->nivel.enemigos[i].camino ==2 && juego->nivel.enemigos[i].vida > 0){
            juego->nivel.enemigos[i].pos_en_camino ++;
        }
    }
}
/*
* ubica de a un orco en la posicion 0 del camino 1, aumenta su tope y define su cantidad de vida.
*/
void inicializar_orcos (juego_t* juego){
    juego->nivel.enemigos[juego->nivel.tope_enemigos].camino= PRIMER_CAMINO;
    juego->nivel.enemigos[juego->nivel.tope_enemigos].pos_en_camino=0;
    juego->nivel.enemigos[juego->nivel.tope_enemigos].vida= VIDA_BASE_ORCOS +rand()% EXTRA_ORCOS;
    if(juego->nivel.tope_enemigos < juego->nivel.max_enemigos_nivel)
        juego->nivel.tope_enemigos++;
}
/*
* ubica de a un orcos en la posicion 0 del camino 2, aumenta su tope y define su cantidad de vida.
*/
void inicializar_orcos_3y4(juego_t* juego){     
    juego->nivel.enemigos[juego->nivel.tope_enemigos].camino= SEGUNDO_CAMINO;
    juego->nivel.enemigos[juego->nivel.tope_enemigos].pos_en_camino=0;
    juego->nivel.enemigos[juego->nivel.tope_enemigos].vida= VIDA_BASE_ORCOS +rand()% EXTRA_ORCOS;
    if(juego->nivel.tope_enemigos < juego->nivel.max_enemigos_nivel){
        juego->nivel.tope_enemigos++;
    }
}

/*
* Cuando llega a la cantidad requerida de orcos pregunta si el usuario quiere agregar un nuevo defensor.
*/
void pregunta_defensores_nuevos(juego_t* juego, int tope_matriz, int* resistencia_torre){
    if(juego->nivel.tope_enemigos!=0 && juego->nivel.tope_enemigos < juego->nivel.max_enemigos_nivel && (juego->nivel.tope_enemigos % CANTIDAD_PARA_EXTRA_1) ==0 && juego->nivel_actual == PRIMER_NIVEL && juego->torres.enanos_extra > 0){
        agregar_nuevo_defensor(juego, juego->nivel.defensores, &juego->nivel.tope_defensores, tope_matriz, ENANOS, resistencia_torre);       
    }
    else if (juego->nivel.tope_enemigos!=0 && juego->nivel.tope_enemigos < juego->nivel.max_enemigos_nivel && (juego->nivel.tope_enemigos % CANTIDAD_PARA_EXTRA) ==0  && juego->nivel_actual == SEGUNDO_NIVEL && juego->torres.elfos_extra > 0){
        agregar_nuevo_defensor(juego, juego->nivel.defensores, &juego->nivel.tope_defensores, tope_matriz, ELFOS, resistencia_torre);   
    }
    else if (juego->nivel.tope_enemigos!=0 && juego->nivel.tope_enemigos < juego->nivel.max_enemigos_nivel && (juego->nivel.tope_enemigos % CANTIDAD_PARA_EXTRA) ==0 && (juego->nivel_actual == TERCER_NIVEL || juego->nivel_actual == CUARTO_NIVEL)){
        agregar_nuevo_defensor(juego, juego->nivel.defensores, &juego->nivel.tope_defensores, tope_matriz, ELFOS, resistencia_torre); 
    }
}
/* devuelve true si dos puntos estan a distancia manhattan menor o igual a 3, y false si no lo estan.
*/
bool esta_a_manhattan(coordenada_t defensor, coordenada_t enemigo){
    bool llega_el_ataque=false;
    if (abs(defensor.fil-enemigo.fil) + abs(defensor.col-enemigo.col) <= DIST_MANHATTAN)
        llega_el_ataque=true;
    return llega_el_ataque;
}
/* 
* devuelve true si hay un enemigo dentro del rango de ataque de un enano, o false en caso contrario.
*/
bool esta_alrededor_enano(coordenada_t defensor, coordenada_t enemigo){
    bool llega_el_ataque=false;
    int i=defensor.fil -1; 
    while(!llega_el_ataque && (i<= (defensor.fil +1))){ 
        int j= defensor.col -1;
        while(!llega_el_ataque && j <= (defensor.col + 1)){
                if (enemigo.fil==i && enemigo.col==j && enemigo.fil != defensor.fil && enemigo.col != defensor.col)
                    llega_el_ataque= true;
            j++;
        }
        i++;
    }   
    return llega_el_ataque;
}
/* devuelve el valor correcto para atacar.
*/
int calular_fuerza_ataque( int critico, int fallo, int letal, int comun){
    int numero_porcentual= rand()% 100;
    if (numero_porcentual > fallo ){
        if(numero_porcentual < critico ){
            return letal;
        }
        else {
            return comun;
        }
    }
    else return 0;
}

/* quita vida a un enemigo si esta a distancia manhattan menor o igual a tres de un elfo. 
* o si esta  alrededor de un enano.
*/
void realizar_ataque(juego_t* juego, defensor_t defensores, coordenada_t camino,  char tipo, int *vida){
    int contador =0;
    if(esta_a_manhattan( defensores.posicion, camino) && tipo == ELFOS){
        *vida-= calular_fuerza_ataque(juego->critico_legolas, juego->fallo_legolas,  ATAQUE_LETAL_ELFOS, FUERZA_ELFOS);

    }
    else if(esta_alrededor_enano( defensores.posicion, camino) && tipo ==ENANOS && contador==0){
        *vida-= calular_fuerza_ataque(juego->critico_gimli, juego->fallo_gimli, ATAQUE_LETAL_ENANOS, FUERZA_ENANOS);
        contador++;
    }
}
/* 
* recorre los vectores de enemigos y de defensores para restarle puntos de vida a los enemigos correspondientes (que se encuentren en el rango de elfos o enanos) y tengan vida mayor que 0.
*/
void ataque_defensores( juego_t* juego, defensor_t defensores[MAX_DEFENSORES], char tipo){
    for(int i=0; i<juego->nivel.tope_defensores; i++){
        for(int j=0; j<juego->nivel.tope_enemigos; j++){
            if (juego->nivel.enemigos[j].vida > 0 && defensores[i].tipo == tipo){
                if (juego->nivel.enemigos[j].camino== PRIMER_CAMINO)
                    realizar_ataque(juego, defensores[i], juego->nivel.camino_1[juego->nivel.enemigos[j].pos_en_camino], tipo, &juego->nivel.enemigos[j].vida);
                else if(juego->nivel.enemigos[j].camino == SEGUNDO_CAMINO)
                    realizar_ataque(juego, defensores[i], juego->nivel.camino_2[juego->nivel.enemigos[j].pos_en_camino], tipo, &juego->nivel.enemigos[j].vida);
            }
        }
    }
}

void jugar_turno(juego_t* juego){
    if (juego->nivel_actual== PRIMER_NIVEL || juego->nivel_actual == SEGUNDO_NIVEL){
        ataque_defensores( juego, juego->nivel.defensores,  ENANOS);
        ataque_defensores( juego, juego->nivel.defensores,  ELFOS);
        avance_orcos( juego); 
        inicializar_orcos(juego);
        pregunta_defensores_nuevos(juego, MAX_MATRIZ_1, &juego->torres.resistencia_torre_1);
        torre_atacada_por_orcos(juego);
    }
    else if(juego->nivel_actual == TERCER_NIVEL || juego->nivel_actual == CUARTO_NIVEL){
        ataque_defensores( juego, juego->nivel.defensores,  ENANOS);
        ataque_defensores( juego, juego->nivel.defensores,  ELFOS);
        avance_orcos( juego);
        inicializar_orcos(juego);
        inicializar_orcos_3y4(juego);
        if (rand()% 2 < 2){
            pregunta_defensores_nuevos(juego, MAX_MATRIZ_1, &juego->torres.resistencia_torre_1);
        }
        else{ 
            pregunta_defensores_nuevos(juego, MAX_MATRIZ_1, &juego->torres.resistencia_torre_2);
        }
        torre_atacada_por_orcos(juego);
    }
}
void imprimir_datos(juego_t juego){
    printf(" -------------------------- \n");
    for (int k=0; k<juego.nivel.tope_enemigos; k++){
        printf (" vida orco %i es %i   ",k, juego.nivel.enemigos[k].vida);
    }
    for(int i=0; i<juego.nivel.tope_defensores; i++){
        printf(" el defensor %i es de tipo %c ",i,  juego.nivel.defensores[i].tipo );
        printf(" y tiene fuerza de ataque %i  ", juego.nivel.defensores[i].fuerza_ataque);
        printf(" y su posicion es fil: %i , col: %i \n", juego.nivel.defensores[i].posicion.fil, juego.nivel.defensores[i].posicion.col);
    }
    printf("la resistencia de la torre 1 es %i \n y la de la torre 2 es %i", juego.torres.resistencia_torre_1, juego.torres.resistencia_torre_2);
    printf(" -------------------------- \n");
}
/*recibe un juego con sus estructuras validas
* asigna un caracter o entero a cada coordenada dependiendo que encuentre en ella
*/
void mostrar_nivel_1_2(juego_t juego, char defensor){
    for(int i=0; i< MAX_MATRIZ_1; i++){
        for(int j=0; j< MAX_MATRIZ_1; j++){
            int ubicacion=0;
            if(es_torre( juego.nivel.camino_1,inicializar_coordenada(i, j), juego.nivel.tope_camino_1) && juego.torres.resistencia_torre_1 >0)
                printf(COLOR_VERDE"%c  "COLOR_NORMAL, TORRE);
            else if(es_entrada( juego.nivel.camino_1,inicializar_coordenada(i, j)))
                printf(COLOR_VERDE"%c  "COLOR_NORMAL, ENTRADA);
            else if(es_defensor(juego.nivel.defensores, juego.nivel.tope_defensores, inicializar_coordenada(i, j), &ubicacion))
                printf(COLOR_CYAN"%c  "COLOR_NORMAL, juego.nivel.defensores[ubicacion].tipo);
            else if(es_enemigo(juego.nivel.enemigos, juego.nivel.tope_enemigos, juego.nivel.camino_1, inicializar_coordenada(i, j))) 
                printf(COLOR_MAGENTA"%c  "COLOR_NORMAL, ENEMIGO);
            else if(posicion_invalida(juego.nivel.camino_1, juego.nivel.camino_2, juego.nivel.tope_camino_1, juego.nivel.tope_camino_2, inicializar_coordenada(i, j)))
                printf(COLOR_ROJO"%c  "COLOR_NORMAL, CAMINO);
            else
                printf(COLOR_AMARILLO"%c  "COLOR_NORMAL, TERRENO);
        }
        printf("\n");
    }
    imprimir_datos(juego);
}
/*recibe un juego con sus estructuras validas
* asigna un caracter o entero a cada coordenada dependiendo que encuentre en ella
*/
 void mostrar_nivel_3_4(juego_t juego){ 
    for(int i=0; i<MAX_MATRIZ_2; i++){
        for(int j=0; j<MAX_MATRIZ_2; j++){
            int ubicacion=0;
            if(es_torre(juego.nivel.camino_1, inicializar_coordenada(i, j), juego.nivel.tope_camino_1) && juego.torres.resistencia_torre_1 >0)
                printf(COLOR_VERDE"%c  "COLOR_NORMAL, TORRE);   
            else if(es_torre( juego.nivel.camino_2,inicializar_coordenada(i, j),juego.nivel.tope_camino_2) && juego.torres.resistencia_torre_2 >0)
                printf(COLOR_VERDE"%c  "COLOR_NORMAL, TORRE);  
            else if(es_entrada( juego.nivel.camino_1,inicializar_coordenada(i, j)))
                printf(COLOR_VERDE"%c  "COLOR_NORMAL, ENTRADA);
            else if(es_entrada( juego.nivel.camino_2,inicializar_coordenada(i, j)))
                printf(COLOR_VERDE"%c  "COLOR_NORMAL, ENTRADA);                   
            else if(es_defensor(juego.nivel.defensores, juego.nivel.tope_defensores, inicializar_coordenada(i, j), &ubicacion))
                    printf(COLOR_CYAN"%c  "COLOR_NORMAL, juego.nivel.defensores[ubicacion].tipo);
            else if(es_enemigo(juego.nivel.enemigos, juego.nivel.tope_enemigos, juego.nivel.camino_1, inicializar_coordenada(i, j)))
                printf(COLOR_MAGENTA"%c  "COLOR_NORMAL, ENEMIGO);
            else if(es_enemigo(juego.nivel.enemigos, juego.nivel.tope_enemigos, juego.nivel.camino_2, inicializar_coordenada(i, j)))
                printf(COLOR_MAGENTA"%c  "COLOR_NORMAL, ENEMIGO);
            else if(posicion_invalida(juego.nivel.camino_1, juego.nivel.camino_2, juego.nivel.tope_camino_1, juego.nivel.tope_camino_2, inicializar_coordenada(i,j)))
                printf(COLOR_ROJO"%c  "COLOR_NORMAL, CAMINO);
            else
                printf(COLOR_AMARILLO"%c  "COLOR_NORMAL, TERRENO);
        }
        printf("\n");
    }
    imprimir_datos(juego);
}

/* recibe un nivel con las coordenadas de camino, matriz, orcos y defensores validados
* muestra el terreno del nivel pasado por parametro
*/
void mostrar_terreno(juego_t juego, int nivel_actual){
    if(nivel_actual == 1)
        mostrar_nivel_1_2(juego, ENANOS);
    else if(nivel_actual == 2) 
        mostrar_nivel_1_2(juego, ELFOS);
    else  
         mostrar_nivel_3_4(juego); 
}

/* imprime en pantalla la matriz con sus datos cargados y validos
*
*/
void mostrar_juego(juego_t juego){
    mostrar_terreno(juego, juego.nivel_actual);
}
