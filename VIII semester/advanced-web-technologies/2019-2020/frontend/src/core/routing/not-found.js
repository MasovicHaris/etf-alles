import React from 'react';
import { useTranslation } from 'react-i18next';
import styled from 'styled-components';
import Typography from '@material-ui/core/Typography';

const Wrapper = styled.div`
  text-align: center;
  justify-content: center;
  display: flex;
  flex-direction: column;
  width: 100%;
`;

function NotFound() {
  const { t } = useTranslation();
  return (
    <Wrapper>
      <Typography variant="h3">{t('NOT_FOUND.404')}</Typography>
      <Typography variant="h6">{t('NOT_FOUND.MSG')}</Typography>
    </Wrapper>
  );
}

export default NotFound;
