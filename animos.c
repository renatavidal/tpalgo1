
#include "animos.h"


const char MANANA= 'M';
const char TARDE= 'T';
const char NOCHE= 'N';
const char PIE_DERECHO = 'D';
const char PIE_IZQUIERDO = 'I';
const char HAMBURGUESA= 'H';
const char PIZZA= 'P';
const char ENSALADA ='E';
const char GUISO='G';
const char BUEN_HUMOR= 'B';
const char REGULAR_HUMOR= 'R';
const char MAL_HUMOR='M';
const int SUENIO_MIN = 0;
const int SUENIO_MEDIO = 4;
const int SUENIO_ALTO = 8;
const int SUENIO_MAX = 12;
const int HUMEDAD_MAX = 75;
const int HUMEDAD_MEDIA= 50;
const int HUMEDAD_MIN= 25;
const int VIENTO_MAX = 75;
const int VIENTO_MEDIO= 50;
const int VIENTO_MIN= 25;
const int PRIMER_DIA= 1;
const int ULTIMO_DIA = 30;
const int DIA_PRIMERA_MITAD= 10;
const int DIA_SEGUNDA_MITAD = 20;
const int PUNTAJE_PIE_IZQ = 0;
const int PUNTAJE_PIE_DER = 10;
const int PUNTAJE_GUISO = 5;
const int PUNTAJE_PIZZA= 10;
const int PUNTAJE_HAMBURGUESA= 15;
const int PUNTAJE_ENSALADA= 20;
const int PUNTAJE_SUENIO_ALTO = 20;
const int PUNTAJE_SUENIO_MEDIO = 10;
const int PUNTAJE_SUENIO_BAJO = 0;
const int PUNTAJE_FINAL_MIN = 5;
const int PUNTAJE_FINAL_BAJO = 20;
const int PUNTAJE_FINAL_ALTO = 35;
const int PUNTAJE_FINAL_MAX = 50;



/* 
*pre condicion: 
*post condicion: la funcion devuelve true si hora cumple con las condiciones solicitadas de horario (ser igual a M, T O N), de lo contrario de devuelve false. 
*/
bool hora_valida( char hora){
     return(hora == MANANA || hora == TARDE || hora == NOCHE);}
/* 
*pre condicion: -
*post condicion: hora es M, T O N (excluyente).
*/
void pedir_hora_valida (char* hora){
    printf("otra pregunta: que hora es? va, mejor dicho, es mañana tarde o noche? Para mañana presiona M mayuscula, para tarde presione T mayuscula y para noche presione N mayuscula \n");
    scanf(" %c", hora);
      
    while (!hora_valida(*hora)){
      printf("Atencion! necesitamos que te concentres, te dijimos que presiones M, T o N segun sea manana, tarde o noche respectivamente  \n");
      scanf(" %c", hora);} 
}

/* 
*pre condicion: 
*post condicion: la funcion devuelve true si hora es igual a MANANA, de lo contrario devuelve false. 
*/

bool temprano(char hora){
     return (hora == MANANA);}
/* 
*pre condicion: 
*post condicion: la funcion devuelve true si hora es igual a TARDE, de lo contrario devuelve false. 
*/

bool medio_dia(char hora){
     return (hora == TARDE);}
/* 
*pre condicion: 
*post condicion: la funcion devuelve true si hora es igual a NOCHE, de lo contrario devuelve false. 
*/

bool anochecer(char hora){
     return (hora == NOCHE);}

/* 
*pre condicion: 
*post condicion: valor de humedad es determinado segun valor de hora, 75 si es temprano, 25 si es medio dia y 75 si es anochecer .
*/

int dia_humedo (char hora){
   int humedad;
   if(temprano (hora)){
      (humedad = HUMEDAD_MAX);}
   if(medio_dia (hora)){
      (humedad = HUMEDAD_MIN );}
   if(anochecer (hora)){
      (humedad = HUMEDAD_MEDIA);}
return humedad;
}

/* 
*pre condicion: 
*post condicion: la funcion devuelve true si dias_del_mes es valido por estar dentro del rango de dias solicitado (de 1 a 30), de lo contrario devuelve false. 
*/ 

