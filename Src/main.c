/**
  ******************************************************************************
  * File Name          : main.c
  * Description        : Main program body
  ******************************************************************************
  *
  * COPYRIGHT(c) 2017 STMicroelectronics
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32f4xx_hal.h"
#include "i2c.h"
#include "rng.h"
#include "spi.h"
#include "gpio.h"

/* USER CODE BEGIN Includes */
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "lcd5110.h"
/* USER CODE END Includes */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
/* Private variables ---------------------------------------------------------*/

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
void Error_Handler(void);

/* USER CODE BEGIN PFP */
/* Private function prototypes -----------------------------------------------*/

/* USER CODE END PFP */

/* USER CODE BEGIN 0 */
LCD5110_display lcd1;

#define BMP180_PARAM_MG 3038
#define BMP180_PARAM_MH -7357
#define BMP180_PARAM_MI 3791

const unsigned char smile[] = { 0x00, 0x00, 0x00, 0x00, 0x80, 0xc0, 0xe0, 0xf0,
		0xf8, 0x7c, 0x7c, 0x3c, 0x1e, 0x1e, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f,
		0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x1f, 0x1e, 0x1e, 0x3c, 0x7c, 0x7c, 0xf8,
		0xf0, 0xe0, 0xc0, 0x80, 0x00, 0x00, 0x00, 0x00, 0xc0, 0xf0, 0xfe, 0xff,
		0xff, 0x0f, 0x07, 0x01, 0x00, 0x00, 0x00, 0xf0, 0xfc, 0xfe, 0xfe, 0xfe,
		0xf8, 0xf0, 0x00, 0x00, 0x00, 0x00, 0xf0, 0xfc, 0xfe, 0xfe, 0xfe, 0xfc,
		0xf0, 0x00, 0x00, 0x02, 0x03, 0x07, 0x0f, 0xff, 0xff, 0xfc, 0xf0, 0x00,
		0xff, 0xff, 0xff, 0xff, 0x80, 0x00, 0x00, 0x00, 0x40, 0xc0, 0xc0, 0xc0,
		0xc3, 0xc7, 0xc7, 0xc3, 0xc3, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc3,
		0xc7, 0xc7, 0xc7, 0xc3, 0xc0, 0xc0, 0xc0, 0xc0, 0x00, 0x00, 0x00, 0x00,
		0xff, 0xff, 0xff, 0xff, 0x03, 0x07, 0x3f, 0x7f, 0xff, 0xf8, 0xf0, 0xc0,
		0x80, 0x03, 0x07, 0x0f, 0x1f, 0x1f, 0x3f, 0x7f, 0x7f, 0x7f, 0xff, 0xff,
		0xff, 0xff, 0x7f, 0x7f, 0x3f, 0x3f, 0x1f, 0x1f, 0x0f, 0x07, 0x01, 0x80,
		0xe0, 0xf0, 0xf8, 0xff, 0x7f, 0x1f, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x03, 0x03, 0x07, 0x0f, 0x1f, 0x1e, 0x3e, 0x3c, 0x3c, 0x78, 0x78,
		0x78, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0x78, 0x78, 0x78, 0x3c, 0x3c,
		0x3e, 0x1e, 0x1f, 0x0f, 0x07, 0x03, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00 //
		};


