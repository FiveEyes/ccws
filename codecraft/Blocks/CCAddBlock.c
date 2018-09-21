#include "CCAddBlock.h"
#include <stdio.h>
int CCAddBlock_isEnable(CCPureBlock *block) {
  return isRef(&(block->outBuff[0]));
}

void CCAddBlock_apply(CCPureBlock *block) {
  GCPtr *pa = getRef(&(block->inRef[0]));
  GCPtr *pb = getRef(&(block->inRef[1]));
  int a = getInt(pa);
  int b = getInt(pb);
  Call(pa, freeItem);
  Call(pb, freeItem);
  //printf("adding %d %d\n", a, b);
  block->outBuff[0] = createInt(a+b);
}