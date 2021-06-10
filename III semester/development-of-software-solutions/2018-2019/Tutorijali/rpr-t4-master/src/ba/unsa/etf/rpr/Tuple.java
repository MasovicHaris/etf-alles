package ba.unsa.etf.rpr;

public class Tuple<T1, T2, T3, T4> {
    private T1 item1 = null;
    private T2 item2 = null;
    private T3 item3 = null;
    private T4 item4 = null;
    Tuple(T1 item1, T2 item2, T3 item3, T4 item4){
        if(item1 == null || item2 == null || item3 == null || item4 == null) throw new IllegalArgumentException();
        this.item1 = item1;
        this.item2 = item2;
        this.item3 = item3;
        this.item4 = item4;
    }

    public T1 getItem1() {
        return item1;
    }

    public T2 getItem2() {
        return item2;
    }

    public T3 getItem3() {
        return item3;
    }

    public T4 getItem4() {
        return item4;
    }

}