bool dias_validos(int dia_del_mes){
     return(dia_del_mes>= PRIMER_DIA && dia_del_mes<= ULTIMO_DIA);}

/* 
*pre condicion: 
*post condicion: hora es M, T O N (excluyente).
*/

void pedir_dia_valido (int *dia_del_mes){
    printf(" Buenos dias! necesitamos su ayuda, hay tres datos que son claves para planear estrategias, la velocidad del viento, el porcentaje de humedad y el animo de los lideres, Legolas y Gimli. Claramente no pretendemos que sepas  esos datos, de eso nos encargamos los expertos, de hecho no se porque le di esa informacion confidencial... tendre que matarlo? *se escuchan voces del fondo* bueno me dicen que no... tan solo buscamos que contestes unas simples preguntas");
     printf(" primera pregunta: que dia del mes es? necesitamos que lo ingreses en numeros (entre 1 y 30) \n");
     scanf("%i", dia_del_mes);

      while (!dias_validos(*dia_del_mes)){
           printf("Atencion! necesitamos que te concentres, te dijimos que nos digas que dia es, no puede ser menor que 1 ni mayor que 30  \n");
           scanf(" %i", dia_del_mes);} 
}


/* 
*pre condicion:
*post condicion: la funcion devuelve true si cumple con el rango valido de dias para ser los primeros dias del mes (de 1 a 10).
*/
bool primeros_dias(int dia_del_mes){
     return (dia_del_mes >= PRIMER_DIA && dia_del_mes <= DIA_PRIMERA_MITAD);}
/* 
*pre condicion: :
*post condicion: la funcion devuelve true si cumple con el rango valido de dias para ser los dias medios del mes(de 11 a 20).
*/


bool mitad_dias(int dia_del_mes){
     return (dia_del_mes > DIA_PRIMERA_MITAD && dia_del_mes <= DIA_SEGUNDA_MITAD);} 

/* 
*pre condicion: :
*post condicion: la funcion devuelve true si cumple con el rango valido de dias para ser los ultimos dias del mes (de 21 a 30).
*/

bool ultimos_dias(int dia_del_mes){
     return (dia_del_mes > DIA_SEGUNDA_MITAD && dia_del_mes <= ULTIMO_DIA);}

/* 
*pre condicion: dias_del_mes tiene un valor dentro del rango valido de dias del mes solicitado (de 1 a 30 inclusive).
*post condicion: se determina la velocidad del viento segun que dia del mes es.
*/

int fecha(int dia_del_mes){
     int viento;
     if(primeros_dias(dia_del_mes)){
        (viento= VIENTO_MAX);}
     else if(mitad_dias(dia_del_mes)){
       (viento= VIENTO_MEDIO);}
     else if (ultimos_dias(dia_del_mes)){
       (viento= VIENTO_MIN);}
 return viento;     
}
/* 
*pre condicion: 
*post condicion: la funcion va a devolver true si pie_legolas cumple con ser uno de los dos requisitos para ser valida (I Para PIE_IZQUIERDO o D para PIE_DERECHO), o false en caso contrario.
*/

bool paso_valido_legolas(char pie_legolas){
      return (pie_legolas== PIE_IZQUIERDO || pie_legolas == PIE_DERECHO);}
/* 
*pre condicion: -
*post condicion: pie_legolas cumple con los requisitos para ser un dato valido (ser igual a I para pie izquierdo o D para pie derecho).
*/
void pedir_paso_valido_l (char *pie_legolas){
      
      printf("estas siendo de mucha ayuda para el equipo, unas ultimas preguntas y te dejaremos en libertad... esto es un poco mas personal,pero necesario. comenzaremos a especular sobre el humor de uno de los lideres, Legolas: con que pie se levanto hoy?  escribi I para izquierdo y D para derecho \n");
      scanf(" %c", pie_legolas);
      while (!paso_valido_legolas( *pie_legolas)){
           printf( "Atencion, te pedimos que escribas I para pie izquierdo y D para pie derecho! en mayusculas y primero legolas y luego gimli, vuelve a intentarlo \n");
           scanf(" %c", pie_legolas);}
}
/* 
*pre condicion: -
*post condicion: la funcion devuelve true si pie_legolas es el pie derecho (D) o false en caso contrario.
*/

