# Overkill

Project Overkill is a home made Game Engine.
The goal of this project for me is to learn as much as possible about game engines.
That is why I wish to make this engine as powerful as possible while relying as little as possible on libraries & the STL.

Planned features for v1
-----------------------
* Full Entity-Component-System model
* Basic 2D & 3D with DirectX (DirectX code is heavily inspired by http://www.rastertek.com/tutdx11.html)
* Rudimentary sound engine
* Data storage in JSon file
* Mono-threaded
* Windows only
* Handling keyboard/mouse only

Current Objectives
------------------
* [FEATURE] Implement ambient lighting
* [FEATURE] Implement specular lighting
* [FEATURE] Handle mouse input
* [REFACTOR] Make generic asset library
* [REFACTOR] Cache component tuple list in systems

Current Bugs/Issues
-------------------
* The JSon parser fails when encountering empty arrays or objects.
* String/StringView classes are still a pain to use. It'd be nice to handle more operators.

Beyond v1
---------
* Game Editor to generate the game data
* Better memory management
* Multi-platform
* Gamepad support
* Multiple threads
* Expanding graphic & sound capabilities
* Implement Physics Engine
* More data storage options (ex: binary files)
* Custom scriting language for Gameplay code
* Network API ?