const unsigned char Bender [] = {
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF8,
0xFC, 0xFF, 0xDF, 0xAF, 0x55, 0x80, 0x55, 0x00, 0x55, 0x00, 0x55, 0x00, 0x55, 0x00, 0x55, 0x00,
0x55, 0x00, 0x55, 0x00, 0x55, 0x80, 0xD5, 0x80, 0xD5, 0xE0, 0xF5, 0x60, 0x75, 0x70, 0x75, 0x60,
0x75, 0xE0, 0xD5, 0x80, 0xD5, 0x00, 0x55, 0x00, 0x55, 0x00, 0x57, 0x07, 0x5E, 0x3C, 0x70, 0xF0,
0xE0, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x03, 0x5F, 0xFF, 0xFF, 0xFF, 0xD7, 0xEE, 0xD5, 0xE8, 0xD5, 0xA0, 0xD5, 0x80,
0xD5, 0xC0, 0xF5, 0xE0, 0xBD, 0xF8, 0xDF, 0xEE, 0x7F, 0x3B, 0x3F, 0x0F, 0x0F, 0x06, 0x06, 0x06,
0x06, 0x06, 0x0C, 0x0C, 0x38, 0x38, 0xF1, 0xC1, 0xC3, 0x07, 0x07, 0x3C, 0x3D, 0xF8, 0xF5, 0xC0,
0x55, 0x00, 0x55, 0x00, 0x55, 0x03, 0x57, 0x1E, 0x7C, 0xF0, 0xE0, 0xC0, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x03, 0xC7, 0xFF, 0xFD, 0x7A,
0xDD, 0xFE, 0xFF, 0x77, 0x7F, 0x3C, 0x7E, 0x3F, 0x3F, 0x3F, 0x7F, 0xFF, 0x80, 0x80, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0x0F, 0x8F, 0xC4, 0xE0, 0x7D, 0x3F, 0x1F, 0x00, 0x00, 0x00,
0x80, 0x80, 0xE1, 0xE7, 0x7F, 0x3E, 0x55, 0x00, 0x55, 0x00, 0x55, 0x00, 0x55, 0x00, 0x55, 0x01,
0x57, 0x0F, 0x5C, 0x78, 0x70, 0xE0, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0xE0, 0xF0, 0xBC, 0xDF, 0xEF,
0xF7, 0xFF, 0xFF, 0xFF, 0x47, 0x03, 0x01, 0x00, 0x00, 0x00, 0xC0, 0xE0, 0xF0, 0xE0, 0x00, 0x01,
0x07, 0x07, 0x0E, 0xCC, 0xCC, 0xFC, 0x7C, 0x3C, 0x1C, 0x0E, 0x07, 0x83, 0xC1, 0xE0, 0x70, 0x30,
0x78, 0x1C, 0x5C, 0x0F, 0x57, 0x03, 0xD5, 0xC0, 0xD5, 0xE0, 0x75, 0x30, 0x35, 0xB8, 0xDD, 0xF8,
0xFD, 0xF8, 0xFD, 0xB8, 0x35, 0x30, 0xF5, 0xC0, 0xD5, 0x03, 0x57, 0x0F, 0x5F, 0xBC, 0xF0, 0xF0,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1F, 0xFF,
0xFF, 0x7F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFE, 0xFC, 0xF8, 0xF0, 0xF0, 0xF0, 0xE1,
0xF1, 0xF0, 0x78, 0xB8, 0x5E, 0x2E, 0x57, 0x81, 0xD1, 0xE8, 0xF4, 0xB8, 0xFC, 0xBE, 0x77, 0xA3,
0x55, 0x80, 0xD5, 0xC0, 0xF5, 0x78, 0x3D, 0xBE, 0xFF, 0xE6, 0xF3, 0xF9, 0x1D, 0x0D, 0x07, 0x07,
0x0F, 0xF9, 0xF9, 0xF0, 0xF0, 0xB8, 0x19, 0x1F, 0xC6, 0xCE, 0xFB, 0xFB, 0x7F, 0xE8, 0xF5, 0xFE,
0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x07, 0x0F, 0x1F, 0x1F, 0x1F, 0x3B, 0x77, 0x7F, 0x7F, 0x6F, 0x7F, 0x7F,
0x7F, 0x3F, 0x3F, 0x3B, 0x1D, 0x1C, 0x1D, 0x1E, 0x1F, 0x0E, 0x1F, 0x0F, 0x1F, 0x3F, 0x7D, 0xEE,
0xFF, 0xFE, 0xF7, 0xEA, 0x7F, 0x7F, 0x7F, 0x3F, 0x1F, 0x1E, 0x7F, 0xE3, 0xC1, 0xE0, 0xF1, 0x73,
0x1F, 0x1E, 0x9F, 0xFB, 0xF3, 0x60, 0x70, 0xFC, 0xDD, 0xEF, 0xD7, 0xE3, 0xD7, 0xE1, 0xD5, 0xF8,
0xFD, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
};