bool paso_derecho_legolas (char pie_legolas){
     return(pie_legolas == PIE_DERECHO);}
/* 
*pre condicion: -
*post condicion: la funcion devuelve true si pie_legolas es el pie izquierdo (I) o false en caso contrario.
*/
bool paso_izquierdo_legolas (char pie_legolas){
     return( pie_legolas == PIE_IZQUIERDO);}

/* 
*pre condicion: pie_legolas es valido segun la determinacion de que sea derecho o izquierdo.
*post condicion:  el puntaje de legolas aumentara 10 si es pie derecho o sumara 0  si es izquierdo.
*/
void despertar_l (char pie_legolas, int *puntaje_legolas){ 
    if (paso_derecho_legolas(pie_legolas)){
       (*puntaje_legolas = PUNTAJE_PIE_DER);}
    else {
      (*puntaje_legolas = PUNTAJE_PIE_IZQ);}
}

/* 
*pre condicion:
*post condicion: si cena_legolas cumple con ser alguna de las cuatro comidas la funcion devolvera true, de lo contrario devolvera false.
*/

bool comida_legolas_valida (char cena_legolas){
     return(cena_legolas == ENSALADA || cena_legolas == GUISO || cena_legolas == PIZZA || cena_legolas == HAMBURGUESA);}
/* 
*pre condicion:-
*post condicion: cena_legolas sera valida por cumplir con ser una de las cuatro comidas requeridas, (E) para ensalada, (H) para hambuerguesa, (P) para pizza o (G) para guiso.
*/
void cena_valida_legolas(char *cena_legolas){
    
  printf("Ahora bien, sabemos que hay solo 4 comidas que puede haber comido: ensalada, hamburguesa, pizza o guiso. para contestar escribe la letra inicial de la comida en mayuscula \n");
  scanf(" %c", cena_legolas);

  while(!comida_legolas_valida (*cena_legolas)){
         printf("ojo! dijimos que escribas E para ensalada, H para hamburguesa, P para pizza o G para guiso. ninguna otra variable, ya sabemos que no comen otra cosa! y en mayusculas por favor ... \n");
         scanf(" %c", cena_legolas);}
}
/* 
*pre condicion: 
*post condicion: si cena_legolas cumple con ser E para ensalada la funcion devolvera true, de lo contrario devolvera false.
*/
bool ensalada_comida_legolas (char cena_legolas){
     return(cena_legolas == ENSALADA);}
/* 
*pre condicion: 
*post condicion: si cena_legolas cumple con ser H para hamburguesa la funcion devolvera true, de lo contrario devolvera false.
*/
bool hambuerguesa_comida_legolas (char cena_legolas){
     return(cena_legolas == HAMBURGUESA);} 
/* 
*pre condicion: 
*post condicion: si cena_legolas cumple con ser P para pizza la funcion devolvera true, de lo contrario devolvera false.
*/
bool pizza_comida_legolas (char cena_legolas){
     return(cena_legolas == PIZZA);}
/* 
*pre condicion: 
*post condicion: si cena_legolas cumple con ser G para guiso la funcion devolvera true, de lo contrario devolvera false.
*/
bool guiso_comida_legolas (char cena_legolas){
     return(cena_legolas == GUISO);}
/* 
*pre condicion: cena_legolas es  valido por cumplir con ser alguna de las 4 comidas permitidas.
*post condicion: el dato puntaje_legolas se modificara segun corresponda a cada comida, se sumara 20 para ensalada, 15 para hamburguesa, 10 para pizza y 5 para guiso.
*/

