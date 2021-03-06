#include <stdio.h>
#include <stdlib.h>
#include <string.h>
DataBase addDataBase (DataBase db, DataBase novo) { 
    if (db == NULL) return novo;
    if (strcmp(db->name, novo->name) > 0) 
       db->esquerda = addDataBase (db->esquerda, novo);
    else if (strcmp(db->name, novo->name) < 0)
       db->direita = addDataBase (db->direita, novo);
    return db;
}
void printDataBases (DataBase raiz) {
   if (raiz != NULL) {
      if (strcmp(raiz->name, "NNNNNNNNNNNNNNNNNN"))
         printf ("%s\n", raiz->name);
      printDataBases (raiz->esquerda);
      printDataBases(raiz->direita);
   }
}
void printTables (Table raiz) {
   if (raiz != NULL) {
      if (strcmp(raiz->name, "NNNNNNNNNNNNNNNNNN"))
         printf ("%s\n", raiz->name);
      printTables (raiz->esquerda);
      printTables(raiz->direita);
   }
}
void printCollumns (Collumn raiz) {
   if (raiz != NULL) {
      if (strcmp(raiz->name, "NNNNNNNNNNNNNNNNNN"))
         printf ("%s\n", raiz->name);
      printCollumns (raiz->esquerda);
      printCollumns(raiz->direita);
   }
}
void printCollumnsCompleto (Collumn raiz) {
   if (raiz != NULL) {
      if (strcmp(raiz->name, "NNNNNNNNNNNNNNNNNN"))
         printf ("| %s | %s |\n", raiz->name, raiz->tipo);
      printCollumnsCompleto (raiz->esquerda);
      printCollumnsCompleto(raiz->direita);
   }
}
Table addTable (Table db, Table novo) { 
    if (db == NULL) return novo;
    if (strcmp(db->name, novo->name) > 0) 
       db->esquerda = addTable (db->esquerda, novo);
    else if (strcmp(db->name, novo->name) < 0)
       db->direita = addTable (db->direita, novo);
    return db;
}
Collumn addCollumn (Collumn db, Collumn novo) { 
   //printf("Adicionando collumn\n");
    if (db == NULL) return novo;
    if (strcmp(db->name, novo->name) > 0) 
       db->esquerda = addCollumn (db->esquerda, novo);
    else if (strcmp(db->name, novo->name) < 0)
       db->direita = addCollumn (db->direita, novo);
    return db;
}
 DataBase removeraizDatabase (DataBase r) {  
    struct database *p, *q;
    if (r->esquerda == NULL) {
       q = r->direita;
       free (r);  
       return q;
    }
    p = r; q = r->esquerda;
    while (q->direita != NULL) {
       p = q; q = q->direita;
    }
    // q é nó anterior a r na ordem e-r-d
    // p é pai de q
    if (p != r) {
       p->direita = q->esquerda;
       q->esquerda = r->esquerda;
    }
    q->direita = r->direita;
    free (r);
    return q;
}
Table removeraizTable (Table r) {  
    struct table *p, *q;
    if (r->esquerda == NULL) {
       q = r->direita;
       free (r);
       return q;
    }
    p = r; q = r->esquerda;
    while (q->direita != NULL) {
       p = q; q = q->direita;
    }
    // q é nó anterior a r na ordem e-r-d
    // p é pai de q
    if (p != r) {
       p->direita = q->esquerda;
       q->esquerda = r->esquerda;
    }
    q->direita = r->direita;
    free (r);
    return q;
}
Collumn removeraizCollumn (Collumn r) {  
    Collumn p, q;
    if (r->esquerda == NULL) {
       q = r->direita;
       free (r);
       return q;
    }
    p = r; q = r->esquerda;
    while (q->direita != NULL) {
       p = q; q = q->direita;
    }
    // q é nó anterior a r na ordem e-r-d
    // p é pai de q
    if (p != r) {
       p->direita = q->esquerda;
       q->esquerda = r->esquerda;
    }
    q->direita = r->direita;
    free (r);
    return q;
}
DataBase buscaDataBase (DataBase r, char *k) {
    if (r == NULL || strcmp(r->name,k) == 0)
       return r;
    if (strcmp (r->name, k) > 0)
       return  buscaDataBase (r->esquerda, k);
    else
       return buscaDataBase (r->direita, k);
}
Table buscaTable (Table r, char *k) {
    if (r == NULL || strcmp(r->name,k) == 0)
       return r;
    if (strcmp (r->name, k) > 0)
       return  buscaTable (r->esquerda, k);
    else
       return buscaTable (r->direita, k);
}
Collumn buscaCollumn (Collumn r, char *k) {
    if (r == NULL || strcmp(r->name,k) == 0)
       return r;
    if (strcmp (r->name, k) > 0)
       return  buscaCollumn (r->esquerda, k);
    else
       return buscaCollumn (r->direita, k);
}
int numeroDeColunas (Collumn r) {
   if (r != NULL) {
      return numeroDeColunas (r->direita) + numeroDeColunas (r->esquerda) + 1;
   }
   return 0;
}
char * getNomeColunas (Collumn r) {
   if (r != NULL) {  
      char * aux;
      aux = malloc(10000 * sizeof(char));
      strcpy (aux, ",");
      strcat (aux, r->name);
      strcat (aux, getNomeColunas(r->direita));
      strcat (aux, getNomeColunas(r->esquerda));
      return aux;
   }
   return ",";
}
DataBase removeDatabase (DataBase r, char *k) {
    if (r == NULL || strcmp(r->name,k) == 0)
        return removeraizDatabase(r);
    if (strcmp (r->name, k) > 0)
       r->esquerda =  removeDatabase (r->esquerda, k);
    else
       r->direita = removeDatabase (r->direita, k);
}
Table removeTable (Table r, char *k) {
    if (r == NULL || strcmp(r->name,k) == 0)
        return removeraizTable(r);
    if (strcmp (r->name, k) > 0)
       r->esquerda =  removeTable (r->esquerda, k);
    else
       r->direita = removeTable (r->direita, k);
}
Collumn removeCollumn (Collumn r, char *k) {
    if (r == NULL || strcmp(r->name,k) == 0)
        return removeraizCollumn(r);
    if (strcmp (r->name, k) > 0)
       r->esquerda =  removeCollumn (r->esquerda, k);
    else
       r->direita = removeCollumn (r->direita, k);
}
/* Lista encadeada */
/* Boolean */
void 
insereBoolean (Booleano p, bool x)
{
   Booleano nova, aux;
   aux = p;
   while (aux->proximo != NULL) aux = aux->proximo;
   nova = malloc (sizeof (struct boolean));
   nova->valor = x;
   nova->id = aux->id + 1;
   nova->proximo = aux->proximo;
   aux->proximo = nova;
}
void restoreBoolean (Booleano p, Booleano novo) {
   Booleano aux;
   aux = p;
   while (aux->proximo != NULL) aux = aux->proximo;
   aux->proximo = novo;
}
void printListBooleano(Booleano lista){
    Booleano aux;
    aux = lista;
    while (aux != NULL) {
        printf("%d %d\n",aux->id, aux->valor);
        aux = aux->proximo;
    }
}
int * listarIdOfCollumnBoolean (Booleano lista,   int *ids) {
   Booleano aux;
    aux = lista;
    int i = 0;
    while (aux != NULL) {
       ids[i++] = aux->id;
        aux = aux->proximo;
    }
    return ids;
}
int * listarIdOfCollumnBooleanByValor (Booleano lista, int *ids, char * valor) {
   Booleano aux;
    aux = lista;
    int i = 0;
    while (aux != NULL) {
       if (strcmp (valor, "TRUE") == 0 && aux->valor) ids[i++] = aux->id;
       if (strcmp (valor, "FALSE") == 0 && !aux->valor) ids[i++] = aux->id;
        aux = aux->proximo;
    }
    return ids;
}
int getTamanhoListaBoolean (Booleano lista) {
   Booleano aux = lista;
   int qnt = 0;
   while (aux != NULL) {
       qnt++;
        aux = aux->proximo;
    }
    return qnt;
}
Booleano
buscaBooleanoByValor (int x, Booleano le)
{
    Booleano p;
   p = le;
   while (p != NULL && p->valor != x) 
      p = p->proximo; 
   return p;
}
Booleano
buscaBooleanById (int x, Booleano le)
{
    Booleano p;
   p = le;
   while (p != NULL && p->id != x) 
      p = p->proximo; 
   return p;
}
void 
removeBooleanById (Booleano p, unsigned int x)
{
   Booleano lixo, aux;
   aux = p;
   lixo = p->proximo;
   while (lixo != NULL && lixo->id != x) {
       aux = lixo;
       lixo = lixo->proximo;
   }
   if (lixo == NULL)
        return;
   aux->proximo = lixo->proximo;
   free (lixo);
}
void 
removeBooleanByValor (Booleano p, int x)
{
   Booleano lixo, aux;
   aux = p;
   lixo = p->proximo;
   while (lixo != NULL && lixo->valor != x) {
       aux = lixo;
       lixo = lixo->proximo;
   }
   if (lixo == NULL)
        return;
   aux->proximo = lixo->proximo;
   free (lixo);
}

