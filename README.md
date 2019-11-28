# Segundo Parcial 2019 Programación 2
Funciones comentadas para llevar a cabo el ejercicio del parcial. 
No compila (al menos por ahora) porque me limité a crear las funciones y estructuras, pero no creé un lote de prueba (al menos por ahora) y todavía faltan algunas pavadas, cómo imprimir el mejor fertilizante por tipo (aunque la lógica de eso ya está, literalmente faltaría imprimirlo en pantalla).

# ¿Qué hace el programa?
1) Carga crecimientos.dat en una lista. Si hay registros duplicados los fusiona y actualiza la fórmula C (h2 - h1), pero aún no divide por nada
2) Termino de calcular la fórmula C. Debido a que en mi lista tengo un registro por planta (y no un registro por planta por día, como en crecimientos.dat), sé que cada planta se estudió 365 días. Por ende, a la acumulación que hice POR DIA de la fórmula (h2 - h1), lo divido por 365. Esta tarea se aplica a todas las plantas. Para sacar el crecimiento mensual, debería dividir ((h2 - h1) / 365 ) / 12. Eso me dará un promedio de crecimiento mensual.
3) Teniendo la fórmulaC ya calculada por todas las plantas, calculo el mejor fertilizante. El mejor fertilizante es el valor más grande que se de a partir del cálculo (formulaC / precio por mililitro).
