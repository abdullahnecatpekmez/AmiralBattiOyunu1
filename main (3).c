#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define uz 13//max gemi uzunlugunu belirten sembolik sabit
#define boyut 24// matrisin max boyut degerini belirten sembolik sabit
//FONKSIYON PROTOTIPLERI
void atama(char [][boyut],int);//Bu fonksiyonlarin gorevleri kullanim sirasinda anlatilacaktir..
void yazdirma(char [][boyut],int);
int cift_olma_durumu(int);
void gemileriyazdirma(int [][boyut],int kenar);
int gemilerinyerlestirilmesi(int [][boyut],int i,int j,int uzunluk[],int u,int kenar,int,int);
int sonuc(char [][boyut],int [][boyut],int,int,int,int);
//MAIN FONKSIYONU
int main()
{
    srand(time(NULL));
    char sutun;
    char savasalani[boyut][boyut];//oyuncunun ekranda gordugu karakter tabanli matris
    int gemiyerlestir[boyut][boyut]= {0};//0 ve 1 lerden olusan uzerine gemilerin yerlestirildigi matris
    int uzunluk[uz]= {0};//gemilerin uzunluklarin tutuldugu dizi
    int ciftmi,u,i,j,hak,gemisay,kenar,dogrultu,yon,toplamuzunluk=0,dogru;
    printf("Savas alaninin buyuklugunu 3 ile 25 sayilari arasinda cift olarak giriniz--->");
    scanf("%d",&kenar);
    ciftmi=cift_olma_durumu(kenar);
    while ((kenar<3 || kenar>25)||(ciftmi==0))//kullanicinin girdigi kenar sayisini kontrol eden while dongusu...
    {
        printf("Bak iste hatali veri girisi yaptin!!Dikkatli ol..\nKenar uzunlugunu 3 ile 25 arasinda cift sayi olacak sekilde gir--->\n");
        scanf("%d",&kenar);
        ciftmi=cift_olma_durumu(kenar);
    }
    gemisay=kenar/2;//savas alanindaki gemilerin sayisi matrisin bir kenarinin yarisi kadardir.
    for (u=0; u<gemisay; u++)//kullanicidan gemi uzunluklarinin alindigi ve bunlarin bir diziye atandigi for dongusu...
    {
        printf("Gemilerin uzunluklari 2 ile %d arasinda olmalidir.\n",gemisay+1);
        printf("%d. geminin uzunlugunu giriniz--->",u+1);
        scanf("%d",&uzunluk[u]);
        while (uzunluk[u]<2 || uzunluk[u]>kenar/2+1)//gemilerin uzunluklarini kontrol eden dongu..
        {
            printf("Hatali veri girisi!Lutfen %d.geminin uzunlugunu belrtilen sinirlar dahilinde giriniz\n",u+1);
            scanf("%d",&uzunluk[u]);
        }
        toplamuzunluk+=uzunluk[u];
    }
    hak=kenar*kenar-toplamuzunluk;
    printf("Toplam atis yapma hakkiniz:%d\n",hak);
    printf("Oyun basliyor...\n\n");
    atama(savasalani,kenar);//atama fonksiyonu ile savasalanina O atiyoruz ve oyun alaninin ilk hali goruntuleniyor..
    yazdirma(savasalani,kenar);//savas alanini ekranda gösteren fonksiyonu yazdiriyoruz..
    u=0;
    do
    {
        i=rand()%kenar;//rand ile secilen satir..
        j=rand()%kenar;//rand ile secilen sutun..
        dogrultu=rand()%2;//yatay yada dikey olmasini rand ile belirleriz..
        yon=rand()%2;//sol,sag yada asagi yukari olmasini rand ile belirleriz..
        u=gemilerinyerlestirilmesi(gemiyerlestir,i,j,uzunluk,u,kenar,dogrultu,yon);
    }
    while (u<kenar/2);

    //gemileriyazdirma(gemiyerlestir,kenar);//yerlestirilen gemileri görmek icin kullanilir.YERLESTIRILEN GEMILERI GORMEK ICIN YORUM ISARETINI KALDIRINIZ.

    do
    {
        printf("\nAtis icin satiri giriniz\n");
        scanf("%d",&i);
        while (i<1||i>kenar)//oyuncudan alinan satirin kontrolunun yapildigi dongu..
        {
            printf("Satiri yanlis girdiniz. Lutfen 1-%d arasinda giriniz.\n",kenar);
            scanf("%d",&i);
        }
        i-=1;
        do//kullanicidan alinan satirin kontrolunun yapildigi dongu...
        {

            printf("Atis icin sutunu giriniz\n");
            scanf(" %c",&sutun);
            if (sutun>=65 && sutun<=65+kenar-1)//kullanici sutun degerini buyuk harf girerse
            {
                dogru=1;
                j=sutun-65;
            }
            else if (sutun>=97 && sutun<=97+kenar-1)//kullanici sutun degerini kcuk harf girerse
            {
                dogru=1;
                j=sutun-97;
            }
        }
        while (dogru!=1);

        gemisay=sonuc(savasalani,gemiyerlestir,i,j,kenar,gemisay);//
        printf("Kalan atis yapma hakkiniz:%d\n\n",hak-1);
        yazdirma(savasalani,kenar);//oyuncunun her atisindan sonra oyun alaninin ekranda görüntülenmesini sağlayan fonksiyon..
        hak--;//kullanici her atisi gerceklestirdikten sonra atis yapma hakkını bir azaltiriz.

        //gemileriyazdirma(gemiyerlestir,kenar);//EGER HER ATISTAN SONRA EKRANDA GEMILERIN BULUNDUGU YERLERI GORMEK ISTIYORSANIZ YORUM ISARETLERINI KALDIRIN!

        if (hak>=0 && gemisay==0)
        {
            printf("\nSupersiniz oyunu kazandiniz :)\n");
            break;
        }
    }
    while (hak>0);
    if (hak==0&&gemisay!=0)
    {
        printf("\nUzgunum,oyunu kaybettiniz! :(\n\nGemilerin bulundugu yerler 1 ile belirtilmistir\n");
        gemileriyazdirma(gemiyerlestir,kenar);//oyuncu oyunu kaybederse ekranda gemilerin bulundugu yerleri gosterir.
    }
    return 0;
}

