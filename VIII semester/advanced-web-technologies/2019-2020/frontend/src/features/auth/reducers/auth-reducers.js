import cacheHelper from '../../../core/helpers/cookies-helper';

import { AUTH_ACTIONS } from '../constants/auth-constants';

const getAuthInitialState = () => {
  const token = cacheHelper.getCookie('token');

  return {
    userLoggedIn: Boolean(token),
    loginInProgress: false,
    signupInProgress: false,
    token: token || null,
    user: {
      id: null,
      name: '',
      surname: '',
      username: '',
    },
    usernameInvalid: false,
    profile: {
      id: 0,
      username: '',
      name: '',
      surname: '',
      picture: '',
      description: '',
    },
    uploadedImageUrl: '',
    updateUserProfileInProgress: false,
    uploadImageInProgress: false,
    getProfileInProgress: false,
    deleteUserProfileInProgress: false,
  };
};

export const auth = (state = getAuthInitialState(), action) => {
  switch (action.type) {
    case AUTH_ACTIONS.HANDLE_LOGIN_IN_PROGRESS:
      return { ...state, loginInProgress: action.status };
    case AUTH_ACTIONS.HANDLE_LOGIN_SUCCESS:
      const { user, token } = action.data;
      return { ...state, user, token, userLoggedIn: true };
    case AUTH_ACTIONS.HANDLE_SIGNUP_IN_PROGRESS:
      return { ...state, signupInProgress: action.status };
    case AUTH_ACTIONS.HANDLE_USERNAME_CHECK_SUCCESS:
      return { ...state, usernameInvalid: action.data };
    case AUTH_ACTIONS.HANDLE_GET_USER_SUCCESS:
      return { ...state, profile: action.data };
    case AUTH_ACTIONS.HANDLE_GET_USER_IN_PROGRESS:
      return { ...state, getProfileInProgress: action.status };
    case AUTH_ACTIONS.HANDLE_UPDATE_PROFILE_IN_PROGRESS:
      return { ...state, updateUserProfileInProgress: action.status };
    case AUTH_ACTIONS.HANDLE_UPDATE_PROFILE_SUCCESS:
      return { ...state, token: action.data.token, uploadedImageUrl: '' };
    case AUTH_ACTIONS.HANDLE_UPLOAD_NEW_IMAGE_IN_PROGRESS:
      return { ...state, uploadImageInProgress: action.status };
    case AUTH_ACTIONS.HANDLE_UPLOAD_NEW_IMAGE_SUCCESS:
      return { ...state, uploadedImageUrl: action.data };
    case AUTH_ACTIONS.HANDLE_DELETE_PROFILE_IN_PROGRESS:
      return { ...state, deleteUserProfileInProgress: action.status };
    case AUTH_ACTIONS.HANDLE_DELETE_PROFILE_SUCCESS:
    case AUTH_ACTIONS.HANDLE_LOGOUT:
      return getAuthInitialState();
    default:
      return state;
  }
};
