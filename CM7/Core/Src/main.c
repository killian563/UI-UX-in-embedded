#include "stm32h7xx_hal.h"
#include "arm_math.h"
#include "stm32h745i_discovery_lcd.h"
#include "stm32h745i_discovery_ts.h"
#include "stm32h7xx_hal_ltdc.h"
#include <string.h>
#include <stdio.h>

// ADC, DMA, and FFT Configuration
#define ADC_CHANNEL ADC_CHANNEL_0
#define ADC_SAMPLING_RATE 10000  // 10 kHz for low-frequency signals
#define FFT_SIZE_DEFAULT 256
#define MAX_FFT_SIZE 1024
#define LCD_WIDTH 480
#define LCD_HEIGHT 272

// FFT and Windowing Variables
uint32_t fftSize = FFT_SIZE_DEFAULT;
float32_t adcBuffer[MAX_FFT_SIZE];
float32_t fftInput[MAX_FFT_SIZE];
float32_t fftOutput[MAX_FFT_SIZE];
float32_t fftMagnitude[MAX_FFT_SIZE / 2];
arm_rfft_fast_instance_f32 fftHandler;
float32_t windowCoeff[MAX_FFT_SIZE];

// Touch and UI Variables
TS_State_t TS_State;
TS_Init_t TS_Init;
typedef enum { RECTANGULAR, HANNING, HAMMING, BLACKMAN } WindowType;
WindowType currentWindow = RECTANGULAR;
typedef enum { STOPPED, RUNNING } AnalysisState;
AnalysisState state = STOPPED;
float scale = 1.0f;

// Button Areas (x, y, width, height)
#define BUTTON_START_X 20
#define BUTTON_START_Y 220
#define BUTTON_WIDTH 100
#define BUTTON_HEIGHT 40
#define BUTTON_FFT_X 140
#define BUTTON_SCALE_X 260
#define BUTTON_WINDOW_X 380

// ADC, DMA, and Timer Handles
ADC_HandleTypeDef hadc1;
DMA_HandleTypeDef hdma_adc1;
TIM_HandleTypeDef htim2;

// Function Prototypes
void SystemClock_Config(void);
void ADC_Init(void);
void TIM_Init(void);
void ApplyWindow(float32_t *input, float32_t *window, uint32_t size);
void DrawSpectrum(void);
void DrawButton(uint32_t x, uint32_t y, uint8_t pressed);
void CheckTouch(void);
void Error_Handler(void);

// Main Function
int main(void) {
    HAL_Init();
    SystemClock_Config();
    BSP_LCD_Init(0, LCD_ORIENTATION_LANDSCAPE);
    BSP_LCD_DisplayOn(0);

    // Initialize Touchscreen
    TS_Init.Width = LCD_WIDTH;
    TS_Init.Height = LCD_HEIGHT;
    BSP_TS_Init(0, &TS_Init);

    ADC_Init();
    TIM_Init();

    // Initialize FFT
    arm_rfft_fast_init_f32(&fftHandler, fftSize);

    // Generate Window Coefficients
    for (uint32_t i = 0; i < fftSize; i++) {
        switch (currentWindow) {
            case RECTANGULAR:
                windowCoeff[i] = 1.0f;
                break;
            case HANNING:
                windowCoeff[i] = 0.5f * (1.0f - arm_cos_f32(2.0f * PI * i / (fftSize - 1)));
                break;
            case HAMMING:
                windowCoeff[i] = 0.54f - 0.46f * arm_cos_f32(2.0f * PI * i / (fftSize - 1));
                break;
            case BLACKMAN:
                windowCoeff[i] = 0.42f - 0.5f * arm_cos_f32(2.0f * PI * i / (fftSize - 1)) +
                                 0.08f * arm_cos_f32(4.0f * PI * i / (fftSize - 1));
                break;
        }
    }

    // Start ADC with DMA
    HAL_ADC_Start_DMA(&hadc1, (uint32_t *)adcBuffer, fftSize);
    HAL_TIM_Base_Start(&htim2);

    while (1) {
        if (state == RUNNING) {
            // Apply window to ADC data
            ApplyWindow(adcBuffer, windowCoeff, fftSize);

            // Perform FFT
            arm_rfft_fast_f32(&fftHandler, fftInput, fftOutput, 0);
            arm_cmplx_mag_f32(fftOutput, fftMagnitude, fftSize / 2);

            // Draw spectrum and UI
            DrawSpectrum();
        }
        CheckTouch();
        DrawButton(BUTTON_START_X, BUTTON_START_Y, state == RUNNING);
        DrawButton(BUTTON_FFT_X, BUTTON_START_Y, 0);
        DrawButton(BUTTON_SCALE_X, BUTTON_START_Y, 0);
        DrawButton(BUTTON_WINDOW_X, BUTTON_START_Y, 0);
        HAL_Delay(50);
    }
}

