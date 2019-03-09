#include <stdio.h>
#include <stdlib.h>
#include <time.h>

 typedef struct Reservation {
    char location_id[50],reservation_time[50],latitude[50],longitude[50],city[20];
    int reservation_id;
    struct Reservation * next;
    struct Reservation * prev;
    struct Users *rootUser;

}reservation;


   typedef struct Categories{
    char category_name[20],*category_via;
    int sub_category_count,user_count,reservation_count,depth;
    struct Categories * next;
    struct Categories * prev;
    struct Map *prevMap;
    struct Categories * sub_category[10];
    struct Users *Users[20];

 }categories;
 //BÝNARY SEARCH TREE
 typedef struct Users{
    char *user_id , *category_name;
    int  rezervation_count,id;
    struct Users *next;
    struct Users *prev;
    struct Users *leftChild;
    struct Users *rightChild;
    struct Reservation *rootReservation;
    struct Categories *rootCategory;

 }users;
 reservation* reservationAdd(reservation *r , char location_id[],char reservation_time[],char latitude[],char longitude[],char city[]){
    if(r==NULL){
        reservation *temp = (reservation * )malloc(sizeof(reservation));
        strcpy(temp->location_id,location_id);
        strcpy(temp->reservation_time,reservation_time);
        strcpy(temp->latitude,latitude);
        strcpy(temp->longitude,longitude);
        strcpy(temp->city,city);
        temp -> reservation_id = 0;
        temp -> prev = NULL;
        temp -> next = NULL;
        return temp;

    }else{
        reservation *temp = (reservation * )malloc(sizeof(reservation));
        strcpy(temp->location_id,location_id);
        strcpy(temp->reservation_time,reservation_time);
        strcpy(temp->latitude,latitude);
        strcpy(temp->longitude,longitude);
        strcpy(temp->city,city);
        temp -> reservation_id = (temp -> prev -> reservation_id) +1;

        reservation *iter=r;
        while(iter->next != NULL)
            iter = iter->next;

        iter -> next = temp;
        temp -> prev = iter;
        temp -> next = NULL;
        return r;
    }
}
 reservation* reservationDelete(reservation *r,int reservation_id){
    reservation *iter=r;
    while(iter->next != NULL && (iter -> next -> reservation_id != reservation_id))
        iter = iter -> next;
    if(iter -> next -> reservation_id == reservation_id){
        reservation *temp = iter->next;
        iter -> next = temp -> next;
        temp -> next -> prev = iter;
        while(temp != NULL)
            temp -> reservation_id -= 1;
        free(temp);
        printf("Reservation was delete!\n");
        return r;

    }else{
        printf("Reservation not found..!\n");
        return r;
    }

 }

  void printReservation(reservation *r){
      if(r != NULL){
        printf("Location id: %s\n",r->location_id);
        printf("Reservation time: %s\n",r->reservation_time);
        printf("Latitude: %s\n",r->latitude);
        printf("Longitude: %s\n",r->longitude);
        printf("City: %s\n",r->city);
        printf("Reservation id: %d\n",r->reservation_id);
        printf("-----------------------------------------\n");
        printReservation(r->next);
      }

  }
 users* userAdd(categories *c,users *u,char *user_name){
    if(u==NULL){
        users *temp = (users*)malloc(sizeof(users));
        temp->category_name =c->category_name;
        temp->id=1;
        temp->leftChild=NULL;
        temp->rightChild=NULL;
        temp->next=NULL;
        temp->prev =NULL;
        temp->rootCategory=c;
        temp->rezervation_count=0;
        temp->rootReservation=NULL;
        temp->user_id=user_name;

        c->Users[c->user_count]=temp;
        c->user_count++;
        while(c->prev!=NULL){
            c->prev->user_count++;
            c=c->prev;
        }
        return temp;
    }




 }

 void printUsers(users *u){
    if(u!=NULL){
        printUsers(u->leftChild);
        printf("User id: %d\n",u->id);
        printf("User name: %s\n",u->user_id);
        printf("Category name: %s\n",u->category_name);
        printf("Reservation count: %d\n",u->rezervation_count);
        printf("---------------------------------------------------\n");
        printUsers(u->rightChild);
    }

 }

 users* userDelete(users *u,char user_id[]){
    // 1. Durumda belli bir kategorinin altýnda yer alan tüm kullanýcýlar silinmelidir.
    // 2. durumda ise belli bir kategori altýndaki belli bir kullanýcý bulunarak silinmelidir.
    // 3. durumda ise belli bir kullanýcýnýn tüm kategorilerdeki kullanýcý düðümleri silinmelidir.
    int ch;
    printf("1- Delete users under Category\n");
    printf("2- Delete a specific user under the category\n");
    printf("3- Delete a user node in all categories\n");
    scanf("%d",&ch);
    switch(ch){
        case 1:
            break;
        case 2:
            break;
        case 3:
            break;
        default:
            break;

    }
 }


 typedef struct Map{
    int sub_category_count,depth;
    char *via;
    categories * subCategory[50];
 }map;


