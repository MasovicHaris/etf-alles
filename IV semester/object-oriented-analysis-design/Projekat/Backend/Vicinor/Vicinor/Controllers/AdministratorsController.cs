using System;
using System.Collections.Generic;
using System.Data;
using System.Data.Entity;
using System.Linq;
using System.Net;
using System.Threading.Tasks;
using System.Web;
using System.Web.Mvc;
using Vicinor.Model;
using Vicinor.Models;

namespace Vicinor.Controllers
{
    public class AdministratorsController : Controller
    {
        private VicinorContext db = new VicinorContext();

        // GET: Administrators
        public ActionResult Index()
        {
            return View(db.Administrator.ToList());
        }

        // GET: Administrators/Details/5
        public ActionResult Details(int? id)
        {
            if (id == null)
            {
                return new HttpStatusCodeResult(HttpStatusCode.BadRequest);
            }
            Administrator administrator = db.Korisnik.OfType<Administrator>().SingleOrDefault(s => s.KorisnikId == id);

            if (administrator == null)
            {
                return HttpNotFound();
            }
            return View(administrator);
        }

        // GET: Administrators/Create
        public ActionResult Create()
        {
            return View();
        }

        // POST: Administrators/Create
        // To protect from overposting attacks, please enable the specific properties you want to bind to, for 
        // more details see http://go.microsoft.com/fwlink/?LinkId=317598.
        [HttpPost]
        public void Create([Bind(Include = "Password,Username")] Administrator administrator)
        {
            if (ModelState.IsValid)
            {
                db.Administrator.Add(administrator);
                db.SaveChanges();
             //   return RedirectToAction("Index");
            }

           // return View(administrator);
        }

        // PUT: Administrators/Add
        [HttpPost]
        public JsonResult Add(string Password, string Username)
        {
            Administrator administrator=(new Administrator());
            administrator.Password = Password;
            administrator.Username = Username;
            db.Administrator.Add(administrator);
            db.SaveChanges();
            return Json(administrator, JsonRequestBehavior.AllowGet);
        }
        // GET: Administrators/Edit/5
        public ActionResult Edit(int? id)
        {
            if (id == null)
            {
                return new HttpStatusCodeResult(HttpStatusCode.BadRequest);
            }
            Administrator administrator = db.Korisnik.OfType<Administrator>().SingleOrDefault(s => s.KorisnikId == id);
            if (administrator == null)
            {
                return HttpNotFound();
            }
            return View(administrator);
        }

        // POST: Administrators/Edit/5
        // To protect from overposting attacks, please enable the specific properties you want to bind to, for 
        // more details see http://go.microsoft.com/fwlink/?LinkId=317598.
        [HttpPost]
        [ValidateAntiForgeryToken]
        public ActionResult Edit([Bind(Include = "KorisnikId,Password,Username")] Administrator administrator)
        {
            if (ModelState.IsValid)
            {
                db.Entry(administrator).State = EntityState.Modified;
                db.SaveChanges();
                return RedirectToAction("Index");
            }
            return View(administrator);
        }

        // GET: Administrators/Delete/5
        public ActionResult Delete(int? id)
        {
            if (id == null)
            {
                return new HttpStatusCodeResult(HttpStatusCode.BadRequest);
            }
            Administrator administrator = db.Korisnik.OfType<Administrator>().SingleOrDefault(s => s.KorisnikId == id);
            if (administrator == null)
            {
                return HttpNotFound();
            }
            return View(administrator);
        }

        // POST: Administrators/Delete/5
        [HttpPost, ActionName("Delete")]
        [ValidateAntiForgeryToken]
        public ActionResult DeleteConfirmed(int id)
        {
            Administrator administrator = db.Korisnik.OfType<Administrator>().SingleOrDefault(s => s.KorisnikId == id);
            db.Administrator.Remove(administrator);
            db.SaveChanges();
            return RedirectToAction("Index");
        }

        protected override void Dispose(bool disposing)
        {
            if (disposing)
            {
                db.Dispose();
            }
            base.Dispose(disposing);
        }

        [HttpGet]
        public JsonResult  GetAccount(string username, string password)
        {
            Administrator registrovaniKorisnik = db.Korisnik.OfType<Administrator>().SingleOrDefault(s => s.Username == username && s.Password == password);

            if (registrovaniKorisnik == null)
            {
                return Json(0, JsonRequestBehavior.AllowGet);
            }
            return Json(registrovaniKorisnik, JsonRequestBehavior.AllowGet);
        }

        // PUT: Administrators/changeUsername/3
        [HttpPut]
        public void changeUsername(int id, String username)
        {
            db.Korisnik.OfType<Administrator>().SingleOrDefault(s => s.KorisnikId == id).Username = username ;
            db.SaveChanges();
        }

        // PUT: Administrators/changePassword/3
        [HttpPut]
        public void changePassword(int id, String password)
        {
            db.Korisnik.OfType<Administrator>().SingleOrDefault(s => s.KorisnikId == id).Password = password;
            db.SaveChanges();
        }

    }
}
