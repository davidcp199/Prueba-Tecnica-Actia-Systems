DESCRIPCION

    Este proyecto en C++ implementa tres módulos que se comunican entre sí a través de una interfaz común IModule. Cada módulo trabaja en su propio hilo, simulando un pequeño sistema de procesamiento de datos en cadena.

    -> El primer módulo genera de forma continua arreglos de bytes aleatorios, con longitudes entre 1 y 100 y valores entre 0 y 255.

    -> El segundo módulo recibe los arrays, busca una secuencia de bytes y solo envía al siguiente módulo los que la contienen.

    -> El tercer módulo almacena los arreglos recibidos junto con su timestamp (UTC) y los muestra en orden cronológico, con 100 de máximo.

    El programa principal simplemente crea los tres módulos, los conecta y los ejecuta durante 100 segundos.


DOCKER

    Se ha preparado un contenedor Docker para que el proyecto se compile y ejecute en cualquier sistema Linux.

    Imagen: Ubuntu 22.04 LTS
    Compilador: g++ 11.4
    cmake 3.22+


COMPILACION Y EJECUCION

    Local
        # Compilar proyecto
        make

        # Ejecutar programa principal
        make run

        # Ejecutar tests
        make tests

        # Limpiar compilación
        make clean

    Con Docker

        # Construir imagen Docker
        make docker_build

        # Ejecutar proyecto principal
        make docker_run

        # Ejecutar tests
        make docker_run_tests

        # Abrir shell interactiva dentro del contenedor
        make docker_shell

FUNCIONAMIENTO Y POSIBLES MEJORAS

    El modulo 1 tiene un hilo interno que corre continuamente, la generación no requiere mutex al no haber acceso compartido a datos.

    Existe un riesgo al enviar los datos al siguiente modulo sin control no teniendo ningún buffer en este módulo, si el siguiente módulo no pudiera tratarlos a tiempo se podrían perder estos datos, una posible mejora futura sería una integración de este buffer en el módulo 1.

    El módulo 2 usa mutex para proteger la cola y evita race conditions, con limitación de 100 arrays para evitar el descontrol en memoria.

    Lo mismo hacemos con el módulo 3, con el uso de mutex protegemos el acceso al buffer evitando condiciones de carrera si se reciben datos simultaneamente del módulo 2. De igual forma, tiene un tamaño máximo de 100 registros para controlar la memoria eliminando los más antiguos si se llena.

    La secuencia de bytes que busca el Modulo 2 actualmente esta harcodeada lo que hace que sea poco exportable. Ademas, los máximos de los buffer también están fijos.
    
    En el módulo 3, se imprimen todos los registros cada vez que recibimos un nuevo array, que con lo anterior de un buffer limitado si la entrega es grande y rapida puede suponer pérdidas.

    Se podrían realizar mejoras futuras parametrizando estas variables e imprimiendo simplemente en el modulo 3 solo los últimos N registros, o incluso solo el útlimo añadiendolo un archivo.