/* Integer */
void 
insereInteger (Integer p, int x)
{
   Integer nova, aux;
   aux = p;
   while (aux->proximo != NULL) aux = aux->proximo;
   nova = malloc (sizeof (struct integer));
   nova->valor = x;
   nova->id = aux->id + 1;
   nova->proximo = aux->proximo;
   aux->proximo = nova;
}
void restoreInteger (Integer p, Integer novo) {
   Integer aux;
   aux = p;
   while (aux->proximo != NULL) aux = aux->proximo;
   aux->proximo = novo;
}
void printList(Integer lista){
    Integer aux;
    aux = lista;
    while (aux != NULL) {
        printf("%d %d\n",aux->id, aux->valor);
        aux = aux->proximo;
    }
}
int * listarIdOfCollumnInteger (Integer lista,   int *ids) {
   Integer aux;
    aux = lista;
    int i = 0;
    while (aux != NULL) {
       ids[i++] = aux->id;
        aux = aux->proximo;
    }
    return ids;
}
int * listarIdOfCollumnIntegerByValor (Integer lista, int *ids, int valor, char op) {
   Integer aux;
    aux = lista;
    int i = 0;
    
    while (aux != NULL) {
       if (op == '=') {
          if (valor == aux->valor) ids[i++] = aux->id;
       }
        if (op == '>') {
          if (valor < aux->valor) ids[i++] = aux->id;
       }
        if (op == '<') {
          if (valor > aux->valor) ids[i++] = aux->id;
       }
       
        aux = aux->proximo;
    }
    return ids;
}
int getTamanhoListaInteger (Integer lista) {
   Integer aux = lista;
   int qnt = 0;
   while (aux != NULL) {
       qnt++;
        aux = aux->proximo;
    }
    return qnt;
}
Integer
buscaIntegerByValor (int x, Integer le)
{
    Integer p;
   p = le;
   while (p != NULL && p->valor != x) 
      p = p->proximo; 
   return p;
}
Integer
buscaIntegerById (int x, Integer le)
{
    Integer p;
   p = le;
   while (p != NULL && p->id != x) 
      p = p->proximo; 
   return p;
}
void 
removeIntegerById (Integer p, unsigned int x)
{
   Integer lixo, aux;
   aux = p;
   lixo = p->proximo;
   while (lixo != NULL && lixo->id != x) {
       aux = lixo;
       lixo = lixo->proximo;
   }
   if (lixo == NULL)
        return;
   aux->proximo = lixo->proximo;
   free (lixo);
}
void 
removeIntegerByValor (Integer p, int x)
{
   Integer lixo, aux;
   aux = p;
   lixo = p->proximo;
   while (lixo != NULL && lixo->valor != x) {
       aux = lixo;
       lixo = lixo->proximo;
   }
   if (lixo == NULL)
        return;
   aux->proximo = lixo->proximo;
   free (lixo);
}

