1. Agregar tarea (nombre, prioridad): La usuaria ingresa el nombre de una tarea y su prioridad (un número entero). La aplicación agrega la tarea a la lista de tareas por hacer.

2. Establecer precedencia entre tareas (tarea1, tarea2): La usuaria ingresa los nombres de dos tareas existentes. La aplicación establece que la tarea1 debe realizarse antes que la tarea2.

3. Mostrar tareas por hacer: La aplicación muestra todas las tareas pendientes, ordenadas según su prioridad y teniendo en cuenta las relaciones de precedencia.

Suponiendo que el archivo de ejemplo se cargó en la aplicación, la salida de esta opción se debería ver así:
Tareas por hacer, ordenadas por prioridad y precedencia:
1. TareaD (Prioridad: 1)
2. TareaA (Prioridad: 3)
3. TareaB (Prioridad: 2) - Precedente: TareaA
4. TareaC (Prioridad: 4) - Precedente: TareaB
5. TareaE (Prioridad: 5) - Precedente: TareaD

En este ejemplo de salida, las tareas se enumeran en el orden en que deben realizarse, teniendo en cuenta tanto su prioridad como las relaciones de precedencia. La tarea con la prioridad más alta (menor número) se muestra primero, seguida de las tareas que dependen de ella en función de las relaciones de precedencia establecidas. Cada tarea se muestra con su nombre, prioridad y, si corresponde, las tareas precedentes.

4. Marcar tarea como completada (nombre): La usuaria ingresa el nombre de una tarea. La aplicación marca la tarea como completada y la elimina de la lista de tareas por hacer. Si la tarea tiene relaciones de precedencia, se debe colocar una advertencia: “¿estás seguro que desea eliminar la tarea?”

5. Deshacer última acción: La aplicación deshace la última acción realizada por la usuaria, ya sea agregar/eliminar una tarea, establecer precedencia o marcar una tarea como completada. Si no hay acciones que deshacer, se debe mostrar un aviso.

6. Cargar datos de tareas desde un archivo de texto (nombre_archivo): La aplicación carga los datos de las tareas pendientes desde un archivo de texto indicado por la usuaria.

