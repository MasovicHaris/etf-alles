import jwtDecode from 'jwt-decode';
import { call, put, takeLatest } from 'redux-saga/effects';

import cookiesHelper from '../../../core/helpers/cookies-helper';

import {
  handleLoginInProgress,
  handleLoginSuccess,
  handleSignupInProgress,
  handleUsernameCheckSuccess,
  handleGetUserSuccess,
  handleGetUserInProgress,
  handleUpdateProfileInProgress,
  handleUpdateProfileSuccess,
  handleUploadNewImageSuccess,
  handleUploadNewImageInProgress,
  handleDeleteProfileInProgress,
  handleDeleteProfileSuccess,
} from '../actions/auth-actions';
import { handleShowMessage } from '../../snackbar/actions/snackbar-actions';

import cookieHelper from '../../../core/helpers/cookies-helper';
import AuthApi from '../../../api/auth-api';
import UserApi from '../../../api/user-api';

import { SNACKBAR_SEVERITY_VARIANTS } from '../../snackbar/constants/snackbar-constants';
import { AUTH_ACTIONS } from '../constants/auth-constants';

function* requestLogin({ username, password, history }) {
  try {
    yield put(handleLoginInProgress(true));

    const { data } = yield call(AuthApi.requestLogin, { username, password });

    cookieHelper.setCookie('token', data.token);

    yield put(handleLoginSuccess(data));
    history.push('/');
  } catch (err) {
    yield put(handleShowMessage('AUTH.ERROR_LOGGING_IN', SNACKBAR_SEVERITY_VARIANTS.ERROR));
  } finally {
    yield put(handleLoginInProgress(false));
  }
}

function* requestSignup({ data, history }) {
  try {
    yield put(handleSignupInProgress(true));

    yield call(AuthApi.requestSignup, data);

    yield put(handleShowMessage('AUTH.SUCCESSFULLY_CREATED_ACCOUNT', SNACKBAR_SEVERITY_VARIANTS.SUCCESS));
    history.push('/login');
  } catch (err) {
    yield put(handleShowMessage('AUTH.ERROR_CREATING_ACCOUNT', SNACKBAR_SEVERITY_VARIANTS.ERROR));
  } finally {
    yield put(handleSignupInProgress(false));
  }
}

function* requestUsernameCheck({ data }) {
  try {
    const res = yield call(AuthApi.requestUsernameCheck, data);

    yield put(handleUsernameCheckSuccess(Boolean(res.data.invalid)));
  } catch (err) {
    yield put(handleShowMessage('AUTH.ERROR_CHECKING_USERNAME', SNACKBAR_SEVERITY_VARIANTS.ERROR));
    yield put(handleUsernameCheckSuccess(false));
  }
}

function* getUserProfile({ token }) {
  try {
    yield put(handleGetUserInProgress(true));
    const { username } = jwtDecode(token);
    const res = yield call(UserApi.requestUserProfile, username);

    delete res.data.password;
    delete res.data.createdAt;
    delete res.data.updatedAt;

    yield put(handleGetUserSuccess(res.data));
  } catch (err) {
    yield put(handleShowMessage('AUTH.ERROR_GETTING_USER_PROFILE', SNACKBAR_SEVERITY_VARIANTS.ERROR));
  } finally {
    yield put(handleGetUserInProgress(false));
  }
}

function* requestUpdateProfile({ data, history }) {
  try {
    yield put(handleUpdateProfileInProgress(true));

    const res = yield call(UserApi.requestUpdateProfile, data);
    const { token } = res.data;

    cookieHelper.setCookie('token', token);

    history.push('/');
    yield put(handleShowMessage('AUTH.SUCCESSFULLY_UPDATED_PROFILE', SNACKBAR_SEVERITY_VARIANTS.SUCCESS));
    yield put(handleUpdateProfileSuccess(res.data));
  } catch (err) {
    yield put(handleShowMessage('AUTH.ERROR_GETTING_USER_PROFILE', SNACKBAR_SEVERITY_VARIANTS.ERROR));
  } finally {
    yield put(handleUpdateProfileInProgress(false));
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

function* requestDeleteProfile({ history }) {
  try {
    yield put(handleDeleteProfileInProgress(true));

    cookiesHelper.removeCookie('token');
    yield call(UserApi.requestDeleteProfile);

    history.push('/');
    yield put(handleDeleteProfileSuccess());
    yield put(handleShowMessage('AUTH.SUCCESSFULLY_DELETED_PROFILE', SNACKBAR_SEVERITY_VARIANTS.SUCCESS));
  } catch (err) {
    yield put(handleShowMessage('AUTH.ERROR_DELETING_PROFILE', SNACKBAR_SEVERITY_VARIANTS.ERROR));
  } finally {
    yield put(handleDeleteProfileInProgress(false));
  }
}

export default function* saga() {
  yield takeLatest(AUTH_ACTIONS.HANDLE_LOGIN, requestLogin);
  yield takeLatest(AUTH_ACTIONS.HANDLE_SIGNUP, requestSignup);
  yield takeLatest(AUTH_ACTIONS.HANDLE_USERNAME_CHECK, requestUsernameCheck);
  yield takeLatest(AUTH_ACTIONS.HANDLE_GET_USER, getUserProfile);
  yield takeLatest(AUTH_ACTIONS.HANDLE_UPDATE_PROFILE, requestUpdateProfile);
  yield takeLatest(AUTH_ACTIONS.HANDLE_UPLOAD_NEW_IMAGE, requestUploadImage);
  yield takeLatest(AUTH_ACTIONS.HANDLE_DELETE_PROFILE, requestDeleteProfile);
}
