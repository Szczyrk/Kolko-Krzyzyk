
#include <vcl.h>
#include <math.h>
#pragma hdrstop
#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
int tmp,a;
char ruch;

class Pole
{
public:
TImage *btn;
char kto;
 void __fastcall Klik(TObject *sender);
};

 TGroupBox* Group = new TGroupBox(Form1);
Pole ***Obiekt;

void Reset();

int Wazona(Pole ***Obiekt, char spr, char blok)
{
 int k=0,l=0;
for (int x = 0 ; x < a ; x++)
              {
                for (int y = 0 ; y < a ; y++)
                 {
                 if(Obiekt[x][y]->kto==spr)k++;
                 if(Obiekt[x][y]->kto==blok){k=1;break;}
                 }

                l+=k*k;
                k=0;
              }

         for (int y = 0 ; y < a ; y++)
             {
                for (int x = 0 ; x < a ; x++)
                 {
                 if(Obiekt[x][y]->kto==spr)k++;
                 if(Obiekt[x][y]->kto==blok){k=1;break;}
                 }

                l+=k*k;
                k=0;
             }

       for(int x=0,y=0;x<a&&y<a;x++,y++)
               {
                 if(Obiekt[x][y]->kto==spr)k++;
                 if(Obiekt[x][y]->kto==blok){k=1;break;}
               }

                l+=k*k;
                k=0;

           for (int x = a-1,y=0 ; x > 0;x--,y++)
                {
                 if(Obiekt[x][y]->kto==spr)k++;
                 if(Obiekt[x][y]->kto==blok){k=1;break;}
                }

               l+=k*k;
        return l;
}
bool Sprawdz(Pole ***Obiekt, char spr)
{
        int k=0;
         for (int x = 0 ; x < a ; x++)
              {
                for (int y = 0 ; y < a ; y++)
                 {
                 if(Obiekt[x][y]->kto==spr)k++;
                 }

                if(k==a)return true;
                k=0;
              }

         for (int y = 0 ; y < a ; y++)
             {
                for (int x = 0 ; x < a ; x++)
                 {
                 if(Obiekt[x][y]->kto==spr)k++;
                 }

                if(k==a)return true;
                k=0;
             }

       for(int x=0,y=0;x<a&&y<a;x++,y++)
               {
                 if(Obiekt[x][y]->kto==spr)k++;
               }
                if(k==a)return true;
                k=0;

           for (int x = a-1,y=0 ;x > 0,y<a;x--,y++)
                {
                 if(Obiekt[x][y]->kto==spr)k++;
                }
               if(k==a)return true;

        return false;
}


int Krok_o(Pole ***Obiekt)
{
        bool spr=false;
        int pkt,pkt1=0;
           for (int y = 0 ; y < a ; y++)
                {
                for (int x = 0 ; x < a ; x++)
                 {
                       if(Obiekt[x][y]->kto =='n')
                       {

                             Obiekt[x][y]->kto ='o';
                             spr=Sprawdz(Obiekt,'o');
                             if(spr==true)
                             {
                                 Obiekt[x][y]->kto='n';
                                 return 100;
                             }
                                Obiekt[x][y]->kto ='x';
                             spr=Sprawdz(Obiekt,'x');
                             if(spr==true)
                             {
                                 Obiekt[x][y]->kto='n';
                                 return 50;
                             }
                             Obiekt[x][y]->kto='x';
                               pkt=Wazona(Obiekt,'o','x');
                               if(pkt>pkt1)
                               {
                               pkt1=pkt;
                               }
                               Obiekt[x][y]->kto='n';

                       }
                 }
                }
               return pkt1;
}


void Krok_x(Pole ***Obiekt)
{
        bool spr=false;
        int pkt,pkt1=0,pkt2=0, x1=0,y1=0;
           for (int y = 0 ; y < a ; y++)
                {
                for (int x = 0 ; x < a ; x++)
                 {
                       if(Obiekt[x][y]->kto =='n')
                       {
                                Obiekt[x][y]->kto ='x';
                             spr=Sprawdz(Obiekt,'x');
                             if(spr==true)
                             {
                             ShowMessage("true");
                                 Obiekt[x][y]->btn->Picture->LoadFromFile("img/x.bmp");
                                 ruch='o';
                                 Form1->tura->Picture->LoadFromFile("img/osmall.bmp");
                                 Obiekt[x][y]->btn->Enabled=false;
                                 return;
                             }
                             Obiekt[x][y]->kto ='o';
                             spr=Sprawdz(Obiekt,'o');
                             if(spr==true)
                             {
                                 Obiekt[x][y]->btn->Picture->LoadFromFile("img/x.bmp");
                                 ruch='o';
                                 Obiekt[x][y]->kto='x';
                                 Form1->tura->Picture->LoadFromFile("img/osmall.bmp");
                                 Obiekt[x][y]->btn->Enabled=false;
                                 return;
                             }
                             Obiekt[x][y]->kto='x';
                               pkt=Wazona(Obiekt,'x','o');
                               if(pkt>pkt1)
                               {
                               pkt1=pkt;
                               pkt=Krok_o(Obiekt);
                                  if(pkt>pkt2)
                                 {
                                 pkt2=pkt;
                                  x1=x;y1=y;
                                 }
                               }
                               Obiekt[x][y]->kto='n';

                       }
                 }
                }
             Obiekt[x1][y1]->btn->Picture->LoadFromFile("img/x.bmp");
                 ruch='o';
                Obiekt[x1][y1]->kto='x';
               Form1->tura->Picture->LoadFromFile("img/osmall.bmp");
               Obiekt[x1][y1]->btn->Enabled=false;
}

