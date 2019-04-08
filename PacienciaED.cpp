#include<conio2.h>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
#define TF 30

struct Tpcarta
{
    int num, naipe;
};
typedef struct Tpcarta tpCarta;

struct Carta{
	int num;
	int naipe;
	char status;
	int cor;
	struct Carta *prox;
};
typedef struct Carta carta;

struct Monte{
	int qntCartas;
	 carta *prim;
	 struct Monte *prox;
};
typedef struct Monte monte;

struct Jogo{
	monte *prim;
	struct Jogo *prox;
};
typedef struct Jogo jogo;

jogo *criaJogo(){
	jogo *novo = (jogo*)malloc(sizeof(jogo));
	novo->prim = NULL;
	novo->prox = NULL;
	return novo;
}

monte *criaMonte(){
	monte *novo = (monte*)malloc(sizeof(monte));
	novo->prim = NULL;
	novo->prox = NULL;
	novo->qntCartas = 0;	
	return novo;
}

carta *criaCarta(int numC, int naipeC)
{
	carta *novaCarta = (carta*)malloc(sizeof(carta));
	novaCarta->naipe = naipeC;
	novaCarta->num = numC;
	novaCarta->status = 0;
	if(naipeC == 3|| naipeC == 4)
		novaCarta->cor = 4;
	else
		novaCarta->cor = 0;
	novaCarta->prox = NULL;
	return novaCarta;
}

void CriaBaralho(Tpcarta cartas[52])
{
    for (int i = 0; i < 52; i++)
    { //inicialização
        cartas[i].num = i / 4 +1;
        switch (i%4)
        {
            case 0: cartas[i].naipe = 3; break; //copas
            case 1: cartas[i].naipe = 4; break; //ouro
            case 2: cartas[i].naipe = 5; break; //paus
            case 3: cartas[i].naipe = 6; break; //espada
        }
        
    }
}

void InsereCartaBaralho(carta **baralho, int num, int naipe)
{
	carta *novaCarta, *aux;
	novaCarta = criaCarta(num, naipe);
	if(*baralho == NULL)
		*baralho = novaCarta;
	else
	{
		aux = *baralho;
		while(aux->prox != NULL)
			aux = aux->prox;
		aux->prox = novaCarta;			 
	}
}

void InsereMonte(monte **baralho)
{
	monte *novoMonte, *aux;
	novoMonte = criaMonte();
	if(*baralho == NULL)
		*baralho = novoMonte;
	else
	{
		aux = *baralho;
		while(aux->prox != NULL)
			aux = aux->prox;
		aux->prox = novoMonte;		 
	}
}

void EmbaralhaBaralho(Tpcarta cartas[52], jogo **jogo)
{
     srand(time(0));
     int j,i,k,l;
     Tpcarta Aux;
     carta *AuxCarta;
     monte *monte;
     for (i = 0; i < 52; i++) 
     { //embaralhar;
        do 
        {
            j = rand()%52;
        } while (i == j);
        Aux = cartas[i];
        cartas[i] = cartas[j];
        cartas[j] = Aux;
    }
    
    for(i=0; i<4; i++)
    {
    	
    	if(i==0)
		{
    		*jogo = criaJogo();
    		monte = criaMonte();
    		(*jogo)->prim = monte;
    		monte->qntCartas = 23;
    		for(j=0; j < 23; j++)
				InsereCartaBaralho(&monte->prim ,cartas[j].num, cartas[j].naipe);
    	}
    	else
    	{
    		if(i==1)
    		{
    			(*jogo)->prox = criaJogo();
    			monte = criaMonte();
    			(*jogo)->prox->prim = monte;
    			monte->qntCartas = 1;
    				InsereCartaBaralho(&monte->prim ,cartas[j].num, cartas[j].naipe);
    			monte->prim->status = 1;
    			j++;
    		}
    		else
    		{
    			if(i==2)
    			{
    				(*jogo)->prox->prox = criaJogo();
    				for(k=0;k<4;k++)
    					InsereMonte(&(*jogo)->prox->prox->prim);
    			}
    			else
    			{
    				(*jogo)->prox->prox->prox = criaJogo();
    				for(k=1;k<=7;k++)
    				{
    					InsereMonte(&(*jogo)->prox->prox->prox->prim);
    					if(k == 1)
    					{
    						monte = (*jogo)->prox->prox->prox->prim;
    						monte->qntCartas=1;
    						InsereCartaBaralho(&monte->prim ,cartas[j].num, cartas[j].naipe);
    						j++;
    						monte->prim->status = 1;
    					}
    					else
    					{
    						monte = monte->prox;
    						monte->qntCartas=k;
    						if(monte != NULL)
    						{
    							for(l=k;l>0;l--)
	    						{
	    							InsereCartaBaralho(&monte->prim ,cartas[j].num, cartas[j].naipe);
	    							j++;
	    							if(l == 1)
	    							{
	    								AuxCarta = monte->prim;
	    								while(AuxCarta->prox != NULL)
	    									AuxCarta = AuxCarta->prox;
	    								AuxCarta->status = 1;
	    							}
	    								
	    						}
    						}
	    					else
	    						printf("Monte NULL");
    					}
    				}
    			}
    		}
    	}
    	
    }
}

void ApontaMonte(jogo *jogo, monte **mvirado, monte **mdesvirado, monte **mA, monte **mB, monte **mC, monte **mD, monte **m1, monte **m2, monte **m3, monte **m4, monte **m5, monte **m6, monte **m7)
{
	*mvirado = jogo->prim;
	jogo = jogo->prox;
	*mdesvirado = jogo->prim;
	jogo = jogo->prox;	
	*mA = jogo->prim;		*mB = (*mA)->prox;			
	*mC = (*mB)->prox;		*mD = (*mC)->prox;	
	jogo = jogo->prox;	
	*m1 = jogo->prim;		*m2 = (*m1)->prox;	
	*m3 = (*m2)->prox;   	*m4 = (*m3)->prox;
	*m5 = (*m4)->prox;		*m6 = (*m5)->prox;
	*m7 = (*m6)->prox;
}

void MolduraCartas(int ci,int li,int cf,int lf,int cor)   //moldura
{
    int i;
    textcolor(cor);
    gotoxy(ci,li);printf("%c",218);
    gotoxy(cf,lf);printf("%c",217);
    gotoxy(cf,li);printf("%c",191);
    gotoxy(ci,lf);printf("%c",192);

    for(i=ci+1;i<cf;i++)
    {
        gotoxy(i,li);printf("%c",196);
        gotoxy(i,lf);printf("%c",196);// linha horizontal
    }
    for(i=li+1;i<lf;i++)
    {
        gotoxy(ci,i);printf("%c",179);//linha vertical
        gotoxy(cf,i);printf("%c",179);
    }
}

void Moldura(int ci,int li,int cf,int lf,int cor)   //moldura
{
    int i;
    textcolor(cor);
    gotoxy(ci,li);printf("%c",201);
    gotoxy(cf,lf);printf("%c",188);
    gotoxy(cf,li);printf("%c",187);
    gotoxy(ci,lf);printf("%c",200);

    for(i=ci+1;i<cf;i++)
    {
        gotoxy(i,li);printf("%c",205);
        gotoxy(i,lf);printf("%c",205);// linha horizontal
    }
    for(i=li+1;i<lf;i++)
    {
        gotoxy(ci,i);printf("%c",186);//linha vertical
        gotoxy(cf,i);printf("%c",186);
    }
}

void Tela()
{
	textbackground(GREEN);
	clrscr();
    Moldura(1,1,80,25,0);  //moldura da tela
    MolduraCartas(3,2,9,5,0);  //ordem: coluna inicial, linha inicial,col final, lin final e cor.
    MolduraCartas(11,2,17,5,0);
    MolduraCartas(40,2,46,5,0); 
    MolduraCartas(48,2,54,5,0);
    MolduraCartas(56,2,62,5,0);
    MolduraCartas(64,2,70,5,0);        
}

void ImprimeCarta(carta* cartaEx)
{
	if(cartaEx->status == 1)
	{
		if(cartaEx->num==1)
		{
			textcolor(cartaEx->cor);
			printf("A%c",cartaEx->naipe);
		}
		else
		if(cartaEx->num==11)
		{
			textcolor(cartaEx->cor);
			printf("J%c",cartaEx->naipe);
		}
		else
		if(cartaEx->num==12)
		{
			textcolor(cartaEx->cor);
			printf("Q%c",cartaEx->naipe);
		}
		else
		if(cartaEx->num==13)
		{
			textcolor(cartaEx->cor);
			printf("K%c",cartaEx->naipe);
		}
		else	
		{
			textcolor(cartaEx->cor);
			printf("%d%c",cartaEx->num,cartaEx->naipe);
		}
	}
	else
		printf("###");
}

void BoxFinal(int ci,int li,int cf,int lf)
{
      gotoxy(ci,li);printf("%c",218);//sup esq
      gotoxy(cf,li);printf("%c",191);//sup dir
      gotoxy(ci,lf);printf("%c",192);//inf esq
      gotoxy(cf,lf);printf("%c",217);//inf dir

      for(int i=ci+1;i<cf;i++)
      {
            gotoxy(i,li);printf("%c",196);//hor
            gotoxy(i,lf);printf("%c",196);
      }

      for(int i=li+1;i<lf;i++)
      {
            gotoxy(ci,i);printf("%c",179);//vert
            gotoxy(cf,i);printf("%c",179);
      }
}

void VoceGanhou()
{
    clrscr();
    system("COLOR 01"); 
    textbackground(BLACK);
    textcolor(9); 
    textcolor(9);         
    BoxFinal(10,2,70,22); BoxFinal(11,3,71,23); BoxFinal(12,4,72,24);
    textcolor(4);gotoxy(27,9);printf("%c %c PACIENCIA INSANA %c %c©",3,4,5,6);
    gotoxy(34,13);printf("VOCE GANHOU!!!");
	gotoxy(22,18);printf("Pressione qualquer tecla para finalizar. . .");getch(); 
}

void TelaAbertura()
{
        //clrscr();
       //textcolor(10);
       system("COLOR 01"); 
       BoxFinal(10,2,70,22); BoxFinal(11,3,71,23); 
       textcolor(4);
       gotoxy(28,2); printf(" ##############    #### ");
       gotoxy(28,3); printf(" ###############   #### ");
       gotoxy(28,4); printf(" ####        ####  ####");
       gotoxy(28,5); printf(" ####         ###  ####");
       gotoxy(28,6); printf(" ####        ####  ####");
       gotoxy(28,7); printf(" ################  ####");
       gotoxy(28,8); printf(" ###############   ####");
       gotoxy(28,9); printf(" ############      ####");
       gotoxy(28,10);printf(" ####              ####");
       gotoxy(28,11);printf(" ####              ####");
       gotoxy(28,12);printf(" ####              ####");
       gotoxy(28,13);printf(" ####              ####");
       textcolor(4);gotoxy(28,15);printf("%c %c PACIENCIA INSANA %c %c",3,4,5,6);
       textcolor(4);gotoxy(2,24);printf("Lucas Coelho RA:261132423");//textcolor(10);
       textcolor(4);gotoxy(55,24);printf("Matheus Braz RA:261132113");//textcolor(10);
       gotoxy(18,18);system("PAUSE");//system("color 07");
}

void InicializaJogo(monte *mvirado, monte *mdesvirado, monte *m1, monte *m2, monte *m3, monte *m4, monte *m5, monte *m6, monte *m7)
{
    carta *aux;
    textbackground(GREEN);
    clrscr();
    Tela();
    aux = m1->prim;                         //MONTE 1
    gotoxy(9,8);
    ImprimeCarta(aux);

    aux = m2->prim;
	while(aux->prox != NULL)					//MONTE 2
    	aux = aux->prox;
    gotoxy(19,8);
    ImprimeCarta(aux);

    aux = m3->prim; 
	while(aux->prox != NULL)						//MONTE 3
    	aux = aux->prox;
    gotoxy(29,8);
    ImprimeCarta(aux);

	aux = m4->prim;  
	while(aux->prox != NULL)					//MONTE 4
    	aux = aux->prox;
    gotoxy(39,8);
    ImprimeCarta(aux);

    aux = m5->prim;
	while(aux->prox != NULL)						//MONTE 5
    	aux = aux->prox;
    gotoxy(49,8);
    ImprimeCarta(aux);

    aux = m6->prim;	
	while(aux->prox != NULL)					//MONTE 6
    	aux = aux->prox;
    gotoxy(59,8);
    ImprimeCarta(aux);

    aux = m7->prim;
	while(aux->prox != NULL)					//MONTE 7
    	aux = aux->prox;
    gotoxy(69,8);
    ImprimeCarta(aux);
    
    aux = mvirado->prim;
	while(aux->prox != NULL)					//MONTE VIRADO
    	aux = aux->prox;
    textcolor(0);
    gotoxy(5,3);
    ImprimeCarta(aux);
    gotoxy(6,4);
    ImprimeCarta(aux);
    
    aux = mdesvirado->prim;  					//MONTE DESVIRADO
    gotoxy(13,3);
    ImprimeCarta(aux);
    gotoxy(14,4);
    ImprimeCarta(aux);
}

void Mensagem()
{
    gotoxy(12,23);
    printf("Movimento Invalido!          ");
    getch();
    gotoxy(12,23);
    printf("                             ");
}

void Espaco()
{
    gotoxy(13,3);
    printf("    ");
    gotoxy(13,4);
    printf("    ");
}

void Destino1(monte *m, int *valida, carta *aux1, carta **aux2)
{
	if(m->prim != NULL)
	{
		*aux2 = m->prim;
		while((*aux2)->prox != NULL)					
			*aux2 = (*aux2)->prox;
		if(aux1->num == (*aux2)->num-1 && aux1->cor != (*aux2)->cor)
		{
			(*aux2)->prox = aux1;
			*aux2 = (*aux2)->prox;
			*valida = 1;
		}
		else
			*valida = 0;
	}
	else
	{
		if(aux1->num == 13)
		{
			m->prim = aux1;
			*aux2 = m->prim;
			*valida = 1;
		}
		else
			*valida = 0;
	}
}

void DestinoA(monte *m, int *valida, carta *aux1, carta **aux2)
{
	if(m->prim != NULL)
	{
		*aux2 = m->prim;
		while((*aux2)->prox != NULL)					
			*aux2 = (*aux2)->prox;
		if(aux1->num == (*aux2)->num+1 && aux1->naipe == (*aux2)->naipe)
		{
			(*aux2)->prox = aux1;
			*aux2 = (*aux2)->prox;
			*valida = 1;
		}
		else
			*valida = 0;
	}
	else
	{
		if(aux1->num == 1)
		{
			m->prim = aux1;
			*aux2 = m->prim;
			*valida = 1;
		}
		else
			*valida = 0;
	}
}