// System Clock Configuration for CM7
void SystemClock_Config(void) {
    RCC_OscInitTypeDef RCC_OscInitStruct = {0};
    RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

    // Configure the main internal regulator output voltage
    __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE0);
    while (!__HAL_PWR_GET_FLAG(PWR_FLAG_VOSRDY)) {}

    // Initialize HSE and PLL
    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
    RCC_OscInitStruct.HSEState = RCC_HSE_ON;
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
    RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
    RCC_OscInitStruct.PLL.PLLM = 5;
    RCC_OscInitStruct.PLL.PLLN = 160;
    RCC_OscInitStruct.PLL.PLLP = 2;
    RCC_OscInitStruct.PLL.PLLQ = 2;
    RCC_OscInitStruct.PLL.PLLR = 2;
    HAL_RCC_OscConfig(&RCC_OscInitStruct);

    // Initialize CPU, AHB, and APB buses
    RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK |
                                  RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2 |
                                  RCC_CLOCKTYPE_D1PCLK1 | RCC_CLOCKTYPE_D3PCLK1;
    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
    RCC_ClkInitStruct.SYSCLKDivider = RCC_SYSCLK_DIV1;
    RCC_ClkInitStruct.AHBCLKDivider = RCC_HCLK_DIV2;
    RCC_ClkInitStruct.APB1CLKDivider = RCC_APB1_DIV2;
    RCC_ClkInitStruct.APB2CLKDivider = RCC_APB2_DIV2;
    RCC_ClkInitStruct.APB3CLKDivider = RCC_APB3_DIV2;
    RCC_ClkInitStruct.APB4CLKDivider = RCC_APB4_DIV2;
    HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_4);
}

// ADC Initialization
void ADC_Init(void) {
    ADC_ChannelConfTypeDef sConfig = {0};
    hadc1.Instance = ADC1;
    hadc1.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV4;
    hadc1.Init.Resolution = ADC_RESOLUTION_12B;
    hadc1.Init.ScanConvMode = ADC_SCAN_DISABLE;
    hadc1.Init.ContinuousConvMode = ENABLE;
    hadc1.Init.DiscontinuousConvMode = DISABLE;
    hadc1.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_RISING;
    hadc1.Init.ExternalTrigConv = ADC_EXTERNALTRIG_T2_TRGO;
    hadc1.Init.Overrun = ADC_OVR_DATA_OVERWRITTEN;
    hadc1.Init.OversamplingMode = DISABLE;
    HAL_ADC_Init(&hadc1);

    sConfig.Channel = ADC_CHANNEL;
    sConfig.Rank = ADC_REGULAR_RANK_1;
    sConfig.SamplingTime = ADC_SAMPLETIME_810CYCLES_5;
    HAL_ADC_ConfigChannel(&hadc1, &sConfig);

    // DMA for ADC
    __HAL_RCC_DMA1_CLK_ENABLE();
    hdma_adc1.Instance = DMA1_Stream0;
    hdma_adc1.Init.Request = DMA_REQUEST_ADC1;
    hdma_adc1.Init.Direction = DMA_PERIPH_TO_MEMORY;
    hdma_adc1.Init.PeriphInc = DMA_PINC_DISABLE;
    hdma_adc1.Init.MemInc = DMA_MINC_ENABLE;
    hdma_adc1.Init.PeriphDataAlignment = DMA_PDATAALIGN_HALFWORD;
    hdma_adc1.Init.MemDataAlignment = DMA_MDATAALIGN_HALFWORD;
    hdma_adc1.Init.Mode = DMA_CIRCULAR;
    hdma_adc1.Init.Priority = DMA_PRIORITY_HIGH;
    HAL_DMA_Init(&hdma_adc1);
    __HAL_LINKDMA(&hadc1, DMA_Handle, hdma_adc1);
}

// Timer Initialization for ADC Trigger
void TIM_Init(void) {
    __HAL_RCC_TIM2_CLK_ENABLE();
    htim2.Instance = TIM2;
    htim2.Init.Prescaler = (SystemCoreClock / 2 / ADC_SAMPLING_RATE) - 1;
    htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
    htim2.Init.Period = 1;
    htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
    HAL_TIM_Base_Init(&htim2);

    TIM_MasterConfigTypeDef sMasterConfig = {0};
    sMasterConfig.MasterOutputTrigger = TIM_TRGO_UPDATE;
    sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
    HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig);
}

// Apply Window Function
void ApplyWindow(float32_t *input, float32_t *window, uint32_t size) {
    for (uint32_t i = 0; i < size; i++) {
        fftInput[i] = input[i] * window[i];
    }
}

