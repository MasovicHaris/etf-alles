import React, { Fragment, useEffect } from 'react';
import { useSelector, useDispatch } from 'react-redux';
import { useHistory } from 'react-router-dom';
import { useParams } from 'react-router-dom';
import { useTranslation } from 'react-i18next';
import styled from 'styled-components';
import MaterialContainer from '@material-ui/core/Container';
import { makeStyles } from '@material-ui/core/styles';
import Grid from '@material-ui/core/Grid';
import Card from '@material-ui/core/Card';
import Paper from '@material-ui/core/Paper';
import CardMedia from '@material-ui/core/CardMedia';
import CardActionArea from '@material-ui/core/CardActionArea';
import CardContent from '@material-ui/core/CardContent';
import Typography from '@material-ui/core/Typography';
import Button from '@material-ui/core/Button';
import CardActions from '@material-ui/core/CardActions';
/*import IconButton from '@material-ui/core/IconButton';
import StarIcon from '@material-ui/icons/Star';
import StarBorderIcon from '@material-ui/icons/StarBorder';
import CheckCircleIcon from '@material-ui/icons/CheckCircle';
import CheckCircleOutlineIcon from '@material-ui/icons/CheckCircleOutline';
*/
import ApplicationHeader from '../../shared-components/header';
import Spinner from '../../shared-components/spinner';

import { handleGetCreator, handleSubscribeTo, handleGetSubscribers, handleGetEventsByAnyCreator, handleUnsubscribe } from '../actions/events-page-actions';
import { useState } from 'react';

const Container = styled(MaterialContainer)`
  background-color: #fff;
`;

const useStyles = makeStyles(theme => ({
  title: {
    fontSize: 20,
    fontWeight: 'bold',
    paddingBottom: '20px',
    paddingTop: '50px',
  },
  info: {
    fontSize: 14,
  },
  grid: {
    minHeight: '90vh',
  },
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
    borderRadius: '100%',
    height: '90%',
    width: '90%',
    maxHeight: '200px',
    maxWidth: '200px',
    minHeight: '150px',
    minWidth: '150px',
    objectFit: 'cover',
    border: '1px solid black',
  },
  buttonSub: {
    padding: '10px',
    display: 'flex',
    align: 'right',
    justifyContent: 'right',
  },
  card: {
    background: '#fff',
    height: '300px',
    display: 'flex',
    flexDirection: 'column',
    justifyContent: 'space-between',
  },
  icon: {
    padding: '0px',
  },
  icon_label: {
    paddingRight: '0px',
  },
  icon_label_bold: {
    paddingRight: '3px',
    textDecoration: 'underline',
    fontWeight: 'bold',
  },
  // HEADER STYLES
  header: {
    textAlign: 'center',
    padding: '25px 0',
  },
  // CARD STYLES
  card_root: {
    maxWidth: 300,
    minWidth: 260,
    height: 440,
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
  card_actions: {
    paddingBottom: 0,
    height: 40,
  },
  card_actions__secondary: {
    height: 50,
  },
  card_actions__button: {
    color: 'rgba(0, 0, 0, 0.54)',
    textTransform: 'none',
  },
  paper: {
    margin: '40px',
    padding: '30px',
    maxWidth: 1500,
  },
  img: {
    margin: 'auto',
    display: 'block',
    maxWidth: '100%',
    maxHeight: '100%',
  },
  spinner: {
    marginTop: '40px',
    display: 'flex',
    justifyContent: 'center',
  },
}));

