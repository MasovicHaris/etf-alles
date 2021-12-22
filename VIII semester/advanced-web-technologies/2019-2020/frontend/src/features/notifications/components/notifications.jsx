import React, { Fragment, useEffect } from 'react';
import { useSelector, useDispatch } from 'react-redux';
import { useHistory } from 'react-router-dom';
import { useTranslation } from 'react-i18next';
import styled from 'styled-components';
import MaterialContainer from '@material-ui/core/Container';
import { makeStyles } from '@material-ui/core/styles';
import Button from '@material-ui/core/Button';
import Card from '@material-ui/core/Card';
import CardContent from '@material-ui/core/CardContent';
import Typography from '@material-ui/core/Typography';
import CardActions from '@material-ui/core/CardActions';
import Grid from '@material-ui/core/Grid';
import { handleGetNotifications } from '../actions/notifications-actions';
import ApplicationHeader from '../../shared-components/header';

const Container = styled(MaterialContainer)`
  background-color: #fff;
`;

const useStyles = makeStyles({
  card: {
    background: '#dbe5f0',
  },
});

function Notifications() {
  const classes = useStyles();
  const { t } = useTranslation();
  const dispatch = useDispatch();
  const history = useHistory();

  const notifications = useSelector(state => state.notifications.notifications);

  useEffect(() => {
    dispatch(handleGetNotifications());
  }, [dispatch]);

  const notificationItems = notifications.map(notification => (
    <Grid item xs={12} sm={6} lg={3} key={notification.notificationId}>
      <Card className={classes.card}>
        <CardContent>
          <Typography component="h5" variant="h5">
            {notification.message}
          </Typography>
        </CardContent>
        <CardActions>
          <Button size="small" color="primary">
            {t('EVENTS.CATEGORIES_GET_EVENTS_BUTTON')}
          </Button>
        </CardActions>
      </Card>
    </Grid>
  ));

  return (
    <Fragment>
      <ApplicationHeader />
      <Container component="main">
        <h1>{t('EVENTS.CATEGORIES_TITLE')}</h1>
        <h2>{t('EVENTS.CATEGORIES_SUBTITLE')}</h2>
        <Grid container spacing={3}>
          {notificationItems}
        </Grid>
      </Container>
    </Fragment>
  );
}

export default Notifications;
