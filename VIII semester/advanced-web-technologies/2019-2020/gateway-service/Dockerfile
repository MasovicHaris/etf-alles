FROM node:10.20.1

USER root

RUN ["apt-get", "update"]
RUN ["apt-get", "install", "-y", "netcat"]

WORKDIR /usr/src/app

COPY package*.json ./

RUN npm install

COPY . .

COPY run.sh eureka.sh

RUN ["chmod", "775", "eureka.sh"]

ENTRYPOINT ["/usr/src/app/eureka.sh"]