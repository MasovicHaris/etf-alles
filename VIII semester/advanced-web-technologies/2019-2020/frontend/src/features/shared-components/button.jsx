import React from 'react';
import PropTypes from 'prop-types';
import styled from 'styled-components';
import MaterialButton from '@material-ui/core/Button';
import StyledSpinner from '../shared-components/spinner';

const Wrapper = styled(MaterialButton)`
  opacity: ${props => props.opacity};
  padding: ${props => props.padding};
  margin-right: ${props => props.mright};
  background-color: ${props => props.theme.buttonColor};

  &:hover {
    background-color: ${props => props.theme.buttonColor};
    opacity: 0.7;
  }
`;

const Spinner = styled(StyledSpinner)`
  color: ${props => props.theme.primaryColor};
`;

function Button({ children, spinnerSize, loadingInProgress, ...rest }) {
  return <Wrapper {...rest}>{loadingInProgress ? <Spinner size={`${spinnerSize}px`} /> : children}</Wrapper>;
}

Button.propTypes = {
  children: PropTypes.oneOfType([PropTypes.element.isRequired, PropTypes.string.isRequired]),
  type: PropTypes.string,
  disabled: PropTypes.bool,
  loadingInProgress: PropTypes.bool,
  onClick: PropTypes.func,
  spinnerSize: PropTypes.number,
};

Button.defaultProps = {
  type: '',
  disabled: false,
  loadingInProgress: false,
  onClick: () => {},
  spinnerSize: 20,
};

export default Button;
