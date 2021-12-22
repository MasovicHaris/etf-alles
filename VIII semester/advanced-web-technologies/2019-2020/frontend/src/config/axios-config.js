import axios from 'axios';

import store from '../core/store';
import cookiesHelper from '../core/helpers/cookies-helper';

import { BACKEND_API } from './constants';

const instance = axios.create({ baseURL: BACKEND_API });

// middlewares
instance.interceptors.response.use(
  response => {
    return response;
  },
  error => {
    if (error && error.response) {
      const { status } = error.response;
      if (status === 405) {
        cookiesHelper.removeCookie('token');
        window.location.href = '/login';
        return;
      }
      return Promise.reject(error.response);
    }
    return Promise.reject(error);
  }
);

instance.interceptors.request.use(
  config => {
    const state = store.getState();
    const token = state && state.auth && state.auth.token;
    if (token) {
      config.headers['authorization'] = `Bearer ${token}`;
    }
    return config;
  },
  error => {
    Promise.reject(error);
  }
);

export default instance;
