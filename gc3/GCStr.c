#include "GCHeader.h"
#include "GCStr.h"

GCPtr GCStr_create(struct GCStrvt *vt, const char *data) {
  int len = strlen(data);
  GCStr *p = (GCStr *)GCMake(sizeof(GCStr) + sizeof(char) * len);
  p->vt = getGCStrvt();
  p->sz = len;
  strcpy(p->s, data);

  return getGCPtrvt()->create(getGCPtrvt(), OBJ, p);
}

GCPtr GCStr_copy(GCStr *ptr) {
  GCPtr ret;

  GCStr *p = (GCStr *)GCMake(sizeof(GCStr) + sizeof(char) * (ptr->sz));
  p->vt = ptr->vt;
  p->sz = ptr->sz;
  strcpy(p->s, ptr->s);

  return getGCPtrvt()->create(getGCPtrvt(), OBJ, p);
}

void GCStr_free(GCStr *ptr) {
  GCFree(ptr);
}

GCPtr GCStr_toStr(GCStr *ptr) {
  return getGCPtrvt()->create(getGCPtrvt(), OBJ, ptr);
}


struct GCStrvt gcStrvt;

void initGCStrvt() {
  InitGCObjvtHeader(&gcStrvt, GCStr, "Str");
  /*
  gcStrvt.create = GCStr_create;
  gcStrvt.copy = GCStr_copy;
  gcStrvt.free = GCStr_free;
  gcStrvt.type = "Str";
  */
}

struct GCStrvt * getGCStrvt() {
  return &gcStrvt;
}
