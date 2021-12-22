import { NOTIFICATIONS_ACTIONS } from '../constants/notifications-constants';

const initialState = {
  getNotificationsInProgress: false,
  notifications: [],
  notification: null,
};

export const notifications = (state = initialState, action) => {
  switch (action.type) {
    case NOTIFICATIONS_ACTIONS.HANDLE_GET_NOTIFICATIONS_SUCCESS:
      return { ...state, notifications: action.data.reverse() };
    case NOTIFICATIONS_ACTIONS.HANDLE_GET_NOTIFICATIONS_IN_PROGRESS:
      return { ...state, getNotificationsInProgress: action.status };
    case NOTIFICATIONS_ACTIONS.HANDLE_GET_NOTIFICATIONS_BY_ID_SUCCESS:
      return { ...state, notifications: action.data.reverse() };
    case NOTIFICATIONS_ACTIONS.HANDLE_GET_NOTIFICATIONS_BY_ID_IN_PROGRESS:
      return { ...state, getNotificationsInProgress: action.status };
    case NOTIFICATIONS_ACTIONS.HANDLE_PUT_NOTIFICATION_BY_ID_SUCCESS:
      return { ...state, notifications: action.data.reverse() };
    case NOTIFICATIONS_ACTIONS.HANDLE_PUT_NOTIFICATION_BY_ID_IN_PROGRESS:
      return { ...state, getNotificationsInProgress: action.status };
    default:
      return state;
  }
};
