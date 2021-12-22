import React, { Fragment, useEffect, createRef } from 'react';
import { useSelector, useDispatch } from 'react-redux';
import { useHistory } from 'react-router-dom';
import { useTranslation } from 'react-i18next';
import { makeStyles } from '@material-ui/core/styles';
import { useFormik } from 'formik';
import CssBaseline from '@material-ui/core/CssBaseline';
import TextField from '@material-ui/core/TextField';
import BackupIcon from '@material-ui/icons/Backup';
import CloseIcon from '@material-ui/icons/Close';
import Grid from '@material-ui/core/Grid';
import MaterialContainer from '@material-ui/core/Container';
import styled from 'styled-components';
import * as Yup from 'yup';

import { handleUsernameCheck, handleGetUser, handleUpdateProfile, handleUploadNewImage, handleDeleteProfile } from '../actions/auth-actions';

import AlertDialog from '../../shared-components/alert-dialog';
import Button from '../../shared-components/button';
import ApplicationHeader from '../../shared-components/header';
import Spinner from '../../shared-components/spinner';
import { useState } from 'react';

const Container = styled(MaterialContainer)`
  background-color: #fff;
`;

const useStyles = makeStyles(theme => ({
  paper: {
    display: 'flex',
    flexDirection: 'column',
    alignItems: 'center',
  },
  form: {
    width: '100%',
    marginTop: theme.spacing(3),
  },
  submit: {
    marginTop: '10px',
    marginBottom: '30px',
    width: '150px',
  },
  imageOuterDiv: {
    width: '100%',
    marginTop: '30px',
    backgroundColor: '#fff',
  },
  imageInnerDiv: {
    padding: '10px',
    display: 'flex',
    justifyContent: 'center',
  },
  image: {
    borderRadius: '50%',
    height: '250px',
    width: '250px',
    objectFit: 'cover',
    border: '1px solid black',
  },
  spinner: {
    marginTop: '40px',
    display: 'flex',
    justifyContent: 'center',
  },
  uploadIconOuter: {
    position: 'relative',
  },
  uploadIcon: {
    position: 'absolute',
    right: '100px',
    top: '100px',
    borderRadius: '50%',
    padding: '5px',
    height: '40px',
    width: '40px',
    '&:hover': {
      background: '#2c3e50',
      cursor: 'pointer',
    },
  },
  spinnerIcon: {
    position: 'absolute',
    right: '100px',
    top: '100px',
    padding: '5px',
    height: '40px',
    width: '40px',
  },
  inputImage: {
    display: 'none',
  },
}));

const RedButton = styled(Button)`
  background-color: red;
  margin: 10px 15px 30px 15px;
  width: 150px;
`;

