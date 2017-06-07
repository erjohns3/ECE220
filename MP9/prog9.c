#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "prog9.h"

int little_endian_2(FILE *fptr){
  unsigned char c1,c2;
  int ret;
  //get the next 2 characters from the file
  fscanf(fptr,"%c%c", &c1,&c2);
  //flip the position of the characters
  ret=c2;
  ret<<=8;
  ret+=c1;
  return ret;
}

int little_endian_4(FILE *fptr){
  unsigned char c1,c2,c3,c4;
  int ret;
  //get the next 4 characters from the file
  fscanf(fptr,"%c%c%c%c", &c1,&c2,&c3,&c4);
  //flip the position of the characters
  ret=c4;
  ret<<=8;
  ret+=c3;
  ret<<=8;
  ret+=c2;
  ret<<=8;
  ret+=c1;
  return ret;
}

WAV *read_file(char *wavfile){
  int i;
  WAV* wav_ptr = (WAV*)malloc(sizeof(WAV));
  //open the file so that it can be read from
  FILE *f = fopen(wavfile,"r");
  //put the header information in little endian form
  fscanf(f,"%c%c%c%c",&(* wav_ptr).RIFF[0],&(* wav_ptr).RIFF[1],&(* wav_ptr).RIFF[2],&(* wav_ptr).RIFF[3]);
  (* wav_ptr).ChunkSize = little_endian_4(f);
  fscanf(f,"%c%c%c%c",&(* wav_ptr).WAVE[0],&(* wav_ptr).WAVE[1],&(* wav_ptr).WAVE[2],&(* wav_ptr).WAVE[3]);
  fscanf(f,"%c%c%c%c",&(* wav_ptr).fmt[0],&(* wav_ptr).fmt[1],&(* wav_ptr).fmt[2],&(* wav_ptr).fmt[3]);
  (* wav_ptr).Subchunk1Size = little_endian_4(f);
  (* wav_ptr).AudioFormat = little_endian_2(f);
  (* wav_ptr).NumChan = little_endian_2(f);
  (* wav_ptr).SamplesPerSec = little_endian_4(f);
  (* wav_ptr).bytesPerSec = little_endian_4(f);
  (* wav_ptr).blockAlign = little_endian_2(f);
  (* wav_ptr).bitsPerSample = little_endian_2(f);
  (* wav_ptr).extra = (char *)malloc(((* wav_ptr).Subchunk1Size-16)*sizeof(char));
  for(i=0;i<(* wav_ptr).Subchunk1Size-16;i++)
    fscanf(f,"%c",&(* wav_ptr).extra[i]);
  fscanf(f,"%c%c%c%c",&(* wav_ptr).Subchunk2ID[0],&(* wav_ptr).Subchunk2ID[1],&(* wav_ptr).Subchunk2ID[2],&(* wav_ptr).Subchunk2ID[3]);
  (* wav_ptr).Subchunk2Size = little_endian_4(f);
  (* wav_ptr).data = (short int *)malloc(((* wav_ptr).Subchunk2Size*8/(* wav_ptr).bitsPerSample)*sizeof(short int));
  for(i=0;i<(* wav_ptr).Subchunk2Size*8/(* wav_ptr).bitsPerSample;i++)
    (* wav_ptr).data[i] = little_endian_2(f);
  
  //print out all the header information
  printf("ChunkID: %c%c%c%c\n",(* wav_ptr).RIFF[0],(* wav_ptr).RIFF[1],(* wav_ptr).RIFF[2],(* wav_ptr).RIFF[3]);
  printf("ChunkSize: %i\n",(* wav_ptr).ChunkSize);
  printf("Format: %c%c%c%c\n",(* wav_ptr).WAVE[0],(* wav_ptr).WAVE[1],(* wav_ptr).WAVE[2],(* wav_ptr).WAVE[3]);
  printf("Subchunk1ID: %c%c%c%c\n",(* wav_ptr).fmt[0],(* wav_ptr).fmt[1],(* wav_ptr).fmt[2],(* wav_ptr).fmt[3]);
  printf("Subchunk1Size: %i\n",(* wav_ptr).Subchunk1Size);
  printf("AudioFormat: %hi\n",(* wav_ptr).AudioFormat);
  printf("NumChan: %hi\n",(* wav_ptr).NumChan);
  printf("SamplesPerSec: %i\n",(* wav_ptr).SamplesPerSec);
  printf("bytesPerSec: %i\n",(* wav_ptr).bytesPerSec);
  printf("blockAlign: %hi\n",(* wav_ptr).blockAlign);
  printf("bitsPerSample: %hi\n",(* wav_ptr).bitsPerSample);
  printf("Subchunk2ID: %c%c%c%c\n",(* wav_ptr).Subchunk2ID[0],(* wav_ptr).Subchunk2ID[1],(* wav_ptr).Subchunk2ID[2],(* wav_ptr).Subchunk2ID[3]);
  printf("Subchunk2Size: %i\n",(* wav_ptr).Subchunk2Size);

  return wav_ptr;
}

