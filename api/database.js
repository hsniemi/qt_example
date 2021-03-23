const mysql = require('mysql');
const connection = mysql.createPool({
  host: 'localhost',
  user: 'root',
  password: 'HSN823ya',
  database: 'qt_example'
});
module.exports = connection;