char* concat(const char *s1, const char *s2)
{
    char *result = malloc(strlen(s1) + strlen(s2) + 1);
    strcpy(result, s1);
    strcat(result, s2);
    return result;
}
 categories* categoryAdd(map *m,categories *c, char category_name[],char *ust_category_name){
    if(c==NULL){
            categories *temp = (categories*)malloc(sizeof(categories));
            strcpy(temp->category_name,category_name);
            temp->depth=1;
            temp->category_via = concat(m->via,category_name);
            temp->prevMap=m;
            temp->next =NULL;
            temp->prev =NULL;
            temp->reservation_count =0;
            temp->user_count=0;
            temp->sub_category_count=0;
            temp->sub_category[temp->sub_category_count]=NULL;
            temp->Users[temp->user_count]=NULL;
            m->subCategory[m->sub_category_count] = temp;
            m->sub_category_count++;
            return temp;
    }
    categories *iter =c;
    if(ust_category_name!=NULL){

        while(iter->next!=NULL && strcmp(iter->category_name,ust_category_name)!=0)
            iter=iter->next;
        if(strcmp(iter->category_name,ust_category_name)==0){
            categories *temp = (categories*)malloc(sizeof(categories));
            char *via = concat(iter->category_via,":");

            strcpy(temp->category_name,category_name);
            temp ->category_via =concat(via,category_name);
            temp ->depth=iter->depth+1;
            temp ->next =NULL;
            temp ->prev = iter;
            temp ->reservation_count = 0;
            temp ->user_count = 0;
            temp ->Users[temp->user_count] = NULL;
            temp ->sub_category_count =0;
            temp ->prevMap=NULL;



            iter ->sub_category[iter->sub_category_count] = temp;
            iter->sub_category_count++;

            while(iter->prev!=NULL){
                iter ->prev->sub_category_count++;
                iter=iter->prev;
            }
            while(iter->next!=NULL)
                iter=iter->next;
            iter ->next =temp;

            return c;
        }
    }
    while(iter->next!=NULL)
        iter=iter->next;

    categories *temp = (categories*)malloc(sizeof(categories));
    char *via = concat(iter->category_via,":");

    strcpy(temp->category_name,category_name);
    temp ->category_via =concat(via,category_name);
    temp ->depth=iter->depth+1;
    temp ->next =NULL;
    temp ->prev = iter;
    temp ->reservation_count = 0;
    temp ->user_count = 0;
    temp ->Users[temp->user_count] = NULL;
    temp ->sub_category_count =0;
    temp ->prevMap=NULL;


    iter ->next =temp;
    iter ->sub_category[iter->sub_category_count] = temp;
    iter->sub_category_count++;

    while(iter->prev!=NULL){
        iter ->prev->sub_category_count++;
        iter=iter->prev;
    }


    return c;

 }

