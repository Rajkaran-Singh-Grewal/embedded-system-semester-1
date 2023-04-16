/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "stdio.h"
#include "stdint.h"
#include "string.h"
#include "stdlib.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
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
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
UART_HandleTypeDef huart2;
SPI_HandleTypeDef hspi1;
TIM_HandleTypeDef htim1;
/* USER CODE BEGIN PV */
static const int16_t pushPin = 0;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART2_UART_Init(void);
/* USER CODE BEGIN PFP */
void unitTest(void);
uint8_t gpsParser(char*, uint8_t);
void displayStrings(GPSDATA);
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
void unitTest(void){
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
  uint8_t continueFlag = 1;
  while(continueFlag){
    if(deBounceReadPin(pushPin,'A',10) == 0){
      printf("%s\n",sentenceIdString);
      ssd1331_clear_screen(BLACK);
      ssd1331_display_string(0,10,sentenceIdString,FONT_1206,WHITE);
      if(deBounceReadPin(pushPin, 'A',10) == 0){
        printf("%s\n",utcTimeString);
        ssd1331_clear_screen(BLACK);
        ssd1331_display_string(0,10,utcTimeString,FONT_1206,WHITE);
        if(deBounceReadPin(pushPin,'A',10) == 0){
          printf("%s\n",latitudeString);
          ssd1331_clear_screen(BLACK);
          ssd1331_display_string(0,10,latitudeString,FONT_1206,WHITE);
          if(deBounceReadPin(pushPin,'A',10) == 0){
            printf("%s\n",latitudeMeasureString);
            ssd1331_clear_screen(BLACK);
            ssd1331_display_screen(0,10,latitudeMeasureString,FONT_1206,WHITE);
            if(deBounceReadPin(pushPin,'A',10) == 0){
              printf("%s\n",longitudeString);
              ssd1331_clear_screen(BLACK);
              ssd1331_display_string(0,10,longitudeString,FONT_1206,WHITE);
              if(deBounceReadPin(pushPin,'A',10) == 0){
                printf("%s\n",longitudeMeasureString);
                ssd1331_clear_screen(BLACK);
                ssd1331_display_string(0,10,longitudeMeasureString,FONT_1206,WHITE);
                if(deBounceReadPin(pushPin,'A',10) == 0){
                  printf("%s\n",positionFixString);
                  ssd1331_clear_screen(BLACK);
                  ssd1331_display_string(0,10,positionFixString,FONT_1206,WHITE);
                  if(deBounceReadPin(pushPin,'A',10) == 0){
                    printf("%s\n",satellitesUsedString);
                    ssd1331_clear_screen(BLACK);
                    ssd1331_display_string(0,10,satellitesUsedString,FONT_1206,WHITE);
                    if(deBounceReadPin(pushPin,'A',10) == 0){
                      printf("%s\n",horizontalDilutionOfPrecisionString);
                      ssd1331_clear_screen(BLACK);
                      ssd1331_display_string(0,10,horizontalDilutionOfPrecisionString,FONT_1206,WHITE);
                      if(deBounceReadPin(pushPin,'A',10) == 0){
                        printf("%s\n",altitudeString);
                        ssd1331_clear_screen(BLACK);
                        ssd1331_display_string(0,10,altitudeString,FONT_1206,WHITE);
                        if(deBounceReadPin(pushPin,'A',10) == 0){
                          printf("%s\n",altitudeUnitsString);
                          ssd1331_clear_screen(BLACK);
                          ssd1331_display_string(0,10,altitudeUnitsString,FONT_1206,WHITE);
                          if(deBounceReadPin(pushPin,'A',10) == 0){
                            printf("%s\n",geoidSeperationString);
                            ssd1331_clear_screen(BLACK);
                            ssd1331_display_string(0,10,geoidSeperationString,FONT_1206,WHITE);
                            if(deBounceReadPin(pushPin,'A',10) == 0){
                              printf("%s\n",inMetersString);
                              ssd1331_clear_screen(BLACK);
                              ssd1331_display_string(0,10,inMetersString,FONT_1206,WHITE);
                              if(deBounceReadPin(pushPin,'A',10) == 0){
                                printf("%s\n",dgpsAgeString);
                                ssd1331_clear_screen(BLACK);
                                ssd1331_display_string(0,10,dgpsAgeString,FONT_1206,WHITE);
                                if(deBounceReadPin(pushPin,'A',10) == 0){
                                  printf("%s\n",checkSumString);
                                  ssd1331_clear_screen(BLACK);
                                  ssd1331_display_string(0,10,checkSumString,FONT_1206,WHITE);
                                  continueFlag = 0;
                                }
                              }
                            }
                          }
                        }
                      }
                    }
                  }
                }
              }
            }
          }
        }
      }
    }
  }
  ssd1331_clear_screen(BLACK);
  ssd1331_display_string(0,10,"Finish Program",FONT_1206,WHITE);
}
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_USART2_UART_Init();
  /* USER CODE BEGIN 2 */
  pushButtonInit();
  ssd1331_init();
  uint8_t testFlag = 1;
  /* USER CODE END 2 */

  /* Infinite loop */
  char string[80];
  /* USER CODE BEGIN WHILE */
  while (testFlag == 0)
  {
    /* USER CODE END WHILE */
    scanf("Please Print geo location string %s",&string);
    
    /* USER CODE BEGIN 3 */
    scanf("Please Enter geo-location string\r\n %s",&string);
    gpsParser(string,(uint8_t)strlen(string));
  }
  if(testFlag == 1){
    unitTest();
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  if (HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure LSE Drive Capability
  */
  HAL_PWR_EnableBkUpAccess();
  __HAL_RCC_LSEDRIVE_CONFIG(RCC_LSEDRIVE_LOW);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_LSE|RCC_OSCILLATORTYPE_MSI;
  RCC_OscInitStruct.LSEState = RCC_LSE_ON;
  RCC_OscInitStruct.MSIState = RCC_MSI_ON;
  RCC_OscInitStruct.MSICalibrationValue = 0;
  RCC_OscInitStruct.MSIClockRange = RCC_MSIRANGE_6;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_MSI;
  RCC_OscInitStruct.PLL.PLLM = 1;
  RCC_OscInitStruct.PLL.PLLN = 16;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV7;
  RCC_OscInitStruct.PLL.PLLQ = RCC_PLLQ_DIV2;
  RCC_OscInitStruct.PLL.PLLR = RCC_PLLR_DIV2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK)
  {
    Error_Handler();
  }

  /** Enable MSI Auto calibration
  */
  HAL_RCCEx_EnableMSIPLLMode();
}

/**
  * @brief USART2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART2_UART_Init(void)
{

  /* USER CODE BEGIN USART2_Init 0 */

  /* USER CODE END USART2_Init 0 */

  /* USER CODE BEGIN USART2_Init 1 */

  /* USER CODE END USART2_Init 1 */
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 115200;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  huart2.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart2.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART2_Init 2 */

  /* USER CODE END USART2_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
/* USER CODE BEGIN MX_GPIO_Init_1 */
/* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(LD3_GPIO_Port, LD3_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : LD3_Pin */
  GPIO_InitStruct.Pin = LD3_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(LD3_GPIO_Port, &GPIO_InitStruct);

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */