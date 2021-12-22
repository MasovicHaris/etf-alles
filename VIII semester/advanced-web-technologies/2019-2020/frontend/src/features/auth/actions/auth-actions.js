import cookieHelper from '../../../core/helpers/cookies-helper';

import { AUTH_ACTIONS } from '../constants/auth-constants';

export const handleLogin = (username, password, history) => ({
  type: AUTH_ACTIONS.HANDLE_LOGIN,
  username,
  password,
  history,
});

export const handleLoginInProgress = status => ({
  type: AUTH_ACTIONS.HANDLE_LOGIN_IN_PROGRESS,
  status,
});

export const handleLoginSuccess = data => ({
  type: AUTH_ACTIONS.HANDLE_LOGIN_SUCCESS,
  data,
});

export const handleSignup = (data, history) => ({
  type: AUTH_ACTIONS.HANDLE_SIGNUP,
  data,
  history,
});

export const handleSignupInProgress = status => ({
  type: AUTH_ACTIONS.HANDLE_SIGNUP_IN_PROGRESS,
  status,
});

export const handleLogout = () => {
  cookieHelper.removeCookie('token');

  return { type: AUTH_ACTIONS.HANDLE_LOGOUT };
};

export const handleUsernameCheck = data => ({
  type: AUTH_ACTIONS.HANDLE_USERNAME_CHECK,
  data,
});

export const handleUsernameCheckSuccess = data => ({
  type: AUTH_ACTIONS.HANDLE_USERNAME_CHECK_SUCCESS,
  data,
});

export const handleGetUser = token => ({
  type: AUTH_ACTIONS.HANDLE_GET_USER,
  token,
});

export const handleGetUserInProgress = status => ({
  type: AUTH_ACTIONS.HANDLE_GET_USER_IN_PROGRESS,
  status,
});

export const handleGetUserSuccess = data => ({
  type: AUTH_ACTIONS.HANDLE_GET_USER_SUCCESS,
  data,
});

export const handleUpdateProfile = (data, history) => ({
  type: AUTH_ACTIONS.HANDLE_UPDATE_PROFILE,
  data,
  history,
});

export const handleUpdateProfileInProgress = status => ({
  type: AUTH_ACTIONS.HANDLE_UPDATE_PROFILE_IN_PROGRESS,
  status,
});

export const handleUpdateProfileSuccess = data => ({
  type: AUTH_ACTIONS.HANDLE_UPDATE_PROFILE_SUCCESS,
  data,
});

export const handleUploadNewImage = file => ({
  type: AUTH_ACTIONS.HANDLE_UPLOAD_NEW_IMAGE,
  file,
});

export const handleUploadNewImageInProgress = status => ({
  type: AUTH_ACTIONS.HANDLE_UPLOAD_NEW_IMAGE_IN_PROGRESS,
  status,
});

export const handleUploadNewImageSuccess = data => ({
  type: AUTH_ACTIONS.HANDLE_UPLOAD_NEW_IMAGE_SUCCESS,
  data,
});

export const handleDeleteProfile = history => ({
  type: AUTH_ACTIONS.HANDLE_DELETE_PROFILE,
  history,
});

export const handleDeleteProfileInProgress = status => ({
  type: AUTH_ACTIONS.HANDLE_DELETE_PROFILE_IN_PROGRESS,
  status,
});

export const handleDeleteProfileSuccess = data => ({
  type: AUTH_ACTIONS.HANDLE_DELETE_PROFILE_SUCCESS,
  data,
});
