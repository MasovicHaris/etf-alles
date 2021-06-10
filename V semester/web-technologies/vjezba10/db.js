const Sequelize = require("sequelize");
const sequelize = new Sequelize("vezeWT","root","root",{host:"127.0.0.1",dialect:"mysql",logging:false});
const db={};

db.Sequelize = Sequelize;  
db.sequelize = sequelize;

//import modela
db.autor = sequelize.import(__dirname+'/autor.js');
db.knjiga = sequelize.import(__dirname+'/knjiga.js');
db.biblioteka = sequelize.import(__dirname+'/biblioteka.js');

//relacije
// Veza 1-n vise knjiga se moze nalaziti u biblioteci
db.biblioteka.hasMany(db.knjiga,{as:'knjigeBiblioteke'});

// Veza n-m autor moze imati vise knjiga, a knjiga vise autora
db.autorKnjiga=db.knjiga.belongsToMany(db.autor,{as:'autori',through:'autor_knjiga',foreignKey:'knjigaId'});
db.autor.belongsToMany(db.knjiga,{as:'knjige',through:'autor_knjiga',foreignKey:'autorId'});


module.exports=db;