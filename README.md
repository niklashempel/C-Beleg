# C Beleg

## Quickstart

The project can either be built with CMake and then copied to the webserver or by using a Docker container. 

### Download project

```sh
git clone https://github.com/niklashempel/C-Beleg
```

```sh
cd C-Beleg
```

### Build with CMake

```sh
cmake -DCMAKE_C_COMPILER=/usr/bin/gcc CMakeLists.txt -DCMAKE_BUILD_TYPE:STRING=Release -S . -B ./build
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
