using System;
using System.Collections.Generic;
using System.Data;
using System.Data.Entity;
using System.Linq;
using System.Net;
using System.Text;
using System.Web;
using System.Web.Mvc;
using Vicinor.Model;
using Vicinor.Models;


namespace Vicinor.Controllers
{
    public class RegistrovaniKorisniksController : Controller
    {
        private VicinorContext db = new VicinorContext();

        // GET: RegistrovaniKorisniks
        public ActionResult Index()
        {
            return View( db.RegistrovaniKorisnik.ToList());
        }

        // GET: RegistrovaniKorisniks/Details/5
        public ActionResult Details(int? id)
        {
            if (id == null)
            {
                return new HttpStatusCodeResult(HttpStatusCode.BadRequest);
            }
            RegistrovaniKorisnik registrovaniKorisnik = db.Korisnik.OfType<RegistrovaniKorisnik>().SingleOrDefault(s => s.KorisnikId == id);
            if (registrovaniKorisnik == null)
            {
                return HttpNotFound();
            }
            return View(registrovaniKorisnik);
        }

        // GET: RegistrovaniKorisniks/Create
        public ActionResult Create()
        {
            return View();
        }
        [HttpPost]
        [ValidateAntiForgeryToken]
        public ActionResult Create([Bind(Include = "KorisnikId,Password,Username,FirstName,LastName,Email,Banned,DateOfBirth,Image")] RegistrovaniKorisnik registrovaniKorisnik)
        {
            if (ModelState.IsValid)
            {
                db.Korisnik.Add(registrovaniKorisnik);
                db.SaveChanges();
                return RedirectToAction("Index");
            }

            return View(registrovaniKorisnik);
        }
        
        // POST: RegistrovaniKorisniks/Create
        // To protect from overposting attacks, please enable the specific properties you want to bind to, for 
        // more details see http://go.microsoft.com/fwlink/?LinkId=317598.
        [HttpPost]
        public void Add(string Password, string Username, string FirstName, string LastName, string Email,Boolean Banned,DateTime DateOfBirth,string Image)
        {
            RegistrovaniKorisnik registrovaniKorisnik = new RegistrovaniKorisnik(Password, Username, FirstName, LastName, Email, Banned,DateOfBirth, EncodeBase64(Image));
            db.RegistrovaniKorisnik.Add(registrovaniKorisnik);
            db.SaveChanges();
        }
        public byte[] EncodeBase64(string data)
        {
            string s = data.Trim().Replace(" ", "+");
            if (s.Length % 4 > 0)
                s = s.PadRight(s.Length + 4 - s.Length % 4, '=');
            return (Convert.FromBase64String(s));
        }

        // GET: RegistrovaniKorisniks/Edit/5
        public ActionResult Edit(int? id)
        {
            if (id == null)
            {
                return new HttpStatusCodeResult(HttpStatusCode.BadRequest);
            }
            RegistrovaniKorisnik registrovaniKorisnik = db.Korisnik.OfType<RegistrovaniKorisnik>().SingleOrDefault(s => s.KorisnikId == id);
            if (registrovaniKorisnik == null)
            {
                return HttpNotFound();
            }
            return View(registrovaniKorisnik);
        }

        // POST: RegistrovaniKorisniks/Edit/5
        // To protect from overposting attacks, please enable the specific properties you want to bind to, for 
        // more details see http://go.microsoft.com/fwlink/?LinkId=317598.
        [HttpPost]
        [ValidateAntiForgeryToken]
        public ActionResult Edit([Bind(Include = "KorisnikId,Password,Username,FirstName,LastName,Email,Banned,DateOfBirth,Image")] RegistrovaniKorisnik registrovaniKorisnik)
        {
            if (ModelState.IsValid)
            {
                var lista = new List<Restoran>();
                
                db.Entry(registrovaniKorisnik).State = EntityState.Modified;
                db.SaveChanges();
                return RedirectToAction("Index");
            }
            return View(registrovaniKorisnik);
        }

        // GET: RegistrovaniKorisniks/Delete/5
        public ActionResult Delete(int? id)
        {
            if (id == null)
            {
                return new HttpStatusCodeResult(HttpStatusCode.BadRequest);
            }
            RegistrovaniKorisnik registrovaniKorisnik = db.Korisnik.OfType<RegistrovaniKorisnik>().SingleOrDefault(s => s.KorisnikId == id);
            if (registrovaniKorisnik == null)
            {
                return HttpNotFound();
            }
            return View(registrovaniKorisnik);
        }

