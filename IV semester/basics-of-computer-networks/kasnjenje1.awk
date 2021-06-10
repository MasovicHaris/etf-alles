BEGIN {
	najveci_id_paketa = 0;
}

{  
	akcija = $1;
	vrijeme = $2;
	od = $3;
	prema = $4;
	tip = $5;
	velicina_paketa = $6;
	id_toka = $8;
	izvor = $9;
	odrediste = $10;
	br_sekvence = $11;
	id_paketa = $12;	

	if (id_paketa > najveci_id_paketa)
		najveci_id_paketa = id_paketa;

	if (pocetno_vrijeme[id_paketa] == 0) 
		pocetno_vrijeme[id_paketa] = vrijeme;

	if (id_toka == 2 && akcija != "d") {
		if (akcija == "r") {
			krajnje_vrijeme[id_paketa] = vrijeme;
		}
	} 
	else {
		krajnje_vrijeme[id_paketa] = -1;
	}  	
}                                                       

END {
	for (id_paketa = 0; id_paketa <= najveci_id_paketa; id_paketa++) {
		pocetak = pocetno_vrijeme[id_paketa];
		kraj = krajnje_vrijeme[id_paketa];
		trajanje_paketa = kraj - pocetak;
	if (pocetak < kraj) printf("%f %f\n", pocetak, trajanje_paketa) > "kasnjenje2.txt";
	}
}
