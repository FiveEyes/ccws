#pragma once
#include "GCTypes.h"

#define GCObjvtHeader(VT,OBJ) \
  GCPtr (*create)(VT *vt, ...); \
  GCPtr (*copy)(OBJ *ptr); \
  void (*free)(OBJ *ptr); \
  GCPtr (*toStr)(OBJ *ptr); \
  const char *type

#define InitGCObjvtHeader(var,prefix,typename) \
  (var)->create = prefix##_create; \
  (var)->copy = prefix##_copy; \
  (var)->free = prefix##_free; \
  (var)->toStr = prefix##_toStr; \
  (var)->type = typename

//#define Call(this,method) (this)->vt->method(this)
#define Call(this,method,...) (this)->vt->method(this,##__VA_ARGS__)

struct GCObjvt;

typedef struct GCObj {
  struct GCObjvt *vt;
} GCObj;

struct GCObjvt {
  GCObjvtHeader(struct GCObjvt, GCObj);
};

void * GCMake(unsigned int sz);

void GCFree(void *p);

GCPtr toStr(GCObj *p);

void print(GCObj *p);
void println(GCObj *p);