function EventsInfoPage() {
  const classes = useStyles();
  const { t } = useTranslation();
  const dispatch = useDispatch();
  const userLoggedIn = useSelector(state => state.auth.userLoggedIn);
  const userLoggedInId = useSelector(state => state.auth.profile.id);
  const mySubscribers = useSelector(state => state.events.mySubscribers);
  const getUserEventsInProgres = useSelector(state => state.events.getUserEventsInProgres);
  const getSubscribers = useSelector(state => state.events.getSubscribers);
  const getEventsInProgres = useSelector(state => state.events.getEventsInProgres);
  const userEvents = useSelector(state => state.events.userEvents);
  const params = useParams();
  const userId = params.idUser;
  const history = useHistory();
  const { id, name, surname, picture, username, description } = useSelector(state => state.events.creatorOfEvent);

  const [subbed, setSubbed] = useState(false);

  useEffect(() => {
    if (!id) {
      dispatch(handleGetCreator(userId));
    } else {
      dispatch(handleGetSubscribers(id));
      dispatch(handleGetEventsByAnyCreator(id));
    }
  }, [dispatch, userId, id]);

  useEffect(() => {
    const subbedOrNot = mySubscribers.includes(parseInt(userId));
    setSubbed(subbedOrNot);
  }, [mySubscribers, userId]);

  const subscribeClicked = () => {
    dispatch(handleSubscribeTo(userId));
    setSubbed(true);
  };

  const unsubscribeClicked = () => {
    dispatch(handleUnsubscribe(userId));
    setSubbed(false);
  };

  const eventClicked = id => {
    history.push(`/event-info/${id}`);
  };

  // const interestedClicked = event => {;
  //   dispatch(handleInterestedClicked(event));
  // };

  // const goingToClicked = event => {
  //   dispatch(handleGoingToClicked(event));
  // };

  const formatDescription = description => (description && description.length > 100 ? description.substr(0, 100) + '...' : description);

  // function InterestedIcon(event) {
  //   if (event.marked && !event.going) {
  //     return <StarIcon />;
  //   }
  //   return <StarBorderIcon />;
  // }

  // function GoingIcon(event) {
  //   if (event.marked && event.going) {
  //     return <CheckCircleIcon />;
  //   }
  //   return <CheckCircleOutlineIcon />;
  // }

  // function ActionsForLoggedUsers(event) {
  //   if (userLoggedIn) {
  //     return (
  //       <Grid container justify="flex-end">
  //         <IconButton aria-label="event-interested" component="span" title={t('EVENTS.EVENTS_INTERESTED_BUTTON')} onClick={() => interestedClicked(event)}>
  //           {InterestedIcon(event)}  <label className={classes.numberOf}>{event.numberOfInterested}</label>
  //         </IconButton>
  //         <IconButton aria-label="event-going" component="span" title={t('EVENTS.EVENTS_GOING_BUTTON')} onClick={() => goingToClicked(event)}>
  //           {GoingIcon(event)} <label className={classes.numberOf}>{event.numberOfGoing}</label>
  //         </IconButton>
  //       </Grid>
  //     );
  //   }
  // }

  const getDate = date => {
    const d = new Date(date);
    const days = ['Sunday', 'Monday', 'Tuesday', 'Wednesday', 'Thursday', 'Friday', 'Saturday'];
    return days[d.getDay()] + ', ' + d.getDate() + '.' + (d.getMonth() + 1) + '.' + d.getFullYear() + '.';
  };

  const eventsItems = userEvents.map(eventData => {
    return (
      <Grid item xs={12} sm={6} md={4} lg={3} key={eventData.id || ''}>
        <Card className={classes.card_root}>
          <CardActionArea className={classes.card_media}>
            <CardMedia className={classes.card_media} image={eventData.imageUrl} title={eventData.title} onClick={() => eventClicked(eventData.id)} />
            {/* {ActionsForLoggedUsers(eventData)} */}
          </CardActionArea>
          <CardContent className={classes.card_actions}>
            <Typography color="textSecondary" component="p">
              {getDate(eventData.date)}
            </Typography>
          </CardContent>
          <CardContent className={classes.card_content}>
            <Typography gutterBottom variant="h5" component="h2" className={classes.card_title}>
              {eventData.title}
            </Typography>
            <Typography component="p">{formatDescription(eventData.description)}</Typography>
          </CardContent>
          <CardActions className={classes.card_actions__secondary}>
            <Grid container>
              <Grid item>
                <Button size="medium" className={classes.card_actions__button} onClick={() => eventClicked(eventData.id)}>
                  {t('EVENTS.EVENTS_GET_INFO_BUTTON')}
                </Button>
              </Grid>
            </Grid>
          </CardActions>
        </Card>
      </Grid>
    );
  });

  if (!userLoggedIn) {
    return null;
  }

  return (
    <Fragment>
      <ApplicationHeader />
      {getUserEventsInProgres || getSubscribers || getEventsInProgres ? (
        <div className={classes.spinner}>
          <Spinner size="50px" />
        </div>
      ) : (
        <Container component="main">
          <Paper className={classes.paper}>
            <Grid container spacing={2}>
              <Grid item>
                <div className={classes.imageOuterDiv}>
                  <div className={classes.imageInnerDiv}>
                    <img className={classes.image} src={picture || ''} alt="ProfileImage" />{' '}
                  </div>
                </div>
              </Grid>
              <Grid item xs={12} sm container>
                <Grid item xs container direction="column" spacing={2}>
                  <Grid item xs>
                    <Typography className={classes.title}>{name + ' ' + surname}</Typography>
                    <Typography className={classes.info} color="textSecondary" gutterBottom>
                      <b>{t('AUTH.USERNAME') + ': '}</b>
                      {username}
                    </Typography>
                    <Typography className={classes.info} color="textSecondary" gutterBottom>
                      <b>{t('AUTH.DESCRIPTION') + ': '}</b>
                      {description}
                    </Typography>
                  </Grid>
                  <Grid item></Grid>
                </Grid>
                <Grid item>
                  {!subbed && userLoggedInId !== id ? (
                    <div className={classes.buttonSub}>
                      <Button variant="contained" color="primary" onClick={() => subscribeClicked()}>
                        {t('EVENTS.SUBSCRIBE_BUTTON')}
                      </Button>
                    </div>
                  ) : (
                    <div className={classes.buttonSub}>
                      <Button variant="contained" color="primary" onClick={() => unsubscribeClicked()}>
                        {t('EVENTS.UNSUBSCRIBE_BUTTON')}
                      </Button>
                    </div>
                  )}
                </Grid>
              </Grid>
            </Grid>

            <Typography className={classes.title}>Creator of:</Typography>
            {userEvents.length !== 0 ? (
              <Container component="main">
                <Grid container spacing={3}>
                  {userEvents ? eventsItems : ''}
                </Grid>
              </Container>
            ) : (
              <Typography component="p">{t('EVENTS.EVENTS_NOT_FOUND')}</Typography>
            )}
          </Paper>
        </Container>
      )}
    </Fragment>
  );
}

export default EventsInfoPage;
