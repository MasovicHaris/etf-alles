const express = require('express');
const app = express();
const path = require('path');
var mysql = require('mysql');
const bodyParser = require('body-parser');

app.use(bodyParser.json());
app.use(bodyParser.urlencoded({
  extended: true
}));

var con = mysql.createConnection({
  host: "localhost",
  user: "root",
  password: "",
  database: "lab9"
});

con.connect(function (err) {
  if (err) throw err;
  console.log("Connected to database!");
});

app.use('/css', express.static(__dirname));

app.get('/imenik', (req, res) => {
  var sql = "SELECT * from imenik";
  con.query(sql, function (err, result) {
    if (err) throw err;
    res.render(path.join(__dirname, 'tabela2.ejs'), {
      redovi: result,
      varijabla: 1
    });
  });
}).post('/imenik', (req, res) => {
  let brojindexa = null;
  var sql = "SELECT * from imenik";
  con.query(sql, function (err, result) {
    if (err) throw err;
    brojindexa = result.length + 1;
    let tijelo = req.body;
    var sql = `INSERT into imenik VALUES ('${brojindexa}', '${tijelo.ime}','${tijelo['prezime']}','${tijelo['adresa']}','${tijelo['brtel']}')`;
    con.query(sql, function (err, result) {
      if (err) throw err;
      res.redirect('/imenik');
    });
  });
});


app.get('/poznanik/:kontakt', (req, res) => {
  let idKontakta = req.params.kontakt;
  var sql = "SELECT * from adresar WHERE idKontakta='" + idKontakta + "'";
  con.query(sql, function (err, result) {
    if (err) throw err;
      let string = "(";
      for(let i=0;i<result.length;++i) string +=  result[i].idPoznanik.toString() + ",";
      string = string.replace(/.$/,")");
      let sql2 = "SELECT * from imenik WHERE imenik_id IN " + string + ";";
      con.query(sql2, function (err, result) {
        if (err) throw err;
        res.render(path.join(__dirname, 'tabela2.ejs'), {
          redovi: result,
          varijabla: 0
        });
      });
  });
});

app.listen(3000, () => {
  console.log("Slušam 3000 port!");
});