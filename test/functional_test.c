#include "tinyaiff.h"

int main(int argc, char **argv)
{
  AIFF *aiff;
  uint32_t numframes = 5;
  uint32_t read_frames;
  int8_t type[5];
  int8_t buffer[256];

  if(argc == 0)
    return -1;

  printf("%s\n", argv[1]);

  aiff = aiff_open(argv[1]);
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
  aiff_getcompressiontype(aiff, type); type[4]='\0';
  printf("compression : %s\n", type);
  printf("\n");
  
  do{
    read_frames = aiff_readframes(aiff, numframes, buffer);
    //    printf("%d ", read_frames);
  }while(read_frames == numframes);

  //  printf("\n");
  /* aiff_rewind(aiff); */

  aiff_close(aiff);
  return 0;
}
