/****************************************************************************
 * main.c
 *
 *   Authors: Daniel Pereira de Carvalho <daniel.carvalho@ufu.br>
 *            Marcelo Barros de Almeida  <marcelo.barros@ufu.br>
 *
 ****************************************************************************/

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <stdint.h>

 /****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

#define SRAM_START  0x20000000U                  /* Inicio da SRAM CORTEX-M */
#define SRAM_SIZE   (128U * 1024U)               /* Tam. SRAM STM32F411 128K */
#define SRAM_END    ((SRAM_START) + (SRAM_SIZE)) /* Final da SRAM STM32F411 */

#define STACK_START SRAM_END                     /* Inicio da Stack */

/****************************************************************************
 * Private Function Prototypes
 ****************************************************************************/

int main(void);

/* Prototipos de funcoes para as System Exceptions */

void reset_handler     (void);
void nmi_handler       (void) __attribute__ ((weak, alias("default_handler")));
void hardfault_handler (void) __attribute__ ((weak, alias("default_handler")));
void memmanage_handler (void) __attribute__ ((weak, alias("default_handler")));
void busfault_handler  (void) __attribute__ ((weak, alias("default_handler")));
void usagefault_handler(void) __attribute__ ((weak, alias("default_handler")));
void svc_handler       (void) __attribute__ ((weak, alias("default_handler")));
void debugmon_handler  (void) __attribute__ ((weak, alias("default_handler")));
void pendsv_handler    (void) __attribute__ ((weak, alias("default_handler")));
void systick_handler   (void) __attribute__ ((weak, alias("default_handler")));

void WWDG_handler             (void) __attribute__ ((weak, alias("default_handler")));
void PVD_handler              (void) __attribute__ ((weak, alias("default_handler")));
void TAMPSTAMP_handler        (void) __attribute__ ((weak, alias("default_handler")));
void RTCWKUP_handler          (void) __attribute__ ((weak, alias("default_handler")));
void FLASH_handler            (void) __attribute__ ((weak, alias("default_handler")));
void RCC_handler              (void) __attribute__ ((weak, alias("default_handler")));
void EXTI0_handler            (void) __attribute__ ((weak, alias("default_handler")));
void EXTI1_handler            (void) __attribute__ ((weak, alias("default_handler")));
void EXTI2_handler            (void) __attribute__ ((weak, alias("default_handler")));
void EXTI3_handler            (void) __attribute__ ((weak, alias("default_handler")));
void EXTI4_handler            (void) __attribute__ ((weak, alias("default_handler")));
void DMA1Stream0_handler      (void) __attribute__ ((weak, alias("default_handler")));
void DMA1Stream1_handler      (void) __attribute__ ((weak, alias("default_handler")));
void DMA1Stream2_handler      (void) __attribute__ ((weak, alias("default_handler")));
void DMA1Stream3_handler      (void) __attribute__ ((weak, alias("default_handler")));
void DMA1Stream4_handler      (void) __attribute__ ((weak, alias("default_handler")));
void DMA1Stream5_handler      (void) __attribute__ ((weak, alias("default_handler")));
void DMA1Stream6_handler      (void) __attribute__ ((weak, alias("default_handler")));
void ADC_handler              (void) __attribute__ ((weak, alias("default_handler")));
void EXTI9_handler            (void) __attribute__ ((weak, alias("default_handler")));
void TIM1BRKTIM9_handler      (void) __attribute__ ((weak, alias("default_handler")));
void TIM1UPTIM10_handler      (void) __attribute__ ((weak, alias("default_handler")));
void TIM1TRGCOMTIM11_handler  (void) __attribute__ ((weak, alias("default_handler")));
void TIM1CC_handler           (void) __attribute__ ((weak, alias("default_handler")));
void TIM2_handler             (void) __attribute__ ((weak, alias("default_handler")));
void TIM3_handler             (void) __attribute__ ((weak, alias("default_handler")));
void TIM4_handler             (void) __attribute__ ((weak, alias("default_handler")));
void I2C1EV_handler           (void) __attribute__ ((weak, alias("default_handler")));
void I2C1ER_handler           (void) __attribute__ ((weak, alias("default_handler")));
void I2C2EV_handler           (void) __attribute__ ((weak, alias("default_handler")));
void I2C2ER_handler           (void) __attribute__ ((weak, alias("default_handler")));
void SPI1_handler             (void) __attribute__ ((weak, alias("default_handler")));
void SPI2_handler             (void) __attribute__ ((weak, alias("default_handler")));
void USART1_handler           (void) __attribute__ ((weak, alias("default_handler")));
void USART2_handler           (void) __attribute__ ((weak, alias("default_handler")));
void EXTI1510_handler         (void) __attribute__ ((weak, alias("default_handler")));
void RTCAlarm_handler         (void) __attribute__ ((weak, alias("default_handler")));
void OTGFSWKUP_handler        (void) __attribute__ ((weak, alias("default_handler")));
void DMA1Stream7_handler      (void) __attribute__ ((weak, alias("default_handler")));
void SDIO_handler             (void) __attribute__ ((weak, alias("default_handler")));
void TIM5_handler             (void) __attribute__ ((weak, alias("default_handler")));
void SPI3_handler             (void) __attribute__ ((weak, alias("default_handler")));
void DMA2Stream0_handler      (void) __attribute__ ((weak, alias("default_handler")));
void DMA2Stream1_handler      (void) __attribute__ ((weak, alias("default_handler")));
void DMA2Stream2_handler      (void) __attribute__ ((weak, alias("default_handler")));
void DMA2Stream3_handler      (void) __attribute__ ((weak, alias("default_handler")));
void DMA2Stream4_handler      (void) __attribute__ ((weak, alias("default_handler")));
void OTGFS_handler            (void) __attribute__ ((weak, alias("default_handler")));
void DMA2Stream5_handler      (void) __attribute__ ((weak, alias("default_handler")));
void DMA2Stream6_handler      (void) __attribute__ ((weak, alias("default_handler")));
void DMA2Stream7_handler      (void) __attribute__ ((weak, alias("default_handler")));
void USART6_handler           (void) __attribute__ ((weak, alias("default_handler")));
void I2C3EV_handler           (void) __attribute__ ((weak, alias("default_handler")));
void I2C3ER_handler           (void) __attribute__ ((weak, alias("default_handler")));
void FPU_handler              (void) __attribute__ ((weak, alias("default_handler")));
void SPI4_handler             (void) __attribute__ ((weak, alias("default_handler")));
void SPI5_handler             (void) __attribute__ ((weak, alias("default_handler")));

 /****************************************************************************
 * External Data
 ****************************************************************************/

