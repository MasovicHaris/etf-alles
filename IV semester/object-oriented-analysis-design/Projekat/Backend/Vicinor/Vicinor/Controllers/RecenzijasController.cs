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
    public class RecenzijasController : Controller
    {
        private VicinorContext db = new VicinorContext();

        // GET: Recenzijas
        public ActionResult Index()
        {
            return View(db.Recenzija.ToList());
        }

        // GET: Recenzijas/Details/5
        public ActionResult Details(int? id)
        {
            if (id == null)
            {
                return new HttpStatusCodeResult(HttpStatusCode.BadRequest);
            }
            Recenzija recenzija = db.Recenzija.Find(id);
            if (recenzija == null)
            {
                return HttpNotFound();
            }
            return View(recenzija);
        }

        // GET: Recenzijas/Create
        public ActionResult Create()
        {
            return View();
        }

        // POST: Recenzijas/Create
        // To protect from overposting attacks, please enable the specific properties you want to bind to, for 
        // more details see http://go.microsoft.com/fwlink/?LinkId=317598.
        [HttpPost]
        [ValidateAntiForgeryToken]
        public ActionResult Create([Bind(Include = "RecenzijaId,Comment,StarRating,TimeOfRez")] Recenzija recenzija)
        {
            if (ModelState.IsValid)
            {
                db.Recenzija.Add(recenzija);
                db.SaveChanges();
                return RedirectToAction("Index");
            }

            return View(recenzija);
        }

        // GET: Recenzijas/Edit/5
        public ActionResult Edit(int? id)
        {
            if (id == null)
            {
                return new HttpStatusCodeResult(HttpStatusCode.BadRequest);
            }
            Recenzija recenzija = db.Recenzija.Find(id);
            if (recenzija == null)
            {
                return HttpNotFound();
            }
            return View(recenzija);
        }

        // POST: Recenzijas/Edit/5
        // To protect from overposting attacks, please enable the specific properties you want to bind to, for 
        // more details see http://go.microsoft.com/fwlink/?LinkId=317598.
        [HttpPost]
        [ValidateAntiForgeryToken]
        public ActionResult Edit([Bind(Include = "RecenzijaId,Comment,StarRating,TimeOfRez")] Recenzija recenzija)
        {
            if (ModelState.IsValid)
            {
                db.Entry(recenzija).State = EntityState.Modified;
                db.SaveChanges();
                return RedirectToAction("Index");
            }
            return View(recenzija);
        }

        // GET: Recenzijas/Delete/5
        public ActionResult Delete(int? id)
        {
            if (id == null)
            {
                return new HttpStatusCodeResult(HttpStatusCode.BadRequest);
            }
            Recenzija recenzija = db.Recenzija.Find(id);
            if (recenzija == null)
            {
                return HttpNotFound();
            }
            return View(recenzija);
        }

        // POST: Recenzijas/Delete/5
        [HttpPost, ActionName("Delete")]
        [ValidateAntiForgeryToken]
        public ActionResult DeleteConfirmed(int id)
        {
            Recenzija recenzija = db.Recenzija.Find(id);
            db.Recenzija.Remove(recenzija);
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
