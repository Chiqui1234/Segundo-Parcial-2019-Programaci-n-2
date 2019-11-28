// Bibliotecas
#include <stdio.h>
#include <stdlib.h>
// MACROS para los algoritmos
#define CANT_TIPO_PLANTAS 3
// MACROS para nombres de archivos
#define PLANTAS "plantas.dat"
#define FERTILIZANTES "fertilizantes.txt"
// MACROS útiles para los miembros de algunas estructuras
#define NOMBRE_SIZE 40+1
#define COMPONENTE_SIZE 80+1

/** ¿Qué tengo que hacer?
 * plantas.dat es un binario ordenado por id sin registros duplicados.
 *      ID (0~256) | Nombre[40] | Tipo = {A, T, O}
 * crecimiento.dat es un binario que está ordenado por "llegada de los datos", es decir, por fecha.
 *      ID Fertilizante (1~10) | ID Planta (0~256) | Fecha (DDMMYYYY) | Ml de fertilizante (2 dígitos) | Cm de altura (2 dígitos)
 *      Según entiendo, el campo 4 se refiere a los mililitros utilizados en esa fecha. De igual modo los cm de altura se refiere a la altura total de la planta, no la diferencia de altura con respecto al día anterior (este dato tendríamos que procesarlo en el algoritmo).
 *      El profe sugiere implementar la "Fórmula C":
 *      C = (H2 - H1) / T, dónde H1 y H2 son alturas medidas de la planta y la T es el tiempo. Si tomáramos hoy la altura de un arbol y da 200cm y al día siguiente da 201cm, tendríamos que hacer (según entiendo):
 *      (201 - 200) / 1 día
 * fertilizantes.txt es un archivo de texto, dónde cada línea contiene:
 *      ID Fertilizante (1~10);Nombre[40];Componente1,Componente2,ComponenteN[80];Precio por Ml de fertilizante (2 dígitos);Tipo = {N, Q}
 *      Hay que tener en cuenta que estos campos (literal) están escritos en la primer línea del .txt, por lo que hay que avanzar una línea antes de leer.
 * 
 * SE PIDE generar un binario con un registro por planta, dónde se indique el índice de crecimiento mensual y anual (esto se calcula con la "Fórmula C"). También se debe imprimir, para cada TIPO de planta, los datos del fertilizante con mejor rendimiento anual (se haría con "Fórmula C" dividido el precio).
 * Restricciones / Consideraciones: 1 mes = 30 días y 1 año = 365 días. crecimiento.dat está completo y ambos binarios se pueden recorrer secuencialmente una vez. Nodo de hasta 20 bytes, memoria estática de hasta 15 bytes.
 */

typedef struct planta // Igual a plantas.dat, pero sin fecha (sólo ordeno por ID de Planta)
{
    short int idP;          // id planta
    short int idF;          // id fertilizante
    short int cantidadF;    // cantidad fertilizante (mililitros)
    short int altura;
    char tipo;              // A, T, O
} ST_PLANTA; // 8 bytes

typedef struct nodoPlantas
{
    ST_PLANTA planta;
    float formulaC; // Este miembro no forma parte de la estructura de crecimiento.dat. Acá se guarda un registro que se actualiza día a día (osea, los 365 días del año). Luego se divide por 12 para tener un promedio de crecimiento por mes.
    struct nodoPlantas *ste;
} ST_NODO; // 16 bytes

typedef struct mejorFertilizante // La uso para guardar los récords de los mejores fertilizantes (de los 3 tipos de planta)
{
    int id;
    float formulaC; // El mejor fertilizante es el que tiene mayor "Fórmula C"
} ST_FERTILIZANTE;

typedef struct fertilizante // Me sirve para parsear fertilizante.txt
{
    short int id;
    char nombre[NOMBRE_SIZE];
    char componentes[COMPONENTE_SIZE];
    short int precioMl;
    char tipo; // N (Natural) ó Q (Químico)
} BIN_FERTILIZANTE;

typedef enum tipoDePlanta // Este tipo de dato se creó para que *obtenerTipoDePlanta devuelva un número en vez de una letra. Siendo que el tipo de planta A se guarda en la celda 0 de un vector, T en la celda 1 y la O en la celda dos
{
    A = 0,
    T = 1,
    O = 2
} TIPO;

// Funciones de nodos
ST_NODO *crearNodo(ST_PLANTA aux);
ST_NODO *insertarOrdenadoSinDuplicarEdicionEzpezial(ST_NODO **cabecera, ST_PLANTA dato); // Del binario a una lista única

// Funciones de archivos
FILE *open(const char *nombre, const char *permiso);

// Funciones
void cargarCrecimiento(ST_NODO **cabecera, const char *nombre);
TIPO *obtenerTipoDePlanta(ST_NODO *cabecera, int id); // Cuándo encuentra la planta buscada, devuelve su tipo
void calcularMejoresFertilizantes(ST_NODO **cabecera, ST_FERTILIZANTE mejorFertilizante[], const char *archivoFertilizantes); // Esta función recorre mi cabecera y por cada planta que lee compara el récord que hay para "formulaC" y, si es mayor que el récord, se lo guarda. 
BIN_FERTILIZANTE obtenerFertilizante(int id, const char *nombre); // Parsea y devuelve el fertilizante, que se busca por ID
void calcularFormulaC(ST_NODO **cabecera);