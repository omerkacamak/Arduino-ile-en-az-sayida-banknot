#include <LiquidCrystal.h>
#include <EEPROM.h>
#define Buton1 13
#define Buton2 A0
#define Buton3 A1
#define Buton4 A2
#define Buton5 A3
#define Bitis A4
#define Reset 7
#define Yesil 9
#define Kirmizi 8
LiquidCrystal lcd (12,11,5,4,3,2);
int btndrm1=0;
int btndrm2=0;
int btndrm3=0;
int btndrm4=0;
int btndrm5=0;
int bitisButon=0;
int resetButon=0;
int sayac=0;
int bes=20;
int on=20;
int yirmi=10;
int elli=30;
int yuz=5;
int hizmetID[4]={1,2,3,4};
String hizmetAD [4] ={"kopukleme","yikama","kurulama","cilalama"};
int kalanHizmetAdet[4]={30,50,100,20};
int hizmetFiyat [4]={15,10,5,50};
int toplamTutar=0;  // makineye atilan tutar!
int hizmetTutari=0;

int besAdet=0;
int onAdet =0;
int yirmiAdet=0;
int elliAdet=0;
int yuzAdet=0;
                                                          // EEPROMDA 0,1,2,3 adresleri hizmetler için tutuldu.    4 5 6 7 8  adresleri ise 5 tl 10 tl 20tl için tutuldu!
int hizmeteGecis=0;


int paraUstuDevam=0;  /// 1 olursa devam   2 olursa PARA SIKIŞMA !


int kopTik=0;
int yikTik=0;
int kurTik=0;  int cilTik=0;

int tmpbes=0;  int tmpon=0; int tmpyirmi=0; int tmpelli=0; int tmpyuz=0;
int tmpkop=0; int tmpyik=0; int tmpkur=0; int tmpcil=0;

int kyuz=0, kelli=0, kyirmi=0, kon=0, kbes=0; int paraustu=0;
void setup() {
 
 Serial.begin(9600);
 randomSeed(analogRead(A5));
 lcd.begin(16,2);
 pinMode(Buton1,INPUT);
 pinMode(Buton2,INPUT);
 pinMode(Buton3,INPUT);
 pinMode(Buton4,INPUT);
 pinMode(Buton5,INPUT);
 pinMode(Bitis,INPUT);
 pinMode(Reset,INPUT);
 pinMode(Yesil,OUTPUT);
  pinMode(Kirmizi,OUTPUT);
 

/*EEPROM.write(0,30);
EEPROM.write(1,50);
EEPROM.write(2,100);
EEPROM.write(3,20);                        

EEPROM.write(4,20);
EEPROM.write(5,20);
EEPROM.write(6,10);                                        // BU KISIMDAN MAKİNEYİ EN BAŞTAKİ DEĞERLERE DÖNDÜREBİLİRSİN!             ////////////////////////////////////
EEPROM.write(7,30);
EEPROM.write(8,5);*/
//EEPROM.write(8,0);
lcd.print("PARA AT");
 bes=EEPROM.read(4);
 on=EEPROM.read(5);
 yirmi=EEPROM.read(6);
 elli=EEPROM.read(7);
 yuz=EEPROM.read(8);

tmpbes=bes;
tmpon=on;
tmpyirmi=yirmi;
tmpelli=elli;
tmpyuz=yuz;


 
for(int i=0; i<4;i++)
{
  kalanHizmetAdet[i]= EEPROM.read(i); // hizmetler eeproma kaydediliyor
}

tmpkop=kalanHizmetAdet[0];     tmpyik=kalanHizmetAdet[1];    tmpkur=kalanHizmetAdet[2];   tmpcil=kalanHizmetAdet[3]; // hizmet adetleri geçici olarak kaydediliyor. // resetleme işlemini yapabilmek için ilk değerleri tmp olarak aldık.
 
 ekran();
 

}

