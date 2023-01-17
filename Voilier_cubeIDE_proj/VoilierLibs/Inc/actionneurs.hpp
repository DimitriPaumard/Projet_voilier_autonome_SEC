/*
 * safran.cpp
 *
 *  Created on: Jan 11, 2023
 *      Author: youn
 */

#include "stm32f4xx_hal.h"
TIM_HandleTypeDef htim4;

#define LEFT true
#define RIGHT false

static void MX_TIM4_Init(void);
void setAngle(int angle);
void safran_init(void);


void safran_init(){
	MX_TIM4_Init();
	/* USER CODE BEGIN 2 */
	HAL_TIM_Base_Start(&htim4);
	// Start PWM at Port-B pin#6
	HAL_TIM_PWM_Start(&htim4,TIM_CHANNEL_1);
}

//TODO - verifier implem
void setSafranAngle(float angle){
	int mid = 70;
	int max = 100;
	int min = 50;
	int coeff_dir_right = 45-0/max-mid ;
	int coeff_dir_left = 45-0/min-mid ;
	int output=  mid;
	// on considere que l'angle max est de +/- 45°
	if (angle > 45) angle = 45;
	if (angle < -45) angle = -45;
	if (angle > 0 ) //on tourne à droite
	{
		//on prend la valeur max comme reference
		output = mid + (angle/coeff_dir_right);
	} else if (angle < 0) //on tourne à gauche
	{
		//on prend la valeur min comme reference
		output = mid + ( (-1 * angle)/coeff_dir_left);
	}
	__HAL_TIM_SetCompare(&htim4, TIM_CHANNEL_1, angle);
}

static void MX_TIM4_Init(void)
{

  /* USER CODE BEGIN TIM4_Init 0 */

  /* USER CODE END TIM4_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};
  TIM_OC_InitTypeDef sConfigOC = {0};

  /* USER CODE BEGIN TIM4_Init 1 */

  /* USER CODE END TIM4_Init 1 */
  htim4.Instance = TIM4;
  htim4.Init.Prescaler = 19;
  htim4.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim4.Init.Period = 1000;
  htim4.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim4.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim4) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim4, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_Init(&htim4) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim4, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse = 500;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  if (HAL_TIM_PWM_ConfigChannel(&htim4, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM4_Init 2 */

  /* USER CODE END TIM4_Init 2 */
  HAL_TIM_MspPostInit(&htim4);

}





