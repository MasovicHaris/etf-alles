import 'date-fns';
import React, { Fragment, useEffect, createRef, useState } from 'react';
import { useSelector, useDispatch } from 'react-redux';
import { useParams } from 'react-router-dom';
import { useTranslation } from 'react-i18next';
import { makeStyles } from '@material-ui/core/styles';
import { useFormik } from 'formik';
import { useHistory } from 'react-router-dom';
import CssBaseline from '@material-ui/core/CssBaseline';
import BackupIcon from '@material-ui/icons/Backup';
import CloseIcon from '@material-ui/icons/Close';
import TextField from '@material-ui/core/TextField';
import Grid from '@material-ui/core/Grid';
import Container from '@material-ui/core/Container';
import Select from '@material-ui/core/Select';
import MenuItem from '@material-ui/core/MenuItem';
import InputLabel from '@material-ui/core/InputLabel';
import DateFnsUtils from '@date-io/date-fns';
import FormHelperText from '@material-ui/core/FormHelperText';
import { KeyboardDatePicker, MuiPickersUtilsProvider } from '@material-ui/pickers';
import styled from 'styled-components';
import * as Yup from 'yup';

import { handleGetCategories, handleGetLocations, handleUpdateEvent, setSelectedDate, handleGetEvent, handleUploadNewImage, setSelectedEndDate } from '../actions/events-page-actions';

import Button from '../../shared-components/button';
import ApplicationHeader from '../../shared-components/header';
import Spinner from '../../shared-components/spinner';

const Header = styled.h1`
  text-align: center;
`;

const useStyles = makeStyles(theme => ({
  root: {
    display: 'flex',
    alignItems: 'center',
  },
  paper: {
    marginTop: theme.spacing(8),
    display: 'flex',
    flexDirection: 'column',
    alignItems: 'center',
  },
  form: {
    width: '100%',
    height: '100%',
    marginTop: theme.spacing(3),
  },
  submit: {
    marginTop: '10px',
    marginBottom: '30px',
    width: '150px',
  },
  formControl: {
    margin: theme.spacing(1),
    minWidth: 120,
  },
  selectEmpty: {
    marginTop: theme.spacing(2),
  },
  spinner: {
    marginTop: '50px',
    display: 'flex',
    justifyContent: 'center',
  },
  spinnerIcon: {
    position: 'absolute',
    top: '50px',
    right: '125px',
    padding: '5px',
    height: '40px',
    width: '40px',
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
    height: '90%',
    width: '90%',
    maxHeight: '290px',
    maxWidth: '290px',
    minHeight: '150px',
    minWidth: '150px',
    objectFit: 'cover',
    border: '1px solid gray',
  },
  inputImage: {
    display: 'none',
  },
  uploadIconOuter: {
    position: 'relative',
  },
  uploadIcon: {
    position: 'absolute',
    top: '50px',
    right: '125px',
    borderRadius: '50%',
    padding: '5px',
    height: '40px',
    width: '40px',
    '&:hover': {
      background: '#2c3e50',
      cursor: 'pointer',
    },
  },
  timeField: {
    marginRight: '20px',
    width: '40%',
  },
  error: {
    color: '#f44336',
  },
}));

const RedButton = styled(Button)`
  background-color: red;
  margin: 10px 15px 30px 15px;
  width: 150px;
`;

