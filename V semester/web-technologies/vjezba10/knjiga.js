const Sequelize = require("sequelize");

module.exports = function(sequelize,DataTypes){
    const Knjiga = sequelize.define("knjiga",{
        naziv:Sequelize.STRING,
        broj:Sequelize.INTEGER
    })
    return Knjiga;
};