        // POST: RegistrovaniKorisniks/Delete/5
        [HttpPost, System.Web.Http.ActionName("Delete")]
        [ValidateAntiForgeryToken]
        public ActionResult DeleteConfirmed(int id)
        {
            RegistrovaniKorisnik registrovaniKorisnik = db.Korisnik.OfType<RegistrovaniKorisnik>().SingleOrDefault(s => s.KorisnikId == id);
            db.RegistrovaniKorisnik.Remove(registrovaniKorisnik);
            db.SaveChanges();
            return RedirectToAction("Index");
        }

        // PUT: RegistrovaniKorisniks/BanUser/3
        [HttpPut]
        public void BanUser(int id)
        {
            db.Korisnik.OfType<RegistrovaniKorisnik>().SingleOrDefault(s => s.KorisnikId == id).Banned = true;
            db.SaveChanges();
        }

        // PUT: RegistrovaniKorisniks/UnbanUser/3
        [HttpPut]
        public void UnbanUser(int id)
        {
            db.Korisnik.OfType<RegistrovaniKorisnik>().SingleOrDefault(s => s.KorisnikId == id).Banned = false;
            db.SaveChanges();
        }

        // PUT: RegistrovaniKorisniks/changeUsername/3
        [HttpPut]
        public void changeUsername(int id, String username)
        {
            db.Korisnik.OfType<RegistrovaniKorisnik>().SingleOrDefault(s => s.KorisnikId == id).Username = username;
            db.SaveChanges();
        }

        // PUT: RegistrovaniKorisniks/changePassword/3
        [HttpPut]
        public void changePassword(int id, String password)
        {
            if (password.Length > 0)
            {
                db.Korisnik.OfType<RegistrovaniKorisnik>().SingleOrDefault(s => s.KorisnikId == id).Password = password;
                db.SaveChanges();
            }
           
        }

        [HttpPut]
        public void changeEmail(int id, String email)
        {
            db.Korisnik.OfType<RegistrovaniKorisnik>().SingleOrDefault(s => s.KorisnikId == id).Email = email;
            db.SaveChanges();
        }

        [HttpPut]
        public void changeFirstName(int id, String fName)
        {
            db.Korisnik.OfType<RegistrovaniKorisnik>().SingleOrDefault(s => s.KorisnikId == id).FirstName = fName;
            db.SaveChanges();
        }

        [HttpPut]
        public void changeLastName(int id, String lName)
        {
            db.Korisnik.OfType<RegistrovaniKorisnik>().SingleOrDefault(s => s.KorisnikId == id).LastName = lName;
            db.SaveChanges();
        }



        protected override void Dispose(bool disposing)
        {
            if (disposing)
            {
                db.Dispose();
            }
            base.Dispose(disposing);
        }

        // [Route("RegistrovaniKorisniks")]
        public JsonResult GetAccount(string username, string password)
        {
            RegistrovaniKorisnik registrovaniKorisnik = db.Korisnik.OfType<RegistrovaniKorisnik>().SingleOrDefault(s => s.Username == username && s.Password == password);

            if (registrovaniKorisnik == null)
            {
                return Json(0, JsonRequestBehavior.AllowGet);
            }
            return Json(registrovaniKorisnik, JsonRequestBehavior.AllowGet);
        }
        [System.Web.Http.HttpGet]
        public JsonResult GetAll()
        {
            List<RegistrovaniKorisnik> registrovaniKorisnici = db.Korisnik.OfType<RegistrovaniKorisnik>().ToList();
            if (registrovaniKorisnici == null)
            {
                return Json(0, JsonRequestBehavior.AllowGet);
            }
            return Json(registrovaniKorisnici, JsonRequestBehavior.AllowGet);
        }
        [System.Web.Http.HttpGet]
        public JsonResult GetFavList(int id)
        {
           RegistrovaniKorisnik registrovaniKorisnici = db.Korisnik.OfType<RegistrovaniKorisnik>().SingleOrDefault(s => s.KorisnikId == id);

            if (registrovaniKorisnici == null)
            {
                return Json(0, JsonRequestBehavior.AllowGet);
            }
            return Json(registrovaniKorisnici.ListOfRestaurants, JsonRequestBehavior.AllowGet);
        }
        [HttpPut]
        public void AddRestoraunt(int id,string name,string description,string phone)
        {
            Restoran r = new Restoran();
            r.Name = name;
            r.Description = description;
            r.PhoneNumber = phone;
            db.Korisnik.OfType<RegistrovaniKorisnik>().SingleOrDefault(s => s.KorisnikId == id).ListOfRestaurants.Add(r);
          
            db.SaveChanges();
        }




    }
}
