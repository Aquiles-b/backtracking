#include <stdio.h>
#include <stdlib.h>

typedef struct gift{
    int valor;
    int peso;
}gift_t;

typedef struct presentes{
    int num_gifts;
    int p_max;
    gift_t *gifts;
}presentes_t;

typedef struct saco{
    int tam;
    int valor;
    int *melhor_subcjt_gifts;
}saco_t;

/*Cria uma struct presentes_t e retorna um ponteiro para ela.*/
presentes_t *cria_presentes_t(){
    presentes_t *presentes = malloc(sizeof(presentes_t));
    presentes->num_gifts = 0;
    presentes->p_max = 0;
    presentes->gifts = NULL;

    return presentes;
}

/*Destroi struct @presentes.(grinch odeia natal)*/
presentes_t *grinch(presentes_t *presentes){
    free(presentes->gifts);
    free(presentes);

    return NULL;
}

/*Le os gifts e coloca na struct @presentes.*/
void le_presentes(presentes_t *presentes){
    scanf("%d", &presentes->num_gifts);
    scanf("%d", &presentes->p_max);
    presentes->gifts = malloc(sizeof(gift_t)*presentes->num_gifts);
    for (int i = 0; i < presentes->num_gifts; i++) {
        scanf("%d %d", &presentes->gifts[i].valor, &presentes->gifts[i].peso);
    }
}

/*Debug*/
void imprime_presentes(presentes_t *prese){
    printf ("%d\n", prese->num_gifts);
    printf ("%d\n", prese->p_max);
    for (int i = 0; i < prese->num_gifts; i++) {
        printf ("%d %d\n", prese->gifts[i].valor, prese->gifts[i].peso);
    }
}

/*Cria o subconjunto de presentes da vez.*/
void analisa_subconjunto(int *vet, presentes_t *presentes, saco_t *melhor_saco){
    saco_t aux_saco;
    aux_saco.melhor_subcjt_gifts = malloc(sizeof(presentes->num_gifts));
    aux_saco.tam = 0;
    for (int i = 0; i < presentes->num_gifts; i++) {
        if (vet[i] == 1)
            aux_saco.melhor_subcjt_gifts[aux_saco.tam++] = i+1;
    }

    free(aux_saco.melhor_subcjt_gifts);
}

/*Cria todos os subconjuntos de presentes.*/
void acha_melhor_subconjunto_gifts(int *vet, presentes_t *prese, int indice, saco_t *saco){
    if (indice == prese->num_gifts){
        analisa_subconjunto(vet, prese, saco);
        return;
    }
    vet[indice] = 0;
    acha_melhor_subconjunto_gifts(vet, prese, indice+1, saco);
    vet[indice] = 1;
    acha_melhor_subconjunto_gifts(vet, prese, indice+1, saco);
}

/*Retorna uma struct saco_t com o melhor subconjunto dos presentes.*/
saco_t *melhor_saco(presentes_t *presentes){
    int vet[presentes->num_gifts];
    saco_t *saco = malloc(sizeof(saco_t));
    saco->melhor_subcjt_gifts = malloc(sizeof(presentes->num_gifts));

    acha_melhor_subconjunto_gifts(vet, presentes, 0, saco);
    
    return saco;
}

int main(){
    int tam;
    presentes_t *presentes = cria_presentes_t();
    /* le_presentes(presentes); */

    grinch(presentes);

    return 0;
}
