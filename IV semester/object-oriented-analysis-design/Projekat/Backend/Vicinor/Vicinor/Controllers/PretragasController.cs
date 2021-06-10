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
    public class PretragasController : Controller
    {
        private VicinorContext db = new VicinorContext();

        // GET: Pretragas
        public ActionResult Index()
        {
            return View(db.Pretraga.ToList());
        }

        // GET: Pretragas/Details/5
        public ActionResult Details(int? id)
        {
            if (id == null)
            {
                return new HttpStatusCodeResult(HttpStatusCode.BadRequest);
            }
            Pretraga pretraga = db.Pretraga.Find(id);
            if (pretraga == null)
            {
                return HttpNotFound();
            }
            return View(pretraga);
        }

        // GET: Pretragas/Create
        public ActionResult Create()
        {
            return View();
        }

        // POST: Pretragas/Create
        // To protect from overposting attacks, please enable the specific properties you want to bind to, for 
        // more details see http://go.microsoft.com/fwlink/?LinkId=317598.
        [HttpPost]
        [ValidateAntiForgeryToken]
        public ActionResult Create([Bind(Include = "PretragaId,TimeOfSearch")] Pretraga pretraga)
        {
            if (ModelState.IsValid)
            {
                db.Pretraga.Add(pretraga);
                db.SaveChanges();
                return RedirectToAction("Index");
            }

            return View(pretraga);
        }

        // GET: Pretragas/Edit/5
        public ActionResult Edit(int? id)
        {
            if (id == null)
            {
                return new HttpStatusCodeResult(HttpStatusCode.BadRequest);
            }
            Pretraga pretraga = db.Pretraga.Find(id);
            if (pretraga == null)
            {
                return HttpNotFound();
            }
            return View(pretraga);
        }

        // POST: Pretragas/Edit/5
        // To protect from overposting attacks, please enable the specific properties you want to bind to, for 
        // more details see http://go.microsoft.com/fwlink/?LinkId=317598.
        [HttpPost]
        [ValidateAntiForgeryToken]
        public ActionResult Edit([Bind(Include = "PretragaId,TimeOfSearch")] Pretraga pretraga)
        {
            if (ModelState.IsValid)
            {
                db.Entry(pretraga).State = EntityState.Modified;
                db.SaveChanges();
                return RedirectToAction("Index");
            }
            return View(pretraga);
        }

        // GET: Pretragas/Delete/5
        public ActionResult Delete(int? id)
        {
            if (id == null)
            {
                return new HttpStatusCodeResult(HttpStatusCode.BadRequest);
            }
            Pretraga pretraga = db.Pretraga.Find(id);
            if (pretraga == null)
            {
                return HttpNotFound();
            }
            return View(pretraga);
        }

        // POST: Pretragas/Delete/5
        [HttpPost, ActionName("Delete")]
        [ValidateAntiForgeryToken]
        public ActionResult DeleteConfirmed(int id)
        {
            Pretraga pretraga = db.Pretraga.Find(id);
            db.Pretraga.Remove(pretraga);
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
