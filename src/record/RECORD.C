/* 
 * CjO-ōn-Ę[-Å_[-Û]]
 *
 * CjOF
 *        [1,2,3,4,...]
 * ōnF
 *        [1-9], G:S, F:tC, L:Ci[, O:I[o[, B(l), D()
 *        B:l, D:, K:OU, 
 *        R:ã
 * ĘF
 *        O:AEg, 1H:VOqbg, 2H:ņÛÅ
 *        3H:OÛÅ, HR:{ÛÅ, G:]Å, E:G[
 * Å_F
 *        [1,2,3,4]
 * ÛF
 *        [1,2,3]
 *
 * oÍá
 *
 * žO   Å ÅČ ĀÅ QÛÅRÛÅ {ÛÅ l Å_  Û ÅĶ
 * ------------------------------------------------------------------------
 * ―Š    4      20     18    5      2     0      1      2    8     2  .278
 */
/*	Example input:
 *	93/10/10 vs Jokers
 *	1kura   1-7F-O  2-3G-O-1        4-4F-O
 *	2sino   1-5G-1H 2-K-O   5-K-O
 *	3dai    1-K-O   3-K-O
 *	>ike-p  5-9G-1H-1
 *	4hiro   2-9O-3H 3-5G-O
 *	>mine   5-3L-O
 *	5sueyosi        2-K-O   3-5G-E
 *	6y-osa  2-8O-2H-1       3-8O-2H-1
 *	7ehara  2-2F-E  3-K-O
 *	8ogata  2-9G-1H-1       5-8F-O
 *	9sophia 2-7G-1H-1       4-K-O
 */
/*
	kura, sino, dai, ike-p, hiro, mine, sueyoshi, y-osa,
	ehara, ogata, sophia, ekimira, ito, suzu
 */
#include <stdio.h>
#include <ctype.h>

struct record {
	char nickname[16];
	char fullname[32];
	unsigned char number;
	int game; /* QÁ */
	int hit_num; /* Å */
	int try_num;  /* ÅČ */
	int k;	/* OU */
	int h1;
	int h2;
	int h3;
	int h4; /* {ÛÅ */
	int bb; /* l */
	int er;
	int steal;
	int get; /* Å_ */
	int run; /* ū_ */
	float ave; /* "ÅĶ */
	struct record *next;
	struct record *prev;
} rec[] = {
#define sinozaki 0
{"sino","Âč čķ",3},
#define haya 1
{"haya","Ņ@ O@",5},
#define yamashita 2
{"y-osa","Rš Cj",6},
#define ehara 3
{"ehara","]ī P@",7},
#define ekimura 4
{"ekimura","Øš pņ",8},
#define tshimizu 5
{"tshimizu","ī V",9},
#define sueyoshi 6
{"sueyoshi","g ēF",10},
#define sophia 7
{"sophia","Âī šm",11},
#define kurachi 8
{"kurachi","qm Gū",20},
#define dai 9
{"dai","―Š åã",21},
#define mine 10
{"mine","õR O@",23},
#define tamotsu 11
{"tamotsu","rc Û@",24},
#define ogata 12
{"ogata","Žû īj",27},
#define hiro 13
{"hiro","Ņ@ Os ",30},
#define hazedon 14
{"hazedon","Íš Äj",1},
#define suzu 15
{"suzu","éØ Nę",16},
#define tanaka 16
{"tanaka","c Gũ",4},
#define juzu 17
{"juzu","ė",0},
#define takemoto 18
{"takemoto","|{ ―",0},
#define nakajima 19
{"nakajima"," kę",18},
#define siozawa 20
{"siozawa","āV",0},
#define ohta 21
{"ohta","ūc Ũ",2},
#define mizutani 22
{"mizutani","J F",0},
#define ohnishi 23
{"ohnishi","åž Ã",0},
#define takasu 24
{"takasu","{ [",0},
#define tsuchie 25
{"tsuchie","y]",0},
#define sugioka 26
{"sugioka","Š",0},
#define machiyama 27
{"sugioka","ŌR aÎ",18},
#define fujinaga 28
{"fujinaga","Ąi",0},
#define kojiro 29
{"kojiro","õY",0},
#define sakurai 30
{"sakurai","ũä Ö",0},
#define itoh 31
{"itoh","ÉĄ",0},
#define kawahara 32
{"kawahara","ėī",0},
#define okiyama 33
{"okiyama","ŦR",0},

#define total 34 
{"total"," v ",0},
};
#define TOTALMEM 34 
	
struct record *top,*undertop;
int totalgames =0;

usage(av)
char *av;
{
        printf("%s [-sHl] DATAFILE\n",av);
}

