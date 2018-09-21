#pragma once
#include "GCTypes.h"
#include "GCObj.h"

#define GCPtrvtHeader(VT) \
  GCObjvtHeader(VT,GCPtr); \
  void (*freeItem)(GCPtr *ptr)

#define InitGCPtrvtHeader(var,prefix,type) \
  InitGCObjvtHeader(var,prefix,type); \
  (var)->freeItem = prefix##_freeItem

#define Call(this,method,...) (this)->vt->method(this,##__VA_ARGS__)

#define CallPtr(type,this,method,...) \
	(((type *)((this)->obj))->vt->method((type *)((this)->obj),##__VA_ARGS__))
  
struct GCPtrvt;

enum GCType {
  REF = 0,
  INT,
  DBL,
  STR,
  OBJ
};

extern const char * GCTypeStr[];

typedef struct GCPtr {
  struct GCPtrvt *vt;
  enum GCType tt;
  union {
    struct GCPtr *ref;
    int i;
    double d;
    const char *s;
    GCObj *obj;
  };
} GCPtr;

typedef struct GCPtrvt {
	GCPtrvtHeader(struct GCPtrvt);
} GCPtrvt;

// GCPtr create(struct GCObjvt *vt, enum GCType tt, void *data);
// GCPtr copy(GCPtr *ptr); 
// void free(GCPtr *ptr);
// void freeItem(GCPtr *ptr);

void initGCPtrvt();

GCPtr getNullPtr();

GCPtrvt * getGCPtrvt();

GCPtr createRef(GCPtr *p);
GCPtr createInt(int i);
GCPtr createDbl(double d);
GCPtr createStr(const char *s);
GCPtr createObj(GCObj *obj);


int isRef(GCPtr *p);

char movPtr(GCPtr *d, GCPtr *s);
char cpyPtr(GCPtr *d, GCPtr *s);
char refPtr(GCPtr *d, GCPtr *s);

GCPtr * getRootPtr(GCPtr *p);
char movRootPtr(GCPtr *d, GCPtr *s);
char refRootPtr(GCPtr *d, GCPtr *s);


GCPtr * getRef(GCPtr *p);
int getInt(GCPtr *p);
double getDbl(GCPtr *p);
const char * getStr(GCPtr *p);
GCObj * getObj(GCPtr *p);