function NewEvent() {
  const { t } = useTranslation();
  const classes = useStyles();
  const dispatch = useDispatch();
  const history = useHistory();
  const params = useParams();
  const idEvent = params.idEvent;
  const refImageInput = createRef();

  const selectedDate = useSelector(state => state.events.selectedDate);
  const selectedEndDate = useSelector(state => state.events.selectedEndDate);
  const url = useSelector(state => state.events.uploadedImageUrl);
  const uploadImageInProgress = useSelector(state => state.events.uploadImageInProgress);

  useEffect(() => {
    dispatch(handleGetCategories());
  }, [dispatch]);

  useEffect(() => {
    dispatch(handleGetLocations());
  }, [dispatch]);

  useEffect(() => {
    dispatch(handleGetEvent(idEvent));
  }, [dispatch, idEvent]);

  useEffect(() => {
    setUploadedImageUrl(url);
  }, [url]);

  const validationSchema = Yup.object().shape({
    title: Yup.string().required(t('EVENTS.TITLE_IS_REQUIRED')),
    address: Yup.string().required(t('EVENTS.ADDRESS_IS_REQUIRED')),
    category: Yup.string().required(t('EVENTS.CATEGORY_IS_REQUIRED')),
    timeTo: Yup.string().test('is-greater', t('EVENTS.TIME_TO_NOT_VALID'), () => {
      if (!timeFrom || timeFrom === '') return true;
      return new Date('01/01/2000 ' + timeTo) >= new Date('01/01/2000 ' + timeFrom);
    }),
    timeFrom: Yup.string().test('is-less', t('EVENTS.TIME_FROM_NOT_VALID'), () => {
      if (!timeTo || timeTo === '') return true;
      return new Date('01/01/2000 ' + timeFrom) <= new Date('01/01/2000 ' + timeTo);
    }),
    date: Yup.string()
      .test('valid-date', t('EVENTS.DATE_NOT_VALID'), () => {
        return selectedDate.getDate() >= new Date().getDate();
      })
      .test('date-required', t('EVENTS.DATE_REQUIRED'), () => {
        return selectedDate;
      }),
    // location: Yup.string().required(t('EVENTS.LOCATION_IS_REQUIRED')),
  });

  const [uploadedImageUrl, setUploadedImageUrl] = useState(url);
  const [timeTo, setTimeTo] = useState('10:00');
  const [timeFrom, setTimeFrom] = useState('08:00');

  const handleDateChange = date => {
    dispatch(setSelectedDate(date));
  };

  const handleEndDateChange = date => {
    dispatch(setSelectedEndDate(date));
  };

  const handleTimeChange = e => {
    if (e.target.id === 'timeFrom') setTimeFrom(e.target.value);
    else setTimeTo(e.target.value);
  };

  const handleClose = () => {
    history.push('/my-events');
  };

  const categories = useSelector(state => state.events.categories);
  const locations = useSelector(state => state.events.locations);
  const event = useSelector(state => state.events.eventInfo);
  const updateEventInProgres = useSelector(state => state.events.updateEventInProgres);

  const { values, errors, touched, handleChange, handleBlur, handleSubmit, resetForm, setValues } = useFormik({
    enableReinitialize: true,
    initialValues: {
      title: event ? event.title : '',
      address: event ? event.address : '',
      date: event ? event.date : '',
      endDate: event ? event.endDate : '',
      description: event ? event.description : '',
      category: event && event.category ? event.category.id : '',
      location: event && event.location ? event.location.id : '',
      imageUrl: event && event.imageUrl ? event.imageUrl : 'https://storage.googleapis.com/event4u-d02b0.appspot.com/1612555831809_default.jpg',
      timeFrom: event && event.timeFrom ? event.timeFrom : '',
      timeTo: event && event.timeTo ? event.timeTo : '',
    },
    validationSchema,
    onSubmit: values => {
      if (uploadedImageUrl) {
        values.imageUrl = uploadedImageUrl;
      }
      values.date = selectedDate;
      values.timeFrom = timeFrom;
      values.timeTo = timeTo;
      values.endDate = selectedEndDate;
      dispatch(handleUpdateEvent(values, idEvent));
      resetForm({});
      !updateEventInProgres && history.push('/my-events');
    },
  });

  const fields = [
    { value: values.title, label: 'EVENTS.TITLE', name: 'title', error: touched.title && errors.title },
    { value: values.address, label: 'EVENTS.ADDRESS', name: 'address', error: touched.address && errors.address },
    { value: values.date, label: 'EVENTS.DATE', name: 'date', date: true, error: touched.date && errors.date },
    { value: values.endDate, label: 'EVENTS.END_DATE', name: 'endDate', date: true, error: touched.endDate && errors.endDate },
    { times: true },
    { value: values.description, label: 'EVENTS.DESCRIPTION', name: 'description', textArea: true, error: touched.description && errors.description },
    { value: values.category, label: 'EVENTS.CATEGORY', name: 'category', categories: true, error: touched.category && errors.category },
    // { value: values.location, label: 'EVENTS.LOCATION', name: 'location', locations: true, error: touched.location && errors.location },
  ];

  const timeFields = [
    { value: values.timeFrom, label: 'EVENTS.TIME_FROM', name: 'timeFrom', time: true, error: touched.timeFrom && errors.timeFrom, initValue: '08:00' },
    { value: values.timeTo, label: 'EVENTS.TIME_TO', name: 'timeTo', time: true, error: touched.timeTo && errors.timeTo, initValue: '10:00' },
  ];

  const onCloseUploadedImage = () => {
    setValues({ ...values, imageUrl: values.imageUrl });
    setUploadedImageUrl('');
  };

  const onUploadNewImage = e => {
    e.preventDefault();
    const reader = new FileReader();
    const file = e.target.files[0];
    if (reader && file) {
      reader.onloadend = () => {
        dispatch(handleUploadNewImage(file));
      };
      reader.readAsDataURL(file);
    }
  };

  function MenuItems(items, isCategories) {
    if (isCategories)
      return items.map(item => (
        <MenuItem value={item.id} key={item.id}>
          {item.name}
        </MenuItem>
      ));
    return items.map(item => (
      <MenuItem value={item.id} key={item.id}>
        {item.city}, {item.country}
      </MenuItem>
    ));
  }

  function FormField(field) {
    if (field.date) {
      return (
        <Grid key={field.name} item xs={12}>
          <MuiPickersUtilsProvider utils={DateFnsUtils}>
            <KeyboardDatePicker
              disableToolbar
              variant="inline"
              inputVariant="outlined"
              format="MM/dd/yyyy"
              margin="normal"
              id="date-picker-inline"
              label={t(field.label)}
              value={field.name === 'date' ? selectedDate : selectedEndDate}
              onChange={field.name === 'date' ? handleDateChange : handleEndDateChange}
              helperText={field.error}
              error={Boolean(field.error)}
              disablePast
              KeyboardButtonProps={{
                'aria-label': 'change date',
              }}
            />
          </MuiPickersUtilsProvider>
        </Grid>
      );
    } else if (field.times) {
      return (
        <Grid key="time" item xs={12}>
          {TimeField(timeFields[0])}
          {TimeField(timeFields[1])}
        </Grid>
      );
    } else if (field.categories) {
      return (
        <Grid key={field.name} item xs={12}>
          <InputLabel htmlFor={field.name}>{t('EVENTS.CATEGORY')}</InputLabel>
          <Select
            disabled
            value={event && event.category ? event.category.id : ''}
            id={field.name}
            onChange={handleChange}
            onBlur={handleBlur}
            label={t(field.label)}
            error={Boolean(field.error)}
            variant="outlined"
            name={field.name}
            fullWidth
          >
            {MenuItems(categories, true)}
          </Select>
          {Boolean(field.error) ? <FormHelperText className={classes.error}>{field.error}</FormHelperText> : ''}
        </Grid>
      );
    } else if (field.locations) {
      return (
        <Grid key={field.name} item xs={12}>
          <InputLabel htmlFor={field.name}>{t('EVENTS.LOCATION')}</InputLabel>
          <Select
            disabled
            value={event && event.location ? event.location.id : ''}
            id={field.name}
            onChange={handleChange}
            onBlur={handleBlur}
            label={t(field.label)}
            error={Boolean(field.error)}
            variant="outlined"
            name={field.name}
            fullWidth
          >
            {MenuItems(locations, false)}
          </Select>
        </Grid>
      );
    } else {
      return (
        <Grid key={field.name} item xs={12}>
          <TextField
            value={field.value}
            onChange={handleChange}
            onBlur={handleBlur}
            label={t(field.label)}
            error={Boolean(field.error)}
            variant="outlined"
            name={field.name}
            fullWidth
            multiline={field.textArea || false}
          />
        </Grid>
      );
    }
  }

  function TimeField(field) {
    return (
      <TextField
        id={field.name}
        label={t(field.label)}
        type="time"
        defaultValue={field.initValue}
        error={Boolean(field.error)}
        helperText={field.error}
        variant="outlined"
        className={classes.timeField}
        InputLabelProps={{
          shrink: true,
        }}
        inputProps={{
          step: 300, // 5 min
        }}
        onChange={handleTimeChange}
        onBlur={handleBlur}
      />
    );
  }

  return (
    <Fragment>
      <ApplicationHeader />
      <Container component="main" maxWidth="xs">
        <CssBaseline />
        <div className={classes.paper}>
          <Header>{t('EVENTS.UPDATE_EVENT_TITILE')}</Header>
          <form className={classes.form} onSubmit={handleSubmit} noValidate>
            <Grid container spacing={2}>
              <div className={classes.imageOuterDiv}>
                <div className={classes.imageInnerDiv}>
                  <img className={classes.image} src={uploadedImageUrl || values.imageUrl} alt="EventImage" />{' '}
                  <div className={classes.uploadIconOuter}>
                    {uploadImageInProgress ? (
                      <div className={classes.spinnerIcon}>
                        <Spinner size="30px" />
                      </div>
                    ) : uploadedImageUrl === '' ? (
                      <Fragment>
                        <input type="file" ref={refImageInput} className={classes.inputImage} onChange={onUploadNewImage} />
                        <BackupIcon className={classes.uploadIcon} fontSize="large" onClick={() => refImageInput.current.click()} />
                      </Fragment>
                    ) : (
                      <CloseIcon className={classes.uploadIcon} fontSize="large" onClick={onCloseUploadedImage} />
                    )}
                  </div>
                </div>
              </div>
              {fields.map(field => FormField(field))}
              <div className={classes.root}>
                <RedButton fullWidth type="button" variant="contained" color="primary" onClick={() => handleClose()} xs={6}>
                  {t('EVENTS.CANCEL')}
                </RedButton>
                <Button type="submit" fullWidth variant="contained" color="primary" className={classes.submit} xs={6}>
                  {t('EVENTS.UPDATE_EVENT')}
                </Button>
              </div>
            </Grid>
          </form>
        </div>
      </Container>
    </Fragment>
  );
}

export default NewEvent;