void Movimentacao(monte **mvirado, monte **mdesvirado, monte **mA, monte **mB, monte **mC, monte **mD, monte **m1, monte **m2, monte **m3, monte **m4, monte **m5, monte **m6, monte **m7, 
				int Origem, int Destino, int *L1,int *L2,int *L3,int *L4,int *L5,int *L6,int *L7, int Pos)
{
    int valida = -1, Cont=0;
	carta *aux1, *aux2, *ant1;
    if(Origem==0)
    {
    	if((*mvirado)->qntCartas > 0)
    	{
    		aux1 = (*mvirado)->prim;
        	while(aux1->prox != NULL)		
			{	
				ant1 = aux1;				
    			aux1 = aux1->prox;
    		}
			aux1->status = 1;   			
    		if((*mdesvirado)->prim != NULL)
    		{
    			aux2 = (*mdesvirado)->prim;
    			while(aux2->prox != NULL)					
    				aux2 = aux2->prox;
    			aux2->prox = aux1;
    			aux2 = aux2->prox;
    		}
    		else
    		{
    			(*mdesvirado)->prim = aux1;
    			aux2 = (*mdesvirado)->prim;
    		}  		
    		(*mvirado)->qntCartas--;
    		(*mdesvirado)->qntCartas++;
    		Espaco();
    		gotoxy(13,3);
        	ImprimeCarta(aux2);
        	gotoxy(14,4);
        	ImprimeCarta(aux2);
        	if((*mvirado)->qntCartas==0)
	        {
	        	(*mvirado)->prim = NULL;
	            textcolor(0);
	            gotoxy(5,3);
	            printf("   ");
	            gotoxy(6,4);
	            printf("   ");
	            gotoxy(5,3);
	            printf("0 0");
	            gotoxy(6,4);
	            printf("0 0");
	        }
	        else
    			ant1->prox = NULL;
        }
        else
        if((*mdesvirado)->qntCartas > 1)
        {
        	(*mvirado)->prim = (*mdesvirado)->prim->prox;
        	(*mdesvirado)->prim->prox = NULL;
        	aux1 = (*mvirado)->prim;
           	(*mvirado)->qntCartas = (*mdesvirado)->qntCartas-1;
           	(*mdesvirado)->qntCartas = 1;
            while(aux1 != NULL)
            {
            	aux1->status = 0;
            	aux1 = aux1->prox;
            }
			gotoxy(5,3);
            ImprimeCarta((*mvirado)->prim);
            gotoxy(6,4);
            ImprimeCarta((*mvirado)->prim);	            	
    		aux2 = (*mdesvirado)->prim;
    		Espaco();
    		gotoxy(13,3);
    		ImprimeCarta(aux2);
    		gotoxy(14,4);
    		ImprimeCarta(aux2);
        }
        else
        	Mensagem();
    }
    else
    if(Origem==15)
    {
    	if((*mdesvirado)->qntCartas > 0)
	    {
    		if(Destino==1)
    		{	
	    		aux1 = (*mdesvirado)->prim;
	        	while(aux1->prox != NULL)		
				{	
					ant1 = aux1;				
	    			aux1 = aux1->prox;
	    		}
	    		Destino1(*m1, &valida, aux1, &aux2);
   				if(valida > 0)
	    		{
		    		(*m1)->qntCartas++;
		    		gotoxy(9,(*L1)++);
		        	ImprimeCarta(aux2);
	    		}
	    		else
	    			Mensagem();
	        }
	        else
	        if(Destino==2)
    		{	
	    		aux1 = (*mdesvirado)->prim;
	        	while(aux1->prox != NULL)		
				{	
					ant1 = aux1;				
	    			aux1 = aux1->prox;
	    		}
	    		Destino1(*m2, &valida, aux1, &aux2);
   				if(valida > 0)
	    		{
		    		(*m2)->qntCartas++;
		    		gotoxy(19,(*L2)++);
		        	ImprimeCarta(aux2);
	    		}
	    		else
	    			Mensagem();
	        }
	        else
	        if(Destino==3)
    		{	
	    		aux1 = (*mdesvirado)->prim;
	        	while(aux1->prox != NULL)		
				{	
					ant1 = aux1;				
	    			aux1 = aux1->prox;
	    		}
	    		Destino1(*m3, &valida, aux1, &aux2);
   				if(valida > 0)
	    		{
		    		(*m3)->qntCartas++;
		    		gotoxy(29,(*L3)++);
		        	ImprimeCarta(aux2);
	    		}
	    		else
	    			Mensagem();
	        }
	        else
	        if(Destino==4)
    		{	
	    		aux1 = (*mdesvirado)->prim;
	        	while(aux1->prox != NULL)		
				{	
					ant1 = aux1;				
	    			aux1 = aux1->prox;
	    		}
	    		Destino1(*m4, &valida, aux1, &aux2);
   				if(valida > 0)
	    		{
		    		(*m4)->qntCartas++;
		    		gotoxy(39,(*L4)++);
		        	ImprimeCarta(aux2);
	    		}
	    		else
	    			Mensagem();
	        }
	        else
	        if(Destino==5)
    		{	
	    		aux1 = (*mdesvirado)->prim;
	        	while(aux1->prox != NULL)		
				{	
					ant1 = aux1;				
	    			aux1 = aux1->prox;
	    		}
	    		Destino1(*m5, &valida, aux1, &aux2);
   				if(valida > 0)
	    		{
		    		(*m5)->qntCartas++;
		    		gotoxy(49,(*L5)++);
		        	ImprimeCarta(aux2);
	    		}
	    		else
	    			Mensagem();
	        }
	        else
	        if(Destino==6)
    		{	
	    		aux1 = (*mdesvirado)->prim;
	        	while(aux1->prox != NULL)		
				{	
					ant1 = aux1;				
	    			aux1 = aux1->prox;
	    		}
	    		Destino1(*m6, &valida, aux1, &aux2);
   				if(valida > 0)
	    		{
		    		(*m6)->qntCartas++;
		    		gotoxy(59,(*L6)++);
		        	ImprimeCarta(aux2);
	    		}
	    		else
	    			Mensagem();
	        }
	        else
	        if(Destino==7)
    		{	
	    		aux1 = (*mdesvirado)->prim;
	        	while(aux1->prox != NULL)		
				{	
					ant1 = aux1;				
	    			aux1 = aux1->prox;
	    		}
	    		Destino1(*m7, &valida, aux1, &aux2);
   				if(valida > 0)
	    		{
		    		(*m7)->qntCartas++;
		    		gotoxy(69,(*L7)++);
		        	ImprimeCarta(aux2);
	    		}
	    		else
	    			Mensagem();
	        }
	        else
	        if(Destino==8)
    		{	
	    		aux1 = (*mdesvirado)->prim;
	        	while(aux1->prox != NULL)		
				{	
					ant1 = aux1;				
	    			aux1 = aux1->prox;
	    		}
	    		DestinoA(*mA, &valida, aux1, &aux2);
   				if(valida > 0)
	    		{
		    		(*mA)->qntCartas++;
		    		gotoxy(42,3);
		        	ImprimeCarta(aux2);
		        	gotoxy(43,4);
		        	ImprimeCarta(aux2);
	    		}
	    		else
	    			Mensagem();
	        }
	        else
	        if(Destino==9)
    		{	
	    		aux1 = (*mdesvirado)->prim;
	        	while(aux1->prox != NULL)		
				{	
					ant1 = aux1;				
	    			aux1 = aux1->prox;
	    		}
	    		DestinoA(*mB, &valida, aux1, &aux2);
   				if(valida > 0)
	    		{
		    		(*mB)->qntCartas++;
		    		gotoxy(50,3);
		        	ImprimeCarta(aux2);
		        	gotoxy(51,4);
		        	ImprimeCarta(aux2);
	    		}
	    		else
	    			Mensagem();
	        }
	        else
	        if(Destino==10)
    		{	
	    		aux1 = (*mdesvirado)->prim;
	        	while(aux1->prox != NULL)		
				{	
					ant1 = aux1;				
	    			aux1 = aux1->prox;
	    		}
	    		DestinoA(*mC, &valida, aux1, &aux2);
   				if(valida > 0)
	    		{
		    		(*mC)->qntCartas++;
		    		gotoxy(58,3);
		        	ImprimeCarta(aux2);
		        	gotoxy(59,4);
		        	ImprimeCarta(aux2);
	    		}
	    		else
	    			Mensagem();
	        }
	        else
	        if(Destino==11)
    		{	
	    		aux1 = (*mdesvirado)->prim;
	        	while(aux1->prox != NULL)		
				{	
					ant1 = aux1;				
	    			aux1 = aux1->prox;
	    		}
	    		DestinoA(*mD, &valida, aux1, &aux2);
   				if(valida > 0)
	    		{
		    		(*mD)->qntCartas++;
		    		gotoxy(66,3);
		        	ImprimeCarta(aux2);
		        	gotoxy(67,4);
		        	ImprimeCarta(aux2);
	    		}
	    		else
	    			Mensagem();
	        }
	        else
	        	Mensagem();
	        if(valida > 0)
	        {
		    	(*mdesvirado)->qntCartas--;
		    	if((*mdesvirado)->qntCartas==0)
		    	{
		    		(*mdesvirado)->prim = NULL;
		    		Espaco();
		    	}   
		        else
		        {
		        	ant1->prox = NULL;
		        	Espaco();
		        	gotoxy(13,3);
	    			ImprimeCarta(ant1);
	    			gotoxy(14,4);
	    			ImprimeCarta(ant1);
		        }
	        }
    	}
    	else
	        Mensagem();
    }
    else
    if(Origem == 1)
    {
    	aux1 = (*m1)->prim;
    	while(aux1 != NULL && aux1->status == 0)
    	{
    		aux1 = aux1->prox;
    		Pos++;
    	}
    	if((*m1)->qntCartas > 0 && Pos <= (*m1)->qntCartas && Pos > 0)
	    {
    		if(Destino==2)
    		{	
	    		aux1 = (*m1)->prim;
	        	while(aux1->prox != NULL && Pos>1)		
				{	
					ant1 = aux1;			
	    			aux1 = aux1->prox;
	    			Pos--;
	    		}
	    		Destino1(*m2, &valida, aux1, &aux2);
	    		while(aux1 != NULL)
	    		{
	    			aux1 = aux1->prox;
	    			Cont++;
	    		}
   				if(valida > 0)
	    		{
		    		(*m2)->qntCartas += Cont;
		    		for(int i=Cont;i>0;i--)
		    		{
		    			gotoxy(19,(*L2)++);
		        		ImprimeCarta(aux2);
		        		aux2 = aux2->prox;
		    		}
	    		}
	    		else
	    			Mensagem();
	        }
	        else
	        if(Destino==3)
    		{	
	    		aux1 = (*m1)->prim;
	        	while(aux1->prox != NULL && Pos>1)		
				{	
					ant1 = aux1;				
	    			aux1 = aux1->prox;
	    			Pos--;
	    		}
	    		Destino1(*m3, &valida, aux1, &aux2);
	    		while(aux1 != NULL)
	    		{
	    			aux1 = aux1->prox;
	    			Cont++;
	    		}
   				if(valida > 0)
	    		{
		    		(*m3)->qntCartas += Cont;
		    		for(int i=Cont;i>0;i--)
		    		{
		    			gotoxy(29,(*L3)++);
		        		ImprimeCarta(aux2);
		        		aux2 = aux2->prox;
		    		}
	    		}
	    		else
	    			Mensagem();
	        }
	    	else
	        if(Destino==4)
    		{	
	    		aux1 = (*m1)->prim;
	        	while(aux1->prox != NULL && Pos>1)		
				{	
					ant1 = aux1;				
	    			aux1 = aux1->prox;
	    			Pos--;
	    		}
	    		Destino1(*m4, &valida, aux1, &aux2);
	    		while(aux1 != NULL)
	    		{
	    			aux1 = aux1->prox;
	    			Cont++;
	    		}
   				if(valida > 0)
	    		{
		    		(*m4)->qntCartas += Cont;
		    		for(int i=Cont;i>0;i--)
		    		{
		    			gotoxy(39,(*L4)++);
		        		ImprimeCarta(aux2);
		        		aux2 = aux2->prox;
		    		}
	    		}
	    		else
	    			Mensagem();
	        }
	        else
	        if(Destino==5)
    		{	
	    		aux1 = (*m1)->prim;
	        	while(aux1->prox != NULL && Pos>1)		
				{	
					ant1 = aux1;				
	    			aux1 = aux1->prox;
	    			Pos--;
	    		}
	    		Destino1(*m5, &valida, aux1, &aux2);
	    		while(aux1 != NULL)
	    		{
	    			aux1 = aux1->prox;
	    			Cont++;
	    		}
   				if(valida > 0)
	    		{
		    		(*m5)->qntCartas += Cont;
		    		for(int i=Cont;i>0;i--)
		    		{
		    			gotoxy(49,(*L5)++);
		        		ImprimeCarta(aux2);
		        		aux2 = aux2->prox;
		    		}
	    		}
	    		else
	    			Mensagem();
	        }
	        else
	        if(Destino==6)
    		{	
	    		aux1 = (*m1)->prim;
	        	while(aux1->prox != NULL && Pos>1)		
				{	
					ant1 = aux1;				
	    			aux1 = aux1->prox;
	    			Pos--;
	    		}
	    		Destino1(*m6, &valida, aux1, &aux2);
	    		while(aux1 != NULL)
	    		{
	    			aux1 = aux1->prox;
	    			Cont++;
	    		}
   				if(valida > 0)
	    		{
		    		(*m6)->qntCartas += Cont;
		    		for(int i=Cont;i>0;i--)
		    		{
		    			gotoxy(59,(*L6)++);
		        		ImprimeCarta(aux2);
		        		aux2 = aux2->prox;
		    		}
	    		}
	    		else
	    			Mensagem();
	        }
	        else
	        if(Destino==7)
    		{	
	    		aux1 = (*m1)->prim;
	        	while(aux1->prox != NULL && Pos>1)		
				{	
					ant1 = aux1;				
	    			aux1 = aux1->prox;
	    			Pos--;
	    		}
	    		Destino1(*m7, &valida, aux1, &aux2);
	    		while(aux1 != NULL)
	    		{
	    			aux1 = aux1->prox;
	    			Cont++;
	    		}
   				if(valida > 0)
	    		{
		    		(*m7)->qntCartas += Cont;
		    		for(int i=Cont;i>0;i--)
		    		{
		    			gotoxy(69,(*L7)++);
		        		ImprimeCarta(aux2);
		        		aux2 = aux2->prox;
		    		}
	    		}
	    		else
	    			Mensagem();
	        }
	        else
	        if(Destino==8)
    		{	
	    		aux1 = (*m1)->prim;
	        	while(aux1->prox != NULL && Pos>1)		
				{	
					ant1 = aux1;				
	    			aux1 = aux1->prox;
	    			Pos--;
	    		}
	    		DestinoA(*mA, &valida, aux1, &aux2);
	    		while(aux1 != NULL)
	    		{
	    			aux1 = aux1->prox;
	    			Cont++;
	    		}
   				if(valida > 0)
	    		{
		    		(*mA)->qntCartas += Cont;
	    			gotoxy(42,3);
	        		ImprimeCarta(aux2);
	        		gotoxy(43,4);
	        		ImprimeCarta(aux2);
	    		}
	    		else
	    			Mensagem();
	        }
	        else
			if(Destino==9)
    		{	
	    		aux1 = (*m1)->prim;
	        	while(aux1->prox != NULL && Pos>1)		
				{	
					ant1 = aux1;				
	    			aux1 = aux1->prox;
	    			Pos--;
	    		}
	    		DestinoA(*mB, &valida, aux1, &aux2);
	    		while(aux1 != NULL)
	    		{
	    			aux1 = aux1->prox;
	    			Cont++;
	    		}
   				if(valida > 0)
	    		{
		    		(*mB)->qntCartas += Cont;
	    			gotoxy(50,3);
	        		ImprimeCarta(aux2);
	        		gotoxy(51,4);
	        		ImprimeCarta(aux2);
	    		}
	    		else
	    			Mensagem();
	        }
			else
			if(Destino==10)
    		{	
	    		aux1 = (*m1)->prim;
	        	while(aux1->prox != NULL && Pos>1)		
				{	
					ant1 = aux1;				
	    			aux1 = aux1->prox;
	    			Pos--;
	    		}
	    		DestinoA(*mC, &valida, aux1, &aux2);
	    		while(aux1 != NULL)
	    		{
	    			aux1 = aux1->prox;
	    			Cont++;
	    		}
   				if(valida > 0)
	    		{
		    		(*mC)->qntCartas += Cont;
	    			gotoxy(58,3);
	        		ImprimeCarta(aux2);
	        		gotoxy(59,4);
	        		ImprimeCarta(aux2);
	    		}
	    		else
	    			Mensagem();
	        }
	        else
			if(Destino==11)
    		{	
	    		aux1 = (*m1)->prim;
	        	while(aux1->prox != NULL && Pos>1)		
				{	
					ant1 = aux1;				
	    			aux1 = aux1->prox;
	    			Pos--;
	    		}
	    		DestinoA(*mD, &valida, aux1, &aux2);
	    		while(aux1 != NULL)
	    		{
	    			aux1 = aux1->prox;
	    			Cont++;
	    		}
   				if(valida > 0)
	    		{
		    		(*mD)->qntCartas += Cont;
	    			gotoxy(66,3);
	        		ImprimeCarta(aux2);
	        		gotoxy(67,4);
	        		ImprimeCarta(aux2);
	    		}
	    		else
	    			Mensagem();
	        }
	        else
	        	Mensagem();
	        if(valida > 0)
	        {
		    	(*m1)->qntCartas -= Cont;
		    	if((*m1)->qntCartas==0)
			    {
			    	(*m1)->prim = NULL;
			    	while(Cont>0)
			    	{
			    		gotoxy(9,--(*L1));
	        			printf("   ");
	        			Cont--;
			    	}
			    }
		        else
		        {
		        	ant1->prox = NULL;
		        	while(Cont>0)
			    	{
			    		gotoxy(9,--(*L1));
	        			printf("   ");
	        			Cont--;
			    	}
			    	if(ant1->status == 0)
			    	{
			    		ant1->status = 1;
			    		gotoxy(9,(*L1)++);
		        		ImprimeCarta(ant1);
			    	}
		        }
	        }
    	}
    	else
	        Mensagem();
    }
    else
    if(Origem == 2)
    {
    	aux1 = (*m2)->prim;
    	while(aux1 != NULL && aux1->status == 0)
    	{
    		aux1 = aux1->prox;
    		Pos++;
    	}
    	if((*m2)->qntCartas > 0 && Pos <= (*m2)->qntCartas && Pos > 0)
	    { 
    		if(Destino==1)
    		{	
	    		aux1 = (*m2)->prim;
	        	while(aux1->prox != NULL && Pos>1)		
				{	
					ant1 = aux1;				
	    			aux1 = aux1->prox;
	    			Pos--;
	    		}
	    		Destino1(*m1, &valida, aux1, &aux2);
	    		while(aux1 != NULL)
	    		{
	    			aux1 = aux1->prox;
	    			Cont++;
	    		}
   				if(valida > 0)
	    		{
		    		(*m1)->qntCartas += Cont;
		    		for(int i=Cont;i>0;i--)
		    		{
		    			gotoxy(9,(*L1)++);
		        		ImprimeCarta(aux2);
		        		aux2 = aux2->prox;
		    		}
	    		}
	    		else
	    			Mensagem();
	        }
	        else
	        if(Destino==3)
    		{	
	    		aux1 = (*m2)->prim;
	        	while(aux1->prox != NULL && Pos>1)		
				{	
					ant1 = aux1;				
	    			aux1 = aux1->prox;
	    			Pos--;
	    		}
	    		Destino1(*m3, &valida, aux1, &aux2);
	    		while(aux1 != NULL)
	    		{
	    			aux1 = aux1->prox;
	    			Cont++;
	    		}
   				if(valida > 0)
	    		{
		    		(*m3)->qntCartas += Cont;
		    		for(int i=Cont;i>0;i--)
		    		{
		    			gotoxy(29,(*L3)++);
		        		ImprimeCarta(aux2);
		        		aux2 = aux2->prox;
		    		}
	    		}
	    		else
	    			Mensagem();
	        }
	    	else
	        if(Destino==4)
    		{	
	    		aux1 = (*m2)->prim;
	        	while(aux1->prox != NULL && Pos>1)		
				{	
					ant1 = aux1;				
	    			aux1 = aux1->prox;
	    			Pos--;
	    		}
	    		Destino1(*m4, &valida, aux1, &aux2);
	    		while(aux1 != NULL)
	    		{
	    			aux1 = aux1->prox;
	    			Cont++;
	    		}
   				if(valida > 0)
	    		{
		    		(*m4)->qntCartas += Cont;
		    		for(int i=Cont;i>0;i--)
		    		{
		    			gotoxy(39,(*L4)++);
		        		ImprimeCarta(aux2);
		        		aux2 = aux2->prox;
		    		}
	    		}
	    		else
	    			Mensagem();
	        }
	        else
	        if(Destino==5)
    		{	
	    		aux1 = (*m2)->prim;
	        	while(aux1->prox != NULL && Pos>1)		
				{	
					ant1 = aux1;				
	    			aux1 = aux1->prox;
	    			Pos--;
	    		}
	    		Destino1(*m5, &valida, aux1, &aux2);
	    		while(aux1 != NULL)
	    		{
	    			aux1 = aux1->prox;
	    			Cont++;
	    		}
   				if(valida > 0)
	    		{
		    		(*m5)->qntCartas += Cont;
		    		for(int i=Cont;i>0;i--)
		    		{
		    			gotoxy(49,(*L5)++);
		        		ImprimeCarta(aux2);
		        		aux2 = aux2->prox;
		    		}
	    		}
	    		else
	    			Mensagem();
	        }
	        else
	        if(Destino==6)
    		{	
	    		aux1 = (*m2)->prim;
	        	while(aux1->prox != NULL && Pos>1)		
				{	
					ant1 = aux1;				
	    			aux1 = aux1->prox;
	    			Pos--;
	    		}
	    		Destino1(*m6, &valida, aux1, &aux2);
	    		while(aux1 != NULL)
	    		{
	    			aux1 = aux1->prox;
	    			Cont++;
	    		}
   				if(valida > 0)
	    		{
		    		(*m6)->qntCartas += Cont;
		    		for(int i=Cont;i>0;i--)
		    		{
		    			gotoxy(59,(*L6)++);
		        		ImprimeCarta(aux2);
		        		aux2 = aux2->prox;
		    		}
	    		}
	    		else
	    			Mensagem();
	        }
	        else
	        if(Destino==7)
    		{	
	    		aux1 = (*m2)->prim;
	        	while(aux1->prox != NULL && Pos>1)		
				{	
					ant1 = aux1;				
	    			aux1 = aux1->prox;
	    			Pos--;
	    		}
	    		Destino1(*m7, &valida, aux1, &aux2);
	    		while(aux1 != NULL)
	    		{
	    			aux1 = aux1->prox;
	    			Cont++;
	    		}
   				if(valida > 0)
	    		{
		    		(*m7)->qntCartas += Cont;
		    		for(int i=Cont;i>0;i--)
		    		{
		    			gotoxy(69,(*L7)++);
		        		ImprimeCarta(aux2);
		        		aux2 = aux2->prox;
		    		}
	    		}
	    		else
	    			Mensagem();
	        }
	        else
	        if(Destino==8)
    		{	
	    		aux1 = (*m2)->prim;
	        	while(aux1->prox != NULL && Pos>1)		
				{	
					ant1 = aux1;				
	    			aux1 = aux1->prox;
	    			Pos--;
	    		}
	    		DestinoA(*mA, &valida, aux1, &aux2);
	    		while(aux1 != NULL)
	    		{
	    			aux1 = aux1->prox;
	    			Cont++;
	    		}
   				if(valida > 0)
	    		{
		    		(*mA)->qntCartas += Cont;
	    			gotoxy(42,3);
	        		ImprimeCarta(aux2);
	        		gotoxy(43,4);
	        		ImprimeCarta(aux2);
	    		}
	    		else
	    			Mensagem();
	        }
	        else
			if(Destino==9)
    		{	
	    		aux1 = (*m2)->prim;
	        	while(aux1->prox != NULL && Pos>1)		
				{	
					ant1 = aux1;				
	    			aux1 = aux1->prox;
	    			Pos--;
	    		}
	    		DestinoA(*mB, &valida, aux1, &aux2);
	    		while(aux1 != NULL)
	    		{
	    			aux1 = aux1->prox;
	    			Cont++;
	    		}
   				if(valida > 0)
	    		{
		    		(*mB)->qntCartas += Cont;
	    			gotoxy(50,3);
	        		ImprimeCarta(aux2);
	        		gotoxy(51,4);
	        		ImprimeCarta(aux2);
	    		}
	    		else
	    			Mensagem();
	        }
			else
			if(Destino==10)
    		{	
	    		aux1 = (*m2)->prim;
	        	while(aux1->prox != NULL && Pos>1)		
				{	
					ant1 = aux1;				
	    			aux1 = aux1->prox;
	    			Pos--;
	    		}
	    		DestinoA(*mC, &valida, aux1, &aux2);
	    		while(aux1 != NULL)
	    		{
	    			aux1 = aux1->prox;
	    			Cont++;
	    		}
   				if(valida > 0)
	    		{
		    		(*mC)->qntCartas += Cont;
	    			gotoxy(58,3);
	        		ImprimeCarta(aux2);
	        		gotoxy(59,4);
	        		ImprimeCarta(aux2);
	    		}
	    		else
	    			Mensagem();
	        }
	        else
			if(Destino==11)
    		{	
	    		aux1 = (*m2)->prim;
	        	while(aux1->prox != NULL && Pos>1)		
				{	
					ant1 = aux1;				
	    			aux1 = aux1->prox;
	    			Pos--;
	    		}
	    		DestinoA(*mD, &valida, aux1, &aux2);
	    		while(aux1 != NULL)
	    		{
	    			aux1 = aux1->prox;
	    			Cont++;
	    		}
   				if(valida > 0)
	    		{
		    		(*mD)->qntCartas += Cont;
	    			gotoxy(66,3);
	        		ImprimeCarta(aux2);
	        		gotoxy(67,4);
	        		ImprimeCarta(aux2);
	    		}
	    		else
	    			Mensagem();
	        }
	        else
	        	Mensagem();
	        if(valida > 0)
	        {
		    	(*m2)->qntCartas -= Cont;
		    	if((*m2)->qntCartas==0)
			    {
			    	(*m2)->prim = NULL;
			    	while(Cont>0)
			    	{
			    		gotoxy(19,--(*L2));
	        			printf("   ");
	        			Cont--;
			    	}
			    }
		        else
		        {
		        	ant1->prox = NULL;
		        	while(Cont>0)
			    	{
			    		gotoxy(19,--(*L2));
	        			printf("   ");
	        			Cont--;
			    	}
			    	if(ant1->status == 0)
			    	{
			    		ant1->status = 1;
			    		gotoxy(19,(*L2)++);
		                ImprimeCarta(ant1);
			    	}
		        }
	        }
    	}
    	else
	        Mensagem();
	}
	else
    if(Origem == 3)
    {
    	aux1 = (*m3)->prim;
    	while(aux1 != NULL && aux1->status == 0)
    	{
    		aux1 = aux1->prox;
    		Pos++;
    	}
    	if((*m3)->qntCartas > 0 && Pos <= (*m3)->qntCartas && Pos > 0)
	    { 
    		if(Destino==1)
    		{	
	    		aux1 = (*m3)->prim;
	        	while(aux1->prox != NULL && Pos>1)		
				{	
					ant1 = aux1;				
	    			aux1 = aux1->prox;
	    			Pos--;
	    		}
	    		Destino1(*m1, &valida, aux1, &aux2);
	    		while(aux1 != NULL)
	    		{
	    			aux1 = aux1->prox;
	    			Cont++;
	    		}
   				if(valida > 0)
	    		{
		    		(*m1)->qntCartas += Cont;
		    		for(int i=Cont;i>0;i--)
		    		{
		    			gotoxy(9,(*L1)++);
		        		ImprimeCarta(aux2);
		        		aux2 = aux2->prox;
		    		}
	    		}
	    		else
	    			Mensagem();
	        }
	        else
	        if(Destino==2)
    		{	
	    		aux1 = (*m3)->prim;
	        	while(aux1->prox != NULL && Pos>1)		
				{	
					ant1 = aux1;				
	    			aux1 = aux1->prox;
	    			Pos--;
	    		}
	    		Destino1(*m2, &valida, aux1, &aux2);
	    		while(aux1 != NULL)
	    		{
	    			aux1 = aux1->prox;
	    			Cont++;
	    		}
   				if(valida > 0)
	    		{
		    		(*m2)->qntCartas += Cont;
		    		for(int i=Cont;i>0;i--)
		    		{
		    			gotoxy(19,(*L2)++);
		        		ImprimeCarta(aux2);
		        		aux2 = aux2->prox;
		    		}
	    		}
	    		else
	    			Mensagem();
	        }
	    	else
	        if(Destino==4)
    		{	
	    		aux1 = (*m3)->prim;
	        	while(aux1->prox != NULL && Pos>1)		
				{	
					ant1 = aux1;				
	    			aux1 = aux1->prox;
	    			Pos--;
	    		}
	    		Destino1(*m4, &valida, aux1, &aux2);
	    		while(aux1 != NULL)
	    		{
	    			aux1 = aux1->prox;
	    			Cont++;
	    		}
   				if(valida > 0)
	    		{
		    		(*m4)->qntCartas += Cont;
		    		for(int i=Cont;i>0;i--)
		    		{
		    			gotoxy(39,(*L4)++);
		        		ImprimeCarta(aux2);
		        		aux2 = aux2->prox;
		    		}
	    		}
	    		else
	    			Mensagem();
	        }
	        else
	        if(Destino==5)
    		{	
	    		aux1 = (*m3)->prim;
	        	while(aux1->prox != NULL && Pos>1)		
				{	
					ant1 = aux1;				
	    			aux1 = aux1->prox;
	    			Pos--;
	    		}
	    		Destino1(*m5, &valida, aux1, &aux2);
	    		while(aux1 != NULL)
	    		{
	    			aux1 = aux1->prox;
	    			Cont++;
	    		}
   				if(valida > 0)
	    		{
		    		(*m5)->qntCartas += Cont;
		    		for(int i=Cont;i>0;i--)
		    		{
		    			gotoxy(49,(*L5)++);
		        		ImprimeCarta(aux2);
		        		aux2 = aux2->prox;
		    		}
	    		}
	    		else
	    			Mensagem();
	        }
	        else
	        if(Destino==6)
    		{	
	    		aux1 = (*m3)->prim;
	        	while(aux1->prox != NULL && Pos>1)		
				{	
					ant1 = aux1;				
	    			aux1 = aux1->prox;
	    			Pos--;
	    		}
	    		Destino1(*m6, &valida, aux1, &aux2);
	    		while(aux1 != NULL)
	    		{
	    			aux1 = aux1->prox;
	    			Cont++;
	    		}
   				if(valida > 0)
	    		{
		    		(*m6)->qntCartas += Cont;
		    		for(int i=Cont;i>0;i--)
		    		{
		    			gotoxy(59,(*L6)++);
		        		ImprimeCarta(aux2);
		        		aux2 = aux2->prox;
		    		}
	    		}
	    		else
	    			Mensagem();
	        }
	        else
	        if(Destino==7)
    		{	
	    		aux1 = (*m3)->prim;
	        	while(aux1->prox != NULL && Pos>1)		
				{	
					ant1 = aux1;				
	    			aux1 = aux1->prox;
	    			Pos--;
	    		}
	    		Destino1(*m7, &valida, aux1, &aux2);
	    		while(aux1 != NULL)
	    		{
	    			aux1 = aux1->prox;
	    			Cont++;
	    		}
   				if(valida > 0)
	    		{
		    		(*m7)->qntCartas += Cont;
		    		for(int i=Cont;i>0;i--)
		    		{
		    			gotoxy(69,(*L7)++);
		        		ImprimeCarta(aux2);
		        		aux2 = aux2->prox;
		    		}
	    		}
	    		else
	    			Mensagem();
	        }
	        else
	        if(Destino==8)
    		{	
	    		aux1 = (*m3)->prim;
	        	while(aux1->prox != NULL && Pos>1)		
				{	
					ant1 = aux1;				
	    			aux1 = aux1->prox;
	    			Pos--;
	    		}
	    		DestinoA(*mA, &valida, aux1, &aux2);
	    		while(aux1 != NULL)
	    		{
	    			aux1 = aux1->prox;
	    			Cont++;
	    		}
   				if(valida > 0)
	    		{
		    		(*mA)->qntCartas += Cont;
	    			gotoxy(42,3);
	        		ImprimeCarta(aux2);
	        		gotoxy(43,4);
	        		ImprimeCarta(aux2);
	    		}
	    		else
	    			Mensagem();
	        }
	        else
			if(Destino==9)
    		{	
	    		aux1 = (*m3)->prim;
	        	while(aux1->prox != NULL && Pos>1)		
				{	
					ant1 = aux1;				
	    			aux1 = aux1->prox;
	    			Pos--;
	    		}
	    		DestinoA(*mB, &valida, aux1, &aux2);
	    		while(aux1 != NULL)
	    		{
	    			aux1 = aux1->prox;
	    			Cont++;
	    		}
   				if(valida > 0)
	    		{
		    		(*mB)->qntCartas += Cont;
	    			gotoxy(50,3);
	        		ImprimeCarta(aux2);
	        		gotoxy(51,4);
	        		ImprimeCarta(aux2);
	    		}
	    		else
	    			Mensagem();
	        }
			else
			if(Destino==10)
    		{	
	    		aux1 = (*m3)->prim;
	        	while(aux1->prox != NULL && Pos>1)		
				{	
					ant1 = aux1;				
	    			aux1 = aux1->prox;
	    			Pos--;
	    		}
	    		DestinoA(*mC, &valida, aux1, &aux2);
	    		while(aux1 != NULL)
	    		{
	    			aux1 = aux1->prox;
	    			Cont++;
	    		}
   				if(valida > 0)
	    		{
		    		(*mC)->qntCartas += Cont;
	    			gotoxy(58,3);
	        		ImprimeCarta(aux2);
	        		gotoxy(59,4);
	        		ImprimeCarta(aux2);
	    		}
	    		else
	    			Mensagem();
	        }
	        else
			if(Destino==11)
    		{	
	    		aux1 = (*m3)->prim;
	        	while(aux1->prox != NULL && Pos>1)		
				{	
					ant1 = aux1;				
	    			aux1 = aux1->prox;
	    			Pos--;
	    		}
	    		DestinoA(*mD, &valida, aux1, &aux2);
	    		while(aux1 != NULL)
	    		{
	    			aux1 = aux1->prox;
	    			Cont++;
	    		}
   				if(valida > 0)
	    		{
		    		(*mD)->qntCartas += Cont;
	    			gotoxy(66,3);
	        		ImprimeCarta(aux2);
	        		gotoxy(67,4);
	        		ImprimeCarta(aux2);
	    		}
	    		else
	    			Mensagem();
	        }
	        else
	        	Mensagem();
	        if(valida > 0)
	        {
		    	(*m3)->qntCartas -= Cont;
		    	if((*m3)->qntCartas==0)
			    {
			    	(*m3)->prim = NULL;
			    	while(Cont>0)
			    	{
			    		gotoxy(29,--(*L3));
	        			printf("   ");
	        			Cont--;
			    	}
			    }
		        else
		        {
		        	ant1->prox = NULL;
		        	while(Cont>0)
			    	{
			    		gotoxy(29,--(*L3));
	        			printf("   ");
	        			Cont--;
			    	}
			    	if(ant1->status == 0)
			    	{
			    		ant1->status = 1;
			    		gotoxy(29,(*L3)++);
		                ImprimeCarta(ant1);
			    	}
		        }
	        }
    	}
    	else
	        Mensagem();
	}
	else
    if(Origem == 4)
    {
    	aux1 = (*m4)->prim;
    	while(aux1 != NULL && aux1->status == 0)
    	{
    		aux1 = aux1->prox;
    		Pos++;
    	}
    	if((*m4)->qntCartas > 0 && Pos <= (*m4)->qntCartas && Pos > 0)
	    { 
    		if(Destino==1)
    		{	
	    		aux1 = (*m4)->prim;
	        	while(aux1->prox != NULL && Pos>1)		
				{	
					ant1 = aux1;				
	    			aux1 = aux1->prox;
	    			Pos--;
	    		}
	    		Destino1(*m1, &valida, aux1, &aux2);
	    		while(aux1 != NULL)
	    		{
	    			aux1 = aux1->prox;
	    			Cont++;
	    		}
   				if(valida > 0)
	    		{
		    		(*m1)->qntCartas += Cont;
		    		for(int i=Cont;i>0;i--)
		    		{
		    			gotoxy(9,(*L1)++);
		        		ImprimeCarta(aux2);
		        		aux2 = aux2->prox;
		    		}
	    		}
	    		else
	    			Mensagem();
	        }
	        else
	        if(Destino==2)
    		{	
	    		aux1 = (*m4)->prim;
	        	while(aux1->prox != NULL && Pos>1)		
				{	
					ant1 = aux1;				
	    			aux1 = aux1->prox;
	    			Pos--;
	    		}
	    		Destino1(*m2, &valida, aux1, &aux2);
	    		while(aux1 != NULL)
	    		{
	    			aux1 = aux1->prox;
	    			Cont++;
	    		}
   				if(valida > 0)
	    		{
		    		(*m2)->qntCartas += Cont;
		    		for(int i=Cont;i>0;i--)
		    		{
		    			gotoxy(19,(*L2)++);
		        		ImprimeCarta(aux2);
		        		aux2 = aux2->prox;
		    		}
	    		}
	    		else
	    			Mensagem();
	        }
	    	else
	        if(Destino==3)
    		{	
	    		aux1 = (*m4)->prim;
	        	while(aux1->prox != NULL && Pos>1)		
				{	
					ant1 = aux1;				
	    			aux1 = aux1->prox;
	    			Pos--;
	    		}
	    		Destino1(*m3, &valida, aux1, &aux2);
	    		while(aux1 != NULL)
	    		{
	    			aux1 = aux1->prox;
	    			Cont++;
	    		}
   				if(valida > 0)
	    		{
		    		(*m3)->qntCartas += Cont;
		    		for(int i=Cont;i>0;i--)
		    		{
		    			gotoxy(29,(*L3)++);
		        		ImprimeCarta(aux2);
		        		aux2 = aux2->prox;
		    		}
	    		}
	    		else
	    			Mensagem();
	        }
	        else
	        if(Destino==5)
    		{	
	    		aux1 = (*m4)->prim;
	        	while(aux1->prox != NULL && Pos>1)		
				{	
					ant1 = aux1;				
	    			aux1 = aux1->prox;
	    			Pos--;
	    		}
	    		Destino1(*m5, &valida, aux1, &aux2);
	    		while(aux1 != NULL)
	    		{
	    			aux1 = aux1->prox;
	    			Cont++;
	    		}
   				if(valida > 0)
	    		{
		    		(*m5)->qntCartas += Cont;
		    		for(int i=Cont;i>0;i--)
		    		{
		    			gotoxy(49,(*L5)++);
		        		ImprimeCarta(aux2);
		        		aux2 = aux2->prox;
		    		}
	    		}
	    		else
	    			Mensagem();
	        }
	        else
	        if(Destino==6)
    		{	
	    		aux1 = (*m4)->prim;
	        	while(aux1->prox != NULL && Pos>1)		
				{	
					ant1 = aux1;				
	    			aux1 = aux1->prox;
	    			Pos--;
	    		}
	    		Destino1(*m6, &valida, aux1, &aux2);
	    		while(aux1 != NULL)
	    		{
	    			aux1 = aux1->prox;
	    			Cont++;
	    		}
   				if(valida > 0)
	    		{
		    		(*m6)->qntCartas += Cont;
		    		for(int i=Cont;i>0;i--)
		    		{
		    			gotoxy(59,(*L6)++);
		        		ImprimeCarta(aux2);
		        		aux2 = aux2->prox;
		    		}
	    		}
	    		else
	    			Mensagem();
	        }
	        else
	        if(Destino==7)
    		{	
	    		aux1 = (*m4)->prim;
	        	while(aux1->prox != NULL && Pos>1)		
				{	
					ant1 = aux1;				
	    			aux1 = aux1->prox;
	    			Pos--;
	    		}
	    		Destino1(*m7, &valida, aux1, &aux2);
	    		while(aux1 != NULL)
	    		{
	    			aux1 = aux1->prox;
	    			Cont++;
	    		}
   				if(valida > 0)
	    		{
		    		(*m7)->qntCartas += Cont;
		    		for(int i=Cont;i>0;i--)
		    		{
		    			gotoxy(69,(*L7)++);
		        		ImprimeCarta(aux2);
		        		aux2 = aux2->prox;
		    		}
	    		}
	    		else
	    			Mensagem();
	        }
	        else
	        if(Destino==8)
    		{	
	    		aux1 = (*m4)->prim;
	        	while(aux1->prox != NULL && Pos>1)		
				{	
					ant1 = aux1;				
	    			aux1 = aux1->prox;
	    			Pos--;
	    		}
	    		DestinoA(*mA, &valida, aux1, &aux2);
	    		while(aux1 != NULL)
	    		{
	    			aux1 = aux1->prox;
	    			Cont++;
	    		}
   				if(valida > 0)
	    		{
		    		(*mA)->qntCartas += Cont;
	    			gotoxy(42,3);
	        		ImprimeCarta(aux2);
	        		gotoxy(43,4);
	        		ImprimeCarta(aux2);
	    		}
	    		else
	    			Mensagem();
	        }
	        else
			if(Destino==9)
    		{	
	    		aux1 = (*m4)->prim;
	        	while(aux1->prox != NULL && Pos>1)		
				{	
					ant1 = aux1;				
	    			aux1 = aux1->prox;
	    			Pos--;
	    		}
	    		DestinoA(*mB, &valida, aux1, &aux2);
	    		while(aux1 != NULL)
	    		{
	    			aux1 = aux1->prox;
	    			Cont++;
	    		}
   				if(valida > 0)
	    		{
		    		(*mB)->qntCartas += Cont;
	    			gotoxy(50,3);
	        		ImprimeCarta(aux2);
	        		gotoxy(51,4);
	        		ImprimeCarta(aux2);
	    		}
	    		else
	    			Mensagem();
	        }
			else
			if(Destino==10)
    		{	
	    		aux1 = (*m4)->prim;
	        	while(aux1->prox != NULL && Pos>1)		
				{	
					ant1 = aux1;				
	    			aux1 = aux1->prox;
	    			Pos--;
	    		}
	    		DestinoA(*mC, &valida, aux1, &aux2);
	    		while(aux1 != NULL)
	    		{
	    			aux1 = aux1->prox;
	    			Cont++;
	    		}
   				if(valida > 0)
	    		{
		    		(*mC)->qntCartas += Cont;
	    			gotoxy(58,3);
	        		ImprimeCarta(aux2);
	        		gotoxy(59,4);
	        		ImprimeCarta(aux2);
	    		}
	    		else
	    			Mensagem();
	        }
	        else
			if(Destino==11)
    		{	
	    		aux1 = (*m4)->prim;
	        	while(aux1->prox != NULL && Pos>1)		
				{	
					ant1 = aux1;				
	    			aux1 = aux1->prox;
	    			Pos--;
	    		}
	    		DestinoA(*mD, &valida, aux1, &aux2);
	    		while(aux1 != NULL)
	    		{
	    			aux1 = aux1->prox;
	    			Cont++;
	    		}
   				if(valida > 0)
	    		{
		    		(*mD)->qntCartas += Cont;
	    			gotoxy(66,3);
	        		ImprimeCarta(aux2);
	        		gotoxy(67,4);
	        		ImprimeCarta(aux2);
	    		}
	    		else
	    			Mensagem();
	        }
	        else
	        	Mensagem();
	        if(valida > 0)
	        {
		    	(*m4)->qntCartas -= Cont;
		    	if((*m4)->qntCartas==0)
			    {
			    	(*m4)->prim = NULL;
			    	while(Cont>0)
			    	{
			    		gotoxy(39,--(*L4));
	        			printf("   ");
	        			Cont--;
			    	}
			    }
		        else
		        {
		        	ant1->prox = NULL;
		        	while(Cont>0)
			    	{
			    		gotoxy(39,--(*L4));
	        			printf("   ");
	        			Cont--;
			    	}
			    	if(ant1->status == 0)
			    	{
			    		ant1->status = 1;
			    		gotoxy(39,(*L4)++);
		                ImprimeCarta(ant1);
			    	}
		        }
	        }
    	}
    	else
	        Mensagem();
	}
	else
    if(Origem == 5)
    {
    	aux1 = (*m5)->prim;
    	while(aux1 != NULL && aux1->status == 0)
    	{
    		aux1 = aux1->prox;
    		Pos++;
    	}
    	if((*m5)->qntCartas > 0 && Pos <= (*m5)->qntCartas && Pos > 0)
	    { 
    		if(Destino==1)
    		{	
	    		aux1 = (*m5)->prim;
	        	while(aux1->prox != NULL && Pos>1)		
				{	
					ant1 = aux1;				
	    			aux1 = aux1->prox;
	    			Pos--;
	    		}
	    		Destino1(*m1, &valida, aux1, &aux2);
	    		while(aux1 != NULL)
	    		{
	    			aux1 = aux1->prox;
	    			Cont++;
	    		}
   				if(valida > 0)
	    		{
		    		(*m1)->qntCartas += Cont;
		    		for(int i=Cont;i>0;i--)
		    		{
		    			gotoxy(9,(*L1)++);
		        		ImprimeCarta(aux2);
		        		aux2 = aux2->prox;
		    		}
	    		}
	    		else
	    			Mensagem();
	        }
	        else
	        if(Destino==2)
    		{	
	    		aux1 = (*m5)->prim;
	        	while(aux1->prox != NULL && Pos>1)		
				{	
					ant1 = aux1;				
	    			aux1 = aux1->prox;
	    			Pos--;
	    		}
	    		Destino1(*m2, &valida, aux1, &aux2);
	    		while(aux1 != NULL)
	    		{
	    			aux1 = aux1->prox;
	    			Cont++;
	    		}
   				if(valida > 0)
	    		{
		    		(*m2)->qntCartas += Cont;
		    		for(int i=Cont;i>0;i--)
		    		{
		    			gotoxy(19,(*L2)++);
		        		ImprimeCarta(aux2);
		        		aux2 = aux2->prox;
		    		}
	    		}
	    		else
	    			Mensagem();
	        }
	    	else
	        if(Destino==3)
    		{	
	    		aux1 = (*m5)->prim;
	        	while(aux1->prox != NULL && Pos>1)		
				{	
					ant1 = aux1;				
	    			aux1 = aux1->prox;
	    			Pos--;
	    		}
	    		Destino1(*m3, &valida, aux1, &aux2);
	    		while(aux1 != NULL)
	    		{
	    			aux1 = aux1->prox;
	    			Cont++;
	    		}
   				if(valida > 0)
	    		{
		    		(*m3)->qntCartas += Cont;
		    		for(int i=Cont;i>0;i--)
		    		{
		    			gotoxy(29,(*L3)++);
		        		ImprimeCarta(aux2);
		        		aux2 = aux2->prox;
		    		}
	    		}
	    		else
	    			Mensagem();
	        }
	        else
	        if(Destino==4)
    		{	
	    		aux1 = (*m5)->prim;
	        	while(aux1->prox != NULL && Pos>1)		
				{	
					ant1 = aux1;				
	    			aux1 = aux1->prox;
	    			Pos--;
	    		}
	    		Destino1(*m4, &valida, aux1, &aux2);
	    		while(aux1 != NULL)
	    		{
	    			aux1 = aux1->prox;
	    			Cont++;
	    		}
   				if(valida > 0)
	    		{
		    		(*m4)->qntCartas += Cont;
		    		for(int i=Cont;i>0;i--)
		    		{
		    			gotoxy(39,(*L4)++);
		        		ImprimeCarta(aux2);
		        		aux2 = aux2->prox;
		    		}
	    		}
	    		else
	    			Mensagem();
	        }
	        else
	        if(Destino==6)
    		{	
	    		aux1 = (*m5)->prim;
	        	while(aux1->prox != NULL && Pos>1)		
				{	
					ant1 = aux1;				
	    			aux1 = aux1->prox;
	    			Pos--;
	    		}
	    		Destino1(*m6, &valida, aux1, &aux2);
	    		while(aux1 != NULL)
	    		{
	    			aux1 = aux1->prox;
	    			Cont++;
	    		}
   				if(valida > 0)
	    		{
		    		(*m6)->qntCartas += Cont;
		    		for(int i=Cont;i>0;i--)
		    		{
		    			gotoxy(59,(*L6)++);
		        		ImprimeCarta(aux2);
		        		aux2 = aux2->prox;
		    		}
	    		}
	    		else
	    			Mensagem();
	        }
	        else
	        if(Destino==7)
    		{	
	    		aux1 = (*m5)->prim;
	        	while(aux1->prox != NULL && Pos>1)		
				{	
					ant1 = aux1;				
	    			aux1 = aux1->prox;
	    			Pos--;
	    		}
	    		Destino1(*m7, &valida, aux1, &aux2);
	    		while(aux1 != NULL)
	    		{
	    			aux1 = aux1->prox;
	    			Cont++;
	    		}
   				if(valida > 0)
	    		{
		    		(*m7)->qntCartas += Cont;
		    		for(int i=Cont;i>0;i--)
		    		{
		    			gotoxy(69,(*L7)++);
		        		ImprimeCarta(aux2);
		        		aux2 = aux2->prox;
		    		}
	    		}
	    		else
	    			Mensagem();
	        }
	        else
	        if(Destino==8)
    		{	
	    		aux1 = (*m5)->prim;
	        	while(aux1->prox != NULL && Pos>1)		
				{	
					ant1 = aux1;				
	    			aux1 = aux1->prox;
	    			Pos--;
	    		}
	    		DestinoA(*mA, &valida, aux1, &aux2);
	    		while(aux1 != NULL)
	    		{
	    			aux1 = aux1->prox;
	    			Cont++;
	    		}
   				if(valida > 0)
	    		{
		    		(*mA)->qntCartas += Cont;
	    			gotoxy(42,3);
	        		ImprimeCarta(aux2);
	        		gotoxy(43,4);
	        		ImprimeCarta(aux2);
	    		}
	    		else
	    			Mensagem();
	        }
	        else
			if(Destino==9)
    		{	
	    		aux1 = (*m5)->prim;
	        	while(aux1->prox != NULL && Pos>1)		
				{	
					ant1 = aux1;				
	    			aux1 = aux1->prox;
	    			Pos--;
	    		}
	    		DestinoA(*mB, &valida, aux1, &aux2);
	    		while(aux1 != NULL)
	    		{
	    			aux1 = aux1->prox;
	    			Cont++;
	    		}
   				if(valida > 0)
	    		{
		    		(*mB)->qntCartas += Cont;
	    			gotoxy(50,3);
	        		ImprimeCarta(aux2);
	        		gotoxy(51,4);
	        		ImprimeCarta(aux2);
	    		}
	    		else
	    			Mensagem();
	        }
			else
			if(Destino==10)
    		{	
	    		aux1 = (*m5)->prim;
	        	while(aux1->prox != NULL && Pos>1)		
				{	
					ant1 = aux1;				
	    			aux1 = aux1->prox;
	    			Pos--;
	    		}
	    		DestinoA(*mC, &valida, aux1, &aux2);
	    		while(aux1 != NULL)
	    		{
	    			aux1 = aux1->prox;
	    			Cont++;
	    		}
   				if(valida > 0)
	    		{
		    		(*mC)->qntCartas += Cont;
	    			gotoxy(58,3);
	        		ImprimeCarta(aux2);
	        		gotoxy(59,4);
	        		ImprimeCarta(aux2);
	    		}
	    		else
	    			Mensagem();
	        }
	        else
			if(Destino==11)
    		{	
	    		aux1 = (*m5)->prim;
	        	while(aux1->prox != NULL && Pos>1)		
				{	
					ant1 = aux1;				
	    			aux1 = aux1->prox;
	    			Pos--;
	    		}
	    		DestinoA(*mD, &valida, aux1, &aux2);
	    		while(aux1 != NULL)
	    		{
	    			aux1 = aux1->prox;
	    			Cont++;
	    		}
   				if(valida > 0)
	    		{
		    		(*mD)->qntCartas += Cont;
	    			gotoxy(66,3);
	        		ImprimeCarta(aux2);
	        		gotoxy(67,4);
	        		ImprimeCarta(aux2);
	    		}
	    		else
	    			Mensagem();
	        }
	        else
	        	Mensagem();
	        if(valida > 0)
	        {
		    	(*m5)->qntCartas -= Cont;
		    	if((*m5)->qntCartas==0)
			    {
			    	(*m5)->prim = NULL;
			    	while(Cont>0)
			    	{
			    		gotoxy(49,--(*L5));
	        			printf("   ");
	        			Cont--;
			    	}
			    }
		        else
		        {
		        	ant1->prox = NULL;
		        	while(Cont>0)
			    	{
			    		gotoxy(49,--(*L5));
	        			printf("   ");
	        			Cont--;
			    	}
			    	if(ant1->status == 0)
			    	{
			    		ant1->status = 1;
			    		gotoxy(49,(*L5)++);
		                ImprimeCarta(ant1);
			    	}
		        }
	        }
    	}
    	else
	        Mensagem();
	}
	else
    if(Origem == 6)
    {
    	aux1 = (*m6)->prim;
    	while(aux1 != NULL && aux1->status == 0)
    	{
    		aux1 = aux1->prox;
    		Pos++;
    	}
    	if((*m6)->qntCartas > 0 && Pos <= (*m6)->qntCartas && Pos > 0)
	    { 
    		if(Destino==1)
    		{	
	    		aux1 = (*m6)->prim;
	        	while(aux1->prox != NULL && Pos>1)		
				{	
					ant1 = aux1;				
	    			aux1 = aux1->prox;
	    			Pos--;
	    		}
	    		Destino1(*m1, &valida, aux1, &aux2);
	    		while(aux1 != NULL)
	    		{
	    			aux1 = aux1->prox;
	    			Cont++;
	    		}
   				if(valida > 0)
	    		{
		    		(*m1)->qntCartas += Cont;
		    		for(int i=Cont;i>0;i--)
		    		{
		    			gotoxy(9,(*L1)++);
		        		ImprimeCarta(aux2);
		        		aux2 = aux2->prox;
		    		}
	    		}
	    		else
	    			Mensagem();
	        }
	        else
	        if(Destino==2)
    		{	
	    		aux1 = (*m6)->prim;
	        	while(aux1->prox != NULL && Pos>1)		
				{	
					ant1 = aux1;				
	    			aux1 = aux1->prox;
	    			Pos--;
	    		}
	    		Destino1(*m2, &valida, aux1, &aux2);
	    		while(aux1 != NULL)
	    		{
	    			aux1 = aux1->prox;
	    			Cont++;
	    		}
   				if(valida > 0)
	    		{
		    		(*m2)->qntCartas += Cont;
		    		for(int i=Cont;i>0;i--)
		    		{
		    			gotoxy(19,(*L2)++);
		        		ImprimeCarta(aux2);
		        		aux2 = aux2->prox;
		    		}
	    		}
	    		else
	    			Mensagem();
	        }
	    	else
	        if(Destino==3)
    		{	
	    		aux1 = (*m6)->prim;
	        	while(aux1->prox != NULL && Pos>1)		
				{	
					ant1 = aux1;				
	    			aux1 = aux1->prox;
	    			Pos--;
	    		}
	    		Destino1(*m3, &valida, aux1, &aux2);
	    		while(aux1 != NULL)
	    		{
	    			aux1 = aux1->prox;
	    			Cont++;
	    		}
   				if(valida > 0)
	    		{
		    		(*m3)->qntCartas += Cont;
		    		for(int i=Cont;i>0;i--)
		    		{
		    			gotoxy(29,(*L3)++);
		        		ImprimeCarta(aux2);
		        		aux2 = aux2->prox;
		    		}
	    		}
	    		else
	    			Mensagem();
	        }
	        else
	        if(Destino==4)
    		{	
	    		aux1 = (*m6)->prim;
	        	while(aux1->prox != NULL && Pos>1)		
				{	
					ant1 = aux1;				
	    			aux1 = aux1->prox;
	    			Pos--;
	    		}
	    		Destino1(*m4, &valida, aux1, &aux2);
	    		while(aux1 != NULL)
	    		{
	    			aux1 = aux1->prox;
	    			Cont++;
	    		}
   				if(valida > 0)
	    		{
		    		(*m4)->qntCartas += Cont;
		    		for(int i=Cont;i>0;i--)
		    		{
		    			gotoxy(39,(*L4)++);
		        		ImprimeCarta(aux2);
		        		aux2 = aux2->prox;
		    		}
	    		}
	    		else
	    			Mensagem();
	        }
	        else
	        if(Destino==5)
    		{	
	    		aux1 = (*m6)->prim;
	        	while(aux1->prox != NULL && Pos>1)		
				{	
					ant1 = aux1;				
	    			aux1 = aux1->prox;
	    			Pos--;
	    		}
	    		Destino1(*m5, &valida, aux1, &aux2);
	    		while(aux1 != NULL)
	    		{
	    			aux1 = aux1->prox;
	    			Cont++;
	    		}
   				if(valida > 0)
	    		{
		    		(*m5)->qntCartas += Cont;
		    		for(int i=Cont;i>0;i--)
		    		{
		    			gotoxy(49,(*L5)++);
		        		ImprimeCarta(aux2);
		        		aux2 = aux2->prox;
		    		}
	    		}
	    		else
	    			Mensagem();
	        }
	        else
	        if(Destino==7)
    		{	
	    		aux1 = (*m6)->prim;
	        	while(aux1->prox != NULL && Pos>1)		
				{	
					ant1 = aux1;				
	    			aux1 = aux1->prox;
	    			Pos--;
	    		}
	    		Destino1(*m7, &valida, aux1, &aux2);
	    		while(aux1 != NULL)
	    		{
	    			aux1 = aux1->prox;
	    			Cont++;
	    		}
   				if(valida > 0)
	    		{
		    		(*m7)->qntCartas += Cont;
		    		for(int i=Cont;i>0;i--)
		    		{
		    			gotoxy(69,(*L7)++);
		        		ImprimeCarta(aux2);
		        		aux2 = aux2->prox;
		    		}
	    		}
	    		else
	    			Mensagem();
	        }
	        else
	        if(Destino==8)
    		{	
	    		aux1 = (*m6)->prim;
	        	while(aux1->prox != NULL && Pos>1)		
				{	
					ant1 = aux1;				
	    			aux1 = aux1->prox;
	    			Pos--;
	    		}
	    		DestinoA(*mA, &valida, aux1, &aux2);
	    		while(aux1 != NULL)
	    		{
	    			aux1 = aux1->prox;
	    			Cont++;
	    		}
   				if(valida > 0)
	    		{
		    		(*mA)->qntCartas += Cont;
	    			gotoxy(42,3);
	        		ImprimeCarta(aux2);
	        		gotoxy(43,4);
	        		ImprimeCarta(aux2);
	    		}
	    		else
	    			Mensagem();
	        }
	        else
			if(Destino==9)
    		{	
	    		aux1 = (*m6)->prim;
	        	while(aux1->prox != NULL && Pos>1)		
				{	
					ant1 = aux1;				
	    			aux1 = aux1->prox;
	    			Pos--;
	    		}
	    		DestinoA(*mB, &valida, aux1, &aux2);
	    		while(aux1 != NULL)
	    		{
	    			aux1 = aux1->prox;
	    			Cont++;
	    		}
   				if(valida > 0)
	    		{
		    		(*mB)->qntCartas += Cont;
	    			gotoxy(50,3);
	        		ImprimeCarta(aux2);
	        		gotoxy(51,4);
	        		ImprimeCarta(aux2);
	    		}
	    		else
	    			Mensagem();
	        }
			else
			if(Destino==10)
    		{	
	    		aux1 = (*m6)->prim;
	        	while(aux1->prox != NULL && Pos>1)		
				{	
					ant1 = aux1;				
	    			aux1 = aux1->prox;
	    			Pos--;
	    		}
	    		DestinoA(*mC, &valida, aux1, &aux2);
	    		while(aux1 != NULL)
	    		{
	    			aux1 = aux1->prox;
	    			Cont++;
	    		}
   				if(valida > 0)
	    		{
		    		(*mC)->qntCartas += Cont;
	    			gotoxy(58,3);
	        		ImprimeCarta(aux2);
	        		gotoxy(59,4);
	        		ImprimeCarta(aux2);
	    		}
	    		else
	    			Mensagem();
	        }
	        else
			if(Destino==11)
    		{	
	    		aux1 = (*m6)->prim;
	        	while(aux1->prox != NULL && Pos>1)		
				{	
					ant1 = aux1;				
	    			aux1 = aux1->prox;
	    			Pos--;
	    		}
	    		DestinoA(*mD, &valida, aux1, &aux2);
	    		while(aux1 != NULL)
	    		{
	    			aux1 = aux1->prox;
	    			Cont++;
	    		}
   				if(valida > 0)
	    		{
		    		(*mD)->qntCartas += Cont;
	    			gotoxy(66,3);
	        		ImprimeCarta(aux2);
	        		gotoxy(67,4);
	        		ImprimeCarta(aux2);
	    		}
	    		else
	    			Mensagem();
	        }
	        else
	        	Mensagem();
	        if(valida > 0)
	        {
		    	(*m6)->qntCartas -= Cont;
		    	if((*m6)->qntCartas==0)
			    {
			    	(*m6)->prim = NULL;
			    	while(Cont>0)
			    	{
			    		gotoxy(59,--(*L6));
	        			printf("   ");
	        			Cont--;
			    	}
			    }
		        else
		        {
		        	ant1->prox = NULL;
		        	while(Cont>0)
			    	{
			    		gotoxy(59,--(*L6));
	        			printf("   ");
	        			Cont--;
			    	}
			    	if(ant1->status == 0)
			    	{
			    		ant1->status = 1;
			    		gotoxy(59,(*L6)++);
		                ImprimeCarta(ant1);
			    	}
		        }
	        }
    	}
    	else
	        Mensagem();
	}
	else
    if(Origem == 7)
    {
    	aux1 = (*m7)->prim;
    	while(aux1 != NULL && aux1->status == 0)
    	{
    		aux1 = aux1->prox;
    		Pos++;
    	}
    	if((*m7)->qntCartas > 0 && Pos <= (*m7)->qntCartas && Pos > 0)
	    { 
    		if(Destino==1)
    		{	
	    		aux1 = (*m7)->prim;
	        	while(aux1->prox != NULL && Pos>1)		
				{	
					ant1 = aux1;				
	    			aux1 = aux1->prox;
	    			Pos--;
	    		}
	    		Destino1(*m1, &valida, aux1, &aux2);
	    		while(aux1 != NULL)
	    		{
	    			aux1 = aux1->prox;
	    			Cont++;
	    		}
   				if(valida > 0)
	    		{
		    		(*m1)->qntCartas += Cont;
		    		for(int i=Cont;i>0;i--)
		    		{
		    			gotoxy(9,(*L1)++);
		        		ImprimeCarta(aux2);
		        		aux2 = aux2->prox;
		    		}
	    		}
	    		else
	    			Mensagem();
	        }
	        else
	        if(Destino==2)
    		{	
	    		aux1 = (*m7)->prim;
	        	while(aux1->prox != NULL && Pos>1)		
				{	
					ant1 = aux1;				
	    			aux1 = aux1->prox;
	    			Pos--;
	    		}
	    		Destino1(*m2, &valida, aux1, &aux2);
	    		while(aux1 != NULL)
	    		{
	    			aux1 = aux1->prox;
	    			Cont++;
	    		}
   				if(valida > 0)
	    		{
		    		(*m2)->qntCartas += Cont;
		    		for(int i=Cont;i>0;i--)
		    		{
		    			gotoxy(19,(*L2)++);
		        		ImprimeCarta(aux2);
		        		aux2 = aux2->prox;
		    		}
	    		}
	    		else
	    			Mensagem();
	        }
	    	else
	        if(Destino==3)
    		{	
	    		aux1 = (*m7)->prim;
	        	while(aux1->prox != NULL && Pos>1)		
				{	
					ant1 = aux1;				
	    			aux1 = aux1->prox;
	    			Pos--;
	    		}
	    		Destino1(*m3, &valida, aux1, &aux2);
	    		while(aux1 != NULL)
	    		{
	    			aux1 = aux1->prox;
	    			Cont++;
	    		}
   				if(valida > 0)
	    		{
		    		(*m3)->qntCartas += Cont;
		    		for(int i=Cont;i>0;i--)
		    		{
		    			gotoxy(29,(*L3)++);
		        		ImprimeCarta(aux2);
		        		aux2 = aux2->prox;
		    		}
	    		}
	    		else
	    			Mensagem();
	        }
	        else
	        if(Destino==4)
    		{	
	    		aux1 = (*m7)->prim;
	        	while(aux1->prox != NULL && Pos>1)		
				{	
					ant1 = aux1;				
	    			aux1 = aux1->prox;
	    			Pos--;
	    		}
	    		Destino1(*m4, &valida, aux1, &aux2);
	    		while(aux1 != NULL)
	    		{
	    			aux1 = aux1->prox;
	    			Cont++;
	    		}
   				if(valida > 0)
	    		{
		    		(*m4)->qntCartas += Cont;
		    		for(int i=Cont;i>0;i--)
		    		{
		    			gotoxy(39,(*L4)++);
		        		ImprimeCarta(aux2);
		        		aux2 = aux2->prox;
		    		}
	    		}
	    		else
	    			Mensagem();
	        }
	        else
	        if(Destino==5)
    		{	
	    		aux1 = (*m7)->prim;
	        	while(aux1->prox != NULL && Pos>1)		
				{	
					ant1 = aux1;				
	    			aux1 = aux1->prox;
	    			Pos--;
	    		}
	    		Destino1(*m5, &valida, aux1, &aux2);
	    		while(aux1 != NULL)
	    		{
	    			aux1 = aux1->prox;
	    			Cont++;
	    		}
   				if(valida > 0)
	    		{
		    		(*m5)->qntCartas += Cont;
		    		for(int i=Cont;i>0;i--)
		    		{
		    			gotoxy(49,(*L5)++);
		        		ImprimeCarta(aux2);
		        		aux2 = aux2->prox;
		    		}
	    		}
	    		else
	    			Mensagem();
	        }
	        else
	        if(Destino==6)
    		{	
	    		aux1 = (*m7)->prim;
	        	while(aux1->prox != NULL && Pos>1)		
				{	
					ant1 = aux1;				
	    			aux1 = aux1->prox;
	    			Pos--;
	    		}
	    		Destino1(*m6, &valida, aux1, &aux2);
	    		while(aux1 != NULL)
	    		{
	    			aux1 = aux1->prox;
	    			Cont++;
	    		}
   				if(valida > 0)
	    		{
		    		(*m6)->qntCartas += Cont;
		    		for(int i=Cont;i>0;i--)
		    		{
		    			gotoxy(59,(*L6)++);
		        		ImprimeCarta(aux2);
		        		aux2 = aux2->prox;
		    		}
	    		}
	    		else
	    			Mensagem();
	        }
	        else
	        if(Destino==8)
    		{	
	    		aux1 = (*m7)->prim;
	        	while(aux1->prox != NULL && Pos>1)		
				{	
					ant1 = aux1;				
	    			aux1 = aux1->prox;
	    			Pos--;
	    		}
	    		DestinoA(*mA, &valida, aux1, &aux2);
	    		while(aux1 != NULL)
	    		{
	    			aux1 = aux1->prox;
	    			Cont++;
	    		}
   				if(valida > 0)
	    		{
		    		(*mA)->qntCartas += Cont;
	    			gotoxy(42,3);
	        		ImprimeCarta(aux2);
	        		gotoxy(43,4);
	        		ImprimeCarta(aux2);
	    		}
	    		else
	    			Mensagem();
	        }
	        else
			if(Destino==9)
    		{	
	    		aux1 = (*m7)->prim;
	        	while(aux1->prox != NULL && Pos>1)		
				{	
					ant1 = aux1;				
	    			aux1 = aux1->prox;
	    			Pos--;
	    		}
	    		DestinoA(*mB, &valida, aux1, &aux2);
	    		while(aux1 != NULL)
	    		{
	    			aux1 = aux1->prox;
	    			Cont++;
	    		}
   				if(valida > 0)
	    		{
		    		(*mB)->qntCartas += Cont;
	    			gotoxy(50,3);
	        		ImprimeCarta(aux2);
	        		gotoxy(51,4);
	        		ImprimeCarta(aux2);
	    		}
	    		else
	    			Mensagem();
	        }
			else
			if(Destino==10)
    		{	
	    		aux1 = (*m7)->prim;
	        	while(aux1->prox != NULL && Pos>1)		
				{	
					ant1 = aux1;				
	    			aux1 = aux1->prox;
	    			Pos--;
	    		}
	    		DestinoA(*mC, &valida, aux1, &aux2);
	    		while(aux1 != NULL)
	    		{
	    			aux1 = aux1->prox;
	    			Cont++;
	    		}
   				if(valida > 0)
	    		{
		    		(*mC)->qntCartas += Cont;
	    			gotoxy(58,3);
	        		ImprimeCarta(aux2);
	        		gotoxy(59,4);
	        		ImprimeCarta(aux2);
	    		}
	    		else
	    			Mensagem();
	        }
	        else
			if(Destino==11)
    		{	
	    		aux1 = (*m7)->prim;
	        	while(aux1->prox != NULL && Pos>1)		
				{	
					ant1 = aux1;				
	    			aux1 = aux1->prox;
	    			Pos--;
	    		}
	    		DestinoA(*mD, &valida, aux1, &aux2);
	    		while(aux1 != NULL)
	    		{
	    			aux1 = aux1->prox;
	    			Cont++;
	    		}
   				if(valida > 0)
	    		{
		    		(*mD)->qntCartas += Cont;
	    			gotoxy(66,3);
	        		ImprimeCarta(aux2);
	        		gotoxy(67,4);
	        		ImprimeCarta(aux2);
	    		}
	    		else
	    			Mensagem();
	        }
	        else
	        	Mensagem();
	        if(valida > 0)
	        {
		    	(*m7)->qntCartas -= Cont;
		    	if((*m7)->qntCartas==0)
			    {
			    	(*m7)->prim = NULL;
			    	while(Cont>0)
			    	{
			    		gotoxy(69,--(*L7));
	        			printf("   ");
	        			Cont--;
			    	}
			    }
		        else
		        {
		        	ant1->prox = NULL;
		        	while(Cont>0)
			    	{
			    		gotoxy(69,--(*L7));
	        			printf("   ");
	        			Cont--;
			    	}
			    	if(ant1->status == 0)
			    	{
			    		ant1->status = 1;
			    		gotoxy(69,(*L7)++);
		        		ImprimeCarta(ant1);
			    	}
		        }
	        }
    	}
    	else
	        Mensagem();
	}
	else
    if(Origem==8)
    {
    	if((*mA)->qntCartas > 0)
	    {
    		if(Destino==1)
    		{	
	    		aux1 = (*mA)->prim;
	        	while(aux1->prox != NULL)		
				{	
					ant1 = aux1;				
	    			aux1 = aux1->prox;
	    		}
	    		Destino1(*m1, &valida, aux1, &aux2);
   				if(valida > 0)
	    		{
		    		(*m1)->qntCartas++;
		    		gotoxy(9,(*L1)++);
		        	ImprimeCarta(aux2);
	    		}
	    		else
	    			Mensagem();
	        }
	        else
	        if(Destino==2)
    		{	
	    		aux1 = (*mA)->prim;
	        	while(aux1->prox != NULL)		
				{	
					ant1 = aux1;				
	    			aux1 = aux1->prox;
	    		}
	    		Destino1(*m2, &valida, aux1, &aux2);
   				if(valida > 0)
	    		{
		    		(*m2)->qntCartas++;
		    		gotoxy(19,(*L2)++);
		        	ImprimeCarta(aux2);
	    		}
	    		else
	    			Mensagem();
	        }
	        else
	        if(Destino==3)
    		{	
	    		aux1 = (*mA)->prim;
	        	while(aux1->prox != NULL)		
				{	
					ant1 = aux1;				
	    			aux1 = aux1->prox;
	    		}
	    		Destino1(*m3, &valida, aux1, &aux2);
   				if(valida > 0)
	    		{
		    		(*m3)->qntCartas++;
		    		gotoxy(29,(*L3)++);
		        	ImprimeCarta(aux2);
	    		}
	    		else
	    			Mensagem();
	        }
	        else
	        if(Destino==4)
    		{	
	    		aux1 = (*mA)->prim;
	        	while(aux1->prox != NULL)		
				{	
					ant1 = aux1;				
	    			aux1 = aux1->prox;
	    		}
	    		Destino1(*m4, &valida, aux1, &aux2);
   				if(valida > 0)
	    		{
		    		(*m4)->qntCartas++;
		    		gotoxy(39,(*L4)++);
		        	ImprimeCarta(aux2);
	    		}
	    		else
	    			Mensagem();
	        }
	        else
	        if(Destino==5)
    		{	
	    		aux1 = (*mA)->prim;
	        	while(aux1->prox != NULL)		
				{	
					ant1 = aux1;				
	    			aux1 = aux1->prox;
	    		}
	    		Destino1(*m5, &valida, aux1, &aux2);
   				if(valida > 0)
	    		{
		    		(*m5)->qntCartas++;
		    		gotoxy(49,(*L5)++);
		        	ImprimeCarta(aux2);
	    		}
	    		else
	    			Mensagem();
	        }
	        else
	        if(Destino==6)
    		{	
	    		aux1 = (*mA)->prim;
	        	while(aux1->prox != NULL)		
				{	
					ant1 = aux1;				
	    			aux1 = aux1->prox;
	    		}
	    		Destino1(*m6, &valida, aux1, &aux2);
   				if(valida > 0)
	    		{
		    		(*m6)->qntCartas++;
		    		gotoxy(59,(*L6)++);
		        	ImprimeCarta(aux2);
	    		}
	    		else
	    			Mensagem();
	        }
	        else
	        if(Destino==7)
    		{	
	    		aux1 = (*mA)->prim;
	        	while(aux1->prox != NULL)		
				{	
					ant1 = aux1;				
	    			aux1 = aux1->prox;
	    		}
	    		Destino1(*m7, &valida, aux1, &aux2);
   				if(valida > 0)
	    		{
		    		(*m7)->qntCartas++;
		    		gotoxy(69,(*L7)++);
		        	ImprimeCarta(aux2);
	    		}
	    		else
	    			Mensagem();
	        }
	        else
	        if(Destino==9)
    		{	
	    		aux1 = (*mA)->prim;
	        	while(aux1->prox != NULL)		
				{	
					ant1 = aux1;				
	    			aux1 = aux1->prox;
	    		}
	    		DestinoA(*mB, &valida, aux1, &aux2);
   				if(valida > 0)
	    		{
		    		(*mB)->qntCartas++;
		    		gotoxy(50,3);
		        	ImprimeCarta(aux2);
		        	gotoxy(51,4);
		        	ImprimeCarta(aux2);
	    		}
	    		else
	    			Mensagem();
	        }
	        else
	        if(Destino==10)
    		{	
	    		aux1 = (*mA)->prim;
	        	while(aux1->prox != NULL)		
				{	
					ant1 = aux1;				
	    			aux1 = aux1->prox;
	    		}
	    		DestinoA(*mC, &valida, aux1, &aux2);
   				if(valida > 0)
	    		{
		    		(*mC)->qntCartas++;
		    		gotoxy(58,3);
		        	ImprimeCarta(aux2);
		        	gotoxy(59,4);
		        	ImprimeCarta(aux2);
	    		}
	    		else
	    			Mensagem();
	        }
	        else
	        if(Destino==11)
    		{	
	    		aux1 = (*mA)->prim;
	        	while(aux1->prox != NULL)		
				{	
					ant1 = aux1;				
	    			aux1 = aux1->prox;
	    		}
	    		DestinoA(*mD, &valida, aux1, &aux2);
   				if(valida > 0)
	    		{
		    		(*mD)->qntCartas++;
		    		gotoxy(66,3);
		        	ImprimeCarta(aux2);
		        	gotoxy(67,4);
		        	ImprimeCarta(aux2);
	    		}
	    		else
	    			Mensagem();
	        }
	        else
	        	Mensagem();
	        if(valida > 0)
	        {
		    	(*mA)->qntCartas--;
		    	if((*mA)->qntCartas==0)
		    	{
		    		(*mA)->prim = NULL;
		    		gotoxy(42,3);
		        	printf("   ");
		        	gotoxy(43,4);
		        	printf("   ");
		    	}   
		        else
		        {
		        	ant1->prox = NULL;
		        	gotoxy(42,3);
	    			ImprimeCarta(ant1);
	    			gotoxy(43,4);
	    			ImprimeCarta(ant1);
		        }
	        }
    	}
    	else
	        Mensagem();
    }
    else
    if(Origem==9)
    {
    	if((*mB)->qntCartas > 0)
	    {
    		if(Destino==1)
    		{	
	    		aux1 = (*mB)->prim;
	        	while(aux1->prox != NULL)		
				{	
					ant1 = aux1;				
	    			aux1 = aux1->prox;
	    		}
	    		Destino1(*m1, &valida, aux1, &aux2);
   				if(valida > 0)
	    		{
		    		(*m1)->qntCartas++;
		    		gotoxy(9,(*L1)++);
		        	ImprimeCarta(aux2);
	    		}
	    		else
	    			Mensagem();
	        }
	        else
	        if(Destino==2)
    		{	
	    		aux1 = (*mB)->prim;
	        	while(aux1->prox != NULL)		
				{	
					ant1 = aux1;				
	    			aux1 = aux1->prox;
	    		}
	    		Destino1(*m2, &valida, aux1, &aux2);
   				if(valida > 0)
	    		{
		    		(*m2)->qntCartas++;
		    		gotoxy(19,(*L2)++);
		        	ImprimeCarta(aux2);
	    		}
	    		else
	    			Mensagem();
	        }
	        else
	        if(Destino==3)
    		{	
	    		aux1 = (*mB)->prim;
	        	while(aux1->prox != NULL)		
				{	
					ant1 = aux1;				
	    			aux1 = aux1->prox;
	    		}
	    		Destino1(*m3, &valida, aux1, &aux2);
   				if(valida > 0)
	    		{
		    		(*m3)->qntCartas++;
		    		gotoxy(29,(*L3)++);
		        	ImprimeCarta(aux2);
	    		}
	    		else
	    			Mensagem();
	        }
	        else
	        if(Destino==4)
    		{	
	    		aux1 = (*mB)->prim;
	        	while(aux1->prox != NULL)		
				{	
					ant1 = aux1;				
	    			aux1 = aux1->prox;
	    		}
	    		Destino1(*m4, &valida, aux1, &aux2);
   				if(valida > 0)
	    		{
		    		(*m4)->qntCartas++;
		    		gotoxy(39,(*L4)++);
		        	ImprimeCarta(aux2);
	    		}
	    		else
	    			Mensagem();
	        }
	        else
	        if(Destino==5)
    		{	
	    		aux1 = (*mB)->prim;
	        	while(aux1->prox != NULL)		
				{	
					ant1 = aux1;				
	    			aux1 = aux1->prox;
	    		}
	    		Destino1(*m5, &valida, aux1, &aux2);
   				if(valida > 0)
	    		{
		    		(*m5)->qntCartas++;
		    		gotoxy(49,(*L5)++);
		        	ImprimeCarta(aux2);
	    		}
	    		else
	    			Mensagem();
	        }
	        else
	        if(Destino==6)
    		{	
	    		aux1 = (*mB)->prim;
	        	while(aux1->prox != NULL)		
				{	
					ant1 = aux1;				
	    			aux1 = aux1->prox;
	    		}
	    		Destino1(*m6, &valida, aux1, &aux2);
   				if(valida > 0)
	    		{
		    		(*m6)->qntCartas++;
		    		gotoxy(59,(*L6)++);
		        	ImprimeCarta(aux2);
	    		}
	    		else
	    			Mensagem();
	        }
	        else
	        if(Destino==7)
    		{	
	    		aux1 = (*mB)->prim;
	        	while(aux1->prox != NULL)		
				{	
					ant1 = aux1;				
	    			aux1 = aux1->prox;
	    		}
	    		Destino1(*m7, &valida, aux1, &aux2);
   				if(valida > 0)
	    		{
		    		(*m7)->qntCartas++;
		    		gotoxy(69,(*L7)++);
		        	ImprimeCarta(aux2);
	    		}
	    		else
	    			Mensagem();
	        }
	        else
	        if(Destino==8)
    		{	
	    		aux1 = (*mB)->prim;
	        	while(aux1->prox != NULL)		
				{	
					ant1 = aux1;				
	    			aux1 = aux1->prox;
	    		}
	    		DestinoA(*mA, &valida, aux1, &aux2);
   				if(valida > 0)
	    		{
		    		(*mA)->qntCartas++;
		    		gotoxy(42,3);
		        	ImprimeCarta(aux2);
		        	gotoxy(43,4);
		        	ImprimeCarta(aux2);
	    		}
	    		else
	    			Mensagem();
	        }
	        else
	        if(Destino==10)
    		{	
	    		aux1 = (*mB)->prim;
	        	while(aux1->prox != NULL)		
				{	
					ant1 = aux1;				
	    			aux1 = aux1->prox;
	    		}
	    		DestinoA(*mC, &valida, aux1, &aux2);
   				if(valida > 0)
	    		{
		    		(*mC)->qntCartas++;
		    		gotoxy(58,3);
		        	ImprimeCarta(aux2);
		        	gotoxy(59,4);
		        	ImprimeCarta(aux2);
	    		}
	    		else
	    			Mensagem();
	        }
	        else
	        if(Destino==11)
    		{	
	    		aux1 = (*mB)->prim;
	        	while(aux1->prox != NULL)		
				{	
					ant1 = aux1;				
	    			aux1 = aux1->prox;
	    		}
	    		DestinoA(*mD, &valida, aux1, &aux2);
   				if(valida > 0)
	    		{
		    		(*mD)->qntCartas++;
		    		gotoxy(66,3);
		        	ImprimeCarta(aux2);
		        	gotoxy(67,4);
		        	ImprimeCarta(aux2);
	    		}
	    		else
	    			Mensagem();
	        }
	        else
	        	Mensagem();
	        if(valida > 0)
	        {
		    	(*mB)->qntCartas--;
		    	if((*mB)->qntCartas==0)
		    	{
		    		(*mB)->prim = NULL;
		    		gotoxy(50,3);
		        	printf("   ");
		        	gotoxy(51,4);
		        	printf("   ");
		    	}   
		        else
		        {
		        	ant1->prox = NULL;
		        	gotoxy(50,3);
	    			ImprimeCarta(ant1);
	    			gotoxy(51,4);
	    			ImprimeCarta(ant1);
		        }
	        }
    	}
    	else
	        Mensagem();
    }
    else
    if(Origem==10)
    {
    	if((*mC)->qntCartas > 0)
	    {
    		if(Destino==1)
    		{	
	    		aux1 = (*mC)->prim;
	        	while(aux1->prox != NULL)		
				{	
					ant1 = aux1;				
	    			aux1 = aux1->prox;
	    		}
	    		Destino1(*m1, &valida, aux1, &aux2);
   				if(valida > 0)
	    		{
		    		(*m1)->qntCartas++;
		    		gotoxy(9,(*L1)++);
		        	ImprimeCarta(aux2);
	    		}
	    		else
	    			Mensagem();
	        }
	        else
	        if(Destino==2)
    		{	
	    		aux1 = (*mC)->prim;
	        	while(aux1->prox != NULL)		
				{	
					ant1 = aux1;				
	    			aux1 = aux1->prox;
	    		}
	    		Destino1(*m2, &valida, aux1, &aux2);
   				if(valida > 0)
	    		{
		    		(*m2)->qntCartas++;
		    		gotoxy(19,(*L2)++);
		        	ImprimeCarta(aux2);
	    		}
	    		else
	    			Mensagem();
	        }
	        else
	        if(Destino==3)
    		{	
	    		aux1 = (*mC)->prim;
	        	while(aux1->prox != NULL)		
				{	
					ant1 = aux1;				
	    			aux1 = aux1->prox;
	    		}
	    		Destino1(*m3, &valida, aux1, &aux2);
   				if(valida > 0)
	    		{
		    		(*m3)->qntCartas++;
		    		gotoxy(29,(*L3)++);
		        	ImprimeCarta(aux2);
	    		}
	    		else
	    			Mensagem();
	        }
	        else
	        if(Destino==4)
    		{	
	    		aux1 = (*mC)->prim;
	        	while(aux1->prox != NULL)		
				{	
					ant1 = aux1;				
	    			aux1 = aux1->prox;
	    		}
	    		Destino1(*m4, &valida, aux1, &aux2);
   				if(valida > 0)
	    		{
		    		(*m4)->qntCartas++;
		    		gotoxy(39,(*L4)++);
		        	ImprimeCarta(aux2);
	    		}
	    		else
	    			Mensagem();
	        }
	        else
	        if(Destino==5)
    		{	
	    		aux1 = (*mC)->prim;
	        	while(aux1->prox != NULL)		
				{	
					ant1 = aux1;				
	    			aux1 = aux1->prox;
	    		}
	    		Destino1(*m5, &valida, aux1, &aux2);
   				if(valida > 0)
	    		{
		    		(*m5)->qntCartas++;
		    		gotoxy(49,(*L5)++);
		        	ImprimeCarta(aux2);
	    		}
	    		else
	    			Mensagem();
	        }
	        else
	        if(Destino==6)
    		{	
	    		aux1 = (*mC)->prim;
	        	while(aux1->prox != NULL)		
				{	
					ant1 = aux1;				
	    			aux1 = aux1->prox;
	    		}
	    		Destino1(*m6, &valida, aux1, &aux2);
   				if(valida > 0)
	    		{
		    		(*m6)->qntCartas++;
		    		gotoxy(59,(*L6)++);
		        	ImprimeCarta(aux2);
	    		}
	    		else
	    			Mensagem();
	        }
	        else
	        if(Destino==7)
    		{	
	    		aux1 = (*mC)->prim;
	        	while(aux1->prox != NULL)		
				{	
					ant1 = aux1;				
	    			aux1 = aux1->prox;
	    		}
	    		Destino1(*m7, &valida, aux1, &aux2);
   				if(valida > 0)
	    		{
		    		(*m7)->qntCartas++;
		    		gotoxy(69,(*L7)++);
		        	ImprimeCarta(aux2);
	    		}
	    		else
	    			Mensagem();
	        }
	        else
	        if(Destino==8)
    		{	
	    		aux1 = (*mC)->prim;
	        	while(aux1->prox != NULL)		
				{	
					ant1 = aux1;				
	    			aux1 = aux1->prox;
	    		}
	    		DestinoA(*mA, &valida, aux1, &aux2);
   				if(valida > 0)
	    		{
		    		(*mA)->qntCartas++;
		    		gotoxy(42,3);
		        	ImprimeCarta(aux2);
		        	gotoxy(43,4);
		        	ImprimeCarta(aux2);
	    		}
	    		else
	    			Mensagem();
	        }
	        else
	        if(Destino==9)
    		{	
	    		aux1 = (*mC)->prim;
	        	while(aux1->prox != NULL)		
				{	
					ant1 = aux1;				
	    			aux1 = aux1->prox;
	    		}
	    		DestinoA(*mB, &valida, aux1, &aux2);
   				if(valida > 0)
	    		{
		    		(*mB)->qntCartas++;
		    		gotoxy(50,3);
		        	ImprimeCarta(aux2);
		        	gotoxy(51,4);
		        	ImprimeCarta(aux2);
	    		}
	    		else
	    			Mensagem();
	        }
	        else
	        if(Destino==11)
    		{	
	    		aux1 = (*mC)->prim;
	        	while(aux1->prox != NULL)		
				{	
					ant1 = aux1;				
	    			aux1 = aux1->prox;
	    		}
	    		DestinoA(*mD, &valida, aux1, &aux2);
   				if(valida > 0)
	    		{
		    		(*mD)->qntCartas++;
		    		gotoxy(66,3);
		        	ImprimeCarta(aux2);
		        	gotoxy(67,4);
		        	ImprimeCarta(aux2);
	    		}
	    		else
	    			Mensagem();
	        }
	        else
	        	Mensagem();
	        if(valida > 0)
	        {
		    	(*mC)->qntCartas--;
		    	if((*mC)->qntCartas==0)
		    	{
		    		(*mC)->prim = NULL;
		    		gotoxy(58,3);
		        	printf("   ");
		        	gotoxy(59,4);
		        	printf("   ");
		    	}   
		        else
		        {
		        	ant1->prox = NULL;
		        	gotoxy(58,3);
	    			ImprimeCarta(ant1);
	    			gotoxy(59,4);
	    			ImprimeCarta(ant1);
		        }
	        }
    	}
    	else
	        Mensagem();
    }
    else
    if(Origem==11)
    {
    	if((*mD)->qntCartas > 0)
	    {
    		if(Destino==1)
    		{	
	    		aux1 = (*mD)->prim;
	        	while(aux1->prox != NULL)		
				{	
					ant1 = aux1;				
	    			aux1 = aux1->prox;
	    		}
	    		Destino1(*m1, &valida, aux1, &aux2);
   				if(valida > 0)
	    		{
		    		(*m1)->qntCartas++;
		    		gotoxy(9,(*L1)++);
		        	ImprimeCarta(aux2);
	    		}
	    		else
	    			Mensagem();
	        }
	        else
	        if(Destino==2)
    		{	
	    		aux1 = (*mD)->prim;
	        	while(aux1->prox != NULL)		
				{	
					ant1 = aux1;				
	    			aux1 = aux1->prox;
	    		}
	    		Destino1(*m2, &valida, aux1, &aux2);
   				if(valida > 0)
	    		{
		    		(*m2)->qntCartas++;
		    		gotoxy(19,(*L2)++);
		        	ImprimeCarta(aux2);
	    		}
	    		else
	    			Mensagem();
	        }
	        else
	        if(Destino==3)
    		{	
	    		aux1 = (*mD)->prim;
	        	while(aux1->prox != NULL)		
				{	
					ant1 = aux1;				
	    			aux1 = aux1->prox;
	    		}
	    		Destino1(*m3, &valida, aux1, &aux2);
   				if(valida > 0)
	    		{
		    		(*m3)->qntCartas++;
		    		gotoxy(29,(*L3)++);
		        	ImprimeCarta(aux2);
	    		}
	    		else
	    			Mensagem();
	        }
	        else
	        if(Destino==4)
    		{	
	    		aux1 = (*mD)->prim;
	        	while(aux1->prox != NULL)		
				{	
					ant1 = aux1;				
	    			aux1 = aux1->prox;
	    		}
	    		Destino1(*m4, &valida, aux1, &aux2);
   				if(valida > 0)
	    		{
		    		(*m4)->qntCartas++;
		    		gotoxy(39,(*L4)++);
		        	ImprimeCarta(aux2);
	    		}
	    		else
	    			Mensagem();
	        }
	        else
	        if(Destino==5)
    		{	
	    		aux1 = (*mD)->prim;
	        	while(aux1->prox != NULL)		
				{	
					ant1 = aux1;				
	    			aux1 = aux1->prox;
	    		}
	    		Destino1(*m5, &valida, aux1, &aux2);
   				if(valida > 0)
	    		{
		    		(*m5)->qntCartas++;
		    		gotoxy(49,(*L5)++);
		        	ImprimeCarta(aux2);
	    		}
	    		else
	    			Mensagem();
	        }
	        else
	        if(Destino==6)
    		{	
	    		aux1 = (*mD)->prim;
	        	while(aux1->prox != NULL)		
				{	
					ant1 = aux1;				
	    			aux1 = aux1->prox;
	    		}
	    		Destino1(*m6, &valida, aux1, &aux2);
   				if(valida > 0)
	    		{
		    		(*m6)->qntCartas++;
		    		gotoxy(59,(*L6)++);
		        	ImprimeCarta(aux2);
	    		}
	    		else
	    			Mensagem();
	        }
	        else
	        if(Destino==7)
    		{	
	    		aux1 = (*mD)->prim;
	        	while(aux1->prox != NULL)		
				{	
					ant1 = aux1;				
	    			aux1 = aux1->prox;
	    		}
	    		Destino1(*m7, &valida, aux1, &aux2);
   				if(valida > 0)
	    		{
		    		(*m7)->qntCartas++;
		    		gotoxy(69,(*L7)++);
		        	ImprimeCarta(aux2);
	    		}
	    		else
	    			Mensagem();
	        }
	        else
	        if(Destino==8)
    		{	
	    		aux1 = (*mD)->prim;
	        	while(aux1->prox != NULL)		
				{	
					ant1 = aux1;				
	    			aux1 = aux1->prox;
	    		}
	    		DestinoA(*mA, &valida, aux1, &aux2);
   				if(valida > 0)
	    		{
		    		(*mA)->qntCartas++;
		    		gotoxy(42,3);
		        	ImprimeCarta(aux2);
		        	gotoxy(43,4);
		        	ImprimeCarta(aux2);
	    		}
	    		else
	    			Mensagem();
	        }
	        else
	        if(Destino==9)
    		{	
	    		aux1 = (*mD)->prim;
	        	while(aux1->prox != NULL)		
				{	
					ant1 = aux1;				
	    			aux1 = aux1->prox;
	    		}
	    		DestinoA(*mB, &valida, aux1, &aux2);
   				if(valida > 0)
	    		{
		    		(*mB)->qntCartas++;
		    		gotoxy(50,3);
		        	ImprimeCarta(aux2);
		        	gotoxy(51,4);
		        	ImprimeCarta(aux2);
	    		}
	    		else
	    			Mensagem();
	        }
	        else
	        if(Destino==10)
    		{	
	    		aux1 = (*mD)->prim;
	        	while(aux1->prox != NULL)		
				{	
					ant1 = aux1;				
	    			aux1 = aux1->prox;
	    		}
	    		DestinoA(*mC, &valida, aux1, &aux2);
   				if(valida > 0)
	    		{
		    		(*mC)->qntCartas++;
		    		gotoxy(58,3);
		        	ImprimeCarta(aux2);
		        	gotoxy(59,4);
		        	ImprimeCarta(aux2);
	    		}
	    		else
	    			Mensagem();
	        }
	        else
	        	Mensagem();
	        if(valida > 0)
	        {
		    	(*mD)->qntCartas--;
		    	if((*mD)->qntCartas==0)
		    	{
		    		(*mD)->prim = NULL;
		    		gotoxy(66,3);
		        	printf("   ");
		        	gotoxy(67,4);
		        	printf("   ");
		    	}   
		        else
		        {
		        	ant1->prox = NULL;
		        	gotoxy(66,3);
	    			ImprimeCarta(ant1);
	    			gotoxy(67,4);
	    			ImprimeCarta(ant1);
		        }
	        }
    	}
    	else
	        Mensagem();
	}
}

