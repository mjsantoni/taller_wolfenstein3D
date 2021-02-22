# CLIENTE

El Cliente es el módulo encargado de la comunicación más cercana con el usuario, tanto recibiendo el input del mismo a lo largo de todo el juego y traduciéndolo para que el Servidor genere las acciones de juego correspondientes, como siendo el encargado de renderizar constantemente la pantalla del juego para que el usuario pueda ver lo que está pasando. De esta manera, se puede dividir al Cliente en tres secciones diferenciadas:

- Las clases encargadas de procesar los eventos generados por el usuario y los cambios recibidos desde el Servidor como consecuencia de estos eventos.
- Las clases encargadas de renderizar la pantalla del jugador, basándose en la técnica de Ray Casting (resumida más adelante).
- Las clases encargadas propiamente de comunicarse con el Servidor, enviando eventos y recibiendo cambios constantemente.

A continuación, se da una vista a alto nivel de los tres grupos de clases, a través de un Diagrama de Clases.

INSERTAR DIAGRAMA DE CLASES DE CADA GRUPO


##RENDERIZACIÓN EN PANTALLA


Wolfenstein 1992 es un juego que utiliza una técnica conocida como Ray Casting para traducir un mapa en dos dimensiones (ancho y largo) en una pantalla que simula ser 3D, ya que permite al usuario sentir una sensación de profundidad a lo largo de la partida. Esta técnica, utilizada por primera vez en 1985 en el juego Alternate Reality: The City, consiste en, tomando al jugador como un punto en un mapa de dos dimensiones, lanzar a partir de su posición, y dependiendo del ángulo en el que mire, una serie de rayos (el número de rayos varía según la implementación) los cuales le permiten al jugador conocer la distancia exacta de las paredes o puertas (elementos del entorno) que tenga más cerca. Conociendo el ángulo y la distancia a la que se encuentra una pared, se puede dibujar la misma en la pantalla de manera de simular una visión 3D del jugador.

###Proceso de renderización del entorno del jugador

El siguiente diagrama de secuencia muestra a muy alto nivel el proceso de renderización de las paredes o puertas que conforman el entorno del jugador, para una posición y ángulo determinados.

![diag_clases_1](capturas/diagramaDeClases_rayCasting.png)

Sobre las clases que participan en esta secuencia:

- RayCaster: es la clase principal en la renderización del entorno del jugador. A partir de una posición **x**, una posición **y**, y un determinado ángulo, se encarga de mostrar las paredes y/o puertas más cercanas al jugador. No se encarga de la renderización de objetos presentes en el mapa, aunque guarda en un diccionario <ángulo, distancia> la distancia más cercana obtenida para cada ángulo, la cual será importante para la clase encargada de renderizar objetos.

- RayCastingDrawingAssistant: se encarga de renderizar propiamente las texturas en la pantalla. El RayCaster encuentra, para cada ángulo, la información necesaria (distancia, tipo de objeto encontrado, posición relativa en la que el rayo chocó con ese objeto) y se la transfiere al Assistant a través de la clase ObjectInfo. Esta clase puede, a partir de esos datos, obtener la posición y dimensiones de pantalla en la que deberá dibujar tanto la pared como el suelo y el techo. Para conseguir la textura correspondiente, el Assistant recurre al TextureManager, quien, a partir del tipo de objeto, puede devolverle la SdlTexture (wrapper para SDL_Texture, propia de la librería SDL), quien puede dibujarse a sí misma en pantalla.

- ObjectInfo: contiene toda la información necesaria sobre un objeto, desde el tipo de objeto y la ruta de su imagen, hasta sus dimensiones en el mapa. También puede guardar información contextual, como la distancia y posición relativa en la que un rayo la encontró (que varían según la posición y ángulo del jugador).

- ClientMap: es una clase relativamente central del Cliente, y que es muy utilizada tanto por el RayCaster como por el ObjectDrawer. El RayCaster le consulta continuamente, para cada rayo, si en una determinada posición existe o no una pared o puerta. También necesita consultarle si un rayo está o no dentro del rango del mapa, ya que utiliza esta respuesta como condición de corte al lanzamiento de cada rayo.

###Proceso de renderización de objetos en el mapa

El siguiente diagrama de secuencia muestra a muy alto nivel el proceso de renderización de los objetos presentes en el mapa, para una posición y ángulo determinados.

![diag_clases_1](capturas/diagramaDeClases_objectDrawing.png)

Sobre las clases que participan en esta secuencia:

- ObjectDrawer: es la clase principal en la renderización de objetos. Le solicita al ClientMap todos sus objetos (entre los cuales se incluyen objetos propiamente dichos, enemigos y efectos (un misil, una explosión o un efecto de sangre). A partir de una posición **x**, una posición **y**, y un determinado ángulo, verifica qué objetos deben mostrarse (sólo aquellos que entren en el ángulo de visión del jugador y que no estén bloqueados por una pared). Para estos objetos, calcula la distancia y el ángulo relativo al jugador en el que se encuentran, y delega al ObjectDrawingAssistant la responsabilidad de dibujarlos en la pantalla.

- ObjectDrawingAssistant: de forma análoga al RayCastingDrawingAssistant, se encarga de renderizar los objetos en la pantalla, también a partir de información contenida en un objeto ObjectInfo. Calcula en qué parte de la pantalla debe dibujar el objeto, pide la SdlTexture a TextureManager, y simplemente lo renderiza.

- ClientMap: en este caso, su rol es mucho más limitado, ya que solamente es utilizado por el ObjectDrawer para obtener la lista de objetos presentes.

###Renderización del arma del jugador

Es un proceso mucho más simple que los anteriores, ya que es simplemente dibujar la textura del arma del jugador en la pantalla. La GameScreen le indica al WeaponDrawer tanto cuál es el arma que tiene el jugador como la animación actual que debe mostrar (la animación varía dependiendo de si el jugador está o no disparando el arma). El WeaponDrawer utiliza al TextureManager para obtener la imagen adecuada y simplemente la renderiza en la pantalla, con un tamaño prefijado.

###UI del jugador

Al igual que la renderización del arma del jugador, es un proceso simple y principalmente harcodeado, ya que se divide a la pantalla en 7 secciones, y en cada una de ellas se muestra un valor correspondiente al jugador. Recibe de la GameScreen la proporción de la vida actual del jugador con respecto a la inicial, para saber qué animación debe mostrar para la cara del jugador (que varía según su vida).

##GENERACIÓN DE EVENTOS Y MANEJO DE CAMBIOS

###Generación de eventos

Las acciones del usuario (input de teclado y de mouse) generan eventos en el cliente. En primera instancia, estos eventos son propios de SDL (SDL_Event), los cuales son traducidos en eventos propios del código (Event). Estos eventos son serializados y enviados al Servidor a través del Socket correspondiente.

![diag_clases_1](capturas/diagramaDeClases_eventGeneration.png)


Las clases que participan en esta secuencia son:

- EventGenerator: es quien lee los SDL_Event y los traduce en eventos de la clase Event. Simplemente los encola en una BlockingQueue, y vuelve a esperar un nuevo evento.

- BlockingQueue: es una cola bloqueante, en la cual en este caso se encolan Events.




