#include <stdio.h>
#include <stdlib.h>

typedef struct objetos{
    int valor;
    int peso;
}objetos_t;

typedef struct presentes{
    int num_objetos;
    int p_max;
    objetos_t *objetos;
}presentes_t;

typedef struct saco{
    int tam;
    int valor;
    int *melhor_subcjt_gifts;
}saco_t;

/*Cria uma struct presentes_t e retorna um ponteiro para ela.*/
presentes_t *cria_presentes_t(){
    presentes_t *presentes = malloc(sizeof(presentes_t));
    presentes->num_objetos = 0;
    presentes->p_max = 0;
    presentes->objetos = NULL;

    return presentes;
}

/*Destroi struct @presentes.(grinch odeia natal)*/
presentes_t *grinch(presentes_t *presentes){
    free(presentes->objetos);
    free(presentes);

    return NULL;
}

/*Le os objetos e coloca na struct @presentes.*/
void le_presentes(presentes_t *presentes){
    scanf("%d %d", &presentes->num_objetos, &presentes->p_max);
    presentes->objetos = malloc(sizeof(objetos_t)*presentes->num_objetos);
    for (int i = 0; i < presentes->num_objetos; i++) {
        scanf("%d %d", &presentes->objetos[i].valor, &presentes->objetos[i].peso);
    }
}

/*Imprime informacoes sobre os presentes.*/
void imprime_presentes(presentes_t *prese){
    system("clear");
    printf ("\nNumero de objetos: %d\n", prese->num_objetos);
    printf ("Peso maximo: %d\n", prese->p_max);
    printf ("\nNº objeto -> valor  peso\n");
    for (int i = 0; i < prese->num_objetos; i++) {
        printf ("   %dº obj -> %5d %5d\n", i+1, prese->objetos[i].valor, prese->objetos[i].peso);
    }
    printf ("\n");
}

/*Devolve o peso do saco.*/
int peso_do_saco(saco_t *saco, presentes_t *prese){
    int peso = 0;
    for (int i = 0; i < saco->tam; i++) {
        peso += prese->objetos[saco->melhor_subcjt_gifts[i]].peso;
    }

    return peso;
}

/*Devolve o valor do saco.*/
int valor_do_saco(saco_t *saco, presentes_t *prese){
    int valor = 0;
    for (int i = 0; i < saco->tam; i++) {
        valor += prese->objetos[saco->melhor_subcjt_gifts[i]].valor;
    }

    return valor;
}

/*Passa informacoes do novo melhor saco.*/
void atualiza_melhor_saco(saco_t *saco, saco_t *novo_saco){
    saco->valor = novo_saco->valor;
    saco->tam = novo_saco->tam;
    free(saco->melhor_subcjt_gifts);
    saco->melhor_subcjt_gifts = novo_saco->melhor_subcjt_gifts;
}

/*Compara dois sacos e atualiza o melhor.*/
void compara_sacos(saco_t *saco, saco_t *aux_saco, presentes_t *prese){
    int peso = peso_do_saco(aux_saco, prese);
    aux_saco->valor = valor_do_saco(aux_saco, prese);

    if (peso > prese->p_max){
        free(aux_saco->melhor_subcjt_gifts);
        return;
    }
    if (aux_saco->valor > saco->valor){
        atualiza_melhor_saco(saco, aux_saco);
        return;
    }
    else if (aux_saco->valor == saco->valor && peso < peso_do_saco(saco, prese)) {
        atualiza_melhor_saco(saco, aux_saco);
        return;
    }

    free(aux_saco->melhor_subcjt_gifts);
}

/*Cria o subconjunto de presentes da vez.*/
void analisa_subconjunto(int *vet, presentes_t *presentes, saco_t *cria_melhor_saco){
    saco_t *aux_saco = malloc(sizeof(saco_t));
    aux_saco->melhor_subcjt_gifts = malloc(sizeof(int)*presentes->num_objetos);
    aux_saco->tam = 0;
    for (int i = 0; i < presentes->num_objetos; i++) {
        if (vet[i] == 1){
            aux_saco->melhor_subcjt_gifts[aux_saco->tam] = i;
            aux_saco->tam++;
        }
    }
    compara_sacos(cria_melhor_saco, aux_saco, presentes);
    free(aux_saco);
}

/*Cria todos os subconjuntos de presentes com backtracking.*/
void acha_melhor_subconjunto_gifts(int *vet, presentes_t *prese, int indice, saco_t *saco){
    if (indice == prese->num_objetos){
        analisa_subconjunto(vet, prese, saco);
        return;
    }
    vet[indice] = 0;
    acha_melhor_subconjunto_gifts(vet, prese, indice+1, saco);
    vet[indice] = 1;
    acha_melhor_subconjunto_gifts(vet, prese, indice+1, saco);
}

/*Retorna uma struct saco_t com o melhor subconjunto dos presentes.*/
saco_t *cria_melhor_saco(presentes_t *presentes){
    if (presentes->objetos == NULL)
        return NULL;
    int vet[presentes->num_objetos];
    saco_t *saco = malloc(sizeof(saco_t));
    saco->valor = -1;
    saco->tam = 0;
    saco->melhor_subcjt_gifts = NULL;

    acha_melhor_subconjunto_gifts(vet, presentes, 0, saco);

    return saco;
}

/*Destroi struct saco_t.*/
saco_t *destroi_saco(saco_t *saco){
    free(saco->melhor_subcjt_gifts);
    free(saco);

    return NULL;
}

/*Imprime os presentes e o valor do saco.*/
void imprime_saco (saco_t *saco){
    for (int i = 0; i < saco->tam; i++) {
        printf ("%d ", saco->melhor_subcjt_gifts[i]+1);
    }
    printf ("\n%d\n", saco->valor);
}

/*Imprime os presentes e o valor do saco de forma mais detalhada.*/
void imprime_saco_detalhado (saco_t *saco){
    printf ("Objetos escolhidos: ");
    for (int i = 0; i < saco->tam; i++) {
        printf ("%dº ", saco->melhor_subcjt_gifts[i]+1);
    }
    printf ("\nValor total: %d\n", saco->valor);
}

int main(){
    presentes_t *presentes = cria_presentes_t();
    le_presentes(presentes);
    imprime_presentes(presentes);

    saco_t *saco = cria_melhor_saco(presentes);
    /* imprime_saco(saco); */
    imprime_saco_detalhado(saco);

    presentes = grinch(presentes);
    saco = destroi_saco(saco);

    return 0;
}
