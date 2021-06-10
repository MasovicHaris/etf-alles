package ba.unsa.etf.rpr.tutorijal03;

import org.omg.Messaging.SYNC_WITH_TRANSPORT;

import java.util.Scanner;

public class Program {
	Imenik imenik = new Imenik();

	private FiksniBroj.Grad dajGrad(Integer unos){
		switch (unos){
			case 1:
				return FiksniBroj.Grad.TRAVNIK;
			case 2:
				return FiksniBroj.Grad.ORASJE;
			case 3:
				return FiksniBroj.Grad.ZENICA;
			case 4:
				return FiksniBroj.Grad.SARAJEVO;
			case 5:
				return FiksniBroj.Grad.LIVNO;
			case 6:
				return FiksniBroj.Grad.TUZLA;
			case 7:
				return FiksniBroj.Grad.MOSTAR;
			case 8:
				return FiksniBroj.Grad.BIHAC;
			case 9:
				return FiksniBroj.Grad.GORAZDE;
			case 10:
				return FiksniBroj.Grad.SIROKIBRIJEG;
			case 11:
				return FiksniBroj.Grad.BRCKO;
		}
		return null;
	}

	public void dodajBroj(){
		System.out.println("-----------------------");
		System.out.println("0. Za povratak,");
		System.out.println("1. Za Fiksni,");
		System.out.println("2. Za Mobilni,");
		System.out.println("3. Za Medjunarodni.");
		System.out.println("-----------------------");
		Scanner scanner = new Scanner(System.in);
		Integer unos = scanner.nextInt();
		String broj = null;
		switch (unos){
			case 0:
				return;
			case 1:
				System.out.println("Unesite 1.TRAVNIK, 2.ORASJE, 3.ZENICA, 4.SARAJEVO, 5.LIVNO, 6.TUZLA, 7.MOSTAR, 8.BIHAC, 9.GORAZDE, 10.SIROKIBRIJEG, 11.BRCKO");
				scanner = new Scanner(System.in);
				unos = scanner.nextInt();
				FiksniBroj.Grad grad = dajGrad(unos);
				if(grad == null) return;
				System.out.println("Unesite Broj u formatu 123-456");
				scanner = new Scanner(System.in);
				broj = scanner.nextLine();
				System.out.println("Unesite ime i prezime osobe");
				scanner = new Scanner(System.in);
				imenik.dodaj(scanner.nextLine(), new FiksniBroj(grad, broj));
				return;
			case 2:
				System.out.println("Unesite mobilnu mrezu");
				scanner = new Scanner(System.in);
				unos = scanner.nextInt();
				System.out.println("Unesite Broj u formatu 123-456");
				scanner = new Scanner(System.in);
				broj = scanner.nextLine();
				System.out.println("Unesite ime i prezime osobe");
				scanner = new Scanner(System.in);
				imenik.dodaj(scanner.nextLine(), new MobilniBroj(unos, broj));
				return;
			case 3:
				System.out.println("Unesite pozivni broj drzave u formatu +387");
				scanner = new Scanner(System.in);
				String medjunarodni = scanner.nextLine();
				System.out.println("Unesite Broj u formatu 123-456");
				scanner = new Scanner(System.in);
				broj = scanner.nextLine();
				System.out.println("Unesite ime i prezime osobe");
				scanner = new Scanner(System.in);
				imenik.dodaj(scanner.nextLine(), new MedunarodniBroj(medjunarodni, broj));
				return;
			default:
				return;
		}

	}

	public void dajBroj(){
		System.out.println("Unesite ime i prezime osobe");
		Scanner scanner = new Scanner(System.in);
		System.out.println(imenik.dajBroj(scanner.nextLine()));
	}

