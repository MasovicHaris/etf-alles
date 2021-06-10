using System;
using System.Collections.Generic;
using System.Data;
using System.Data.Entity;
using System.Linq;
using System.Net;
using System.Web;
using System.Web.Mvc;
using Vicinor.Model;
using Vicinor.Models;

namespace Vicinor.Controllers
{
    public class KorisnikUSistemusController : Controller
    {
        private VicinorContext db = new VicinorContext();

        // GET: KorisnikUSistemus
        public ActionResult Index()
        {
            return View(db.KorisnikUSistemu.ToList());
        }

        // GET: KorisnikUSistemus/Details/5
        public ActionResult Details(int? id)
        {
            if (id == null)
            {
                return new HttpStatusCodeResult(HttpStatusCode.BadRequest);
            }
            KorisnikUSistemu korisnikUSistemu = db.Korisnik.OfType<KorisnikUSistemu>().SingleOrDefault(s => s.KorisnikId == id);
            if (korisnikUSistemu == null)
            {
                return HttpNotFound();
            }
            return View(korisnikUSistemu);
        }

        // GET: KorisnikUSistemus/Create
        public ActionResult Create()
        {
            return View();
        }

        // POST: KorisnikUSistemus/Create
        // To protect from overposting attacks, please enable the specific properties you want to bind to, for 
        // more details see http://go.microsoft.com/fwlink/?LinkId=317598.
        [HttpPost]
        [ValidateAntiForgeryToken]
        public ActionResult Create([Bind(Include = "KorisnikId,Password,Username")] KorisnikUSistemu korisnikUSistemu)
        {
            if (ModelState.IsValid)
            {
                db.Korisnik.Add(korisnikUSistemu);
                db.SaveChanges();
                return RedirectToAction("Index");
            }

            return View(korisnikUSistemu);
        }

        // GET: KorisnikUSistemus/Edit/5
        public ActionResult Edit(int? id)
        {
            if (id == null)
            {
                return new HttpStatusCodeResult(HttpStatusCode.BadRequest);
            }
            KorisnikUSistemu korisnikUSistemu = db.Korisnik.OfType<KorisnikUSistemu>().SingleOrDefault(s => s.KorisnikId == id);
            if (korisnikUSistemu == null)
            {
                return HttpNotFound();
            }
            return View(korisnikUSistemu);
        }

        // POST: KorisnikUSistemus/Edit/5
        // To protect from overposting attacks, please enable the specific properties you want to bind to, for 
        // more details see http://go.microsoft.com/fwlink/?LinkId=317598.
        [HttpPost]
        [ValidateAntiForgeryToken]
        public ActionResult Edit([Bind(Include = "KorisnikId,Password,Username")] KorisnikUSistemu korisnikUSistemu)
        {
            if (ModelState.IsValid)
            {
                db.Entry(korisnikUSistemu).State = EntityState.Modified;
                db.SaveChanges();
                return RedirectToAction("Index");
            }
            return View(korisnikUSistemu);
        }

        // GET: KorisnikUSistemus/Delete/5
        public ActionResult Delete(int? id)
        {
            if (id == null)
            {
                return new HttpStatusCodeResult(HttpStatusCode.BadRequest);
            }
            KorisnikUSistemu korisnikUSistemu = db.Korisnik.OfType<KorisnikUSistemu>().SingleOrDefault(s => s.KorisnikId == id);
            if (korisnikUSistemu == null)
            {
                return HttpNotFound();
            }
            return View(korisnikUSistemu);
        }

        // POST: KorisnikUSistemus/Delete/5
        [HttpPost, ActionName("Delete")]
        [ValidateAntiForgeryToken]
        public ActionResult DeleteConfirmed(int id)
        {
            KorisnikUSistemu korisnikUSistemu = db.Korisnik.OfType<KorisnikUSistemu>().SingleOrDefault(s => s.KorisnikId == id);
            db.KorisnikUSistemu.Remove(korisnikUSistemu);
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
    }
}