// Draw Spectrum on LCD
void DrawSpectrum(void) {
    BSP_LCD_FillRect(0, 0, 0, LCD_WIDTH, LCD_HEIGHT, LCD_COLOR_RGB565_BLACK);
    uint32_t displayPoints = fftSize / 2;
    float maxMag = 0.0f;
    for (uint32_t i = 1; i < displayPoints; i++) {
        if (fftMagnitude[i] > maxMag) maxMag = fftMagnitude[i];
    }
    if (maxMag < 1.0f) maxMag = 1.0f;

    for (uint32_t i = 1; i < displayPoints; i++) {
        uint32_t x = (i * LCD_WIDTH) / displayPoints;
        uint32_t height = (uint32_t)(fftMagnitude[i] * scale * (LCD_HEIGHT - 60) / maxMag);
        if (height > LCD_HEIGHT - 60) height = LCD_HEIGHT - 60;
        BSP_LCD_DrawVLine(0, x, LCD_HEIGHT - height, height, LCD_COLOR_RGB565_GREEN);
    }
}

// Draw Button on LCD
void DrawButton(uint32_t x, uint32_t y, uint8_t pressed) {
    uint32_t color = pressed ? LCD_COLOR_RGB565_RED : LCD_COLOR_RGB565_BLUE;
    BSP_LCD_FillRect(0, x, y, BUTTON_WIDTH, BUTTON_HEIGHT, color);
}

// Check Touch Input
void CheckTouch(void) {
    BSP_TS_GetState(0, &TS_State);
    if (TS_State.TouchDetected) {
        uint16_t x = TS_State.TouchX;
        uint16_t y = TS_State.TouchY;

        // Start/Stop Button
        if (x >= BUTTON_START_X && x <= BUTTON_START_X + BUTTON_WIDTH &&
            y >= BUTTON_START_Y && y <= BUTTON_START_Y + BUTTON_HEIGHT) {
            state = (state == RUNNING) ? STOPPED : RUNNING;
            DrawButton(BUTTON_START_X, BUTTON_START_Y, 1);
            HAL_Delay(200);
        }
        // FFT Size Button
        else if (x >= BUTTON_FFT_X && x <= BUTTON_FFT_X + BUTTON_WIDTH &&
                 y >= BUTTON_START_Y && y <= BUTTON_START_Y + BUTTON_HEIGHT) {
            fftSize = (fftSize == 128) ? 256 : (fftSize == 256) ? 512 : (fftSize == 512) ? 1024 : 128;
            arm_rfft_fast_init_f32(&fftHandler, fftSize);
            for (uint32_t i = 0; i < fftSize; i++) {
                switch (currentWindow) {
                    case RECTANGULAR: windowCoeff[i] = 1.0f; break;
                    case HANNING: windowCoeff[i] = 0.5f * (1.0f - arm_cos_f32(2.0f * PI * i / (fftSize - 1))); break;
                    case HAMMING: windowCoeff[i] = 0.54f - 0.46f * arm_cos_f32(2.0f * PI * i / (fftSize - 1)); break;
                    case BLACKMAN: windowCoeff[i] = 0.42f - 0.5f * arm_cos_f32(2.0f * PI * i / (fftSize - 1)) +
                                                    0.08f * arm_cos_f32(4.0f * PI * i / (fftSize - 1)); break;
                }
            }
            DrawButton(BUTTON_FFT_X, BUTTON_START_Y, 1);
            HAL_Delay(200);
        }
        // Scale/Zoom Button
        else if (x >= BUTTON_SCALE_X && x <= BUTTON_SCALE_X + BUTTON_WIDTH &&
                 y >= BUTTON_START_Y && y <= BUTTON_START_Y + BUTTON_HEIGHT) {
            scale = (scale >= 2.0f) ? 1.0f : scale + 0.5f;
            DrawButton(BUTTON_SCALE_X, BUTTON_START_Y, 1);
            HAL_Delay(200);
        }
        // Windowing Button
        else if (x >= BUTTON_WINDOW_X && x <= BUTTON_WINDOW_X + BUTTON_WIDTH &&
                 y >= BUTTON_START_Y && y <= BUTTON_START_Y + BUTTON_HEIGHT) {
            currentWindow = (WindowType)((currentWindow + 1) % 4);
            for (uint32_t i = 0; i < fftSize; i++) {
                switch (currentWindow) {
                    case RECTANGULAR: windowCoeff[i] = 1.0f; break;
                    case HANNING: windowCoeff[i] = 0.5f * (1.0f - arm_cos_f32(2.0f * PI * i / (fftSize - 1))); break;
                    case HAMMING: windowCoeff[i] = 0.54f - 0.46f * arm_cos_f32(2.0f * PI * i / (fftSize - 1)); break;
                    case BLACKMAN: windowCoeff[i] = 0.42f - 0.5f * arm_cos_f32(2.0f * PI * i / (fftSize - 1)) +
                                                    0.08f * arm_cos_f32(4.0f * PI * i / (fftSize - 1)); break;
                }
            }
            DrawButton(BUTTON_WINDOW_X, BUTTON_START_Y, 1);
            HAL_Delay(200);
        }
    }
}

// HAL ADC Callback
void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef *hadc) {
    if (state == RUNNING && hadc == &hadc1) {
        // ADC conversion complete, data is ready in adcBuffer
    }
}

// Error Handler
void Error_Handler(void) {
    while (1) {
        // Infinite loop for error handling
    }
}
