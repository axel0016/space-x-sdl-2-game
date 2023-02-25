#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <windows.h>
#include <unistd.h>
#include <string.h>
/***************VAR**********************/

int ygscreen = 70;
int taille_matrice = 6;
int XRect = 471, YRect = 140, size_bloc = 70, xrect1=145,yrect1=145,xrect2=795,yrect2=140;
int matrice[7][7] ;
int g=0;
int GG,b,ch=0,d,yu;
int  score=0,scos,tp=0,savop;
int ab[36],tr[36],score1[5],save[36],savep[36],bot[36],bot2[36],n1=1,n2=1,sybon;
int grid[36];
time_t debut,finp,debutp,dt;
double difference,difference1 ;
char prenom[50]="";
int i=0;
int l;
int write0=0;
typedef struct {
char nom[50];
int score;
int jj;
int mois;
int ans;
}joueur;

/*************************************/


void tri (FILE* F,int z){
  joueur tab[6],tab2[6];
  joueur x;
  int n=0,i=0;

  if(z==1){
    F=fopen("D:/playerscore.txt","r");
    fscanf(F,"%50s : %d",tab[i].nom,&tab[i].score);

    while (!feof(F)){
      n++;
      i++;
     fscanf(F,"%s : %03d",tab[i].nom,&tab[i].score);

  }
    fclose(F);



   for (i=0;i<n-1;i++){
    for(int j=i+1;j<n;j++){
        if(tab[i].score>tab[j].score){
            x=tab[i];
            tab[i]=tab[j];
            tab[j]=x;
        }
    }
   }



   for (i=0;i<n;i++){
    printf("%s : %03d\n",tab[i].nom,tab[i].score);
   }
   if(n>5){
    n=5;
   }
    F=fopen("D:/playerscore.txt","w");
    for (i=0;i<n;i++){
        fprintf(F,"%s : %03d",tab[i].nom,tab[i].score);
        fputc('\n',F);
   }
    fclose(F);

  }
  if(z==2){
    F=fopen("D:/playervscpuscore.txt","r");
    fscanf(F,"%s : %03d",tab2[i].nom,&tab2[i].score);

    while (!feof(F)){
      n++;
      i++;
     fscanf(F,"%s : %03d",tab2[i].nom,&tab2[i].score);

  }
    fclose(F);



   for (i=0;i<n-1;i++){
    for(int j=i+1;j<n;j++){
          if(tab[i].score<tab[j].score){
            x=tab[i];
            tab[i]=tab[j];
            tab[j]=x;
        }
           }
   }

   for (i=0;i<n;i++){
    printf("%s : %03d\n",tab2[i].nom,tab2[i].score);
   }
   if(n>5){
    n=5;
   }
    F=fopen("D:/playervscpuscore.txt","w");
    for (i=0;i<n;i++){
        fprintf(F,"%s : %03d",tab2[i].nom,tab2[i].score);
        fputc('\n',F);
   }
    fclose(F);

  }

}
int fiche(char* nom,int score,int n)
{
    FILE* F;

    if(n==1){
    F=fopen("D:/playerscore.txt","a+");
    fprintf(F,"%s : %03d",nom,score);
    fputc('\n',F);
    fclose(F);
    tri(F,n);
    }
    if(n==2){
    F=fopen("D:/playervscpuscore.txt","a+");
    fprintf(F,"%s : %03d",nom,score);
    fputc('\n',F);
    fclose(F);
    tri(F,n);
    fclose(F);
    }

    return 0;
}



/**********************************/
void drawInfos(SDL_Renderer *render,int s,int c,int p){

     time_t fin ;


     fin=time(NULL) ;


     difference = difftime(fin, debut) ;
     if(p==1){
        if((c==0)){
        difference=0;
        difference=difference+tp-scos;
                   }
        else{
        difference=0;
        difference+=tp;}
     }
     if((b>1)&&(p==0)){
         if((c==0)){

        difference=difftime(fin,debutp)+tp-scos;
                   }
        if((c==1)||(savop==1)){

        difference=difftime(fin,debutp)+tp ;


        }

     }
          if((s==1)&&(c==0)){

                difference+=scos;
                   }

    char chaine[40] = "";
    TTF_Font* font = TTF_OpenFont("abnes.ttf",10);
    SDL_Color color = {255,255,255,255};
    sprintf(chaine,"| score : %.0f | temps : %.0f |",(difference/3),difference);
    SDL_Surface *text = TTF_RenderText_Solid(font,chaine,color);
    SDL_Texture *text_texture = SDL_CreateTextureFromSurface(render,text);
    SDL_FreeSurface(text);
    SDL_Rect rect_text = {536,29,300,35};
    SDL_RenderCopy(render,text_texture,NULL,&rect_text);
    TTF_CloseFont(font);

}



void initialize_matrice(int matrice[7][7]){
{
    srand(time(NULL));
    int num[49], i,l,m;
    for (i=0; i<49; i++){
        num[i]=0;
    }
    for(i=0; i<36; i++){
        int j= i / 6;
        grid[i]= (rand() % 2) + 1; /* soit 1 soit 2 la valeur*/
        if (grid[i] == 1){
           int k = i+j;
           num[k]= num[k] + 1;
           j= j + i + 8;
           num[j]= num[j] + 1;
        }
        else if (grid[i] ==2){
            int k = i+j+1;
           num[k]= num[k] + 1;
           j= j + i + 7;
           num[j]= num[j] + 1;
        }
    }
    i=0;
    for (m=0; m<7; m++){
        for(l=0; l<7; l++){
            matrice[m][l]=num[i];
            i++;
        }
    }
    for (m=0; m<7; m++){
        for(l=0; l<7; l++){
    printf("%4d",matrice[m][l]);
        }printf("\n");
    }
}

}



void drawRect(SDL_Renderer *window,int x,int y,int w,int h,int r,int g,int b,int a){
    SDL_Rect rect = {x,y,w,h};
    SDL_SetRenderDrawColor(window,r,g,b,a);
    SDL_RenderFillRect(window,&rect);
}


