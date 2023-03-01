#include <stdio.h>
#include <stdlib.h>
#include <string.h>

	struct foodlist{
		char food_name[200];
		int foodgram;
		float food_pay;
		struct foodlist *next;
	};
	
	struct foodlist *first=NULL;
	struct foodlist *andd=NULL;
		
	FILE *fl=fopen("\\Users\\enest\\Desktop_2\\2.sınıf\\veri yapıları\\odev_1\\menu.txt","r+a");  // menu dosyas�n� okuma+yazma format�nda a�ar

	void preparation(){		 	       // txt deki verileri listeye alma (�n haz�rl�k)
		
		while(!feof(fl)){ 
			struct foodlist *temp=(struct foodlist*) malloc(sizeof(struct foodlist));
			struct foodlist *iter=temp;
			fscanf(fl,"%s",iter->food_name);
			fscanf(fl,"%d",&iter->foodgram);	
			fscanf(fl,"%f",&iter->food_pay);
		
			if(first==NULL){
				first=temp;
				first->next=first;
				andd=first;	
			}
			struct foodlist *devriye=first->next;
			struct foodlist *devriye2=NULL;		
			if(temp->food_pay >= andd->food_pay){
				andd->next=temp;
				temp->next=first;
				andd=temp;
			}
			if(temp->food_pay <= first->food_pay){
				andd->next=temp;
				temp->next=first;
				first=temp;
			}
			if(temp->food_pay > first->food_pay && temp->food_pay < andd->food_pay){
				devriye2=andd;
				while(temp->food_pay > devriye->food_pay){
					devriye2=devriye;
					devriye=devriye->next;
				}
				devriye2->next=temp;
				temp->next=devriye;
			}
			
		}	
	}

	void addfood(){		               // kullan�c�n�n girdi�i yeme�i s�ral� olarak listeye ve txt ye kaydetme...
	char gecici[100];
		struct foodlist *temp=(struct foodlist*) malloc(sizeof(struct foodlist));
		struct foodlist *iter=temp;
		printf("eklemek istediginiz yemegin ismini giriniz: "); scanf("%s",iter->food_name);
		printf("yememgin gramini giriniz: "); scanf("%d",&iter->foodgram);
		printf("fiyatini giriniz: "); scanf("%f",&iter->food_pay);
	//	printf("%s",iter->food_name);
		
		fprintf(fl,"\n%s ",iter->food_name);
		fprintf(fl,"%d ",iter->foodgram);
		fprintf(fl,"%0.2f",iter->food_pay);
		
				if(first==NULL){
				first=temp;
				first->next=first;
				andd=first;	
			}
			struct foodlist *devriye=first->next;
			struct foodlist *devriye2=NULL;		
			if(temp->food_pay >= andd->food_pay){
				andd->next=temp;
				temp->next=first;
				andd=temp;
			}
			if(temp->food_pay < first->food_pay){
				andd->next=temp;
				temp->next=first;
				first=temp;
			}
			if(temp->food_pay == first->food_pay){
				temp->next=first->next;
				first->next=temp;	
			}
			
			if(temp->food_pay > first->food_pay && temp->food_pay < andd->food_pay){
				while(temp->food_pay > devriye->food_pay){
					devriye2=devriye;
					devriye=devriye->next;
				}
				devriye2->next=temp;
				temp->next=devriye;
			}
			

	}
	
	void printlist(){	               // listeleme
		system("cls");
	
		struct foodlist *temp=first;
		
		do{
			printf("%s:\t\tgramaj:\t%d, fiyat:  %0.2f\n",temp->food_name,temp->foodgram,temp->food_pay);
			temp=temp->next;	
		}while(temp!=first);
		printf("\n\n");
	}
	
	void dellist(){			           // silme
		int cont=0;
		struct foodlist *prev=andd;
		struct foodlist *iter=first;
		char *list_name;
		list_name=iter->food_name;
		char *del, del1[100];
		printf("ismi giriniz: "); scanf("%s",del1);
		del=&del1[0];	
		int i=0;
		do{	
			list_name=iter->food_name;
			if(list_name[i]==del[i]){
				i++;
				int a=0;
				while(list_name[a]!=NULL && del[a]!=NULL){
					a++;
				}
				
				if(list_name[a]==NULL && del[a]==NULL){
					system("cls");
					printf("girilen yemek bulundu");
					prev->next=iter->next;
					free(iter);
					cont=1;
				}
				
				if(cont==1){
					printf("\nsilme islemi basarili.\n\n");
					break;	
				}
			}
			prev=iter;	
			iter=iter->next;
		}while(iter!=first);
		
		if(iter==first){
			printf("\nGirilen yemek bulunamadi!!!\n\n");	
		} 
				
    }
	
	void selectionfood(){
		system("cls");
		char selection;
		selection=getchar();
		struct foodlist *temp=first;
		printf("istediginiz yemek ise (e), degil ise (h) yi tuslayin.\nAna menuye donmek icin (a) tuslayin\n\n");
		printf("%s %dgr %0.2fTL (e),(h)\n",temp->food_name,temp->foodgram,temp->food_pay);
		scanf("%c",&selection);
		temp=temp->next;
		
		while(selection=='h'){
			selection=getchar();
			printf("%s %dgr %0.2fTL (e),(h)\n",temp->food_name,temp->foodgram,temp->food_pay);
			scanf("%c",&selection);
			
			if(selection=='h'){
				temp=temp->next;
			}
			else break;
		}
		if(selection=='a'){
		system("cls");
		}
		
		if(selection=='e'){
			printf("\nsecilen yemek: %s\nAfiyet olsun.\n",temp->food_name);
		}	
	}
	
	void exit(){
		struct foodlist *temp=first;
		fclose(fl);
		FILE *fl=fopen("menu.txt","w");  // txt yi a�ar i�indeki her�eyi siler

		do{
		fprintf(fl,"%s",temp->food_name);
		fprintf(fl," %d",temp->foodgram);
		fprintf(fl," %0.2f",temp->food_pay);
		if(temp!=andd) fprintf(fl,"\n");
		
		printf("%s",temp->food_name);
		printf(" %d",temp->foodgram);
		printf(" %0.2f",temp->food_pay);
		if(temp!=andd) printf("\n");
		
		
		temp=temp->next;	
		}while(temp!=first);
		
	}
	
int main(){
	preparation();  // ilk kod ba�lad���nda txtdeki verileri listeye s�ral� olarak kaydeder..
	int i=0,exitt=0;
	while(1){
		if(exitt==1){
			system("cls");
			printf("\nSistemden basariyla cikis yapildi...\niyi gunler...");
			return 0;
		}
		printf("Yemek kaydi icin(1), Yemek kaydi silmek icin(2), Listeyi goruntulemek icin(3), Yemek secimi icin(4), Cikis icin(5)\n\n");
    	scanf("%d",&i);
		switch (i){
			case 1:
				addfood();
				break;
			case 2:
				dellist();
				break;
			case 3:
				printlist();
				break;
			case 4:
				selectionfood();
				break;
			case 5:
				exit();
				exitt=1;
				break;
			default:
				printf("Lutfen gecerli bir sayi giriniz!!!");
				break;				
		}
	}		
	return 0;	
}
	
