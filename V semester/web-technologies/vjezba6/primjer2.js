const http = require('http');
const fs = require('fs');
const url = require('url');

http.createServer((req,res) => {
   if(req.method=='POST' && req.url == '/'){
       let tijeloZahtjeva = '';
       req.on('data',(data) => { tijeloZahtjeva += data; });
       req.on('end',() => {
           //primljen čitav zahtjev
           let parametri = new url.URLSearchParams(tijeloZahtjeva);
           let novaLinija = parametri.get('ime') + "," + parametri.get('prezime') + "," + parametri.get('adresa') + "," 
           + parametri.get('broj_telefona') + "\n";
           fs.appendFile('imenik.csv', novaLinija , (err) => {
               if(err) throw err;
               console.log("Novi red uspješno dodan!");
               res.writeHead(200,{});
               res.end(parametri.toString());
           });
       });
    }
}).listen(8080);