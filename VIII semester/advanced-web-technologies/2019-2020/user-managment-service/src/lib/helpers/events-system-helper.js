import grpc from 'grpc';
import path from 'path';
const protoLoader = require('@grpc/proto-loader');

import servicesHelper from './services-helper';

import { SERVICES } from '../../config/constants';

const requestProtoDefinition = protoLoader.loadSync(path.join(__dirname, '..', 'proto', 'event4u.proto'));
const requestDefinition = grpc.loadPackageDefinition(requestProtoDefinition);

const logEvent = (request, callback) => {
  const systemEventsServiceUrl = servicesHelper.getServiceUrl(SERVICES.SYSTEM_EVENTS_SERVICE);
  const client = new requestDefinition.action(systemEventsServiceUrl, grpc.credentials.createInsecure());

  client.logAction(request, (err, result) => {
    if (err) {
      console.log('[logEvent] - ', err);
      callback(null);
    }
    callback(result);
  });
};

export default {
  logEvent,
};
