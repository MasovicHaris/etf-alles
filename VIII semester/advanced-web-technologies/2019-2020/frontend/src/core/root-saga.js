import { all } from 'redux-saga/effects';

import authSagas from '../features/auth/sagas/auth-sagas';
import eventsSagas from '../features/events-page/sagas/events-page-sagas';
import notificationsSaga from '../features/notifications/sagas/notifications-sagas'

export default function* rootSaga() {
  yield all([authSagas(), eventsSagas(), notificationsSaga()]);
}