/* Variaveis exportadas pelo linker script */

extern uint32_t _sdata;     /* Inicio da secao .data */
extern uint32_t _edata;     /* Fim da secao .data */
extern uint32_t _la_data;   /* Origem da secao .data na FLASH */

extern uint32_t _sbss;      /* Inicio da secao .bss */
extern uint32_t _ebss;      /* Fim da secao .bss */

/****************************************************************************
 * Private Data
 ****************************************************************************/

/* Tabela de Vetores de Interrupção */

uint32_t vectors[] __attribute__((section(".isr_vectors"))) =
{
  STACK_START,                            /* 0x0000 0000 */
  (uint32_t)reset_handler,                /* 0x0000 0004 */
  (uint32_t)nmi_handler,                  /* 0x0000 0008 */
  (uint32_t)hardfault_handler,            /* 0x0000 000c */
  (uint32_t)memmanage_handler,            /* 0x0000 0010 */
  (uint32_t)busfault_handler,             /* 0x0000 0014 */
  (uint32_t)usagefault_handler,           /* 0x0000 0018 */
  0,                                      /* 0x0000 001c */
  0,                                      /* 0x0000 0020 */
  0,                                      /* 0x0000 0024 */
  0,                                      /* 0x0000 0028 */
  (uint32_t)svc_handler,                  /* 0x0000 002c */
  (uint32_t)debugmon_handler,             /* 0x0000 0030 */
  0,                                      /* 0x0000 0034 */
  (uint32_t)pendsv_handler,               /* 0x0000 0038 */
  (uint32_t)systick_handler,              /* 0x0000 003c */
  (uint32_t)WWDG_handler,                 /* 0x0000 0040 */
  (uint32_t)PVD_handler,                  /* 0x0000 0044 */
  (uint32_t)TAMPSTAMP_handler,            /* 0x0000 0048 */
  (uint32_t)RTCWKUP_handler,              /* 0x0000 004c */
  (uint32_t)FLASH_handler,                /* 0x0000 0050 */
  (uint32_t)RCC_handler,                  /* 0x0000 0054 */
  (uint32_t)EXTI0_handler,                /* 0x0000 0058 */
  (uint32_t)EXTI1_handler,                /* 0x0000 005c */
  (uint32_t)EXTI2_handler,                /* 0x0000 0060 */
  (uint32_t)EXTI3_handler,                /* 0x0000 0064 */
  (uint32_t)EXTI4_handler,                /* 0x0000 0068 */
  (uint32_t)DMA1Stream0_handler,          /* 0x0000 006c */
  (uint32_t)DMA1Stream1_handler,          /* 0x0000 0070 */
  (uint32_t)DMA1Stream2_handler,          /* 0x0000 0074 */
  (uint32_t)DMA1Stream3_handler,          /* 0x0000 0078 */
  (uint32_t)DMA1Stream4_handler,          /* 0x0000 007c */
  (uint32_t)DMA1Stream5_handler,          /* 0x0000 0080 */
  (uint32_t)DMA1Stream6_handler,          /* 0x0000 0084 */
  (uint32_t)ADC_handler,                  /* 0x0000 0088 */
  (uint32_t)EXTI9_handler,                /* 0x0000 009c */
  (uint32_t)TIM1BRKTIM9_handler,          /* 0x0000 00A0 */
  (uint32_t)TIM1UPTIM10_handler,          /* 0x0000 00A4 */
  (uint32_t)TIM1TRGCOMTIM11_handler,      /* 0x0000 00A8 */
  (uint32_t)TIM1CC_handler,               /* 0x0000 00Ac */
  (uint32_t)TIM2_handler,                 /* 0x0000 00B0 */
  (uint32_t)TIM3_handler,                 /* 0x0000 00B4 */
  (uint32_t)TIM4_handler,                 /* 0x0000 00B8 */
  (uint32_t)I2C1EV_handler,               /* 0x0000 00Bc */
  (uint32_t)I2C1ER_handler,               /* 0x0000 00C0 */
  (uint32_t)I2C2EV_handler,               /* 0x0000 00C4 */
  (uint32_t)I2C2ER_handler,               /* 0x0000 00C8 */
  (uint32_t)SPI1_handler,                 /* 0x0000 00Cc */
  (uint32_t)SPI2_handler,                 /* 0x0000 00D0 */
  (uint32_t)USART1_handler,               /* 0x0000 00D4 */
  (uint32_t)USART2_handler,               /* 0x0000 00D8 */
  (uint32_t)EXTI1510_handler,             /* 0x0000 00E0 */
  (uint32_t)RTCAlarm_handler,             /* 0x0000 00E4 */
  (uint32_t)OTGFSWKUP_handler,            /* 0x0000 00E8 */
  (uint32_t)DMA1Stream7_handler,          /* 0x0000 00FC */
  (uint32_t)SDIO_handler,                 /* 0x0000 0104 */
  (uint32_t)TIM5_handler,                 /* 0x0000 0108 */
  (uint32_t)SPI3_handler,                 /* 0x0000 010c */
  (uint32_t)DMA2Stream0_handler,          /* 0x0000 0120 */
  (uint32_t)DMA2Stream1_handler,          /* 0x0000 0124 */
  (uint32_t)DMA2Stream2_handler,          /* 0x0000 0128 */
  (uint32_t)DMA2Stream3_handler,          /* 0x0000 012c */
  (uint32_t)DMA2Stream4_handler,          /* 0x0000 0130 */
  (uint32_t)OTGFS_handler,                /* 0x0000 014c */
  (uint32_t)DMA2Stream5_handler,          /* 0x0000 0150 */
  (uint32_t)DMA2Stream6_handler,          /* 0x0000 0154 */
  (uint32_t)DMA2Stream7_handler,          /* 0x0000 0158 */
  (uint32_t)USART6_handler,               /* 0x0000 015c */
  (uint32_t)I2C3EV_handler,               /* 0x0000 0160 */
  (uint32_t)I2C3ER_handler,               /* 0x0000 0164 */
  (uint32_t)FPU_handler,                  /* 0x0000 0184 */
  (uint32_t)SPI4_handler,                 /* 0x0000 0190 */
  (uint32_t)SPI5_handler,                 /* 0x0000 0194 */
};

/****************************************************************************
 * Private Functions
 ****************************************************************************/

void reset_handler(void)
{
  uint32_t i; 

  /* Copia a secao .data para a RAM */
   
  uint32_t size = (uint32_t)&_edata - (uint32_t)&_sdata;
  uint8_t *pDst = (uint8_t*)&_sdata;                      /* SRAM */
  uint8_t *pSrc = (uint8_t*)&_la_data;                    /* FLASH */
  
  for(i = 0; i < size; i++)
  {
    *pDst++ = *pSrc++;
  }

  /* Preenche a secao .bss com zero */

  size = (uint32_t)&_ebss - (uint32_t)&_sbss;
  pDst = (uint8_t*)&_sbss;
  for(i = 0 ; i < size; i++)
  {
    *pDst++ = 0;
  }

  /* Chama a funcao main() */

  main();
}

void default_handler(void)
{
  while(1){};
}