	public void dajImeZaBroj(){
		System.out.println("-----------------------");
		System.out.println("0. Za povratak,");
		System.out.println("1. Za Fiksni,");
		System.out.println("2. Za Mobilni,");
		System.out.println("3. Za Medjunarodni.");
		System.out.println("-----------------------");
		Scanner scanner = new Scanner(System.in);
		Integer unos = scanner.nextInt();
		String broj = null;
		switch (unos){
			case 0:
				return;
			case 1:
				System.out.println("Unesite 1.TRAVNIK, 2.ORASJE, 3.ZENICA, 4.SARAJEVO, 5.LIVNO, 6.TUZLA, 7.MOSTAR, 8.BIHAC, 9.GORAZDE, 10.SIROKIBRIJEG, 11.BRCKO");
				scanner = new Scanner(System.in);
				unos = scanner.nextInt();
				FiksniBroj.Grad grad = dajGrad(unos);
				if(grad == null) return;
				System.out.println("Unesite Broj u formatu 123-456");
				scanner = new Scanner(System.in);
				broj = scanner.nextLine();
				System.out.println(imenik.dajIme(new FiksniBroj(grad, broj)));
				return;
			case 2:
				System.out.println("Unesite mobilnu mrezu");
				scanner = new Scanner(System.in);
				unos = scanner.nextInt();
				System.out.println("Unesite Broj u formatu 123-456");
				scanner = new Scanner(System.in);
				broj = scanner.nextLine();
				System.out.println(imenik.dajIme(new MobilniBroj(unos, broj)));
				return;
			case 3:
				System.out.println("Unesite pozivni broj drzave u formatu +387");
				scanner = new Scanner(System.in);
				String medjunarodni = scanner.nextLine();
				System.out.println("Unesite Broj u formatu 123-456");
				scanner = new Scanner(System.in);
				broj = scanner.nextLine();
				System.out.println(imenik.dajIme( new MedunarodniBroj(medjunarodni, broj)));
				return;
			default:
				return;
		}
	}

	public void dajTelefonskeBrojeveZaSlovo(){
		System.out.println("Unesite slovo");
		Scanner scanner =  new Scanner(System.in);
		System.out.println(imenik.naSlovo(scanner.next().charAt(0)));
	}

	public void dajSortiranaImenaZaGrad(){
		System.out.println("Unesite 1.TRAVNIK, 2.ORASJE, 3.ZENICA, 4.SARAJEVO, 5.LIVNO, 6.TUZLA, 7.MOSTAR, 8.BIHAC, 9.GORAZDE, 10.SIROKIBRIJEG, 11.BRCKO");
		Scanner scanner = new Scanner(System.in);
		Integer unos = scanner.nextInt();
		FiksniBroj.Grad grad = dajGrad(unos);
		if(grad == null) return;
		System.out.println(imenik.izGrada(grad));
	}


    public static void main(String[] args) {
		Program program = new Program();
	    while (true){
	    	System.out.println("------------------------------------------------------------------------------");
	    	System.out.println("Unesite redni broj komande koju zelite da izvrsite!");
			System.out.println("1. Dodaj broj,");
			System.out.println("2. Daj broj za odredjeno ime,");
			System.out.println("3. Daj ime za odredjeni broj,");
			System.out.println("4. Daj telefonske brojeve koji pocinju slovom,");
			System.out.println("5. Daj sortirana imena telefonskih brojeva iz grada,");
			System.out.println("0. Exit.");
			System.out.println("------------------------------------------------------------------------------");
			Scanner scanner  = new Scanner(System.in);
			Integer unos = scanner.nextInt();
			switch (unos){
				case 0:
					return;
				case 1:
					program.dodajBroj();
					break;
				case 2:
					program.dajBroj();
					break;
				case 3:
					program.dajImeZaBroj();
					return;
				case 4:
					program.dajTelefonskeBrojeveZaSlovo();
					return;
				case 5:
					program.dajSortiranaImenaZaGrad();
					return;
				default:
					System.out.println("Neispravan unos!");
					break;
			}

		}
    }
}