const unsigned char babe [] = {
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x7E, 0x3F, 0x1F, 0x0F, 0x03,
0x07, 0x02, 0x06, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC0, 0xF0, 0xF8, 0xFC, 0xFF, 0xFF,
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x3F, 0x3F, 0x1F, 0x1F, 0x1F, 0x3E, 0x70, 0xD0, 0x80, 0x00,
0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
0xFF, 0xFF, 0x3F, 0x1F, 0x3F, 0x9F, 0x1F, 0x3F, 0x1F, 0x0F, 0x07, 0x07, 0x02, 0x01, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0xC0, 0xE0, 0xFC, 0xFF, 0xFF,
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x01, 0xFF, 0xDF, 0x9F, 0xDF, 0xFE, 0xFC, 0x00, 0x00, 0x0C, 0x0C,
0xCC, 0x7F, 0x0F, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
0x7F, 0x7F, 0x3F, 0x3F, 0x3F, 0x3E, 0x3E, 0x3E, 0x3E, 0x3E, 0x30, 0x60, 0x60, 0xC0, 0x40, 0x00,
0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x80, 0xC0, 0xE0, 0xF0, 0xF8, 0xFC, 0xFC, 0xFE, 0xFE, 0xFF, 0xFF, 0xFF, 0xFF,
0xFF, 0xFF, 0xE3, 0xC3, 0x83, 0x83, 0x03, 0x07, 0x1F, 0xFF, 0xFE, 0xE7, 0xCF, 0x9F, 0x27, 0x25,
0x02, 0x08, 0x0C, 0xFF, 0xDB, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3F, 0x1F, 0x1F, 0x0F,
0x07, 0x03, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80,
0xC0, 0xF1, 0xFF, 0xFF, 0x7E, 0x09, 0x03, 0x07, 0x26, 0x24, 0x48, 0x48, 0xC8, 0xC0, 0xC0, 0xE0,
0xF0, 0xF0, 0xF8, 0xFC, 0xFC, 0xFE, 0xFF, 0xFF, 0xFF, 0xEF, 0x9F, 0x7F, 0xFF, 0xFF, 0xFF, 0xFF,
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x0F, 0x1F, 0x1F, 0x3F, 0x3C, 0x00, 0x00, 0xFF, 0xFF, 0xFF,
0xFF, 0xFF, 0xFF, 0xFC, 0x78, 0x10, 0xC0, 0xE0, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0xFF, 0xFE, 0xFC, 0xF8, 0xE0, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0xC0, 0xCF, 0xCF,
0xFF, 0xFE, 0xFE, 0xFF, 0xFF, 0xFF, 0xE7, 0xF1, 0xF0, 0xE0, 0xE0, 0xE0, 0xC0, 0xC0, 0x80, 0x80,
0x80, 0x0F, 0x3F, 0xFF, 0xFF, 0x9F, 0x87, 0x87, 0x8F, 0xDF, 0xF7, 0xFF, 0xDB, 0xE1, 0xFF, 0xF8,
0xFC, 0xFD, 0xFB, 0xFF, 0xFF, 0xFF, 0x7F, 0xFF, 0x7F, 0xFF, 0xFE, 0xFC, 0xF8, 0xF8, 0xF0, 0xF8,
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x9F, 0xC7, 0xE3, 0xF8, 0xFF, 0xFF, 0x4B, 0x01, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0xFF, 0x3F, 0xBF, 0x1F, 0x0F, 0x0F, 0x07, 0x04, 0x06, 0x07, 0x07, 0x87,
0x87, 0x83, 0xC3, 0xC3, 0xC7, 0xC3, 0xC7, 0xE7, 0xC3, 0xFF, 0xFF, 0xC7, 0xC3, 0xC3, 0x03, 0x03,
0x03, 0x03, 0x07, 0x07, 0x07, 0x03, 0x03, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x03, 0x07, 0x07,
0x07, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x83, 0xC7, 0xC7, 0xCF, 0xCF, 0x4F, 0x2F,
0x3F, 0x3F, 0x3F, 0x1F, 0x1F, 0x0F, 0x17, 0x13, 0x3F, 0x7C, 0xFC, 0xFF, 0xF7, 0xE3, 0xE7, 0xE7,
0xD0, 0xF0, 0xE0, 0x60, 0x60, 0x60, 0x60, 0x60,
};


const unsigned char Thermometer [] = {
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFC, 0xF2, 0xF2, 0xFC, 0x00, 0xA8, 0xA8, 0xA8, 0xA8, 0x00,
0x00, 0x54, 0x54, 0x40, 0x4E, 0x11, 0x2E, 0x2F, 0x2F, 0x2E, 0x11, 0x0E, 0x00, 0x00, 0x00, 0x00
};

