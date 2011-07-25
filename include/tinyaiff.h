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


/*
   This function open an AIFF or AIFF-C file and return an AIFF instance.
   The argument file is a filename.  Return NULL, if fail.

   discussion:
   This function also parse an AIFF or AIFF-C COMM chunk and find SSND chunk.
   When a file do not contain a COMM chunk and SSND chunk, this function return NULL.
*/
AIFF *aiff_open(char *file);

/* This function release AIFF instance */
void aiff_close(AIFF *aiff);

/*
   this function read the next num(2nd argument) *frames* from the audio file.
   data buffer size must be

    data buffer size = samples * bitwidth / 8 * channels
*/
uint32_t aiff_readframes(AIFF *aiff, uint32_t num, int8_t *data);

/* Rewind the read pointer. The next aiff_readframes will start from the beginning*/
void aiff_rewind(AIFF *aiff);

/* Return the file size */
uint32_t aiff_getfilesize(AIFF *aiff);

/*
  Return the formtype of enum
  AIFF_FORMTYPE_AIFF or AIFF_FORMTYPE_AIFC or AIFF_FORMTYPE_INVALID
 */
uint32_t aiff_getformtype(AIFF *aiff);

/* Return the number of audio channels */
int16_t aiff_getchannels(AIFF *aiff);

/* Return the number of audio frames in the file */
uint32_t aiff_getsampleframes(AIFF *aiff);

/* Return the size in bytes of individual samples */
int16_t aiff_getsamplesize(AIFF *aiff);

/* Return the sampling rate */
uint64_t aiff_getsamplerate(AIFF *aiff);

/* Copy compression type(4byte) to type */
void aiff_getcompressiontype(AIFF *aiff, int8_t *type);

#endif
