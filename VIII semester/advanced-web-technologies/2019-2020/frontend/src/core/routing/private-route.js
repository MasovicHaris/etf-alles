import React from 'react';
import { Route, Redirect } from 'react-router-dom';
import PropTypes from 'prop-types';

function PrivateRoute({ component: Component, routes, userLoggedIn, ...rest }) {
  return userLoggedIn ? <Route {...rest} render={props => <Component {...props} routes={routes} />} /> : <Redirect to="/login" />;
}

PrivateRoute.propTypes = {
  component: PropTypes.func,
  routes: PropTypes.array,
};

PrivateRoute.defaultProps = {
  component: () => {},
  routes: [],
};

export default PrivateRoute;
