# Beleg4
## CMake
### cmake configure
```
cmake -DCMAKE_C_COMPILER=/usr/bin/gcc CMakeLists.txt --no-warn-unused-cli -DCMAKE_EXPORT_COMPILE_COMMANDS:BOOL=TRUE -DCMAKE_BUILD_TYPE:STRING=Release -S . -B ./build
```

### cmake build
```
cmake --build ./build --config Release
```

## Docker
```
docker build . -t beleg
```
```
docker run -d -p 9000:80 beleg
```

### SQLite
SQLite is obtained from their [download page](https://www.sqlite.org/download.html) and compiled together with the rest.