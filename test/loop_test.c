#include "tinyaiff.h"
#include <stdlib.h>
#include <string.h>


int main(int argc, char **argv)
{
  AIFF *aiff;
  FILE *outfile;
  uint32_t numframes = 5;
  uint32_t read_frames;
  int8_t type[5];
  int8_t buffer[256];
  int i;

  if(argc == 0)
    return -1;

  printf("%s\n", argv[1]);

  aiff = aiff_open(argv[1]);
  if(aiff == NULL){
    printf("FAIL: aiff_open\n");
    return -1;
  }

  outfile = fopen(argv[2], "wb");
  if(outfile == NULL){
    printf("FAIL: open output file\n");
    goto cleanup;
  }
  // data info
  printf("filesize    : %d\n", aiff_getfilesize(aiff));
  switch(aiff_getformtype(aiff)){
  case AIFF_FORMTYPE_AIFF:     printf("formtype    : AIFF\n"); break;
  case AIFF_FORMTYPE_AIFC:     printf("formtype    : AIFC\n"); break;
  case AIFF_FORMTYPE_INVALID:  printf("formtype    : INVALID\n"); break;
  }
  printf("channels    : %d\n", aiff_getchannels(aiff));
  printf("sampleframes: %d\n", aiff_getsampleframes(aiff));
  printf("samplesize  : %d\n", aiff_getsamplesize(aiff));
  printf("samplerate  : %llu\n", (long long unsigned int)aiff_getsamplerate(aiff));
  if(aiff_getformtype(aiff) == AIFF_FORMTYPE_AIFC){
    aiff_getcompressiontype(aiff, type); type[4]='\0';
    printf("compression : %s , %s\n", type, !strncmp((char*)type,"NONE",4) ? "(RAW PCM)":"(Not RAW PCM)");
  }

  
  for(i=0; i<5; ++i){
    do{
      read_frames = aiff_readframes(aiff, numframes, buffer);
      fwrite(buffer,
             1, 
             read_frames * aiff_getchannels(aiff) * (aiff_getsamplesize(aiff) / 8),
             outfile);
    }while(read_frames == numframes);
    aiff_rewind(aiff);
  }



 cleanup:
  aiff_close(aiff);
  fclose(outfile);
  printf("\n");
  return 0;


  
}
