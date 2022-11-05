FROM httpd:alpine

RUN apk update
RUN apk add curl gcc libc-dev

COPY ./httpd.conf /usr/local/apache2/conf/httpd.conf
COPY src/ src/
RUN gcc -Wall -o /usr/local/apache2/cgi-bin/default src/default.c
RUN gcc -Wall -o /usr/local/apache2/cgi-bin/new src/new.c
COPY styles/default.css /usr/local/apache2/default.css
RUN chmod a-x /usr/local/apache2/default.css

CMD [ "httpd-foreground" ]