void valor_cena_legolas (char cena_legolas, int *puntaje_legolas){
 
 if   (ensalada_comida_legolas (cena_legolas)){
      (*puntaje_legolas = *puntaje_legolas + PUNTAJE_ENSALADA);}
 else if (hambuerguesa_comida_legolas (cena_legolas)){
      (*puntaje_legolas = *puntaje_legolas + PUNTAJE_HAMBURGUESA);}
 else if (pizza_comida_legolas (cena_legolas)){
      (*puntaje_legolas = *puntaje_legolas + PUNTAJE_PIZZA);}
 else {
      (*puntaje_legolas= *puntaje_legolas + PUNTAJE_GUISO);}

}      


/* 
*pre condicion: 
*post condicion: la funcion devolvera true si el valor de suenio_legolas esta dentro del rango se horas se suenio determinado (de 0 a 12), de lo contrario devolvera false.
*/

bool suenio_valido_legolas( int suenio_legolas){
     return (suenio_legolas >= SUENIO_MIN && suenio_legolas <= SUENIO_MAX);}
/* 
*pre condicion: -
*post condicion: el valor del int* suenio_legolas estara dentro del rango de horas determinado (de 0 a 12).
*/
void pedir_horas_de_suenio_validas_l (int *suenio_legolas){
  printf(" ultima pregunta sobre nuestro querido legolas! queremos saber cuantas horas durmio esta noche, podria decirnos? ingrese el numero de horas en digitos... sabemos que no es mas de 12 por favor tenga seriedad.. \n");
  scanf("%i", suenio_legolas);
 
  while (!suenio_valido_legolas(*suenio_legolas)){
  printf(" Por favor seriedad!! ingrese el numero de horas nuevamente, menos de 12 y de 0 en adelante por supuesto! \n");
  scanf("%i", suenio_legolas);}
}
/* 
*pre condicion: suenio_legolas tiene su valor dentro de los rangos solicitados para ser valido (entre 0 y 12).
*post condicion: puuntaje_legolas sera modificado segun los puntos correspondidos a la cantidad de horas de suenio, medidas en suenio_legolas 0 puntos de 0 a 4 horas de suenio, 10 puntos de 5 a 8 horas de suenio y 20 puntos de 9 a 12 horas de suenio.
*/
void puntos_suenio_legolas (int suenio_legolas, int *puntaje_legolas){

 if (suenio_legolas >= SUENIO_MIN && suenio_legolas <= SUENIO_MEDIO){               
      (*puntaje_legolas = *puntaje_legolas + PUNTAJE_SUENIO_BAJO);}   
 else if (suenio_legolas > SUENIO_MEDIO && suenio_legolas <= SUENIO_ALTO){
      (*puntaje_legolas = *puntaje_legolas + PUNTAJE_SUENIO_MEDIO);}
 else {
      (*puntaje_legolas= *puntaje_legolas + PUNTAJE_SUENIO_ALTO);}

}  

/* 
*pre condicion:-
*post condicion: la funcion devolvera true si pie_gimli tiene un valor que satisfaga ser I o D,y por ende sea valida.
*/
bool paso_valido_gimli(char pie_gimli){
      return (pie_gimli== PIE_IZQUIERDO || pie_gimli == PIE_DERECHO);}
/* 
*pre condicion: -
*post condicion: pie_gimli cumple con ser I o D, segun sea paso izquierdo o derecho.
*/
void pedir_paso_valido_g (char *pie_gimli){
      
      printf("vamos con las preguntas sobe gimli ahora: con que pie se levanto hoy?  escribi I para izquierdo y D para derecho \n");
      scanf(" %c", pie_gimli);
      while (!paso_valido_legolas( *pie_gimli)){
           printf( "Atencion, te pedimos que escribas I para pie izquierdo y D para pie derecho! en mayusculas y primero legolas y luego gimli, vuelve a intentarlo \n");
           scanf(" %c", pie_gimli);}
}    
/* 
*pre condicion:
*post condicion: la funcion devolvera true si pie_gimli es igual a D para pie derecho, de lo contrario devolvera false.
*/
bool paso_derecho_gimli (char pie_gimli){
     return(pie_gimli == PIE_DERECHO);}
