import { call, put, takeLatest } from 'redux-saga/effects';

import {
  handleGetCategoriesSuccess,
  handleGetCategoriesInProgress,
  handleGetEventsByCategoryInProgress,
  handleGetEventsByCategorySuccess,
  handleInterestedClickedInProgress,
  handleInterestedClickedSuccess,
  handleGoingToClickedInProgress,
  handleGoingToClickedSuccess,
  handleGetCategoryInProgress,
  handleGetCategorySuccess,
  handleGetEventInProgress,
  handleGetEventSuccess,
  handleGetCreatorInProgress,
  handleGetCreatorSuccess,
  handleGetEventsByCreatorInProgress,
  handleGetEventsByCreatorSuccess,
  handleGetEventsByAnyCreatorInProgress,
  handleGetEventsByAnyCreatorSuccess,
  handleDeleteEventInProgress,
  handleDeleteEventSuccess,
  handleGetLocationsSuccess,
  handleGetLocationsInProgress,
  handleAddEventSuccess,
  handleAddEventInProgress,
  handleUpdateEventInProgress,
  handleUpdateEventSuccess,
  handleSubscribeToInProgress,
  handleSubscribeToSuccess,
  handleUnsubscribeSuccess,
  handleGetSubscribersInProgress,
  handleGetSubscribersSuccess,
  handleUploadNewImageInProgress,
  handleUploadNewImageSuccess,
  handleGetMyEventsInterestedInProgress,
  handleGetMyEventsInterestedSuccess,
  handleGetMyEventsGoingInProgress,
  handleGetMyEventsGoingSuccess,
} from '../actions/events-page-actions';

import { handleShowMessage } from '../../snackbar/actions/snackbar-actions';

import EventsApi from '../../../api/events-api';

import UserApi from '../../../api/user-api';

import NotificationApi from '../../../api/notifications-api';

import { SNACKBAR_SEVERITY_VARIANTS } from '../../snackbar/constants/snackbar-constants';
import { EVENTS_ACTIONS } from '../constants/events-page-constants';

function* getCategories() {
  try {
    yield put(handleGetCategoriesInProgress(true));
    const res = yield call(EventsApi.requestGetCategories);
    yield put(handleGetCategoriesSuccess(res.data));
  } catch (err) {
    yield put(handleShowMessage('EVENTS.ERROR_GET_CATEGORIES', SNACKBAR_SEVERITY_VARIANTS.ERROR));
  } finally {
    yield put(handleGetCategoriesInProgress(false));
  }
}

function* getEventsByCategory({ data }) {
  try {
    yield put(handleGetEventsByCategoryInProgress(true));
    const res = yield call(EventsApi.requestGetEventsByCategory, data);
    yield put(handleGetEventsByCategorySuccess(res.data));
  } catch (err) {
    yield put(handleShowMessage('EVENTS.ERROR_GET_EVENTS', SNACKBAR_SEVERITY_VARIANTS.ERROR));
  } finally {
    yield put(handleGetEventsByCategoryInProgress(false));
  }
}

function* getEventsByCategoryLoggedInUser({ data }) {
  try {
    yield put(handleGetEventsByCategoryInProgress(true));
    const res = yield call(EventsApi.requestGetEventsByCategoryLoggedUser, data);
    yield put(handleGetEventsByCategorySuccess(res.data));
  } catch (err) {
    yield put(handleShowMessage('EVENTS.ERROR_GET_EVENTS', SNACKBAR_SEVERITY_VARIANTS.ERROR));
  } finally {
    yield put(handleGetEventsByCategoryInProgress(false));
  }
}

function* markEventAsInterested({ data }) {
  try {
    yield put(handleInterestedClickedInProgress(true));
    if (data.marked && !data.going) {
      const res = yield call(EventsApi.requestRemoveMark, data.event.id);
      yield put(handleInterestedClickedSuccess(res.data));
    } else {
      const res = yield call(EventsApi.requestMarkEventAsInterested, data.event.id);
      yield put(handleInterestedClickedSuccess(res.data));
    }
  } catch (err) {
    yield put(handleShowMessage('EVENTS.ERROR_MARK_EVENT', SNACKBAR_SEVERITY_VARIANTS.ERROR));
  } finally {
    yield put(handleInterestedClickedInProgress(false));
  }
}

