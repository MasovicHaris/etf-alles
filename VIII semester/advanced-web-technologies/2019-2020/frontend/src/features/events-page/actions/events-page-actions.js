import { EVENTS_ACTIONS } from '../constants/events-page-constants';

export const handleGetCategories = () => ({
  type: EVENTS_ACTIONS.HANDLE_GET_CATEGORIES,
});

export const handleGetCategoriesInProgress = status => ({
  type: EVENTS_ACTIONS.HANDLE_GET_CATEGORIES_IN_PROGRESS,
  status,
});

export const handleGetCategoriesSuccess = data => ({
  type: EVENTS_ACTIONS.HANDLE_GET_CATEGORIES_SUCCESS,
  data,
});

export const handleGetEventsByCategory = data => ({
  type: EVENTS_ACTIONS.HANDLE_GET_EVENTS_BY_CATEGORY,
  data,
});

export const handleGetEventsByCategoryLoggedUser = data => ({
  type: EVENTS_ACTIONS.HANDLE_GET_EVENTS_BY_CATEGORY_LOGGED_IN_USER,
  data,
});

export const handleGetEventsByCategoryInProgress = status => ({
  type: EVENTS_ACTIONS.HANDLE_GET_EVENTS_BY_CATEGORY_IN_PROGRESS,
  status,
});

export const handleGetEventsByCategorySuccess = data => ({
  type: EVENTS_ACTIONS.HANDLE_GET_EVENTS_BY_CATEGORY_SUCCESS,
  data,
});

export const handleCategoryClicked = data => ({
  type: EVENTS_ACTIONS.HANDLE_CATEGORY_CHOSEN,
  data,
});

export const handleInterestedClicked = data => ({
  type: EVENTS_ACTIONS.HANDLE_EVENT_MARKED_AS_INTERESTED,
  data,
});

export const handleInterestedClickedInProgress = status => ({
  type: EVENTS_ACTIONS.HANDLE_EVENT_MARKED_AS_INTERESTED_IN_PROGRESS,
  status,
});

export const handleInterestedClickedSuccess = data => ({
  type: EVENTS_ACTIONS.HANDLE_EVENT_MARKED_AS_INTERESTED_SUCCESS,
  data,
});

export const handleGoingToClicked = data => ({
  type: EVENTS_ACTIONS.HANDLE_EVENT_MARKED_AS_GOING_TO,
  data,
});

export const handleGoingToClickedInProgress = status => ({
  type: EVENTS_ACTIONS.HANDLE_EVENT_MARKED_AS_INTERESTED_IN_PROGRESS,
  status,
});

export const handleGoingToClickedSuccess = data => ({
  type: EVENTS_ACTIONS.HANDLE_EVENT_MARKED_AS_INTERESTED_SUCCESS,
  data,
});

export const handleGetCategory = data => ({
  type: EVENTS_ACTIONS.HANDLE_GET_CATEGORY,
  data,
});

export const handleGetCategoryInProgress = status => ({
  type: EVENTS_ACTIONS.HANDLE_GET_CATEGORY_IN_PROGRESS,
  status,
});

export const handleGetCategorySuccess = data => ({
  type: EVENTS_ACTIONS.HANDLE_GET_CATEGORY_SUCCESS,
  data,
});

export const handleGetEvent = data => ({
  type: EVENTS_ACTIONS.HANDLE_GET_EVENT,
  data,
});

export const handleGetEventLoggedUser = data => ({
  type: EVENTS_ACTIONS.HANDLE_GET_EVENT_LOGGED_IN_USER,
  data,
});

export const handleGetEventInProgress = status => ({
  type: EVENTS_ACTIONS.HANDLE_GET_EVENT_IN_PROGRESS,
  status,
});

export const handleGetEventSuccess = data => ({
  type: EVENTS_ACTIONS.HANDLE_GET_EVENT_SUCCESS,
  data,
});

export const handleGetCreator = data => ({
  type: EVENTS_ACTIONS.HANDLE_GET_CREATOR,
  data,
});

export const handleGetCreatorInProgress = status => ({
  type: EVENTS_ACTIONS.HANDLE_GET_CREATOR_IN_PROGRESS,
  status,
});

export const handleGetCreatorSuccess = data => ({
  type: EVENTS_ACTIONS.HANDLE_GET_CREATOR_SUCCESS,
  data,
});

export const handleGetEventsByCreator = () => ({
  type: EVENTS_ACTIONS.HANDLE_GET_EVENTS_BY_CREATOR,
});

export const handleGetEventsByCreatorInProgress = status => ({
  type: EVENTS_ACTIONS.HANDLE_GET_EVENTS_BY_CREATOR_IN_PROGRESS,
  status,
});

export const handleGetEventsByCreatorSuccess = data => ({
  type: EVENTS_ACTIONS.HANDLE_GET_EVENTS_BY_CREATOR_SUCCESS,
  data,
});

export const handleGetEventsByAnyCreator = data => ({
  type: EVENTS_ACTIONS.HANDLE_GET_EVENTS_BY_ANY_CREATOR,
  data,
});

export const handleGetEventsByAnyCreatorInProgress = status => ({
  type: EVENTS_ACTIONS.HANDLE_GET_EVENTS_BY_ANY_CREATOR_IN_PROGRESS,
  status,
});

export const handleGetEventsByAnyCreatorSuccess = data => ({
  type: EVENTS_ACTIONS.HANDLE_GET_EVENTS_BY_ANY_CREATOR_SUCCESS,
  data,
});

