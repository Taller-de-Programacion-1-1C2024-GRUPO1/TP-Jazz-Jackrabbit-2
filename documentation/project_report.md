# Project Report

This report provides a detailed timeline of the project, from the initial task division to problem-solving and the final outcome. It clarifies which tasks were completed by each team member and it also details the software tools and libraries used, along with documentation sources.

## Task Division

For this project, each team member chose to undertake different tasks, involving a progressive allocation of responsibilities and expertise.

### Ignacio Sugai:

- **GAME & PHYSICS**: Played a pivotal role in creating the game's physics engine from scratch. He meticulously crafted the game loop, ensuring smooth and consistent gameplay dynamics. Additionally, he developed all types of entities present within the game, meticulously implementing their behaviors, interactions, and physics properties. His expertise in game physics and engine design contributed significantly to the overall immersive experience and realism of the game.

### Juan Martin de la Cruz:

- **COMPILATION**: Created CMake files to streamline the game's compilation process, ensuring smooth and efficient builds.

- **CONFIGURATION**: Utilized an external library to parse YAML files and generate proper map readings and configurations, ensuring smooth integration of game resources into the build process.

- **PROTOCOL**: Spearheaded the implementation of robust command and snapshot transmission protocols, ensuring reliable communication between clients and servers.

- **SERVER**: Led the development of server-side logic, crafting efficient algorithms and data structures to handle game state management and player interactions seamlessly, while also proactively addressing potential deadlocks or race conditions when working with multiple threads that share a significant amount of data simultaneously.

- **TESTING**: Establishes a comprehensive testing framework, creating unit tests for the protocol using googletests libraries to verify its functionality and robustness.

- **DOCUMENTATION**: Took charge of documenting the project and creating the user manual to provide comprehensive guidance for users. He ensured that all aspects of the project, including setup instructions, gameplay mechanics and  tips, were thoroughly documented to facilitate smooth user experience and development processes. Additionally, he created UML diagrams, code documentation, and other supplementary materials to provide further clarity and insight into the project's architecture and implementation details.

### Juan Patricio Amboage :

- **USER INTERFACE**: Took the lead in developing the game's user interface, leveraging the SDL library to create visually engaging and intuitive interfaces for players. His attention to detail and user-centric approach ensured that the interface elements were not only aesthetically pleasing but also functional and easy to navigate.

- **MAP CREATOR**: Pioneered the development of the map creation feature, utilizing SDL to empower users to design and customize maps within the game. He implemented intuitive tools and interfaces that allowed users to manipulate terrain, place objects, and customize environments according to their preferences. 

### Ian von der Heyde:

- **QT**: Utilized an external library (QT) to create the game's lobby, providing an intuitive and visually appealing interface for players to navigate and interact with.

- **CLIENT**: Designed and implemented the logic for clients, orchestrating their connection to the server and enabling them to receive game snapshots while sending commands seamlessly. He ensured a smooth and responsive gameplay experience by managing the flow of data between clients and the server, facilitating real-time interactions within the game environment.


In addition to the specific responsibilities assigned to each team member, we all applied optimal object-oriented programming logic to ensure a modular and scalable software design. We efficiently employed concepts such as inheritance, encapsulation, polymorphism, and abstraction to create clean and maintainable code.

Throughout the project development, we extensively used core technologies such as sockets for client-server communication, queues for real-time data management, smart pointers for safe memory management, and threads for implementing concurrent operations and maximizing system performance.

These architectural and technical decisions were crucial in ensuring the stability, efficiency, and scalability of the game, reflecting our commitment to best software development practices.

## Tools & Libraries

- IDE: Visual Studio Code
- Version Control: Git
- Ensure code quality and consistency: [pre-commit](https://pre-commit.com/index.html)
- Memory Checking: Valgrind
- SDL2pp: [libSDL2pp](https://sdl2pp.amdmi3.ru/) and [Lazy Foo](https://lazyfoo.net/tutorials/SDL/)
- QT: [Official documentation](https://doc.qt.io/)
- Testing: [Official documentation of Google Tests](https://github.com/google/googletest/tree/5b7fd63d6d69f1754d5f3be956949484ebac06d5)

