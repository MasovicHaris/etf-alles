import express from 'express';
import dotenv from 'dotenv';
import bodyParser from 'body-parser';
import cookieParser from 'cookie-parser';
import cors from 'cors';
import proxy from 'express-http-proxy';
import { Eureka } from 'eureka-js-client';

import serviceHelper from './lib/helpers/services-helper';

import { PORT, FRONTEND_URL, FULL_BASE_URL, EUREKA_HOST_BASE_URL, BACKEND_HOST_BASE_URL, SERVICES } from './config/constants';

import userRoutes from './lib/middlewares/get-user';

dotenv.config();

const app = express();
const APPLICATION_NAME = 'gateway-service';

const client = new Eureka({
  instance: {
    app: APPLICATION_NAME,
    hostName: SERVICES.GATEWAY_SERVICE,
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
    preferIpAddress: true,
  },
  eureka: {
    host: EUREKA_HOST_BASE_URL,
    port: 8761,
    servicePath: '/eureka/apps/',
    preferIpAddress: true,
  },
});

client.start((error) => {
  console.log('[gateway-service]', error || 'Eureka connected!');
  app.use(
    '*',
    cors({
      origin: FRONTEND_URL,
      optionsSuccessStatus: 200,
      credentials: true,
    })
  );

  // direct proxy
  const userManagementServiceUrl = serviceHelper.getServiceUrl(SERVICES.USER_MANAGEMENT_SERVICE);
  const eventsServiceUrl = serviceHelper.getServiceUrl(SERVICES.EVENT_SERVICE);
  const notificationsServiceUrl = serviceHelper.getServiceUrl(SERVICES.NOTIFICATION_SERVICE);

  app.use(
    '/aggregator',
    proxy(userManagementServiceUrl, {
      filter: (req, res) => req.path.includes('/api/auth') || req.path.includes('/api/users'),
    }),
    proxy(eventsServiceUrl, {
      filter: (req, res) => {
        if (req.path.includes('/events-micro')) {
          if (req.path.includes('/locations') && req.method != 'GET') return false;
          if (req.path.includes('/categories') && req.method != 'GET') return false;
          return true;
        }
        return false;
      },
    }),
    proxy(notificationsServiceUrl, {
      filter: (req, res) => req.path.includes('/users') || req.path.includes('/notifications') || req.path.includes('/events') || req.path.includes('/ws'),
    })
  );

  app.use(bodyParser.json());
  app.use(bodyParser.urlencoded({ extended: false }));
  app.use(cookieParser());
  app.use('/aggregator', userRoutes);
});
app.listen(PORT, () => console.log(`[gateway-service] Listening on port ${PORT}!`));

export default client;
