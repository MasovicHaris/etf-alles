import React from 'react';
import { useTranslation } from 'react-i18next';
import Typography from '@material-ui/core/Typography';
import { makeStyles } from '@material-ui/core/styles';

const useStyles = makeStyles({
  center: {
    textAlign: 'center',
    width: '100%',
  },
  image: {
    width: '400px',
  },
});

function NothingFound({ msg }) {
  const classes = useStyles();
  const { t, i18n } = useTranslation();
  return (
    <div className={classes.center}>
      <img className={classes.image} src="https://assets.materialup.com/uploads/b17ea0c7-df76-4ce1-bf82-4a2cf6ae866d/preview.jpg" alt="Not found image"></img>
      <Typography component="p">{msg}</Typography>
    </div>
  );
}

export default NothingFound;
