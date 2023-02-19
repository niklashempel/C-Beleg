FROM httpd:alpine as base

RUN apk update
RUN apk add build-base curl libc-dev cmake make

FROM base as build

COPY ./httpd.conf /usr/local/apache2/conf/httpd.conf
COPY src/ src/
COPY CMakeLists.txt CMakeLists.txt

RUN cmake -DCMAKE_C_COMPILER=/usr/bin/gcc CMakeLists.txt -DCMAKE_BUILD_TYPE:STRING=Release -S . -B ./build &&\
    cmake --build ./build --config Release 

WORKDIR /usr/local/apache2/build/src/pages

RUN cp default.cgi /usr/local/apache2/cgi-bin/default.cgi
RUN cp edit.cgi /usr/local/apache2/cgi-bin/edit.cgi
RUN cp delete.cgi /usr/local/apache2/cgi-bin/delete.cgi
RUN cp new.cgi /usr/local/apache2/cgi-bin/new.cgi

RUN chmod 1777 /usr/local/apache2/cgi-bin

CMD [ "httpd-foreground" ]
