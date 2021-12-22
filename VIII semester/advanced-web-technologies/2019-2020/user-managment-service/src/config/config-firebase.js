import Multer from 'multer';
import admin from 'firebase-admin';

import firebaseConfig from '../../firebase.json';
import { STORAGE_BUCKET, FIREBASE_DATABASE_URL } from './constants';

admin.initializeApp({
  credential: admin.credential.cert(firebaseConfig),
  storageBucket: STORAGE_BUCKET,
  databaseURL: FIREBASE_DATABASE_URL,
});

export const bucket = admin.storage().bucket();

export const multer = Multer({
  storage: Multer.memoryStorage(),
});
