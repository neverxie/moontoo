#include "all.h"

/* ---------------------- moontu list start ---------------------- */

#define mt_offset_of(type, member) ((int)&(((type *)0)->member))

#define mt_container_of(ptr, type, member) ({ \
		const typeof(((type *)0)->member) *__ptr = (ptr);\
		(type *)((char *)__ptr - mt_offset_of(type, member));})

struct mt_list_node {
	struct mt_list_node *next;
	struct mt_list_node *prev;
};
typedef struct mt_list_node mt_list_t;

static inline void mt_list_init(mt_list_t *l) {
	l->next = l;
	l->prev = l;
}

static inline mt_list_insert_after(mt_list_t *l, mt_list_t *n) {
	l->next->prev = n;
	n->next = l->next;

	l->next = n;
	n->prev = l;
}
static inline mt_list_insert_before(mt_list_t *l, mt_list_t *n) {}

#define mt_list_entry(node, type, member) \
	mt_container_of(node, type, member)

/* ----------------------- moontu list end ----------------------- */

struct stu {
	char *name;
	unsigned int num;
	struct mt_list_t l;
};

static struct stu *__create() {}
static void __destroy() {}

struct stu *stu_reg() {}
void stu_unreg() {}
void stu_find() {}
void stu_print() {}

void main(void) {
	int i;
	int sum = 0;
	struct stu a;

	for (i = 1; i <= 100; i++) {
		sum += i;
	}
	printf("1 + 2 + ... + 100 = %d\n", sum);
	printf("hello world!\n");
	int offset = mt_offset_of(struct stu, name);
	printf("offset: %d\n", offset);
	offset = mt_offset_of(struct stu, num);
	printf("offset: %d\n", offset);
	struct stu *p = mt_container_of(&(a.num), struct stu, num);
	printf("%x\n", p);
}

