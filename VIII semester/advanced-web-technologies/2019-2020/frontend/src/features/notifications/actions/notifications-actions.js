import { NOTIFICATIONS_ACTIONS } from '../constants/notifications-constants';

export const handleGetNotifications = () => ({
  type: NOTIFICATIONS_ACTIONS.HANDLE_GET_NOTIFICATIONS,
});

export const handleGetNotificationsInProgress = status => ({
  type: NOTIFICATIONS_ACTIONS.HANDLE_GET_NOTIFICATIONS_IN_PROGRESS,
  status,
});

export const handleGetNotificationsSuccess = data => ({
  type: NOTIFICATIONS_ACTIONS.HANDLE_GET_NOTIFICATIONS_SUCCESS,
  data,
});

export const handleGetNotificationsById = data => ({
  type: NOTIFICATIONS_ACTIONS.HANDLE_GET_NOTIFICATIONS_BY_ID,
  data,
});

export const handleGetNotificationsByIdInProgress = status => ({
  type: NOTIFICATIONS_ACTIONS.HANDLE_GET_NOTIFICATIONS_BY_ID_IN_PROGRESS,
  status,
});

export const handleGetNotificationsByIdSuccess = data => ({
  type: NOTIFICATIONS_ACTIONS.HANDLE_GET_NOTIFICATIONS_BY_ID_SUCCESS,
  data,
});

export const handlePutNotificationsById = data => ({
  type: NOTIFICATIONS_ACTIONS.HANDLE_PUT_NOTIFICATION_BY_ID,
  data,
});

export const handlePutNotificationsByIdInProgress = status => ({
  type: NOTIFICATIONS_ACTIONS.HANDLE_PUT_NOTIFICATION_BY_ID_IN_PROGRESS,
  status,
});

export const handlePutNotificationsByIdSuccess = data => ({
  type: NOTIFICATIONS_ACTIONS.HANDLE_PUT_NOTIFICATION_BY_ID_SUCCESS,
  data,
});
