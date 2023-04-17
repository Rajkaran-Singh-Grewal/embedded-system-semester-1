#include "stdio.h"
#include "stdint.h"
#include "string.h"
#include "stdlib.h"

typedef struct UTCTime{
  char hh[3];
  char mm[3];
  char ss[5];
}UTCTime;

typedef struct Latitude{
  char degrees[3];
  char minutes[3];
  char decimalDegrees[5];
}Latitude;

typedef struct Longitude{
  char degrees[4];
  char minutes[3];
  char decimalDegrees[5];
}Longitude;

typedef struct GPSDATA{
  char sentenceID[7];
  UTCTime utcTime;
  Latitude latitude;
  char latitudeMeasure;
  Longitude longitude;
  char longitudeMeasure;
  char positionFix;
  char satellitesUsed[2];
  char horizontalDilutionOfPrecision[7];
  char altitude[7];
  char altitudeUnits;
  char geoidSeperation;
  char inMeters;
  char ageOfDGPSDataInSeconds;
  char checkSum[4];
}GPSDATA;

void unitTest(void);
uint8_t gpsParser(char*,uint8_t);
void displayStrings(GPSDATA);

void unitTest(void){
  printf("Testing has begun\r\n");
  char testString[] = "$GPGGA,092750.000,5321.6802,N,00630.3372,W,1,8,1.03,61.7,M,55.2,M,,*76";
  char testString2[] = "$GPGGA,092751.000,5321.6802,N,00630.3371,W,1,8,1.03,61.7,M,55.3,M,,*75";
  char testString3[] = "$GPGGA,014729.10,4303.5753,N,08019.0810,W,1,6,1.761,214.682,M,0,M,0,*5D";
  uint8_t result = 0;
  result = gpsParser(testString,(uint8_t)strlen(testString));
  if(result == 1){
    printf("\r\nTask 1 Case 1 was successful\r\n");
  }else{
    printf("\r\nTask 1 Case 1 was not successful\r\n");
  }
  result = gpsParser(testString2,(uint8_t)strlen(testString2));
  if(result == 1){
    printf("\r\nTask 1 Case 2 was successful\r\n");
  }else{
    printf("\r\nTask 1 Case 2 was not successful\r\n");
  
  }
  result = gpsParser(testString3,(uint8_t)strlen(testString3));
  if(result == 1){
    printf("\r\nTask 1 Case 3 was successful\r\n");
  }else{
    printf("\r\nTask 1 Case 3 was not successful\r\n");
  }
}
uint8_t gpsParser(char *string,uint8_t len){
  int i = 0;   
  while(*string != '\0'){
    if(*string == ','){
      if(*++string == ','){
        int j = 1;
        char *tempString = malloc((len - i) * sizeof(char));
        tempString[0] = 'X';
        while(*string != '\0'){
          tempString[j] = *string++;
          j++;
        }
        for(int k = 0; k < j;k++){
          string--;
        }
        while(*tempString != '\0'){
          string++;
          *string = *tempString++;
        }
        string++;
        *string = NULL;
        for(int k = 0; k < j;k++){
          string--;
        }
        string--;
        len++;
      }else{
        string--;
      }
    }
    string++;
    i++;
  }
  for(int k = 0; k < i; k++){
    string--;
  }
  char* token = strtok(string, ","); 
  GPSDATA gpsdata;
  for(int i = 0;i<6;i++){
    gpsdata.sentenceID[i] = *token++;
  }
  gpsdata.sentenceID[7] = NULL;
  token = strtok(NULL,",");
  UTCTime utctime;
  char * utctimeString = malloc(10 * sizeof(char));
  utctimeString = token;
  token = strtok(NULL,",");
  for(int i = 0; i < 2; i++){
    utctime.hh[i] = *utctimeString++;
  }
  utctime.hh[2] = '\0';
  for(int i = 0; i < 2; i++){
    utctime.mm[i] = *utctimeString++;
  }
  utctime.mm[2] = '\0';
  i = 0;
  while(*utctimeString != '\0'){
    utctime.ss[i] = *utctimeString++;
    i++;
  }
  for(;i<5;i++){
    utctime.ss[i] = '0';
  }
  gpsdata.utcTime = utctime;
  char* latitudeString = malloc(11 * sizeof(char));
  latitudeString = token;
  token = strtok(NULL,",");
  Latitude latitude;
  for(int i = 0; i < 2; i++){
    latitude.degrees[i] = *latitudeString++;
  }
  latitude.degrees[2] = '\0';
  for(int i = 0; i < 2; i++){
    latitude.minutes[i] = *latitudeString++;
  }
  latitude.minutes[2] = '\0';
  i = 0;
  while(*latitudeString != '\0'){
    latitude.decimalDegrees[i] = *latitudeString++;
    i++;
  }
  for(;i<5;i++){
    latitude.decimalDegrees[i] = '0';
  } 
  gpsdata.latitude = latitude;
  gpsdata.latitudeMeasure = *token;
  token = strtok(NULL,",");
  Longitude longitude;
  char* longitudeString = malloc(12 * sizeof(char));
  longitudeString = token;
  token = strtok(NULL,",");
  for(int i = 0; i < 3;i++){
    longitude.degrees[i] = *longitudeString++;
  }
  longitude.degrees[3] = '\0';
  for(int i = 0; i < 2; i++){
    longitude.minutes[i] = *longitudeString++;
  }
  longitude.minutes[2] = '\0';
  i = 0;
  while(*longitudeString != '\0'){
    longitude.decimalDegrees[i] = *longitudeString++;
    i++;
  }
  for(;i<5;i++){
    longitude.decimalDegrees[i] = '0';
  }
  gpsdata.longitude = longitude;
  gpsdata.longitudeMeasure = *token;
  token = strtok(NULL,",");
  gpsdata.positionFix = *token;
  token = strtok(NULL,",");
  gpsdata.satellitesUsed[0] = *token;
  gpsdata.satellitesUsed[1] = '\0';
  token = strtok(NULL,",");
  char* horizontalDilutionOfPrecisionString = malloc(7 * sizeof(char));
  horizontalDilutionOfPrecisionString = token;
  token = strtok(NULL,",");
  i = 0;
  while(*horizontalDilutionOfPrecisionString != '\0'){
    gpsdata.horizontalDilutionOfPrecision[i] = *horizontalDilutionOfPrecisionString++;
    i++;
  }
  for(;i < 6;i++){
    gpsdata.horizontalDilutionOfPrecision[i] = '0';
  }
  gpsdata.horizontalDilutionOfPrecision[7] = '\0';
  char* altitudeString = malloc(8 * sizeof(char));
  altitudeString = token;
  token = strtok(NULL,",");
  i = 0;
  while(*altitudeString != '\0'){
    gpsdata.altitude[i] = *altitudeString++;
    i++;
  }
  for(;i<7;i++){
    gpsdata.altitude[i] = '0';
  }
  gpsdata.altitudeUnits = *token;
  token = strtok(NULL,",");
  gpsdata.geoidSeperation = *token;
  token = strtok(NULL,",");
  gpsdata.inMeters = *token;
  token = strtok(NULL,",");
  gpsdata.ageOfDGPSDataInSeconds = *token;
  token = strtok(NULL,",");
  char * checkSumString = malloc(5 * sizeof(char));
  checkSumString = token;
  token = strtok(NULL,",");
  i = 0;
  if(*checkSumString == '*'){
    checkSumString++;
  }
  while(*checkSumString != '\0'){
    gpsdata.checkSum[i] = *checkSumString++;
    i++;
  }
  for(;i<4;i++){
    gpsdata.checkSum[i] = NULL;
  }
  if(token != '\0'){
    printf("Token has not bee fully allocated!");
    return 0;
  }
  displayStrings(gpsdata);
  return 1;
}
void displayStrings(GPSDATA gpsdata){
  char sentenceIdString[20];
  char* sentenceID = gpsdata.sentenceID;
  snprintf(sentenceIdString,20,"Sentence ID: %s",sentenceID);
  char utcTimeString[64];
  snprintf(utcTimeString,64,"UTC Time: %d hr %d min %f sec",
           atoi(gpsdata.utcTime.hh),
           atoi(gpsdata.utcTime.mm),
           atof(gpsdata.utcTime.ss));
  char latitudeString[64];
  snprintf(latitudeString,64,"Latitude: %d degrees %d minutes %f decimal degrees",
           atoi(gpsdata.latitude.degrees),
           atoi(gpsdata.latitude.minutes),
           atof(gpsdata.latitude.decimalDegrees));
  char latitudeMeasureString[64];
  if(gpsdata.latitudeMeasure == 'N'){
    snprintf(latitudeMeasureString,64,"Latitude: measured is North of the equator");
  }else{
    snprintf(latitudeMeasureString,64,"Latitude: measured is South of the equator");
  }
  char longitudeString[64];
  snprintf(longitudeString,64,"Longitude: %d degrees %d minutes %f decimal degrees",
            atoi(gpsdata.longitude.degrees),
            atoi(gpsdata.longitude.minutes),
            atof(gpsdata.longitude.decimalDegrees));
  char longitudeMeasureString[64];
  if(gpsdata.longitudeMeasure == 'W'){
    snprintf(longitudeMeasureString,64,"Longitude: measured is West of Greenwich England");
  }else{
    snprintf(longitudeMeasureString,64,"Longitude: measured is East of Greenwich England");
  }
  char positionFixString[64];
  if(gpsdata.positionFix == '0'){
    snprintf(positionFixString,64,"Position Fix: Invalid");
  }else if(gpsdata.positionFix == '1'){
    snprintf(positionFixString,64,"Position Fix: Valid SPS");
  }else if(gpsdata.positionFix == '2'){
    snprintf(positionFixString,64,"Position Fix: Valid DGPS");
  }else if(gpsdata.positionFix == '3'){
    snprintf(positionFixString,64,"Position Fix: Valid PPS");
  }
  char satellitesUsedString[64];
  snprintf(satellitesUsedString,64,"Satellites Used: %d", atoi(&gpsdata.satellitesUsed));
  char horizontalDilutionOfPrecisionString[64];
  snprintf(horizontalDilutionOfPrecisionString,64,"HDOP 38466 Horizontal dilution of precision %f",atof(gpsdata.horizontalDilutionOfPrecision));
  char altitudeString[68];
  snprintf(altitudeString,68,"Altitude in meters according to WGS-84 ellipsoid %f meters",atof(gpsdata.altitude));
  char altitudeUnitsString[64];
  snprintf(altitudeUnitsString,64,"Altitude Units: M = Meters");
  char geoidSeperationString[64];
  snprintf(geoidSeperationString,64,"Geoid Seperation %d",atoi(&gpsdata.geoidSeperation));
  char inMetersString[64];
  snprintf(inMetersString,64,"In Meters");
  char dgpsAgeString[64];
  if(gpsdata.ageOfDGPSDataInSeconds == 'X'){
    snprintf(dgpsAgeString,64,"DGPS Age: %d Age of DGPS data in seconds",0);
  }else{
    snprintf(dgpsAgeString,64,"DGPS Age: %d Age of DGPS data in seconds",
           atoi(&gpsdata.ageOfDGPSDataInSeconds));
  }
  char checkSumString[64];
  char *ptr;
  long checkSum = strtoul(gpsdata.checkSum,&ptr,10);
  snprintf(checkSumString,64,"Checksum: = %lu",checkSum);
  printf("%s\n",sentenceIdString);
  printf("%s\n",utcTimeString);
  printf("%s\n",latitudeString);
  printf("%s\n",latitudeMeasureString);
  printf("%s\n",longitudeString);
  printf("%s\n",longitudeMeasureString);
  printf("%s\n",positionFixString);
  printf("%s\n",satellitesUsedString);
  printf("%s\n",horizontalDilutionOfPrecisionString);
  printf("%s\n",altitudeString);
  printf("%s\n",altitudeUnitsString);
  printf("%s\n",geoidSeperationString);
  printf("%s\n",inMetersString);
  printf("%s\n",dgpsAgeString);
  printf("%s\n",checkSumString);
}
int main(){
  unitTest();
  printf("Program Has Ended\r\n");
  return 0;
}
