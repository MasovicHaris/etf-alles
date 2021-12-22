import { combineReducers } from 'redux';

import { auth } from '../features/auth/reducers/auth-reducers';
import { snackbar } from '../features/snackbar/reducers/snackbar-reducers';
import { events } from '../features/events-page/reducers/events-page-reducers';
import { notifications } from '../features/notifications/reducers/notifications-reducer';

const appReducer = combineReducers({
  auth,
  snackbar,
  events,
  notifications,
});

export const rootReducer = (state, action) => {
  return appReducer(state, action);
};