void loop() {

 //Serial.println(EEPROM.read(1));
  btndrm1=digitalRead(Buton1);
  btndrm2=digitalRead(Buton2);
  btndrm3=digitalRead(Buton3);
  btndrm4=digitalRead(Buton4);
  btndrm5=digitalRead(Buton5);
  bitisButon=digitalRead(Bitis);
  resetButon=digitalRead(Reset);
 
 /* EEPROM.write(0,bes);
  EEPROM.write(1,on);
  EEPROM.write(2,yirmi);      // makine içindeki para hafızada !
  EEPROM.write(3,elli);
  EEPROM.write(4,yuz);*/
 resetButonFonk();
 paraUstu();
if(hizmeteGecis==0)
{
  butonBasim();
}
else if(hizmeteGecis==1)
{
  hizmetButonBasim();
}


if(hizmetTutari>toplamTutar)
{
     lcd.setCursor(0,0);  
    lcd.clear();
    lcd.print("O kadar para");
    lcd.setCursor(0,1);
    lcd.print("Atmadiniz!");
}


  
 if(bitisButon==1)
 {
  if(  hizmeteGecis==1)
  {
    lcd.clear();
    lcd.print("İŞLEM BİTTİ");
    rastgeleSayi();
  }
  
  else if(  hizmeteGecis==0)
 {
hizmeteGecis=1;
  lcd.clear();
  lcd.print("Hizmet secimi yap."); 
  }
 
  
 }
  while(bitisButon==1)
  {
    delay(10);
    bitisButon=digitalRead(Bitis);
  }
  

}


void ekran()
{
 Serial.println(" ");

// Serial.print("BES"); Serial.print(" "); Serial.print("ON"); Serial.print(" "); Serial.print("YIR"); Serial.print(" "); Serial.print("ELLI");Serial.print(" ");  Serial.print("YUZ"); Serial.println(" ");
 Serial.print(EEPROM.read(4));Serial.print("  "); Serial.print(EEPROM.read(5)); Serial.print("  ");   Serial.print(EEPROM.read(6));Serial.print("  "); Serial.print(EEPROM.read(7)); Serial.print("  ");   Serial.print(EEPROM.read(8)); Serial.print("\t");
  Serial.println("  ");
 
  for(int i=0; i<4 ;i++)
  {
      Serial.print(hizmetID[i]); Serial.print(","); Serial.print(hizmetAD[i]); Serial.print(","); Serial.print(EEPROM.read(i)); Serial.print(","); Serial.print( hizmetFiyat[i]); Serial.print(" "); Serial.print("TL"); 
      Serial.println(" ");
  }
  
  
}



void resetButonFonk()
{
  
  if(resetButon==1)
  {
   digitalWrite(Kirmizi,LOW);
   digitalWrite(Yesil,LOW);
    lcd.clear();
    lcd.print("Para Atin");
    hizmeteGecis=0;
    toplamTutar=0; // yatırılan para
    hizmetTutari=0; // hizmelerin bedeli
    
 /*   bes-=besAdet;
    EEPROM.write(4,bes);*/
EEPROM.write(4,tmpbes); // geçici değişkeni yani en baştaki değeri atadık!
bes=tmpbes;


EEPROM.write(5,tmpon); // geçici değişkeni yani en baştaki değeri atadık!
on=tmpon;                                                  


EEPROM.write(6,tmpyirmi); // geçici değişkeni yani en baştaki değeri atadık!
yirmi=tmpyirmi;


EEPROM.write(7,tmpelli); // geçici değişkeni yani en baştaki değeri atadık!
elli=tmpelli;


EEPROM.write(8,tmpyuz); // geçici değişkeni yani en baştaki değeri atadık!
yuz=tmpyuz;
   




EEPROM.write(0,tmpkop);
kalanHizmetAdet[0]=tmpkop;                               

EEPROM.write(1,tmpyik);
kalanHizmetAdet[1]=tmpyik;


EEPROM.write(2,tmpkur);
kalanHizmetAdet[2]=tmpkur;


EEPROM.write(3,tmpcil);
kalanHizmetAdet[3]=tmpcil;
  
    


   ekran();
    
    
    
  }

   while(resetButon==1)
  {
    delay(10);
    resetButon=digitalRead(Reset);
  }
}

