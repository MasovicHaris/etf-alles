import React, { Fragment, useEffect, useState } from 'react';
import { useSelector, useDispatch } from 'react-redux';
import { useHistory } from 'react-router-dom';
import { useTranslation } from 'react-i18next';
import styled from 'styled-components';
import MaterialContainer from '@material-ui/core/Container';
import { makeStyles } from '@material-ui/core/styles';
import Tabs from '@material-ui/core/Tabs';
import Tab from '@material-ui/core/Tab';
import Card from '@material-ui/core/Card';
import CardActionArea from '@material-ui/core/CardActionArea';
import CardMedia from '@material-ui/core/CardMedia';
import CardContent from '@material-ui/core/CardContent';
import CheckCircleIcon from '@material-ui/icons/CheckCircle';
import StarIcon from '@material-ui/icons/Star';
import AddIcon from '@material-ui/icons/Add';
import Typography from '@material-ui/core/Typography';
import CardActions from '@material-ui/core/CardActions';
import Grid from '@material-ui/core/Grid';
import IconButton from '@material-ui/core/IconButton';
import DeleteOutlineIcon from '@material-ui/icons/DeleteOutline';
import EditOutlinedIcon from '@material-ui/icons/EditOutlined';
import Button from '@material-ui/core/Button';

import { handleGetEventsByCreator, handleDeleteEvent, handleGetMyEventsInterested, handleGetMyEventsGoing } from '../actions/events-page-actions';

import ApplicationHeader from '../../shared-components/header';
import AlertDialog from '../../shared-components/alert-dialog';
import Spinner from '../../shared-components/spinner';

const Container = styled(MaterialContainer)`
  background-color: #fff;
`;

const useStyles = makeStyles({
  root: {
    display: 'flex',
    flexDirection: 'column',
    alignItems: 'center',
  },
  card_root: {
    maxWidth: 300,
    width: 400,
    height: 440,
    display: 'flex',
    flexDirection: 'column',
  },
  card_media: {
    height: 200,
  },
  card_content: {
    height: 150,
    paddingTop: 0,
  },
  card_title: {
    fontWeight: 600,
  },
  icon: {
    padding: '2px',
  },
  icon_label: {
    paddingRight: '3px',
  },
  description: {
    overflow: 'hidden',
    maxHeight: '120px',
  },
  no_padidng: {
    padding: '0px !important',
  },
  numberOf: {
    fontSize: '16px',
  },
  addIcon: {
    fontSize: 80,
    color: '#ccc',
  },
  action: {
    height: '100%',
    display: 'flex',
  },
  autoMargin: {
    marginTop: 'auto',
  },
  spinner: {
    marginTop: '40px',
    display: 'flex',
    justifyContent: 'center',
  },
});

