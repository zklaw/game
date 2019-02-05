#pragma once


class State{
private:
    Player gamer;
public:
    State(){
    }
    State(Player &x){
        gamer=x;
    }
    void setGamer(Player g){
        gamer=g;
    }

    int load_from_file(personal data[],int N){
        FILE *file;
        file = fopen("players1.dat","r+b");
        if (file == NULL)
        {
            perror("Nie udalo sie otworzyc pliku.");
            return 0;
        }

        fseek(file,-N*sizeof(personal),SEEK_END);

        fread(data,sizeof(personal),N,file);

        fclose(file);
        return 1;
    }
    void save_to_file(void){
    //zapisanie struktury i pozycji xy, zapisanie pozycji xy i typ collectibli
        FILE *file;
        file = fopen("players1.dat","a+b");
        if (file == NULL)
        {
            perror("Nie udalo sie otworzyc pliku.");
            return;
        }
        personal *data= (personal*)malloc(1*sizeof(personal));
        data[0]=gamer.getData();
        fwrite(&data[0],sizeof(personal),1,file);
        free(data);
        fclose(file);
    }
    void ask_to_save(int x, int y){
        outtextxy(x,y,"Czy chcesz zapisac? T czy N");
        char option;
        do{
            option=getch();
        }while(option!='t'&&option!='T'&&option!='n'&&option!='N');
        if(option=='t'||option=='T'){
            this->save_to_file();
        }
    }
    void ranking(int x, int y){
        setcolor(WHITE);
        outtextxy(x,y,"Ranking");
        personal ranking[4];
        for(int i=0;i<4;i++){
            Helpers::default_fill_structure(ranking[i]);
        }
        personal help;
        int change;
        this->load_from_file(ranking,4);
        do{
            change=0;
            for(int i=0;i<3;i++){
                if(ranking[i].points<ranking[i+1].points){
                    help=ranking[i];
                    ranking[i]=ranking[i+1];
                    ranking[i+1]=help;
                    change++;
                }
            }
        }while(change!=0);
        char r[500];
        for(int i=0;i<4;i++){
            sprintf(r,"%d. imie: %s, punkty: %d\n",i+1,ranking[i].name,ranking[i].points);
            setcolor(WHITE);
            outtextxy(x,y+(i+1)*30,r);
         }

    }
};