function* markEventAsGoing({ data }) {
  try {
    yield put(handleGoingToClickedInProgress(true));
    if (data.marked && data.going) {
      const res = yield call(EventsApi.requestRemoveMark, data.event.id);
      yield put(handleGoingToClickedSuccess(res.data));
    } else {
      const res = yield call(EventsApi.requestMarkEventAsGoingTo, data.event.id);
      yield put(handleGoingToClickedSuccess(res.data));
    }
  } catch (err) {
    yield put(handleShowMessage('EVENTS.ERROR_MARK_EVENT', SNACKBAR_SEVERITY_VARIANTS.ERROR));
  } finally {
    yield put(handleGoingToClickedInProgress(false));
  }
}

function* getCategoryById({ data }) {
  try {
    yield put(handleGetCategoryInProgress(true));
    const res = yield call(EventsApi.requestGetCategoryById, data);
    yield put(handleGetCategorySuccess(res.data));
  } catch (err) {
    yield put(handleShowMessage('EVENTS.ERROR_GET_CATEGORIES', SNACKBAR_SEVERITY_VARIANTS.ERROR));
  } finally {
    yield put(handleGetCategoryInProgress(false));
  }
}

function* getEventById({ data }) {
  try {
    yield put(handleGetEventInProgress(true));
    const res = yield call(EventsApi.requestGetEventById, data);
    yield put(handleGetEventSuccess(res.data));
  } catch (err) {
    yield put(handleShowMessage('EVENTS.ERROR_GET_EVENTS', SNACKBAR_SEVERITY_VARIANTS.ERROR));
  } finally {
    yield put(handleGetEventInProgress(false));
  }
}

function* getEventByIdLoggedUser({ data }) {
  try {
    yield put(handleGetEventInProgress(true));
    const res = yield call(EventsApi.requestGetEventByIdLoggedUser, data);
    yield put(handleGetEventSuccess(res.data));
  } catch (err) {
    yield put(handleShowMessage('EVENTS.ERROR_GET_EVENTS', SNACKBAR_SEVERITY_VARIANTS.ERROR));
  } finally {
    yield put(handleGetEventInProgress(false));
  }
}

function* getCreator({ data }) {
  try {
    yield put(handleGetCreatorInProgress(true));
    const res = yield call(UserApi.requestUserProfileById, data);
    yield put(handleGetCreatorSuccess(res.data));
  } catch (err) {
    yield put(handleShowMessage('EVENTS.ERROR_GET_EVENTS', SNACKBAR_SEVERITY_VARIANTS.ERROR));
  } finally {
    yield put(handleGetCreatorInProgress(false));
  }
}

function* getEventsByCreator() {
  try {
    yield put(handleGetEventsByCreatorInProgress(true));
    const res = yield call(EventsApi.requestGetEventsByCreator);
    yield put(handleGetEventsByCreatorSuccess(res.data));
  } catch (err) {
    yield put(handleShowMessage('EVENTS.ERROR_GET_EVENTS', SNACKBAR_SEVERITY_VARIANTS.ERROR));
  } finally {
    yield put(handleGetEventsByCreatorInProgress(false));
  }
}

function* getEventsByAnyCreator({ data }) {
  try {
    yield put(handleGetEventsByAnyCreatorInProgress(true));
    const res = yield call(EventsApi.requestGetEventsByAnyCreator, data);
    yield put(handleGetEventsByAnyCreatorSuccess(res.data));
  } catch (err) {
    yield put(handleShowMessage('EVENTS.ERROR_GET_EVENTS', SNACKBAR_SEVERITY_VARIANTS.ERROR));
  } finally {
    yield put(handleGetEventsByAnyCreatorInProgress(false));
  }
}

function* deleteEventById({ data }) {
  try {
    yield put(handleDeleteEventInProgress(true));
    const res = yield call(EventsApi.requestDeleteEvent, data);
    yield put(handleDeleteEventSuccess(res.data));
    yield put(handleShowMessage('EVENTS.EVENT_DELETED', SNACKBAR_SEVERITY_VARIANTS.SUCCESS));
  } catch (err) {
    yield put(handleShowMessage('EVENTS.ERROR_DELETE_EVENTS', SNACKBAR_SEVERITY_VARIANTS.ERROR));
  } finally {
    yield put(handleDeleteEventInProgress(false));
    window.location.reload(false);
  }
}

