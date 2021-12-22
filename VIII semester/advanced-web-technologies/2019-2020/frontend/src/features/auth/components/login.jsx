import React, { Fragment } from 'react';
import { useSelector, useDispatch } from 'react-redux';
import { useTranslation } from 'react-i18next';
import { makeStyles } from '@material-ui/core/styles';
import { useFormik } from 'formik';
import { Redirect, useHistory } from 'react-router-dom';
import CssBaseline from '@material-ui/core/CssBaseline';
import TextField from '@material-ui/core/TextField';
import Link from '@material-ui/core/Link';
import Grid from '@material-ui/core/Grid';
import MaterialContainer from '@material-ui/core/Container';
import styled from 'styled-components';
import * as Yup from 'yup';

import { handleLogin } from '../actions/auth-actions';

import ApplicationHeader from '../../shared-components/header';
import Button from '../../shared-components/button';

import signUpLogo from '../../../config/images/sign-up-white.png';

const Container = styled(MaterialContainer)`
  background-color: #fff;
`;

const Image = styled.img`
  padding: 10px;
`;

const Header = styled.h1`
  text-align: center;
`;

const useStyles = makeStyles(theme => ({
  paper: {
    marginTop: theme.spacing(8),
    display: 'flex',
    flexDirection: 'column',
    alignItems: 'center',
  },
  form: {
    width: '100%',
    marginTop: theme.spacing(3),
  },
  submit: {
    margin: theme.spacing(3, 0, 2),
  },
}));

function Login() {
  const { t } = useTranslation();
  const dispatch = useDispatch();
  const classes = useStyles();
  const history = useHistory();

  const userLoggedIn = useSelector(state => state.auth.userLoggedIn);
  const loginInProgress = useSelector(state => state.auth.loginInProgress);

  const validationSchema = Yup.object().shape({
    username: Yup.string().required(t('AUTH.USERNAME_IS_REQUIRED')),
    password: Yup.string().required(t('AUTH.PASSWORD_IS_REQUIRED')),
  });

  const { values, errors, touched, handleChange, handleBlur, handleSubmit } = useFormik({
    initialValues: {
      username: '',
      password: '',
    },
    validationSchema,
    onSubmit: ({ username, password }) => {
      dispatch(handleLogin(username, password, history));
    },
  });

  const usernameError = touched.username && errors.username;
  const passwordError = touched.password && errors.password;

  if (userLoggedIn) {
    return <Redirect to="/" />;
  }

  return (
    <Fragment>
      <ApplicationHeader isAuthPage />
      <Container component="main" maxWidth="xs">
        <CssBaseline />
        <div className={classes.paper}>
          <Image src={signUpLogo} alt="logo" />
          <Header>{t('AUTH.LOGIN_TEXT')}</Header>
          <form className={classes.form} onSubmit={handleSubmit} noValidate>
            <Grid container spacing={2}>
              <Grid item xs={12}>
                <TextField
                  value={values.username}
                  onChange={handleChange}
                  onBlur={handleBlur}
                  label={t('AUTH.USERNAME')}
                  error={Boolean(usernameError)}
                  helperText={usernameError}
                  variant="outlined"
                  name="username"
                  fullWidth
                />
              </Grid>
              <Grid item xs={12}>
                <TextField
                  value={values.password}
                  onChange={handleChange}
                  onBlur={handleBlur}
                  error={Boolean(passwordError)}
                  helperText={passwordError}
                  name="password"
                  label={t('AUTH.PASSWORD')}
                  type="password"
                  variant="outlined"
                  fullWidth
                />
              </Grid>
            </Grid>
            <Button type="submit" fullWidth variant="contained" color="primary" loadingInProgress={loginInProgress} className={classes.submit}>
              {t('AUTH.SIGN_IN')}
            </Button>
            <Grid container justify="flex-end">
              <Grid item>
                <Link href="/signup" variant="body2">
                  {t('AUTH.DONT_HAVE_ACCOUNT')}
                </Link>
              </Grid>
            </Grid>
          </form>
        </div>
      </Container>
    </Fragment>
  );
}

export default Login;
