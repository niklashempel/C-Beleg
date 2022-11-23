FROM httpd:alpine as base

RUN apk update
RUN apk add build-base curl libc-dev cmake make

FROM base as build

COPY ./httpd.conf /usr/local/apache2/conf/httpd.conf
COPY src/ src/
COPY CMakeLists.txt CMakeLists.txt

RUN cmake -DCMAKE_C_COMPILER=/usr/bin/gcc CMakeLists.txt --no-warn-unused-cli -DCMAKE_EXPORT_COMPILE_COMMANDS:BOOL=TRUE -DCMAKE_BUILD_TYPE:STRING=Release -DLDL_FLAG= -S . -B ./build &&\
    cmake --build ./build --config Release 

WORKDIR /usr/local/apache2/build/src/pages

RUN cp default /usr/local/apache2/cgi-bin/default
RUN cp edit /usr/local/apache2/cgi-bin/edit
RUN cp delete /usr/local/apache2/cgi-bin/delete
RUN cp new /usr/local/apache2/cgi-bin/new
RUN cp create /usr/local/apache2/cgi-bin/create
RUN cp update /usr/local/apache2/cgi-bin/update

RUN chmod 1777 /usr/local/apache2/cgi-bin

CMD [ "httpd-foreground" ]
