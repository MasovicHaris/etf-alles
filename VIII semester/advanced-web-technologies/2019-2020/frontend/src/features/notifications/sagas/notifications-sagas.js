import { call, put, takeLatest } from 'redux-saga/effects';

import {
  handleGetNotificationsByIdInProgress,
  handleGetNotificationsSuccess,
  handleGetNotificationsInProgress,
  handleGetNotificationsByIdSuccess,
  handlePutNotificationsByIdSuccess,
  handlePutNotificationsByIdInProgress,
} from '../actions/notifications-actions';
import { handleShowMessage } from '../../snackbar/actions/snackbar-actions';

import NotificationsApi from '../../../api/notifications-api';

import { SNACKBAR_SEVERITY_VARIANTS } from '../../snackbar/constants/snackbar-constants';
import { NOTIFICATIONS_ACTIONS } from '../constants/notifications-constants';

function* getNotifications() {
  try {
    yield put(handleGetNotificationsInProgress(true));
    const res = yield call(NotificationsApi.requestGetNotifications);
    yield put(handleGetNotificationsSuccess(res.data));
  } catch (err) {
    yield put(handleShowMessage('NOTIFICATIONS.ERROR_GET_NOTIFICATIONS', SNACKBAR_SEVERITY_VARIANTS.ERROR));
  } finally {
    yield put(handleGetNotificationsInProgress(false));
  }
}

function* getNotificationsById({ data }) {
  try {
    yield put(handleGetNotificationsByIdInProgress(true));
    const res = yield call(NotificationsApi.requestGetNotificationById, data);
    yield put(handleGetNotificationsByIdSuccess(res.data));
  } catch (err) {
    yield put(handleShowMessage('NOTIFICATIONS.ERROR_GET_NOTIFICATIONS', SNACKBAR_SEVERITY_VARIANTS.ERROR));
  } finally {
    yield put(handleGetNotificationsByIdInProgress(false));
  }
}

function* updateNotificationsById({ data }) {
  try {
    yield put(handlePutNotificationsByIdInProgress(true));
    const res = yield call(NotificationsApi.requestUpdateNotificationRead, data);
    yield put(handlePutNotificationsByIdSuccess(res.data));
  } catch (err) {
    yield put(handleShowMessage('NOTIFICATIONS.ERROR_PUT_NOTIFICATIONS', SNACKBAR_SEVERITY_VARIANTS.ERROR));
  } finally {
    yield put(handlePutNotificationsByIdInProgress(false));
  }
}

export default function* saga() {
  yield takeLatest(NOTIFICATIONS_ACTIONS.HANDLE_GET_NOTIFICATIONS, getNotifications);
  yield takeLatest(NOTIFICATIONS_ACTIONS.HANDLE_GET_NOTIFICATIONS_BY_ID, getNotificationsById);
  yield takeLatest(NOTIFICATIONS_ACTIONS.HANDLE_PUT_NOTIFICATION_BY_ID, updateNotificationsById);
}
