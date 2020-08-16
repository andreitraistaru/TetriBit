//Traistaru Andrei-Cristian
//Grupa 312 CD

#include<stdio.h>
#include<math.h>
#define LATIME 8
#define LUNGIME 8
typedef unsigned long long TIP;
typedef unsigned long long* TIP_PTR;

int elimin_randuri(TIP_PTR harta,int *schimbat)
{
	static int linii_complete=0;
	int i=0;
	TIP masca_1,masca_2;
	(*schimbat) = 0;
	while(i<LUNGIME)
	{
		masca_1 = ( 1 << LATIME );
		masca_1--;
		masca_1 = ( masca_1 << (i*LATIME) );
		if( ( (*harta) & masca_1 ) == masca_1 )
		{
			linii_complete++;
			(*schimbat) = 1;
			masca_1 = ( 1ULL << (LATIME*(LUNGIME-i-1)) );
			masca_1--;
			masca_1 = ( masca_1 << (LATIME*(i+1)) );
			masca_1 = ( (*harta) & masca_1 );
			masca_1 = ( masca_1 >> LATIME );
			masca_2 = ( 1ULL << (LATIME*i) );
			masca_2--;
			masca_2 = ( (*harta) & masca_2 );
			(*harta) = ( masca_1 | masca_2 );
			i--;
		}
		i++;
	}
	return linii_complete;
}

double scor(TIP harta,int linii_complete)
{
	int zerouri=0,i;
	for(i=0 ; i<LUNGIME*LATIME ; i++)
	{
		if( ( harta & ( 1ULL << i ) ) == 0 )
		{
			zerouri++;
		}
	}
	return ((double) ( sqrt((double)zerouri) ) + 
					(pow((double)1.25,(double)linii_complete) ) );
}

void afisez(TIP harta)
{
	int i,j;
	for(i=LUNGIME-1 ; i>=0 ; i--)
	{
		for(j=LATIME-1 ; j>=0 ; j--)
		{
			if( ( harta & ( 1ULL<<(i*LATIME+j) ) ) == 0 )
			{
				printf(".");
			}
			else
			{
				printf("#");
			}
		}
		printf("\n");	
	}
	printf("\n");
}

int verific_ciocnire(TIP harta,TIP piesa,int rand)
{
	int i;
	for(i=0 ; i<LATIME ; i++)
	{
		if( ( harta & ( 1ULL<<(rand*LATIME-1-i) ) ) != 0 )
		{
			if( ( piesa & ( 1<<(LATIME-1-i) ) ) !=0 )
			{
				return 0;	//ciocnire, jocul s-a terminat
			}		
		}
	}
	return 1;
}