void hizmetButonBasim() // para atma işleminden hemen sonra hizmet seçimi!
{
   if(btndrm1==1) // köpükleme
  {
 if(kalanHizmetAdet[0]!=0)
 {
  if(hizmetTutari<=toplamTutar)
  {
  
  kopTik++;
lcd.clear();
kalanHizmetAdet[0]--;
hizmetTutari+=hizmetFiyat[0];
EEPROM.write(0,kalanHizmetAdet[0]);
 lcd.print("Toplam "); lcd.print(hizmetTutari); lcd.print(" "); lcd.print("TL");
 lcd.setCursor(0,1);
 lcd.print("Yatirilan  ");  lcd.print(toplamTutar); lcd.print(" "); lcd.print("TL");
   
    ekran();
    Serial.println(" \n");
   
  }

  else 
  {
    lcd.clear();
    lcd.print("O kadar para");
    lcd.setCursor(0,1);
    lcd.print("Atmadiniz!");
  }
  }

  else if(kalanHizmetAdet[0]==0)
  {
    lcd.clear();
    lcd.print("Bu hizmet");
    lcd.setCursor(0,1);
    lcd.print("Kalmadi");
  }
  }
  while(btndrm1==1)
  {
    delay(10);
    btndrm1=digitalRead(Buton1);
  }



   if(btndrm2==1) // Yikama!
  {
 if(kalanHizmetAdet[1]!=0)
  {  
  yikTik++;
lcd.clear();
kalanHizmetAdet[1]--;
hizmetTutari+=hizmetFiyat[1];
EEPROM.write(1,kalanHizmetAdet[1]);
  lcd.print("Toplam "); lcd.print(hizmetTutari); lcd.print(" "); lcd.print("TL");
 lcd.setCursor(0,1);
 lcd.print("Yatirilan  ");  lcd.print(toplamTutar); lcd.print(" "); lcd.print("TL");
   
    ekran();
    Serial.println(" \n");
   
  }
  // buraya
    else if(kalanHizmetAdet[1]==0)
  {
    lcd.clear();
    lcd.print("Bu hizmet");
    lcd.setCursor(0,1);
    lcd.print("Kalmadi");
  }
  }
  while(btndrm2==1) //
  {
    delay(10);
    btndrm2=digitalRead(Buton2);
  }
  //******************

   if(btndrm3==1) // kurulama
  {
   if(kalanHizmetAdet[2]!=0)
  {
  kurTik++;
lcd.clear();
kalanHizmetAdet[2]--;
hizmetTutari+=hizmetFiyat[2];
EEPROM.write(2,kalanHizmetAdet[2]);
lcd.print("Toplam "); lcd.print(hizmetTutari); lcd.print(" "); lcd.print("TL");
 lcd.setCursor(0,1);
 lcd.print("Yatirilan  ");  lcd.print(toplamTutar); lcd.print(" "); lcd.print("TL");
   
    ekran();
    Serial.println(" \n");
   
  }

     else if(kalanHizmetAdet[2]==0)
  {
    lcd.clear();
    lcd.print("Bu hizmet");
    lcd.setCursor(0,1);
    lcd.print("Kalmadi");
  }
  }
  while(btndrm3==1)
  {
    delay(10);
    btndrm3=digitalRead(Buton3);
  }


  //********************------

  
   if(btndrm4==1) // cilalama
  {

if(kalanHizmetAdet[3]!=0)
  {  
  cilTik++;
lcd.clear();
kalanHizmetAdet[3]--;
hizmetTutari+=hizmetFiyat[3];
EEPROM.write(3,kalanHizmetAdet[3]);
  lcd.print("Toplam "); lcd.print(hizmetTutari); lcd.print(" "); lcd.print("TL");
 lcd.setCursor(0,1);
 lcd.print("Yatirilan  ");  lcd.print(toplamTutar); lcd.print(" "); lcd.print("TL");
   
    ekran();
    Serial.println(" \n");
   
  } 

     else if(kalanHizmetAdet[3]==0)
  {
    lcd.clear();
    lcd.print("Bu hizmet");
    lcd.setCursor(0,1);
    lcd.print("Kalmadi");
  }
  }
  while(btndrm4==1)
  {
    delay(10);
    btndrm4=digitalRead(Buton4);
  }
  
}

