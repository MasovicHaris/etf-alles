import axios from '../config/axios-config';

const requestGetNotifications = () => {
  return axios({
    method: 'GET',
    url: `/notifications`,
  });
};

const requestGetNotificationById = userId => {
  return axios({
    method: 'GET',
    url: `/notifications/getByUserId/${userId}`,
  });
};

const requestUpdateNotificationRead = notificationId => {
  return axios({
    method: 'PUT',
    url: `/notifications/setAsRead/${notificationId}`,
  });
};

const requestSubscribeTo = userId => {
  return axios({
    method: 'POST',
    url: `/users/subscribeTo/${userId}`,
  });
};

const requestUnsubscribe = userId => {
  return axios({
    method: 'POST',
    url: `/users/deleteSubscriber/${userId}`,
  });
};

const requestGetSubscribers = userId => {
  return axios({
    method: 'GET',
    url: `/users/subscribers/${userId}`,
  });
};

export default {
  requestGetNotifications,
  requestGetNotificationById,
  requestUpdateNotificationRead,
  requestSubscribeTo,
  requestGetSubscribers,
  requestUnsubscribe
};
