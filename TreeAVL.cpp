#include <stdio.h>
#include <stdlib.h>

struct Tree {
    int info;
    Tree *esq, *dir;
};

typedef struct Tree tree;

tree* criaNo(int info) {
    tree* novo = (tree*)malloc(sizeof(tree));
    if (novo != NULL) {
        novo->info = info;
        novo->esq = novo->dir = NULL;
    }
    return novo;
}

void rotacao_esquerda(tree **p) {
    tree *q, *temp;
    q = (*p)->dir;
    temp = q->esq;
    q->esq = *p;
    (*p)->dir = temp;
    *p = q;
}

void rotacao_direita(tree **p) {
    tree *q, *temp;
    q = (*p)->esq;
    temp = q->dir;
    q->dir = *p;
    (*p)->esq = temp;
    *p = q;
}

void calc_altura(tree *raiz, int n, int *maior) {
    if (raiz != NULL) {
        if (n > *maior) 
            *maior = n;
        calc_altura(raiz->esq, n + 1, maior);
        calc_altura(raiz->dir, n + 1, maior);
    }
}

int altura(tree* raiz) {
    int maior = 0;
    calc_altura(raiz, 1, &maior);
    return maior;
}

void insereAVL(tree **raiz, int info, int *flag) {
    int fb, fb_filho;
    if (*raiz == NULL) {
        *raiz = criaNo(info);
        *flag = 0;
    } else {
        if (info < (*raiz)->info) {
            insereAVL(&(*raiz)->esq, info, flag);
        } else {
            insereAVL(&(*raiz)->dir, info, flag);
        }
    }

    if (!*flag) {
        fb = altura((*raiz)->dir) - altura((*raiz)->esq);
        if (fb == 2) {
            *flag = 1;
            fb_filho = altura((*raiz)->dir->dir) - altura((*raiz)->dir->esq);
            if (fb_filho == 1) {
                rotacao_esquerda(raiz);
            } else {
                rotacao_direita(&(*raiz)->dir);
                rotacao_esquerda(raiz);
            }
        } else if (fb == -2) {
            *flag = 1;
            fb_filho = altura((*raiz)->esq->dir) - altura((*raiz)->esq->esq);
            if (fb_filho == -1) {
                rotacao_direita(raiz);
            } else {
                rotacao_esquerda(&(*raiz)->esq);
                rotacao_direita(raiz);
            }
        }
    }
}

void exibirArvore(tree *raiz) {
    if (raiz != NULL) {
        exibirArvore(raiz->esq);
        printf("%d ", raiz->info);
        exibirArvore(raiz->dir);
    }
}

int main() {
    tree *raiz = NULL;
    int flag = 0;

    insereAVL(&raiz, 10, &flag);
    insereAVL(&raiz, 20, &flag);
    insereAVL(&raiz, 30, &flag);
    insereAVL(&raiz, 25, &flag);
    insereAVL(&raiz, 15, &flag);
    insereAVL(&raiz, 5, &flag);

    printf("Arvore AVL em ordem crescente: ");
    exibirArvore(raiz);

    return 0;
}


