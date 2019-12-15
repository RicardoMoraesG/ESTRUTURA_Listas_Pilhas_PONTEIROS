/*versão testes*/
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
struct no {
    int info;
    struct no *prox;
};
/** FUNÇÕES PARA LISTAS
**/
struct no* inserirNoInicio(struct no* L, int v) {
    struct no *p;//ponteiro tipo struct
    p = (struct no *) malloc(sizeof(struct no));//Aloca espaço de memoria para o novo no
    p->info = v; //Coloca a informacao no novo noh
    p->prox = L; //Faz o encadeamento do novo noh no inicio da Lista
    L = p; //Faz a Lista apontar para o novo noh, o qual passa a ser o primeiro

    return L; //Retorna o endereco do novo noh para atualizar a Lista no prog. principal
}//Fim inserirNoInicio()
struct no* inserirNoFim(struct no* L, int v) {
    struct no *p, *n;
    n = (struct no *) malloc(sizeof(struct no)); //aloca memoria
    n->info = v;//coloca a informação no novo nó
    n->prox = NULL;//como sera o ultimo no, coloca NULL no seu prox
    if (L == NULL) {//tratamento de lista vazia
        return n;
    }
    //localizar o ultimo no da lista
    p = L; //aponta pp para o primeiro
    while(p->prox!=NULL)
        p = p->prox;//anda o p ate o ultimo nó
    p->prox = n; //faz o encadeamento do ultimo nó com o novo nó.
    return L;
};//fim inserirNoFim(struct no *L, int v)
void imprimirLista(struct no* L) {
    struct no *p;//ponteiro tipo struct
    if(L==NULL) { //Tratamento de Caso de Lista Vazia
        printf("Lista Vazia!");
        return;
    }
    p = L; //Aponta p para o primeiro noh da Lista;recebe o endereco do primero no da lista
    while (p != NULL) {
        printf("%i->",p->info);
        p = p->prox;
    }
}//Fim imprimirLista()
struct no* removerDoInicio(struct no* L, int* v) {
    struct no* p;
    p = L; // aponta p para o primeiro no, que sera removido
    *v = p->info; // coloca em val(atraves de v) a informação do nó removido
    L = p->prox; // aponta L para o segundo nom o qual passara a ser o primero
    free(p); // libera espaço de memoria usada pelo no removido
    return L;
};//removerDoInicio
struct no* removerDoFim(struct no* L,int* v) {
    struct no *p, *q;
    if (L == NULL) {
        printf("\n Lista vazia!");
        return L;
    }
    p = L;
    while (p->prox != NULL) //Posiciona p no ultimo noh
        p = p->prox;
    if (L->prox != NULL) { //Lista tem mais de 1 noh
        q = L;
        while (q->prox != p) //Posiciona q no noh anterior ao p
            q = q->prox;
        q->prox = NULL; //Finaliza a Lista no penultimo noh
    } else { //Lista só tem 1 noh
        L = NULL;
    }
    *v = p->info; //Pega a informacao no noh que será removido
    printf("\n Valor %i removido da Lista", p->info);
    free(p); //Libera memoria do noh removido

