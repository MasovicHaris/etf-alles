package ba.unsa.etf.rpr.zadaca2;

import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.*;

class KorisniciModelTest {
    @Test
    void konstruktor() {
        KorisniciModel m = new KorisniciModel();
        assertNull(m.getTrenutniKorisnik());
        assertTrue(m.getKorisnici().isEmpty());
    }

    @Test
    void napuni() {
        KorisniciModel m = new KorisniciModel();
        m.napuni();
        assertEquals(4, m.getKorisnici().size());
        assertNull(m.getTrenutniKorisnik());
    }

    @Test
    void napuni2() {
        KorisniciModel m = new KorisniciModel();
        m.napuni();
        String s = "";
        for(Korisnik k : m.getKorisnici())
            s += k;
        String expected = "Ljubović VedranDelić AmraSijerčić TarikFejzić Rijad";
        assertEquals(expected, s);
    }

    @Test
    void trenutniKorisnik() {
        KorisniciModel m = new KorisniciModel();
        m.napuni();
        m.setTrenutniKorisnik(m.getKorisnici().get(0));
        String s = "" + m.getTrenutniKorisnik();
        assertEquals("Ljubović Vedran", s);
    }


    @Test
    void promijeniTrenutniKorisnik() {
        KorisniciModel m = new KorisniciModel();
        m.napuni();
        m.setTrenutniKorisnik(m.getKorisnici().get(2));
        m.getTrenutniKorisnik().setIme("aaaaa");
        assertEquals("aaaaa", m.getKorisnici().get(2).getIme());
    }}