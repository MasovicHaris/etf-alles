import request from 'request';
import dotenv from 'dotenv';
import { v4 as uuidv4 } from 'uuid';
import { expect } from 'chai';

dotenv.config();

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

describe('Get all users', () => {
  it('Treba da vrati 200, sa svim userima', (done) => {
    request.get(
      {
        headers: {
          'content-type': 'application/json',
          authorization: `Bearer ${token}`,
        },
        url: `${process.env.FULL_BASE_URL}/api/users`,
        json: true,
      },
      async (error, response, body) => {
        expect(response && response.statusCode).to.equal(200);
        done();
      }
    );
  });
});

describe('Get specific user', () => {
  it('Treba da vrati specific usera, sve ok', (done) => {
    request.get(
      {
        headers: {
          'content-type': 'application/json',
          authorization: `Bearer ${token}`,
        },
        url: `${process.env.FULL_BASE_URL}/api/users/masha`,
        json: true,
      },
      async (error, response, body) => {
        expect(response && response.statusCode).to.equal(200);
        done();
      }
    );
  });

  it('Treba da vrati 404, nema tog usera', (done) => {
    request.get(
      {
        headers: {
          'content-type': 'application/json',
          authorization: `Bearer ${token}`,
        },
        url: `${process.env.FULL_BASE_URL}/api/users/nepostojieci`,
        json: true,
      },
      async (error, response, body) => {
        expect(response && response.statusCode).to.equal(404);
        done();
      }
    );
  });
});

describe('Update and delete', () => {
  it('Treba da kreira user-a, update-uje ga i delete-a ga', (done) => {
    let token = null;
    const randomValue = uuidv4();
    const username = `randomUsername${randomValue}`;
    request.post(
      {
        headers: {
          'content-type': 'application/json',
        },
        url: `${process.env.FULL_BASE_URL}/api/auth/signup`,
        body: {
          name: 'ajla',
          surname: 'ajlaprez',
          password: 'passworddd',
          username,
        },
        json: true,
      },
      (error, response, body) => {
        expect(response && response.statusCode).to.equal(200, 'Please check if other services are running!');

        request.post(
          {
            headers: {
              'content-type': 'application/json',
            },
            url: `${process.env.FULL_BASE_URL}/api/auth/login`,
            body: {
              username,
              password: 'passworddd',
            },
            json: true,
          },
          (error, response, body) => {
            expect(response && response.statusCode).to.equal(200);
            token = body.token;

            request.put(
              {
                headers: {
                  'content-type': 'application/json',
                  authorization: `Bearer ${token}`,
                },
                url: `${process.env.FULL_BASE_URL}/api/users/update`,
                body: {
                  name: 'promjena imena',
                },
                json: true,
              },
              async (error, response, body) => {
                expect(response && response.statusCode).to.equal(200);
                token = body.token;

                request.delete(
                  {
                    headers: {
                      'content-type': 'application/json',
                      authorization: `Bearer ${token}`,
                    },
                    url: `${process.env.FULL_BASE_URL}/api/users/delete`,
                    json: true,
                  },
                  async (error, response, body) => {
                    expect(response && response.statusCode).to.equal(200, 'Please check if other services are running!');
                    done();
                  }
                );
              }
            );
          }
        );
      }
    );
  });
});
