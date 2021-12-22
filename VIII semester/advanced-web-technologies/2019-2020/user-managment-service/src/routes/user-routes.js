import express from 'express';

import UserController from '../controllers/User';
import AuthController from '../controllers/Auth';
import { multer } from '../config/config-firebase';

const userRouter = express.Router();

userRouter.get('/', AuthController.checkValidToken, UserController.getAllUsers);

userRouter.get('/:username', AuthController.checkValidToken, UserController.getSpecificUser);

userRouter.put('/update', AuthController.checkValidToken, UserController.updateUser);

userRouter.delete('/delete', AuthController.checkValidToken, UserController.deleteUser);

userRouter.post('/profile-picture', multer.single('profileImage'), UserController.uploadImage);

export default userRouter;
