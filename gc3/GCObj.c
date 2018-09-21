#include "GCHeader.h"
#include "GCObj.h"
#include "GCPtr.h"
#include "GCStr.h"

void * GCMake(unsigned int sz) {
  return malloc(sz);
}


void GCFree(void *p) {
  free(p);
}

GCPtr toStr(GCObj *p) {
  return p->vt->toStr(p);
}

void print(GCObj *obj) {
  GCPtr p = toStr(obj);
  if(p.tt == STR) { 
    printf("%s", p.s);
  } else if(p.tt == OBJ && strcmp(p.obj->vt->type, "Str") == 0) {
    printf("%s", ((GCStr *)(p.obj))->s);
  } else {
    printf("print error\n");
    printf("type: %s %s\n", GCTypeStr[p.tt], p.obj->vt->type);
  }
}

void println(GCObj *p) {
  print(p);
  puts("");
}