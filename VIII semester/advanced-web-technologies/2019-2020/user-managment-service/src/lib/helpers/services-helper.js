import client from '../../index';

import { SERVICES } from '../../config/constants';

const getServiceUrl = (serviceName = SERVICES.EVENT_SERVICE) => {
  const baseUrl = client.getInstancesByAppId(serviceName)[0].homePageUrl;
  const systemEventsUrl = baseUrl.split('//')[1].split(':')[0];

  switch (serviceName) {
    case SERVICES.EVENT_SERVICE:
      return `${baseUrl}events-micro`;
    case SERVICES.SYSTEM_EVENTS_SERVICE:
      return process.platform === 'win32' ? `dns:///${systemEventsUrl}:6565` : `dns://${systemEventsUrl}:6565`;
    default:
      return null;
  }
};

export default {
  getServiceUrl,
};
