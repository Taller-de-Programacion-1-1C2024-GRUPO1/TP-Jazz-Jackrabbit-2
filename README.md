# Jazz Jackrabbit 2 - Taller de Programación (75.42) - Facultad de Ingeniería de la Universidad de Buenos Aires

This project is the final group assignment for the subject 'Taller de Programación' (course code 75.42) at the Faculty of Engineering, University of Buenos Aires. The aim of the project is to implement a functional and comprehensive version of the classic game Jazz Jackrabbit 2 using modern programming techniques and tools learned during the course such as Sockets and Threads. The project focuses on collaborative development, problem-solving, and practical application of software engineering principles.

## Authors
| Nombre | Apellido | Padrón |
| ------ | -------- | ------ |
| Ian  | von der Heyde | 107638 |
| Ignacio | Sugai | 109549 |
| Juan Martín | de la Cruz | 109588 |
| Juan Patricio | Amboage | 106892 |

-----------------
### Installation and Usage

> ⚠️ **WARNING THIS PROJECT IS STILL IN BETA** ⚠️

1. **Clone the repository**:
   ```
   git clone git@github.com:Taller-de-Programacion-1-1C2024-GRUPO1/TP-Jazz-Jackrabbit-2.git
   ```
2. **Navigate to the project directory**:
   ```
   cd TP-Jazz-Jackrabbit-2
   ```
3. **Install all the dependencies**:
   ```
   chmod +x install_all.sh
   sudo ./install_all.sh
   ```
4. **Build the game**:
   ```
   chmod +x run_all.sh
   sudo ./run_all.sh
   ```
4. **Run the game**:
   > **NOTE**: You need to open two terminals - one dedicated to running the server and another for the client.

   *Start the Server*:
   ```
   jazz_server <port>
   ```
   Replace `<port>` with the port number you want to use for the server, e.g., `jazz_server 8080`.

   *Start a Client*:
   ```
   jazz_client <host> <port>
   ```
   Replace `<host>` with the hostname or IP address of the server you want to connect to, and `<port>` with the port number used by the server, e.g., `jazz_client localhost 8080`.

-----------------
### Testing
After building the game, to run the tests *you will need to be in the build folder and execute:*
```
GTEST_COLOR=1 ctest --tests-dir build --output-on-failure -j 12
```
-----------------
### Acknowledgements
We would like to thank our course instructor **Martín Di Paola** and the Faculty of Engineering for their support and guidance throughout the project. 

For more detailed information on the project's implementation, refer to the project documentation and source code in the repository.

-----------------
### License
MIT License - Copyright (c) 2024 Taller-de-Programacion-1C2024-GRUPO1
