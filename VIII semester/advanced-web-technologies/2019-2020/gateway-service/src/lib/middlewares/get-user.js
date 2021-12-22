import express from 'express';

import serviceHelper from '../helpers/services-helper';
import { SERVICES } from '../../config/constants';

const axios = require('axios');

export const getSpecificUserById = async (req, res) => {
  axios.defaults.headers.common['Authorization'] = req.headers.authorization;
  let finalRes = '';
  try {
    const userId = req.params.userId;
    axios
      .get('http://' + req.headers.host + '/aggregator/api/users')
      .then((response) => {
        response.data.forEach((element) => {
          if (element.id == userId) {
            finalRes = element;
          }
        });
      })
      .catch((error) => {
        console.log('[user-management-service] getSpecificUserById - ', error.message);
        res.status(500).json({ error: 'Error getting specific user. ' });
      })
      .finally(() => {
        if (!res) {
          return res.status(404).send({
            error: true,
            message: 'User not found.',
          });
        }
        res.status(200).json(finalRes);
      });
  } catch (e) {
    console.log('[user-management-service] getSpecificUserById - ', e.message);
    res.status(500).json({ error: 'Error getting specific user. ' });
  }
};

const userRouter = express.Router();

userRouter.get('/getSpecificUserById/:userId', getSpecificUserById);

export default userRouter;
