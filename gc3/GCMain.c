#include "GCTypes.h"
#include "GCObj.h"
#include "GCPtr.h"
#include "GCStr.h"
#include <stdio.h>
void gcDbgPrint(GCPtr *p) {
  printf("%p %d\n", p, p->tt);
  if(p->tt == OBJ) {
    GCStr *obj = (GCStr *)(p->obj);
    printf("%p ", obj);
    printf("%s\n",  obj->vt->type);
    printf("%d %s\n",  obj->sz, obj->s);
  }
}
int main() {
  puts("welcome");
  initGCPtrvt();
  initGCStrvt();
  GCPtr ps = getGCStrvt()->create(getGCStrvt(), "hello world");
  gcDbgPrint(&ps);
  println((GCObj *)&ps);
  GCPtr pi = createInt(100);
  gcDbgPrint(&pi);
  println((GCObj *)&pi);
  GCPtr pd = createDbl(100.0);
  gcDbgPrint(&pd);
  println((GCObj *)&pd);
  GCPtr pcs = createStr("hello again");
  println((GCObj *)&pcs);
  GCPtr pr = createRef(&pcs);
  println((GCObj *)&pr);
  GCPtr prr = createRef(&pr);
  println((GCObj *)&prr);
  refRootPtr(&prr, &pr);
  refPtr(&pr, &pi);
  println((GCObj *)&pcs);
  println((GCObj *)&pr);
  println((GCObj *)&prr);
  printf("pcs:%p, pr:%p, prr:%p\n", &pcs, &pr, &prr);

  puts("bye");
  return 0;
}