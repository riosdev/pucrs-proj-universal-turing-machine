#include "T1_RafaelRios.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

TList transicoes;
List estados;
List alfabeto;
List entradas;

FILE *input;

int main(int argc, char **argv){
    char str[500];

    {//Insere 0(branco) no alfabeto
        char branco[2] = "[";
        push(&alfabeto,strdup(branco));
    }
    //Arquivo ou stdin?
    if(argc == 2){
        input = fopen(argv[1],"r");
    }else{
        input = stdin;
    }
    //Construcao da máquina
    parse_machine(input);
    //Construcao das entradas
    puts("Pronto para processar entradas.");
    parse_input();
    //Execucao
    puts("Processamento imediato ou passo a passo? <RUN/STEP>");
    do{
        fgets(str,500,input);
        if(str[strlen(str)-1]=='\n') str[strlen(str)-1] = 0;
    }while((strcmp(str,"RUN") != 0) && (strcmp(str,"STEP") != 0));
    if(!strcmp(str, "STEP")){
        puts("Processamento passo a passo.");
        exec(1);
    }else{
        puts("Processamento imediato");
        exec(0);
    }
    //Codificacao da Maquina
    printf("Codificar Maquina? <SIM/NAO> ");
    do{
        fgets(str,4,stdin);
    }
    while(strcmp(str,"SIM") && strcmp(str,"sim") && strcmp(str,"NAO") && strcmp(str,"nao"));
    if(!strcmp(str,"SIM") || !strcmp(str,"sim")) {codificar();}
    //Encerramento
    if(stdin != input) fclose(input);
    return 0;
}

void parse_machine(FILE* fd){
    char str[2000];
    do{
        fgets(str, 2000, fd);
    }while(strstr(str,"BEGIN_MACHINE")==NULL);
    while((fgets(str,2000,fd),strstr(str,"END_MACHINE"))==NULL){
        if(strlen(str)>15){//BINARY
            FILE *fd = fopen("mt.b","w+");
            decodificar(str,fd);
            rewind(fd);
            parse_machine(fd);
            fclose(fd);
        }else{
            char * sstr[5];
            sstr[0] = strdup(strtok(str," "));
            if(!find(&estados,sstr[0])){
                push(&estados, sstr[0]);
            }
            sstr[1] = strdup(strtok(NULL," "));
            if(!find(&estados,sstr[1])){
                push(&estados, sstr[1]);
            }
            sstr[2] = strdup(strtok(NULL," "));
            if(!find(&alfabeto,sstr[2])){
                push(&alfabeto, sstr[2]);
            }
            sstr[3] = strdup(strtok(NULL," "));
            if(!find(&alfabeto,sstr[3])){
                push(&alfabeto, sstr[3]);
            }
            sstr[4] = strdup(strtok(NULL," \n"));
            if((*(sstr[4]) == 'R') || (*(sstr[4]) == 'S') || (*(sstr[4]) == 'L')){
                Transicao* t = malloc(sizeof(Transicao));
                init_transition(t,sstr[0],sstr[1],sstr[2],sstr[3],sstr[4]);
                tpush(&transicoes,t);
            }
        }
    }
}

void parse_input(){
    char str[221];
    do{
        fgets(str, 200, input);
    }while(strstr(str,"BEGIN_INPUT")==NULL);
    while((memset(str,0,221),fgets(str, 200, input),strstr(str,"END_INPUT"))==NULL){
        memcpy(str+10, str, strlen(str));
        memset(str, '[', 10);
        memset(str+strlen(str)-1,'[',10);
        push(&entradas, strdup(str)+10);
    }
}

void exec(int step){
    Node *n = entradas.head;
    int i = 0;
    while(n != NULL){
        int achou = 0;
        char *fita_entrada = n->valor;
        char *estado_atual = transicoes.head->transicao->e_in;
        printf("PROCESSANDO ENTRADA %d de %d\n", ++i, size(&entradas));
        if(step){
            puts("Processamento passo a passo. Pressione ENTER para continuar...");
            getchar();
        }
        printf("ENTRADA: %s\n", fita_entrada);
        do{
            if(step) {getchar();}
            TNode *tn = transicoes.head;
            achou = 0;
            while(tn != NULL){
                Transicao* t = tn->transicao;
                if((!strcmp(estado_atual, t->e_in)) && (*fita_entrada == *(t->entrada))){
                    estado_atual = t->e_out;
                    *fita_entrada = *(t->saida);
                    if(*(t->movimento) == 'R'){
                        fita_entrada++;
                    }else if(*(t->movimento) == 'L'){
                        fita_entrada--;
                    }
                    printf("%s %s\n", fita_entrada, estado_atual);
                    achou = 1;
                    break;
                }
                tn = tn->next;
            }
        }while(achou);
        puts("TRANSICAO NAO ENCONTRADA. PROCESSAMENTO CONCLUIDO\n");
        n = n->next;
    }
}

int find(List* q, char *t){
    Node *n = q->head;
    int i = 0;
    while(n != NULL){
        if(strcmp(t,n->valor) == 0) {return i+1; break;}
        n = n->next;
        i++;
    }
    return 0;
}

void init_transition(Transicao *t, char *ei, char *eo, char *e, char *s, char *m){
    t->e_in = strdup(ei);
    t->e_out = strdup(eo);
    t->entrada = strdup(e);
    t->saida = strdup(s);
    t->movimento = strdup(m);
}

void codificar(){
    FILE *fd = fopen("mt.b","w+");
    TNode *tn = transicoes.head;
    while(tn != NULL){
        Transicao *t = tn->transicao;
        int i, n;
        n = find(&estados,t->e_in);
        for(i = 0; i < n; i++) {putchar('0');fputc('0',fd);}
        putchar('1');fputc('1',fd);
        n = find(&estados,t->e_out);
        for(i = 0; i < n; i++) {putchar('0');fputc('0',fd);}
        putchar('1');fputc('1',fd);
        n = find(&alfabeto,t->entrada);
        for(i = 0; i < n; i++) {putchar('0');fputc('0',fd);}
        putchar('1');fputc('1',fd);
        n = find(&alfabeto,t->saida);
        for(i = 0; i < n; i++) {putchar('0');fputc('0',fd);}
        putchar('1');fputc('1',fd);
        if(*(t->movimento) == 'R'){
            n = 1;
        }else if(*(t->movimento) == 'L'){
            n = 2;
        }else{
            n = 3;
        }
        for(i = 0; i < n; i++) {putchar('0');fputc('0',fd);}
        tn = tn->next;
        fputs("11",stdout);
        fputs("11",fd);
    }
    putchar('\n');
    fputc('\n',fd);
    fclose(fd);
}

void decodificar(char *mt, FILE *fd){
    char *str = malloc(2048);
    char *ptr0 = mt,*ptr1;
    sprintf(str, "BEGIN_MACHINE\n");
    while(strlen(ptr0) > 10){
        char sstr[50];
        int i,n[5];
        for(i = 0; i < 5; i++){
            ptr1 = strchr(ptr0, '1');
            n[i] = ptr1-ptr0;
            ptr0 = ptr1+1;
        }
        sprintf(sstr,"%d %d %c %c ", n[0], n[1], (n[2]==1)?'[':(n[2]+95), (n[3]==1)?'[':(n[3]+95));
        switch(n[4]){
            case 1: strcat(sstr,"R\n");break;
            case 2: strcat(sstr,"L\n");break;
            case 3: strcat(sstr,"S\n");break;
        }
        strcat(str, sstr);
        ptr0++;
    }
    fputs(str,stdout);
    strcat(str,"END_MACHINE");
    fputs(str,fd);
}