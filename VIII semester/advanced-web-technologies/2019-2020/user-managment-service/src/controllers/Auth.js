import jwt from 'jsonwebtoken';
import crypto from 'crypto';
import axios from 'axios';

import db from '../lib/db';
import servicesHelper from '../lib/helpers/services-helper';
import eventsSystemHelper from '../lib/helpers/events-system-helper';

import { JWT_SECRET, JWT_EXPIRE_TIME_TOKEN, SERVICES, GRPC_ACTION_TYPES, GRPC_USER_RESOURCE, DEFAULT_PICTURE } from '../config/constants';

export const login = async (req, res) => {
  try {
    const { username, password } = req.body;

    if (!username || !password) return res.status(400).json({ error: 'Error with request params. ' });

    const hashedPassword = crypto.createHash('sha256').update(password).digest('base64');

    const result = await db.User.findOne({ where: { username, password: hashedPassword } });

    if (!result) return res.status(401).json({ error: 'Error while trying to login. ' });

    const user = {
      id: result.id,
      name: result.name,
      surname: result.surname,
      username: result.username,
    };

    const token = jwt.sign(user, JWT_SECRET, {
      algorithm: 'HS256',
      expiresIn: JWT_EXPIRE_TIME_TOKEN,
    });

    const response = {
      user,
      token,
    };

    res.status(200).json(response);
  } catch (e) {
    console.log('[user-management-service] logIn - ', e.message);
    res.status(400).json({ error: 'Error while trying to login. ' });
  }
};

export const signUp = async (req, res) => {
  try {
    const { username, name, surname, password } = req.body;

    if (!username || !name || !surname || !password) return res.status(400).json({ error: 'Error with request params. ' });

    const hashedPassword = crypto.createHash('sha256').update(password).digest('base64');

    const result = await db.User.create({ username, name, surname, password: hashedPassword, picture: DEFAULT_PICTURE, dateOfRegistration: new Date() });

    if (!result) return res.status(500).json({ error: 'Error creating user. ' });

    // event
    const signUpEventUrl = servicesHelper.getServiceUrl();
    await axios.post(`${signUpEventUrl}/users/${result.id}`);

    // inform system events about newly created event
    eventsSystemHelper.logEvent(
      {
        serviceName: SERVICES.USER_MANAGEMENT_SERVICE,
        userId: result.id,
        actionType: GRPC_ACTION_TYPES.CREATE,
        resourceName: GRPC_USER_RESOURCE,
      },
      (result) => {
        if (!result) {
          console.log('[user-management-service] signUp - Error sending grpc message!');
          return res.status(500).json({ error: 'Error creating user. ' });
        }
        res.status(200).json({ username, name, surname });
      }
    );
  } catch (e) {
    console.log('[user-management-service] signUp - ', e.message);
    res.status(400).json({ error: 'Error creating user. ' });
  }
};

export const checkValidToken = (req, res, next) => {
  const token = req.headers['authorization'] ? req.headers['authorization'].split(' ')[1] : null;

  if (token) {
    jwt.verify(token, JWT_SECRET, (err, user) => {
      if (err) return res.status(405).json({ error: true, message: 'Unauthorized access.' });
      req.user = user;
      next();
    });
  } else {
    return res.status(403).send({
      error: true,
      message: 'No token provided.',
    });
  }
};

export const checkValidUsername = async (req, res) => {
  try {
    const result = await db.User.findOne({ where: { username: req.params.username } });

    if (!result) {
      return res.status(200).send({ invalid: false });
    }

    return res.status(200).send({ invalid: true });
  } catch (e) {
    console.log('[user-management-service] checkValidUsername - ', e.message);
    res.status(500).json({ error: 'Error checking valid username. ' });
  }
};

export default {
  login,
  signUp,
  checkValidToken,
  checkValidUsername,
};
