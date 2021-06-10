package ba.unsa.etf.rpr.tutorijal_3;

public class MedunarodniBroj extends TelefonskiBroj {
    private String broj;
    public MedunarodniBroj(String drzava, String broj)
    {
        this.broj += drzava + broj;
    }
    @Override
    public String ispisi()
    {
        return broj;
    }
    @Override
    public int hashCode()
    {
        return broj.hashCode();
    }
}
