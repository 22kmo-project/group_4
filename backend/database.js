const mysql = require('mysql');
const connection = mysql.createPool({
  host: 'localhost',
  user: 'group4',
  password: 'netpass',
  database: 'group4'
});
module.exports = connection;