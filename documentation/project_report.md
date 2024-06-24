# Project Report

This report provides a detailed timeline of the project, from the initial task division to problem-solving and the final outcome. It clarifies which tasks were completed by each team member and it also details the software tools and libraries used, along with documentation sources.

## Tools & Libraries

- IDE: Visual Studio Code
- Version Control: Git
- Ensure code quality and consistency: [pre-commit](https://pre-commit.com/index.html)
- Memory Checking: Valgrind
- SDL2pp: [libSDL2pp](https://sdl2pp.amdmi3.ru/) and [Lazy Foo](https://lazyfoo.net/tutorials/SDL/)
- QT: [Official documentation](https://doc.qt.io/)
- Testing: [Official documentation of Google Tests](https://github.com/google/googletest/tree/5b7fd63d6d69f1754d5f3be956949484ebac06d5)

## Task Division

For this project, each team member chose to undertake different tasks, involving a progressive allocation of responsibilities and expertise.

### Ignacio Agustin Sugai

- **GAME & PHYSICS**: Played a pivotal role in creating the game's physics engine from scratch. He meticulously crafted the game loop, ensuring smooth and consistent gameplay dynamics. Additionally, he developed all types of entities present within the game, meticulously implementing their behaviors, interactions, and physics properties.

### Juan Martin de la Cruz

- **COMPILATION**: Created CMake files to streamline the game's compilation process, ensuring smooth and efficient builds.

- **CONFIGURATION**: Utilized an external library to parse YAML files and generate proper map readings and configurations, ensuring smooth integration of game resources into the build process.

- **PROTOCOL**: Spearheaded the implementation of robust command and snapshot transmission protocols, ensuring reliable communication between clients and servers.

- **SERVER**: Led the development of server-side logic, crafting efficient algorithms and data structures to handle game state management and player interactions seamlessly, while also proactively addressing potential deadlocks or race conditions when working with multiple threads that share a significant amount of data simultaneously.

- **TESTING**: Establishes a comprehensive testing framework, creating unit tests for the protocol using googletests libraries to verify its functionality and robustness.

- **DOCUMENTATION**: Took charge of documenting the project and creating the user manual to provide comprehensive guidance for users. He ensured that all aspects of the project, including setup instructions, gameplay mechanics and  tips, were thoroughly documented to facilitate smooth user experience and development processes. Additionally, he created UML diagrams, code documentation, and other supplementary materials to provide further clarity and insight into the project's architecture and implementation details.

### Juan Patricio Amboage

- **USER INTERFACE**: Took the lead in developing the game's user interface, leveraging the SDL library to create visually engaging and intuitive interfaces for players. His attention to detail and user-centric approach ensured that the interface elements were not only aesthetically pleasing but also functional and easy to navigate.

- **MAP CREATOR**: Pioneered the development of the map creation feature, utilizing SDL to empower users to design and customize maps within the game. He implemented intuitive tools and interfaces that allowed users to manipulate terrain, place objects, and customize environments according to their preferences. 

### Ian von der Heyde

- **COMPILATION**: Created CMake files for project compilation.

- **QT**: Utilized an external library (QT) to create the game's lobby, providing an intuitive and visually appealing interface for players to navigate and interact with.

- **CLIENT**: Designed and implemented the logic for clients, orchestrating their connection to the server and enabling them to receive server responses and game snapshots while sending commands seamlessly. He ensured a smooth and responsive gameplay experience by managing the flow of data between clients and the server, facilitating real-time interactions within the game environment.

- **DOCUMENTATION**: he created UML diagrams to assist with project documentation.


In addition to the specific responsibilities assigned to each team member, we all applied optimal object-oriented programming logic to ensure a modular and scalable software design. We efficiently employed concepts such as inheritance, encapsulation, polymorphism, and abstraction to create clean and maintainable code.

Throughout the project development, we extensively used core technologies such as sockets for client-server communication, queues for real-time data management, smart pointers for safe memory management, and threads for implementing concurrent operations and maximizing system performance.

These architectural and technical decisions were crucial in ensuring the stability, efficiency, and scalability of the game, reflecting our commitment to best software development practices.

## Project Planning

None of us had prior experience in developing a project of this scale. We divided the workload into four main components:

- **Server Logic and Protocol:** One team member focused on developing the server-side logic and handling communication protocols.
- **Game Physics and Logic:** Another team member worked on the physics and core game logic to ensure smooth gameplay.
- **QT and Client Logic:** A third team member was responsible for the client-side logic and user interface using QT, and also contributed to the communication logic.
- **SDL and Map Editor Development:** The final team member handled the development of SDL-related features and the map editor.

During the first week, we concentrated on getting familiar with the specific libraries we would be using, such as QT and SDL. We also learned how to create and use shell scripts (.sh files) for quick installation and compilation of the game. This preparation was crucial for streamlining our development process and ensuring that everyone had a solid understanding of the tools and technologies involved.

This structured approach allowed us to focus on our respective areas of expertise while ensuring that we were all aligned on the project's overall goals and technical requirements.

After the initial days of preparation, each team member was able to focus on their respective part of the project and effectively develop their specific logic.

Communication and consistency were key to our success as a team. We understood the importance of daily progress, and we made it a point to advance our work every single day. This regular communication ensured that everyone was aware of each other's progress and could address any issues promptly, maintaining a steady pace towards project completion.

## Challenges

We recognized that ensuring the game’s physics operated correctly would be a significant challenge. However, without visual confirmation, it was difficult to verify the accuracy of the physics. To address this, we developed a separate SDL project specifically for testing the physics. This proof of concept (POC) allowed us to validate and refine the physics independently, accelerating our development process and mitigating potential issues that might arise during the full integration of the game components.

Upon completing the server and client logic development, we allocated two days to the integration process. Given the project's complexity and the errors we encountered, we decided to meticulously review the code line by line. This collaborative approach—leveraging the collective expertise of the team—enabled us to swiftly resolve issues. As the adage goes, "four heads are better than one," and having each team member deeply familiar with their respective components facilitated efficient troubleshooting.

Time management was initially anticipated to be a critical challenge. However, our dedication and consistent effort from the outset proved beneficial. By the third week, our focus shifted primarily to bug fixing and the addition of minor features. This proactive approach allowed us to stay on schedule and ensure a higher quality final product.

## Feedback

This project provided us with valuable insights into the dynamics of real-world projects. We navigated significant challenges, such as ensuring accurate game physics and integrating complex server-client logic. Also, The meticulous code review and collaborative troubleshooting during the integration phase underscored the value of teamwork and collective problem-solving.

Additionally, our disciplined time management and consistent effort from day one allowed us to stay on schedule, shifting our focus to bug fixing and feature enhancements by the third week. This project not only strengthened our technical skills but also reinforced the importance of preparation, communication, and perseverance in delivering a high-quality product. Regular weekly meetings with our assigned mentor were instrumental in refining various aspects of our code, particularly in terms of design and efficiency. These sessions provided targeted feedback that helped us improve our project's overall quality.
