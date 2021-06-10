BEGIN {
	br_odbacenih = 0;
	br_poslanih = 0;
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

	if (id_toka == 2 && od == 0 && akcija == "+") {
		br_poslanih++;
	} 
	else if (id_toka == 2  && akcija == "d") {
		br_odbacenih++;
		print vrijeme " " br_odbacenih > "gubici2.txt"
	}
}

END {
	printf("Broj poslanih paketa: %d\nBroj izgubljenih paketa: %d\nGubici: %.2f %% \n", br_poslanih, br_odbacenih, 100*br_odbacenih/br_poslanih);
}