categories* categoryDelete(categories *c,char category_name[]){
    /*- Kategori silme: Kategori silme iþlemi sýrasýnda silinecek kategori düðümüne doðrudan baðlý
    kullanýcý düðümleri varsa onlar da kategoriyle beraber silinecektir.
    Ayrýca silinecek kategorinin altýnda bulunan kategoriler silinmemeli bunun yerine silinecek kategorinin bir üst düðümüne baðlanmalýdýr. */
    categories *iter = c;
    categories *temp;
    if(strcmp(iter->category_name,category_name)==0){

        if(iter->next!=NULL){
            temp = iter->next;
            while(temp!=NULL){
                temp->depth--;
                temp=temp->next;
            }
            temp = iter->next;
            temp->category_via = concat("Reservation:",temp->category_name);
            while(temp->next!=NULL){
                char *via = concat(temp->category_via,":");
                temp->next->category_via =concat(via,temp->next->category_name);
                temp=temp->next;
            }
            temp = iter->next;
            temp->prevMap = iter->prevMap;
            temp->prev = iter->prev;

            iter=NULL;
            return temp;
        }
        iter=NULL;
        return iter;
    }

    while(iter->next != NULL && strcmp(iter->next->category_name,category_name)!=0)
        iter=iter->next;

    temp = iter->next;
    if(temp!=NULL){
        if(strcmp(temp->category_name,category_name)==0){

            if(temp->next!=NULL){
                while(temp->next!=NULL){
                    char *via = concat(iter->category_via,":");
                    temp->next->category_via =concat(via,temp->next->category_name);
                    temp=temp->next;
                }
                temp = iter->next;
                iter->next = temp->next;
                temp->next->prev = iter;
                temp->next->depth--;

                temp=NULL;
                iter->sub_category_count--;
                while(iter->prev!=NULL){
                    iter->prev->sub_category_count--;
                    iter=iter->prev;
                }
                return iter;
            }
            iter->sub_category_count--;
            iter->next=NULL;
            while(iter->prev!=NULL){
               iter->prev->sub_category_count--;
               iter=iter->prev;
            }

            return iter;

        }
    }
    return c;
 }
 void printCategory(categories *c){
     while(c!=NULL){
            printf("----------------------------------------------\n");
            printf("Category name : %s\n",c->category_name);
            printf("Category via : %s\n",c->category_via);
            printf("Sub category count : %d\n",c->sub_category_count);
            printf("Users count : %d\n",c->user_count);
            printf("Reservation count : %d\n",c->reservation_count);
            printf("Depth : %d\n",c->depth);
            printf("----------------------------------------------\n");
            for(int i=0;i<c->user_count;i++){
                if(c->Users[i]!=NULL){
                    printUsers(c->Users[i]);
                }
            }


            c = c->next;
     }

 }

 categories* categorySearch(map *m,categories *c , char category_name[]){
    if(c != NULL){
        categories *iter = c;
        while(iter->next!=NULL && strcmp(iter->category_name,category_name)!=0)
            iter=iter->next;
        if(strcmp(iter->category_name,category_name)==0){
            printCategory(iter);
            int secim;
            char category[20];
            printf("1-Add category under this category\n");
            printf("2-Delete this category\n");
            printf("3-No,Thanks!\n");
            scanf("%d",&secim);
            switch(secim){
                case 1:
                    printf("Kategori ismini giriniz: ");
                    scanf("%s",&category);
                    c=categoryAdd(m,iter,category,category_name);
                    break;
                case 2:
                    c=categoryDelete(c,category_name);
                    break;
                case 3:
                    break;
                case 4:
                    break;
                default:
                    break;

            }
            return c;
        }
    }
    return c;
 }

map* kategoriIslem(map *m){
    int secim;
    printf("1- Kategori ekle\n");
    printf("2- Kategori sil\n");
    printf("3- Kategori bul\n");
    scanf("%d",&secim);

    char category_name[20];
    printf("Kategori ismini giriniz: ");
    scanf("%s",&category_name);

    switch(secim){
        case 1:
            m->subCategory[m->sub_category_count]= categoryAdd(m,m->subCategory[m->sub_category_count],category_name,NULL);
            break;
        case 2:
            for(int i=0;i<m->sub_category_count;i++){
                if(m->subCategory[i]!=NULL)
                     m->subCategory[i]=categoryDelete(m->subCategory[i],category_name);

            }
            break;
        case 3:
            for(int i=0;i<m->sub_category_count;i++){
                if(m->subCategory[i]!=NULL){
                     m->subCategory[i]=categorySearch(m,m->subCategory[i],category_name);
                }

            }
            break;
        default:
            break;
    }
    return m;
}
categories* kategoriBul(map *m,categories *c,char category_name[]){
    if(c != NULL){
        categories *iter = c;
        while(iter->next!=NULL && strcmp(iter->category_name,category_name)!=0)
            iter=iter->next;
        if(strcmp(iter->category_name,category_name)==0){
            return iter;
        }
        return NULL;
    }
    return NULL;

}
map* kullaniciIslem(map *m){
    int secim;
    char user_name[20], category_name[20];
    printf("1- Kullanici ekle\n");
    printf("2- Kullanici sil\n");
    printf("3- Kullanici goruntule\n");
    scanf("%d",&secim);
    printf("Kullanici ismini giriniz: ");
    scanf("%s",&user_name);
    switch(secim){
        case 1:
            printf("Kategori ismini giriniz: ");
            scanf("%s",&category_name);
            categories *c=NULL;
            for(int i=0;i<m->sub_category_count;i++){
                if(m->subCategory[i]!=NULL){
                    c=kategoriBul(m,m->subCategory[i],category_name);
                    if(c!=NULL){
                        c->Users[c->user_count] = userAdd(c,c->Users[c->user_count],user_name);
                    }
                }
            }
            break;
        case 2:
            break;
        case 3:
            break;
        default:
            break;
    }
    return m;
}
void rezervasonIslem(){
    int secim;
    printf("1- Rezervasyon ekle\n");
    printf("2- Rezervasyon iptal et\n");
    printf("3- Rezervasyon incele\n");
    switch(secim){
        case 1:
            break;
        case 2:
            break;
        case 3:
            break;
        default:
            break;
    }
}
void listeleIslem(){
    int secim;
    printf("1- Kullaniciya gore kategori listeleme\n");
    printf("2- Kategoriye gore kullanici listele\n");
    printf("3- Rezervasyon yerine gore kullanici listele\n");
    printf("4- Kullaniciya gore rezervasyon listele\n");
    scanf("%d",&secim);
    switch(secim){
        case 1:
            break;
        case 2:
            break;
        case 3:
            break;
        case 4:
            break;
        default:
            break;
    }
}

