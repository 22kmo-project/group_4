const mysql = require('mysql');
const connection = mysql.createPool({
  host: 'localhost',
  user: 'group_4',
  password: 'netpass',
  database: 'group_4'
});
module.exports = connection;