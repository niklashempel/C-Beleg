FROM httpd:alpine

RUN apk update
RUN apk add curl gcc libc-dev

COPY ./httpd.conf /usr/local/apache2/conf/httpd.conf
COPY src/ src/
RUN gcc -Wall -o /usr/local/apache2/cgi-bin/default src/default.c
RUN gcc -Wall -o /usr/local/apache2/cgi-bin/hello src/hello.c
# RUN mv hello /usr/local/apache2/cgi-bin/

CMD [ "httpd-foreground" ]
