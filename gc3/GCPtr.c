#include "GCHeader.h"
#include "GCPtr.h"
#include "GCStr.h"

const char * GCTypeStr[] = {
  "Ref",
  "Int",
  "Dbl",
  "Str", //"StrConst",
  "Obj"
};


GCPtrvt gcPtrvt;

GCPtr getNullPtr() {
	static int flag = 1;
	static GCPtr nullPtr;
	if(flag) {
		nullPtr = createRef(NULL);
		flag = 0;
	}
	return nullPtr;
}

GCPtr GCPtr_create(struct GCPtrvt *vt, enum GCType tt, void *data) {
  GCPtr ret;
  ret.vt = vt;
  ret.tt = tt;
  switch(tt) {
  case REF: ret.ref = (struct GCPtr *)data; break;
  case INT: ret.i = *(int *)data; break;
  case DBL: ret.d = *(double *)data; break;
  case STR: ret.s = (const char *)data; break;
  case OBJ: ret.obj = (struct GCObj *)data; break;
  default: ret.ref = NULL;
  }
  return ret;
}


/*
GCPtr GCPtr_shallowCopy(GCPtr *p) {
  return *p;
}
*/

GCPtr GCPtr_copy(GCPtr *p) {
  if(p->tt != OBJ) {
    return *p;
  }
  return p->obj->vt->copy(p->obj);
}

void GCPtr_free(GCPtr *p) {
  p->vt->freeItem(p);
  GCFree(p);
}

void GCPtr_freeItem(GCPtr *p) {
  //printf("freeItem %p: ", p); println(p);
  if(p->tt == OBJ) {
    p->obj->vt->free(p->obj);
  }
  
  if(p->tt != REF) {
    *p = getNullPtr();
  }
  
}

GCPtr GCPtr_toStr(GCPtr *p) {
  char buff[100];
  GCStr *s;
  p = getRootPtr(p);
  switch(p->tt) {
  case STR:
    return *p;
  case OBJ:
    return p->obj->vt->toStr(p->obj);
  case INT:
    sprintf(buff, "%d", p->i);
    break;
  case DBL:
    sprintf(buff, "%lf", p->d);
    break;
  case REF:
    sprintf(buff, "%p", p->ref);
    break;
  }
  //printf("buff %s\n", buff);
  return getGCStrvt()->create(getGCStrvt(), buff);
}

void initGCPtrvt() {
  //unsigned int i;
  InitGCPtrvtHeader(&gcPtrvt, GCPtr, "Ptr");
}

 GCPtrvt * getGCPtrvt() {
  return &gcPtrvt;
}


GCPtr createRef(GCPtr *p) {
  return gcPtrvt.create(&gcPtrvt, REF, p);
}
GCPtr createInt(int i) {
  return gcPtrvt.create(&gcPtrvt, INT, &i);
}
GCPtr createDbl(double d) {
  return gcPtrvt.create(&gcPtrvt, DBL, &d);
}

GCPtr createStr(const char *s) {
  return gcPtrvt.create(&gcPtrvt, STR, s);
}

GCPtr createObj(GCObj *obj) {
  return gcPtrvt.create(&gcPtrvt, OBJ, obj);
}

int isRef(GCPtr *p) {
  return p->tt == REF;
}

char movPtr(GCPtr *d, GCPtr *s) {
  if(d == s) return 1;

  if(s->tt == REF) {
    return 0;
  }

  if(d->tt != REF) {
    GCPtr_freeItem(d);
  }
  
  *d = *s;
  s->tt = REF;
  s->ref = d;
  return 1;
}

char cpyPtr(GCPtr *d, GCPtr *s) {
  if(d == s) return 1;

  if(d->tt != REF) {
    GCPtr_freeItem(d);
  }

  s = getRootPtr(s);
  if(s == 0 || s->tt == REF) return 0;

  *d = GCPtr_copy(s);
  return 1;
}

char refPtr(GCPtr *d, GCPtr *s) {
  if(d == s) return 0;

  if(d->tt != REF) {
    GCPtr_freeItem(d);
  }

  d->tt = REF;
  d->ref = s;
  return 1;
}

GCPtr * getRootPtr(GCPtr *p) {
  GCPtr *nxt = p;
  while(nxt && nxt->tt == REF && nxt->ref) {
    nxt = nxt->ref;
    if(nxt == p) return 0;
  }
  return nxt; 
}

char movRootPtr(GCPtr *d, GCPtr *s) {
  s = getRootPtr(s);
  return movPtr(d, s);
}

char refRootPtr(GCPtr *d, GCPtr *s) {
  //printf("s: %p\n", s);
  s = getRootPtr(s);
  //printf("root: %p\n", s);
  return refPtr(d, s);
}


GCPtr * getRef(GCPtr *p) {
  if(p->tt != REF) {
    return 0;
  }
  return p->ref;
}

int getInt(GCPtr *p) {
  p = getRootPtr(p);
  if(p->tt != INT) {
    return 0;
  }
  return p->i;
}

double getDbl(GCPtr *p) {
  p = getRootPtr(p);
  if(p->tt != DBL) {
    return 0.0;
  }
  return p->d;
}

const char * getStr(GCPtr *p) {
  p = getRootPtr(p);
  if(p->tt != STR) {
	return NULL;
  }
  return p->s;
}
GCObj * getObj(GCPtr *p) {
  p = getRootPtr(p);
  if(p->tt != OBJ) {
	return NULL;
  }
  return p->obj;
}