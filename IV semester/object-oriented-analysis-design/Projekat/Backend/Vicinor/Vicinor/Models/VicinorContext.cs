using System;
using System.Collections.Generic;
using System.Data.Entity;
using System.Data.Entity.ModelConfiguration.Conventions;
using System.Linq;
using System.Web;
using Vicinor.Model;
namespace Vicinor.Models
{
    public class VicinorContext: DbContext
    {
        public VicinorContext():base("AzureConnection") 
        {

        }
        public DbSet<Administrator> Administrator { get; set; }
        public DbSet<Korisnik> Korisnik { get; set; }
        public DbSet<KorisnikUSistemu> KorisnikUSistemu { get; set; }
        public DbSet<Lokacija> Lokacija { get; set; }
        public DbSet<NeregistrovaniKorisnik> NeregistrovaniKorisnik { get; set; }
        public DbSet<Pretraga> Pretraga { get; set; }
        public DbSet<Recenzija> Recenzija { get; set; }
        public DbSet<RegistrovaniKorisnik> RegistrovaniKorisnik { get; set; }
        public DbSet<Restoran> Restoran { get; set; }
        protected override void OnModelCreating(DbModelBuilder modelBuilder) {
            modelBuilder.Conventions.Remove<PluralizingTableNameConvention>();
        }


    }
}