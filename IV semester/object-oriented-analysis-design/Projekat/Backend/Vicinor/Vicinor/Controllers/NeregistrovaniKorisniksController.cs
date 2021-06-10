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
    public class NeregistrovaniKorisniksController : Controller
    {
        private VicinorContext db = new VicinorContext();

        // GET: NeregistrovaniKorisniks
        public ActionResult Index()
        {
            return View(db.NeregistrovaniKorisnik.ToList());
        }

        // GET: NeregistrovaniKorisniks/Details/5
        public ActionResult Details(int? id)
        {
            if (id == null)
            {
                return new HttpStatusCodeResult(HttpStatusCode.BadRequest);
            }
            NeregistrovaniKorisnik neregistrovaniKorisnik = db.Korisnik.OfType<NeregistrovaniKorisnik>().SingleOrDefault(s => s.KorisnikId == id);
            if (neregistrovaniKorisnik == null)
            {
                return HttpNotFound();
            }
            return View(neregistrovaniKorisnik);
        }

        // GET: NeregistrovaniKorisniks/Create
        public ActionResult Create()
        {
            return View();
        }

        // POST: NeregistrovaniKorisniks/Create
        // To protect from overposting attacks, please enable the specific properties you want to bind to, for 
        // more details see http://go.microsoft.com/fwlink/?LinkId=317598.
        [HttpPost]
        [ValidateAntiForgeryToken]
        public ActionResult Create([Bind(Include = "KorisnikId")] NeregistrovaniKorisnik neregistrovaniKorisnik)
        {
            if (ModelState.IsValid)
            {
                db.NeregistrovaniKorisnik.Add(neregistrovaniKorisnik);
                db.SaveChanges();
                return RedirectToAction("Index");
            }

            return View(neregistrovaniKorisnik);
        }

        // GET: NeregistrovaniKorisniks/Edit/5
        public ActionResult Edit(int? id)
        {
            if (id == null)
            {
                return new HttpStatusCodeResult(HttpStatusCode.BadRequest);
            }
            NeregistrovaniKorisnik neregistrovaniKorisnik = db.Korisnik.OfType<NeregistrovaniKorisnik>().SingleOrDefault(s => s.KorisnikId == id);
            if (neregistrovaniKorisnik == null)
            {
                return HttpNotFound();
            }
            return View(neregistrovaniKorisnik);
        }

        // POST: NeregistrovaniKorisniks/Edit/5
        // To protect from overposting attacks, please enable the specific properties you want to bind to, for 
        // more details see http://go.microsoft.com/fwlink/?LinkId=317598.
        [HttpPost]
        [ValidateAntiForgeryToken]
        public ActionResult Edit([Bind(Include = "KorisnikId")] NeregistrovaniKorisnik neregistrovaniKorisnik)
        {
            if (ModelState.IsValid)
            {
                db.Entry(neregistrovaniKorisnik).State = EntityState.Modified;
                db.SaveChanges();
                return RedirectToAction("Index");
            }
            return View(neregistrovaniKorisnik);
        }

        // GET: NeregistrovaniKorisniks/Delete/5
        public ActionResult Delete(int? id)
        {
            if (id == null)
            {
                return new HttpStatusCodeResult(HttpStatusCode.BadRequest);
            }
            NeregistrovaniKorisnik neregistrovaniKorisnik = db.Korisnik.OfType<NeregistrovaniKorisnik>().SingleOrDefault(s => s.KorisnikId == id);
            if (neregistrovaniKorisnik == null)
            {
                return HttpNotFound();
            }
            return View(neregistrovaniKorisnik);
        }

        // POST: NeregistrovaniKorisniks/Delete/5
        [HttpPost, ActionName("Delete")]
        [ValidateAntiForgeryToken]
        public ActionResult DeleteConfirmed(int id)
        {
            NeregistrovaniKorisnik neregistrovaniKorisnik = db.Korisnik.OfType<NeregistrovaniKorisnik>().SingleOrDefault(s => s.KorisnikId == id);
            db.NeregistrovaniKorisnik.Remove(neregistrovaniKorisnik);
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
        public JsonResult GetAll()
        {
            List<NeregistrovaniKorisnik> registrovaniKorisnici = db.Korisnik.OfType<NeregistrovaniKorisnik>().ToList();
            if (registrovaniKorisnici == null)
            {
                return Json(0, JsonRequestBehavior.AllowGet);
            }
            return Json(registrovaniKorisnici, JsonRequestBehavior.AllowGet);
        }
    }
}
