# RAIG3D
Raig3D is a Cocos2dx C++ demonstration project for the server side application `R.A.I.G` https://github.com/damorton/raig.git. The game will execute its game loop and on each iteration will generate a random start and goal position in the game world. This request is sent to the RAIG server application which will process the path. Once the path is complete RAIG will send the path back to the game client. The path is stored as a `vector` of `Vector3` data structures with an `X`, `Y`, and `Z` value. The Cocos2dx framework provides a way to visualize the process using `TMXTiledMap`.

## Instructions

1. Install Cocos2dx http://www.cocos2d-x.org/wiki/Installations

2. Make sure you have the RAIG server application running first. https://github.com/damorton/raig.git. or You can connect to `damortonpi.duckdns.org` for testing but this may not always be available.

3. To connect to the server application change the target address in `HelloWorldScene.cpp` to:
```
m_RaigAI->InitConnection("127.0.0.1", "27000");
```

### Ubuntu 

- Download the repo
- Extract contents of the .zip file
- `cd RAIG3D-master/`
- Build
```
$ cocos run -s ./ -p linux
```
- Run `$ ./linux-build/bin/RAIG3D`

### Windows 

- Coming soon..

## Dependencies

- libraig - https://github.com/damorton/libraig.git

Dependencies are located in the `external` directory.
