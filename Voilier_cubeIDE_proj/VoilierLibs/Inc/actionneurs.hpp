/*
 * safran.cpp
 *
 *  Created on: Jan 11, 2023
 *      Author: youn
 */

#include "stm32f4xx_hal.h"
#include "tim.h"


#define LEFT true
#define RIGHT false

void setAngle(int angle);
void safran_init(void);


void safranInit(){
	MX_TIM4_Init();
	/* USER CODE BEGIN 2 */
	HAL_TIM_Base_Start(&htim4);
	// Start PWM at Port-B pin#6
	HAL_TIM_PWM_Start(&htim4,TIM_CHANNEL_1);
}

void voileInit(){

}


/**
  * @brief setSafranAngle Function. Configure le compare register du TIM4 channel 1.
  * @param angle : float [+45; -45] SENS TRIGONOMETRIQUE; - a gauche et + a droite
  * @retval None
  * TODO : verifier implem
  */
void setSafranAngle(float angle){
	int mid = 70;
	int max = 100;
	int min = 50;
	int coeff_dir_right = 45-0/max-mid ;
	int coeff_dir_left = 45-0/mid-min ;
	int output =  mid;
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
		output = mid - (angle/coeff_dir_left);
	}
	__HAL_TIM_SetCompare(&htim4, TIM_CHANNEL_1, output);
}


/**
  * @brief setVoileAngle Function. Configure le compare register du TIM4 channel 2.
  * @param angle : float [+90; -90] SENS TRIGONOMETRIQUE; - a gauche et + a droite
  * @retval None
  * TODO : verifier implem
  */
void setVoileAngle(float angle) {
	int mid = 70;
	int max = 100;
	int min = 50;
	int coeff_dir_right = 45-0/max-mid ;
	int coeff_dir_left = 45-0/mid-min ;
	int output =  mid;
	__HAL_TIM_SetCompare(&htim4, TIM_CHANNEL_2, output);
}
