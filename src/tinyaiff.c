#include "tinyaiff.h"
#include <stdlib.h>
#include <string.h>

static void getid(char *buf, FILE *fp)
{
  fread(buf, 1, 4, fp);
}

static int32_t get32be(FILE *fp)
{
  uint32_t d=0;
  fread(&d, 1, 4, fp);
  return (int32_t)((d >> 24) | ((d >> 8) & 0x0000FF00) | 
                   ((d << 8) & 0x00FF0000) | (d << 24));
}

static int16_t get16be(FILE *fp)
{
  uint16_t d=0;
  fread(&d, 1, 2, fp);
  return (int16_t)(((d >> 8) & 0x00FF) | ((d << 8) & 0x0FF0));
}


typedef struct AIFFExtFloat{
  uint8_t exponent[2];
  uint8_t mantissa[8];
}AIFFExtFloat;


static uint64_t getsamplerate(FILE *fp)
{
  AIFFExtFloat ext;
  uint64_t m = 0;
  int32_t e, i;

  fread(&ext, 1, 10, fp);

  for(i=0; i<8; i++)
    m = (m<<8) + ext.mantissa[i];

  e = (((int32_t)ext.exponent[0]&0x7F)<<8) | ext.exponent[1];

  if(e == 0x7FFF && m)
    return 0.0;

  e -= 16383 + 63;

  if(ext.exponent[0] & 0x80)
    m = -m;

  if(e > 0)
    m <<= e;
  else if(e < 0)
    m >>= -e;

  return m;
}


static int parseheader(AIFF *aiff)
{
  char id[4];
  char formtype[4];
  int32_t chunksize;

  getid(id, aiff->fp);
  if(strncmp(id, "FORM", 4) != 0){
    printf("invalid chunkid for FORM\n");
    return -1;
  }

  chunksize = get32be(aiff->fp) + 8;
  chunksize += chunksize & 1;
  aiff->filesize = chunksize;

  getid(formtype, aiff->fp);
  if(!strncmp(formtype, "AIFF", 4)){
    aiff->formtype = AIFF_FORMTYPE_AIFF;
  }
  else if(!strncmp(formtype, "AIFC", 4)){
    aiff->formtype = AIFF_FORMTYPE_AIFC;
  } 
  else{
    printf("invalid formtype %s\n", formtype);
    aiff->formtype = AIFF_FORMTYPE_INVALID;
    return -1;
  }

  return 0;
}


static int parsecommonchunk(AIFF *aiff)
{
  char id[4];
  int32_t chunksize;
  FILE *fp = aiff->fp;

  while(ftell(fp) != aiff->filesize){
    getid(id, fp);
    chunksize = get32be(fp);
    chunksize += chunksize & 1;

    if(!strncmp(id, "COMM", 4)){
      aiff->channels = get16be(fp);
      aiff->sampleframes = get32be(fp);
      aiff->samplesize = get16be(fp);
      aiff->samplerate = getsamplerate(fp);
      chunksize -= 18;
      if(aiff->formtype == AIFF_FORMTYPE_AIFC){
        getid((char*)aiff->compressiontype, fp);
        chunksize -= 4;
        // pass compression detail
      }
      aiff->foundcommonchunk = 1;
    }

    fseek(fp, chunksize, SEEK_CUR);

    if(aiff->foundcommonchunk)
      break;
  }  

  if(!aiff->foundcommonchunk){
    printf("not found common chunk\n");    
    return -1;
  }

  if(aiff->channels == 0){
    printf("invalid number of channels\n");
    return -1;
  }

  if(aiff->sampleframes == 0){
    printf("invalid number of sampleframes\n");
    return -1;
  }

  if(aiff->samplesize == 0){
    printf("invalid number of samplesize\n");
    return -1;
  }

  if(aiff->samplerate == 0){
    printf("invalid number of samplerate\n");
    return -1;
  }

  return 0;
}


static int skiptossndchunk(AIFF *aiff)
{
  char id[4];
  int32_t chunksize;
  uint32_t offset;
  uint32_t blocksize;
  FILE *fp = aiff->fp;

  while(ftell(fp) != aiff->filesize){
    getid(id, fp);
    chunksize = get32be(fp);
    chunksize += chunksize & 1;
    if(!strncmp(id, "SSND", 4)){
      offset = (uint32_t)get32be(fp);
      blocksize = (uint32_t)get32be(fp);
      fseek(fp, offset, SEEK_CUR);
      aiff->ssndstart = ftell(fp);
      return 0;
    }
    fseek(fp, chunksize, SEEK_CUR);
  }

  return -1;
}


AIFF *aiff_open(char *file)
{
  int rc;
  AIFF *aiff;

  aiff = (AIFF*)malloc(sizeof(*aiff));
  if(!aiff)
    return NULL;

  aiff->fp = fopen(file, "rb");
  if(aiff->fp == NULL)
    goto cleanup;

  aiff->foundcommonchunk = 0;
  aiff->readedsampleframes = 0;

  rc = parseheader(aiff);
  if(rc != 0)
    goto cleanup;

  rc = parsecommonchunk(aiff);
  if(rc != 0)
    goto cleanup;  

  rc = skiptossndchunk(aiff);
  if(rc != 0)
    goto cleanup;

  return aiff;


 cleanup:
  if(aiff->fp)
    fclose(aiff->fp);

  free(aiff);
  return NULL;
}


void aiff_close(AIFF *aiff)
{
  if(aiff){
    if(aiff->fp)
      fclose(aiff->fp);

    free(aiff);
  }
}



uint32_t aiff_readframes(AIFF *aiff, uint32_t num, int8_t *data)
{
  FILE *fp = aiff->fp;
  uint32_t samples;
  uint32_t read_byte;

  if(aiff->readedsampleframes == aiff->sampleframes)
    return 0;

  read_byte = fread(data, 
                    1, 
                    num * (aiff->samplesize >> 3) * aiff->channels,
                    fp);

  samples = read_byte / (aiff->samplesize >> 3) / aiff->channels;
  aiff->readedsampleframes += samples;
  return samples;
}


void aiff_rewind(AIFF *aiff)
{
  fseek(aiff->fp, aiff->ssndstart, SEEK_SET);
  aiff->readedsampleframes = 0;
}


uint32_t aiff_getfilesize(AIFF *aiff)
{
  return aiff->filesize;
}

uint32_t aiff_getformtype(AIFF *aiff)
{
  return aiff->formtype;
}

int16_t aiff_getchannels(AIFF *aiff)
{
  return aiff->channels;
}

uint32_t aiff_getsampleframes(AIFF *aiff)
{
  return aiff->sampleframes;
}

int16_t aiff_getsamplesize(AIFF *aiff)
{
  return aiff->samplesize;
}

uint64_t aiff_getsamplerate(AIFF *aiff)
{
  return aiff->samplerate;
}