const unsigned char Barometer [] = {
0x00, 0xE0, 0xF8, 0x1C, 0x0C, 0x24, 0x46, 0x86, 0x06, 0x06, 0xA6, 0x46, 0xAE, 0x1C, 0xFC, 0xF0,
0x00, 0x1F, 0x3F, 0x70, 0xE2, 0xC7, 0xC2, 0xD0, 0xCD, 0xD0, 0xC0, 0xC0, 0x60, 0x70, 0x1F, 0x0F
};

const unsigned char Pressure [] = {
0x00, 0xC0, 0x30, 0x88, 0x04, 0x24, 0x42, 0x96, 0xCA, 0xC2, 0x24, 0x94, 0x08, 0xB0, 0xC0, 0x00,
0x00, 0x03, 0x0D, 0x10, 0x21, 0x24, 0x42, 0x51, 0x69, 0x42, 0x24, 0x20, 0x11, 0x0C, 0x03, 0x00
};

const unsigned char Gas_1 [] = {
0x00, 0x00, 0xE0, 0xFC, 0xBC, 0x1E, 0xBF, 0xFF, 0xFF, 0xBF, 0x1E, 0xBC, 0xFC, 0xE0, 0x00, 0x00,
0x00, 0x00, 0x00, 0x7B, 0xC3, 0xDF, 0xE7, 0xDE, 0xDE, 0xE7, 0xDF, 0xC3, 0x7B, 0x00, 0x00, 0x00
};

const unsigned char Gas_2 [] = {
0x00, 0x00, 0xE0, 0xFC, 0xBC, 0x1E, 0xBF, 0xFF, 0xFF, 0xBF, 0x1E, 0xBC, 0xFC, 0xE0, 0x00, 0x00,
0x00, 0x00, 0x00, 0x3F, 0x63, 0x7F, 0x77, 0x7E, 0x7E, 0x77, 0x7F, 0x63, 0x3F, 0x00, 0x00, 0x00
};

int16_t AC1=0;
int16_t AC2=0;
int16_t AC3=0;
uint16_t AC4=0;
uint16_t AC5=0;
uint16_t AC6=0;
int16_t B1=0;
int16_t B2=0;
int16_t MB=0;
int16_t MC=0;
int16_t MD=0;

const int barRegisters[11] = {0xAA, 0xAC, 0xAE, 0xB0, 0xB2, 0xB4, 0xB6, 0xB8, 0xBa, 0xBC, 0xBE};

int CalculateB5(int data, int AC6, int AC5, int MC, int MD)
{
	return ((data - AC6)*AC5/32768) + MC*2048/((data - AC6)*AC5/32768) + MD;
}

int CalculateTempBAR(int data, int AC6, int AC5, int MC, int MD)
{
	 return (CalculateB5(data, AC6, AC5, MC, MD) + 8)/16 - 100;
}

int32_t CalculatePressBAR(uint32_t data, uint32_t AC6, uint32_t AC5, int32_t MC, int32_t MD, int32_t B2, uint8_t oss){
	  int32_t B3, B6, X3, p, X1, X2;
	  uint32_t B4, B7, B5;
	  B5 = CalculateTempBAR(data, AC6, AC5, MC, MD);
	  B6 = B5 - 4000;
	  X3 = (((int32_t) B2 *((B6 * B6) >> 12))>> 11) +((AC2 * B6) >> 11);
	  B3 = ((((int32_t)AC1 * 4 + X3) << oss) + 2) >> 2;
	  X3 = (((AC3 * B6) >> 13) + ((B1 * ((B6 * B6) >> 12)) >> 16) + 2) >> 2;
	  B4 = (AC4 * (uint32_t)(X3 + 32768)) >> 15;
	  B7 = ((uint32_t)data - B3) * (50000 >> oss);
	  if (B7 < 0x80000000) p = (B7 << 1) / B4; else p = (B7 / B4) << 1;
		p += ((((p >> 8) * (p >> 8) * BMP180_PARAM_MG) >> 16) + ((BMP180_PARAM_MH * p) >> 16) + BMP180_PARAM_MI) >> 4;

		return p * 407 * 0.00750061683;
}

