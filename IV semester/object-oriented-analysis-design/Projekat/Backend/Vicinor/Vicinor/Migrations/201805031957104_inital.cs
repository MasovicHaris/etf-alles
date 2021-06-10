namespace Vicinor.Migrations
{
    using System;
    using System.Data.Entity.Migrations;
    
    public partial class inital : DbMigration
    {
        public override void Up()
        {
            CreateTable(
                "dbo.Korisnik",
                c => new
                    {
                        KorisnikId = c.Int(nullable: false, identity: true),
                        Password = c.String(),
                        Username = c.String(),
                        FirstName = c.String(),
                        LastName = c.String(),
                        Email = c.String(),
                        Banned = c.Boolean(),
                        DateOfBirth = c.DateTime(),
                        Image = c.Binary(),
                        Discriminator = c.String(nullable: false, maxLength: 128),
                        Location_LokacijaId = c.Int(),
                        Location_LokacijaId1 = c.Int(),
                    })
                .PrimaryKey(t => t.KorisnikId)
                .ForeignKey("dbo.Lokacija", t => t.Location_LokacijaId)
                .ForeignKey("dbo.Lokacija", t => t.Location_LokacijaId1)
                .Index(t => t.Location_LokacijaId)
                .Index(t => t.Location_LokacijaId1);
            
            CreateTable(
                "dbo.Restoran",
                c => new
                    {
                        RestoranId = c.Int(nullable: false, identity: true),
                        Name = c.String(),
                        Description = c.String(),
                        PhoneNumber = c.String(),
                        Image = c.Binary(),
                        Location_LokacijaId = c.Int(),
                        RegistrovaniKorisnik_KorisnikId = c.Int(),
                        Pretraga_PretragaId = c.Int(),
                    })
                .PrimaryKey(t => t.RestoranId)
                .ForeignKey("dbo.Lokacija", t => t.Location_LokacijaId)
                .ForeignKey("dbo.Korisnik", t => t.RegistrovaniKorisnik_KorisnikId)
                .ForeignKey("dbo.Pretraga", t => t.Pretraga_PretragaId)
                .Index(t => t.Location_LokacijaId)
                .Index(t => t.RegistrovaniKorisnik_KorisnikId)
                .Index(t => t.Pretraga_PretragaId);
            
            CreateTable(
                "dbo.Recenzija",
                c => new
                    {
                        RecenzijaId = c.Int(nullable: false, identity: true),
                        Comment = c.String(),
                        StarRating = c.Int(nullable: false),
                        TimeOfRez = c.DateTime(nullable: false),
                        User_KorisnikId = c.Int(),
                        Restoran_RestoranId = c.Int(),
                    })
                .PrimaryKey(t => t.RecenzijaId)
                .ForeignKey("dbo.Korisnik", t => t.User_KorisnikId)
                .ForeignKey("dbo.Restoran", t => t.Restoran_RestoranId)
                .Index(t => t.User_KorisnikId)
                .Index(t => t.Restoran_RestoranId);
            
            CreateTable(
                "dbo.Lokacija",
                c => new
                    {
                        LokacijaId = c.Int(nullable: false, identity: true),
                        X = c.Int(nullable: false),
                        Y = c.Int(nullable: false),
                    })
                .PrimaryKey(t => t.LokacijaId);
            
            CreateTable(
                "dbo.Pretraga",
                c => new
                    {
                        PretragaId = c.Int(nullable: false, identity: true),
                        TimeOfSearch = c.DateTime(nullable: false),
                        ChosenRestaurant_RestoranId = c.Int(),
                        User_KorisnikId = c.Int(),
                    })
                .PrimaryKey(t => t.PretragaId)
                .ForeignKey("dbo.Restoran", t => t.ChosenRestaurant_RestoranId)
                .ForeignKey("dbo.Korisnik", t => t.User_KorisnikId)
                .Index(t => t.ChosenRestaurant_RestoranId)
                .Index(t => t.User_KorisnikId);
            
        }
        
        public override void Down()
        {
            DropForeignKey("dbo.Pretraga", "User_KorisnikId", "dbo.Korisnik");
            DropForeignKey("dbo.Restoran", "Pretraga_PretragaId", "dbo.Pretraga");
            DropForeignKey("dbo.Pretraga", "ChosenRestaurant_RestoranId", "dbo.Restoran");
            DropForeignKey("dbo.Korisnik", "Location_LokacijaId1", "dbo.Lokacija");
            DropForeignKey("dbo.Korisnik", "Location_LokacijaId", "dbo.Lokacija");
            DropForeignKey("dbo.Restoran", "RegistrovaniKorisnik_KorisnikId", "dbo.Korisnik");
            DropForeignKey("dbo.Restoran", "Location_LokacijaId", "dbo.Lokacija");
            DropForeignKey("dbo.Recenzija", "Restoran_RestoranId", "dbo.Restoran");
            DropForeignKey("dbo.Recenzija", "User_KorisnikId", "dbo.Korisnik");
            DropIndex("dbo.Pretraga", new[] { "User_KorisnikId" });
            DropIndex("dbo.Pretraga", new[] { "ChosenRestaurant_RestoranId" });
            DropIndex("dbo.Recenzija", new[] { "Restoran_RestoranId" });
            DropIndex("dbo.Recenzija", new[] { "User_KorisnikId" });
            DropIndex("dbo.Restoran", new[] { "Pretraga_PretragaId" });
            DropIndex("dbo.Restoran", new[] { "RegistrovaniKorisnik_KorisnikId" });
            DropIndex("dbo.Restoran", new[] { "Location_LokacijaId" });
            DropIndex("dbo.Korisnik", new[] { "Location_LokacijaId1" });
            DropIndex("dbo.Korisnik", new[] { "Location_LokacijaId" });
            DropTable("dbo.Pretraga");
            DropTable("dbo.Lokacija");
            DropTable("dbo.Recenzija");
            DropTable("dbo.Restoran");
            DropTable("dbo.Korisnik");
        }
    }
}
