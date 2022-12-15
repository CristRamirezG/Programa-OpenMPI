# Programa-OpenMPI
Programa creado con openMPI
Enunciado:
La ANFP solicita a la Universidad Tecnológica Metropolitana, la elaboración del fixture (Un fixture
es una tabla de emparejamientos de equipos o jugadores en un torneo por sistema de "todos
contra todos") para el torneo 2022. Pero dada la actual situación de crisis económica, sanitaria y
social que enfrenta el país, el principal énfasis es minimizar los desplazamientos que tienen que
realizar los equipos.
La modalidad de juego, establece que cada equipo se enfrente dos veces con cada uno de los
equipos contrincantes, uno en calidad de “visita” (realiza un desplazamiento) y otro en calidad de
“local” (no debe desplazarse).
Otra restricción importante, es que el torneo debe tener dos rondas, en una primera etapa cada
equipo juega contra todos los demás y esto se repite en la segunda ronda, pero invirtiendo el
desplazamiento, es decir que si la primera ronda fue local, en la segunda debe ser visitante.
Asuma que el equipo se queda en el Estadio en el que juega, para la siguiente iteración.

```
AudaxItaliano -33.540833 -70.578333
Cobresal -26.251944 -69.628611
Colo-Colo -33.506611 -70.605944
CoquimboUnido -29.965278 -71.338333
CuricóUnido -34.974356 -71.230707
DeportesAntofagasta -23.670139 -70.404583
DeportesLa Serena -29.911111 -71.251944
Everton -33.014444 -71.535000
Huachipato -36.755556 -73.107222
Ñublense -36.618056 -72.107500
O'Higgins -34.177778 -70.737500
Palestino -33.520833 -70.672778
SantiagoWanderers -33.022278 -71.640000
UniónEspañola -33.404553 -70.659017
UniónLa Calera -32.784167 -71.199444
UniversidadCatólica -33.395944 -70.500656
UniversidaddeChile -33.464522 -70.610586
UniversidaddeConcepción -36.815278 -73.023333

```

El trabajo consiste en desarrollar un programa en C/C++ que usando OpenMP y/o Open MPI, que
leyendo un archivo de entrada (equipos.txt) por línea de comandos, entregue el fixture
minimizando los desplazamientos promedios totales
