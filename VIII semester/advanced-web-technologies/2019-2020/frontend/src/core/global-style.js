import React from 'react';
import { createGlobalStyle } from 'styled-components';

const Wrapper = createGlobalStyle`
html,
body {
  font: 400 0.875rem "Roboto", "Helvetica", "Arial", sans-serif;
  -webkit-font-smoothing: antialiased;
  -moz-osx-font-smoothing: grayscale;
  height: 100%;
  margin: 0;
  display: flex;
  flex-direction: column;
}

html {
  box-sizing: border-box;
}

*,
*:before,
*:after {
  box-sizing: inherit;
}

#root {
  background-color: #fff;
  display: flex;
  flex-direction: column;
  flex-grow: 1;

  & > div {
    display: flex;
    flex-grow: 1;
  }
}
`;

function GlobalStyle(props) {
  return <Wrapper {...props} />;
}

export default GlobalStyle;
