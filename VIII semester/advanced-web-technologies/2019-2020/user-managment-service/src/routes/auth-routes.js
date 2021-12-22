import express from 'express';

import AuthController from '../controllers/Auth';

const authRouter = express.Router();

authRouter.post('/login', AuthController.login);

authRouter.post('/signup', AuthController.signUp);

authRouter.get('/check-username/:username', AuthController.checkValidUsername);

authRouter.get('/check-token', AuthController.checkValidToken, (req, res) => res.status(200).json({ tokenValid: true }));

export default authRouter;