function* getLocations() {
  try {
    yield put(handleGetLocationsInProgress(true));
    const res = yield call(EventsApi.requestGetLocations);
    yield put(handleGetLocationsSuccess(res.data));
  } catch (err) {
    yield put(handleShowMessage('EVENTS.ERROR_GET_LOCATIONS', SNACKBAR_SEVERITY_VARIANTS.ERROR));
  } finally {
    yield put(handleGetLocationsInProgress(false));
  }
}

function* addNewEvent({ data }) {
  console.log(data);
  const body = {
    title: data.title,
    address: data.address,
    date: data.date.toJSON(),
    description: data.description,
    idCategory: data.category,
    idLocation: data.location,
    isActive: true,
    imageUrl: data.imageUrl,
    timeFrom: data.timeFrom,
    timeTo: data.timeTo,
    endDate: data.endDate.toJSON(),
  };

  try {
    yield put(handleAddEventInProgress(true));
    const res = yield call(EventsApi.requestAddNewEvent, body);
    yield put(handleAddEventSuccess(res.data));
    yield put(handleShowMessage('EVENTS.EVENT_ADDED', SNACKBAR_SEVERITY_VARIANTS.SUCCESS));
  } catch (err) {
    yield put(handleShowMessage('EVENTS.ERROR_ADD_EVENT', SNACKBAR_SEVERITY_VARIANTS.ERROR));
  } finally {
    yield put(handleAddEventInProgress(false));
  }
}

function* updateEvent({ data, eventId }) {
  const body = {
    title: data.title,
    address: data.address,
    date: data.date.toJSON(),
    description: data.description,
    idCategory: data.category,
    idLocation: data.location,
    isActive: true,
    imageUrl: data.imageUrl,
    timeFrom: data.timeFrom,
    timeTo: data.timeTo,
    endDate: data.endDate.toJSON(),
  };
  try {
    yield put(handleUpdateEventInProgress(true));
    const res = yield call(EventsApi.requestUpdateEvent, body, eventId);
    yield put(handleUpdateEventSuccess(res.data));
    yield put(handleShowMessage('EVENTS.EVENT_UPDATED', SNACKBAR_SEVERITY_VARIANTS.SUCCESS));
  } catch (err) {
    yield put(handleShowMessage('EVENTS.ERROR_UPDATE_EVENT', SNACKBAR_SEVERITY_VARIANTS.ERROR));
  } finally {
    yield put(handleUpdateEventInProgress(false));
  }
}

function* subscribeTo({ data }) {
  try {
    yield put(handleSubscribeToInProgress(true));

    yield call(NotificationApi.requestSubscribeTo, data);

    yield put(handleSubscribeToSuccess(data));
    yield put(handleShowMessage('NOTIFICATIONS.SUBSCRIBED', SNACKBAR_SEVERITY_VARIANTS.SUCCESS));
  } catch (err) {
    yield put(handleShowMessage('NOTIFICATIONS.ERROR_SUBSCRIBED', SNACKBAR_SEVERITY_VARIANTS.ERROR));
  } finally {
    yield put(handleSubscribeToInProgress(false));
  }
}

function* unsubscribe({ data }) {
  try {
    yield call(NotificationApi.requestUnsubscribe, data);

    yield put(handleUnsubscribeSuccess(data));
    yield put(handleShowMessage('NOTIFICATIONS.UNSUBSCRIBED', SNACKBAR_SEVERITY_VARIANTS.SUCCESS));
  } catch (err) {
    yield put(handleShowMessage('NOTIFICATIONS.ERROR_UNSUBSCRIBED', SNACKBAR_SEVERITY_VARIANTS.ERROR));
  }
}

function* getSubscribers({ data }) {
  try {
    yield put(handleGetSubscribersInProgress(true));
    const res = yield call(NotificationApi.requestGetSubscribers, data);
    yield put(handleGetSubscribersSuccess(res.data));
  } catch (err) {
    yield put(handleShowMessage('EVENTS.ERROR_GET_SUBSCRIBERS', SNACKBAR_SEVERITY_VARIANTS.ERROR));
  } finally {
    yield put(handleGetSubscribersInProgress(false));
  }
}

