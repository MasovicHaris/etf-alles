import { SNACKBAR_ACTIONS } from '../constants/snackbar-constants';

export const handleShowMessage = (message, severity) => ({
  type: SNACKBAR_ACTIONS.HANDLE_SHOW_MESSAGE,
  message,
  severity,
});

export const handleCloseMessage = () => ({
  type: SNACKBAR_ACTIONS.HANDLE_CLOSE_MESSAGE,
});

export const handleSnackbarExited = () => ({
  type: SNACKBAR_ACTIONS.HANDLE_EXITED,
});