// ************--*************
void butonBasim() // PARA ATIMI !!
{
  if(btndrm1==1)
  {
lcd.clear();
    besAdet++;
  //  bes--;
  bes++;
     EEPROM.write(4,bes);
//    toplamTutar+= besAdet*5;
toplamTutar+=5;
lcd.print(toplamTutar);   lcd.print("  TL attiniz.") ;
    //Serial.println(sayac);
   ekran();
    Serial.println(" \n");
   
    
  }
  while(btndrm1==1)
  {
    delay(10);
    btndrm1=digitalRead(Buton1);
  }
//**************************
if(btndrm2==1)
  {
 
lcd.clear();
    onAdet++;
   // on--;
   on++;
     EEPROM.write(5,on);
   // toplamTutar+= onAdet*10;
   toplamTutar+=10;
lcd.print(toplamTutar);   lcd.print("  TL attiniz.") ;
    //Serial.println(sayac);
    ekran();
    Serial.println(" \n");
   
    
  }
  while(btndrm2==1)
  {
    delay(10);
    btndrm2=digitalRead(Buton2);
  }

  // *******************************

  if(btndrm3==1)
  {
   
lcd.clear();
    yirmiAdet++;
  //  yirmi--;
  yirmi++;
     EEPROM.write(6,yirmi);
  //  toplamTutar+= yirmiAdet*20;
  toplamTutar+=20;
lcd.print(toplamTutar);   lcd.print("  TL attiniz.") ;
    //Serial.println(sayac);
    ekran();
    Serial.println(" \n");
   
    
  }
  while(btndrm3==1)
  {
    delay(10);
    btndrm3=digitalRead(Buton3);
  }

  //***************----*********

  if(btndrm4==1)
  {
  
lcd.clear();
    elliAdet++;
   // elli--;
   elli++;
     EEPROM.write(7,elli);
  //  toplamTutar+= elliAdet*50;
  toplamTutar+=50;
lcd.print(toplamTutar);   lcd.print("  TL attiniz.") ;
    //Serial.println(sayac);
    ekran();
    Serial.println(" \n");
   
    
  }
  while(btndrm4==1)
  {
    delay(10);
    btndrm4=digitalRead(Buton4);
  }
  
//**-*-*-*-*-*-*-*-*-*

if(btndrm5==1)
  {
   // Serial.print("RADAMEEEEL");
lcd.clear();
    yuzAdet++;
 //   yuz--;
 yuz++;
     EEPROM.write(8,yuz);
 //   toplamTutar+= yuzAdet*100;
 toplamTutar+=100;
lcd.print(toplamTutar);   lcd.print("  TL attiniz.") ;
    //Serial.println(sayac);
    ekran();
    Serial.println(" \n");
   
    
  }
  while(btndrm5==1)
  {
    delay(10);
    btndrm5=digitalRead(Buton5);
  }
  
}




void rastgeleSayi()
{
  int rastgele=random(1,5);

  if(rastgele==2)
  {
    lcd.clear();
    lcd.print("Para sıkıstı");
    digitalWrite(Kirmizi,HIGH);
    paraUstuDevam=2;
    
  }
else if(rastgele==1)
  {
    lcd.clear();
    lcd.print(rastgele);
    digitalWrite(Yesil,HIGH);
    paraUstuDevam=1;
    
  }


  else if(rastgele==3)
  {
    lcd.clear();
    lcd.print(rastgele);
    digitalWrite(Yesil,HIGH);
    paraUstuDevam=1;
    
  }

else if(rastgele==4)
  {
    lcd.clear();
    lcd.print(rastgele);
    digitalWrite(Yesil,HIGH);
    paraUstuDevam=1;
    
  }
  
}


void paraUstu()
{
  
  paraustu=toplamTutar -hizmetTutari;
  if(paraUstuDevam==1)
  {
    // Yesil isik yandı devam para ustune!


if(yuz!=0)
{
kyuz= paraustu/100;
paraustu-=100*kyuz;
yuz-=kyuz;
 EEPROM.write(8,yuz);
}

if(elli!=0)
{
kelli=paraustu/50;
paraustu-=50*kelli;
elli-=kelli;
EEPROM.write(7,elli);
}

if(yirmi!=0)
{
kyirmi=paraustu/20;
paraustu-=20*kyirmi;
yirmi-=kyirmi;
EEPROM.write(6,yirmi);
}

if(on!=0)
{
kon=paraustu/10;
paraustu-=10*kon;
on-=kon;
 EEPROM.write(5,on);
}

if(bes!=0)
{
kbes=paraustu/5;
paraustu-=5*kbes;
bes-=kbes;
  EEPROM.write(4,bes);
}
int ParaUst = toplamTutar -hizmetTutari;
    
    lcd.clear();
    lcd.print("Para Ustunuz:");
    lcd.setCursor(0,1);
    lcd.print(ParaUst); lcd.print(" "); lcd.print("TL");
    ekran();
    Serial.println("  "); Serial.println("  ");  Serial.print(kyuz); Serial.print(" ");Serial.print("yuzluk");Serial.print(" --- "); Serial.print(kelli); Serial.print(" ");Serial.print("tane ellilik");Serial.print(" --- ");
 
    Serial.print(kyirmi); Serial.print(" ");Serial.print("tane yirmilik");Serial.print(" --- ");
    Serial.print(kon); Serial.print(" ");Serial.print("tane onluk");Serial.print(" --- ");
    Serial.print(kbes); Serial.print(" ");Serial.print("tane beslik");Serial.print(" ");
    Serial.println(" "); Serial.println("olarak para ustu verildi!"); 
      
    if(paraustu!=0)
    {
      lcd.clear();
      lcd.print("KASADA YETERLI");
      lcd.setCursor(0,1);
      lcd.print("BANKNOT YOK");
    }
    paraUstuDevam=0;
  }
  else if(paraUstuDevam==2)
  {
     lcd.clear();
    lcd.print("Para sikisti:");
    paraUstuDevam=0;
  }
}
