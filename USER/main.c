/*
红外管未感应到为 red_x == 0
				感应到为 red_x == 1
				白色为感应到  0
				黑色为未感应到 1

*/
#include "stm32f10x.h"
#include "stm32f10x_tim.h"
//#include "stm32f10x_gpio.h"

//从左往右依次为A B C D
//#define red_A GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)
//#define red_B GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_1)
//#define red_C GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_2)
//#define red_D GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_3)

#define arr 500
#define F 0
#define R 1


void init(void);
//void GPIO_Configuration(void);


//int main(void)
//{
//	GPIO_Configuration();
////测试可用
//	GPIO_SetBits(GPIOA,GPIO_Pin_0);
//	GPIO_SetBits(GPIOA,GPIO_Pin_1);
//	GPIO_SetBits(GPIOA,GPIO_Pin_2);
//	GPIO_SetBits(GPIOA,GPIO_Pin_4);
//	GPIO_ResetBits(GPIOA,GPIO_Pin_3);
////测试可用
//	while(1)
//	{
//		if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)==1)
//		{
//			GPIO_SetBits(GPIOC,GPIO_Pin_13);
//		}
//		else
//		{
//			GPIO_ResetBits(GPIOC,GPIO_Pin_13);
//		
//		}
//	}
//	
//	
//}

//void GPIO_Configuration(void)
//{
//  GPIO_InitTypeDef GPIO_InitStructure;
//  
//  RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA , ENABLE); 						  
//	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOC , ENABLE); 						  

//  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4;
//  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; 
//  GPIO_Init(GPIOA, &GPIO_InitStructure);
//	
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
//  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 
//  GPIO_Init(GPIOC, &GPIO_InitStructure);
//}
int main()
{
	
  u8 red_A,red_B,red_C,red_D;
	init();
//		//测试
//		while(1)
//		{
//			red_A = GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0);
//			red_B = GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_1);
//			red_C = GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_2);
//			red_D = GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_3);
//			if(red_A == 0)
//			{
//				GPIO_ResetBits(GPIOC,GPIO_Pin_13);
//			}
//			else
//			{
//				GPIO_SetBits(GPIOC,GPIO_Pin_13);
//			}
//		}
	//开机
	GPIO_ResetBits(GPIOA,GPIO_Pin_8);
	GPIO_ResetBits(GPIOA,GPIO_Pin_9);
	GPIO_ResetBits(GPIOA,GPIO_Pin_10);
	GPIO_ResetBits(GPIOA,GPIO_Pin_11);
	GPIO_SetBits(GPIOA,GPIO_Pin_12);
	TIM_SetCompare1(TIM3,arr);
	TIM_SetCompare2(TIM3,arr);
	while(1)
	{
//    //测试
//		GPIO_ResetBits(GPIOC,GPIO_Pin_13); //绿灯亮
//		if(red_A == 1)
//		{
//			GPIO_SetBits(GPIOC,GPIO_Pin_13);
//		}
//		else
//		{
//			GPIO_ResetBits(GPIOC,GPIO_Pin_13);
//		}
		red_A = GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0);
		red_B = GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_1);
		red_C = GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_2);
		red_D = GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_3);
		


		if(red_A == R & red_B == R & red_C == R & red_D == R)//停车,AIN1,AIN2,BIN1,BIN2,STAY均为0
		{
			
			GPIO_ResetBits(GPIOA,GPIO_Pin_8);
    	GPIO_ResetBits(GPIOA,GPIO_Pin_9);
			GPIO_ResetBits(GPIOA,GPIO_Pin_10);
			GPIO_ResetBits(GPIOA,GPIO_Pin_11);
			GPIO_ResetBits(GPIOA,GPIO_Pin_12);
			TIM_SetCompare1(TIM3,arr);
			TIM_SetCompare2(TIM3,arr);
	    
		}
		else if(red_B ==F & red_C == R)//右转
		{
			GPIO_ResetBits(GPIOA,GPIO_Pin_8);
    	GPIO_ResetBits(GPIOA,GPIO_Pin_9);
			GPIO_SetBits(GPIOA,GPIO_Pin_10);
			GPIO_ResetBits(GPIOA,GPIO_Pin_11);
			GPIO_SetBits(GPIOA,GPIO_Pin_12);
			TIM_SetCompare1(TIM3,arr);
			TIM_SetCompare2(TIM3,3*arr/5);
		}
		else if(red_B == R & red_C == F)//左转
		{
			GPIO_SetBits(GPIOA,GPIO_Pin_8);
    	GPIO_ResetBits(GPIOA,GPIO_Pin_9);
			GPIO_SetBits(GPIOA,GPIO_Pin_10);
			GPIO_SetBits(GPIOA,GPIO_Pin_11);
			GPIO_SetBits(GPIOA,GPIO_Pin_12);
			TIM_SetCompare1(TIM3,3*arr/5);
			TIM_SetCompare2(TIM3,arr);
		}
		else if(red_B == F & red_C == F)//直行
		{
			GPIO_SetBits(GPIOA,GPIO_Pin_8);
    	GPIO_ResetBits(GPIOA,GPIO_Pin_9);
			GPIO_SetBits(GPIOA,GPIO_Pin_10);
			GPIO_ResetBits(GPIOA,GPIO_Pin_11);
			GPIO_SetBits(GPIOA,GPIO_Pin_12);
			TIM_SetCompare1(TIM3,3*arr/5);
			TIM_SetCompare2(TIM3,3*arr/5);
		}

   }
}

