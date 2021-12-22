#!/bin/sh
while ! nc -z eureka-service 8761 ; do
    echo "[system-events] Waiting 4 eureka 2 start"
    sleep 3
done

java -jar /app.jar --spring.config.location=classpath:/docker.properties