main(ac,av)
char *av[];
{
	char buf[1024];
	FILE *fp;
	int i,j,k;
	struct record *p;
	int line=0;
	int sflag = 0;
	int lflag = 0;
	int hflag = 0;

	for(; ac > 1 && av[1][0] == '-'; ac--,av++){
		switch(av[1][1]){
		case 'h':
			usage(av[0]);
			exit(1);
		case 's':
			sflag = 1; /* short format */
			break;
		case 'l':
			lflag = 1; /* short format */
			break;
		case 'H':
			hflag = 1; /* html format */
			break;
		default:
			break;
		}
	}

	if(ac==1){
	    if( (fp = fopen("DATA","r")) == NULL ){
		printf("Can't open DATA file\n");
		exit(1);
	    }
	    while(fgets(buf,sizeof(buf),fp)){
		++line;
		if(buf[0] == '#' || (isspace(buf[0])))
		    continue;
		if(buf[0] == '['){
		    totalgames++;
		    continue;
		}
		 getentry(buf,line);
	    }
	}else while(--ac>0){
	    if( (fp = fopen(av[ac],"r")) == NULL ){
		printf("Can't open %s file\n",av[1]);
		exit(1);
	    }
	    while(fgets(buf,sizeof(buf),fp)){
		++line;
		if(buf[0] == '#' || (isspace(buf[0])))
		    continue;
		if(buf[0] == '['){
		    totalgames++;
		    continue;
		}
		 getentry(buf,line);
	    }
	}


	for(i=0;i<TOTALMEM;i++){
	    if( rec[i].hit_num == 0) 
		rec[i].ave = 0;
	    else
		rec[i].ave = ((float)rec[i].h1+rec[i].h2+rec[i].h3+rec[i].h4)
				/rec[i].hit_num;

	    if((float)(rec[i].game) < ((float)totalgames/2) ){
		    if(!undertop){
			undertop = &rec[i];
			undertop->next = 0;
			undertop->prev = 0;
			continue;
		    }
		    for(p=undertop;;p = p->next){
			if(p->ave < rec[i].ave){
			    rec[i].next = p;
			    if(p==undertop){
				undertop->prev = &rec[i];
				undertop = &rec[i];
				rec[i].prev = 0;
			    }else{
				p->prev->next = &rec[i];
				rec[i].prev = p->prev;
                                p->prev = &rec[i];
			    }
			    break;
			}
			if(!(p->next)){
			    p->next = &rec[i];
			    rec[i].next = 0;
			    rec[i].prev = p;
			    break;
			}
		    }
	    }else{
		    if(!top){
			top = &rec[i];
			top->next = 0;
			top->prev = 0;
			continue;
		    }
		    for(p=top;;p = p->next){
			if(p->ave < rec[i].ave){
			    rec[i].next = p;
			    if(p==top){
				top->prev = &rec[i];
				top = &rec[i];
				rec[i].prev = 0;
			    }else{
				p->prev->next = &rec[i];
				rec[i].prev = p->prev;
				p->prev = &rec[i];
			    }
			    break;
			}
			if(!(p->next)){
			    p->next = &rec[i];
			    rec[i].prev = p;
			    rec[i].next = 0;
			    rec[i].prev = p;
			    break;
			}
		    }
	    }
		
	}
	for(i=0;i<TOTALMEM;i++){
	    rec[total].try_num += rec[i].try_num;
	    rec[total].hit_num += rec[i].hit_num;
	    rec[total].k += rec[i].k;
	    rec[total].h1 += rec[i].h1;
	    rec[total].h2 += rec[i].h2;
	    rec[total].h3 += rec[i].h3;
	    rec[total].h4 += rec[i].h4;
	    rec[total].bb += rec[i].bb;
	    rec[total].er += rec[i].er;
	    rec[total].steal += rec[i].steal;
	    rec[total].run += rec[i].run;
	    rec[total].get += rec[i].get;
	}
	if( rec[total].hit_num == 0) 
		rec[total].ave = 0;
	else
		rec[total].ave = ((float)rec[total].h1+rec[total].h2+rec[total].h3+rec[total].h4)
				/rec[total].hit_num;
	rec[total].game = totalgames;


	if(sflag)
		print1(); /* short format */
	else if(lflag)
		print3(); /* very long format */
	else if(hflag)
	        print5(); /* html format */
	else
		print2(); /* long format / default */
}