/* 
*pre condicion: 
*post condicion: la funcion devolvera true si pie_gimli es igual a I para pie izquierdo, de lo contrario devolvera false.
*/
bool paso_izquierdo_gimli ( char pie_gimli){
     return (pie_gimli == PIE_IZQUIERDO);}
/* 
*pre condicion: pie_gimli esta determinado como valido por cumplir con ser I o D.
*post condicion: la funcion sumara a puntaje_gimli 10 si pie_gimli cumple con ser paso derecho, o sumara 0 si pie_gimli cumple con ser paso izquierdo.
*/
void despertar_g (char pie_gimli, int *puntaje_gimli){

    if (paso_izquierdo_gimli(pie_gimli)){
       (*puntaje_gimli = PUNTAJE_PIE_IZQ);}
    else if (paso_derecho_gimli(pie_gimli)){
       (*puntaje_gimli = PUNTAJE_PIE_DER);}

}

/* 
*pre condicion:-
*post condicion: la funcion devolvera true si cena_gimli es igual a alguna de las cuatro comidas (E,H,P o G),  de lo contrario devolvera false.
*/

bool comida_gimli_valida (char cena_gimli){
     return(cena_gimli == ENSALADA || cena_gimli == GUISO || cena_gimli == PIZZA || cena_gimli == HAMBURGUESA);}
/* 
*pre condicion: -
*post condicion: cena_gimli sera valida por cumplir  con ser una de las cuatro comidas requeridas, (E) para ensalada, (H) para hambuerguesa, (P) para pizza y (G) para guiso. 
*/
void cena_valida_gimli(char *cena_gimli){
    
    printf("Ahora bien, sabemos que gimli puede haber comido las mismas 4 comidas que legolas: ensalada, hamburguesa, pizza o guiso. para contestar escribe la letra inicial de la comida en mayuscula \n");
    scanf(" %c", cena_gimli);

    while(!comida_gimli_valida (*cena_gimli)){
         printf("ojo! dijimos que escribas E para ensalada, H para hamburguesa, P para pizza o G para guiso. ninguna otra variable, ya sabemos que no comen otra cosa! y en mayusculas por favor ... \n");
         scanf(" %c", cena_gimli);}
}
/* 
*pre condicion: 
*post condicion: la funcion devolvera true si cena_gimli es igual a E (para ensalada), de lo contrario devolvera false.
*/
bool ensalada_comida_gimli (char cena_gimli){
     return(cena_gimli == ENSALADA);}
/* 
*pre condicion: 
*post condicion: la funcion devolvera true si cena_gimli es igual a H (para hamburguesa), de lo contrario devolvera false.
*/
bool hambuerguesa_comida_gimli (char cena_gimli){
     return(cena_gimli == HAMBURGUESA);} 
/* 
*pre condicion: 
*post condicion: la funcion devolvera true si cena_gimli es igual a P (para pizza), de lo contrario devolvera false.
*/
bool pizza_comida_gimli (char cena_gimli){
     return(cena_gimli == PIZZA);}
/* 
*pre condicion:
*post condicion: la funcion devolvera true si cena_gimli es igual a G (para guiso), de lo contrario devolvera false.
*/
bool guiso_comida_gimli (char cena_gimli){
     return(cena_gimli == GUISO);}
/* 
*pre condicion: cena_gimli es igual alguno de los 4 dispuestos validos para las comidas (E,  H, P o G).
*post condicion: la variable puntaje_gimli se vera modificada al sumarle el valor correspondiente que se le asigno a cada comida.
*/

void valor_cena_gimli (char cena_gimli, int *puntaje_gimli){
 
 if (ensalada_comida_gimli (cena_gimli)){
      (*puntaje_gimli = *puntaje_gimli + PUNTAJE_ENSALADA);}
 else if (hambuerguesa_comida_gimli (cena_gimli)){
      (*puntaje_gimli = *puntaje_gimli + PUNTAJE_HAMBURGUESA);}
 else if (pizza_comida_gimli (cena_gimli)){
      (*puntaje_gimli = *puntaje_gimli + PUNTAJE_PIZZA);}
 else {
      (*puntaje_gimli= *puntaje_gimli + PUNTAJE_GUISO);}

}      