function MyEventsPage() {
  const classes = useStyles();
  const { t } = useTranslation();
  const dispatch = useDispatch();
  const history = useHistory();
  const userLoggedIn = useSelector(state => state.auth.userLoggedIn);

  const [value, setValue] = useState(0);
  const myEvents = useSelector(state => state.events.myEvents);
  const myEventsGoing = useSelector(state => state.events.myEventsGoing);
  const myEventsInterested = useSelector(state => state.events.myEventsInterested);
  const getEventsInProgres = useSelector(state => state.events.getEventsInProgres);
  const getMyEventsGoingInProgres = useSelector(state => state.events.getMyEventsGoingInProgres);
  const getMyEventsInterestedInProgres = useSelector(state => state.events.getMyEventsInterestedInProgres);
  const [events, setEvents] = useState([]);
  const [isOpen, setIsOpen] = useState(false);
  const [eventToDelete, setEventToDelete] = useState();

  useEffect(() => {
    setEvents(myEvents);
  }, [myEvents]);

  useEffect(() => {
    setEvents(myEventsGoing);
  }, [myEventsGoing]);

  useEffect(() => {
    setEvents(myEventsInterested);
  }, [myEventsInterested]);

  const handleChange = (event, newValue) => {
    setValue(newValue);
    switch (newValue) {
      case 1:
        dispatch(handleGetMyEventsGoing());
        break;
      case 2:
        dispatch(handleGetMyEventsInterested());
        break;
      default:
        dispatch(handleGetEventsByCreator());
    }
  };

  const getDate = date => {
    const d = new Date(date);
    const days = ['Sunday', 'Monday', 'Tuesday', 'Wednesday', 'Thursday', 'Friday', 'Saturday'];
    return days[d.getDay()] + ', ' + d.getDate() + '.' + (d.getMonth() + 1) + '.' + d.getFullYear() + '.';
  };

  useEffect(() => {
    dispatch(handleGetEventsByCreator());
    // setEvents(myEvents);
  }, [dispatch]);

  const editClicked = event => {
    history.push(`/edit-event/${event.id}`);
  };

  const deleteClicked = event => {
    setIsOpen(true);
    setEventToDelete(event);
    // dispatch(handleDeleteEvent(event.id));
  };

  const deleteEvent = () => {
    dispatch(handleDeleteEvent(eventToDelete.id));
    setEventToDelete(null);
  };

  const newEventClicked = () => {
    history.push(`/new-event`);
  };

  const eventClicked = id => {
    history.push(`/event-info/${id}`);
  };

  const formatDescription = description => (description && description.length > 100 ? description.substr(0, 100) + '...' : description);

  function ActionsForLoggedUsers(event) {
    if (userLoggedIn && event) {
      return (
        <Grid container justify="flex-end">
          <IconButton disabled aria-label="event-interested" component="span" title={t('EVENTS.EVENTS_INTERESTED_BUTTON')}>
            <StarIcon /> <label className={classes.numberOf}>{event.numberOfInterested}</label>
          </IconButton>
          <IconButton disabled aria-label="event-going" component="span" title={t('EVENTS.EVENTS_GOING_BUTTON')}>
            <CheckCircleIcon /> <label className={classes.numberOf}>{event.numberOfGoing}</label>
          </IconButton>
        </Grid>
      );
    }
  }

  const eventsItems = events.map(event => (
    <Grid item xs={12} sm={6} lg={3} key={event.id}>
      <Card className={classes.card_root}>
        <CardMedia className={classes.card_media} image={event.imageUrl} title={event.title} />
        <CardContent className={classes.card_actions}>
          <Grid container spacing={3}>
            <Grid item xs={7}>
              <Typography color="textSecondary">{getDate(event.date)}</Typography>
            </Grid>
            <Grid item xs={5} className={classes.no_padidng}>
              {ActionsForLoggedUsers(event)}
            </Grid>
          </Grid>
          <Typography component="h5" variant="h5">
            {event.title}
          </Typography>
          <Typography component="p" className={classes.description}>
            {formatDescription(event.description)}
          </Typography>
        </CardContent>
        {value === 0 ? (
          <CardActions className={classes.autoMargin}>
            <Grid container>
              <Grid item container>
                <Typography color="textSecondary" className={classes.icon_label}>
                  <IconButton aria-label="edit" className={classes.icon} onClick={() => editClicked(event)}>
                    <EditOutlinedIcon />
                  </IconButton>
                  {t('EVENTS.EVENTS_EDIT_BUTTON')}
                </Typography>
                <Typography color="textSecondary" className={classes.icon_label}>
                  <IconButton aria-label="delete" className={classes.icon} onClick={() => deleteClicked(event)}>
                    {' '}
                    <DeleteOutlineIcon />
                  </IconButton>
                  {t('EVENTS.EVENTS_DELETE_BUTTON')}
                </Typography>
              </Grid>
            </Grid>
          </CardActions>
        ) : (
          <CardActions className={classes.card_actions__secondary}>
            <Grid container>
              <Grid item>
                <Button size="medium" className={classes.card_actions__button} onClick={() => eventClicked(event.id)}>
                  {t('EVENTS.EVENTS_GET_INFO_BUTTON')} &rarr;
                </Button>
              </Grid>
            </Grid>
          </CardActions>
        )}
      </Card>
    </Grid>
  ));

  return (
    <Fragment>
      <ApplicationHeader isMyEvents />
      <AlertDialog setIsOpen={setIsOpen} isOpen={isOpen} title={t('EVENTS.CONFIRM_DELETE_TITLE')} description={t('EVENTS.CONFIRM_DELETE_MSG')} onConfirmClick={deleteEvent} />
      <Container component="main">
        <h1>{t('EVENTS.MY-EVENTS')}</h1>
        <div className={classes.root}>
          <Tabs value={value} indicatorColor="primary" textColor="primary" onChange={handleChange} aria-label="disabled tabs example">
            <Tab label={t('EVENTS.MY_EVENTS_OPTION_0')} />
            <Tab label={t('EVENTS.MY_EVENTS_OPTION_1')} />
            <Tab label={t('EVENTS.MY_EVENTS_OPTION_2')} />
          </Tabs>
        </div>
        {value === 0 && <h2>{t('EVENTS.MY-EVENTS-ACTIONS')}</h2>}
        {value === 1 && <h2>{t('EVENTS.MY-EVENTS-ACTIONS_1')}</h2>}
        {value === 2 && <h2>{t('EVENTS.MY-EVENTS-ACTIONS_1')}</h2>}
        {events.length === 0 && <Typography component="p">{t('EVENTS.MY-EVENTS-NON-CREATED')}</Typography>}
        <br />
        {getEventsInProgres || getMyEventsGoingInProgres || getMyEventsInterestedInProgres ? (
          <div className={classes.spinner}>
            <Spinner size="50px" />
          </div>
        ) : (
          <Grid container spacing={3}>
            {value === 0 && (
              <Grid item xs={12} sm={6} lg={3} key={-1}>
                <Card className={classes.card_root}>
                  <CardActionArea className={classes.action}>
                    {/* <IconButton > */}
                    <AddIcon className={classes.addIcon} onClick={() => newEventClicked()} />
                    {/* </IconButton> */}
                    {/* <Button variant="outlined" size="small" color="primary" onClick={() => newEventClicked()}>
                    {t('EVENTS.CREATE-EVENT')}
                  </Button> */}
                  </CardActionArea>
                </Card>
              </Grid>
            )}
            {events.length !== 0 && eventsItems}
          </Grid>
        )}
      </Container>
    </Fragment>
  );
}

export default MyEventsPage;
