#ifndef __INC_LED_SYSDEFS_ARM_KL27
#define __INC_LED_SYSDEFS_ARM_KL27

#include <stdint.h>
#include "MKL27Z644.h"
#include "core_cm0plus.h"
#include "core_cmFunc.h"
#include <math.h>

#define min(a,b) ((a)<(b)?(a):(b))
#define max(A,B) ( (A)>(B) ? (A) : (B))
#define abs(A) ( (A) < 0 ? -(A) : (A))

typedef volatile uint32_t RoReg;
typedef volatile uint32_t RwReg;
typedef uint32_t prog_uint32_t;
typedef uint8_t boolean;
typedef uint8_t byte;

#define PROGMEM
#define NO_PROGMEM
#define NEED_CXX_BITS

#define FASTLED_ARM
#define FASTLED_ARM_M0_PLUS

#ifndef FASTLED_USE_PROGMEM
#define FASTLED_USE_PROGMEM 0
#endif

#ifndef FASTLED_ALLOW_INTERRUPTS
#define FASTLED_ALLOW_INTERRUPTS 1
#endif

#if FASTLED_ALLOW_INTERRUPTS == 1
#define FASTLED_ACCURATE_CLOCK
#endif

//#if defined(__cplusplus)
//extern "C" {
//#endif /* __cplusplus */
//
//extern volatile uint32_t systick_millis_count;
//#define MS_COUNTER systick_millis_count
//
//#if defined(__cplusplus)
//}
//#endif


#define FASTLED_NO_PINMAP

#ifndef F_CPU
#define F_CPU 48000000
#endif

#define cli()  __disable_irq();
#define sei() __enable_irq();

#endif
