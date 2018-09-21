#pragma once
#include "GCPtr.h"

struct GCStrvt;

typedef struct GCStr {
  struct GCStrvt *vt;
	unsigned int sz;
	char s[1];
} GCStr;

struct GCStrvt {
  GCObjvtHeader(struct GCStrvt, struct GCStr);
};


GCPtr GCStr_create(struct GCStrvt *vt, const char *data);
GCPtr GCStr_copy(GCStr *ptr);
void GCStr_free(GCStr *ptr);
GCPtr GCStr_toStr(GCStr *ptr);

void initGCStrvt();
struct GCStrvt * getGCStrvt();