int cift_olma_durumu(int kenar)//kullanicinin oyun alanini cift bir sayi girmesini kontrol eden fonksiyon...
{
    if (kenar%2==0)
        return 1;
    else
        return 0;
}

void yazdirma(char savasalani[][boyut],int kenar)//ekranda oyun alaninin goruntulenmesini saglayan fonksiyon..
{
    int j,l;
    printf("  ");
    for (l=65; l<65+kenar; l++)
        printf(" %c",l);
    printf("\n");
    for (l=0; l<kenar; l++)
    {
        printf("%2d",l+1);
        for (j=0; j<kenar; j++)
            printf(" %c",savasalani[l][j]);
        printf("\n");
    }
    printf("\n");
}

void gemileriyazdirma(int dizi[][boyut],int kenar)//oyuncu oyunu kaybederse ekranda gemilerin bulundugu yerleri gosteren fonksiyon..
{
    int j,l;
    printf("  ");
    for (l=65; l<65+kenar; l++)
        printf(" %c",l);
    printf("\n");
    for (l=0; l<kenar; l++)
    {
        printf("%2d",l+1);
        for (j=0; j<kenar; j++)
            printf(" %d",dizi[l][j]);
        printf("\n");
    }
    printf("\n");
}

void atama(char dizi[][boyut],int kenar)//oyun alanina en basta O harfinin atanmasini saglar..
{
    int i,j;
    for (i=0; i<kenar; i++)
    {
        for (j=0; j<kenar; j++)
            dizi[i][j]='O';
    }
}
int gemilerinyerlestirilmesi(int gemiyerlestir[][boyut],int i,int j,int uzunluk[],int u,int kenar,int dogrultu,int yon)//gemilerin rastgele oyun alanina yerlestirildigi fonksiyondur.
{
    int tamam=0,a,b,c;
    switch (dogrultu)
    {
    case 0://yatay konum için..
    {
        switch (yon)
        {
        case 0://sol taraf...
        {


            if (j-uzunluk[u]+1>=0)//geminin alanin içinde olup olmadigini kontrol ediyor..
            {
                for (b=i-1; b<=i+1; b++)//geminin yerlesecegi satiri bir ust satiri ve bi alt satiri kontrol ediyor.
                {
                    for (a=j; a>j-uzunluk[u]; a--)
                    {
                        if (gemiyerlestir[b][a]==1)
                        {
                            tamam=0;
                            break;
                        }
                        else tamam=1;
                    }
                    if (tamam==0)
                        break;
                }
                if (gemiyerlestir[i][j+1]==1||gemiyerlestir[i][j-uzunluk[u]]==1)//geminin yerlesecegi kismin uc noktalarini kontrol ediyor
                    tamam=0;
                if (tamam==1)
                {
                    for (c=j; c>=j-uzunluk[u]+1; c--)//eger kontrol edilen kisimlarda bir gemiye  yani 1 degerine rastlanmazsa gemi oraya yerlestirilir.
                        gemiyerlestir[i][c]=1;
                    u++;
                }
            }
        }
        break;
        case 1://sag taraf...
        {
            if (j+uzunluk[u]-1<kenar)//geminin alanin içinde olup olmadigini kontrol ediyor..
                for (b=i-1; b<=i+1; b++)
                {
                    for (a=j; a<j+uzunluk[u]; a++)
                    {
                        if (gemiyerlestir[b][a]==1)
                        {
                            tamam=0;
                            break;
                        }
                        else tamam=1;
                    }
                    if (tamam==0)
                        break;
                }
            if (gemiyerlestir[i][j-1]==1||gemiyerlestir[i][j+uzunluk[u]]==1)
                tamam=0;
            if (tamam==1)
            {
                for (c=j; c<=j+uzunluk[u]-1; c++)
                    gemiyerlestir[i][c]=1;
                u++;
            }
        }
        break;
        }
    }
    break;
    case 1://dikey konum için..
    {
        switch (yon)
        {
        case 0: //yukari taraf...
        {
            if (i-uzunluk[u]+1>=0)//geminin alanin içinde olup olmadigini kontrol ediyor..
            {
                for (b=j-1; b<=j+1; b++)
                {
                    for (a=i; a>i-uzunluk[u]; a--)
                    {
                        if (gemiyerlestir[a][b]==1)
                        {
                            tamam=0;
                            break;
                        }
                        else tamam=1;
                    }
                    if (tamam==0)
                        break;
                }
                if (gemiyerlestir[i+1][j]==1||gemiyerlestir[i-uzunluk[u]][j])
                    tamam=0;
                if (tamam==1)
                {
                    for (c=i; c>=i-uzunluk[u]+1; c--)
                        gemiyerlestir[c][j]=1;
                    u++;
                }
            }
        }
        break;
        case 1://asagi taraf...
        {
            if (i+uzunluk[u]-1<kenar)//geminin alanin içinde olup olmadigini kontrol ediyor..
                for (b=j-1; b<=j+1; b++)
                {
                    for (a=i; a<i+uzunluk[u]; a++)
                    {
                        if (gemiyerlestir[a][b]==1)
                        {
                            tamam=0;
                            break;
                        }
                        else tamam=1;
                    }
                    if (tamam==0)
                        break;
                }
            if (gemiyerlestir[i-1][j]==1||gemiyerlestir[i+uzunluk[u]][j]==1)
                tamam=0;
            if (tamam==1)
            {
                for (c=i; c<=i+uzunluk[u]-1; c++)
                    gemiyerlestir[c][j]=1;
                u++;
            }
        }
        }
        break;
    }
    break;
    }
    return u;
}