    return L;
}//Fim removerDoFim()
int comprimentoLista(struct no* L) {
    struct no *p;
    int cont=0;

    p = L;
    while (p != NULL) {
        cont++;
        p = p->prox;
    }

    return cont;

}//Fim comprimentoLista()
int existe(struct no* L,int v) {
    struct no *p;
    int achou;
    p = L;
    achou=0;
    while ((!achou)&&(p != NULL)) {
        if (p->info == v) //Encontrou um noh que tem o valor procurado
            achou = 1;
        p = p->prox;
    }
    return achou;
}//Fim existe()///////////////////////
struct no* localizaRemove(struct no* L,int v) {
    struct no *p, *q;
    if (!existe(L,v)) {
        printf("O valor solicitado NAO existe na Lista.");
        return L;
    }
    p = L;
    while (p->info != v) //Posicionar p no noh que contém a
        p = p->prox;    // primeira ocorencia do valor procurado
    if (p == L) { //O noh a ser removido eh o primeiro noh da Lista
        L = p->prox; //Faz L apontar para o o segundo noh, que será o primeiro
    } else { //O noh a ser removido eh do fim ou "do meio" da Lista
        q = L;
        while (q->prox != p)  //Posiciona q no noh anterior ao p
            q = q->prox;
        q->prox = p->prox; //Faz o encadeamento
    }
    free(p);
    printf(" Removido com sucesso! ");
    return L;
}//Fim localizaRemove()
/** FUNÇÕES PARA PILHAS
*/
void push(struct no** P,int v) {
    struct no *n;
    n = (struct no *) malloc(sizeof(struct no));
    n->info = v;
    n->prox = *P;
    *P = n;
}//Fim push()
int pop(struct no** P) {
    struct no *p;
    int v;
    p = *P; //aponta p para o no do TOPO
    v = p->info; //Peguei a informacao do no a ser removido
    *P = p->prox; //Faz o Pilha apontar p/ o proximo no
    free(p); //Libera memoria do no a ser removido
    return v; //retorna o valor do no removido

}//Fim pop()
void mostrarPilha(struct no** Pilha) {
    struct no *Paux = NULL;//cria uma pilha auxiliar e a inicializa vazia.
    int v;
    if (*Pilha == NULL) { //verifica se a lista recebida como parametro contêm dados
        printf("Pilha Vazia!\n");
        return;
    }
    //O primeiro estou removendo fora do while
    // para ficar na direcao certa quando imprimir
    v = pop(Pilha);  //Retira da Pilha Original
    printf(" %i\n",v); //Mostrei na tela
    push(&Paux,v); //Guarda na Pilha Auxiliar
    while(*Pilha != NULL) {//se o conteudo do endereco apontado por Pilha for diferente de vazio
        v = pop(Pilha);  //Retira o valor da Pilha Original
        printf("               %i\n", v); //Mostra o valor na tela
        push(&Paux, v); //Guarda na Pilha Auxiliar
    }
    while (Paux != NULL) {//enquanto os valores da pilha auxiliar forem diferentes de vazio
        v = pop(&Paux);  //Retira da Pilha Auxiliar
        push(Pilha, v); //Coloca na Pilha Original
    }
}//Fim mostrarPilha()
void opcMostrarPilha(struct no** Pilha1, struct no** Pilha2) { //limpa a main
    int opcP;
    if ((Pilha1 != NULL) || (Pilha2 != NULL)) {
        printf("\n Qual Pilha deseja imprimir? \n 1) Pilha 1 \n 2) Pilha 2  \n");
        fflush(stdin);
        scanf("%i", &opcP);
        switch(opcP) {
        case 1:
            printf("\nPilha->       ");
            mostrarPilha(Pilha1);
            break;
        case 2:
            printf("\nPilha->       ");
            mostrarPilha(Pilha2);
            break;
        } // fim switch(opcPilha).
    } else {
        printf("\n Pilhas Vazias! ");
    }
}
int QtdeMaioresMedia(struct no** Pilha) {
    struct no *Paux=NULL;
    float media;
    int val,soma=0, cont=0;
    while (*Pilha!=NULL) {
        val = pop(Pilha); //Remove da Pilha Original
        soma = soma + val;
        cont++;
        push(&Paux,val); //Guarda valor na Pilha Auxiliar
    }
    media = (float) soma/cont;
    cont = 0;
    while (Paux!=NULL) {
        val = pop(&Paux); //Remove da Pilha Auxiliar
        if (val > media)  //Verifica se é maior que a media
            cont++;
        push(Pilha,val);  //guarda na Pilha Original
    }
    return cont;
}//Fim QtdeMaioresMedia()
int consultarPosicao(struct no** Pilha,int v) {
    struct no *Paux=NULL;
    int posicao=0, achou=0 ;
    int val;
    while ((!achou)&&(*Pilha!=NULL)) {
        val = pop(Pilha);
        push(&Paux,val);
        posicao++;
        if (val==v) {
            achou = posicao;
        }
    }
    //Voltar elementos para a Pilha original
    while(Paux!=NULL) {
        push(Pilha,pop(&Paux)); //Retira da Paux e insere na Pilha
    }
    return achou;
}//Fim consultarPosicao()
int nroItensPilha(struct no** Pilha) {
    struct no *Paux=NULL;
    int val, cont=0;
    while(*Pilha!=NULL) {
        val = pop(Pilha);
        cont++;
        push(&Paux,val);
    }
    while(Paux!=NULL) {
        push(Pilha,pop(&Paux));
    }
    return cont;
}//Fim nroItensPilha()
int esvaziaMenorInsereMaior(struct no** Pilha1, struct no** Pilha2) {
    struct no **Pmenor, **Pmaior;
    int tp1, tp2;
    tp1=nroItensPilha(Pilha1); //Pega o tamanho da Pilha1
    tp2=nroItensPilha(Pilha2); //Pega o tamanho da Pilha2
    if (tp1==tp2)
        return 0; //Pilha possuem o mesmo tamanho. Nada a fazer
    //Continua aqui se as pilha possuem tamanhos diferentes
    if (tp1>tp2) {
        Pmenor = Pilha2;
        Pmaior = Pilha1;
    } else {
        Pmenor = Pilha1;
        Pmaior = Pilha2;
    }
    //Fazer a transferencia de dados
    while(*Pmenor!=NULL)
        push(Pmaior,pop(Pmenor));
    return 1;
}//Fim esvaziaMenorInsereMaior()
/** FUNÇÕES DO TRABALHO
*/
/*1
/*Recebe como parâmetros uma Lista que contém valores e duas Pilhas vazias. A função deve percorrer a Lista e inserir os valores
    ímpares na Pilha1 e os valores pares na Pilha2.*/
