const http = require('http');
const fs = require('fs');

http.createServer((req, res) => {
    if (req.method == 'GET') {
        let myURL = new URL("localhost:8080" + req.url);
        let searchParametar = myURL.searchParams.get('q');
        fs.readFile('imenik.csv', (err, contents) => {
            if (err) {
                res.writeHead(504, {'Content-Type': 'application/json'});
                throw err;
            }
            let spisakLjudi = contents.toString().split("\n");
            let nizObjekata = [];
            for (let i = 0; i < spisakLjudi.length; ++i) {
                let parametri = spisakLjudi[i].split(",");
                let objekat = { ime: parametri[0], prezime: parametri[1], adresa: parametri[2], brTel: parametri[3] };
                if(objekat.ime.includes(searchParametar)) nizObjekata.push(objekat);
            }
            res.writeHead(200, { 'Content-Type': 'application/json' });
            res.end(JSON.stringify(nizObjekata));
        });
    }
    if(req.method=='POST' && req.url == '/json'){
        let tijeloZahtjeva = '';
       req.on('data',(data) => { tijeloZahtjeva += data; });
       req.on('end',() => {
           //primljen čitav zahtjev
           var parametri = JSON.parse(tijeloZahtjeva);
           let novaLinija = parametri.ime + "," + parametri.prezime + "," + parametri.adresa + "," 
           + parametri.broj_telefona + "\n";
           fs.appendFile('imenik.csv', novaLinija , (err) => {
               if(err) throw err;
               console.log("Novi red uspješno dodan!");
               res.writeHead(200,{});
               res.end(parametri.toString());
           });
       });
    }
}).listen(8080);