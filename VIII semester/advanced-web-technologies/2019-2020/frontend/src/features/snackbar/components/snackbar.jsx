import React from 'react';
import { useDispatch, useSelector } from 'react-redux';
import { useTranslation } from 'react-i18next';
import MaterialSnackbar from '@material-ui/core/Snackbar';
import MuiAlert from '@material-ui/lab/Alert';

import { handleCloseMessage, handleSnackbarExited } from '../actions/snackbar-actions';

function Alert(props) {
  return <MuiAlert elevation={6} variant="filled" {...props} />;
}

function Snackbar() {
  const { t } = useTranslation();
  const dispatch = useDispatch();

  const open = useSelector(state => state.snackbar.messageShown);
  const messageInfo = useSelector(state => state.snackbar.message);

  const handleClose = () => {
    dispatch(handleCloseMessage());
  };

  const handleExited = () => {
    dispatch(handleSnackbarExited());
  };

  return (
    <MaterialSnackbar
      key={messageInfo ? messageInfo.key : undefined}
      anchorOrigin={{
        vertical: 'bottom',
        horizontal: 'right',
      }}
      open={open}
      autoHideDuration={5000}
      onClose={handleClose}
      onExited={handleExited}
    >
      <Alert onClose={handleClose} severity={messageInfo.severity}>
        {t(messageInfo.message)}
      </Alert>
    </MaterialSnackbar>
  );
}

export default Snackbar;
