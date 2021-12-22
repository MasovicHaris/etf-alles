## Pre-running requests

### Setting up the firebase admin key

- In order to use firebase service, you need to add a `.json` file called `firebase.json` to the root folder of this service which represents the firebase private key generated via the admin SDK (`service accounts`).
- To find your firebase config file go to the firebase web page and into your project settings you can generate a new private key configuration file in `.json` format.
- Also you need define the `STORAGE_BUCKET`, `FIREBASE_DATABASE_URL` and `FIREBASE_STORAGE_URL`, in the .env file, which you can find also on the same site.
- After that you have to go to the google storage site, and add a public user role to make your bucket public so anyone can see the uploaded images via links.

### Setting up database (in case of running `locally`)

- You must setup your MYSQL database and remember the connection parameters

### Setting up the environment

- In order to run `user-management-service` you must define these env variables in an `.env` file (in the root service path):

```
DB_USERNAME=your_db_username
DB_PASSWORD=your_password
DB_HOST=your_db_host # in case of docker: db
DB_PORT=your_port
DATABASE=your_database_name
JWT_SECRET=your_secret
JWT_EXPIRE_TIME_TOKEN=1h
INITIAL_DB_SETUP=true # in case of locally, you can do it once, in case of docker: true always
PORT=your_port
FULL_BASE_URL=your_base_url # in case of docker: http://user-management-service:4000
EUREKA_HOST_BASE_URL=localhost # in case of docker: eureka-service
BACKEND_HOST_BASE_URL=localhost # in case of docker: user-management-service
STORAGE_BUCKET=your_storage_bucket
FIREBASE_DATABASE_URL=your_firebase_url
FIREBASE_STORAGE_URL=https://storage.googleapis.com
```

### Running the service (`locally`)

- You must have node (`>= 10` version) as well as npm installed (`>= 6` version)
- All other services must be started
- In case of running locally run:

```shell script
npm install
npm start
```

## Running tests (`locally` only)

- In order to run tests the initial db setup, if you haven't done it already, is required (`INITIAL_DB_SETUP`)
- Open a second terminal (all services must be active) and type `npm test`
- Note:
  - Tests for saving uploaded images were not added due to saving memory space on the firebase service
  - Due to the written endpoint flows (prerequisites, orm, handling responses), tests are written in a way that provides a 100% assurance regarding that endpoints are working or not
