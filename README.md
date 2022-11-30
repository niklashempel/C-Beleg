# Beleg4

## CMake

### cmake configure

```
cmake -DCMAKE_C_COMPILER=/usr/bin/gcc CMakeLists.txt --no-warn-unused-cli -DCMAKE_EXPORT_COMPILE_COMMANDS:BOOL=TRUE -DCMAKE_BUILD_TYPE:STRING=Release -S . -B ./build
```

or if there are sqlite errors:

```
cmake -DCMAKE_C_COMPILER=/usr/bin/gcc CMakeLists.txt --no-warn-unused-cli -DCMAKE_EXPORT_COMPILE_COMMANDS:BOOL=TRUE -DCMAKE_BUILD_TYPE:STRING=Release -DLDL_FLAG='-ldl' -S . -B ./build
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

```
docker run --rm -d -p 9000:80 --mount type=bind,source="$(pwd)"/build/src/pages/data.db,target=/usr/local/apache2/cgi-bin/test.db beleg
```

### SQLite

SQLite is obtained from its [download page](https://www.sqlite.org/download.html) and compiled together with the rest.
