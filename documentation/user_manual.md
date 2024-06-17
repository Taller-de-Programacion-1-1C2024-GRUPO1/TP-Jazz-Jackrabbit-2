<p align="center">
  <img src=utils_png/game_logo.png>
</p>

<center> <h1>JAZZ JACKRABBIT 2</h1> </center>
<center> <h1><i>User Manual</i></h1> </center>


## Introduction

Welcome to the User Manual for Jazz Jackrabbit 2, your ultimate guide to mastering this exciting and action-packed multiplayer game. Whether you are a new player stepping into the vibrant world of Jazz Jackrabbit for the first time or a seasoned veteran looking to refine your skills, this manual is designed to provide comprehensive instructions and insights to enhance your gaming experience.

We will guide you through the initial setup, including installation and configuration, and explain how to create and join games. You'll learn about the diverse range of characters, their unique abilities, and how to use them effectively in both single-player and multiplayer modes.

Prepare to dive into the adventurous world of Jazz Jackrabbit 2, where every match is a new opportunity for excitement and fun. Let's get started!

## Installing and Launching the Game

1. **Clone this repository**:
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

   ***Start the Server***:
   ```
   jazz_server <port>
   ```
   Replace `<port>` with the port number you want to use for the server, e.g., `jazz_server 8080`.
   
   > **NOTE**: For each new player, you will need to start a new client.

   ***Start a Client***:
   ```
   jazz_client <host> <port>
   ```
   Replace `<host>` with the hostname or IP address of the server you want to connect to, and `<port>` with the port number used by the server, e.g., `jazz_client localhost 8080`.

## Description

## How to create a match

## How to join a match

## How to create a map

## How to configure the game

## Important information

## HUD

## Controls

## Cheats

## Enemies

## Weapons

## Items 

## How to win a match

## How to close a match
