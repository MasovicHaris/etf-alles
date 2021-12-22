import React from 'react';
import { useSelector } from 'react-redux';
import { Route, Switch } from 'react-router-dom';
import { ThemeProvider } from 'styled-components';
import { createMuiTheme } from '@material-ui/core/styles';
import { StylesProvider } from '@material-ui/core/styles';
import MaterialThemeProvider from '@material-ui/styles/ThemeProvider';

import SnackBar from '../features/snackbar/components/snackbar';
import PrivateRoute from './routing/private-route';

import routes from './routing/route-config';
import GlobalStyle from './global-style';
import './localization';

const theme = {
  primaryColor: '#ffffff',
  buttonColor: '#2c3e50',
};

const materialTheme = createMuiTheme({
  overrides: {
    MuiOutlinedInput: {
      root: {
        backgroundColor: theme.primaryColor,
        borderColor: theme.buttonColor,
      },
    },
  },
});

function App() {
  const userLoggedIn = useSelector(state => state.auth.userLoggedIn);

  const renderRoutes = () => {
    return routes.map((route, index) => {
      return route.requireAuth ? <PrivateRoute key={index} {...route} userLoggedIn={userLoggedIn} /> : <Route key={index} {...route} />;
    });
  };

  return (
    <StylesProvider injectFirst>
      <GlobalStyle />
      <MaterialThemeProvider theme={materialTheme}>
        <ThemeProvider theme={theme}>
          <Switch>{renderRoutes()}</Switch>
          <SnackBar />
        </ThemeProvider>
      </MaterialThemeProvider>
    </StylesProvider>
  );
}

export default App;