bool verefier(int x){
    if(x==0){

    int m;
    GG=0;
for (m=0; m<36; m++){
    if(grid[m]==tr[m])
       {
         GG++;
       }
}
if (GG>35){
    printf(" bsa7tkkkkkkkkkk and good game and finly bye ");
    return true;
}
else return false;
}
if(x==1){
        FILE* F2;
    F2=fopen("C:/soul.bin","rb");
            for(int i=0;i<36;i++){
            fread(&grid[i],sizeof(int),1,F2);
        }
        fclose(F2);
        int m;
    GG=0;
for (m=0; m<36; m++){
    if(grid[m]==tr[m])
       {
         GG++;
       }
}
if (GG>35){
    printf(" bsa7tkkkkkkkkkk and good game and finly bye ");
    return true;
}

else {return false;}

}
else return false;

}



void drawMap( SDL_Renderer *window,int x, int y,int z){

int i,j,l=0,u=0;char number[50] = "";
    for( i= 0; i < taille_matrice; i++){
    for( j = 0; j < taille_matrice; j++){
            SDL_Rect rect = {x + l + i*size_bloc,y +u + j*size_bloc + ygscreen,size_bloc,size_bloc};
            SDL_SetRenderDrawColor(window,255,255,255,255);
            SDL_RenderFillRect(window,&rect);
            SDL_SetRenderDrawColor(window,0,0,0,255);
            SDL_RenderDrawRect(window,&rect);

    }
    }

     if(z==0){

    TTF_Font* font = TTF_OpenFont("arial.ttf",50);
    SDL_Color color = {26,56,217,255};
    for( i = 0; i < 7; i++){
    for( j = 0; j < 7; j++){
            sprintf(number,"%d",matrice[j][i]);
            SDL_Surface *text = TTF_RenderText_Solid(font,number,color);
            SDL_Texture *text_texture = SDL_CreateTextureFromSurface(window,text);
            SDL_FreeSurface(text);
            SDL_Rect rect_text = {x + i*size_bloc - 12,y + j*size_bloc + ygscreen-15,25,35};
            SDL_RenderCopy(window,text_texture,NULL,&rect_text);
    }}}

    else{

        FILE* F2;
    F2=fopen("C:/mat.bin","rb");

    for (int i=0;i<7;i++){
        for(int j=0;j<7;j++){
            fread(&matrice[i][j],sizeof(int),1,F2);
        }
    }
    fclose(F2);


    TTF_Font* font = TTF_OpenFont("arial.ttf",50);
    SDL_Color color = {26,56,217,255};
    for( i = 0; i < 7; i++){
    for( j = 0; j < 7; j++){
            sprintf(number,"%d",matrice[j][i]);
            SDL_Surface *text = TTF_RenderText_Solid(font,number,color);
            SDL_Texture *text_texture = SDL_CreateTextureFromSurface(window,text);
            SDL_FreeSurface(text);
            SDL_Rect rect_text = {x + i*size_bloc - 12,y + j*size_bloc + ygscreen-15,25,35};
            SDL_RenderCopy(window,text_texture,NULL,&rect_text);
    }}


TTF_CloseFont(font);
    }


}




void drawLine(SDL_Renderer *window, int x,int y){
if(((x>471)&&(x<891)&&(y>209)&&(y<625))){
int i = (x - XRect) / size_bloc , j = (y - YRect - ygscreen) / size_bloc;

SDL_SetRenderDrawColor(window,0,0,0,255);
if ((ab[i+j*6]%3)==0){
SDL_RenderDrawLine(window,i*size_bloc + XRect , j*size_bloc + YRect + ygscreen,(i+1)*size_bloc + XRect ,(j+1)*size_bloc + YRect + ygscreen);
}
if ((ab[i+j*6]%3)==1){
SDL_SetRenderDrawColor(window,255,255,255,255);
SDL_RenderDrawLine(window,i*size_bloc + XRect , j*size_bloc + YRect + ygscreen,(i+1)*size_bloc + XRect ,(j+1)*size_bloc + YRect + ygscreen);
SDL_SetRenderDrawColor(window,0,0,0,255);
SDL_RenderDrawLine(window,i*size_bloc + XRect , (j+1)*size_bloc + YRect + ygscreen,(i+1)*size_bloc + XRect ,j*size_bloc + YRect + ygscreen);
}
if ((ab[i+j*6]%3)==2){
SDL_SetRenderDrawColor(window,255,255,255,255);
SDL_RenderDrawLine(window,i*size_bloc + XRect , (j+1)*size_bloc + YRect + ygscreen,(i+1)*size_bloc + XRect ,j*size_bloc + YRect + ygscreen);
}
ab[i+j*6]=ab[i+j*6]+1;

tr[i+j*6]=(ab[i+j*6]%3);

}
}

void drawLinech(SDL_Renderer *window, int x,int y){
if(((x>150)&&(x<559)&&(y>140)&&(y<627))){
int i = (x - xrect1) / size_bloc , j = (y - yrect1 - ygscreen) / size_bloc;

SDL_SetRenderDrawColor(window,0,0,0,255);
if ((ab[i+j*6]%3)==0){
SDL_RenderDrawLine(window,i*size_bloc +xrect1 , j*size_bloc + yrect1 + ygscreen,(i+1)*size_bloc + xrect1 ,(j+1)*size_bloc + yrect1 + ygscreen);
}
if ((ab[i+j*6]%3)==1){
SDL_SetRenderDrawColor(window,255,255,255,255);
SDL_RenderDrawLine(window,i*size_bloc +xrect1 , j*size_bloc + yrect1 + ygscreen,(i+1)*size_bloc + xrect1 ,(j+1)*size_bloc + yrect1 + ygscreen);
SDL_SetRenderDrawColor(window,0,0,0,255);
SDL_RenderDrawLine(window,i*size_bloc + xrect1 , (j+1)*size_bloc + yrect1 + ygscreen,(i+1)*size_bloc + xrect1 ,j*size_bloc + yrect1 + ygscreen);
}
if ((ab[i+j*6]%3)==2){
SDL_SetRenderDrawColor(window,255,255,255,255);
SDL_RenderDrawLine(window,i*size_bloc + xrect1 , (j+1)*size_bloc + yrect1 + ygscreen,(i+1)*size_bloc + xrect1 ,j*size_bloc + yrect1 + ygscreen);
}
ab[i+j*6]=ab[i+j*6]+1;

tr[i+j*6]=(ab[i+j*6]%3);
printf("i = %d  j = %d \t",i,j);
}
}

