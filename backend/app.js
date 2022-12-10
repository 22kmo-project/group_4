var express = require('express');
var path = require('path');
var cookieParser = require('cookie-parser');
var logger = require('morgan');

var indexRouter = require('./routes/index');
var usersRouter = require('./routes/users');
var cardRouter = require('./routes/card');
var logRouter = require('./routes/log');
var accountRouter = require('./routes/account');
var personRouter = require('./routes/person');
var accountPermissionsRouter = require('./routes/accountPermissions');
var cardPermissionsRouter = require('./routes/cardPermissions');

var app = express();

app.use(logger('dev'));
app.use(express.json());
app.use(express.urlencoded({ extended: false }));
app.use(cookieParser());
app.use(express.static(path.join(__dirname, 'public')));

app.use('/', indexRouter);
app.use('/users', usersRouter);
app.use('/card', cardRouter);
app.use('/log', logRouter);
app.use('/account', accountRouter);
app.use('/person', personRouter);
app.use('/accountPermissions', accountPermissionsRouter);
app.use('/cardPermissions', cardPermissionsRouter);



module.exports = app;