//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
}
void __fastcall Tura()
{
        srand(time(NULL));
        Form1->tura->Visible = true;
   tmp =rand()%2;
   if(tmp==1)
   {
   ruch='o';
   Form1->tura->Picture->LoadFromFile("img/osmall.bmp");
   } else
   {
         Obiekt[a/2][a/2]->btn->Picture->LoadFromFile("img/x.bmp");
         ruch='o';
         Obiekt[a/2][a/2]->kto='x';
         Form1->tura->Picture->LoadFromFile("img/osmall.bmp");
         Obiekt[a/2][a/2]->btn->Enabled = false;
   }
}

void Sprawc_czy_koniec()
{
        int i=0;
      for (int y = 0 ; y < a ; y++)
        {
         for (int x = 0 ; x < a ; x++)
                 {
                 if(Obiekt[x][y]->kto=='n')
                 i++;
                 }
        }
        if(i==0)
                 {
                ShowMessage("Remis");
                Reset();
                }
}
  void __fastcall Pole::Klik(TObject *sender)
  {
      bool spr;

  if(btn->Enabled==true)
   {
      if(ruch=='o')
      {
         btn->Picture->LoadFromFile("img/o.bmp");
         ruch='x';
         kto='o';
         Form1->tura->Picture->LoadFromFile("img/xsmall.bmp");
      }
      else
      {
       btn->Picture->LoadFromFile("img/x.bmp");
       ruch='o';
       kto='x';
       Form1->tura->Picture->LoadFromFile("img/osmall.bmp");
      }
     btn->Enabled=false;

            spr=Sprawdz(Obiekt,'o');
         if(spr==true)
         {
                ShowMessage("Wygra³o O");
                Reset();
         }
                 Krok_x(Obiekt);
         spr=Sprawdz(Obiekt,'x');
         if(spr==true)
         {
                ShowMessage("Wygra³ X");
                Reset();
         }

         Sprawc_czy_koniec();
   }
  }
void __fastcall TForm1::create()
{
int i =0;



Obiekt = new Pole**[a];
for (int i = 0; i<a; i++)
     Obiekt[i] = new Pole*[a];



         for (int y = 0 ; y < a ; y++)
        {
         for (int x = 0 ; x < a ; x++)
                 {
                 Obiekt[x][y] = new Pole;
                 Obiekt[x][y]->btn = new TImage(this);
                 Obiekt[x][y]->btn->Parent = this;
                 Obiekt[x][y]->btn->Name = (String)"Pole"+x+y;
                 Obiekt[x][y]->btn->Left = 240 + (x * 100);
                 Obiekt[x][y]->btn->Top = 100 + (y * 100);
                 Obiekt[x][y]->btn->Height = 100;
                 Obiekt[x][y]->btn->Width = 100;
                 Obiekt[x][y]->btn->Tag = i++;
                 Obiekt[x][y]->btn->Enabled = true;
                 Obiekt[x][y]->btn->AutoSize = true;
                 Obiekt[x][y]->btn->Center = true;
                 Obiekt[x][y]->kto = 'n';
                 Obiekt[x][y]->btn->Picture->LoadFromFile("img/nic.bmp");
                 Obiekt[x][y]->btn->OnClick =Obiekt[x][y]->Klik;
                 }
        }


}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button1Click(TObject *Sender)
{
Rozmiar -> Visible = false;
Label2 -> Visible = false;
Button1 -> Visible = false;
Button2 -> Visible = true;
a=this->Rozmiar->Text.ToInt();
create();
Tura();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button2Click(TObject *Sender)
{
        Reset();
}
//---------------------------------------------------------------------------
 void Reset()
{
    for (int y = 0 ; y < a ; y++)
        {
         for (int x = 0 ; x < a ; x++)
                 {
                 Obiekt[x][y]->kto = 'n';
                 Obiekt[x][y]->btn->Picture->LoadFromFile("img/nic.bmp");
                 Obiekt[x][y]->btn->Enabled = true;
                 }
        }
        Tura();
}

