# Jazz Jackrabbit 2 - Taller de Programación (75.42) - Facultad de Ingeniería de la Universidad de Buenos Aires

This project is the final group assignment for the subject 'Taller de Programación' (course code 75.42) at the Faculty of Engineering, University of Buenos Aires. The aim of the project is to implement a functional and comprehensive version of the classic game Jazz Jackrabbit 2 using modern programming techniques and tools learned during the course such as Sockets and Threads. The project focuses on collaborative development, problem-solving, and practical application of software engineering principles.

## Authors
| Nombre | Apellido | Mail | Padrón |
| ------ | -------- | ------ | ------ |
| Ian  | von der Heyde | ivon@fi.uba.ar | 107638 |
| Ignacio Agustín | Sugai | isugai@fi.uba.ar | 109549 |
| Juan Martín | de la Cruz | jdelacruz@fi.uba.ar | 109588 |
| Juan Patricio | Amboage | jamboage@fi.uba.ar | 106892 |

-----------------
### Installation and Usage

> ⚠️ **WARNING THIS PROJECT CAN ONLY BE USED ON UBUNTU 22.04 LTS** ⚠️

1. **Clone the repository**:
   ```
   git clone https://github.com/Taller-de-Programacion-1-1C2024-GRUPO1/TP-Jazz-Jackrabbit-2.git
   ```
2. **Navigate to the project directory**:
   ```
   cd TP-Jazz-Jackrabbit-2
   ```
3. **Install all the dependencies**:
   ```
   chmod +x install_all.sh
   sh install_all.sh
   ```
4. **Build the game**:
   ```
   chmod +x run_all.sh
   sh run_all.sh
   ```
4. **Run the game**:
   > **NOTE**: You need to open two terminals - one dedicated to running the server and another for the client.

   *Start the Server*:
   ```
   jazz_server <port>
   ```
   Replace `<port>` with the port number you want to use for the server, e.g., `jazz_server 8080`.

   *Start a Client*:
   > **NOTE**: For each new player, you will need to open a new terminal and start a new client.
   ```
   jazz_client <host> <port>
   ```
   Replace `<host>` with the hostname or IP address of the server you want to connect to, and `<port>` with the port number used by the server, e.g., `jazz_client localhost 8080`.

-----------------
### Create or edit a map

> ⚠️ **WARNING READ THE INDICATIONS PROVIDED IN [USER MANUAL](documentation/user_manual.md) ** ⚠️

After building the game, if you want to create a new map and play with it, you will have to start the client from the `build` folder. 
```
cd build
./jazz_client <host> <port>
```
Replace `<host>` with the hostname or IP address of the server you want to connect to, and `<port>` with the port number used by the server, e.g., `jazz_client localhost 8080`.

After saving your awesome new map, you will need to build the game again: 
```
sh run_all.sh
```

-----------------
### Testing
After building the game, to run the tests you will have to execute:
```
sh run_tests.sh
```
-----------------
### Acknowledgements
We would like to thank our course instructor **Martín Di Paola** and the Faculty of Engineering for their support and guidance throughout the project. 

For more detailed information on the project's implementation, refer to the project documentation and source code in the repository.

-----------------
### License
MIT License - Copyright (c) 2024 Taller-de-Programacion-1C2024-GRUPO1
