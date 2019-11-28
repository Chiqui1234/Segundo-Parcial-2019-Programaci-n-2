#include "funciones.h"
int main()
{
    ST_FERTILIZANTE mejorFertilizante[CANT_TIPO_PLANTAS]; // Acá guardo el ID del Fertilizante y su récord. Los tipos de planta son "A", "T" y "O", es decir celda 0, 1 y 2.
    ST_NODO *cabecera = NULL;
    cargarCrecimiento(&cabecera, PLANTAS); // Cargo las plantas en RAM (Lista)
    calcularFormulaC(&cabecera); // La fórmula C ya la tenía semi-calculada pero faltaba dividirla por los días del año
    calcularMejoresFertilizantes(&cabecera, mejorFertilizante, FERTILIZANTES);
}