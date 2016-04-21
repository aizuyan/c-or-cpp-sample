#include<string.h>
#include<malloc.h>
#include<stdio.h>

typedef struct _Bucket{
  void *value;
  char *key;
} Bucket;

typedef struct _zval{
  int age;
  char *name;
} Zval;
int main()
{
    const char *str = "Hello World!!";
    Bucket *tmp = (Bucket *)malloc(sizeof(Bucket));
    tmp->key = (char *)malloc(strlen(str) + 1);

    memcpy(tmp->key, str, strlen(str));
    tmp->key[strlen(str)] = '\0';

    char *name = "燕睿涛";
    Zval *zv;
    zv  = (Zval *)malloc(sizeof(Zval));
    zv->name = (char *)malloc(strlen(name) + 1);
    memcpy((char *)zv->name, name, strlen(name));
    zv->name[strlen(name)] = '\0';
    zv->age = 24;

    tmp->value = zv;
    printf("%s\n%d\n", tmp->key, zv->age);
    free(tmp->key);
    free(tmp);
    free(zv->name);
    free(zv);
}