/* 
*pre condicion:-
*post condicion: la funcion devolvera true si suenio_gimli esta en el rango de horas establecido (de 0 a 12), de lo contrario devolvera false.
*/

bool suenio_valido_gimli( int suenio_gimli){
     return (suenio_gimli >= SUENIO_MIN && suenio_gimli <= SUENIO_MAX);}
/* 
*pre condicion: -
*post condicion: suenio_gimli sera valido por cumplir estar incluida en el rango de horas requerido (de 0 a 12 horas).
*/
void pedir_horas_de_suenio_validas_g (int *suenio_gimli){
  printf(" ultima pregunta! queremos saber cuantas horas durmio esta noche, podria decirnos? ingrese el numero de horas en digitos... sabemos que no es mas de 12 por favor tenga seriedad.. \n");
  scanf("%i", suenio_gimli);
 
  while (!suenio_valido_gimli(*suenio_gimli)){
  printf(" Por favor seriedad!! ingrese el numero de horas nuevamente, menos de 12 y de 0 en adelante por supuesto! \n");
  scanf("%i", suenio_gimli);}
}
/* 
*pre condicion: suenio_gimli cumple con los requisitos para ser valida (ser un numero entre 0 y 12).
*post condicion: puntaje_gimli sera modificada mediante la suma de puntaje correspondiente a cada rango horario de suenio, correspondiente al valor de suenio_gimli, 0 puntos de 0 a 4 horas de suenio, 10 puntos de 5 a 8 horas de suenio y 20 puntos de 9 a 12 horas de suenio.
*/
void puntos_suenio_gimli (int suenio_gimli, int *puntaje_gimli){ 
 if (suenio_gimli >= SUENIO_MIN && suenio_gimli <= SUENIO_MEDIO){
      (*puntaje_gimli = *puntaje_gimli + PUNTAJE_SUENIO_BAJO);}
 else if (suenio_gimli > SUENIO_MEDIO && suenio_gimli <= SUENIO_ALTO){
      (*puntaje_gimli = *puntaje_gimli + PUNTAJE_SUENIO_MEDIO);}
 else {
      (*puntaje_gimli= *puntaje_gimli + PUNTAJE_SUENIO_ALTO);}
}  

/* 
*pre condicion: viento esta dentro de los valores validos establecidos (25, 50 o 75).
*post condicion: imprimira en pantalla la porcion de resumen correspondiente a el valor que tome la variable viento.
*/

