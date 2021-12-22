import React, { Fragment, useEffect, useState, useMemo } from 'react';
import { useSelector, useDispatch } from 'react-redux';
import { useHistory, useParams } from 'react-router-dom';
import { useTranslation } from 'react-i18next';
import styled from 'styled-components';
import { format } from 'date-fns';
import enLocale from 'date-fns/locale/en-US';
import hrLocale from 'date-fns/locale/hr';

// MATERIAL-UI
import { makeStyles } from '@material-ui/core/styles';
import { MuiPickersUtilsProvider, KeyboardDatePicker } from '@material-ui/pickers';
import Button from '@material-ui/core/Button';
import Card from '@material-ui/core/Card';
import CardActionArea from '@material-ui/core/CardActionArea';
import CardActions from '@material-ui/core/CardActions';
import CardContent from '@material-ui/core/CardContent';
import CardMedia from '@material-ui/core/CardMedia';
import CheckCircleIcon from '@material-ui/icons/CheckCircle';
import CheckCircleOutlineIcon from '@material-ui/icons/CheckCircleOutline';
import DateFnsUtils from '@date-io/date-fns';
import FormControl from '@material-ui/core/FormControl';
import Grid from '@material-ui/core/Grid';
import IconButton from '@material-ui/core/IconButton';
import ClearIcon from '@material-ui/icons/Clear';
import InputLabel from '@material-ui/core/InputLabel';
import MaterialContainer from '@material-ui/core/Container';
import Select from '@material-ui/core/Select';
import StarBorderIcon from '@material-ui/icons/StarBorder';
import StarIcon from '@material-ui/icons/Star';
import TextField from '@material-ui/core/TextField';
import Typography from '@material-ui/core/Typography';
import Spinner from '../../shared-components/spinner';
import NothingFound from '../../shared-components/nothing-found';

import { handleGetEventsByCategory, handleInterestedClicked, handleGoingToClicked, handleGetEventsByCategoryLoggedUser, handleGetCategory } from '../actions/events-page-actions';

import ApplicationHeader from '../../shared-components/header';

import { createSortOrderFilter } from '../helpers/sortOrder';

const Container = styled(MaterialContainer)`
  background-color: #fff;
`;

const useStyles = makeStyles({
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
  // FILTER STYLES
  filter_root: {
    marginBottom: '30px',
    justifyContent: 'center',
  },
  filter_address: {
    width: '150px',
    paddingLeft: '50px',
  },
  filter_datepicker: {
    width: '150px',
    paddingLeft: '50px',
  },
  filter_datepicker__util: {
    width: '150px',
  },
  filter_sortorder: {
    width: '150px',
    paddingLeft: '50px',
  },
  filter_sortorder__form: {
    width: '150px',
  },
  numberOf: {
    fontSize: '16px',
  },
  spinner: {
    marginTop: '40px',
    display: 'flex',
    justifyContent: 'center',
  },
});

