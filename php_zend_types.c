### php7中的结构体
typedef struct _Bucket {
  zval              val;
  zend_ulong        h;                /* hash value (or numeric index)   */
  zend_string      *key;              /* string key or NULL for numerics */
} Bucket;

### php7中的zend_string结构体
typedef struct _zend_string     zend_string;
struct _zend_string {
  zend_refcounted_h gc;
  zend_ulong        h;                /* hash value */
  size_t            len;
  char              val[1];
};

### php7中的类型
/* regular data types */
#define IS_UNDEF          0
#define IS_NULL           1
#define IS_FALSE          2
#define IS_TRUE           3
#define IS_LONG           4
#define IS_DOUBLE         5
#define IS_STRING         6
#define IS_ARRAY          7
#define IS_OBJECT         8
#define IS_RESOURCE         9
#define IS_REFERENCE        10

/* constant expressions */
#define IS_CONSTANT         11
#define IS_CONSTANT_AST       12

/* fake types */
#define _IS_BOOL          13
#define IS_CALLABLE         14

/* internal types */
#define IS_INDIRECT               15
#define IS_PTR            17

### php7中的zval
typedef struct _zval_struct zval;
typedef union _zend_value {
  zend_long         lval;       /* long value */
  double            dval;       /* double value */
  zend_refcounted  *counted;
  zend_string      *str;
  zend_array       *arr;
  zend_object      *obj;
  zend_resource    *res;
  zend_reference   *ref;
  zend_ast_ref     *ast;
  zval             *zv;
  void             *ptr;
  zend_class_entry *ce;
  zend_function    *func;
  struct {
    uint32_t w1;
    uint32_t w2;
  } ww;
} zend_value;

struct _zval_struct {
  zend_value        value;      /* value */
  union {
    struct {
      ZEND_ENDIAN_LOHI_4(
        zend_uchar    type,     /* active type */
        zend_uchar    type_flags,
        zend_uchar    const_flags,
        zend_uchar    reserved)     /* call info for EX(This) */
    } v;
    uint32_t type_info;
  } u1;
  union {
    uint32_t     var_flags;
    uint32_t     next;                 /* hash collision chain */
    uint32_t     cache_slot;           /* literal cache slot */
    uint32_t     lineno;               /* line number (for ast nodes) */
    uint32_t     num_args;             /* arguments number for EX(This) */
    uint32_t     fe_pos;               /* foreach position */
    uint32_t     fe_iter_idx;          /* foreach iterator index */
  } u2;
};