print1()
{
    int i,hits;
    float eave;
    struct record *p;
    char t1[10],t2[10];

    printf("\t\t<<< MonStars ÅŽŅ >>> \n");
    printf("%-10s%5s%5s%5s%5s%7s%7s%5s%5s%5s%7s%5s\n",
	   "žO","","Å","ÅČ","ĀÅ","ÛÅ",
	   "l","Å_","ū_","Û","oÛĶ","ÅĶ");
    for(p=top;p;p=p->next){

	hits = 	 p->h1+p->h2+p->h3+p->h4;
	if(p->try_num)
	  eave = ((float)hits + p->er+p->bb)/p->try_num;
	else
	  eave = 0;

	sprintf(t1,"%6.3f",p->ave);
	for(i=0;i<sizeof(t1) && t1[i] != '.';i++)
		t1[i] = ' ';

	sprintf(t2,"%6.3f",eave);
	for(i=0;i<sizeof(t2) && t2[i] != '.';i++)
		t2[i] = ' ';

	printf("%-10s%5d%5d%5d%5d%7d%7d%5d%5d%5d%s%s\n",
		 p->fullname,
		 p->game,
		 p->hit_num,
		 p->try_num,
	         hits,
		 p->h1+p->h2*2+p->h3*3+p->h4*4,
		 p->bb,
		 p->get,
		 p->run,
	         p->steal,
	         t2,
		 t1);
    }

    if(undertop) printf("\t---------- KčĒ ----------\n");
    for(p=undertop;p;p=p->next){
	hits = 	 p->h1+p->h2+p->h3+p->h4;
	if(p->try_num)
	  eave = ((float)hits + p->er+p->bb)/p->try_num;
	else
	  eave = 0;

	sprintf(t1,"%6.3f",p->ave);
	for(i=0;i<sizeof(t1) && t1[i] != '.';i++)
		t1[i] = ' ';

	sprintf(t2,"%6.3f",eave);
	for(i=0;i<sizeof(t2) && t2[i] != '.';i++)
		t2[i] = ' ';

	printf("%-10s%5d%5d%5d%5d%7d%7d%5d%5d%5d%s%s\n",
		 p->fullname,
		 p->game,
		 p->hit_num,
		 p->try_num,
	         hits,
		 p->h1+p->h2*2+p->h3*3+p->h4*4,
		 p->bb,
		 p->get,
		 p->run,
		 p->steal,
	         t2,
		 t1);
    }


    hits = rec[total].h1+rec[total].h2+rec[total].h3+rec[total].h4;
    if(rec[total].try_num){
	  eave = ((float)hits +rec[total].er+rec[total].bb)/rec[total].try_num;
    }else{
	  eave = 0;
    }
    sprintf(t1,"%6.3f",rec[total].ave);
    for(i=0;i<sizeof(t1) && t1[i] != '.';i++)
		t1[i] = ' ';

    sprintf(t2,"%6.3f",eave);
    for(i=0;i<sizeof(t2) && t2[i] != '.';i++)
	t2[i] = ' ';

    printf("------------------------------------------------------------------\n");
    printf("%10s%5d%5d%5d%5d%7d%7d%5d%5d%5d%s%s\n",
		 rec[total].fullname,
		 rec[total].game,
		 rec[total].hit_num,
		 rec[total].try_num,
	         hits,
		 rec[total].h1+rec[total].h2*2+rec[total].h3*3+rec[total].h4*4,
		 rec[total].bb,
		 rec[total].get,
		 rec[total].run,
		 rec[total].steal,
	         t2,
		 t1);
}