map* createMap(map *m){
    if(m==NULL){
        map* temp = (map*)malloc(sizeof(map));
        temp->sub_category_count=0;
        for(int i=0;i<sizeof(m->subCategory)/4;i++)
            temp->subCategory[i]=NULL;
        temp->depth =0;
        temp->via="Reservation:";
        return temp;
    }
}

int main(){
    /*
        1- Kategori Bulma
        2- Kategori ekleme
        3- Kategori Silme
        4- Kullanici ekleme
        5- Kullanici silme
        6- Kullaniciya göre kategori listeleme
        7- Kategoriye göre kullanici listeleme
        8- Rezervasyon yerine göre kullanici listeleme
        9- Kullaniciya göre rezervasyon listeleme
    */

    char kullanici_id[50],yer_id[50],zaman[50],enlem[50],boylam[50],sehir[50],kategori[50],altkategori[50];
   FILE *fp1;
   char birkelime[100];
   char *c,*pch;
   int i;
   fp1 = fopen("rezervasyon.txt","r");
   do {
     c = fgets(birkelime,100,fp1); /* bir satir okuyalim */
     pch = strtok (birkelime,",");
     i=1;
     if (c != NULL){
        while (pch != NULL)
        {
            switch(i){
                case 1:
                    strcpy(kullanici_id,pch);
                    break;
                case 2:
                    strcpy(yer_id,pch);
                    break;
                case 3:
                    strcpy(zaman,pch);
                    break;
                case 4:
                    strcpy(enlem,pch);
                    break;
                case 5:
                    strcpy(boylam,pch);
                    break;
                case 6:
                    strcpy(sehir,pch);
                    break;
                case 7:
                    strcpy(kategori,pch);
                    break;
                default :
                    break;
            }
            pch = strtok (NULL, ",");
            i++;
        }
        pch = strtok(kategori,":");
        i=1;
        while(pch!=NULL){
            if(i==1){
                strcpy(kategori,pch);
                i++;
            }
            else{
                strcpy(altkategori,pch);
            }
            pch = strtok(NULL,":");
        }
     }
   } while (c != NULL);          /* ta ki NULL olana kadar.. */
   fclose(fp1);
        map *m = NULL;
        m=createMap(m);
        m->subCategory[0]=categoryAdd(m,m->subCategory[0],kategori,NULL);
        m->subCategory[0]=categoryAdd(m,m->subCategory[0],altkategori,kategori);
        categories *d=NULL;
        d=kategoriBul(m,m->subCategory[0],altkategori);
        d->Users[0]=userAdd(d,d->Users[0],kullanici_id);

        for(int i=0;i<m->sub_category_count;i++)
            printCategory(m->subCategory[i]);


    int secim;
    do{
        printf("1- Kategori islemleri\n");
        printf("2- Kullanici islemleri\n");
        printf("3- Rezervasyon islemleri\n");
        printf("4- Listeleme islemleri\n");
        printf("0- Cikis\n");
        scanf("%d",&secim);
        switch(secim){
            case 1:
                m=kategoriIslem(m);
                break;
            case 2:
                m=kullaniciIslem(m);
                break;
            case 3:
               // rezervasyonIslem();
                break;
            case 4:
              //  listeleIslem();
                break;
            default:
                exit(1);
                break;
        }
        for(int i=0;i<m->sub_category_count;i++)
            printCategory(m->subCategory[i]);
    }while(secim!=0);
    return 0;
}
