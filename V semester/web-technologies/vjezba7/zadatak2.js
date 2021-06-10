const express = require('express');
const app = express();
const path = require('path');

app.use('/css', express.static(path.join(__dirname)));
app.use(express.static('public'));
app.listen(8085);