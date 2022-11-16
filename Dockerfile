FROM httpd:alpine as base

RUN apk update
RUN apk add build-base curl libc-dev cmake make

FROM base as build

COPY ./httpd.conf /usr/local/apache2/conf/httpd.conf
COPY src/ src/
COPY CMakeLists.txt CMakeLists.txt

RUN cmake -DCMAKE_C_COMPILER=/usr/bin/gcc CMakeLists.txt --no-warn-unused-cli -DCMAKE_EXPORT_COMPILE_COMMANDS:BOOL=TRUE -DCMAKE_BUILD_TYPE:STRING=Release -S . -B ./build &&\
    cmake --build ./build --config Release 

RUN cp ./build/src/pages/default /usr/local/apache2/cgi-bin/default
RUN cp ./build/src/pages/edit /usr/local/apache2/cgi-bin/edit
RUN cp ./build/src/pages/delete /usr/local/apache2/cgi-bin/delete

CMD [ "httpd-foreground" ]