int prima_transformare(TIP harta,TIP_PTR harta_nou,TIP_PTR piesa_1,
											TIP_PTR piesa_2,long long trans)
{
	//verificam daca randul 2 din piesa loveste ceva in primul rand din harta
	if(verific_ciocnire(harta,*piesa_2,LUNGIME)==0)
	{
		afisez(harta);
		(*harta_nou) = harta;
		return 0;	//ciocnire, jocul s-a terminat
	}

	//nu ciocneste, deci putem sa coboram rand 2 din piesa
	//efectuam deplasarea in cadrul randului

	if(trans < 0)	//spre stanga
	{
		while( ( trans<0 ) && ( ( (*piesa_1) & ( 1ULL<<(LATIME-1) ) ) == 0 )
						 && ( ( (*piesa_2) & ( 1ULL<<(LATIME-1) ) ) == 0 ) )
		{
			//incerc deplasarea cu o unitate si verific daca ciocneste ceva
			trans++;
			(*piesa_1) = ( (*piesa_1) << 1 );
			(*piesa_2) = ( (*piesa_2) << 1 );

			if(verific_ciocnire(harta,*piesa_2,LUNGIME)==0)
			{
				//ciocnire, deci revin la pozitia anterioara
				trans--;
				(*piesa_1) = ( (*piesa_1) >> 1 );
				(*piesa_2) = ( (*piesa_2) >> 1 );

				break;	//transformarea curenta s-a incheiat
			}
		}

		//noua harta
		(*harta_nou) = ( harta ^ ( (*piesa_2) << (LATIME*(LUNGIME-1)) ) );
	}

	else if(trans > 0)	//spre dreapta
	{
		while( ( trans>0 ) && ( ( (*piesa_1) & 1 ) == 0 ) && 
										( ( (*piesa_2) & 1 ) == 0 ))
		{
			//incerc deplasarea cu o unitate si verific daca ciocneste ceva
			trans--;
			(*piesa_1) = ( (*piesa_1) >> 1 );
			(*piesa_2) = ( (*piesa_2) >> 1 );

			if(verific_ciocnire(harta,*piesa_2,LUNGIME)==0)
			{
				//ciocnire, deci revin la pozitia anterioara
				trans++;
				(*piesa_1) = ( (*piesa_1) << 1 );
				(*piesa_2) = ( (*piesa_2) << 1 );

				break;	//transformarea curenta s-a incheiat
			}
		}

		//noua harta
		(*harta_nou) = ( harta ^ ( (*piesa_2) << (LATIME*(LUNGIME-1)) ) );
	}

	else	//nu se deplaseaza deloc in cadrul randului
	{
		(*harta_nou) = ( harta ^ ( (*piesa_2) << (LATIME*(LUNGIME-1)) ) );
	}

	afisez(*harta_nou);	//afisez harta dupa transformarea curenta

	return 2;	//trec la urmatoarea transformare
}

int celelalte_transformari(TIP harta,TIP_PTR harta_nou,TIP_PTR piesa_1,
									TIP_PTR piesa_2,long long trans,int rand)
{
	//verificam daca randul 2 din piesa loveste ceva din harta pe randul
	//trimis ca parametru al functiei

	if(verific_ciocnire(harta,*piesa_2,rand)==0)
	{
		if( ( rand==LUNGIME-1 ) && ( *piesa_1 != 0 ) )
		{
			afisez(*harta_nou);
			return 0;	//ciocnire, jocul s-a terminat
		}
		else
		{
			return 1;
		}
	}

	//nu ciocneste, dar verificam daca randul 1 din piesa loveste ceva din
	//harta pe randul unde se afla acum randul 2 al piesei

	if(verific_ciocnire(harta,*piesa_1,(rand+1))==0)
	{
		if(rand == (LUNGIME-1) )
		{	//ciocnire, jocul s-a terminat
			afisez(*harta_nou);	//afisez harta corespunzatoare
			return 0;			//mutarii anterioare
		}
		else
		{
			return 1;
		}
	}

	//nu ciocneste, putem sa coboram piesa si sa o deplasam in cadrul randului

	if(trans < 0)	//spre stanga
	{
		while( ( trans<0 ) && ( ( (*piesa_1) & ( 1ULL<<(LATIME-1) ) ) == 0 )
			 			&& ( ( (*piesa_2) & ( 1ULL<<(LATIME-1) ) ) == 0 ) )
		{
			//incerc deplasarea cu o unitate si verific sa nu ciocnesc ceva
			trans++;
			(*piesa_1) = ( (*piesa_1) << 1 );
			(*piesa_2) = ( (*piesa_2) << 1 );

			if( (verific_ciocnire(harta,*piesa_2,rand)==0) ||
						(verific_ciocnire(harta,*piesa_1,(rand+1))==0) )
			{
				//ciocnire, deci revin la pozitia anterioara
				trans--;
				(*piesa_1) = ( (*piesa_1) >> 1 );
				(*piesa_2) = ( (*piesa_2) >> 1 );
				break;	//transformarea curenta s-a incheiat
			}

		}

		//noua harta
		(*harta_nou) = ( ( harta ^ ( (*piesa_1) << (LATIME*rand) ) ) |
					 ( harta ^ ( (*piesa_2) << (LATIME*(rand-1)) ) ) );

	}
	else if(trans > 0)	//spre dreapta
	{

		while( ( trans>0 ) && ( ( (*piesa_1) & 1 ) == 0 ) &&
										( ( (*piesa_2) & 1 ) == 0 ) )
		{
			//incerc deplasarea cu o unitate si verific sa nu ciocnesc ceva
			trans--;
			(*piesa_1) = ( (*piesa_1) >> 1 );
			(*piesa_2) = ( (*piesa_2) >> 1 );

			if( (verific_ciocnire(harta,*piesa_2,rand)==0) || 
						(verific_ciocnire(harta,*piesa_1,(rand+1))==0) )
			{
				//ciocnire, deci revin la pozitia anterioara
				trans++;
				(*piesa_1) = ( (*piesa_1) << 1 );
				(*piesa_2) = ( (*piesa_2) << 1 );
				break;	//transformarea curenta s-a incheiat
			}
		}

		//noua harta
		(*harta_nou) = ( ( harta ^ ( (*piesa_1) << (LATIME*rand) ) ) |
				( harta ^ ( (*piesa_2) << (LATIME*(rand-1)) ) ) );
	}
	else	//nu se deplaseaza deloc in cadrul randului
	{
		//noua harta
		(*harta_nou) = ( ( harta ^ ( (*piesa_1) << (LATIME*rand) ) ) |
				( harta ^ ( (*piesa_2) << (LATIME*(rand-1)) ) ) );	
	}

	afisez(*harta_nou);	//afisez harta dupa transformarea curenta

	return 2;	//trec la urmatoarea transformare
}