/*
//input: red_A -- PA0 左1
//			 red B -- PA1 左2
//			 red C -- PA2 左3
//			 red D -- PA3 左4
//
//output:TIM3_CH1 -- PA6  
//			 TIM3_CH2 -- PA7
//			 TIM3_CH3 -- PB0  未使用
//			 TIM3_CH4 -- PB1  未使用
//				
//
//				A为左轮，B为右轮
//
//				AIN1 -- PA8
//				AIN2 -- PA9
//				BIN1 -- PA10
//				BIN2 -- PA11
//				
//				STAY -- PA12
//				
//				PWM1 -- PA6
//				PWM2 -- PA7
//
//
//
/ */
void init(void)
{
  GPIO_InitTypeDef GPIO_init;
  TIM_TimeBaseInitTypeDef TIM_time;
	TIM_OCInitTypeDef TIM_oc;
	
	RCC_APB1PeriphClockCmd( RCC_APB1Periph_TIM3 , ENABLE);
  RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA , ENABLE); 	
//  RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOB , ENABLE); 
	
//	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOC , ENABLE);//测试
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_AFIO , ENABLE);
	
	//红外管输入
  GPIO_init.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3;
  GPIO_init.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_init.GPIO_Mode = GPIO_Mode_IN_FLOATING; 
  GPIO_Init(GPIOA, &GPIO_init);
  
	//电机PWM
	GPIO_init.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;	
  GPIO_init.GPIO_Mode = GPIO_Mode_AF_PP; 
  GPIO_Init(GPIOA, &GPIO_init);
	
	//电机正反转
	GPIO_init.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_12;
	GPIO_init.GPIO_Mode = GPIO_Mode_Out_PP; 
	GPIO_Init(GPIOA, &GPIO_init);

//	//测试
//	GPIO_init.GPIO_Pin = GPIO_Pin_13;
//	GPIO_init.GPIO_Mode = GPIO_Mode_Out_PP; 
//	GPIO_Init(GPIOC, &GPIO_init);
	
	
  GPIO_init.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;
  GPIO_Init(GPIOB, &GPIO_init);
	
	TIM_time.TIM_Period = arr - 1;
	TIM_time.TIM_Prescaler = 0;
	TIM_time.TIM_ClockDivision = 0;
	TIM_time.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM3,&TIM_time);
	
	TIM_oc.TIM_OCMode = TIM_OCMode_PWM2;
	TIM_oc.TIM_OutputState = TIM_OutputState_Enable;
	TIM_oc.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OC1Init(TIM3, &TIM_oc);
	TIM_OC2Init(TIM3, &TIM_oc);
//	TIM_OC3Init(TIM3, &TIM_oc);
//	TIM_OC4Init(TIM3, &TIM_oc);
	
	TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);
	TIM_Cmd(TIM3,ENABLE);
}



