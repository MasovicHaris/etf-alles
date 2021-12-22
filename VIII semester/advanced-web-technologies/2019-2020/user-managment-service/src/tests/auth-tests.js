import request from 'request';
import dotenv from 'dotenv';
import { v4 as uuidv4 } from 'uuid';
import { expect } from 'chai';

import db from '../lib/db';

dotenv.config();

let randomUsername = uuidv4();
let token = null;

before((done) => {
  request.post(
    {
      headers: {
        'content-type': 'application/json',
      },
      url: `${process.env.FULL_BASE_URL}/api/auth/login`,
      body: {
        username: 'masha',
        password: 'password',
      },
      json: true,
    },
    (error, response, body) => {
      expect(response && response.statusCode).to.equal(200);
      token = body.token;
      done();
    }
  );
});

after((done) => {
  db.User.destroy({ where: { username: randomUsername } }).then(() => done());
});

describe('Login', () => {
  it('Treba da se login vrati 200, bez greske', (done) => {
    request.post(
      {
        headers: {
          'content-type': 'application/json',
        },
        url: `${process.env.FULL_BASE_URL}/api/auth/login`,
        body: {
          username: 'ajla',
          password: 'password',
        },
        json: true,
      },
      (error, response, body) => {
        expect(response && response.statusCode).to.equal(200);
        done();
      }
    );
  });

  it('Treba da se login vrati 400, jer nije poslan password', (done) => {
    request.post(
      {
        headers: {
          'content-type': 'application/json',
        },
        url: `${process.env.FULL_BASE_URL}/api/auth/login`,
        body: {
          username: 'ajla',
        },
        json: true,
      },
      (error, response, body) => {
        expect(response && response.statusCode).to.equal(400);
        done();
      }
    );
  });
});

describe('Signup', () => {
  it('Treba da signup vrati 200, bez greske', (done) => {
    request.post(
      {
        headers: {
          'content-type': 'application/json',
        },
        url: `${process.env.FULL_BASE_URL}/api/auth/signup`,
        body: {
          username: randomUsername,
          password: 'password2',
          name: 'ajla',
          surname: 'ajlaprez',
        },
        json: true,
      },
      (error, response, body) => {
        expect(response && response.statusCode).to.equal(200, 'Please check if other services are running!');
        done();
      }
    );
  });

  it('Treba da signup vrati 400, losi parametri', (done) => {
    request.post(
      {
        headers: {
          'content-type': 'application/json',
        },
        url: `${process.env.FULL_BASE_URL}/api/auth/signup`,
        body: {
          name: 'ajla',
          surname: 'ajlaprez',
        },
        json: true,
      },
      (error, response, body) => {
        expect(response && response.statusCode).to.equal(400);
        done();
      }
    );
  });
});

describe('Check token', () => {
  it('Treba da signup vrati 200, dobar token', (done) => {
    request.get(
      {
        headers: {
          'content-type': 'application/json',
          authorization: `Bearer ${token}`,
        },
        url: `${process.env.FULL_BASE_URL}/api/auth/check-token`,
        json: true,
      },
      async (error, response, body) => {
        expect(response && response.statusCode).to.equal(200);
        done();
      }
    );
  });

  it('Treba da vrati 403, nema tokena ', (done) => {
    request.get(
      {
        headers: {
          'content-type': 'application/json',
        },
        url: `${process.env.FULL_BASE_URL}/api/auth/check-token`,
        json: true,
      },
      async (error, response, body) => {
        expect(response && response.statusCode).to.equal(403);
        done();
      }
    );
  });
});

describe('Check username', () => {
  it('Treba da check username vrati 200, invalid false', (done) => {
    request.get(
      {
        url: `${process.env.FULL_BASE_URL}/api/auth/check-username/mashanovirandom123123`,
      },
      (error, response, body) => {
        const des = JSON.parse(body);
        expect(des.invalid).to.equal(false);
        expect(response && response.statusCode).to.equal(200);
        done();
      }
    );
  });

  it('Treba da check username vrati 200, invalid true', (done) => {
    request.get(
      {
        url: `${process.env.FULL_BASE_URL}/api/auth/check-username/masha`,
      },
      (error, response, body) => {
        const des = JSON.parse(body);
        expect(des.invalid).to.equal(true);
        expect(response && response.statusCode).to.equal(200);
        done();
      }
    );
  });
});
