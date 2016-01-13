# RAIG3D
Raig3D is Cocos2dx C++ demonstration project for the server side application `R.A.I.G` https://github.com/damorton/raig.git

## Instructions

1. Install Cocos2dx http://www.cocos2d-x.org/wiki/Installations

2. Make sure you have the RAIG server application running first. https://github.com/damorton/raig.git. or You can connect to `damortonpi.duckdns.org` for testing but this may not always be available.

3. To connect to the server application change the target address in `HelloWorldScene.cpp` to:
```
m_RaigAI->InitConnection("127.0.0.1", "27000");
```
or to connect to my super Raspberry Pi:
```
m_RaigAI->InitConnection("damortonpi.duckdns.org", "27000");
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
