const Sequelize = require("sequelize");

module.exports = function(sequelize,DataTypes){
    const Biblioteka = sequelize.define("biblioteka",{
        adresa:Sequelize.STRING
    });
    return Biblioteka;
};