void resumen_viento (int viento){
   if (viento == VIENTO_MAX){
      printf(" Hoy hay un viento que te vuela el peluquin, ");} 
   else if (viento == VIENTO_MEDIO){
      printf(" Hoy el viento esta fuertecito, ");}
   else{
      printf(" Hoy el viento esta tranqui, ");}
}
/* 
*pre condicion: humedad es un valor dentro de los valores validos establecidos (25, 50 0 75).
*post condicion: imprimira en pantalla la porcion de resumen correspondiente a el valor que tome la variable humedad.
*/
void resumen_humedad (int humedad){
   if (humedad == HUMEDAD_MAX ){
      printf(" esta pesaaada la humedad,  ");}
   else if (humedad == HUMEDAD_MEDIA){
      printf(" hay bastante humedad, ");}
   else{
      printf(" esta sequito el clima, ");}
}
/* 
*pre condicion: el rango de valor de puntaje_legolas es de 5 a 50 inclusive.
*post condicion: imprimira en pantalla la porcion de resumen correspondiente a el valor que tome la variable puntaje_legolas.
*/
void resumen_legolas (int puntaje_legolas){
 if (puntaje_legolas >= PUNTAJE_FINAL_MIN && puntaje_legolas <= PUNTAJE_FINAL_BAJO){    
    printf(" el humor de legolas es... bueno, complicado, ");}
 else if (puntaje_legolas > PUNTAJE_FINAL_BAJO && puntaje_legolas <= PUNTAJE_FINAL_ALTO){
    printf(" el humor de legolas es medio medio,  ");}
 else {
    printf( " legolas esta ten points, ");}
}
/* 
*pre condicion: el rango de valor de puntaje_legolas es de 5 a 50 inclusive.
*post condicion: la funcion devolvera una constante (B, M o R) segun el valor que haya tomado puntaje_legolas, 'M' de 5 a 20, 'R' de 21 a 35, y 'B' de 36 a 50.
*/
char humor_legolas (int puntaje_legolas){
 if (puntaje_legolas >= PUNTAJE_FINAL_MIN && puntaje_legolas <= PUNTAJE_FINAL_BAJO){ 
   return MAL_HUMOR;}
 else if(puntaje_legolas > PUNTAJE_FINAL_BAJO && puntaje_legolas <= PUNTAJE_FINAL_ALTO){
   return REGULAR_HUMOR;}
 else{
   return BUEN_HUMOR;}
} 
/* 
*pre condicion:el rango de valor de puntaje_gimli es de 5 a 50 inclusive.
*post condicion: imprimira en pantalla la porcion de resumen correspondiente a el valor que tome la variable puntaje_gimli.
*/
void resumen_gimli( int puntaje_gimli){
 if (puntaje_gimli >= PUNTAJE_FINAL_MIN && puntaje_gimli <= PUNTAJE_FINAL_BAJO){    
    printf(" y el humor de gimli es terrible hoy \n");}
 else if (puntaje_gimli > PUNTAJE_FINAL_BAJO && puntaje_gimli <= PUNTAJE_FINAL_ALTO){     
    printf("y el humor de gimli esta medio pelo \n ");}
 else {   
    printf( "y gimli esta feli' \n ");}
}
/* 
*pre condicion: puntaje_gimli tiene un valor que se encuentra en un rango considerado valido por las sumas posibles. ese rango va de 5 a 50.
*post condicion: la funcion devolvera una constante (B, M o R) segun el valor que haya tomado puntaje_gimli, 'M' de 5 a 20, 'R' de 21 a 35, y 'B' de 36 a 50..
*/
char humor_gimli (int puntaje_gimli){
 if (puntaje_gimli >= PUNTAJE_FINAL_MIN && puntaje_gimli <= PUNTAJE_FINAL_BAJO){ 
   return MAL_HUMOR;}
 else if(puntaje_gimli > PUNTAJE_FINAL_BAJO && puntaje_gimli <= PUNTAJE_FINAL_ALTO){
   return REGULAR_HUMOR;}
 else{
   return BUEN_HUMOR;}
} 

void animos (int* viento, int* humedad, char* animo_legolas, char* animo_gimli){

    char hora;
    char pie_legolas, cena_legolas;
    char pie_gimli, cena_gimli;
    int dia_del_mes, suenio_legolas, suenio_gimli;
    int puntaje_gimli, puntaje_legolas;


    pedir_dia_valido (&dia_del_mes);
    *viento=fecha(dia_del_mes);

    pedir_hora_valida(&hora);
    *humedad=dia_humedo(hora);


    pedir_paso_valido_l (&pie_legolas);
    despertar_l ( pie_legolas, &puntaje_legolas);

   
    cena_valida_legolas(&cena_legolas);
    valor_cena_legolas (cena_legolas, &puntaje_legolas);


    pedir_horas_de_suenio_validas_l (&suenio_legolas);
    puntos_suenio_legolas (suenio_legolas, &puntaje_legolas);


    pedir_paso_valido_g (&pie_gimli);
    despertar_g (pie_gimli, &puntaje_gimli);

    cena_valida_gimli(&cena_gimli);
    valor_cena_gimli (cena_gimli, &puntaje_gimli);

    pedir_horas_de_suenio_validas_g (&suenio_gimli);
    puntos_suenio_gimli (suenio_gimli, &puntaje_gimli);
    
    resumen_viento (*viento);
    resumen_humedad (*humedad);
    resumen_legolas (puntaje_legolas); 
    resumen_gimli( puntaje_gimli);


    *animo_legolas= humor_legolas(puntaje_legolas);
    *animo_gimli= humor_gimli(puntaje_gimli);

}
