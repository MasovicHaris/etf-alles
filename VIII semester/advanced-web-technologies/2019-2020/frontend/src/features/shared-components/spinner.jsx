import React from 'react';
import styled from 'styled-components';
import CircularProgress from '@material-ui/core/CircularProgress';

const Wrapper = styled.div`
  display: flex;
`;

const StyledSpinner = styled(CircularProgress)`
  margin: 0px auto;
  min-height: 15px;
`;

function Spinner(props) {
  return (
    <Wrapper>
      <StyledSpinner {...props} />
    </Wrapper>
  );
}

export default Spinner;
