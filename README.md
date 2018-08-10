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
* Fix JSON handling of strings
* Make generic asset library
* Implement basic lighting in shader
* Handle mouse input
* Cache component tuple list in systems
* Fix/optimize JSon parser

Current Bugs/Issues
-------------------
* The JSon parser doesn't work 100%. It needs to be fixed...
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
