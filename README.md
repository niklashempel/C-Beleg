# Beleg4

## Quickstart

You can either build the program with CMake and copy the files to your webserver or use a Docker container. 

### Download project

```sh
git clone https://github.com/niklashempel/C-Beleg
```

```sh
cd C-Beleg
```

### Build with CMake

```sh
cmake -DCMAKE_C_COMPILER=/usr/bin/gcc CMakeLists.txt --no-warn-unused-cli -DCMAKE_EXPORT_COMPILE_COMMANDS:BOOL=TRUE -DCMAKE_BUILD_TYPE:STRING=Release -DLDL_FLAG='-ldl' -S . -B ./build
```

```sh
cmake --build ./build --config Release
```

The compiled files can then be found under build/src/pages.

### Docker

```sh
docker build . -t beleg
```

```sh
docker run -d -p 9000:80 beleg
```

To mount an external database:

```sh
docker run -d -p 9000:80 --mount type=bind,source=path/to/database/data.db,target=/usr/local/apache2/cgi-bin/data.db beleg
```

Open http://localhost:9000/default.cgi

### SQLite

[SQLite](https://www.sqlite.org/download.html) is used as a third-party database library and compiled together with the other modules.
