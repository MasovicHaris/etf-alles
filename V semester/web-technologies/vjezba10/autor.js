const Sequelize = require("sequelize");

module.exports = function(sequelize,DataTypes){
    const Autor = sequelize.define("autor",{
        ime:Sequelize.STRING
    })
    return Autor;
};
