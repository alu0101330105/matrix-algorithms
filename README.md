# Algoritmos de Multiplicacion de Matrices
Este código se ha usado para testear que algoritmo de multiplicacion de matrices es más rápido.

Para ejecutarlo simplemente utiliza
```bash
$ make
$ ./Matrix
```
Se creará un archivo llamado `output.txt` en la dirección de ejecución que contendrá todos los tiempos de ejecución de cada una de las iteraciones.

Para editar el archivo de salida, los tamaños de las matrices o el número de iteraciones, solo hay que editar las variables:
```c++
int main() {
  std::fstream fs;
  fs.open("output.txt", std::fstream::out);  // << Archivo de salida
  int rows = 10;  // << Número de filas de la primera matriz
  int cols = 10;  // << Número de columnas de la primera matriz
  int iterations = 50;  // << Número de iteraciones
```


