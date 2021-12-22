import { SNACKBAR_ACTIONS } from '../constants/snackbar-constants';

const snackbarInitialState = {
  messageQueue: [],
  messageShown: false,
  message: {},
};

export const snackbar = (state = snackbarInitialState, action) => {
  switch (action.type) {
    case SNACKBAR_ACTIONS.HANDLE_SHOW_MESSAGE:
      const newQueue = [...state.messageQueue];
      newQueue.push({
        message: action.message,
        severity: action.severity,
        key: new Date().getTime(),
      });
      if (state.messageShown) {
        return { ...state, messageShown: false, messageQueue: newQueue };
      }
      if (newQueue.length > 0) {
        const [message, ...tail] = newQueue;
        return { ...state, messageShown: true, message, messageQueue: tail };
      }
      return state;
    case SNACKBAR_ACTIONS.HANDLE_CLOSE_MESSAGE:
      return { ...state, messageShown: false, message: {} };
    case SNACKBAR_ACTIONS.HANDLE_EXITED:
      if (state.messageQueue.length > 0) {
        const [message, ...tail] = state.messageQueue;
        return { ...state, messageShown: true, message, messageQueue: tail };
      }
      return state;
    default:
      return state;
  }
};
