package ba.unsa.etf.rpr;

public class Main {
     public static void main(String[] args) {
    	System.out.println("Potrebno je napraviti neki uvodni kod koji realizira igru šaha. Program neće imati neki korisnički interfejs, pošto to nije fokus u ovom trenutku. Pošto nismo radili vještačku inteligenciju, neće biti ni moguće igrati protiv računara. Zanemarićemo i neka od pravila same igre kako bi zadatak bio jednostavniji, kao što su: rokada, razmjena pijuna za druge figure, mat itd.\n" +
                "\n" +
                "Pravila igre šah se smatraju da su poznata, ako nisu predlažem da se upoznate.\n" +
                "\n" +
                "Program treba sadržavati sljedeće klase:\n" +
                "Apstraktnu klasu Chesspiece i iz nje izvedene klase: King, Queen, Rook, Bishop, Knight i Pawn. Apstraktna klasa treba sadržavati sljedeće metode (čije implementacije ćete eventualno prilagoditi u izvedenim klasama):\n" +
                "getPosition() vraća String koji predstavlja poziciju figure na tabli u obliku uobičajenom za šah npr. \"A4\", \"B5\", \"H1\" i sl.\n" +
                "getColor() vraća boju figure; pobrojani tip Color sa vrijednostima BLACK i WHITE treba biti javni statički član klase Chesspiece;\n" +
                "move(String position) pomjera figuru na novu poziciju; treba baciti izuzetak IllegalArgumentsException ako je pozicija van table ili nije u ispravnom formatu; ako potez nije dozvoljen za tu vrstu figure (za sada zanemarujemo ostale figure na ploči) treba baciti izuzetak tipa IllegalChessMoveException; metoda treba raditi sa velikim i malim slovima;\n" +
                "konstruktor klase treba imati parametre pozicija i boja; treba baciti izuzetak IllegalArgumentsException ako je pozicija van table ili nije u ispravnom formatu.\n" +
                "Klasa Board predstavlja šahovsku ploču sa figurama i u sebi drži sve trenutno aktivne figure na ploči:\n" +
                "konstruktor postavlja ploču u uobičajeno početno stanje za igru;\n" +
                "void move(Class type, Chesspiece.Color color, String position) pomjera figuru koja pripada klasi type, boje color, na poziciju datu stringom position. Ova metoda treba najprije pronaći figuru tipa type date boje među aktivnim figurama. Zatim treba pozvati njenu metodu move da provjeri da li je poziv legalan. Pošto može biti više figura iste boje i tipa, treba pronaći prvu za koju je potez legalan i povući potez. U slučaju da ne postoji niti jedna figura za koju je potez legalan treba baciti IllegalChessMoveException. Konačno treba provjeriti da li se na odredišnoj poziciji već nalazi figura. Ako se nalazi figura druge boje, ona je \"pojedena\" i treba je izbaciti, a ako se nalazi figura iste boje treba baciti IllegalChessMoveException. Također treba voditi računa da kraljica, lovac, top i pijuni ne mogu preskakati druge figure.\n" +
                "void move(String oldPosition, String newPosition) još jedna metoda za pomjeranje figure, s tim što su parametri sada stara i nova pozicija figure. Treba napraviti sve provjere kao i u prošloj metode, ali dodatno ako se na poziciji oldPosition ne nalazi niti jedna figura treba baciti izuzetak IllegalArgumentsException. Obje metode trebaju raditi sa velikim i malim slovima.\n" +
                "boolean isCheck(color) provjerava da li je igrač sa bojom color u šahu.\n" +
                "Sve navedene metode moraju biti realizirane pozivanjem metode move iz klase ChessPiece! Rješenje koje ne bude urađeno na taj način biće bodovano sa 0 bodova!\n" +
                "Klasa Program sadrži metodu main koja omogućuje igračima da povlače poteze. Korisnik unosi naizmjenično poteze bijelog i crnog igrača koristeći skraćenu (algebarsku) notaciju uz oznake figura na engleskom jeziku: K, Q, R, B i N, dok se polja označavaju malim slovom. U metodi main treba biti kreiran objekat tipa Board te koristiti prvu varijantu metode move za povlačenje poteza. U slučaju neispravnog poteza ispisati poruku \"Illegal move\" i tražiti ponovni unos. U slučaju da je nakon nekog poteza došlo do šaha treba ispisati poruku \"CHECK!!!\" što se saznaje pomoću metode isCheck.\n" +
                "Korisnik može unijeti slovo X da preda partiju. Primjer ulaza i izlaza:\n" +
                "\tWhite move: e4\n" +
                "\tBlack move: e5\n" +
                "\tWhite move: Nf3\n" +
                "\tBlack move: Nc6\n" +
                "\tWhite move: Bb5\n" +
                "\tBlack move: a6\n" +
                "\tWhite move: Ba4\n" +
                "\tBlack move: Nf6\n" +
                "\n" +
                "Zadaću treba realizirati tako što će se najprije napraviti fork projekta \"rpr-zadaca1\" koji sadrži dio testova, a zatim implementirati klase i preostale testove kako bi pokrivenost koda testovima bila 100%.\n" +
                "\n" +
                "U zadaći je obavezno pridržavati se svih pravila koja su do sada obrađena na predmetu, te će po tim pravilima biti i ocjenjivano. To uključuje:\n" +
                "ispravno imenovanje paketa, klasa, metoda i promjenljivih,\n" +
                "primjenu komentara,\n" +
                "atomic commits.\n");
    }
}
