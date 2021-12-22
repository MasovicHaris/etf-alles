import React, { useState, Fragment, useCallback, useEffect } from 'react';
import { fade, makeStyles } from '@material-ui/core/styles';
import { useTranslation } from 'react-i18next';
import { useSelector, useDispatch } from 'react-redux';
import { useHistory } from 'react-router-dom';
import i18n from 'i18next';
import AppBar from '@material-ui/core/AppBar';
import Toolbar from '@material-ui/core/Toolbar';
import IconButton from '@material-ui/core/IconButton';
import Typography from '@material-ui/core/Typography';
import Badge from '@material-ui/core/Badge';
import MenuItem from '@material-ui/core/MenuItem';
import Menu from '@material-ui/core/Menu';
import AccountCircle from '@material-ui/icons/AccountCircle';
import NotificationsIcon from '@material-ui/icons/Notifications';
import MoreIcon from '@material-ui/icons/MoreVert';
import LanguageIcon from '@material-ui/icons/Language';
import ExitToAppIcon from '@material-ui/icons/ExitToApp';
import EventIcon from '@material-ui/icons/Event';
import propTypes from 'prop-types';
import NewReleasesIcon from '@material-ui/icons/NewReleases';
import ListItem from '@material-ui/core/ListItem';
import ListItemText from '@material-ui/core/ListItemText';
import PeopleIcon from '@material-ui/icons/People';

import { timeToWords } from '../../core/helpers/time-helper';

import SockJsClient from 'react-stomp';

import { handleLogout } from '../auth/actions/auth-actions';
import { handleGetNotifications, handlePutNotificationsById } from '../notifications/actions/notifications-actions';

import { handleGetEventsByCreator } from '../events-page/actions/events-page-actions';

import { BACKEND_API } from '../../config/constants';

import signUpLogo from '../../config/images/sign-up-white.png';
import styled from 'styled-components';

const useStyles = makeStyles(theme => ({
  menuButton: {
    marginRight: theme.spacing(2),
  },
  title: {
    display: 'none',
    [theme.breakpoints.up('sm')]: {
      display: 'block',
    },
  },
  search: {
    position: 'relative',
    borderRadius: theme.shape.borderRadius,
    backgroundColor: fade(theme.palette.common.white, 0.15),
    '&:hover': {
      backgroundColor: fade(theme.palette.common.white, 0.25),
    },
    width: '100%',
    maxWidth: '300px',
    marginRight: '70px',
    [theme.breakpoints.down('sm')]: {
      marginRight: '100px',
    },
    [theme.breakpoints.down('xs')]: {
      maxWidth: 'unset',
      marginRight: '0px',
    },
  },
  searchIcon: {
    padding: theme.spacing(0, 2),
    height: '100%',
    position: 'absolute',
    pointerEvents: 'none',
    display: 'flex',
    alignItems: 'center',
    justifyContent: 'center',
  },
  inputRoot: {
    color: 'inherit',
  },
  inputInput: {
    padding: theme.spacing(1, 1, 1, 0),
    paddingLeft: `calc(1em + ${theme.spacing(4)}px)`,
    transition: theme.transitions.create('width'),
    width: '100%',
  },
  sectionDesktop: {
    display: 'none',
    [theme.breakpoints.up('md')]: {
      display: 'flex',
    },
  },
  sectionLanguages: {
    display: 'flex',
  },
  sectionMobile: {
    display: 'flex',
    [theme.breakpoints.up('md')]: {
      display: 'none',
    },
  },
  root: {
    maxHeight: '64px',
    display: 'flex',
    [theme.breakpoints.down('xs')]: {
      maxHeight: '56px',
    },
  },
  toolbar: {
    justifyContent: 'space-between',
    backgroundColor: '#2c3e50',
  },
  sectionLanguagesLogged: {
    display: 'flex',
    marginRight: '130px',
    [theme.breakpoints.down('xs')]: {
      marginRight: '0px',
    },
  },
  sectionOfTime: {
    padding: theme.spacing(1, 10, 1, 1),
    display: 'flex',
  },
  menuItem: {
    padding: theme.spacing(0, 0, 0, 0),
    display: 'flex',
  },
}));

