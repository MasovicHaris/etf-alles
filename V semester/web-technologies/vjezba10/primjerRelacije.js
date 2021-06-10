const db = require('./db.js')


function primjeriUpita(){
   //lista knjiga ive andrica
    db.autor.findOne({where:{ime:'Ivo Andric'}}).then(function(andric){
        andric.getKnjige().then(function(resSet){
            console.log("Lista knjiga ive andrica:");
            resSet.forEach(knjiga => {
                console.log("\t"+knjiga.naziv);
            });
        });

        //lista knjiga ive andrica iz biblioteke u Titovoj
        db.biblioteka.findOne({where:{adresa:'Titova 1'}}).then(function(titova){
            andric.getKnjige({where:{bibliotekaId:titova.id}}).then(function(resSet){
                console.log("Lista knjiga ive andrica iz biblioteke u titovoj");
                resSet.forEach(knjiga => {
                    console.log("\t"+knjiga.naziv);
                });               
            });
        });
    });

    //lista knjiga iz biblioteke u ulici Zmaja od Bosne
    db.biblioteka.findOne({where:{adresa:'Zmaja od Bosne bb'}}).then(function(zmajabb){
        zmajabb.getKnjigeBiblioteke().then(function(resSet){
            console.log("lista knjiga iz biblioteke u ulici Zmaja od Bosne");
            resSet.forEach(knjiga => {
                console.log("\t"+knjiga.naziv);
            });
        });
    });

    //lista autora knjige sa nazivom Zajednicka knjiga
    db.knjiga.findOne({where:{naziv:'Zajednicka knjiga'}}).then(function(zknjiga){
        zknjiga.getAutori().then(function(resSet){
            console.log("lista autora knjige sa nazivom Zajednicka knjiga");
            resSet.forEach(autor => {
                console.log("\t"+autor.ime);
            });
        });    
    });

    //kreiranje knjige Modra rijeka (ako ne postoji), dodjeljivanje autora i dodjeljivanje knjige biblioteci
    db.knjiga.findOrCreate({where:{naziv:'Modra rijeka',broj:9}}).then(function(mrijeka){
        console.log('kreiranje knjige Modra rijeka (ako ne postoji), dodjeljivanje autora i dodjeljivanje knjige biblioteci');
        mrijeka=mrijeka[0];
        db.autor.findOne({where:{ime:'Mak Dizdar'}}).then(function(mdizdar){
            mrijeka.addAutori([mdizdar]).then(function(redIzMedjutabele){
                db.biblioteka.findOne({where:{adresa:'Titova 1'}}).then(function(titova){
                    titova.addKnjigeBiblioteke([mrijeka]);
                });
            });
        });
    });
    //na slican nacin mozete i uklanjati autore sa removeAutori ili knjige iz biblioteke sa removeKnjigeBiblioteke
}

primjeriUpita();