void Draw_temperature_values(uint8_t *Buffer, int16_t *dataINTHolders_, uint16_t *dataUINTHolders_)
{
	Buffer[0] = (uint16_t) 0x2E;
	HAL_I2C_Mem_Write(&hi2c2, (uint16_t) (0xEE), (uint16_t)(0xF4), I2C_MEMADD_SIZE_8BIT, Buffer, 1, 500);
	HAL_Delay(450);
	HAL_I2C_Mem_Read(&hi2c2, (uint16_t) (0xEE), (uint16_t)(0xF6),  I2C_MEMADD_SIZE_8BIT, Buffer, 2, 500);

	int temperature = (Buffer[0]<<8) | (Buffer[1]);

	int temperatureBAR = CalculateTempBAR(temperature, dataUINTHolders_[2], dataUINTHolders_[1], dataINTHolders_[9], dataINTHolders_[10]);

	LCD5110_drawBitmap(0, 0, Thermometer, 16, 16, 0, &lcd1.hw_conf);
	LCD5110_set_cursor(18, 4, &lcd1);
	LCD5110_print("C*:", BLACK, &lcd1);

	LCD5110_putint(temperatureBAR, 36, 4, -1, BLACK, &lcd1);

	// Update
	LCD5110_refresh(&lcd1);
}

void Draw_pressure_values(uint8_t *Buffer, int16_t *dataINTHolders_, uint16_t *dataUINTHolders_)
{
	Buffer[0] = (uint16_t) 0x2E;
	HAL_I2C_Mem_Write(&hi2c2, (uint16_t) (0xEE), (uint16_t)(0xF4), I2C_MEMADD_SIZE_8BIT, Buffer, 1, 500);
	HAL_Delay(450);
	HAL_I2C_Mem_Read(&hi2c2, (uint16_t) (0xEE), (uint16_t)(0xF6),  I2C_MEMADD_SIZE_8BIT, Buffer, 2, 500);

	int temperature = (Buffer[0]<<8) | (Buffer[1]);

	int pressureBAR = CalculatePressBAR(temperature, dataUINTHolders_[2], dataUINTHolders_[1], dataINTHolders_[9], dataINTHolders_[10], dataINTHolders_[7], 0);

	LCD5110_drawBitmap(0, 32, Pressure, 16, 16, 0, &lcd1.hw_conf);
	LCD5110_set_cursor(18, 36, &lcd1);
	LCD5110_print("Press:", BLACK, &lcd1);
	LCD5110_putint(pressureBAR, 56, 36, -1, BLACK, &lcd1);

	// Update
	LCD5110_refresh(&lcd1);
}

void Draw_spec_screen_one(uint8_t *Buffer, int16_t *dataINTHolders_, uint16_t *dataUINTHolders_)
{
	// Clear everything already drawn
	LCD5110_clear_scr(&lcd1);

	// Thermometer
	Draw_temperature_values(Buffer, dataINTHolders_, dataUINTHolders_);

	// Barometer
	LCD5110_drawBitmap(0, 16, Barometer, 16, 16, 0, &lcd1.hw_conf);
	LCD5110_set_cursor(18, 20, &lcd1);
	LCD5110_print("Lel:", BLACK, &lcd1);

	// Pressure
	Draw_pressure_values(Buffer, dataINTHolders_, dataUINTHolders_);

	// Update
	LCD5110_refresh(&lcd1);

	// Let it stay for a while on the screen
	HAL_Delay(3000);
}

void Draw_gas_animation()
{
	// 5 times for 3000 delay
	for (int i = 0; i < 5; ++i)
	{
		LCD5110_drawBitmap(0, 0, Gas_1, 16, 16, 0, &lcd1.hw_conf);
		LCD5110_refresh(&lcd1);
		// Delays give both animation and staying on the screen
		HAL_Delay(600);

		LCD5110_drawBitmap(0, 0, Gas_2, 16, 16, 0, &lcd1.hw_conf);
		LCD5110_refresh(&lcd1);
		HAL_Delay(600);
	}
}

void Draw_gas_values_()
{
	LCD5110_set_cursor(18, 4, &lcd1);
	LCD5110_print("Gas:", BLACK, &lcd1);
	LCD5110_putint(10, 40, 4, -1, BLACK, &lcd1);
}