function EventsPage() {
  const classes = useStyles();
  const { t, i18n } = useTranslation();
  const dispatch = useDispatch();
  const history = useHistory();

  const params = useParams();
  const categoryId = params.idCategory;
  const category = useSelector(state => (state.events.category ? state.events.category : null));
  const userLoggedIn = useSelector(state => state.auth.userLoggedIn);
  const events = useSelector(state => state.events.events);
  const getCategoriesInProgress = useSelector(state => state.events.getCategoriesInProgres);

  const SORT_ORDER_FILTER = useMemo(
    () =>
      createSortOrderFilter({
        // newestFirst: t('FILTER.NEWEST_FIRST'),
        // oldestFirst: t('FILTER.OLDEST_FIRST'),
        ascending: t('FILTER.ASCENDING'),
        descending: t('FILTER.DESCENDING'),
      }),
    [t]
  );

  // LOCAL FILTERS
  // address | date | sortOrder
  // _____________
  const [address, setLocation] = useState('');
  const [date, setDate] = useState(null);
  const [sortOrder, setSortOrder] = useState(SORT_ORDER_FILTER[0]);
  // _____________

  useEffect(() => {
    if (!category) dispatch(handleGetCategory(categoryId));
  }, [dispatch, categoryId, category]);

  useEffect(() => {
    if (userLoggedIn) dispatch(handleGetEventsByCategoryLoggedUser(categoryId));
    else dispatch(handleGetEventsByCategory(categoryId));
  }, [dispatch, categoryId, userLoggedIn]);

  const eventClicked = id => {
    history.push(`/event-info/${id}`);
  };

  const interestedClicked = event => {
    dispatch(handleInterestedClicked(event));
  };

  const goingToClicked = event => {
    dispatch(handleGoingToClicked(event));
  };

  /**
   * @description
   * @param events - array of events
   * @param filter - Object containing following entries ->
   * Used for local filtering/sorting of the events based on:
   * 1. address (case insensitive filter)
   * 2. date (date filter)
   * 3. sortOrder (one of the objects inside SORT_ORDER_FILTER array. Sorting is based on its 'sortFunction' method)
   *
   */
  const localFilter = ({ events, filter }) => {
    return events
      .filter(event => ((event.event || event).address ? (event.event || event).address.toLowerCase().includes(filter.address.toLowerCase()) : true))
      .filter(event => (date ? (event.event || event).date === format(date, 'yyyy-MM-dd') : true))
      .sort(filter.sortOrder.sortFunction);
  };

  const getDate = date => format(new Date(date), 'MMMM dd, yyyy');

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

  function ActionsForLoggedUsers(event) {
    if (userLoggedIn) {
      return (
        <Grid container justify="flex-end">
          <IconButton aria-label="event-interested" component="span" title={t('EVENTS.EVENTS_INTERESTED_BUTTON')} onClick={() => interestedClicked(event)}>
            {InterestedIcon(event)} <label className={classes.numberOf}>{event.event.numberOfInterested}</label>
          </IconButton>
          <IconButton aria-label="event-going" component="span" title={t('EVENTS.EVENTS_GOING_BUTTON')} onClick={() => goingToClicked(event)}>
            {GoingIcon(event)} <label className={classes.numberOf}>{event.event.numberOfGoing}</label>
          </IconButton>
        </Grid>
      );
    }
  }

  const formatDescription = description => (description && description.length > 100 ? description.substr(0, 100) + '...' : description);

  const eventsItems = localFilter({ events, filter: { address, date, sortOrder } }).map(eventData => {
    const commonData = userLoggedIn ? (eventData ? eventData.event : {}) : eventData;

    if (!commonData) {
      return [];
    }

    const { id, imageUrl, title, date, description } = commonData;

    return (
      <Grid item xs={12} sm={6} md={4} lg={3} key={id || ''}>
        <Card className={classes.card_root}>
          <CardActionArea className={classes.card_media}>
            <CardMedia className={classes.card_media} image={imageUrl} title={title} onClick={() => eventClicked(id)} />
            {ActionsForLoggedUsers(eventData)}
          </CardActionArea>
          <CardContent className={classes.card_actions}>
            <Typography color="textSecondary" component="p">
              {getDate(date)}
            </Typography>
          </CardContent>
          <CardContent className={classes.card_content}>
            <Typography gutterBottom variant="h5" component="h2" className={classes.card_title}>
              {title}
            </Typography>
            <Typography component="p">{formatDescription(description)}</Typography>
          </CardContent>
          <CardActions className={classes.card_actions__secondary}>
            <Grid container>
              <Grid item>
                <Button size="medium" className={classes.card_actions__button} onClick={() => eventClicked(id)}>
                  {t('EVENTS.EVENTS_GET_INFO_BUTTON')} &rarr;
                </Button>
              </Grid>
            </Grid>
          </CardActions>
        </Card>
      </Grid>
    );
  });

  const onSortClicked = e => {
    const { target } = e;

    const newOrder = SORT_ORDER_FILTER.find(elem => parseInt(elem.value) === parseInt(target.value));

    setSortOrder(newOrder);
  };

  return (
    <Fragment>
      <ApplicationHeader />
      {getCategoriesInProgress ? (
        <div className={classes.spinner}>
          <Spinner size="50px" />
        </div>
      ) : (
        <Container component="main">
          {category && (
            <h1 className={classes.header} style={{ color: category.color }}>
              {category.name}
            </h1>
          )}
          {/* <h2>{t('EVENTS.EVENTS_TITLE')}</h2> */}
          {Array.isArray(events) && events.length ? (
            <>
              <Grid container className={classes.filter_root}>
                <Grid item className={classes.filter_address}>
                  <TextField id="standard-basic" label={t('FILTER.CITY')} value={address} onChange={({ target }) => setLocation(target.value)} />
                </Grid>
                <Grid item className={classes.filter_datepicker}>
                  <MuiPickersUtilsProvider
                    utils={DateFnsUtils}
                    locale={
                      {
                        en: enLocale,
                        ba: hrLocale,
                      }[i18n.language]
                    }
                    className={classes.filter_datepicker__util}
                  >
                    <KeyboardDatePicker
                      disableToolbar
                      variant="inline"
                      format="dd/MM/yyyy"
                      margin="normal"
                      id="date-picker-inline"
                      emptyLabel={t('FILTER.DATE')}
                      value={date}
                      disablePast
                      onChange={setDate}
                      KeyboardButtonProps={{
                        'aria-label': 'change date',
                      }}
                    >
                      <IconButton edge="end" size="small" disabled={!date} onClick={() => setDate(null)}>
                        <ClearIcon />
                      </IconButton>
                    </KeyboardDatePicker>
                  </MuiPickersUtilsProvider>
                </Grid>
                <Grid item className={classes.filter_sortorder}>
                  <FormControl className={classes.filter_sortorder__form}>
                    {/* DONT REMOVE THIS TAG */}
                    <InputLabel />
                    <Select native value={sortOrder.value} onChange={onSortClicked}>
                      {SORT_ORDER_FILTER.map(filter => (
                        <option value={filter.value} key={`${filter.title}-key`}>
                          {filter.title}
                        </option>
                      ))}
                    </Select>
                  </FormControl>
                </Grid>
              </Grid>
              <Grid container spacing={3}>
                {events ? eventsItems : ''}
                {!getCategoriesInProgress && eventsItems.length ? '' : <NothingFound msg={t('EVENTS.EVENTS_NOT_FOUND_FILTER')} />}
              </Grid>
            </>
          ) : (
            !getCategoriesInProgress && <NothingFound msg={t('EVENTS.EVENTS_NOT_FOUND')} />
          )}
        </Container>
      )}
    </Fragment>
  );
}

export default EventsPage;