function MyAccountPage() {
  const { t } = useTranslation();
  const classes = useStyles();
  const dispatch = useDispatch();
  const history = useHistory();
  const refImageInput = createRef();

  const usernameInvalid = useSelector(state => state.auth.usernameInvalid);
  const token = useSelector(state => state.auth.token);
  const userProfile = useSelector(state => state.auth.profile);
  const getProfileInProgress = useSelector(state => state.auth.getProfileInProgress);
  const url = useSelector(state => state.auth.uploadedImageUrl);

  const uploadImageInProgress = useSelector(state => state.auth.uploadImageInProgress);
  const signupInProgress = useSelector(state => state.auth.signupInProgress);
  const deleteUserProfileInProgress = useSelector(state => state.auth.deleteUserProfileInProgress);

  const disabled = deleteUserProfileInProgress || signupInProgress || uploadImageInProgress;

  const [uploadedImageUrl, setUploadedImageUrl] = useState(url);
  const [isOpen, setIsOpen] = useState(false);

  const validationSchema = Yup.object().shape({
    name: Yup.string().required(t('AUTH.FIRST_NAME_IS_REQUIRED')),
    surname: Yup.string().required(t('AUTH.LAST_NAME_IS_REQUIRED')),
    username: Yup.string()
      .required(t('AUTH.USERNAME_IS_REQUIRED'))
      .min(4, t('AUTH.USERNAME_MIN_4')),
  });

  const { values, errors, touched, handleChange, handleBlur, handleSubmit, setValues } = useFormik({
    enableReinitialize: true,
    initialValues: {
      name: userProfile.name || '',
      surname: userProfile.surname || '',
      username: userProfile.username || '',
      password: '',
      picture: userProfile.picture || '',
      description: userProfile.description || '',
    },
    validationSchema,
    onSubmit: values => {
      if (uploadedImageUrl) {
        values.picture = uploadedImageUrl;
      }

      if (!usernameError) {
        dispatch(handleUpdateProfile(values, history));
      }
    },
  });

  const onUsernameInputChange = e => {
    const text = e.target.value;

    if (text.length >= 4 && text !== userProfile.username) {
      dispatch(handleUsernameCheck(text));
    }

    return handleChange(e);
  };

  const usernameError = (touched.username && errors.username) || (usernameInvalid ? t('AUTH.USERNAME_EXISTS_ALREADY') : '');

  const fields = [
    { value: values.name, label: 'AUTH.FIRST_NAME', error: touched.name && errors.name, name: 'name', grid: true },
    { value: values.surname, label: 'AUTH.LAST_NAME', error: touched.surname && errors.surname, name: 'surname', grid: true },
    { value: values.username, label: 'AUTH.USERNAME', error: usernameError, name: 'username', onChange: onUsernameInputChange },
    { value: values.password, label: 'AUTH.NEW_PASSWORD', error: touched.password && errors.password, name: 'password', password: true },
    { value: values.description, label: 'AUTH.DESCRIPTION', name: 'description', textArea: true },
  ];

  useEffect(() => {
    dispatch(handleGetUser(token));
  }, [dispatch, token]);

  useEffect(() => {
    setUploadedImageUrl(url);
  }, [url]);

  const onUploadNewImage = e => {
    e.preventDefault();
    const reader = new FileReader();
    const file = e.target.files[0];
    if (reader && file) {
      reader.onloadend = () => {
        dispatch(handleUploadNewImage(file));
      };
      reader.readAsDataURL(file);
    }
  };

  const onCloseUploadedImage = () => {
    setValues({ ...values, picture: userProfile.picture });
    setUploadedImageUrl('');
  };

  const onDeleteClicked = () => {
    setIsOpen(true);
  };

  const deleteProfile = () => dispatch(handleDeleteProfile(history));

  return (
    <Fragment>
      <AlertDialog isOpen={isOpen} setIsOpen={setIsOpen} title={t('AUTH.CONFIRM_DELETE_PROFILE')} description={t('AUTH.CONFIRM_DELETE_PROFILE_MSG')} onConfirmClick={deleteProfile} />
      <ApplicationHeader isMyAccount />
      {getProfileInProgress ? (
        <div className={classes.spinner}>
          <Spinner size="50px" />
        </div>
      ) : (
        <Container component="main" maxWidth="xs">
          <div className={classes.imageOuterDiv}>
            <div className={classes.imageInnerDiv}>
              <img className={classes.image} src={uploadedImageUrl || values.picture} alt="ProfileImage" />{' '}
              <div className={classes.uploadIconOuter}>
                {uploadImageInProgress ? (
                  <div className={classes.spinnerIcon}>
                    <Spinner size="30px" />
                  </div>
                ) : uploadedImageUrl === '' ? (
                  <Fragment>
                    <input type="file" ref={refImageInput} className={classes.inputImage} onChange={onUploadNewImage} />
                    <BackupIcon className={classes.uploadIcon} fontSize="large" onClick={() => refImageInput.current.click()} />
                  </Fragment>
                ) : (
                  <CloseIcon className={classes.uploadIcon} fontSize="large" onClick={onCloseUploadedImage} />
                )}
              </div>
            </div>
          </div>
          <CssBaseline />
          <div className={classes.paper}>
            <form className={classes.form} onSubmit={handleSubmit} noValidate>
              <Grid container spacing={2}>
                {fields.map(field => (
                  <Grid key={field.name} item xs={12} sm={field.grid ? 6 : null}>
                    <TextField
                      value={field.value}
                      onChange={field.onChange ? field.onChange : handleChange}
                      onBlur={handleBlur}
                      label={t(field.label)}
                      error={Boolean(field.error)}
                      helperText={field.error}
                      variant="outlined"
                      name={field.name}
                      fullWidth
                      type={field.password ? 'password' : 'text'}
                      multiline={field.textArea || false}
                    />
                  </Grid>
                ))}
              </Grid>
              <Button type="submit" fullWidth variant="contained" color="primary" loadingInProgress={signupInProgress} className={classes.submit} disabled={disabled}>
                {t('AUTH.UPDATE_PROFILE')}
              </Button>
              <RedButton fullWidth type="button" variant="contained" color="primary" loadingInProgress={deleteUserProfileInProgress} disabled={disabled} onClick={onDeleteClicked}>
                {t('AUTH.DELETE_PROFILE')}
              </RedButton>
            </form>
          </div>
        </Container>
      )}
    </Fragment>
  );
}

export default MyAccountPage;
