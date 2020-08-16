//Traistaru Andrei-Cristian
//Grupa 312 CD

1. Se intra in main unde se face citirea hartii, a pieselor si a detaliilor
	legate de mutarile pieselor;
2. Pentru fiecare mutare se executa functia 'mutare' care se ocupa de
	realizarea fiecarei mutari in parte; harta se transmite printr-un
	pointer pentru a putea fi modificata si modificarile sa fie vizibile
	in main (la terminarea mutarilor, pentru calculul scorului); in
	functie de rezultatul returnat de 'mutare' se continua sau nu executia
	urmatoarelor mutari, fiind cuprins astfel cazul in care jocul se
	incheie din cauza umplerii hartii;
3. Dupa ce s-au epuizat mutarile/s-a umplut harta se calculeaza scorul in
	functia 'scor' si se afiseaza corespunzator; acest calcul se bazeaza
	pe numarul de randuri eliminate care este returnat de functia
	'elimin_randuri';
4. Functia 'mutare' incepe prin impartirea piesei in doua jumatati
	corespunzatoare celor 2 bytes pe care ii au piesele; daca piesa este
	reprezentata pe un singur byte, atunci primul byte va avea fiecare bit
	initializat la 0; acest lucru permite generalizarea mutarilor pentru
	ambele tipuri de piese; se continua cu apelarea functiei
	'prima_transformare' pentru a se executa coborarea piesei pe primul
	rand din harta; in functie de rezultatul returnat, se continua sirul
	de transformari sau se incheie jocul; incepand cu a doua transformare
	se apeleaza doar functia 'celelalte_transformari' intrucat sunt
	conditii usor diferite pe care trebuie sa le verific; parametrii
	trimisi sunt o copie a hartii originale in care se efectueaza
	transformarile, piesele si randul din harta asupra caruia apar
	modificarile; la final se salveaza copia hartii in cea originala 
	pentru a putea fi folosita drept harta initiala pentru mutarile
	viitoare; acest lucru este necesar pentru a putea afisa fiecare
	transformare in parte, pastrand harta initiala fara modificari pana
	la finalul transformarii (altfel trebuia ca dupa fiecare transformare
	sa sterg transformarea curenta si apoi sa o execut pe urmatoarea);
	se elimina randurile complete daca este cazul si se mai afiseaza inca
	o data harta daca s-au eliminat randuri din aceasta; 
5. In functiile 'prima_transformare' si 'cealata_transformare', se verifica
	daca piesa ciocneste ceva in randul in care coboara(daca ciocneste,
	nu se mai continua si se verifica daca jocul trebuie incheiat(daca
	piesa este de 2 bytes si nu are loc pe harta in intregime) sau daca se
	incheie doar mutarea curenta) apoi se deplaseaza prin shiftarea
	bitilor cu o pozitie din ambele randuri ale piesei(sau doar randul
	inferior daca este vorba de prima transformare); daca in continuare
	nu se ciocneste de nimic se continua cu shiftarea bitilor pana la
	epuizarea deplasarii/ciocnirea cu obstacol/capat de rand; la final se
	afiseaza harta din copie intrucat s-a terminat transformarea curenta;
6. Functia 'verific_ciocnire' compara bit cu bit randul din harta specificat
	in parametrul 'rand' cu piesa trimisa tot ca parametru; in cazul in
	care cei doi biti sunt 1 atunci inseamna ca are loc o coliziune si se
	returneza valoarea 0; altfel se returneaza valoarea 1;
7. Functia 'afisez' compara harta cu o masca formata dintr-un singur bit de 1
	aflat pe fiecare pozitie din harta; daca SI logic are valoarea zero
	inseamna ca harta are un spatiu deci caracterul '.', pentru alta
	valoare harta este ocupata, deci caracterul '#';
8. Functia 'scor' primeste ca parametru harta si numarul de linii complete si
	calculeaza scorul dupa formula indicata;
9. Functia 'elimin_randuri' contorizeaza si returneaza la fiecare apel numarul
	de linii eliminate de la inceputul jocului; astfel contorul este
	variabila statica 'linii_complete' care, la primul apel al acestei
	functii, primeste valoarea zero, iar apoi este incrementat cand se
	elimina cate un rand; folosind operatii pe biti se cauta randuri cu
	toti bitii egali cu 1 si se elimina prin copierea bitilor randurilor
	superioare peste randurile dinharta, incepand cu randul de eliminat
	in sus(randul cel mai de sus are valoarea 0 peste tot deoarece masca
	este shiftata de LATIME ori spre dreapta); modificarile raman vizibile
	in functia apelanta deoarece s-au folosit pointeri; de asemenea,
	parametrul 'int *schimbat' este util pentru functia apelanta care
	decide astfel daca este nevoie sa mai afiseze harta dupa apelarea
	functie 'elimin_randuri' sau nu(valoarea returnata putea decide acest
	lucru doar daca mai contorizam randurile eliminate si in celelalte
	functii	ceea ce nu se intampla).