void pilhasParImpar(struct no** L, struct no** p1, struct no** p2) {
    struct no* p;//ponteiro tipo struct
    int v;
    if(*L == NULL) { //Tratamento de Caso de Lista Vazia
        printf("Lista vazia ou todos os elementos novos ja foram processados!");
        return;
    } else {
        p = *L; //recebe o endereco do primero no da lista
        while (p != NULL) { //se o conteudo é diferente de vazio
            if (p->info % 2 == 0) { // é Par: calcula o valor do nó/2 e verifica se o resto é 0.
                push(p2,p->info); //insere o valor da pilha no endereço de PilhaPar.
            } else { // é impar.
                push(p1, p->info); //passa o endereço de PilhaImpar para receber o valor da pilha original.
            }
            p = p->prox;
        }
        while (*L != NULL) { // apaga os dados da listaNovos após serem processados.
            *L = removerDoInicio(*L, &v);
        }
        printf("\n Pilha Impar: ");
        mostrarPilha(p1);//exibe o resultado da PilhaImpar na tela.
        printf("\n Pilha Par:   ");
        mostrarPilha(p2);//exibe o resultado da PlhaPar na tela.
    }//fim else.
    system("pause");
}//Fim pilhasParImpar()
/*2
/*a qual recebe uma Lista e deve inverter as posições na Lista, ou seja, a informação que está no primeiro nó passa
    para o último nó, a informação no segundo nó passa para o penúltimo e assim por diante.*/
struct no* inverteLista(struct no* L) {
    struct no *p, *Pilha;//ponteiro tipo struct
    if(L==NULL) { //Tratamento de Caso de Lista Vazia
        printf("Lista Vazia!");
        return L;//retorna o primeiro endereço da lista sem executar alterações.
    } else {
        p = L; //recebe o endereco do primero no da lista
        while (p != NULL) {
            push(&Pilha, p->info); //passa as informações da lista para uma pilha
            p = p->prox;//passa para o próximo nó
        }
        p = L;//retorna ao primeiro endereço da lista
        while (p != NULL) {
            p->info = pop(&Pilha); // devolve as informações para a lista, agora na ordem inversa devido à regra da pilha.
            p = p->prox;//passa para o próximo nó.
        }
        p = L; // retorna ao primeiro endereço da lista
        return L;//aponta para o primeiro endereço da lista já modificada.
    }
}//Fim inverteLista()
/*3*
/*a qual recebe como
    parâmetro uma Lista e deve clonar cada um de seus elementos, criando um novo nó
    para o clone.*/
struct no* clonaValorLista(struct no* L, struct no** Ln) {
    struct no *p, *cloneP;
    if(L==NULL) { //Tratamento de Caso de Lista Vazia
        printf("Lista Vazia!");
        return L;//retorna o primeiro endereço da lista sem executar alterações.
    } else {
        p = L; //recebe o endereco do primero no da lista
        while (p != NULL) {
            cloneP = (struct no *) malloc(sizeof(struct no));//Aloca espaço de memoria para o novo no.
            cloneP->info = p->info;
            *Ln = inserirNoInicio(*Ln, p->info);//acrescenta o valor clonado na lista novos
            cloneP->prox = p->prox;
            p->prox = cloneP;
            p = cloneP->prox;
        }
        printf("\n Valores da lista clonados com sucesso! ");
        p = L;
        printf("\n Nova Lista: \n");
        imprimirLista(p);
        printf("\n");
        return L;//aponta para o primeiro endereço da lista já modificada.
    }
}
/*4
/*Recebe como parâmetro uma Pilha e deve clonar cada um de seus elementos, criando um novo
    nó para o clone.*/
