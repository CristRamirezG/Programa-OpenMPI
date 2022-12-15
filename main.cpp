#include <iostream>
#include <algorithm>
#include <vector>
#include <numeric>
#include <math.h>
#include <fstream>
#include <sstream>
#include <mpi.h>

using namespace std;

// Clase para representar una coordenada
class Coord {
public:
  float x, y;
  string nombre;
  Coord(string nombre,float x, float y) : nombre(nombre), x(x), y(y) {}
};

// Función para calcular la distancia euclidiana entre dos coordenadas
float dist(const Coord& a, const Coord& b) {
  return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

int main(int argc, char** argv) {
  // Inicializar MPI
  MPI_Init(&argc, &argv);

  // Obtener el número total de procesos y el número del proceso actual
  int num_procs, proc_num;
  MPI_Comm_size(MPI_COMM_WORLD, &num_procs);
  MPI_Comm_rank(MPI_COMM_WORLD, &proc_num);

  // Crea un vector con las coordenadas a usar en el fixture
  vector<Coord> coords;

  // El proceso 0 se encarga de leer el archivo y distribuir las coordenadas a los demás procesos
  if (proc_num == 0) {
    ifstream archivo("equipos.txt");
    string nombre;
    string linea;
    float x, y;
    string separador;
    if (!archivo) {
      cout << "Error al abrir ejemplo.dat\n";
      exit(EXIT_FAILURE);
    } else {
      while (getline(archivo,linea)) {
        istringstream iss(linea);
        if (iss >> nombre >> x >> y) {
          coords.push_back(Coord(nombre,x,y));
        }
      }
    }
    archivo.close();
  }

  // Distribuir el vector de coordenadas entre los diferentes procesos
  

vector<Coord> proc_coords;
  for (int i = 0; i < coords.size() / num_procs; i++) {
    proc_coords.push_back(Coord("", 0, 0));
  }


  MPI_Scatter(coords.data(), proc_coords.size(), MPI_FLOAT, proc_coords.data(), proc_coords.size(), MPI_FLOAT, 0, MPI_COMM_WORLD);

  // Ordenar el vector de coordenadas de acuerdo al promedio de desplazamientos
  // totales
  sort(proc_coords.begin(), proc_coords.end(), [&](const Coord& a, const Coord& b) {
    int dist_a = 0, dist_b = 0;
    for (const auto& c : proc_coords) {
      dist_a += dist(a, c);
      dist_b += dist(b, c);
    }
    return dist_a < dist_b;
  });

  // Recopilar el vector de coordenadas ordenado por promedio de desplazamientos en el proceso 0
  vector<Coord> sorted_coords;
  for (int i = 0; i < coords.size(); i++) {
    sorted_coords.push_back(Coord("", 0, 0));
  }
  MPI_Gather(proc_coords.data(), proc_coords.size(), MPI_FLOAT, sorted_coords.data(), sorted_coords.size(), MPI_FLOAT, 0, MPI_COMM_WORLD);

  // Imprime el resultado en un archivo CVS
  if (proc_num == 0) {
    ofstream file("partidos.csv");
    if (!file.is_open()) {
      cout << "Error al abrir el archivo\n";
      return 1;
    }
    string local, visita;
    float distancia;
    int contador = 0;
    /*
     * por cada elemento del arreglo ordenado por promedio de desplazamientos
     * genera los pares ordenados para cada equipo segun su cercania
     */
    for (int cont_glob = 0; cont_glob < sorted_coords.size(); cont_glob++) {

      // Solo Para los elementos intermedios arriba
      for(int i = cont_glob; i < sorted_coords.size()-1 ; i++){
        local = sorted_coords[cont_glob].nombre;
        visita = sorted_coords[i++].nombre;
        distancia = dist(sorted_coords[cont_glob],sorted_coords[i++]);
        file << contador << ";\"" << local << "\";\"" << visita << "\";" << distancia << "\n";
        contador++;
      }

      // Solo Para los elementos intermedios abajo
      for(int j = cont_glob; j > 0 ; j--){
        local = sorted_coords[cont_glob].nombre;
        visita = sorted_coords[j--].nombre;
        distancia = dist(sorted_coords[cont_glob],sorted_coords[j--]);
        file << contador << ";\"" << local << "\";\"" << visita << "\";" << distancia << "\n";
        contador++;
      }
    }
    file.close();
  }

  // Finalizar MPI
  MPI_Finalize();
  return EXIT_SUCCESS;
}