const express = require('express');
const bodyParser = require('body-parser');
const fs = require('fs');
const app = express();
const path = require('path');
const url = require('url');

app.use(bodyParser.json());
app.use(bodyParser.urlencoded({
    extended: true
}));

// treba nam statični cs, pristupam kroz web server
app.use('/css', express.static(path.join(__dirname)));
app.use('/js', express.static(path.join(__dirname)));


app.post('/', function (req, res) {
    let tijelo = req.body;
    let novaLinija = tijelo['ime'] + "," + tijelo['prezime'] + "," + tijelo['adresa'] + "," + tijelo['broj_telefona'] + "\n";
    fs.appendFile('imenik.csv', novaLinija, (err) => {
        if (err) throw err;
        console.log("Uspiješno dodan novi red!");
        res.sendFile(path.join(__dirname, 'rezultat.html'));
    });
});

app.post('/z4', function (req, res) {
    let tijelo = req.body.objekat;
    let novaLinija = tijelo['ime'] + "," + tijelo['prezime'] + "," + tijelo['adresa'] + "," + tijelo['broj_telefona'] + "\n";
    fs.appendFile('imenik.csv', novaLinija, (err) => {
        if (err) throw err;
        console.log("Uspiješno dodan novi red!");
        res.sendFile(path.join(__dirname, 'rezultat.html'));
    });
});



app.get('/unos', (req, res) => {
    res.sendFile(path.join(__dirname, 'forma.html'));
}).post('/unos', (req, res) => {
    res.send("http://localhost:8085/unos");
});



app.post('/:ime', (req, res) => {
    fs.readFile('imenik.csv', function (err, data) {
        if (err) throw err;
        var sveOsimReda = data.toString().split('\n');
        sveOsimReda.splice(req.body.red, 1);

        fs.writeFileSync('imenik.csv', "", (err) =>{
            if (err) throw err;
        });
        for (let i = 0; i < sveOsimReda.length; ++i) {
            (function odradi(i) {
                if (sveOsimReda[i] != "") {
                    fs.appendFileSync('imenik.csv', sveOsimReda[i] + "\n", (err) => {
                        if (err) throw err;
                    });
                }
            })(i);
        }   
        res.send("OK");
    });
});

app.get('/', (req, res) => {
    res.sendFile(path.join(__dirname, 'rezultat.html'));
});

app.get('/zadatak3', (req, res) => {
    res.sendFile(path.join(__dirname, 'index.html'));
});


app.get('/zadatak4', (req, res) => {
    res.sendFile(path.join(__dirname, 'ajaxForma.html'));
});


app.get('/index/:broj', (req, res) => {
    let n = req.params.broj;
    res.sendFile(path.join(__dirname, `straniceZaLoad/stranica${n}.html`));
});


app.get('/dajPodatkeJson', (req, res) => {
    fs.readFile('imenik.csv', (err, contents) => {
        if (err) {
            res.writeHead(504, {
                'Content-Type': 'application/json'
            });
            throw err;
        }
        let spisakLjudi = contents.toString().split("\n");
        let nizObjekata = [];
        for (let i = 0; i < spisakLjudi.length; ++i) {
            let parametri = spisakLjudi[i].split(",");
            let objekat = {
                ime: parametri[0],
                prezime: parametri[1],
                adresa: parametri[2],
                broj_telefona: parametri[3]
            };
            nizObjekata.push(objekat);
        }
        res.writeHead(200, {
            'Content-Type': 'application/json'
        });
        res.end(JSON.stringify(nizObjekata));
    });
});

app.listen(8085, () => {
    console.log("Slušam 8085 port!");
});