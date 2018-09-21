#include "CCPureBlock.h"
//#include <stdio.h>

GCPtr CCPureBlock_create(CCPureBlockvt *vt) {
  CCPureBlock *block = (CCPureBlock *)GCMake(sizeof(CCPureBlock));
  block->vt = vt;
  block->inRef = (GCPtr *)GCMake(sizeof(GCPtr) * vt->inputSize);
  block->outBuff = (GCPtr *)GCMake(sizeof(GCPtr) * vt->outputSize);
  for(int i = 0; i < vt->inputSize; ++i) {
    block->inRef[i] = getNullPtr();
  }
  for(int i = 0; i < vt->outputSize; ++i) {
    //printf("init outBuff %d\n", i);
    block->outBuff[i] = getNullPtr();
  }
  return createObj((GCObj *)block);
}

GCPtr CCPureBlock_copy(CCPureBlock *b) {
  CCPureBlock *block = (CCPureBlock *)GCMake(sizeof(CCPureBlock));
  CCPureBlockvt *vt = b->vt;
  block->vt = vt;
  block->inRef = (GCPtr *)GCMake(sizeof(GCPtr) * vt->inputSize);
  block->outBuff = (GCPtr *)GCMake(sizeof(GCPtr) * vt->outputSize);
  for(int i = 0; i < vt->inputSize; ++i) {
    cpyPtr(block->inRef + i, b->inRef + i);
  }
  for(int i = 0; i < vt->outputSize; ++i) {
    cpyPtr(block->outBuff + i, b->outBuff + i);
  }
}

void CCPureBlock_free(CCPureBlock *block) {
  for(int i = 0; i < block->vt->outputSize; ++i) {
    Call(block->outBuff+i, freeItem);
  }
  GCFree(block->inRef);
  GCFree(block->outBuff);
}

GCPtr CCPureBlock_toStr(CCPureBlock *block) {
  return createStr(block->vt->type);
}

void CCPureBlock_set(CCPureBlock *block, int index, GCPtr *p) {
	block->inRef[index] = createRef(p);
}

GCPtr * CCPureBlock_get(CCPureBlock *block, int index) {
	//printf("get %p %d\n", block, index);
  return block->outBuff + index;
}

int CCPureBlock_size(CCPureBlock *block, int i) {
  switch(i) {
  case 0: return block->vt->outputSize;
  case 1: return 0;
  case 2: return block->vt->inputSize;
  }
  return 0;
}

int CCPureBlock_isEnabled(CCPureBlock *block) {
	return 1;
}

void CCPureBlock_apply(CCPureBlock *block) {

}


CCPureBlockvt * createCCPureBlockvt(CCPureBlockEnableFunc enable, CCPureBlockAppFunc apply, int inputSize, int outputSize, char *type) {
  CCPureBlockvt *vt = (CCPureBlockvt *)GCMake(sizeof(CCPureBlockvt));
  InitCCBlockvtHeader(vt,CCPureBlock,type);
  vt->inputSize = inputSize;
  vt->outputSize = outputSize;
  vt->isEnabled = enable;
  vt->apply = apply;
  return vt;
}



