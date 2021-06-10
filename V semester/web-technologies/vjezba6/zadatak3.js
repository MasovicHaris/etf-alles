const http = require('http');
const fs = require('fs');
const path = require('path');
const url = require('url');

http.createServer((req, res) => {
    if (req.method == 'GET' && req.url == '/dajPodatkeJson') {
        fs.readFile('imenik.csv', (err, contents) => {  
            if (err) {
                res.writeHead(504, {'Content-Type': 'application/json'});
                throw err;
            }
            let spisakLjudi = contents.toString().split("\n");
            let nizObjekata = [];
            for(let i=0; i < spisakLjudi.length; ++i){
                let parametri = spisakLjudi[i].split(",");
                let objekat = { ime : parametri[0], prezime : parametri[1], adresa : parametri[2], broj_telefona : parametri[3] };
                nizObjekata.push(objekat);
            }
            res.writeHead(200, {'Content-Type': 'application/json'});
            res.end(JSON.stringify(nizObjekata));
        });
    }
    else if (req.method == 'GET' && req.url == '/'){
        fs.readFile(path.join(__dirname, 'index.html'),function (err, data){
            res.writeHead(200, {'Content-Type': 'text/html'});
            res.end(data.toString());
        });
    } else if (req.method == 'POST' && req.url == '/'){
        let tijeloZahtjeva = '';
        req.on('data', (data) => {
            tijeloZahtjeva += data;
        });
        req.on('end', () => {
            //primljen čitav zahtjev
            let parametri = new url.URLSearchParams(tijeloZahtjeva);
            let novaLinija = parametri.get('ime') + "," + parametri.get('prezime') + "," + parametri.get('adresa') + "," +
                parametri.get('broj_telefona') + "\n";
            fs.appendFile('imenik.csv', novaLinija, (err) => {
                if (err) throw err;
                console.log("Novi red uspješno dodan!");
                fs.readFile(path.join(__dirname, 'prikaz.html'),function (err, data){
                    res.writeHead(200, {'Content-Type': 'text/html'});
                    res.end(data.toString());
                });
            });
        });
    }
}).listen(8080);
 