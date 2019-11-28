#include "funciones.h"
/** ¿Cómo voy a hacerlo?
 * plantas.dat accedo por pup. Chau.
 * crecimiento.dat lo cargo en una lista y añado varios campos más.
 * fertilizantes.txt tiene que ser parseado pero no lo cargo en RAM, porque no hay restricciones de lectura :3
 */
ST_NODO *crearNodo(ST_PLANTA aux)
{
    ST_NODO *nuevoNodo = (ST_NODO*) malloc(sizeof(ST_NODO)); // Pido memoria para un nodo nuevo
    nuevoNodo -> planta = aux;
    nuevoNodo -> formulaC = 0; // Este dato lo proceso después de cargar todos los registros de crecimiento en RAM. Take it easy :D
    nuevoNodo -> ste = NULL;
    return nuevoNodo;
}

void cargarCrecimiento(ST_NODO **cabecera, const char *nombre)
{
    FILE *crecimiento = open(nombre, "rb");
    ST_PLANTA aux; // Para leer el binario
    fread(&aux, sizeof(ST_PLANTA), 1, crecimiento);
    while( !feof(crecimiento) )
    {
        insertarOrdenadoSinDuplicarEdicionEzpezial(&cabecera, aux); // Si está duplicado, voy a aplicar la fórmula C entre el dato que ya tenía y el que estoy por insertar
        fread(&aux, sizeof(ST_PLANTA), 1, crecimiento);
    }
    return;
}

ST_NODO *buscar(ST_NODO *cabecera, ST_PLANTA dato)
{
    ST_NODO *aux = cabecera;
    return aux;
}

TIPO *obtenerTipoDePlanta(ST_NODO *cabecera, int id)
{
    ST_NODO *aux = cabecera;
    while( aux->planta.idP != id && aux->ste != NULL )
        aux = aux->ste;
    
    return aux->planta.idP == id?aux->planta.tipo:-1;
}

ST_NODO *insertarOrdenado(ST_NODO **cabecera, ST_PLANTA dato)
{
    ST_NODO *aux = *cabecera;
    ST_NODO *nodoAnt = NULL;
    ST_NODO *nuevoNodo = crearNodo(dato);
    nuevoNodo->formulaC = 0; // Esto es cero al iniciar porque lo actualizo cuándo hay "ID Planta" duplicado
    while( aux && dato.idP > aux->planta.idP )
    {
        nodoAnt = aux;
        aux = aux->ste;
    }
    if( nodoAnt == NULL )
        *cabecera = nuevoNodo;
    else
        nodoAnt->ste = nuevoNodo;
    nuevoNodo->ste = aux;
    return nuevoNodo;
}

ST_NODO *insertarOrdenadoSinDuplicarEdicionEzpezial(ST_NODO **cabecera, ST_PLANTA dato)
{
    ST_NODO *planta = buscar(*cabecera, dato); // Busco por ID de planta
    if( planta == NULL ) // Si no la encontré, la inserto
        insertarOrdenado(&cabecera, dato);
    else // Si la encontré, actualizo la fórmulaC y los datos de la altura
    {
        planta->formulaC += (dato.altura - planta->planta.altura); // No divido porque esto lo hago a diario, osea, por un día. Cualquier cosa dividida por 1 dará el mismo valor. Lo voy a dividir a lo Nazi cuándo termine todas las insersiones
        planta->planta.altura = dato.altura; // Pongo la nueva altura de la planta
        planta->planta.cantidadF += dato.cantidadF; // Sumo la cantidad del fertilizante (esto terminará siendo anual)
    }
}

void calcularMejoresFertilizantes(ST_NODO **cabecera, ST_FERTILIZANTE mejorFertilizante[], const char *archivoFertilizantes)
{
    ST_NODO *aux = *cabecera;
    FILE *plantas = open(PLANTAS, "rb");
    TIPO tipoDePlanta = obtenerTipoDePlanta(*cabecera, aux->planta.idP); // Devolverá A, T u O (es decir, 0, 1 o 2)
    BIN_FERTILIZANTE fertilizante;
    while( aux )
    {
        fertilizante = obtenerFertilizante(aux->planta.idF, archivoFertilizantes);;
        if( aux->formulaC/fertilizante.precioMl > mejorFertilizante[tipoDePlanta].formulaC/fertilizante.precioMl ) // Si la planta->formulaC/precio x mililitro es mayor que el récord que hay en ese tipo de planta... guardo ese mejor fertilizante
        {
            mejorFertilizante[tipoDePlanta].id = aux->planta.idF;
            mejorFertilizante[tipoDePlanta].formulaC = aux->formulaC;
        }
        aux = aux->ste; // i++
    }
}

float calcularFormulaC(ST_NODO **cabecera)
{
    ST_NODO *aux = *cabecera;
    int primerAltura = 0, ultimaAltura = 0;
    while( aux ) // Paso por cada planta y actualizo la fórmula C. Esto cumple con la fórmula (H2 - H1) / T, dónde T = 365 días :D
    {
        aux->formulaC = aux->formulaC/365;
        aux = aux->ste;
    }
}