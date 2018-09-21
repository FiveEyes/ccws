#include <stdio.h>
#include "CCHeader.h"
#include "Blocks/CCAddBlock.h"

//typedef GCPtr (*CreateFuncR)(struct GCPtrvt *vt, ...);


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
  GCPtr px = createInt(1);
  println((GCObj *)&px);
  GCPtr py = createInt(1);
  println((GCObj *)&py);


  CCPureBlockvt *vt = createCCPureBlockvt(CCAddBlock_isEnable, CCAddBlock_apply, 2, 1, "Add");
  GCPtr addblock = vt->create(vt);
  CallPtr(CCPureBlock,&addblock,set,0,&px);
  CallPtr(CCPureBlock,&addblock,set,1,&py);
  GCPtr * pz = CallPtr(CCPureBlock,&addblock,get,0);
  gcDbgPrint(pz);
  CallPtr(CCPureBlock,&addblock,apply);
  println((GCObj *)pz);
  gcDbgPrint(&px);
  gcDbgPrint(&py);
  println((GCObj *)&px);
  println((GCObj *)&py);

  CallPtr(CCPureBlock,&addblock,set,0,pz);
  CallPtr(CCPureBlock,&addblock,set,1,pz);
  while(getchar()) {
    CallPtr(CCPureBlock,&addblock,apply);
    println((GCObj *)pz);
  }
  return 0;
}