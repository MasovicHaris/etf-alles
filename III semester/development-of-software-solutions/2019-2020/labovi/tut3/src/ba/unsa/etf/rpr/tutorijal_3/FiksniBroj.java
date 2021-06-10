package ba.unsa.etf.rpr.tutorijal_3;

public class FiksniBroj extends TelefonskiBroj {
    public enum Grad{
        TRAVNIK, ORASJE, ZENICA, SARAJEVO,
        LIVNO, TUZLA, MOSTAR, BIHAC, GORAZDE, SIROKIBRIJEG,
        MRKONJICGRAD, BANJALUKA, PRIJEDOR, DOBOJ, SAMAC,
        BIJELJINA, ZVORNIK, PALE, FOCA, TREBINJE, BRCKO;
    }
    private String broj, pozivni;
    private Grad grad;
    public FiksniBroj(Grad grad, String broj)
    {
        this.grad=grad;
        this.broj=broj;
        pozivni="";
        switch(grad)
        {
            case TRAVNIK:
                pozivni += "030";
                break;
            case ORASJE:
                pozivni += "031";
                break;
            case ZENICA:
                pozivni += "032";
                break;
            case SARAJEVO:
                pozivni += "033";
                break;
            case LIVNO:
                pozivni += "034";
                break;
            case TUZLA:
                pozivni += "035";
                break;
            case MOSTAR:
                pozivni += "036";
                break;
            case BIHAC:
                pozivni += "037";
                break;
            case GORAZDE:
                pozivni += "038";
                break;
            case SIROKIBRIJEG:
                pozivni += "039";
                break;
            case MRKONJICGRAD:
                pozivni += "050";
                break;
            case BANJALUKA:
                pozivni += "051";
                break;
            case PRIJEDOR:
                pozivni += "052";
                break;
            case DOBOJ:
                pozivni += "053";
                break;
            case SAMAC:
                pozivni += "054";
                break;
            case BIJELJINA:
                pozivni += "055";
                break;
            case ZVORNIK:
                pozivni += "056";
                break;
            case PALE:
                pozivni += "057";
                break;
            case FOCA:
                pozivni += "058";
                break;
            case TREBINJE:
                pozivni += "059";
                break;
            case BRCKO:
                pozivni += "049";
            default:
                pozivni+="?";
                break;
        }
        pozivni=pozivni+"/"+broj;
    }
    Grad getGrad(){
        return grad;
    }
    @Override
    public String ispisi()
    {
        return pozivni;
    }
    @Override
    public int hashCode(){
        return pozivni.hashCode();
    }
}