void drawLinecontinue(SDL_Renderer *window, int i,int j){

SDL_SetRenderDrawColor(window,0,0,0,255);
if ((save[i+j*6])==1){
SDL_RenderDrawLine(window,i*size_bloc + XRect , j*size_bloc + YRect + ygscreen,(i+1)*size_bloc + XRect ,(j+1)*size_bloc + YRect + ygscreen);
}
if ((save[i+j*6])==2){
SDL_SetRenderDrawColor(window,255,255,255,255);
SDL_RenderDrawLine(window,i*size_bloc + XRect , j*size_bloc + YRect + ygscreen,(i+1)*size_bloc + XRect ,(j+1)*size_bloc + YRect + ygscreen);
SDL_SetRenderDrawColor(window,0,0,0,255);
SDL_RenderDrawLine(window,i*size_bloc + XRect , (j+1)*size_bloc + YRect + ygscreen,(i+1)*size_bloc + XRect ,j*size_bloc + YRect + ygscreen);
}

}

void drawLinecontinuep(SDL_Renderer *window, int i,int j){


SDL_SetRenderDrawColor(window,0,0,0,255);
if ((savep[i+j*6])==1){
SDL_RenderDrawLine(window,i*size_bloc + XRect , j*size_bloc + YRect + ygscreen,(i+1)*size_bloc + XRect ,(j+1)*size_bloc + YRect + ygscreen);
}
if ((savep[i+j*6])==2){
SDL_SetRenderDrawColor(window,255,255,255,255);
SDL_RenderDrawLine(window,i*size_bloc + XRect , j*size_bloc + YRect + ygscreen,(i+1)*size_bloc + XRect ,(j+1)*size_bloc + YRect + ygscreen);
SDL_SetRenderDrawColor(window,0,0,0,255);
SDL_RenderDrawLine(window,i*size_bloc + XRect , (j+1)*size_bloc + YRect + ygscreen,(i+1)*size_bloc + XRect ,j*size_bloc + YRect + ygscreen);
}

}


void drawLinespace(SDL_Renderer *window){
int i,j,hk=1,l;
Sleep(20);
srand(time(NULL));
d= (rand() % 36 );
i=(d/6);
j=(d%6);
printf("i =  %d   j = %d   d =  %d n =  %d \t",i,j,d,n1);

if((n1!=37)){
    for(l=0;l<n1;l++){
    if(bot[l]==d){
        hk=0;
    }
    }
    if(hk==1){
        bot[n1-1]=d;
        n1++;
    }
}
SDL_SetRenderDrawColor(window,0,0,0,255);
if ((grid[i+j*6])==1){
SDL_RenderDrawLine(window,i*size_bloc + XRect , j*size_bloc + YRect + ygscreen,(i+1)*size_bloc + XRect ,(j+1)*size_bloc + YRect + ygscreen);
}

if ((grid[i+j*6])==2){
SDL_SetRenderDrawColor(window,0,0,0,255);
SDL_RenderDrawLine(window,i*size_bloc + XRect , j*size_bloc + YRect + ygscreen,(i+1)*size_bloc + XRect ,(j+1)*size_bloc + YRect + ygscreen);
SDL_SetRenderDrawColor(window,255,255,255,255);
SDL_RenderDrawLine(window,i*size_bloc + XRect , j*size_bloc + YRect + ygscreen,(i+1)*size_bloc + XRect ,(j+1)*size_bloc + YRect + ygscreen);
SDL_SetRenderDrawColor(window,0,0,0,255);
SDL_RenderDrawLine(window,i*size_bloc + XRect , (j+1)*size_bloc + YRect + ygscreen,(i+1)*size_bloc + XRect ,j*size_bloc + YRect + ygscreen);

}

}

void drawLinespacech(SDL_Renderer *window){

int i,j,hk=1,m;

srand(time(NULL));
yu= (rand() % 36 );
i=(yu/6);
j=(yu%6);
printf("i =  %d   j = %d   yu =  %d n =  %d \t",i,j,yu,n2);

if((n2!=37)){
    for(m=0;m<n2;m++){
    if(bot2[m]==yu){
        hk=0;
    }
    }
    if(hk==1){
        bot2[n2-1]=yu;
        n2++;
    }
}
SDL_SetRenderDrawColor(window,0,0,0,255);
if ((grid[i+j*6])==1){
SDL_RenderDrawLine(window,i*size_bloc + xrect2 , j*size_bloc + yrect2 + ygscreen,(i+1)*size_bloc + xrect2 ,(j+1)*size_bloc + yrect2 + ygscreen);
}

if ((grid[i+j*6])==2){
SDL_SetRenderDrawColor(window,255,255,255,255);
SDL_RenderDrawLine(window,i*size_bloc + xrect2 , j*size_bloc + yrect2 + ygscreen,(i+1)*size_bloc + xrect2 ,(j+1)*size_bloc + yrect2 + ygscreen);
SDL_SetRenderDrawColor(window,0,0,0,255);
SDL_RenderDrawLine(window,i*size_bloc + xrect2 , (j+1)*size_bloc + yrect2 + ygscreen,(i+1)*size_bloc + xrect2 ,j*size_bloc + yrect2 + ygscreen);
}

}

SDL_Texture *loadImage(const char path[], SDL_Renderer *renderer)
 {
    SDL_Surface *tmp = NULL;
    SDL_Texture *texture = NULL;
    tmp = IMG_Load(path);
    if(NULL == tmp)
    {
       fprintf(stderr, "Erreur SDL_LoadBMP : %s",SDL_GetError());
       return NULL;
   }
    texture = SDL_CreateTextureFromSurface(renderer, tmp);
    SDL_FreeSurface(tmp);
    if(NULL == texture)
    {
       fprintf(stderr,"Erreur SDL_CreateTextureFromSurface : %s",SDL_GetError());
       return NULL;
    }
    return texture;
 }



