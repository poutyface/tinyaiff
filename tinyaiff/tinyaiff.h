#ifndef _tinyaiff_h
#define _tinyaiff_h

#include <stdio.h>
#include <stdint.h>


enum {
  AIFF_FORMTYPE_AIFF = 1,
  AIFF_FORMTYPE_AIFC,
  AIFF_FORMTYPE_INVALID
};


typedef struct AIFF{
  FILE *fp;
  uint32_t filesize;
  int8_t formtype;
  int16_t channels;
  uint32_t sampleframes;
  int16_t samplesize;
  uint64_t samplerate;
  int8_t compressiontype[4];
  uint8_t foundcommonchunk;
  uint32_t readedsampleframes;
  uint32_t ssndstart;
}AIFF;


AIFF *aiff_open(char *file);
void aiff_close(AIFF *aiff);
uint32_t aiff_readframes(AIFF *aiff, uint32_t num, int8_t *data);
void aiff_rewind(AIFF *aiff);
uint32_t aiff_getfilesize(AIFF *aiff);
uint32_t aiff_getformtype(AIFF *aiff);
int16_t aiff_getchannels(AIFF *aiff);
uint32_t aiff_getsampleframes(AIFF *aiff);
int16_t aiff_getsamplesize(AIFF *aiff);
uint64_t aiff_getsamplerate(AIFF *aiff);
void aiff_getcompressiontype(AIFF *aiff, int8_t *type);
#endif