function ApplicationHeader({ isMyAccount, isAuthPage, onSearch, isMyEvents }) {
  const { t } = useTranslation();
  const history = useHistory();
  const dispatch = useDispatch();
  const classes = useStyles();

  const [anchorEl, setAnchorEl] = useState(null);
  const [languagesAnchor, setLanguagesAnchor] = useState(null);
  const [mobileMoreAnchorEl, setMobileMoreAnchorEl] = useState(null);
  const [NotificationAnchorEl, setNotificationAnchorEl] = useState(null);
  const [loadedNotifications, setLoadedNotifications] = useState(false);
  const [count, setCount] = useState(0);

  const userLoggedIn = useSelector(state => state.auth.userLoggedIn);

  const notifications = useSelector(state => state.notifications.notifications);

  const handleNumberOfNonReadNotifications = useCallback(() => {
    let num = 0;
    notifications.forEach(element => {
      if (element.isRead === false) {
        num++;
      }
    });
    setCount(num);
  }, [notifications]);

  useEffect(() => {
    if (!loadedNotifications && userLoggedIn) {
      dispatch(handleGetNotifications());
      setLoadedNotifications(true);
      dispatch(handleGetEventsByCreator());
    }
    handleNumberOfNonReadNotifications();
  }, [dispatch, handleNumberOfNonReadNotifications, loadedNotifications, userLoggedIn]);

  const isMenuOpen = Boolean(anchorEl);
  const isMobileMenuOpen = Boolean(mobileMoreAnchorEl);
  const isNotificationsOpen = Boolean(NotificationAnchorEl);
  const Image = styled.img`
    width: 50px;
    height: 50px;
    cursor: pointer;
  `;
  const handleProfileMenuOpen = event => {
    setAnchorEl(event.currentTarget);
  };

  const handleMobileMenuClose = () => {
    setMobileMoreAnchorEl(null);
  };

  const handleMenuClose = () => {
    setAnchorEl(null);
    handleMobileMenuClose();
  };

  const handleLanguageClose = e => {
    i18n.changeLanguage(String(e.target.id));
    setLanguagesAnchor(null);
  };

  const handleMobileMenuOpen = event => {
    setMobileMoreAnchorEl(event.currentTarget);
  };

  const handleLangugageMenuOpen = event => {
    setLanguagesAnchor(event.currentTarget);
  };

  const handleMyAccountEventsClicked = () => {
    setAnchorEl(null);
    handleMobileMenuClose();
    history.push(isMyAccount ? '/' : '/my-account');
  };

  const handleLogoutClicked = () => {
    setAnchorEl(null);
    handleMobileMenuClose();
    dispatch(handleLogout());
    history.push('/login');
  };

  const handleNewNotifications = event => {
    setNotificationAnchorEl(event.currentTarget);
    handleNumberOfNonReadNotifications();
    dispatch(handleGetNotifications());
  };
  const handleNewNotificationsClose = () => {
    setNotificationAnchorEl(null);
    handleMobileMenuClose();
  };

  const handleNotificationClicked = notification => {
    dispatch(handlePutNotificationsById(notification.notificationId));
    handleNumberOfNonReadNotifications();
  };

  const handleMyEventsClicked = () => {
    setAnchorEl(null);
    handleMobileMenuClose();
    history.push(isMyEvents ? '/' : '/my-events');
  };

  const handleEventsClicked = () => {
    setAnchorEl(null);
    handleMobileMenuClose();
    history.push('/');
  };

  const menuId = 'primary-search-account-menu';
  const renderMenu = (
    <Menu
      anchorEl={anchorEl}
      anchorOrigin={{ vertical: 'top', horizontal: 'right' }}
      id={menuId}
      keepMounted
      transformOrigin={{ vertical: 'top', horizontal: 'right' }}
      open={isMenuOpen}
      onClose={handleMenuClose}
    >
      <MenuItem onClick={handleMyAccountEventsClicked}>{t(isMyAccount ? 'HEADER.EVENTS' : 'HEADER.MY_ACCOUNT')}</MenuItem>
      <MenuItem onClick={handleMyEventsClicked}>{t(isMyEvents ? 'HEADER.EVENTS' : 'HEADER.MY_EVENTS')}</MenuItem>
      <MenuItem onClick={handleLogoutClicked}>{t('HEADER.LOGOUT')}</MenuItem>
    </Menu>
  );
  const languagesId = 'primary-lang-id';
  const renderLanguages = (
    <Menu
      anchorEl={languagesAnchor}
      anchorOrigin={{ vertical: 'top', horizontal: 'right' }}
      keepMounted
      id={languagesId}
      transformOrigin={{ vertical: 'top', horizontal: 'right' }}
      open={Boolean(languagesAnchor)}
      onClose={handleLanguageClose}
    >
      <MenuItem id={'en'} onClick={handleLanguageClose}>
        {t('HEADER.ENGLISH')}
      </MenuItem>
      <MenuItem id={'ba'} onClick={handleLanguageClose}>
        {t('HEADER.BOSNIAN')}
      </MenuItem>
    </Menu>
  );

  const mobileMenuId = 'primary-search-account-menu-mobile';
  const renderMobileMenu = (
    <Menu
      anchorEl={mobileMoreAnchorEl}
      anchorOrigin={{ vertical: 'top', horizontal: 'right' }}
      id={mobileMenuId}
      keepMounted
      transformOrigin={{ vertical: 'top', horizontal: 'right' }}
      open={isMobileMenuOpen}
      onClose={handleMobileMenuClose}
    >
      <MenuItem onClick={handleMyAccountEventsClicked}>
        <IconButton aria-label="show 11 new notifications" color="inherit">
          {isMyAccount ? <EventIcon /> : <AccountCircle />}
        </IconButton>
        <p>{t(isMyAccount ? 'HEADER.EVENTS' : 'HEADER.MY_ACCOUNT')}</p>
      </MenuItem>
      <MenuItem onClick={handleMyEventsClicked}>
        <IconButton>
          <EventIcon></EventIcon>
        </IconButton>
        <p>{t('HEADER.MY_EVENTS')}</p>
      </MenuItem>
      <MenuItem onClick={handleLogoutClicked}>
        <IconButton aria-label="account of current user" aria-controls="primary-search-account-menu" aria-haspopup="true" color="inherit">
          <ExitToAppIcon />
        </IconButton>
        <p>{t('HEADER.LOGOUT')}</p>
      </MenuItem>
    </Menu>
  );

  const notificationId = 'primary-search-notifications';
  const renderNotification = (
    <Menu
      className={classes.menuItem}
      getContentAnchorEl={null}
      keepMounted
      anchorEl={NotificationAnchorEl}
      anchorOrigin={{
        vertical: 'bottom',
        horizontal: 'center',
      }}
      id={notificationId}
      transformOrigin={{
        vertical: 'top',
        horizontal: 'center',
      }}
      open={isNotificationsOpen}
      onClose={handleNewNotificationsClose}
    >
      {notifications.map(notification => (
        <MenuItem
          component="div"
          className={classes.menuItem}
          key={notification.notificationId}
          value={notification.notificationId}
          onClick={() => handleNotificationClicked(notification)}
          style={notification.isRead ? { backgroundColor: 'white' } : { backgroundColor: '#eceef4' }}
        >
          {notification.type === 1 ? (
            <ListItem>
              <ListItemText
                primary={t('NOTIFICATION.NEWEVENT') + ': ' + JSON.parse(notification.message).event}
                secondary={
                  <React.Fragment>
                    {t('NOTIFICATION.MESSAGE') + JSON.parse(notification.message).event + t('NOTIFICATION.MESSAGE.REMINDER2') + JSON.parse(notification.message).date}
                    <br></br>
                    <Typography variant="caption">
                      <Typography component={'span'} className={classes.sectionOfTime}>
                        <NewReleasesIcon color="primary" fontSize="small" />
                        {timeToWords(notification.dateOfCreating)}
                      </Typography>
                    </Typography>
                  </React.Fragment>
                }
              />
            </ListItem>
          ) : notification.type === 2 ? (
            <ListItem>
              <ListItemText
                primary={t('NOTIFICATION.NEWEVENT.REMINDER') + ': ' + JSON.parse(notification.message).event}
                secondary={
                  <React.Fragment>
                    {t('NOTIFICATION.MESSAGE.REMINDER1') + JSON.parse(notification.message).event + t('NOTIFICATION.MESSAGE.REMINDER2') + JSON.parse(notification.message).date}
                    <br></br>
                    <Typography variant="caption">
                      <Typography component={'span'} className={classes.sectionOfTime}>
                        <EventIcon color="primary" fontSize="small" />
                        {timeToWords(notification.dateOfCreating)}
                      </Typography>
                    </Typography>
                  </React.Fragment>
                }
              />
            </ListItem>
          ) : (
            <ListItem>
              <ListItemText
                primary={t('NOTIFICATION.NEWEVENT2') + ': ' + JSON.parse(notification.message).event}
                secondary={
                  <React.Fragment>
                    {t('NOTIFICATION.MESSAGE2') + JSON.parse(notification.message).event + t('NOTIFICATION.MESSAGE.REMINDER2') + JSON.parse(notification.message).date}
                    <br></br>
                    <Typography variant="caption">
                      <Typography component={'span'} className={classes.sectionOfTime}>
                        <PeopleIcon color="primary" fontSize="small" />
                        {timeToWords(notification.dateOfCreating)}
                      </Typography>
                    </Typography>
                  </React.Fragment>
                }
              />
            </ListItem>
          )}
        </MenuItem>
      ))}
    </Menu>
  );

  return (
    <div className={classes.root}>
      <AppBar position="static">
        <SockJsClient
          url={BACKEND_API + '/ws/'}
          topics={['/topic/notification']}
          onMessage={msg => {
            dispatch(handleGetNotifications());
            handleNumberOfNonReadNotifications();
          }}
        />
        <Toolbar className={classes.toolbar}>
          {userLoggedIn ? (
            <div className={classes.sectionLanguagesLogged}>
              <Image onClick={handleEventsClicked} src={signUpLogo} alt="logo" />
            </div>
          ) : (
            <Typography className={classes.title} variant="h6" noWrap>
              {t('HEADER.EVENT4U')}
            </Typography>
          )}
          {userLoggedIn ? (
            <Fragment>
              <div className={classes.sectionDesktop}>
                <IconButton aria-label="show 17 new notifications" aria-controls={notificationId} aria-haspopup="true" onClick={handleNewNotifications} color="inherit">
                  <Badge badgeContent={count} color="secondary">
                    <NotificationsIcon />
                  </Badge>
                </IconButton>
                <IconButton aria-label="show more" aria-controls={languagesId} aria-haspopup="true" onClick={handleLangugageMenuOpen} color="inherit">
                  <LanguageIcon />
                </IconButton>
                <IconButton edge="end" aria-label="account of current user" aria-controls={menuId} aria-haspopup="true" onClick={handleProfileMenuOpen} color="inherit">
                  <AccountCircle />
                </IconButton>
              </div>
              <div className={classes.sectionMobile}>
                <IconButton aria-label="show 17 new notifications" aria-controls={notificationId} aria-haspopup="true" onClick={handleNewNotifications} color="inherit">
                  <Badge badgeContent={count} color="secondary">
                    <NotificationsIcon />
                  </Badge>
                </IconButton>

                <IconButton aria-label="show more" aria-controls={mobileMenuId} aria-haspopup="true" onClick={handleMobileMenuOpen} color="inherit">
                  <MoreIcon />
                </IconButton>
              </div>
            </Fragment>
          ) : (
            <div style={{ display: 'flex' }}>
              <div className={classes.sectionLanguages}>
                <IconButton aria-label="show more" aria-controls={languagesId} aria-haspopup="true" onClick={handleLangugageMenuOpen} color="inherit">
                  <LanguageIcon />
                </IconButton>
              </div>
              <div className={classes.sectionLanguages}>
                <IconButton aria-label="show more" aria-controls={languagesId} aria-haspopup="true" onClick={() => history.push(isAuthPage ? '/' : '/login')} color="inherit">
                  {isAuthPage ? <EventIcon /> : <ExitToAppIcon />}
                </IconButton>
              </div>
            </div>
          )}
        </Toolbar>
      </AppBar>
      {userLoggedIn && (
        <Fragment>
          {renderMobileMenu}
          {renderMenu}
        </Fragment>
      )}

      {renderNotification}
      {renderLanguages}
    </div>
  );
}

ApplicationHeader.propTypes = {
  onSearch: propTypes.func,
  isMyAccount: propTypes.bool,
  isAuthPage: propTypes.bool,
};

ApplicationHeader.defaultProps = {
  onSearch: () => {},
  isMyAccount: false,
  isAuthPage: false,
};

export default ApplicationHeader;
