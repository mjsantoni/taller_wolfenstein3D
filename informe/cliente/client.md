# CLIENTE

El Cliente es el módulo encargado de la comunicación más cercana con el usuario, tanto recibiendo el input del mismo a lo largo de todo el juego y traduciéndolo para que el Servidor genere las acciones de juego correspondientes, como siendo el encargado de renderizar constantemente la pantalla del juego para que el usuario pueda ver lo que está pasando. De esta manera, se puede dividir al Cliente en tres secciones diferenciadas:

- Las clases encargadas de procesar los eventos generados por el usuario y los cambios recibidos desde el Servidor como consecuencia de estos eventos.
- Las clases encargadas de renderizar la pantalla del jugador, basándose en la técnica de Ray Casting (resumida más adelante).
- Las clases encargadas propiamente de comunicarse con el Servidor, enviando eventos y recibiendo cambios constantemente.

A continuación, se da una vista a alto nivel de los tres grupos de clases, a través de un Diagrama de Clases.

INSERTAR DIAGRAMA DE CLASES DE CADA GRUPO


RENDERIZACIÓN EN PANTALLA


Wolfenstein 1992 es un juego que utiliza una técnica conocida como Ray Casting para traducir un mapa en dos dimensiones (ancho y largo) en una pantalla que simula ser 3D, ya que permite al usuario sentir una sensación de profundidad a lo largo de la partida. Esta técnica, utilizada por primera vez en 1985 en el juego Alternate Reality: The City, consiste en, tomando al jugador como un punto en un mapa de dos dimensiones, lanzar a partir de su posición, y dependiendo del ángulo en el que mire, una serie de rayos (el número de rayos varía según la implementación) los cuales le permiten al jugador conocer la distancia exacta de las paredes o puertas (elementos del entorno) que tenga más cerca. Conociendo el ángulo y la distancia a la que se encuentra una pared, se puede dibujar la misma en la pantalla de manera de simular una visión 3D del jugador.

###Proceso de renderización del entorno del jugador

