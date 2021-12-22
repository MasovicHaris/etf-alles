import axios from '../config/axios-config';

const requestGetCategories = () => {
  return axios({
    method: 'GET',
    url: `/events-micro/categories`,
  });
};

const requestGetEventsByCategory = categoryId => {
  return axios({
    method: 'GET',
    url: `/events-micro/events/category/${categoryId}`,
  });
};

const requestGetEventsByCategoryLoggedUser = categoryId => {
  return axios({
    method: 'GET',
    url: `/events-micro/events/category-user/${categoryId}`,
  });
};

const requestMarkEventAsInterested = eventId => {
  return axios({
    method: 'POST',
    url: `/events-micro/interested/${eventId}`,
  });
};

const requestMarkEventAsGoingTo = eventId => {
  return axios({
    method: 'POST',
    url: `/events-micro/going/${eventId}`,
  });
};

const requestRemoveMark = eventId => {
  return axios({
    method: 'DELETE',
    url: `/events-micro/removeMark/${eventId}`,
  });
};

const requestGetCategoryById = categoryId => {
  return axios({
    method: 'GET',
    url: `/events-micro/categories/${categoryId}`,
  });
};

const requestGetEventById = eventId => {
  return axios({
    method: 'GET',
    url: `/events-micro/events/${eventId}`,
  });
};

const requestGetEventByIdLoggedUser = eventId => {
  return axios({
    method: 'GET',
    url: `/events-micro/events/user/${eventId}`,
  });
};

const requestGetEventsByCreator = () => {
  return axios({
    method: 'GET',
    url: `/events-micro/events/my-events`,
  });
};

const requestGetEventsByAnyCreator = userId => {
  return axios({
    method: 'GET',
    url: `/events-micro/events/creator/${userId}`,
  });
};

const requestDeleteEvent = eventId => {
  return axios({
    method: 'DELETE',
    url: `/events-micro/events/${eventId}`,
  });
};

const requestGetLocations = () => {
  return axios({
    method: 'GET',
    url: `/events-micro/locations`,
  });
};

const requestAddNewEvent = data => {
  return axios({
    method: 'POST',
    url: `events-micro/events`,
    data: data,
  });
};

const requestUpdateEvent = (data, eventId) => {
  return axios({
    method: 'PUT',
    url: `events-micro/events/${eventId}`,
    data: data,
  });
};

const requestGetMyEventsGoing = () => {
  return axios({
    method: 'GET',
    url: '/events-micro/my-events/going'
  })
}

const requestGetMyEventsInterested = () => {
  return axios({
    method: 'GET',
    url: '/events-micro/my-events/interested'
  })
}

export default {
  requestGetCategories,
  requestGetEventsByCategory,
  requestGetEventsByCategoryLoggedUser,
  requestMarkEventAsInterested,
  requestMarkEventAsGoingTo,
  requestRemoveMark,
  requestGetCategoryById,
  requestGetEventById,
  requestGetEventByIdLoggedUser,
  requestGetEventsByCreator,
  requestGetEventsByAnyCreator,
  requestDeleteEvent,
  requestGetLocations,
  requestAddNewEvent,
  requestUpdateEvent,
  requestGetMyEventsInterested,
  requestGetMyEventsGoing
};