void sloop(WAV *inwav, char *outfile, double a, double b, int n){
  //open the output file so that it can be written to
  FILE *f = fopen(outfile,"w");
  //create bitmasks for each value position
  unsigned int mask1 = 0xFF000000;
  unsigned int mask2 = 0x00FF0000;
  unsigned int mask3 = 0x0000FF00;
  unsigned int mask4 = 0x000000FF;
  //initailize loop counters
  int i,j;
  //find the values for the start and end of the sample that is looped
  unsigned int start = (* inwav).NumChan*(* inwav).SamplesPerSec*a;
  unsigned int end = (* inwav).NumChan*(* inwav).SamplesPerSec*b;
  //find the size of the data
  unsigned int dataSize = (end-start)*n*(* inwav).bitsPerSample/8;
  //read the header information from the input WAV and convert it back from little endian form and write it in the output file.
  fprintf(f,"%c%c%c%c",(* inwav).RIFF[0],(* inwav).RIFF[1],(* inwav).RIFF[2],(* inwav).RIFF[3]);
  fprintf(f,"%c%c%c%c",(dataSize+36)&mask4,((dataSize+36)&mask3)>>8,((dataSize+36)&mask2)>>16,((dataSize+36)&mask1)>>24);
  fprintf(f,"%c%c%c%c",(* inwav).WAVE[0],(* inwav).WAVE[1],(* inwav).WAVE[2],(* inwav).WAVE[3]);
  fprintf(f,"%c%c%c%c",(* inwav).fmt[0],(* inwav).fmt[1],(* inwav).fmt[2],(* inwav).fmt[3]);
  fprintf(f,"%c%c%c%c",(* inwav).Subchunk1Size&mask4,((* inwav).Subchunk1Size&mask3)>>8,((* inwav).Subchunk1Size&mask2)>>16,((* inwav).Subchunk1Size&mask1)>>24);
  fprintf(f,"%c%c",(* inwav).AudioFormat&mask4,((* inwav).AudioFormat&mask3)>>8);
  fprintf(f,"%c%c",(* inwav).NumChan&mask4,((* inwav).NumChan&mask3)>>8);
  fprintf(f,"%c%c%c%c",(* inwav).SamplesPerSec&mask4,((* inwav).SamplesPerSec&mask3)>>8,((* inwav).SamplesPerSec&mask2)>>16,((* inwav).SamplesPerSec&mask1)>>24);
  fprintf(f,"%c%c%c%c",(* inwav).bytesPerSec&mask4,((* inwav).bytesPerSec&mask3)>>8,((* inwav).bytesPerSec&mask2)>>16,((* inwav).bytesPerSec&mask1)>>24);
  fprintf(f,"%c%c",(* inwav).blockAlign&mask4,((* inwav).blockAlign&mask3)>>8);
  fprintf(f,"%c%c",(* inwav).bitsPerSample&mask4,((* inwav).bitsPerSample&mask3)>>8);
  for(i=0;i<(* inwav).Subchunk1Size-16;i++)
    fprintf(f,"%c",(* inwav).extra[i]);
  fprintf(f,"%c%c%c%c",(* inwav).Subchunk2ID[0],(* inwav).Subchunk2ID[1],(* inwav).Subchunk2ID[2],(* inwav).Subchunk2ID[3]);
  fprintf(f,"%c%c%c%c",(dataSize+36)&mask4,((dataSize+36)&mask3)>>8,((dataSize+36)&mask2)>>16,((dataSize+36)&mask1)>>24);
  //loop though the chosen sample n times
  for(i=0;i<n;i++){
    for(j=start-1;j<end;j++)
      fprintf(f,"%c%c",(* inwav).data[j]&mask4,((* inwav).data[j]&mask3)>>8);
  }
  //close out of the file
  fclose(f);
}

//Extra credit
void lo_pass(WAV *inwav, char *outfile, int freq){

}