void Draw_spec_screen_two()
{
	// Clear everything already drawn
	LCD5110_clear_scr(&lcd1);

	// Gas
	// Draw gas specs first - no need to redraw them in anim
	Draw_gas_values_();
	// Draw animation
	Draw_gas_animation();

	// Update
	LCD5110_refresh(&lcd1);
}


void FullfillDataArrays(uint8_t *Buffer, int16_t *dataINTHolders_, uint16_t *dataUINTHolders_){
  int count = 0;
  for (int i = 0; i < 11; i ++) {
	HAL_I2C_Mem_Read(&hi2c2, (uint16_t) (0xEE), (uint16_t) barRegisters[i], I2C_MEMADD_SIZE_8BIT, Buffer, 2, 500);
	if(i == 3 || i == 4 || i == 5){
		 dataUINTHolders_[count] = (Buffer[0]<<8) | (Buffer[1]);
		 count++;
	}
	else{
		 dataINTHolders_[i] = (Buffer[0]<<8) | (Buffer[1]);
	}
  }
}

/* USER CODE END 0 */

int main(void)
{

  /* USER CODE BEGIN 1 */

	int16_t dataINTHolders[11] = {AC1, AC2, AC3, 1, 1, 1, B1, B2, MB, MC, MD}; // 1 1 1  take the place for other data type elements
	uint16_t dataUINTHolders[3] = {AC4, AC5, AC6};

	uint8_t Buffer[8];


  /* USER CODE END 1 */

  /* MCU Configuration----------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* Configure the system clock */
  SystemClock_Config();

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_RNG_Init();
  MX_SPI2_Init();
  MX_I2C2_Init();

  /* USER CODE BEGIN 2 */
  lcd1.hw_conf.spi_handle = &hspi2;
  lcd1.hw_conf.spi_cs_pin =  LCD1_CS_Pin;
  lcd1.hw_conf.spi_cs_port = LCD1_CS_GPIO_Port;
  lcd1.hw_conf.rst_pin =  LCD1_RST_Pin;
  lcd1.hw_conf.rst_port = LCD1_RST_GPIO_Port;
  lcd1.hw_conf.dc_pin =  LCD1_DC_Pin;
  lcd1.hw_conf.dc_port = LCD1_DC_GPIO_Port;
  lcd1.def_scr = lcd5110_def_scr;
  LCD5110_init(&lcd1.hw_conf, LCD5110_NORMAL_MODE, 0x40, 2, 3);

  FullfillDataArrays(Buffer, dataINTHolders, dataUINTHolders);

  // Clear everything already drawn
  LCD5110_clear_scr(&lcd1);
  LCD5110_drawBitmap(0, 0, babe, 84, 48, 0, &lcd1.hw_conf);
  // Update
  LCD5110_refresh(&lcd1);
  HAL_Delay(3000);

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
	  Draw_spec_screen_one(Buffer, dataINTHolders, dataUINTHolders);
	  Draw_spec_screen_two();

  /* USER CODE END WHILE */

  /* USER CODE BEGIN 3 */

  }
  /* USER CODE END 3 */

}

/** System Clock Configuration
*/
void SystemClock_Config(void)
{

  RCC_OscInitTypeDef RCC_OscInitStruct;
  RCC_ClkInitTypeDef RCC_ClkInitStruct;

    /**Configure the main internal regulator output voltage 
    */
  __HAL_RCC_PWR_CLK_ENABLE();

  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

    /**Initializes the CPU, AHB and APB busses clocks 
    */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 336;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 8;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

    /**Initializes the CPU, AHB and APB busses clocks 
    */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    Error_Handler();
  }

    /**Configure the Systick interrupt time 
    */
  HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);

    /**Configure the Systick 
    */
  HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

  /* SysTick_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @param  None
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler */
  /* User can add his own implementation to report the HAL error return state */
  while(1) 
  {
  }
  /* USER CODE END Error_Handler */ 
}

#ifdef USE_FULL_ASSERT

/**
   * @brief Reports the name of the source file and the source line number
   * where the assert_param error has occurred.
   * @param file: pointer to the source file name
   * @param line: assert_param error line source number
   * @retval None
   */
void assert_failed(uint8_t* file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
    ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */

}

#endif

/**
  * @}
  */ 

/**
  * @}
*/ 

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
