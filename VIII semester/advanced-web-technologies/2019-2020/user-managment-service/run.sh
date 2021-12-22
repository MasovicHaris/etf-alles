#!/bin/sh
while ! nc -z eureka-service 8761 ; do
    echo "[user-managment-service] Waiting 4 eureka 2 start"
    sleep 3
done

npm start