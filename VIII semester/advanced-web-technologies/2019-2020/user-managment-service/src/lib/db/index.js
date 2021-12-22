import Sequelize from 'sequelize';

import { DB_USERNAME, DB_PASSWORD, DB_HOST, DB_PORT, DATABASE } from '../../config/constants';

const sequelize = new Sequelize(DATABASE, DB_USERNAME, DB_PASSWORD, {
  host: DB_HOST,
  port: DB_PORT,
  dialect: 'mysql',
  logging: false,
});

const db = {};

db.sequelize = sequelize;

db.User = sequelize.import(__dirname + '/models/User.js');

export default db;
