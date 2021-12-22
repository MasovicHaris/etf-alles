import React, { Fragment, useEffect } from 'react';
import { useSelector, useDispatch } from 'react-redux';
import { useParams, useHistory } from 'react-router-dom';
import { useTranslation } from 'react-i18next';
import styled from 'styled-components';
import MaterialContainer from '@material-ui/core/Container';
import { makeStyles } from '@material-ui/core/styles';
import Grid from '@material-ui/core/Grid';
import Button from '@material-ui/core/Button';
import Card from '@material-ui/core/Card';
import CardActions from '@material-ui/core/CardActions';
import CardMedia from '@material-ui/core/CardMedia';
import CardContent from '@material-ui/core/CardContent';
import Typography from '@material-ui/core/Typography';
import AccessTimeIcon from '@material-ui/icons/AccessTime';
import LocationOnIcon from '@material-ui/icons/LocationOn';
import EventIcon from '@material-ui/icons/Event';
import CheckCircleOutlineIcon from '@material-ui/icons/CheckCircleOutline';
import StarBorderIcon from '@material-ui/icons/StarBorder';
import IconButton from '@material-ui/core/IconButton';
import StarIcon from '@material-ui/icons/Star';
import CheckCircleIcon from '@material-ui/icons/CheckCircle';
import AccountCircleIcon from '@material-ui/icons/AccountCircle';
import Link from '@material-ui/core/Link';
import Spinner from '../../shared-components/spinner';

import { handleInterestedClicked, handleGoingToClicked, handleGetEvent, handleGetEventLoggedUser } from '../actions/events-page-actions';

import ApplicationHeader from '../../shared-components/header';

import { handleGetUser } from '../../auth/actions/auth-actions';

import { handleGetCreator } from '../actions/events-page-actions';

import LeafletMap from './LeafletMap';

const Container = styled(MaterialContainer)`
  background-color: #fff;
`;

const useStyles = makeStyles(theme => ({
  card: {
    background: '#fff',
    minHeight: '50vh',
    minWidth: '50%',
    maxWidth: '800px',
    display: 'flex',
    flexDirection: 'column',
    justifyContent: 'space-between',
    marginTop: '50px',
    marginBottom: '50px',
  },
  card_actions__secondary: {
    height: 50,
  },
  card_actions__button: {
    color: 'rgba(0, 0, 0, 0.54)',
    textTransform: 'none',
  },
  title: {
    fontSize: 14,
  },
  icon: {
    padding: '2px',
  },
  icon_label: {
    paddingRight: '10px',
  },
  icon_label_bold: {
    paddingRight: '10px',
    textDecoration: 'underline',
    fontWeight: 'bold',
  },
  grid: {
    minHeight: '90vh',
  },
  creator: {},
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
    height: '100%',
    width: '100%',
    maxHeight: '600px',
    maxWidth: '800px',
    minHeight: '150px',
    minWidth: '150px',
    objectFit: 'cover',
  },
  description: {
    maxWidth: '800px',
    paddingBottom: '20px',
  },
  noPadding: {
    padding: '0px',
  },
  noPaddingLeft: {
    paddingLeft: '0px',
  },
  media: {
    height: '400px',
  },
  numberOf: {
    fontSize: '16px',
  },
  spinner: {
    marginTop: '40px',
    display: 'flex',
    justifyContent: 'center',
  },
}));

function useToggle(initialValue = true) {
  const [value, setValue] = React.useState(initialValue);
  const toggle = React.useCallback(() => {
    setValue(v => !v);
  }, []);
  return [value, toggle];
}

