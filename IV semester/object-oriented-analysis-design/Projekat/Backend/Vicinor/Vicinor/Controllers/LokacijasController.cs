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
    public class LokacijasController : Controller
    {
        private VicinorContext db = new VicinorContext();

        // GET: Lokacijas
        public ActionResult Index()
        {
            return View(db.Lokacija.ToList());
        }

        // GET: Lokacijas/Details/5
        public JsonResult Details(int? id)
        {

            if (id == null)
            {
                return Json(0, JsonRequestBehavior.AllowGet);
            }
            Lokacija lokacija = db.Lokacija.Find(id);
            if (lokacija == null)
            {
                    return Json(0, JsonRequestBehavior.AllowGet);
            }
            return Json(lokacija, JsonRequestBehavior.AllowGet);
        }

        // GET: Lokacijas/Create
        public ActionResult Create()
        {
            return View();
        }

        // POST: Lokacijas/Create
        // To protect from overposting attacks, please enable the specific properties you want to bind to, for 
        // more details see http://go.microsoft.com/fwlink/?LinkId=317598.
        [HttpPost]
        [ValidateAntiForgeryToken]
        public ActionResult Create([Bind(Include = "LokacijaId,X,Y")] Lokacija lokacija)
        {
            if (ModelState.IsValid)
            {
                db.Lokacija.Add(lokacija);
                db.SaveChanges();
                return RedirectToAction("Index");
            }

            return View(lokacija);
        }

        // GET: Lokacijas/Edit/5
        public ActionResult Edit(int? id)
        {
            if (id == null)
            {
                return new HttpStatusCodeResult(HttpStatusCode.BadRequest);
            }
            Lokacija lokacija = db.Lokacija.Find(id);
            if (lokacija == null)
            {
                return HttpNotFound();
            }
            return View(lokacija);
        }

        // POST: Lokacijas/Edit/5
        // To protect from overposting attacks, please enable the specific properties you want to bind to, for 
        // more details see http://go.microsoft.com/fwlink/?LinkId=317598.
        [HttpPost]
        [ValidateAntiForgeryToken]
        public ActionResult Edit([Bind(Include = "LokacijaId,X,Y")] Lokacija lokacija)
        {
            if (ModelState.IsValid)
            {
                db.Entry(lokacija).State = EntityState.Modified;
                db.SaveChanges();
                return RedirectToAction("Index");
            }
            return View(lokacija);
        }

        // GET: Lokacijas/Delete/5
        public ActionResult Delete(int? id)
        {
            if (id == null)
            {
                return new HttpStatusCodeResult(HttpStatusCode.BadRequest);
            }
            Lokacija lokacija = db.Lokacija.Find(id);
            if (lokacija == null)
            {
                return HttpNotFound();
            }
            return View(lokacija);
        }

        // POST: Lokacijas/Delete/5
        [HttpPost, ActionName("Delete")]
        [ValidateAntiForgeryToken]
        public ActionResult DeleteConfirmed(int id)
        {
            Lokacija lokacija = db.Lokacija.Find(id);
            db.Lokacija.Remove(lokacija);
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
