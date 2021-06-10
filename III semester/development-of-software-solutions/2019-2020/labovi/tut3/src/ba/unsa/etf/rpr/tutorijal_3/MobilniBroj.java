package ba.unsa.etf.rpr.tutorijal_3;

public class MobilniBroj extends TelefonskiBroj{
    private String broj;
    public MobilniBroj(int mobilnaMreza, String broj)
    {
        this.broj = "0" + mobilnaMreza + "/" + broj;
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
