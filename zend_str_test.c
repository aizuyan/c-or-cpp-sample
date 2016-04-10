// Example program
#include<stdio.h>
#include<string.h>
#include<malloc.h>
typedef struct _zend_string{
	size_t len;
	char val[1];
} zend_string;

static zend_string *zend_string_init(const char *, size_t);
static zend_string *zend_string_alloc(size_t);

static zend_string *zend_string_init(const char *str, size_t len)
{
	zend_string *ret = zend_string_alloc(len);

	memcpy(ret->val, str, len);
	ret->len = len;
	ret->val[len] = '\0';
	return ret;
}

static zend_string *zend_string_alloc(size_t len)
{
	zend_string *ret = (zend_string*)malloc(sizeof(size_t) + len);
	return ret;
}

int main()
{
  char const *src = "我是吴彦祖！";
  zend_string *zs = zend_string_init(src, strlen(src) + 1);
  printf("%s\n%d\n%d\n%d\n%d\n", zs->val, zs->len, sizeof(size_t), sizeof("我是吴彦祖！"), strlen(src));
}