function EventsInfoPage() {
  const classes = useStyles();
  const { t } = useTranslation();
  const dispatch = useDispatch();
  const userLoggedIn = useSelector(state => state.auth.userLoggedIn);
  const eventInfo = useSelector(state => state.events.eventInfo);
  const getEventInProgres = useSelector(state => state.events.getEventInProgres);
  const creatorId = useSelector(state => (eventInfo != null ? (userLoggedIn ? eventInfo.event && eventInfo.event.creator.id : eventInfo.creator.id) : null));
  const params = useParams();
  const eventId = params.idEvent;

  const token = useSelector(state => state.auth.token);
  const creatorOfEvent = useSelector(state => state.events.creatorOfEvent);
  const history = useHistory();

  const [isMapVisible, toggleIsMapVisible] = useToggle();

  useEffect(() => {
    if (userLoggedIn) dispatch(handleGetEventLoggedUser(eventId));
    else dispatch(handleGetEvent(eventId));
  }, [dispatch, eventId, userLoggedIn]);

  useEffect(() => {
    if (userLoggedIn) {
      dispatch(handleGetUser(token));
      dispatch(handleGetCreator(creatorId));
    }
  }, [dispatch, token, creatorId, userLoggedIn]);

  const getDate = date => {
    const d = new Date(date);
    const days = ['Sunday', 'Monday', 'Tuesday', 'Wednesday', 'Thursday', 'Friday', 'Saturday'];
    const month = 1 + d.getMonth();
    return days[d.getDay()] + ', ' + d.getDate() + '.' + month + '.' + d.getFullYear() + '.';
  };

  const getEndDate = event => {
    if (!event || event.date === event.endDate || !event.endDate) return '';
    const d = new Date(event.endDate);
    const days = ['Sunday', 'Monday', 'Tuesday', 'Wednesday', 'Thursday', 'Friday', 'Saturday'];
    const month = 1 + d.getMonth();
    return '-' + days[d.getDay()] + ', ' + d.getDate() + '.' + month + '.' + d.getFullYear() + '.';
  };

  const getLocation = () => {
    if (!eventInfo) return;
    return userLoggedIn ? eventInfo.event && eventInfo.event.address : eventInfo.address;
  };

  const getTime = () => {
    if (!eventInfo || !eventInfo.event || (eventInfo.event.beginTime === '' && eventInfo.event.endTime === '')) return t('EVENTS.TIME_NOT_AVAILABLE');
    let time = '';
    if (eventInfo && eventInfo.event.beginTime) time += eventInfo.event.beginTime;
    if (eventInfo && eventInfo.event.endTime) time += '-' + eventInfo.event.endTime;
    return time;
  };

  const interestedClicked = event => {
    dispatch(handleInterestedClicked(event));
  };

  const goingToClicked = event => {
    dispatch(handleGoingToClicked(event));
  };

  const openProfile = id => {
    history.push(`/profile/` + id);
  };

  function InterestedIcon(event) {
    if (event.marked && !event.going) {
      return <StarIcon />;
    }
    return <StarBorderIcon />;
  }

  function GoingIcon(event) {
    if (event.marked && event.going) {
      return <CheckCircleIcon />;
    }
    return <CheckCircleOutlineIcon />;
  }

  function Creator(eventInfo) {
    if (userLoggedIn) {
      return (
        <Typography color="textSecondary" className={classes.creator}>
          <IconButton aria-label="creator" className={classes.icon}>
            <AccountCircleIcon></AccountCircleIcon>
          </IconButton>
          {t('EVENTS.CREATOR')}
          <Link href="" onClick={() => openProfile(creatorId)}>
            {creatorOfEvent ? creatorOfEvent.username : creatorId}
          </Link>
        </Typography>
      );
    }
  }

  function ActionsForLoggedUsers(event) {
    if (userLoggedIn) {
      return (
        <Grid container>
          <IconButton aria-label="event-interested" component="span" className={classes.noPaddingLeft} title={t('EVENTS.EVENTS_INTERESTED_BUTTON')} onClick={() => interestedClicked(event)}>
            {InterestedIcon(event)} <label className={classes.numberOf}>{eventInfo.event.numberOfInterested}</label>
          </IconButton>
          <IconButton aria-label="event-going" component="span" title={t('EVENTS.EVENTS_GOING_BUTTON')} onClick={() => goingToClicked(event)}>
            {GoingIcon(event)} <label className={classes.numberOf}>{eventInfo.event.numberOfGoing}</label>
          </IconButton>
        </Grid>
      );
    }
  }

  return (
    <Fragment>
      <ApplicationHeader />
      {getEventInProgres ? (
        <div className={classes.spinner}>
          <Spinner size="50px" />
        </div>
      ) : (
        <Container component="main">
          <Grid
            container
            spacing={0}
            direction="column"
            alignItems="center"
            justify="center"
            key={eventInfo ? (userLoggedIn ? eventInfo.event && eventInfo.event.id : eventInfo.id) : null}
            className={classes.grid}
          >
            <Card className={classes.card}>
              {userLoggedIn
                ? eventInfo && eventInfo.event && eventInfo.event.imageUrl && <CardMedia className={classes.media} image={eventInfo.event.imageUrl} title="EventImage" />
                : eventInfo && <CardMedia className={classes.media} image={eventInfo.imageUrl} title="EventImage" />}
              <CardContent>
                <Grid container spacing={3}>
                  <Grid item xs={7}>
                    <Typography className={(classes.title, classes.icon_label)} color="textSecondary" gutterBottom>
                      <EventIcon />
                      {getDate(eventInfo ? (userLoggedIn ? eventInfo.event && eventInfo.event.date : eventInfo.date) : null)}
                      {getEndDate(eventInfo ? (userLoggedIn ? eventInfo.event : eventInfo) : null)}
                    </Typography>
                    <Typography className={(classes.title, classes.icon_label)} color="textSecondary" gutterBottom>
                      <AccessTimeIcon />
                      {getTime()}
                    </Typography>
                    <Typography className={(classes.title, classes.icon_label)} color="textSecondary" gutterBottom>
                      <LocationOnIcon />
                      {getLocation()}
                    </Typography>
                  </Grid>
                  <Grid item xs={5}>
                    {eventInfo ? Creator(eventInfo) : ''}
                    <br /> <br />
                    {eventInfo ? ActionsForLoggedUsers(eventInfo) : ''}
                  </Grid>
                </Grid>
                <Typography variant="h5" component="h2">
                  {eventInfo ? (userLoggedIn ? eventInfo.event.title : eventInfo.title) : null}
                </Typography>

                <Typography component="p" className={classes.description}>
                  {eventInfo ? (userLoggedIn ? eventInfo.event.description : eventInfo.description) : null}
                </Typography>
                {isMapVisible ? <LeafletMap address={getLocation()} /> : ''}
              </CardContent>
              <CardActions className={classes.card_actions__secondary}>
                <Grid container>
                  <Grid item>
                    <Button size="medium" className={classes.card_actions__button} onClick={toggleIsMapVisible}>
                      {isMapVisible ? t('EVENTS.EVENTS_HIDE_MAP') : t('EVENTS.EVENTS_SHOW_MAP')} &rarr;
                    </Button>
                  </Grid>
                </Grid>
              </CardActions>
            </Card>
          </Grid>
        </Container>
      )}
    </Fragment>
  );
}

export default EventsInfoPage;