export const handleGetMyEventsGoing = () => ({
  type: EVENTS_ACTIONS.HANDLE_GET_MY_EVENTS_GOING,
});

export const handleGetMyEventsGoingInProgress = status => ({
  type: EVENTS_ACTIONS.HANDLE_GET_MY_EVENTS_GOING_IN_PROGRESS,
  status,
});

export const handleGetMyEventsGoingSuccess = data => ({
  type: EVENTS_ACTIONS.HANDLE_GET_MY_EVENTS_GOING_SUCCESS,
  data,
});

export const handleGetMyEventsInterested = () => ({
  type: EVENTS_ACTIONS.HANDLE_GET_MY_EVENTS_INTERESTED,
});

export const handleGetMyEventsInterestedInProgress = status => ({
  type: EVENTS_ACTIONS.HANDLE_GET_MY_EVENTS_INTERESTED_IN_PROGRESS,
  status,
});

export const handleGetMyEventsInterestedSuccess = data => ({
  type: EVENTS_ACTIONS.HANDLE_GET_MY_EVENTS_INTERESTED_SUCCESS,
  data,
});

export const handleDeleteEvent = data => ({
  type: EVENTS_ACTIONS.HANDLE_DELETE_EVENT,
  data,
});

export const handleDeleteEventInProgress = status => ({
  type: EVENTS_ACTIONS.HANDLE_DELETE_EVENT_IN_PROGRESS,
  status,
});

export const handleDeleteEventSuccess = data => ({
  type: EVENTS_ACTIONS.HANDLE_DELETE_EVENT_SUCCESS,
  data,
});

export const handleGetLocations = () => ({
  type: EVENTS_ACTIONS.HANDLE_GET_LOCATIONS,
});

export const handleGetLocationsInProgress = status => ({
  type: EVENTS_ACTIONS.HANDLE_GET_LOCATIONS_IN_PROGRESS,
  status,
});

export const handleGetLocationsSuccess = data => ({
  type: EVENTS_ACTIONS.HANDLE_GET_LOCATIONS_SUCCESS,
  data,
});

export const handleAddNewEvent = data => ({
  type: EVENTS_ACTIONS.HANDLE_ADD_NEW_EVENT,
  data,
});

export const handleAddEventInProgress = status => ({
  type: EVENTS_ACTIONS.HANDLE_ADD_NEW_EVENT_IN_PROGRESS,
  status,
});

export const handleAddEventSuccess = data => ({
  type: EVENTS_ACTIONS.HANDLE_ADD_NEW_EVENT_SUCCESS,
  data,
});

export const handleUpdateEvent = (data, eventId) => ({
  type: EVENTS_ACTIONS.HANDLE_UPDATE_EVENT,
  data,
  eventId,
});

export const handleUpdateEventInProgress = status => ({
  type: EVENTS_ACTIONS.HANDLE_UPDATE_EVENT_IN_PROGRESS,
  status,
});

export const handleUpdateEventSuccess = data => ({
  type: EVENTS_ACTIONS.HANDLE_UPDATE_EVENT_SUCCESS,
  data,
});

export const setSelectedDate = data => ({
  type: EVENTS_ACTIONS.HANDLE_SET_DATE,
  data,
});

export const setSelectedEndDate = data => ({
  type: EVENTS_ACTIONS.HANDLE_SET_END_DATE,
  data,
});

export const handleGetSubscribers = data => ({
  type: EVENTS_ACTIONS.HANDLE_GET_SUBSCRIBERS,
  data,
});

export const handleGetSubscribersInProgress = status => ({
  type: EVENTS_ACTIONS.HANDLE_GET_SUBSCRIBERS_IN_PROGRESS,
  status,
});

export const handleGetSubscribersSuccess = data => ({
  type: EVENTS_ACTIONS.HANDLE_GET_SUBSCRIBERS_SUCCESS,
  data,
});

export const handleSubscribeTo = data => ({
  type: EVENTS_ACTIONS.HANDLE_SUBSCRIBE_TO,
  data,
});

export const handleUnsubscribe = data => ({
  type: EVENTS_ACTIONS.HANDLE_UNSUBSCRIBE,
  data,
});

export const handleSubscribeToInProgress = status => ({
  type: EVENTS_ACTIONS.HANDLE_SUBSCRIBE_TO_IN_PROGRESS,
  status,
});

export const handleSubscribeToSuccess = data => ({
  type: EVENTS_ACTIONS.HANDLE_SUBSCRIBE_TO_SUCCESS,
  data,
});

export const handleUnsubscribeSuccess = data => ({
  type: EVENTS_ACTIONS.HANDLE_UNSUBSCRIBE_SUCCESS,
  data,
});

export const handleUploadNewImage = file => ({
  type: EVENTS_ACTIONS.HANDLE_UPLOAD_NEW_IMAGE,
  file,
});

export const handleUploadNewImageInProgress = status => ({
  type: EVENTS_ACTIONS.HANDLE_UPLOAD_NEW_IMAGE_IN_PROGRESS,
  status,
});

export const handleUploadNewImageSuccess = data => ({
  type: EVENTS_ACTIONS.HANDLE_UPLOAD_NEW_IMAGE_SUCCESS,
  data,
});

export const handleChangeImageUrl = data => ({
  type: EVENTS_ACTIONS.HANDLE_CHANGE_IMAGE_URL,
  data,
});
