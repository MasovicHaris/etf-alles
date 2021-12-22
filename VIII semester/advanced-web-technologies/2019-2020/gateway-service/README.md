## Pre-running requests
- In order to run the `gateway-service` you must define these env variables in an .env file (root service directory):

```
PORT=your_port
FULL_BASE_URL=your_full_base_url // in case of docker: http://gateway-service:4200
FRONTEND_URL=http://localhost:3000
EUREKA_HOST_BASE_URL=localhost // in case of docker: eureka-service
BACKEND_HOST_BASE_URL=localhost // in case of docker: gateway-service
```

## Running the service (`locally`)

- You must have node (`>= 10` version) as well as npm installed (`>= 6` version)
- All other services must be started
- After that run: 

```shell script
npm install
npm start
```