print2()
{
    int i,hits;
    float eave;
    struct record *p;
    char t1[10],t2[10];

#ifdef notdef
    printf("\t\t<<< MonStars ÅŽŅ >>> \n");
    printf("%-10s%5s%5s%5s%5s%7s%7s%7s%5s%5s%5s%5s%7s%5s\n",
	   "žO","","ÅČ","Å","ĀÅ","{ÛÅ","ÛÅ",
	   "l","OU","Å_","ū_","Û","oÛĶ","ÅĶ");
#else
    printf("\t\t<<< MonStars ÅŽŅ >>> \n");
    printf("%-10s%4s%4s%4s%4s%4s%4s%4s%4s%4s%4s%4s%6s%6s\n",
	   "","","Å","Å","Ā","{","Û",
	   "l","O","Å","ū","","o","Å");
    printf("%-10s%4s%4s%4s%4s%4s%4s%4s%4s%4s%4s%4s%6s%6s\n",
	   "žO","","Č","","Å","Å","Å",
	   "","U","_","_","Û","Ķ","Ķ");
#endif
    for(p=top;p;p=p->next){
	hits = 	 p->h1+p->h2+p->h3+p->h4;
	if(p->try_num)
	  eave = ((float)hits + p->er+p->bb)/p->try_num;
	else
	  eave = 0;

	if( p->ave == 1.0 ){
	    sprintf(t1,"%6.3f",1.0);
	}else{
	    sprintf(t1,"%6.3f",p->ave);
	    for(i=0;i<sizeof(t1) && t1[i] != '.';i++)
		t1[i] = ' ';
	}

	if( eave == 1.0 ){
	    sprintf(t2,"%6.3f",1.0);
	}else{
	    sprintf(t2,"%6.3f",eave);
	    for(i=0;i<sizeof(t2) && t2[i] != '.';i++)
		t2[i] = ' ';
	}

#ifdef notdef
	printf("%-10s%5d%5d%5d%5d%7d%7d%7d%5d%5d%5d%5d%s%s\n",
#else
	printf("%-10s%4d%4d%4d%4d%4d%4d%4d%4d%4d%4d%4d%s%s\n",
#endif
		 p->fullname,
		 p->game,
		 p->try_num,
		 p->hit_num,
	         hits,
	         p->h4,
		 p->h1+p->h2*2+p->h3*3+p->h4*4,
		 p->bb,
		 p->k,
		 p->get,
		 p->run,
	         p->steal,
	         t2,
		 t1);
    }

    if(undertop) printf("\t---------- KčĒ ----------\n");
    for(p=undertop;p;p=p->next){
	if(!p->game) continue; /* skip if game is 0*/
	hits = 	 p->h1+p->h2+p->h3+p->h4;
	if(p->try_num)
	  eave = ((float)hits + p->er+p->bb)/p->try_num;
	else
	  eave = 0;

	if( p->ave == 1.0 ){
	    sprintf(t1,"%6.3f",1.0);
	}else{
	    sprintf(t1,"%6.3f",p->ave);
	    for(i=0;i<sizeof(t1) && t1[i] != '.';i++)
		t1[i] = ' ';
	}

	if( eave == 1.0 ){
	    sprintf(t2,"%6.3f",1.0);
	}else{
	    sprintf(t2,"%6.3f",eave);
	    for(i=0;i<sizeof(t2) && t2[i] != '.';i++)
		t2[i] = ' ';
	}

#ifdef notdef
	printf("%-10s%5d%5d%5d%5d%7d%7d%7d%5d%5d%5d%5d%s%s\n",
#else
	printf("%-10s%4d%4d%4d%4d%4d%4d%4d%4d%4d%4d%4d%s%s\n",
#endif
		 p->fullname,
		 p->game,
		 p->try_num,
		 p->hit_num,
	         hits,
	         p->h4,
		 p->h1+p->h2*2+p->h3*3+p->h4*4,
		 p->bb,
		 p->k,
		 p->get,
		 p->run,
		 p->steal,
	         t2,
		 t1);
    }


    hits = rec[total].h1+rec[total].h2+rec[total].h3+rec[total].h4;
    if(rec[total].try_num){
	  eave = ((float)hits +rec[total].er+rec[total].bb)/rec[total].try_num;
    }else{
	  eave = 0;
    }
    sprintf(t1,"%6.3f",rec[total].ave);
    for(i=0;i<sizeof(t1) && t1[i] != '.';i++)
		t1[i] = ' ';

    sprintf(t2,"%6.3f",eave);
    for(i=0;i<sizeof(t2) && t2[i] != '.';i++)
	t2[i] = ' ';

    printf("------------------------------------------------------------------\n");
#ifdef notdef
    printf("%10s%5d%5d%5d%5d%7d%7d%7d%5d%5d%5d%5d%s%s\n",
#else
    printf("%10s%4d%4d%4d%4d%4d%4d%4d%4d%4d%4d%4d%s%s\n",
#endif
		 rec[total].fullname,
		 rec[total].game,
		 rec[total].try_num,
		 rec[total].hit_num,
	         hits,
		 rec[total].h4,
		 rec[total].h1+rec[total].h2*2+rec[total].h3*3+rec[total].h4*4,
		 rec[total].bb,
		 rec[total].k,
		 rec[total].get,
		 rec[total].run,
		 rec[total].steal,
	         t2,
		 t1);
}

print3()
{
    int i,hits;
    float eave;
    struct record *p;
    char t1[10],t2[10];

    printf("\t\t<<< MonStars ÅŽŅ >>> \n");
    printf("%-10s%5s%5s%5s%5s%7s%7s%7s%7s%5s%5s%5s%5s%5s\n",
	"žO","","ÅČ","Å","PÅ","QÛÅ","RÛÅ","{ÛÅ",
	"l","OU","Å_","ū_","Û","ÅĶ");
    printf("------------------------------------------------------------------------------\n");

    for(p=top;p;p=p->next){
	hits = 	 p->h1+p->h2+p->h3+p->h4;
	if(p->try_num)
	  eave = ((float)hits + p->er+p->bb)/p->try_num;
	else
	  eave = 0;

	if( p->ave == 1.0 ){
	    sprintf(t1,"%6.3f",1.0);
	}else{
	    sprintf(t1,"%6.3f",p->ave);
	    for(i=0;i<sizeof(t1) && t1[i] != '.';i++)
		t1[i] = ' ';
	}

	if( eave == 1.0 ){
	    sprintf(t2,"%6.3f",1.0);
	}else{
	    sprintf(t2,"%6.3f",eave);
	    for(i=0;i<sizeof(t2) && t2[i] != '.';i++)
		t2[i] = ' ';
	}

	printf("%-10s%5d%5d%5d%5d%7d%7d%7d%7d%5d%5d%5d%5d%s\n",
		 p->fullname,
		 p->game,
		 p->try_num,
		 p->hit_num,
		 p->h1,
		 p->h2,
		 p->h3,
		 p->h4,
		 p->bb,
		 p->k,
		 p->get,
		 p->run,
		 p->steal,
		 t1);
    }

    if(undertop) printf("\t---------- KčĒ ----------\n");
    for(p=undertop;p;p=p->next){
	hits = 	 p->h1+p->h2+p->h3+p->h4;
	if(p->try_num)
	  eave = ((float)hits + p->er+p->bb)/p->try_num;
	else
	  eave = 0;

	if( p->ave == 1.0 ){
	    sprintf(t1,"%6.3f",1.0);
	}else{
	    sprintf(t1,"%6.3f",p->ave);
	    for(i=0;i<sizeof(t1) && t1[i] != '.';i++)
		t1[i] = ' ';
	}

	if( eave == 1.0 ){
	    sprintf(t2,"%6.3f",1.0);
	}else{
	    sprintf(t2,"%6.3f",eave);
	    for(i=0;i<sizeof(t2) && t2[i] != '.';i++)
		t2[i] = ' ';
	}

	printf("%-10s%5d%5d%5d%5d%7d%7d%7d%7d%5d%5d%5d%5d%s\n",
		 p->fullname,
		 p->game,
		 p->try_num,
		 p->hit_num,
		 p->h1,
		 p->h2,
		 p->h3,
		 p->h4,
		 p->bb,
		 p->k,
		 p->get,
		 p->run,
		 p->steal,
		 t1);
    }


    hits = rec[total].h1+rec[total].h2+rec[total].h3+rec[total].h4;
    if(rec[total].try_num){
	  eave = ((float)hits +rec[total].er+rec[total].bb)/rec[total].try_num;
    }else{
	  eave = 0;
    }
    sprintf(t1,"%6.3f",rec[total].ave);
    for(i=0;i<sizeof(t1) && t1[i] != '.';i++)
		t1[i] = ' ';

    sprintf(t2,"%6.3f",eave);
    for(i=0;i<sizeof(t2) && t2[i] != '.';i++)
	t2[i] = ' ';

    printf("------------------------------------------------------------------------------\n");
    printf("%-10s%5d%5d%5d%5d%7d%7d%7d%7d%5d%5d%5d%5d%s\n",
		 rec[total].fullname,
		 rec[total].game,
		 rec[total].hit_num,
		 rec[total].try_num,
		 rec[total].h1,
		 rec[total].h2,
		 rec[total].h3,
		 rec[total].h4,
		 rec[total].bb,
		 rec[total].k,
		 rec[total].get,
		 rec[total].run,
		 rec[total].steal,
		 t1);
}

print4()
{
    int i,k;
    char t1[20];

    printf("%-10s%5s%5s%5s%5s%7s%7s%7s%7s%5s%5s%5s%5s%5s\n",
	"žO","","ÅČ","Å","ĀÅ","QÛÅ","RÛÅ","{ÛÅ",
	"l","OU","Å_","ū_","Û","ÅĶ");
    printf("------------------------------------------------------------------------------\n");
    for(i=0;i<TOTALMEM;i++){
	if( rec[i].ave == 1.0 ){
		sprintf(t1,"%5.3f",rec[i].ave);
	}else{
		sprintf(t1,"%5.3f",rec[i].ave);
		for(k=0;k<sizeof(t1) && t1[k] != '.';k++){
			t1[k] = ' ';
		}
	}

	printf("%-10s%5d%5d%5d%5d%7d%7d%7d%7d%5d%5d%5d%5d%s\n",
		 rec[i].fullname,
		 rec[i].game,
		 rec[i].try_num,
		 rec[i].hit_num,
		 rec[i].h1,
		 rec[i].h2,
		 rec[i].h3,
		 rec[i].h4,
		 rec[i].bb,
		 rec[i].k,
		 rec[i].get,
		 rec[i].run,
		 rec[i].steal,
		 t1);
    }


    sprintf(t1,"%5.3f",rec[total].ave);
    for(k=0;k<sizeof(t1) && t1[k] != '.';k++){
		t1[k] = ' ';
    }
    printf("------------------------------------------------------------------------------\n");
    printf("%10s%5d%5d%5d%5d%7d%7d%7d%7d%5d%5d%5d%5d%s\n",
		 rec[total].fullname,
		 rec[total].game,
		 rec[total].try_num,
		 rec[total].hit_num,
		 rec[total].h1,
		 rec[total].h2,
		 rec[total].h3,
		 rec[total].h4,
		 rec[total].bb,
		 rec[total].k,
		 rec[total].get,
		 rec[total].run,
		 rec[total].steal,
		 t1);
}

print5()
{
    int i,hits;
    float eave;
    struct record *p;
    char t1[10],t2[10];

   /* printf("Content-type: text/html\n\n"); */

    printf("<html><head><title>Record</title></head>\n");
    printf("<body>\n");
    printf("<h1>MonStars ÅŽŅ</h1>\n");
    printf("<table align=center border collpadding=5>\n");
    printf("<tr><th>žO</th><th></th><th>ÅČ</th><th>Å</th><th>ĀÅ</th><th>{ÛÅ</th><th>ÛÅ</th><th>l</th><th>OU</th><th>Å_</th><th>ū_</th><th>Û</th><th>oÛĶ</th><th>ÅĶ</th></tr><tr></tr>\n");
    for(p=top;p;p=p->next){
	hits = 	 p->h1+p->h2+p->h3+p->h4;
	if(p->try_num)
	  eave = ((float)hits + p->er+p->bb)/p->try_num;
	else
	  eave = 0;

	if( p->ave == 1.0 ){
	    sprintf(t1,"%6.3f",1.0);
	}else{
	    sprintf(t1,"%6.3f",p->ave);
	    for(i=0;i<sizeof(t1) && t1[i] != '.';i++)
		t1[i] = ' ';
	}

	if( eave == 1.0 ){
	    sprintf(t2,"%6.3f",1.0);
	}else{
	    sprintf(t2,"%6.3f",eave);
	    for(i=0;i<sizeof(t2) && t2[i] != '.';i++)
		t2[i] = ' ';
	}

	printf("<tr>");
	printf("<td>%s</td>", p->fullname);
	printf("<td>%d</td>", p->game);
	printf("<td>%d</td>", p->try_num);
	printf("<td>%d</td>", p->hit_num);
	printf("<td>%d</td>", hits);
	printf("<td>%d</td>", p->h4);
	printf("<td>%d</td>", p->h1+p->h2*2+p->h3*3+p->h4*4);
	printf("<td>%d</td>", p->bb);
	printf("<td>%d</td>", p->k);
	printf("<td>%d</td>", p->get);
	printf("<td>%d</td>", p->run);
	printf("<td>%d</td>", p->steal);
	printf("<td>%s</td>", t2);
	printf("<td>%s</td>", t1);
	printf("</tr>\n");

/*
	printf("%-10s%5d%5d%5d%5d%7d%7d%7d%5d%5d%5d%5d%s%s\n",
		 p->fullname,
		 p->game,
		 p->try_num,
		 p->hit_num,
	         hits,
	         p->h4,
		 p->h1+p->h2*2+p->h3*3+p->h4*4,
		 p->bb,
		 p->k,
		 p->get,
		 p->run,
	         p->steal,
	         t2,
		 t1);
*/
    }

    if(undertop) printf("<tr><td align=center colspan=14>KčĒ</td></tr>\n");
    for(p=undertop;p;p=p->next){
	hits = 	 p->h1+p->h2+p->h3+p->h4;
	if(p->try_num)
	  eave = ((float)hits + p->er+p->bb)/p->try_num;
	else
	  eave = 0;

	if( p->ave == 1.0 ){
	    sprintf(t1,"%6.3f",1.0);
	}else{
	    sprintf(t1,"%6.3f",p->ave);
	    for(i=0;i<sizeof(t1) && t1[i] != '.';i++)
		t1[i] = ' ';
	}

	if( eave == 1.0 ){
	    sprintf(t2,"%6.3f",1.0);
	}else{
	    sprintf(t2,"%6.3f",eave);
	    for(i=0;i<sizeof(t2) && t2[i] != '.';i++)
		t2[i] = ' ';
	}

	printf("<tr>");
	printf("<td>%s</td>", p->fullname);
	printf("<td>%d</td>", p->game);
	printf("<td>%d</td>", p->try_num);
	printf("<td>%d</td>", p->hit_num);
	printf("<td>%d</td>", hits);
	printf("<td>%d</td>", p->h4);
	printf("<td>%d</td>", p->h1+p->h2*2+p->h3*3+p->h4*4);
	printf("<td>%d</td>", p->bb);
	printf("<td>%d</td>", p->k);
	printf("<td>%d</td>", p->get);
	printf("<td>%d</td>", p->run);
	printf("<td>%d</td>", p->steal);
	printf("<td>%s</td>", t2);
	printf("<td>%s</td>", t1);
	printf("</tr>\n");

/*
	printf("%-10s%5d%5d%5d%5d%7d%7d%7d%5d%5d%5d%5d%s%s\n",
		 p->fullname,
		 p->game,
		 p->try_num,
		 p->hit_num,
	         hits,
	         p->h4,
		 p->h1+p->h2*2+p->h3*3+p->h4*4,
		 p->bb,
		 p->k,
		 p->get,
		 p->run,
		 p->steal,
	         t2,
		 t1);
*/
      }


    hits = rec[total].h1+rec[total].h2+rec[total].h3+rec[total].h4;
    if(rec[total].try_num){
	  eave = ((float)hits +rec[total].er+rec[total].bb)/rec[total].try_num;
    }else{
	  eave = 0;
    }
    sprintf(t1,"%6.3f",rec[total].ave);
    for(i=0;i<sizeof(t1) && t1[i] != '.';i++)
		t1[i] = ' ';

    sprintf(t2,"%6.3f",eave);
    for(i=0;i<sizeof(t2) && t2[i] != '.';i++)
	t2[i] = ' ';

    printf("<tr></tr>\n");
	printf("<tr>");
	printf("<td>%s</td>", rec[total].fullname);
	printf("<td>%d</td>", rec[total].game);
	printf("<td>%d</td>", rec[total].try_num);
	printf("<td>%d</td>", rec[total].hit_num);
	printf("<td>%d</td>", hits);
	printf("<td>%d</td>", rec[total].h4);
	printf("<td>%d</td>", rec[total].h1+rec[total].h2*2+rec[total].h3*3+rec[total].h4*4);
	printf("<td>%d</td>", rec[total].bb);
	printf("<td>%d</td>", rec[total].k);
	printf("<td>%d</td>", rec[total].get);
	printf("<td>%d</td>", rec[total].run);
	printf("<td>%d</td>", rec[total].steal);
	printf("<td>%s</td>", t2);
	printf("<td>%s</td>", t1);
	printf("</tr>\n");
  
    printf("</table>\n");
    printf("</body></html>\n");

/*
    printf("%10s%5d%5d%5d%5d%7d%7d%7d%5d%5d%5d%5d%s%s\n",
		 rec[total].fullname,
		 rec[total].game,
		 rec[total].try_num,
		 rec[total].hit_num,
	         hits,
		 rec[total].h4,
		 rec[total].h1+rec[total].h2*2+rec[total].h3*3+rec[total].h4*4,
		 rec[total].bb,
		 rec[total].k,
		 rec[total].get,
		 rec[total].run,
		 rec[total].steal,
	         t2,
		 t1);
*/
}

getentry(buf,line)
char *buf;
int line;
{
	int i=0;

	/* skip first 0-9@>.... */
	for(;;){
		if(islower(*(buf+i))){
			buf = buf + i;
			break;
		}else{
			i++;
		}
	}

	if(strstr(buf,"kurachi") == buf){
		fillin(kurachi,buf);
	}else if(strstr(buf,"hiro") == buf){
		fillin(hiro,buf);
	}else if(strstr(buf,"sinozaki") == buf){
		fillin(sinozaki,buf);
	}else if(strstr(buf,"dai") == buf){
		fillin(dai,buf);
	}else if(strstr(buf,"tamotsu") == buf){
		fillin(tamotsu,buf);
	}else if(strstr(buf,"y-osa") == buf){
		fillin(yamashita,buf);
	}else if(strstr(buf,"sophia") == buf){
		fillin(sophia,buf);
	}else if(strstr(buf,"ogata") == buf){
		fillin(ogata,buf);
	}else if(strstr(buf,"ehara") == buf){
		fillin(ehara,buf);
	}else if(strstr(buf,"sueyoshi") == buf){
		fillin(sueyoshi,buf);
/*
	}else if(strstr(buf,"ito") == buf){
		fillin(ito,buf);
*/
	}else if(strstr(buf,"ekimura") == buf){
		fillin(ekimura,buf);
	}else if(strstr(buf,"mine") == buf){
		fillin(mine,buf);
	}else if(strstr(buf,"haya") == buf){
		fillin(haya,buf);
	}else if(strstr(buf,"tshimizu") == buf){
		fillin(tshimizu,buf);
	}else if(strstr(buf,"hazedon") == buf){
		fillin(hazedon,buf);
	}else if(strstr(buf,"suzu") == buf){
		fillin(suzu,buf);
	}else if(strstr(buf,"tanaka") == buf){
		fillin(tanaka,buf);
	}else if(strstr(buf,"juzu") == buf){
		fillin(juzu,buf);
	}else if(strstr(buf,"takemoto") == buf){
		fillin(takemoto,buf);
	}else if(strstr(buf,"nakajima") == buf){
		fillin(nakajima,buf);
	}else if(strstr(buf,"ohta") == buf){
		fillin(ohta,buf);
	}else if(strstr(buf,"mizutani") == buf){
		fillin(mizutani,buf);
	}else if(strstr(buf,"ohnishi") == buf){
		fillin(ohnishi,buf);
	}else if(strstr(buf,"takasu") == buf){
		fillin(takasu,buf);
	}else if(strstr(buf,"tsuchie") == buf){
		fillin(tsuchie,buf);
	}else if(strstr(buf,"sugioka") == buf){
		fillin(sugioka,buf);
	}else if(strstr(buf,"machiyama") == buf){
		fillin(machiyama,buf);
	}else if(strstr(buf,"siozawa") == buf){
		fillin(siozawa,buf);
	}else if(strstr(buf,"fujinaga") == buf){
		fillin(fujinaga,buf);
	}else if(strstr(buf,"kojiro") == buf){
		fillin(kojiro,buf);
	}else if(strstr(buf,"sakurai") == buf){
		fillin(sakurai,buf);
	}else if(strstr(buf,"itoh") == buf){
		fillin(itoh,buf);
	}else if(strstr(buf,"kawahara") == buf){
		fillin(kawahara,buf);
	}else if(strstr(buf,"okiyama") == buf){
		fillin(okiyama,buf);
	}else if(strstr(buf,"fuchida") == buf){ /* Helper */
		;
	}else if(strstr(buf,"arai") == buf){ /* Helper */
		;
	}else if(strstr(buf,"saitoh") == buf){ /* Helper */
		;
	}else{
		printf("Format error! at line %d %s\n",line, buf);
		exit(1);
	}
}

/* token:CjO-ōn-Ę[-Å_[-Û]] */

char *getnexttoken(buf)
char *buf;
{
	char *p =buf;
	for(;*p && *p != ' ' && *p != '\t' && *p != '\n';p++);
	for(;*p && (*p == ' ' || *p == '\t' || *p == '\n');p++);
	return(p);
}

fillin(id,buf)
int id;
char *buf;
{
    char *p = buf;

    rec[id].game += 1;
    while(*(p = getnexttoken(p))){
	rec[id].try_num += 1;
	rec[id].hit_num += 1;

	/* check the 1st field */

	/* check the 2nd field */
	for(;*p != '-'; p++);
	p++;
	switch(*p){
	    case 'B': /* four ball */
	    case 'D': /* dead ball */
		rec[id].hit_num -= 1;
		rec[id].bb += 1;
		break;
	    case 'I': /* interfere */
		rec[id].hit_num -= 1;
		break;
	    case 'K': /* three strike out */
		rec[id].k += 1;
		break;
#if 1 /* added on 2004/06/19 to support pinch-runner */
	    case 'R': /* daisou (pinch-runner) */
		rec[id].hit_num -= 1;
		break;
#endif
	    default:
		/* printf("Data error?\n"); /* */
		;
	}
		
	/* check the 3rd field */
	if(*(p+1) == '*'){rec[id].run++; continue;}
	for(p;*p != '-' && !isspace(*p); p++);
	if(isspace(*p)) continue;
	p++;
	switch(*p){
	    case 'H':
	        switch(*(++p)){
		    case '1':
			rec[id].h1 += 1;
			break;
		    case '2':
			rec[id].h2 += 1;
			break;
		    case '3':
			rec[id].h3 += 1;
			break;
		    case 'R':
			rec[id].h4 += 1;
			break;
		    default:
			printf("Format error!(%s)\n",buf);
		}
		break;
	    case 'E':
		rec[id].er += 1;
		break;
	    case 'G':
		rec[id].hit_num -= 1;
		break;
	}

	/* check the 4th field */
	if(*(p+1) == '*'){rec[id].run++; continue;}
	for(p;*p != '-' && !isspace(*p); p++);
	if(isspace(*p)) continue;
	p++;
	switch(*p){
	    case '1':
		rec[id].get += 1;
		break;
	    case '2':
		rec[id].get += 2;
		break;
	    case '3':
		rec[id].get += 3;
		break;
	    case '4':
		rec[id].get += 4;
		break;
	}

	/* check the 5th(steal) field */
	if(*(p+1) == '*'){rec[id].run++; continue;}
	for(p;*p != '-' && !isspace(*p); p++);
	if(isspace(*p)) continue;
	if(*p == '*'){rec[id].run++; continue;}
	p++;
	switch(*p){
	    case '1':
		rec[id].steal += 1;
		break;
	    case '2':
		rec[id].steal += 2;
		break;
	    case '3':
		rec[id].steal += 3;
		break;
	}
	if(*(p+1) == '*'){rec[id].run++; continue;}

    }
}