function* requestUploadImage({ file }) {
  try {
    yield put(handleUploadNewImageInProgress(true));

    const form = new FormData();
    form.append('profileImage', file);

    const res = yield call(UserApi.requestImageUpload, form);

    yield put(handleUploadNewImageSuccess(res.data.image));
  } catch (err) {
    yield put(handleShowMessage('AUTH.ERROR_UPLOADING_IMAGE', SNACKBAR_SEVERITY_VARIANTS.ERROR));
  } finally {
    yield put(handleUploadNewImageInProgress(false));
  }
}

function* getMyEventsGoing({ data }) {
  try {
    yield put(handleGetMyEventsGoingInProgress(true));
    const res = yield call(EventsApi.requestGetMyEventsGoing, data);
    yield put(handleGetMyEventsGoingSuccess(res.data));
  } catch (err) {
    yield put(handleShowMessage('EVENTS.ERROR_GET_EVENTS', SNACKBAR_SEVERITY_VARIANTS.ERROR));
  } finally {
    yield put(handleGetMyEventsGoingInProgress(false));
  }
}

function* getMyEventsInterested({ data }) {
  try {
    yield put(handleGetMyEventsInterestedInProgress(true));
    const res = yield call(EventsApi.requestGetMyEventsInterested, data);
    yield put(handleGetMyEventsInterestedSuccess(res.data));
  } catch (err) {
    yield put(handleShowMessage('EVENTS.ERROR_GET_EVENTS', SNACKBAR_SEVERITY_VARIANTS.ERROR));
  } finally {
    yield put(handleGetMyEventsInterestedInProgress(false));
  }
}

export default function* saga() {
  yield takeLatest(EVENTS_ACTIONS.HANDLE_GET_CATEGORIES, getCategories);
  yield takeLatest(EVENTS_ACTIONS.HANDLE_GET_EVENTS_BY_CATEGORY, getEventsByCategory);
  yield takeLatest(EVENTS_ACTIONS.HANDLE_GET_EVENTS_BY_CATEGORY_LOGGED_IN_USER, getEventsByCategoryLoggedInUser);
  yield takeLatest(EVENTS_ACTIONS.HANDLE_EVENT_MARKED_AS_INTERESTED, markEventAsInterested);
  yield takeLatest(EVENTS_ACTIONS.HANDLE_EVENT_MARKED_AS_GOING_TO, markEventAsGoing);
  yield takeLatest(EVENTS_ACTIONS.HANDLE_GET_CATEGORY, getCategoryById);
  yield takeLatest(EVENTS_ACTIONS.HANDLE_GET_EVENT, getEventById);
  yield takeLatest(EVENTS_ACTIONS.HANDLE_GET_EVENT_LOGGED_IN_USER, getEventByIdLoggedUser);
  yield takeLatest(EVENTS_ACTIONS.HANDLE_GET_CREATOR, getCreator);
  yield takeLatest(EVENTS_ACTIONS.HANDLE_GET_EVENTS_BY_CREATOR, getEventsByCreator);
  yield takeLatest(EVENTS_ACTIONS.HANDLE_GET_EVENTS_BY_ANY_CREATOR, getEventsByAnyCreator);
  yield takeLatest(EVENTS_ACTIONS.HANDLE_DELETE_EVENT, deleteEventById);
  yield takeLatest(EVENTS_ACTIONS.HANDLE_GET_LOCATIONS, getLocations);
  yield takeLatest(EVENTS_ACTIONS.HANDLE_ADD_NEW_EVENT, addNewEvent);
  yield takeLatest(EVENTS_ACTIONS.HANDLE_UPDATE_EVENT, updateEvent);
  yield takeLatest(EVENTS_ACTIONS.HANDLE_SUBSCRIBE_TO, subscribeTo);
  yield takeLatest(EVENTS_ACTIONS.HANDLE_UNSUBSCRIBE, unsubscribe);
  yield takeLatest(EVENTS_ACTIONS.HANDLE_GET_SUBSCRIBERS, getSubscribers);
  yield takeLatest(EVENTS_ACTIONS.HANDLE_UPLOAD_NEW_IMAGE, requestUploadImage);
  yield takeLatest(EVENTS_ACTIONS.HANDLE_GET_MY_EVENTS_GOING, getMyEventsGoing);
  yield takeLatest(EVENTS_ACTIONS.HANDLE_GET_MY_EVENTS_INTERESTED, getMyEventsInterested);
}