int main()
{	
	TelaAbertura();
    Tpcarta carta[52];
	jogo *jogo;
	monte *mvirado, *mdesvirado, *mA, *mB, *mC, *mD, *m1, *m2, *m3, *m4, *m5, *m6, *m7;
	int L1=9,L2=9,L3=9,L4=9,L5=9,L6=9,L7=9, Origem, Destino, Pos, Ganhou=0, opcao;
	char op[2];
	CriaBaralho(carta);
	EmbaralhaBaralho(carta, &jogo);
	ApontaMonte(jogo, &mvirado, &mdesvirado, &mA, &mB, &mC, &mD, &m1, &m2, &m3, &m4, &m5, &m6, &m7);
	InicializaJogo(mvirado, mdesvirado, m1, m2, m3, m4, m5, m6, m7);
	textcolor(0); gotoxy(9,21); printf("(1)%d",m1->qntCartas); gotoxy(19,21); printf("(2)%d",m2->qntCartas); 
    gotoxy(29,21);printf("(3)%d",m3->qntCartas); gotoxy(39,21); printf("(4)%d",m4->qntCartas);
    gotoxy(49,21); printf("(5)%d",m5->qntCartas); gotoxy(59,21); printf("(6)%d",m6->qntCartas);
    gotoxy(69,21); printf("(7)%d",m7->qntCartas); gotoxy(42,6); printf("(8)");	gotoxy(50,6); 
    printf("(9)"); gotoxy(57,6); printf("(10)"); gotoxy(66,6); printf("(11)"); gotoxy(5,6); printf("(+)");
    textcolor(4);gotoxy(42,24); printf("TECLA DA JOGADA -> (N)N <- QNTD CARTAS"); textcolor(0);
	gotoxy(13,6); printf("(*)");
    do
    {   
        textcolor(0);
        gotoxy(12,23);
        fflush(stdin);
        printf("Digite a Opcao: ");
        scanf("%s", &op);
        opcao = atoi(op);
        if(opcao < 1 || opcao > 11)
        {
        	if(strcmp(op,"+")==0)
        		opcao = 12;
        	else
        	if(strcmp(op,"*")==0)
        		opcao = 13;
        	else
        	if(strcmp(op,"0")!=0)
        		opcao = 14;
        }
        gotoxy(12,23);
        printf("                                                                 ");        
        switch(opcao)
        {
            case 12 : // +
                     Origem=0;
                     Destino=15;
                     gotoxy(12,23);
                     printf("                                                                 "); 
                     Movimentacao(&mvirado, &mdesvirado, &mA, &mB, &mC, &mD, &m1, &m2, &m3, &m4, &m5, &m6, &m7, Origem, Destino, &L1, &L2, &L3, &L4, &L5, &L6, &L7, Pos);
					        
            break;
            
            case 13 : // * 
                     Origem=15;
                     textcolor(0);
                     gotoxy(12,23);
                     printf("Digite o Destino: ");
                     scanf("%d", &Destino);
                     gotoxy(12,23);
                     printf("                                                                 "); 
                     Movimentacao(&mvirado, &mdesvirado, &mA, &mB, &mC, &mD, &m1, &m2, &m3, &m4, &m5, &m6, &m7, Origem, Destino, &L1, &L2, &L3, &L4, &L5, &L6, &L7, Pos);
            break;
            
            case 1 : // 1
                     Origem=1;
                     textcolor(0);
                     gotoxy(12,23);
                     printf("Digite o Destino: ");
                     scanf("%d", &Destino);
                     gotoxy(12,23);
                     printf("                                                                 "); 
                     gotoxy(12,23);
                     printf("Qual posicao de origem: ");
                     scanf("%d", &Pos);
                     gotoxy(12,23);
                     printf("                                                                 "); 
                     Movimentacao(&mvirado, &mdesvirado, &mA, &mB, &mC, &mD, &m1, &m2, &m3, &m4, &m5, &m6, &m7, Origem, Destino, &L1, &L2, &L3, &L4, &L5, &L6, &L7, Pos);
            break; 
            
            case 2 : // 2
                     Origem=2;
                	 textcolor(0);
                     gotoxy(12,23);
                     printf("Digite o Destino: ");
                     scanf("%d", &Destino);
                     gotoxy(12,23);
                     printf("                                                                 "); 
                     gotoxy(12,23);
                     printf("Qual posicao de origem: ");
                     scanf("%d", &Pos);
                     gotoxy(12,23);
                     printf("                                                                 "); 
                     Movimentacao(&mvirado, &mdesvirado, &mA, &mB, &mC, &mD, &m1, &m2, &m3, &m4, &m5, &m6, &m7, Origem, Destino, &L1, &L2, &L3, &L4, &L5, &L6, &L7, Pos);
            break;
            
            case 3 : // 3
                     Origem=3;
                     textcolor(0);
                     gotoxy(12,23);
                     printf("Digite o Destino: ");
                     scanf("%d", &Destino);
                     gotoxy(12,23);
                     printf("                                                                 "); 
                     gotoxy(12,23);
                     printf("Qual posicao de origem: ");
                     scanf("%d", &Pos);
                     gotoxy(12,23);
                     printf("                                                                 "); 
                     Movimentacao(&mvirado, &mdesvirado, &mA, &mB, &mC, &mD, &m1, &m2, &m3, &m4, &m5, &m6, &m7, Origem, Destino, &L1, &L2, &L3, &L4, &L5, &L6, &L7, Pos);
            break;

            case 4 : // 4
                     Origem=4;
                     textcolor(0);
                     gotoxy(12,23);
                     printf("Digite o Destino: ");
                     scanf("%d", &Destino);
                     gotoxy(12,23);
                     printf("                                                                 "); 
                     gotoxy(12,23);
                     printf("Qual posicao de origem: ");
                     scanf("%d", &Pos);
                     gotoxy(12,23);
                     printf("                                                                 "); 
                     Movimentacao(&mvirado, &mdesvirado, &mA, &mB, &mC, &mD, &m1, &m2, &m3, &m4, &m5, &m6, &m7, Origem, Destino, &L1, &L2, &L3, &L4, &L5, &L6, &L7, Pos);
            break;
            
            case 5 : // 5
                     Origem=5;
                     textcolor(0);
                     gotoxy(12,23);
                     printf("Digite o Destino: ");
                     scanf("%d", &Destino);
                     gotoxy(12,23);
                     printf("                                                                 "); 
                     gotoxy(12,23);
                     printf("Qual posicao de origem: ");
                     scanf("%d", &Pos);
                     gotoxy(12,23);
                     printf("                                                                 "); 
                     Movimentacao(&mvirado, &mdesvirado, &mA, &mB, &mC, &mD, &m1, &m2, &m3, &m4, &m5, &m6, &m7, Origem, Destino, &L1, &L2, &L3, &L4, &L5, &L6, &L7, Pos);
            break;
            
            case 6 : // 6
                     Origem=6;
                     textcolor(0);
                     gotoxy(12,23);
                     printf("Digite o Destino: ");
                     scanf("%d", &Destino);
                     gotoxy(12,23);
                     printf("                                                                 "); 
                     gotoxy(12,23);
                     printf("Qual posicao de origem: ");
                     scanf("%d", &Pos);
                     gotoxy(12,23);
                     printf("                                                                 "); 
                     Movimentacao(&mvirado, &mdesvirado, &mA, &mB, &mC, &mD, &m1, &m2, &m3, &m4, &m5, &m6, &m7, Origem, Destino, &L1, &L2, &L3, &L4, &L5, &L6, &L7, Pos);
            break;
            
            case 7 : // 7
                     Origem=7;
                     textcolor(0);
                     gotoxy(12,23);
                     printf("Digite o Destino: ");
                     scanf("%d", &Destino);
                     gotoxy(12,23);
                     printf("                                                                 "); 
                     gotoxy(12,23);
                     printf("Qual posicao de origem: ");
                     scanf("%d", &Pos);
                     gotoxy(12,23);
                     printf("                                                                 "); 
                     Movimentacao(&mvirado, &mdesvirado, &mA, &mB, &mC, &mD, &m1, &m2, &m3, &m4, &m5, &m6, &m7, Origem, Destino, &L1, &L2, &L3, &L4, &L5, &L6, &L7, Pos);
            break;
            
            case 8 : // 8
                     Origem=8;
                     textcolor(0);
                     gotoxy(12,23);
                     printf("Digite o Destino: ");
                     scanf("%d", &Destino);
                     gotoxy(12,23);
                     printf("                                                                 "); 
                     Movimentacao(&mvirado, &mdesvirado, &mA, &mB, &mC, &mD, &m1, &m2, &m3, &m4, &m5, &m6, &m7, Origem, Destino, &L1, &L2, &L3, &L4, &L5, &L6, &L7, Pos);
            break;
            
            case 9 : // 9
                     Origem=9;
                     textcolor(0);
                     gotoxy(12,23);
                     printf("Digite o Destino: ");
                     scanf("%d", &Destino);
                     gotoxy(12,23);
                     printf("                                                                 "); 
                     Movimentacao(&mvirado, &mdesvirado, &mA, &mB, &mC, &mD, &m1, &m2, &m3, &m4, &m5, &m6, &m7, Origem, Destino, &L1, &L2, &L3, &L4, &L5, &L6, &L7, Pos);
            break;
            
            case 10 : // 10
                     Origem=10;
                     textcolor(0);
                     gotoxy(12,23);
                     printf("Digite o Destino: ");
                     scanf("%d", &Destino);
                     gotoxy(12,23);
                     printf("                                                                 "); 
                     Movimentacao(&mvirado, &mdesvirado, &mA, &mB, &mC, &mD, &m1, &m2, &m3, &m4, &m5, &m6, &m7, Origem, Destino, &L1, &L2, &L3, &L4, &L5, &L6, &L7, Pos);
            break;
            
            case 11 : // 11
                     Origem=11;
                     textcolor(0);
                     gotoxy(12,23);
                     printf("Digite o Destino: ");
                     scanf("%d", &Destino);
                     gotoxy(12,23);
                     printf("                                                                 "); 
                     Movimentacao(&mvirado, &mdesvirado, &mA, &mB, &mC, &mD, &m1, &m2, &m3, &m4, &m5, &m6, &m7, Origem, Destino, &L1, &L2, &L3, &L4, &L5, &L6, &L7, Pos);
            break;    
    	}
		textcolor(0); gotoxy(9,21); printf("     "); gotoxy(19,21); printf("     ");
        gotoxy(29,21);printf("     "); gotoxy(39,21); printf("     ");
        gotoxy(49,21); printf("     "); gotoxy(59,21); printf("     ");
        gotoxy(69,21); printf("     ");
		     	
    	textcolor(0); gotoxy(9,21); printf("(1)%d",m1->qntCartas); gotoxy(19,21); printf("(2)%d",m2->qntCartas);
        gotoxy(29,21);printf("(3)%d",m3->qntCartas); gotoxy(39,21); printf("(4)%d",m4->qntCartas);
        gotoxy(49,21); printf("(5)%d",m5->qntCartas); gotoxy(59,21); printf("(6)%d",m6->qntCartas);
        gotoxy(69,21); printf("(7)%d",m7->qntCartas); 
        if(mA->qntCartas == 13 && mB->qntCartas == 13 && mC->qntCartas == 13 && mD->qntCartas == 13)
    	{
    		Ganhou++;
    		VoceGanhou();
    	}	
    }while(opcao !=0 && Ganhou == 0);
}