struct no* clonaValorPilha(struct no** Pilha) {
    struct no *Paux = NULL;//cria uma pilha auxiliar e a inicializa vazia.
    int v;
    if (*Pilha == NULL) { //verifica se a lista recebida como parametro comntêm dados
        printf("Pilha Vazia!");
        return *Pilha;
    } else {
        while(*Pilha != NULL) {//se o conteudo do endereco apontado por Pilha for diferente de vazio
            v = pop(Pilha);  //Retira o valor da Pilha Original
            push(&Paux,v); //Guarda na Pilha Auxiliar
        }
        while (Paux != NULL) {//enquanto os valores da pilha auxiliar forem diferentes de vazio
            v=pop(&Paux);  //Retira da Pilha Auxiliar
            push(Pilha,v); //Devolve o valor à Pilha original
            //segue a mesma lógica da funcao mostrarPilha, somente acrescentando a sequencia abaixo:
            push(Pilha,v); //*******clona o valor, acrescentando um novo nó na pilha.
        }
        printf("\n Valores da Pilha clonados com sucesso! ");
        printf("\nPilha->       ");
        mostrarPilha(Pilha);
    }
}
/*5
* Tenha uma função excluirValorLista(struct no *L, int v) a qual deve
excluir da Lista todos os elementos com um determinado valor (v), retornar 1 se a exclusão foi
feita, ou 0 caso o valor NÃO tenha sido encontrado na Lista.
*/
struct no* excluirValorLista(struct no *L, int v) {
    int achou = 0, quant = 0;
    struct no *p, *q, *x;
    p = L;
    while (p != NULL) {
        achou = 0;
        if (p->info == v) {
            achou = 1;
            quant++;
            x = p;
            if (p == L) { //eh o primeiro noh.
                L = p->prox;//aponta para o proximo nó, que passará a ser o primeiro.
                q = p;
            } else {
                if (p->prox == NULL) { //o nó a ser removido eh o ultimo.
                    q->prox = NULL;
                } else {
                    q->prox = p->prox; //faz o encadeamento pulando o noh a ser removido.
                }
            }
        }
        if (p->prox != NULL) {
            q = p;
        }
        p = p->prox;
        if (achou) {
            free(x);
        }
    }
    if(quant > 0) {
        achou = 1;
        printf("\n Foram removidas %i ocorrencias do valor %i \n", quant, v);
    }
    system("pause");
    return L;
}
void opcExcluirValorLista(struct no* Lista, struct no* ListaNovos) {
    int val;
    printf("\nDigite o valor a ser excluido: ");
    fflush(stdin);
    scanf("%i", &val);
    Lista = excluirValorLista(Lista, val);
    if (ListaNovos != NULL) {
        ListaNovos = excluirValorLista(ListaNovos, val);
    } // remove o valor da lista de novos, assim não será incluido nas pilhas Par/Impar.
}
void opcClonaValoresPilha(struct no** Pilha1, struct no** Pilha2) {
    int opc;
    if ((Pilha1 != NULL) || (Pilha2 != NULL)) {
        printf("\n Qual Pilha deseja clonar? \n 1) Pilha 1 \n 2) Pilha 2  \n");
        fflush(stdin);
        scanf("%i", &opc);
        switch(opc) {
        case 1:
            clonaValorPilha(Pilha1);
            break;
        case 2:
            clonaValorPilha(Pilha2);
            break;
        } // fim switch(opcPilha).
    } else {
        printf("\n Pilhas Vazias! ");
    }
}
/*6
    Excluir da Pilha todos os elementos com um determinado valor (v), retornar 1 se a exclusão
foi feita, ou 0 caso o valor NÃO tenha sido encontrado na Pilha. */
struct no* excluirValorPilha(struct no **Pilha, int x) { //x é o valor a ser eliminado.
    struct no *Paux = NULL;//cria uma pilha auxiliar e a inicializa vazia.
    int v, cont = 0;/*
    //O primeiro estou removendo fora do while
    // para ficar na direcao certa quando imprimir
    v = pop(Pilha);  //Retira da Pilha Original
    printf(" %i\n",v); //Mostrei na tela
    push(&Paux,v); //Guarda na Pilha Auxiliar*/
    while(*Pilha != NULL) {//se o conteudo do endereco apontado por Pilha for diferente de vazio
        v = pop(Pilha);  //Retira o valor da Pilha Original
        if (v != x) //só passa para a pilha auxiliar se for diferente de x.
            push(&Paux, v); //Guarda na Pilha Auxiliar
        else
            cont++;
    }
    while (Paux != NULL) {//enquanto os valores da pilha auxiliar forem diferentes de vazio
        v = pop(&Paux);  //Retira da Pilha Auxiliar
        push(Pilha, v); //Coloca na Pilha Original
    }
    if (cont > 0) // se foram encontrados valores iguais ao informado:
        printf("\n Foram removidos %i ocorrencias do valor %i", cont, v);
    else
        printf("\n Nao existe o valor %i para remover ", x);
    return *Pilha;
}
void opcExcluirValorPilha(struct no** Pilha1, struct no** Pilha2,int val) {
    if ((Pilha1 != NULL) || (Pilha2 != NULL)) {//as pilhas contêm valores:
        printf("\n Qual valor deseja excluir? ");
        fflush(stdin);
        scanf("%i", &val);
        if (val % 2 != 0) { // se o valor é impar, está na pilha 1.
            *Pilha1 = excluirValorPilha(Pilha1, val);
            printf(" da pilha 1 Impares");
        } else { // senão está na pilha 2.
            *Pilha2 = excluirValorPilha(Pilha2, val);
            printf(" da pilha 2 Pares");
        }
    } else  // se as pilhas não contêm valores:
        printf("\n Pilhas Vazias! ");
}
int main() {
    setlocale(LC_ALL,"Portuguese");
    struct no *ListaNovos = NULL; //não duplica os dados na função empilharParImpar().
    struct no *Lista = NULL; //Cria a Lista Vazia
    struct no *Pilha1 = NULL; //Inicializa Pilha1 Vazia
    struct no *Pilha2 = NULL; //Inicializa Pilha2 Vazia
    int op, opcP, val;//op = recebe a opção do usuário,. val = recebe os valores para os nós.

    do {
        printf("\n ->       <- PONTEIROS ->        ->");
        //funções de manipulação de listas e pilhas desenvolvidas pelo professor Julio.
        printf("\n\n LISTA:");
        printf("\n\t 1 -> no inicio. ");
        printf("\n\t 2 -> no final. ");
        printf("\n\t 3 -> REMOVER o primeiro.");
        printf("\n\t 4 -> REMOVER o último.");
        printf("\n\t 5 -> Mostrar a lista.");
        printf("\n\t 6 -> Inverter Valores da Lista ");
        printf("\n\t 7 -> Clonar Valores da Lista ");
        printf("\n\t 8 -> Excluir um valor da Lista");
        printf("\n\t 9 -> Separar a Lista em PILHAS Pares e Impares.");
        if ((Pilha1 == NULL) && (Pilha2 == NULL)) {
            printf("\n\n PILHAS: ");
            printf("\n\t \"execute a função '9' para habilitar as pilhas\"");
        } else {
            printf("\n\n PILHAS: ");
            printf("\n\t 10 = Imprimir pilha.");
            printf("\n\t 11 = Clonar valores da pilha.");
            printf("\n\t 12 = Remover um valor da pilha.");
        }
        printf("\n\n Opcao->  ");
        fflush(stdin);
        scanf("%i", &op);
        switch(op) {
        case 1: //INSERE NOVO NÓ NO INICIO DA LISTA
            printf("Digite o valor: ");
            fflush(stdin);
            scanf("%i",&val);
            Lista = inserirNoInicio(Lista,val);
            ListaNovos = inserirNoInicio(ListaNovos,val);
            printf("\n Valor %i incluído! ", val);
            break;
        case 2: //INSERE NOVO NÓ NO FIM DA LISTA
            printf("Digite o valor: ");
            fflush(stdin);
            scanf("%i",&val);
            Lista = inserirNoFim(Lista,val);
            ListaNovos = inserirNoFim(ListaNovos,val);
            printf("\n Valor %i incluído! ", val);
            break;
        case 3: //Exclui o primeiro nó da lista.
            if (Lista == NULL) {
                printf("\nLista Vazia. Impossivel remover!");
            } else {
                Lista = removerDoInicio(Lista,&val);
                printf("\nValor %i removido da Lista ", val);
            }
            if (ListaNovos != NULL) {
                ListaNovos = removerDoInicio(ListaNovos,&val);
            }
            break;
        case 4:// Exclui o último nó da lista.
            Lista = removerDoFim(Lista, &val);
            break;
        case 5: // IMPRIME LISTA.
            printf("\nLista ->" );
            imprimirLista(Lista);
            break;
        case 6: //INVERTE AS POSIÇÕES NA LISTA.
            Lista = inverteLista(Lista);
            if (ListaNovos != NULL) {
                ListaNovos = inverteLista(ListaNovos);
            }
            printf("\n Nova ordem da Lista: ");
            imprimirLista(Lista);//e os exibe com os valores invertidos.
            break;
        case 7: // CLONA CADA VALOR DA LISTA.
            Lista = clonaValorLista(Lista, &ListaNovos); //CLONA OS VALORES DA LISTA.
            break;
        case 8: // EXCLUI UM VALOR DA LISTA.
            opcExcluirValorLista(Lista, ListaNovos);
            break;
        case 9: //SEPARA A LISTA EM PARES E IMPARES.
            pilhasParImpar(&ListaNovos, &Pilha1, &Pilha2);//só serão empilhados os valores que ainda nao foram processados.
            break;
        case 10: //  IMPRIME A PILHA.
            opcMostrarPilha(&Pilha1,&Pilha2);
            break;
        case 11: //CLONA OS VALORES DA PILHA.
            opcClonaValoresPilha(&Pilha1,&Pilha2);
            break;
        case 12: //EXCLUI UM VALOR DA PILHA.
            opcExcluirValorPilha(&Pilha1,&Pilha2, val);
            break;
        /* FUNÇÕES NÃO VISÍVEIS NA INTERFACE:
         *
         *
         *
         *
         **/
        case 20: // remove os elementos da pilha menor e os insere na pilha maior.
            if (esvaziaMenorInsereMaior(&Pilha1, &Pilha2)){
                printf("Menor agora faz parte da maior: ");
                printf("\n Pilha 1:");
                mostrarPilha(&Pilha1);
                printf("\n Pilha 2:");
                mostrarPilha(&Pilha2);
            }
            break;
        case 21: // mostra a quantidade de elementos em uma pilha.
            val = nroItensPilha(&Pilha1);
            printf("A pilha 1 contêm %i itens.", val);
            val = nroItensPilha(&Pilha2);
            printf("A pilha 2 contêm %i itens.", val);
            break;
        case 22: // mostra a quantidade de elementos na Lista.
            printf("\n Quantidade de elementos na Lista: %i ",comprimentoLista(Lista) );
            break;
        case 23: // pesquisa se existe um valor na lista.
            printf("\n Digite o valor para pesquisar na Lista: ");
            fflush(stdin);
            scanf("%i", &val);
            if (existe(Lista,val)){
               printf("\n O valor %i existe na Lista.", val);
            } else {
                printf("\n A Lista não contêm o valor %i. ", val);
            }
        break;
        case 24:
            printf("\n Digite o valor a ser encontrado e excluído: ");
            fflush(stdin);
            scanf("%i", &val);
            Lista = localizaRemove(Lista, val);
            if (existe(ListaNovos, val))
                ListaNovos = localizaRemove(ListaNovos, val);
        case 25:
            printf("\n Digite o valor a empilhar: "); fflush(stdin); scanf("%i", &val);
            if (val %2 == 0) {
                push(&Pilha2, val);
            printf("\n Valor %i incluído na pilha dos Pares.");
            } else {
                push(&Pilha1, val);
                printf("\n Valor %i incluído na pilha dos Ímpares.");
            }
            break;
        case 26: // remove o primeiro nó da pilha.
            if ((Pilha1 != NULL) || (Pilha2 != NULL)) {
                printf("\n Remover o primeiro de qual pilha? ");
                printf("\n\t 1 = Pilha Impar. ");
                printf("\n\t 2 = Pilha Par. ");
                fflush(stdin); scanf("%i", &val);
                switch (val){
                case 1: pop(&Pilha1);printf("\n Removido!");break;
                case 2: pop(&Pilha2);printf("\n Removido!");break;
                }
            } else
                printf("\n Pilhas vazias, não há o que remover.");
        }
        printf("\n");
        system("pause");
        system("cls");
    } while (op!=0);
    return 0;
}//Fim main()
