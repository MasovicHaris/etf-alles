package ba.unsa.etf.rpr.tutorijal03;

public class FiksniBroj extends TelefonskiBroj implements Comparable {
    private Grad grad = null;
    private String broj = null;

    public Grad getGrad() {
        return grad;
    }

    public void setGrad(Grad grad) {
        this.grad = grad;
    }

    public String getBroj() {
        return broj;
    }

    public void setBroj(String broj) {
        this.broj = broj;
    }

    public FiksniBroj(Grad grad, String broj){
        setGrad(grad);
        setBroj(broj);
    }

    @Override
    public String ispisi(){
        switch (grad){
            case TRAVNIK:
                return "030/" + broj;
            case ORASJE:
                return "031/" + broj;
            case ZENICA:
                return "032/" + broj;
            case SARAJEVO:
                return "033/" + broj;
            case LIVNO:
                return "034/" + broj;
            case TUZLA:
                return "035/" + broj;
            case MOSTAR:
                return "036/" + broj;
            case BIHAC:
                return "037/" + broj;
            case GORAZDE:
                return "038/" + broj;
            case SIROKIBRIJEG:
                return "039/" + broj;
            case BRCKO:
                return "049/" + broj;
            default:
                return null;
        }
    }

    @Override
    public int hashCode() {
        return getGrad().hashCode();
    }

    @Override
    public int compareTo(Object o) {
        TelefonskiBroj o2 = (FiksniBroj) o;
        return ispisi().compareTo(o2.ispisi());
    }

    public enum Grad {
        TRAVNIK, ORASJE, ZENICA, SARAJEVO, LIVNO, TUZLA, MOSTAR, BIHAC, GORAZDE, SIROKIBRIJEG, BRCKO
    }

    @Override
    public boolean equals(Object o) {
        if(o instanceof FiksniBroj){
            return ispisi().equals(((FiksniBroj) o).ispisi());
        }
        return false;
    }
}
