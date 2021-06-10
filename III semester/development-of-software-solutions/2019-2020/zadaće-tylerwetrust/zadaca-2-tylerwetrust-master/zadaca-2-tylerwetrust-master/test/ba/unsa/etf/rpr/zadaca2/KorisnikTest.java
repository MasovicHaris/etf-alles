package ba.unsa.etf.rpr.zadaca2;

import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.*;

class KorisnikTest {
    @Test
    void konstruktor() {
        Korisnik k = new Korisnik("ime", "prezime", "email", "username", "password");
        assertEquals("ime", k.getIme());
        assertEquals("prezime", k.getPrezime());
        assertEquals("email", k.getEmail());
        assertEquals("username", k.getUsername());
        assertEquals("password", k.getPassword());
    }

    @Test
    void toStringTest() {
        Korisnik k = new Korisnik("ime", "prezime", "email", "username", "password");
        String s = "" + k;
        assertEquals("prezime ime", s);
    }

    @Test
    void setteri() {
        Korisnik k = new Korisnik("ime", "prezime", "email", "username", "password");
        k.setIme("a");
        k.setPrezime("b");
        k.setEmail("c");
        k.setUsername("d");
        k.setPassword("e");
        assertEquals("a", k.getIme());
        assertEquals("b", k.getPrezime());
        assertEquals("c", k.getEmail());
        assertEquals("d", k.getUsername());
        assertEquals("e", k.getPassword());
    }
}