#include "tinyaiff.h"

int main()
{
  AIFF *aiff;
  uint32_t numframes = 50;
  uint32_t read_frames;
  int8_t buffer[256];

  aiff = aiff_open("test/test.aif");
  if(aiff == NULL)
    return -1;

  printf("filesize    : %d\n", aiff_getfilesize(aiff));
  switch(aiff_getformtype(aiff)){
  case AIFF_FORMTYPE_AIFF:     printf("formtype    : AIFF\n"); break;
  case AIFF_FORMTYPE_AIFC:     printf("formtype    : AIFC\n"); break;
  case AIFF_FORMTYPE_INVALID:  printf("formtype    : INVALID\n"); break;
  }
  printf("channels    : %d\n", aiff_getchannels(aiff));
  printf("sampleframes: %d\n", aiff_getsampleframes(aiff));
  printf("samplesize  : %d\n", aiff_getsamplesize(aiff));
  printf("samplerate  : %lld\n", aiff_getsamplerate(aiff));

  
  do{
    read_frames = aiff_readframes(aiff, numframes, buffer);
    //    printf("%d ", read_frames);
  }while(read_frames == numframes);

  //  printf("\n");
  /* aiff_rewind(aiff); */

  aiff_close(aiff);
  return 0;
}
