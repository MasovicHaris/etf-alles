import express from 'express';
import dotenv from 'dotenv';
import bodyParser from 'body-parser';
import cookieParser from 'cookie-parser';
import { Eureka } from 'eureka-js-client';

import database from './lib/db/';
import userRoutes from './routes/user-routes';
import authRoutes from './routes/auth-routes';

import { DEFAULT_USERS, PORT, INITIAL_DB_SETUP, FULL_BASE_URL, EUREKA_HOST_BASE_URL, BACKEND_HOST_BASE_URL, SERVICES } from './config/constants';

dotenv.config();
database.sequelize.sync({ force: INITIAL_DB_SETUP }).then(async () => {
  if (INITIAL_DB_SETUP) {
    await database.User.bulkCreate(DEFAULT_USERS);
    console.log('[user-managment-service] Successfully created a new database and imported initial data!');
  }
});

const app = express();
const APPLICATION_NAME = 'user-management-service';

const client = new Eureka({
  instance: {
    app: APPLICATION_NAME,
    hostName: SERVICES.USER_MANAGEMENT_SERVICE,
    ipAddr: BACKEND_HOST_BASE_URL,
    statusPageUrl: FULL_BASE_URL,
    homePageUrl: FULL_BASE_URL,
    vipAddress: APPLICATION_NAME,
    port: {
      $: PORT,
      '@enabled': 'true',
    },
    dataCenterInfo: {
      '@class': 'com.netflix.appinfo.InstanceInfo$DefaultDataCenterInfo',
      name: 'MyOwn',
    },
    registerWithEureka: true,
    fetchRegistry: true,
  },
  eureka: {
    host: EUREKA_HOST_BASE_URL,
    port: 8761,
    servicePath: '/eureka/apps/',
  },
});

client.start((error) => {
  console.log('[user-managment-service]', error || 'Eureka connected!');

  app.use(bodyParser.json());
  app.use(bodyParser.urlencoded({ extended: false }));
  app.use(cookieParser());

  app.use('/api/users', userRoutes);
  app.use('/api/auth', authRoutes);
});

app.listen(PORT, () => console.log(`[user-managment-service] Listening on port ${PORT}!`));

export default client;
