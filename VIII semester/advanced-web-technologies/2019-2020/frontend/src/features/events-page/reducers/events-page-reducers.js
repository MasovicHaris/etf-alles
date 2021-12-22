import { EVENTS_ACTIONS } from '../constants/events-page-constants';

const getEventsInitialState = () => {
  return {
    getCategoriesInProgres: false,
    categories: [],
    category: null,
    getEventsInProgres: false,
    getUserEventsInProgres: false,
    events: [],
    eventInfo: null,
    going: false,
    marked: false,
    markAsInterestedInProgress: false,
    getCategoryInProgres: false,
    getEventInProgres: false,
    getCreatorInProgres: false,
    getMyEventsGoingInProgres: false,
    getMyEventsInterestedInProgres: false,
    creatorOfEvent: {
      id: null,
      name: '',
      surname: '',
      picture: '',
      username: '',
      description: '',
    },
    myEvents: [],
    userEvents: [],
    myEventsGoing: [],
    myEventsInterested: [],
    locations: [],
    getLocationsInProgres: false,
    addNewEventInProgres: false,
    deleteEventInProgres: false,
    selectedDate: new Date(),
    selectedEndDate: new Date(),
    expended: false,
    updateEventInProgres: false,
    getSubscribers: false,
    mySubscribers: [],
    uploadedImageUrl: '',
    uploadImageInProgress: false,
  };
};

