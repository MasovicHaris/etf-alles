var http = require('http');

http.createServer(function (req, res) {
    res.writeHead(200, {'Content-Type': 'text/html'});
    res.write('<h1>Putanja zahtjeva: '+req.url+'</h1>');
    res.end('<b>Metoda:'+req.method+'</b>')
}).listen(8080);