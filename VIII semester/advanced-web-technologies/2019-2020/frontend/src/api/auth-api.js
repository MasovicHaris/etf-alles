import axios from '../config/axios-config';

const requestLogin = data => {
  return axios({
    method: 'POST',
    url: '/api/auth/login',
    data,
  });
};

const requestSignup = data => {
  return axios({
    method: 'POST',
    url: '/api/auth/signup',
    data,
  });
};

const requestUsernameCheck = username => {
  return axios({
    method: 'GET',
    url: `/api/auth/check-username/${username}`,
  });
};

export default {
  requestLogin,
  requestSignup,
  requestUsernameCheck,
};
