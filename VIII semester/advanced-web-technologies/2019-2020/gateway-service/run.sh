#!/bin/sh
while ! nc -z eureka-service 8761 ; do
    echo "[gateway-service] Waiting 4 eureka"
    sleep 3
done

while ! nc -z events-service 8081 ; do
    echo "[gateway-service] Waiting 4 events-service"
    sleep 3
done

while ! nc -z user-management-service 4000 ; do
    echo "[gateway-service] Waiting 4 user-management-service"
    sleep 3
done

while ! nc -z notification-service 8088 ; do
    echo "[gateway-service] Waiting 4 notification-service"
    sleep 3
done
# sleep 20 seconds for connections to happen
echo "[gateway-service] Waiting 20 seconds for all eureka connections, before starting."
sleep 20

npm start