export const events = (state = getEventsInitialState(), action) => {
  switch (action.type) {
    case EVENTS_ACTIONS.HANDLE_GET_CATEGORIES_SUCCESS:
      return { ...state, categories: action.data };
    case EVENTS_ACTIONS.HANDLE_GET_CATEGORIES_IN_PROGRESS:
      return { ...state, getCategoriesInProgres: action.status };
    case EVENTS_ACTIONS.HANDLE_CATEGORY_CHOSEN:
      return { ...state, category: action.data };
    case EVENTS_ACTIONS.HANDLE_GET_EVENTS_BY_CATEGORY_SUCCESS:
      return { ...state, events: action.data };
    case EVENTS_ACTIONS.HANDLE_GET_EVENTS_BY_CATEGORY_IN_PROGRESS:
      return { ...state, getCategoriesInProgres: action.status };
    case EVENTS_ACTIONS.HANDLE_EVENT_MARKED_AS_INTERESTED_IN_PROGRESS:
      return { ...state, markAsInterestedInProgress: action.status };
    case EVENTS_ACTIONS.HANDLE_EVENT_MARKED_AS_INTERESTED_SUCCESS:
      return {
        ...state,
        events: state.events.map(eventInfo => (eventInfo.event.id === action.data.event.id ? { event: action.data.event, going: action.data.going, marked: action.data.marked } : eventInfo)),
        eventInfo: action.data,
      };
    case EVENTS_ACTIONS.HANDLE_EVENT_MARKED_AS_GOING_IN_PROGRESS:
      return { ...state, markAsInterestedInProgress: action.status };
    case EVENTS_ACTIONS.HANDLE_EVENT_MARKED_AS_GOING_SUCCESS:
      return {
        ...state,
        events: state.events.map(eventInfo => (eventInfo.event.id === action.data.event.id ? { event: action.data.event, going: action.data.going, marked: action.data.marked } : eventInfo)),
        eventInfo: action.data,
      };
    case EVENTS_ACTIONS.HANDLE_GET_CATEGORY_IN_PROGRESS:
      return { ...state, getCategoryInProgres: action.status };
    case EVENTS_ACTIONS.HANDLE_GET_CATEGORY_SUCCESS:
      return { ...state, category: action.data };
    case EVENTS_ACTIONS.HANDLE_GET_EVENT_IN_PROGRESS:
      return { ...state, getEventInProgres: action.status };
    case EVENTS_ACTIONS.HANDLE_GET_EVENT_SUCCESS:
      return { ...state, eventInfo: action.data };
    case EVENTS_ACTIONS.HANDLE_GET_CREATOR_IN_PROGRESS:
      return { ...state, getCreatorInProgres: action.status };
    case EVENTS_ACTIONS.HANDLE_GET_CREATOR_SUCCESS:
      return { ...state, creatorOfEvent: action.data };
    case EVENTS_ACTIONS.HANDLE_GET_EVENTS_BY_CREATOR_IN_PROGRESS:
      return { ...state, getEventsInProgres: action.status };
    case EVENTS_ACTIONS.HANDLE_GET_EVENTS_BY_CREATOR_SUCCESS:
      return { ...state, myEvents: action.data };
    case EVENTS_ACTIONS.HANDLE_GET_EVENTS_BY_ANY_CREATOR_IN_PROGRESS:
      return { ...state, getUserEventsInProgres: action.status };
    case EVENTS_ACTIONS.HANDLE_GET_EVENTS_BY_ANY_CREATOR_SUCCESS:
      return { ...state, userEvents: action.data };
    case EVENTS_ACTIONS.HANDLE_GET_MY_EVENTS_GOING_IN_PROGRESS:
      return { ...state, getMyEventsGoingInProgres: action.status };
    case EVENTS_ACTIONS.HANDLE_GET_MY_EVENTS_GOING_SUCCESS:
      return { ...state, myEventsGoing: action.data };
    case EVENTS_ACTIONS.HANDLE_GET_MY_EVENTS_INTERESTED_IN_PROGRESS:
      return { ...state, getMyEventsInterestedInProgres: action.status };
    case EVENTS_ACTIONS.HANDLE_GET_MY_EVENTS_INTERESTED_SUCCESS:
      return { ...state, myEventsInterested: action.data };
    case EVENTS_ACTIONS.HANDLE_GET_LOCATIONS_SUCCESS:
      return { ...state, locations: action.data };
    case EVENTS_ACTIONS.HANDLE_GET_LOCATIONS_IN_PROGRESS:
      return { ...state, getLocationsInProgres: action.status };
    case EVENTS_ACTIONS.HANDLE_ADD_NEW_EVENT_SUCCESS:
      return { ...state, eventInfo: action.data };
    case EVENTS_ACTIONS.HANDLE_ADD_NEW_EVENT_IN_PROGRESS:
      return { ...state, addNewEventInProgres: action.status, uploadedImageUrl: '' };
    case EVENTS_ACTIONS.HANDLE_UPDATE_EVENT_SUCCESS:
      return { ...state, eventInfo: action.data };
    case EVENTS_ACTIONS.HANDLE_UPDATE_EVENT_IN_PROGRESS:
      return { ...state, updateEventInProgres: action.status };
    case EVENTS_ACTIONS.HANDLE_SET_DATE:
      return { ...state, selectedDate: action.data };
    case EVENTS_ACTIONS.HANDLE_SET_END_DATE:
      return { ...state, selectedEndDate: action.data };
    case EVENTS_ACTIONS.HANDLE_DELETE_EVENT_IN_PROGRESS:
      return { ...state, deleteEventInProgres: action.status };
    case EVENTS_ACTIONS.HANDLE_DELETE_EVENT_SUCCESS:
      return { ...state, events: action.data };
    case EVENTS_ACTIONS.HANDLE_EXPAND_CLICKED:
      return { ...state, expanded: action.data };
    case EVENTS_ACTIONS.HANDLE_GET_SUBSCRIBERS_IN_PROGRESS:
      return { ...state, getSubscribers: action.status };
    case EVENTS_ACTIONS.HANDLE_GET_SUBSCRIBERS_SUCCESS:
      return { ...state, mySubscribers: action.data };
    case EVENTS_ACTIONS.HANDLE_SUBSCRIBE_TO_IN_PROGRESS:
      return { ...state, getSubscribers: action.status };
    case EVENTS_ACTIONS.HANDLE_UPLOAD_NEW_IMAGE_IN_PROGRESS:
      return { ...state, uploadImageInProgress: action.status };
    case EVENTS_ACTIONS.HANDLE_UPLOAD_NEW_IMAGE_SUCCESS:
      return { ...state, uploadedImageUrl: action.data };
    case EVENTS_ACTIONS.HANDLE_SUBSCRIBE_TO_SUCCESS:
      return { ...state, mySubscribers: [...state.mySubscribers, parseInt(action.data)] };
    case EVENTS_ACTIONS.HANDLE_UNSUBSCRIBE_SUCCESS:
      return {
        ...state,
        mySubscribers: state.mySubscribers.filter(idSub => idSub !== parseInt(action.data)),
      };
    case EVENTS_ACTIONS.HANDLE_CHANGE_IMAGE_URL:
      return { ...state, uploadedImageUrl: action.data };
    default:
      return state;
  }
};