SDL_Texture *loadttf(const char text[], SDL_Renderer *renderer,int taille,int r,int g ,int b)
 {
    SDL_Color couleurNoire = {r, g, b};
    TTF_Font* font = TTF_OpenFont("abnes.TTF", taille);
    SDL_Surface *tmpt = NULL;
    SDL_Texture *texturet = NULL;
    tmpt = TTF_RenderText_Blended(font, text, couleurNoire);
    if(NULL == tmpt)
    {
       fprintf(stderr, "Erreur SDL_loadttf : %s",SDL_GetError());
       return NULL;
   }
    texturet = SDL_CreateTextureFromSurface(renderer, tmpt);
    SDL_FreeSurface(tmpt);
    if(NULL == texturet)
    {
       fprintf(stderr,"Erreur SDL_CreateTextureFromSurface : %s",SDL_GetError());
       return NULL;
    }
    return texturet;
 }




int main( int argc, char* args[] )
{
    SDL_Init(SDL_INIT_VIDEO|SDL_INIT_TIMER);
    TTF_Init();
    SDL_Window *winMAIN = SDL_CreateWindow("space X",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,1363,710,SDL_WINDOW_SHOWN);
    SDL_Renderer *window = SDL_CreateRenderer(winMAIN,-1,SDL_RENDERER_ACCELERATED);

    int Running = 1;
    char prenom [100];
    SDL_Event evento;

    int m=0;
    for (m=0; m<36; m++){

        printf("nice[%d] = %d :",m ,grid[m]);


      }
    printf("GG = %d",GG);
            if (Mix_OpenAudio(96000, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) < 0)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Erreur initialisation SDL_mixer : %s", Mix_GetError());

    }

    Mix_Music* music = Mix_LoadMUS("cla.mp3");

    if (music <0)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Erreur chargement de la musique : %s", Mix_GetError());
        Mix_CloseAudio();
        SDL_Quit();
        return -1;
    }
        SDL_RenderClear(window);
        Mix_PlayMusic(music, -1);
        SDL_Texture *texture0=loadImage("space X (2).JPG",window);
        SDL_RenderCopy(window,texture0, NULL, NULL);
        Mix_AllocateChannels(2);
                Mix_Volume(0, MIX_MAX_VOLUME);
                Mix_Volume(1, MIX_MAX_VOLUME / 2);
        Mix_Chunk* music1 = Mix_LoadWAV("cla2.wav");
        Mix_Chunk* music2 = Mix_LoadWAV("mouse.wav");
        SDL_RenderPresent(window);
   int o=0,k=1,replay=0,savo=0,sorry=0;
   bool z= false;
   time_t fin;
   float s=0;
   float scorek2=0;
   int l,jk=0,st=0,continu=0,t=0,scot,lose,sm=1,ytb,p=0,G;SDL_Texture *titre = NULL;
          SDL_Rect rect= {500, 100, 350, 100};SDL_StartTextInput();
    while(Running){


        while(SDL_PollEvent(&evento))
     {
        switch (evento.type)
        { case  SDL_MOUSEBUTTONDOWN:


            if((evento.button.x>571)&&(evento.button.x<765)&&(evento.button.y>470)&&(evento.button.y<548))
            {b=0;
            o++;
            if((o==1)&&(continu==0)){
                printf("replay = %d \n\n",replay);
                SDL_RenderClear(window);
                initialize_matrice(matrice);
                SDL_Texture *texture1=loadImage("final.JPG",window);
                SDL_RenderClear(window);
                SDL_RenderCopy(window, texture1, NULL, NULL);
                SDL_RenderPresent(window);
                drawMap(window,XRect,YRect,0);
                Mix_HaltMusic();
                printf("pr");


                Mix_PlayChannel(0, music1, -1);

            printf(" hii give me your name? \n");strcpy(prenom,"");SDL_StartTextInput();




            printf("nice to meet you %s good luck ", prenom);
            debut=time(NULL) ;st=0;p=0;
            }

            }

            if((evento.button.x>945)&&(evento.button.x<1302)&&(evento.button.y>471)&&(evento.button.y<545))
            {ch++;b=0;
            if(ch==1){
                    for (m=0; m<36; m++){

        tr[m]=0;
        ab[m]=0;

         }
            SDL_RenderClear(window);
                initialize_matrice(matrice);
                SDL_Texture *texture1=loadImage("final.JPG",window);
                SDL_RenderClear(window);
                SDL_RenderCopy(window, texture1, NULL, NULL);
                SDL_RenderPresent(window);

                Mix_HaltMusic();

                Mix_PlayChannel(0, music1, -1);

            printf(" hii give me your name? \n");


            debut=time(NULL) ;st=0;
                drawMap(window,yrect1,yrect1,0);
                drawMap(window,xrect2,yrect2,0);strcpy(prenom,"");SDL_StartTextInput();


          G=1;p=0;

           for(int l=0;l<36;l++){
          bot2[l]=36;
    }


            printf("challnge");
            }
            }
            printf(" o = %d  continue %d  t = %d  ch = %d",o,continu,t,ch);
            //////**********************debut menu********************////////////////
            FILE* F2;
            F2=fopen("C:/savost.bin","rb");
            fread(&savo,sizeof(int),1,F2);
            fread(&st,sizeof(int),1,F2);
        fclose(F2);
         if((o<1)&&(continu<1)&&(t<1)&&(ch<1)){
         if((evento.button.x>0)&&(evento.button.x<108)&&(evento.button.y>0)&&(evento.button.y<85))
            {
            SDL_RenderClear(window);
            SDL_Texture *texture3=loadImage("lose.JPG",window);
            SDL_RenderCopy(window, texture3, NULL, NULL);
            SDL_RenderPresent(window);
            scot=1;


            SDL_Rect RECT[5];
            SDL_Rect RECTs={150,580,350,100};
            SDL_Rect RECT2={780,143,350,70};
    int y = 350;
    for (int i=0;i<5;i++){
       //coordonees
       RECT[i].x = 700;
       RECT[i].y = y;
      //largeur
      RECT[i].w=400;
      //hauteur
      RECT[i].h=70;
      y+=70;
    }

            SDL_Texture *titre = NULL;
            FILE* F;
           joueur tab[6];
     char x[100];
     char z[100];
     int i;
        F=fopen("D:/playerscore.txt","r");
    i=0;
    while (!feof(F)){
     sprintf(z,"%d-",i+1);
     fscanf(F,"%s : %03d",tab[i].nom,&tab[i].score);
     if(tab[i].score>0 && tab[i].score<1000){
     sprintf(x,"%s : %03d",tab[i].nom,tab[i].score);
     strcat(z,x);
     titre = loadttf(z, window,  174, 174, 254, 255);
     SDL_RenderCopy(window,titre, NULL,&RECT[i]);
     i++;
     }
  }fclose(F);
  F=fopen("D:/playerscore.txt","r");
   int SD=0;i=0;
  while (SD!=1){
     sprintf(z,"%d-",i+1);printf("hiiiiiiii");
     fscanf(F,"%s : %03d",tab[i].nom,&tab[i].score);
     if(tab[i].score>0 && tab[i].score<1000){
     sprintf(x,"%s : %03d",tab[i].nom,tab[i].score);
     strcat(z,x);
     titre = loadttf(z, window,  174, 174, 254, 255);
     SDL_RenderCopy(window,titre, NULL,&RECTs);

     }SD++;
  }fclose(F);
      sprintf(x,"- %.0f -",scorek2);
     titre = loadttf(x, window,  174, 174, 254, 255);
     SDL_RenderCopy(window,titre, NULL,&RECT2);




            printf("score");
            }
         if((evento.button.x>1271)&&(evento.button.x<1363)&&(evento.button.y>0)&&(evento.button.y<50))
            {
            printf("good bye");
            Running=0;
            }
         if(((evento.button.x>68)&&(evento.button.x<406)&&(evento.button.y>479)&&(evento.button.y<537))&&(savo==1))
            {
                Mix_HaltMusic();b=0;


                debut=time(NULL);
                SDL_RenderClear(window);
                SDL_Texture *texture1=loadImage("final.JPG",window);
                SDL_RenderClear(window);
                SDL_RenderCopy(window, texture1, NULL, NULL);
                SDL_RenderPresent(window);
                drawMap(window,XRect,YRect,1);



                Mix_PlayChannel(0, music1, -1);



            printf("hello again %s good luck \n", prenom);


           FILE* F2;FILE* F;

            F2=fopen("C:/vec.bin","rb");
            for(int i=0;i<36;i++){
            fread(&save[i],sizeof(int),1,F2);
        }
        fclose(F2);
        for (m=0; m<36; m++){

           tr[m]=0;
           tr[m]=save[m];
           ab[m]=save[m];
         }

            for( m= 0; m <6; m++){
             for( l = 0; l <6; l++){

             drawLinecontinue(window,m,l);
             }
             }

        F2=fopen("C:/scos.bin","rb");
            fread(&scos,sizeof(double),1,F2);

        fclose(F2);
        F=fopen("D:/prenom.txt","r");
    fscanf(F,"%50s",prenom);
           drawRect(window,500,100,350,100,0,0,0,255);
          titre = loadttf(prenom, window,  100, 174, 254, 255);
           SDL_RenderCopy(window,titre, NULL,&rect);

            o=0;
            continu=1;


        savo=0;
        F2=fopen("C:/savost.bin","wb");
            fwrite(&savo,sizeof(int),1,F2);
            fwrite(&st,sizeof(int),1,F2);
        fclose(F2);
            printf("continue");write0=1;printf("sttttttt : %d",st);

            }
         if(((evento.button.x>68)&&(evento.button.x<406)&&(evento.button.y>479)&&(evento.button.y<537))&&(savo==0)&&(continu<1))
            {
                printf("you can't continue without saving");
            }

         if((evento.button.x>236)&&(evento.button.x<1201)&&(evento.button.y>283)&&(evento.button.y<388))
            {
                SDL_RenderClear(window);
                initialize_matrice(matrice);
                SDL_Texture *texture1=loadImage("space1.PNG",window);
                SDL_RenderClear(window);
                SDL_RenderCopy(window, texture1, NULL, NULL);
                SDL_RenderPresent(window);
                drawMap(window,XRect,YRect,0);
                Mix_HaltMusic();



                Mix_PlayChannel(0, music1, -1);
                debut=time(NULL);


            printf("hii it's let me show you who's the better good luck \n");


             t=1;



            o=0;st=0;
            for(int l=0;l<36;l++){
          bot[l]=36;
    }
            printf(" continue = %d",continu);
            printf("space 1 ");

            }
         }
         ///////////////*****************************fin********************************//////


         ///////////////**************debut button*****************************/////////////
         if((o>1)||(continu>1)||(ch>1)){
            if((evento.button.x>1271)&&(evento.button.x<1363)&&(evento.button.y>0)&&(evento.button.y<50))
            {if(jk%2==1){
            Mix_Resume(0);
            printf("yessssssssssooooooooooooo");
            }
            if(jk%2==0){
            Mix_Pause(0);
            printf("yessssssssss");}
            jk++;
            }
            if((evento.button.x>0)&&(evento.button.x<46)&&(evento.button.y>0)&&(evento.button.y<43)&&(t==0))
            {if(ch==0){
                b++;
              m=0;
              for (m=0; m<36; m++){

        printf("nice[%d] = %d :",m ,grid[m]);

      }
            printf("GG = %d \n",GG);

             for (m=0; m<36; m++){

        printf("good[%d] = %d| save[%d}  = %d :",m ,tr[m],m,save[m ]);
        printf("replay = %d \n",replay);
            }
        p=b%2;
        if(p==1){
        tp=difference;
        }
        else debutp=time(NULL);

        SDL_RenderClear(window);
        SDL_Texture *texture3=loadImage("pause.JPG",window);
        SDL_RenderCopy(window, texture3, NULL, NULL);
        SDL_RenderPresent(window);

       savop=1;


        printf("pause");}
        else{
                 SDL_RenderClear(window);

                SDL_Texture *texture3=loadImage("internet-in-space-featured.JPG",window);
                SDL_RenderClear(window);
                SDL_RenderCopy(window, texture3, NULL, NULL);
                SDL_RenderPresent(window);
                sorry=1;for (m=0; m<36; m++){

        tr[m]=0;
        ab[m]=0;

         }
            }
          }
            if(p==0){printf(" ch = %d o = %d",ch,o);
            if(((o>=1)&&(write0==1))||(continu>=1)){ printf(" hhhhhhhhhhhhhhhhhhhhhhhhhhhh= %d",write0);
             drawLine(window , evento.button.x , evento.button.y ) ;

             Mix_PlayChannel(1, music2, 0);

            }


             }
            if(p==0){
            if((ch>1)&&(write0==1)){
             drawLinech(window , evento.button.x , evento.button.y ) ;

             Mix_PlayChannel(1, music2, 0);
            }
             }

         }
         if((o>=1)||(t==1)||(continu>=1)||(ch>=1)){
         if(t==1)sm=0;
         if((evento.button.x>0)&&(evento.button.x<46)&&(evento.button.y>44)&&(evento.button.y<81)&&(sm==1))
            {printf("o : %d \n",o);b=0;
             if (ch==0){
                Mix_HaltChannel(0);


                SDL_RenderClear(window);
                initialize_matrice(matrice);
                SDL_Texture *texture1=loadImage("final.JPG",window);
                SDL_RenderClear(window);
                SDL_RenderCopy(window, texture1, NULL, NULL);
                SDL_RenderPresent(window);
                drawMap(window,XRect,YRect,0);

                for (m=0; m<36; m++){

              tr[m]=0;
              ab[m]=0;

               }


                Mix_PlayChannel(0, music1, -1);
             drawRect(window,500,100,350,100,0,0,0,255);
        titre = loadttf(prenom, window,  100, 174, 254, 255);
           SDL_RenderCopy(window,titre, NULL,&rect);

            st=0;jk=0;
             debut=time(NULL) ;

            printf("replay");}
            else{
                    for (m=0; m<36; m++){

        tr[m]=0;
        ab[m]=0;

         }
            SDL_RenderClear(window);
                initialize_matrice(matrice);
                SDL_Texture *texture1=loadImage("final.JPG",window);
                SDL_RenderClear(window);
                SDL_RenderCopy(window, texture1, NULL, NULL);
                SDL_RenderPresent(window);

                Mix_HaltMusic();

                Mix_PlayChannel(0, music1, -1);

            printf(" hii give me your name? \n");drawRect(window,500,100,350,100,0,0,0,255);
           titre = loadttf(prenom, window,  100, 174, 254, 255);
           SDL_RenderCopy(window,titre, NULL,&rect);
            debut=time(NULL) ;st=0;dt=time(NULL);
                drawMap(window,yrect1,yrect1,0);
                drawMap(window,xrect2,yrect2,0);


          G=1;jk=0;




            printf("replay chalnge");


            }
            }

          if((evento.button.x>0)&&(evento.button.x<46)&&(evento.button.y>81)&&(evento.button.y<128)&&(sm==1))
            {
                if(ch==0){
            FILE* F2;FILE* F;
            F2=fopen("C:/mat.bin","wb");

    for (int i=0;i<7;i++){
        for(int j=0;j<7;j++){
            fwrite(&matrice[i][j],sizeof(int),1,F2);
        }
    }
    fclose(F2);

            F2=fopen("C:/vec.bin","wb");
            for(int i=0;i<36;i++){
            fwrite(&tr[i],sizeof(int),1,F2);
        }
        fclose(F2);
        savo=1;st=1;
        F2=fopen("C:/savost.bin","wb");
            fwrite(&savo,sizeof(int),1,F2);
            fwrite(&st,sizeof(int),1,F2);
        fclose(F2);

         fin=time(NULL);
         scos=difftime(fin,debut);

         F2=fopen("C:/scos.bin","wb");
            fwrite(&scos,sizeof(double),1,F2);

        fclose(F2);
        F2=fopen("C:/soul.bin","wb");
            for(int i=0;i<36;i++){
            fwrite(&grid[i],sizeof(int),1,F2);
        }
        fclose(F2);
        F=fopen("D:/prenom.txt","w");
        fprintf(F,"%s",prenom);
        fputc('\n',F);
        fclose(F);


        if( access( "C:/vec.bin", F_OK ) == -1)
    {
        printf("file is not found");

    }
    else printf("saveeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeee");

            printf("save");
            }
            else{
                 SDL_RenderClear(window);

                SDL_Texture *texture3=loadImage("internet-in-space-featured.JPG",window);
                SDL_RenderClear(window);
                SDL_RenderCopy(window, texture3, NULL, NULL);
                SDL_RenderPresent(window);
                sorry=1;for (m=0; m<36; m++){

        tr[m]=0;
        ab[m]=0;

         }
            }
            }
        if((evento.button.x>0)&&(evento.button.x<46)&&(evento.button.y>128)&&(evento.button.y<174))
            {
            if(continu==1)continu=0;
            Mix_HaltChannel(0);
            Mix_HaltChannel(1);
            Mix_PlayMusic(music, -1);
            SDL_Texture *texture2=loadImage("space X (2).JPG",window);
            SDL_RenderClear(window);
            SDL_RenderCopy(window, texture2, NULL, NULL);
            SDL_RenderPresent(window);
            o=0;t=0;continu=0;G=0;ch=0;n1=0;n2=0;write0=0;
        for (m=0; m<36; m++){

        tr[m]=0;
        ab[m]=0;

         }p=0;scot=0;jk=0;


            printf("quit");
            }
         if(sm==0)sm=1;
         }
         /*** button more pause**/
         if((evento.button.x>119)&&(evento.button.x<272)&&(evento.button.y>639)&&(evento.button.y<680)&&(p==1))
            { FILE* F2;FILE* F;
            F2=fopen("C:/mat.bin","wb");

    for (int i=0;i<7;i++){
        for(int j=0;j<7;j++){
            fwrite(&matrice[i][j],sizeof(int),1,F2);
        }
    }
    fclose(F2);

            F2=fopen("C:/vec.bin","wb");
            for(int i=0;i<36;i++){
            fwrite(&tr[i],sizeof(int),1,F2);
        }
        fclose(F2);
        savo=1;st=1;
        F2=fopen("C:/savost.bin","wb");
            fwrite(&savo,sizeof(int),1,F2);
            fwrite(&st,sizeof(int),1,F2);
        fclose(F2);

         fin=time(NULL);
         scos=difftime(fin,debut);

         F2=fopen("C:/scos.bin","wb");
            fwrite(&scos,sizeof(double),1,F2);

        fclose(F2);
        F2=fopen("C:/prenom.bin","wb");
            fwrite(prenom,sizeof(char),1,F2);

        fclose(F2);
        F=fopen("D:/prenom.txt","w");
        fprintf(F,"%s",prenom);
        fputc('\n',F);
        fclose(F);

             printf("save");
            }
        if((evento.button.x>532)&&(evento.button.x<824)&&(evento.button.y>639)&&(evento.button.y<680)&&(p==1))
            {

                for (m=0; m<36; m++){

         savep[m]=tr[m];

         }




          Mix_HaltMusic();



                SDL_RenderClear(window);
                SDL_Texture *texture1=loadImage("final.JPG",window);
                SDL_RenderClear(window);
                SDL_RenderCopy(window, texture1, NULL, NULL);
                SDL_RenderPresent(window);
                drawMap(window,XRect,YRect,0);



                Mix_PlayChannel(0, music1, -1);



            printf("hello again %s good luck \n", prenom);



            for( m= 0; m <6; m++){
             for( l = 0; l <6; l++){

             drawLinecontinuep(window,m,l);
             }
             }
             for (m=0; m<36; m++){

           tr[m]=0;
           tr[m]=savep[m];
           ab[m]=savep[m];
         }
         b++;
         p=b%2;
        if(p==1){
        tp=difference;
        }
        else debutp=time(NULL);







         printf(" b = %d | p = %d ",b,p);
              drawRect(window,500,100,350,100,0,0,0,255);
              titre = loadttf(prenom, window,  100, 174, 254, 255);
           SDL_RenderCopy(window,titre, NULL,&rect);

             printf("resume");
            }
        if((evento.button.x>1052)&&(evento.button.x<1271)&&(evento.button.y>639)&&(evento.button.y<680)&&(p==1))
            {printf("o : %d \n",o);b=0;
            p=0;
                Mix_HaltChannel(0);


                SDL_RenderClear(window);
                initialize_matrice(matrice);
                SDL_Texture *texture1=loadImage("final.JPG",window);
                SDL_RenderClear(window);
                SDL_RenderCopy(window, texture1, NULL, NULL);
                SDL_RenderPresent(window);
                drawMap(window,XRect,YRect,0);

                for (m=0; m<36; m++){

              tr[m]=0;
              ab[m]=0;

               }


                Mix_PlayChannel(0, music1, -1);


            drawRect(window,500,100,350,100,0,0,0,255);
            titre = loadttf(prenom, window,  100, 174, 254, 255);
           SDL_RenderCopy(window,titre, NULL,&rect);st=0;jk=0;
             debut=time(NULL) ;
             printf("replay");
            }
        if((evento.button.x>588)&&(evento.button.x<773)&&(evento.button.y>312)&&(evento.button.y<357)&&(p==1))
            {
             SDL_RenderClear(window);
            SDL_Texture *texture3=loadImage("lose.JPG",window);
            SDL_RenderCopy(window, texture3, NULL, NULL);
            SDL_RenderPresent(window);
            scot=1;

                        SDL_Rect RECT[5];
            SDL_Rect RECTs={150,580,350,100};
            SDL_Rect RECT2={780,143,350,70};
    int y = 350;
    for (int i=0;i<5;i++){
       //coordonees
       RECT[i].x = 700;
       RECT[i].y = y;
      //largeur
      RECT[i].w=400;
      //hauteur
      RECT[i].h=70;
      y+=70;
    }

            SDL_Texture *titre = NULL;
            FILE* F;
           joueur tab[6];
     char x[100];
     char z[100];
     int i;
        F=fopen("D:/playerscore.txt","r");
    i=0;
    while (!feof(F)){
     sprintf(z,"%d-",i+1);
     fscanf(F,"%s : %03d",tab[i].nom,&tab[i].score);
     if(tab[i].score>0 && tab[i].score<1000){
     sprintf(x,"%s : %03d",tab[i].nom,tab[i].score);
     strcat(z,x);
     titre = loadttf(z, window,  174, 174, 254, 255);
     SDL_RenderCopy(window,titre, NULL,&RECT[i]);
     i++;
     }
  }fclose(F);
  F=fopen("D:/playerscore.txt","r");
   int SD=0;i=0;
  while (SD!=1){
     sprintf(z,"%d-",i+1);printf("hiiiiiiii");
     fscanf(F,"%s : %03d",tab[i].nom,&tab[i].score);
     if(tab[i].score>0 && tab[i].score<1000){
     sprintf(x,"%s : %03d",tab[i].nom,tab[i].score);
     strcat(z,x);
     titre = loadttf(z, window,  174, 174, 254, 255);
     SDL_RenderCopy(window,titre, NULL,&RECTs);

     }SD++;
  }fclose(F);
      sprintf(x,"- %.0f -",scorek2);
     titre = loadttf(x, window,  174, 174, 254, 255);
     SDL_RenderCopy(window,titre, NULL,&RECT2);




             printf("score");
            }

            printf("x=  %d:   y =  %d",evento.button.x,evento.button.y);
            /*** fin button more pause**/
         /////////////////////******************* fin button******************///////////
        break;


       case SDL_KEYDOWN:
        switch(evento.key.keysym.sym)
        {
           case SDLK_SPACE:
           printf("tab");
           if ((k==0)||(scot==1)||(lose==1)||(t==1)||(p==1)||(sorry==1)){
            Mix_HaltChannel(0);
            Mix_HaltChannel(1);
            Mix_PlayMusic(music, -1);
            SDL_Texture *texture2=loadImage("space X (2).JPG",window);
            SDL_RenderClear(window);
            SDL_RenderCopy(window, texture2, NULL, NULL);
            SDL_RenderPresent(window);
            printf("GG = %d \n",GG);
            o=0;lose=0;ytb=0;continu=0;t=0;p=0;ch=0;G=0;n2=0;write0=0;jk=0;
        }
        k++;scot=0;sorry=0;
           break;
           case SDLK_ESCAPE:if((o>1)||(continu>1)||(ch>=1)){
               if(scot==1){
                    if(ch>=1){

                    }
                    else{


        SDL_RenderClear(window);
        SDL_Texture *texture3=loadImage("pause.JPG",window);
        SDL_RenderCopy(window, texture3, NULL, NULL);
        SDL_RenderPresent(window);


                    }
               }
               scot=0;sorry=0;n2=0;}
            break;


           case SDLK_RETURN:if((o>=1)||(ch>=1)){

          SDL_StopTextInput();
          write0=1;
          dt=time(NULL);
          debut=time(NULL) ;}

            break;

          case SDLK_BACKSPACE:if((o>=1)||(ch>=1)){
            if(strlen(evento.text.text)==0){
                strcpy(prenom,"");
            }else{
                l=strlen(prenom);
                strcpy(prenom+l-1,prenom+l);
                puts(prenom);

            }

           drawRect(window,500,100,350,100,0,0,0,255);
           titre = loadttf(prenom, window,  100, 174, 254, 255);
           SDL_RenderCopy(window,titre, NULL,&rect);
           puts(prenom);
           titre=NULL;
             SDL_RenderPresent(window);}
           break;

        }


           break;
         case SDL_TEXTINPUT:

            if((o>=1)||(ch>=1)){
            drawRect(window,500,100,350,100,0,0,0,255);
            strcat(prenom,evento.text.text);

           titre = loadttf(prenom, window ,  150, 174, 254, 255);
           SDL_RenderCopy(window,titre, NULL,&rect);
           puts(prenom);
           titre=NULL;}

            break;

        case SDL_QUIT:
            Running=0;
            break;

        default:

        if((o>1)||(continu>1)||(ch>1)||(t==1)){
        if(continu<1){
        z=verefier(0);
        if((z== true)||(n1==37)){
        score=s/10.;
        Mix_HaltChannel(1);
        printf("score : %d ",score);
        SDL_RenderClear(window);
        SDL_Texture *texture3=loadImage("HeroesOfTheStorm_victory1-1024x576.PNG",window);
        SDL_RenderCopy(window, texture3, NULL, NULL);
        SDL_RenderPresent(window);
        k=0;
        continu=0;o=0;ch=0;n1=0;t=0;n2=0;G=0;fiche(prenom,scorek2,1);
        for (m=0; m<36; m++){

        tr[m]=0;
        ab[m]=0;

         }
       /************** scooooooooore*************/////



                     }}
        if(continu>1){

        z=verefier(1);
        if((z== true)||(n1==37)){
        score=s/3.;
        Mix_HaltChannel(1);
        printf("score : %d ",score);
        SDL_RenderClear(window);
        SDL_Texture *texture3=loadImage("HeroesOfTheStorm_victory1-1024x576.PNG",window);
        SDL_RenderCopy(window, texture3, NULL, NULL);
        SDL_RenderPresent(window);
        k=0;
        continu=0;o=0;ch=0;n1=0;t=0;n2=0;G=0;fiche(prenom,scorek2,1);
        for (m=0; m<36; m++){

        tr[m]=0;
        ab[m]=0;

         }
       /************** scooooooooore*************/////

                     }
        }

        }

            break;
        }
     }


        if((ytb==1)){
                score=s/10.;

        Mix_HaltChannel(1);
        SDL_RenderClear(window);
        SDL_Texture *texture3=loadImage("PngItem_6207281.PNG",window);
        SDL_RenderCopy(window, texture3, NULL, NULL);
        SDL_RenderPresent(window);fiche(prenom,scorek2,1);
        k=0;
        continu=0;G=0;n2=0;
        o=0;lose=1;ch=0;

        for (m=0; m<36; m++){

        tr[m]=0;
        ab[m]=0;

         }

                }

        if(((o>=1)||(continu>=1)||(t==1)||(ch>=1))&&(sorry==0)){
            drawRect(window,536,29,300,35,0,0,0,255);
                drawInfos(window,st,o,p);
                fin=time(NULL) ;
                s = difference;
                 scorek2=s/3.;
                if((st==1)&&(continu>=1)){
                    s+=scos;
                }
                if((s>80)&&((o>1)||(continu>1))){
                ytb=1;
               printf("ytb = 1");
                }
                if((n2==37)&&(ch>1)){
                ytb=1;
               printf("ytb = 1");
                }
        }
        if(o==1)o++;
        if(continu==1)continu++;
        if(ch==1)ch++;
        if((t==1)&&(n1!=37)){

             SDL_Delay(1000);
             drawLinespace(window);

             Mix_PlayChannel(1, music2, 1);

        }
        if(n1==37){
            printf(" syyyyyyyybooooooooooooooon");
        }


        if((G==1)&&(n2!=37)){

            fin=time(NULL);
            if(write0==1){
             difference1=difftime(fin, dt);}
             if (((difference1==1)&&(sorry==0))&&(write0==1)){
             drawLinespacech(window);
             dt=time(NULL);


        }}
        if(n2==37){

        }

        SDL_RenderPresent(window);

    }


    SDL_DestroyRenderer(window);
    SDL_DestroyWindow(winMAIN);
    Mix_FreeChunk(music1);
    Mix_FreeChunk(music2);
    Mix_FreeMusic(music);
    Mix_CloseAudio();
    TTF_Quit();
    SDL_Quit();
    return 0;
}
