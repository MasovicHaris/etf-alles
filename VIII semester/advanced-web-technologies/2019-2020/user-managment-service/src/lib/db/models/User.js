import Sequelize from 'sequelize';

export default (sequelize, DataTypes) =>
  sequelize.define('User', {
    id: {
      type: Sequelize.INTEGER,
      primaryKey: true,
      autoIncrement: true,
    },
    username: {
      type: Sequelize.STRING,
      unique: true,
      required: true,
    },
    name: {
      type: Sequelize.STRING,
      required: true,
    },
    surname: {
      type: Sequelize.STRING,
      required: true,
    },
    password: {
      type: Sequelize.STRING,
      required: true,
    },
    picture: {
      type: Sequelize.STRING,
      required: true,
    },
    description: Sequelize.STRING,
    dateOfRegistration: {
      type: Sequelize.DATE,
      required: true,
    },
  });
