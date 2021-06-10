const db = require('./db.js')
db.sequelize.sync({force:true}).then(function(){
    inicializacija().then(function(){
        console.log("Gotovo kreiranje tabela i ubacivanje pocetnih podataka!");
        process.exit();
    });
});
function inicializacija(){
    var autor1,autor2;
    var autoriListaPromisea=[];
    var knjigeListaPromisea=[];
    var bibliotekeListaPromisea=[];
    return new Promise(function(resolve,reject){
    autoriListaPromisea.push(db.autor.create({ime:'Ivo Andric'}));
    autoriListaPromisea.push(db.autor.create({ime:'Mak Dizdar'}));
    Promise.all(autoriListaPromisea).then(function(autori){
        var andric=autori.filter(function(a){return a.ime==='Ivo Andric'})[0];
        var dizdar=autori.filter(function(a){return a.ime==='Mak Dizdar'})[0];

        knjigeListaPromisea.push(
            db.knjiga.create({naziv:'Prokleta avlija',broj:10}).then(function(k){
                k.setAutori([andric]);
                return new Promise(function(resolve,reject){resolve(k);});
            })
        );
        knjigeListaPromisea.push(
            db.knjiga.create({naziv:'Travnicka hronika',broj:4}).then(function(k){
                k.setAutori([andric]);
                return new Promise(function(resolve,reject){resolve(k);});
            })
        );
        knjigeListaPromisea.push(
            db.knjiga.create({naziv:'Kameni spavac',broj:6}).then(function(k){
                k.setAutori([dizdar]);
                return new Promise(function(resolve,reject){resolve(k);});
            })
        );
        knjigeListaPromisea.push(
            db.knjiga.create({naziv:'Zajednicka knjiga',broj:0}).then(function(k){
                k.setAutori([andric,dizdar]);
                return new Promise(function(resolve,reject){resolve(k);});
            })
        );
        Promise.all(knjigeListaPromisea).then(function(knjige){
            var pavlija=knjige.filter(function(k){return k.naziv==='Prokleta avlija'})[0];
            var thronika=knjige.filter(function(k){return k.naziv==='Travnicka hronika'})[0];
            var kspavac=knjige.filter(function(k){return k.naziv==='Kameni spavac'})[0];
            var zknjiga=knjige.filter(function(k){return k.naziv==='Zajednicka knjiga'})[0];
            bibliotekeListaPromisea.push(
                db.biblioteka.create({adresa:'Titova 1'}).then(function(b){
                    return b.setKnjigeBiblioteke([pavlija,thronika]).then(function(){
                    return new Promise(function(resolve,reject){resolve(b);});
                    });
                })
            );
            bibliotekeListaPromisea.push(
                db.biblioteka.create({adresa:'Zmaja od Bosne bb'}).then(function(b){
                    return b.setKnjigeBiblioteke([kspavac,zknjiga]).then(function(){
                    return new Promise(function(resolve,reject){resolve(b);});
                    });
                })
            );
            Promise.all(bibliotekeListaPromisea).then(function(b){resolve(b);}).catch(function(err){console.log("Biblioteke greska "+err);});
        }).catch(function(err){console.log("Knjige greska "+err);});
    }).catch(function(err){console.log("Autori greska "+err);});   
    });
}
