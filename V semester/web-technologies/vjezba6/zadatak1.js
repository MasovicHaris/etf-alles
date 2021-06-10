const http = require('http');
const fs = require('fs');

http.createServer((req, res) => {
    if(req.method == 'GET'){
        fs.readFile('imenik.csv', (err, contents) => {  
            if (err) {
                res.writeHead(504, {'Content-Type': 'application/json'});
                throw err;
            }
            let spisakLjudi = contents.toString().split("\n");
            let nizObjekata = [];
            for(let i=0; i < spisakLjudi.length -1; ++i){
                let parametri = spisakLjudi[i].split(",");
                let objekat = { ime : parametri[0], prezime : parametri[1], adresa : parametri[2], brTel : parametri[3] };
                nizObjekata.push(objekat);
            }
            res.writeHead(200, {'Content-Type': 'application/json'});
            res.end(JSON.stringify(nizObjekata));
        });
    }
}).listen(8080);