int sonuc(char savasalani[][boyut],int gemiyerlestir[][boyut],int i,int j,int kenar,int gemisay)//oyuncunun herhangi bir koordinati girdiğinde burada olan degisiklikler hakkinda kullaniciya bilgi veren fonksiyon..
{
    int ayni,m,sayac,baslangic,bitis,sayici,u,b;
    if (savasalani[i][j]!='O')
    {
        printf("\nBu degerleri daha onceden girdiniz!!!\n");
        ayni=1;
    }
    else ayni=0;
    if (gemiyerlestir[i][j]==1)
    {
        if (ayni!=1)
        {
            savasalani[i][j]='I';
            printf("Tebrikler, tam isabet!\n");
        }
        m=j;
        for (sayac=j; sayac>=0; sayac--) //yatay icin geminin baslangic ve bitis noktasini bulma..
        {
            if (gemiyerlestir[i][sayac]!=1)
                break;
        }
        baslangic=sayac+1;
        for (sayac=m; sayac<kenar; sayac++)
        {
            if (gemiyerlestir[i][sayac]!=1)
                break;
        }
        bitis=sayac-1;
        sayici=0;
        for (b=baslangic; b<=bitis; b++)
        {
            if (savasalani[i][b]=='I')
                sayici++;
            else
                break;
        }
        if (sayici==bitis-baslangic+1 && sayici>1)
        {
            printf("Tebrikler, bir gemiyi batirdiniz...\n");
            gemisay--;
            for (b=baslangic; b<=bitis; b++)
            {
                savasalani[i][b]='B';
            }
        }
        u=i;
        for (sayac=i; sayac>=0; sayac--) //dikey gemiler icin baslangic ve bitis noktalarini bulma...
        {
            if (gemiyerlestir[sayac][j]!=1)
                break;
        }
        baslangic=sayac+1;
        for (sayac=u; sayac<kenar; sayac++)
        {
            if (gemiyerlestir[sayac][j]!=1)
                break;
        }
        bitis=sayac-1;
        sayici=0;
        for (b=baslangic; b<=bitis; b++)
        {
            if (savasalani[b][j]=='I')
                sayici++;
            else
                break;
        }
        if (sayici==bitis-baslangic+1&&sayici>1)
        {
            printf("Tebrikler, bir gemiyi batirdiniz...\n");
            gemisay--;
            for (b=baslangic; b<=bitis; b++)
            {
                savasalani[b][j]='B';
            }
        }
    }
    else
    {
        if (ayni!=1)
        {
            savasalani[i][j]='K';
            printf("Uzgunum, karavana!\n");
        }
    }
    return gemisay;
}