int mutare(TIP_PTR harta,TIP piesa,long long* trans)
{
	TIP piesa_1,piesa_2,masca,harta_nou;
	int i,eroare,modificare;

	//copiem harta in harta_nou in care efectuam transformarile temporar
	harta_nou = (*harta);

	//despartim cele 2 randuri din piesa
	masca = ( 1ULL << LATIME );
	masca--;
	piesa_2 = ( piesa & masca );
	masca = ( masca << LATIME );
	piesa_1 = ( piesa & masca );
	piesa_1 = ( piesa_1 >> LATIME );

	//mutarea e compusa din cele LUNGIME transformari de efectuat
	for(i=0 ; i<LUNGIME ; i++)
	{	//efectuez transformarea curenta si analizez rezultatul obtinut
		if(i==0)
		{
			eroare = prima_transformare(*harta,&harta_nou,&piesa_1,&piesa_2,
																*(trans+i));
		}
		else
		{
			eroare = celelalte_transformari(*harta,&harta_nou,&piesa_1,
											&piesa_2,*(trans+i),LUNGIME-i);
		}
		
		if(eroare == 0)
		{
			(*harta) = harta_nou;
			return 0;	//ciocnire, jocul s-a terminat
		}
		else if(eroare == 1)
		{
			break;	//terminare mutare, coliziunea piesei cu restul hartii
		}
	}

	(*harta) = harta_nou;	//salvez noua harta care devine harta initiala
							//pentru mutarea viitoare

	elimin_randuri(harta,&modificare);

	if(modificare == 1)
	{
		afisez(*harta);
	}

	return 1;	//aici se ajunge doar daca s-au terminat transformarile
				//sau a avut loc o coliziune fara a se incheia jocul
}

int main()
{
	TIP harta,mutari,piesa;
	long long trans[LUNGIME];
	int i;

	scanf("%llu",&harta);	//memorez harta
	scanf("%llu",&mutari);	//memorez nr. de mutari

	afisez(harta);	//afisez harta initial
	
	for( ; mutari>0 ; mutari--)
	{	
		//decrementez variabila mutari pt ca oricum nu mai am nevoie de ea
		
		scanf("%llu",&piesa);
		for(i=0 ; i<LUNGIME ; i++)
		{
			scanf("%llu",&trans[i]);	//citesc transformarile piesei
		}

		if(mutare(&harta,piesa,trans) == 0)	//efectuez mutarea
		{
			break;	//ciocnire, jocul s-a terminat
		}
	}
	
	printf("GAME OVER!\nScore:%.2lf\n",scor(harta,elimin_randuri(&harta,&i)));
	return 0;
}
