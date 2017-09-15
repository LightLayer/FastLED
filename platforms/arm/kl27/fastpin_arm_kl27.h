#ifndef __INC_FASTPIN_ARM_KL27
#define __INC_FASTPIN_ARM_KL27

FASTLED_NAMESPACE_BEGIN

#if defined(FASTLED_FORCE_SOFTWARE_PINS)
#warning "Software pin support forced, pin access will be sloightly slower."
#define NO_HARDWARE_PIN_SUPPORT
#undef HAS_HARDWARE_PIN_SUPPORT

#else

#include "fsl_port.h"
#include "fsl_gpio.h"

/// Template definition for STM32 style ARM pins, providing direct access to the various GPIO registers.  Note that this
/// uses the full port GPIO registers.  In theory, in some way, bit-band register access -should- be faster, however I have found
/// that something about the way gcc does register allocation results in the bit-band code being slower.  It will need more fine tuning.
/// The registers are data output, set output, clear output, toggle output, input, and direction

template<uint8_t PIN, uint8_t _BIT, uint32_t _MASK, typename GPIO_GROUP, typename PORT_GROUP> class _ARMPIN {
public:
  typedef volatile uint32_t * port_ptr_t;
  typedef uint32_t port_t;

  inline static void setOutput() {
	  gpio_pin_config_t conf = {kGPIO_DigitalOutput, 0};
	  PORT_SetPinMux((PORT_Type *)PORT_GROUP::r(), _BIT, kPORT_MuxAsGpio);
	  GPIO_PinInit((GPIO_Type *)GPIO_GROUP::r(), _BIT, &conf);
  }
  inline static void setInput() {  }

  inline static void hi() __attribute__ ((always_inline)) { GPIO_GROUP::r()->PSOR = _MASK; }
  inline static void lo() __attribute__ ((always_inline)) { GPIO_GROUP::r()->PCOR = _MASK; }
  inline static void set(register port_t val) __attribute__ ((always_inline)) { GPIO_GROUP::r()->PDOR = val; }

  inline static void strobe() __attribute__ ((always_inline)) { toggle(); toggle(); }

  inline static void toggle() __attribute__ ((always_inline)) { GPIO_GROUP::r()->PTOR = _MASK; }

  inline static void hi(register port_ptr_t port) __attribute__ ((always_inline)) { hi(); }
  inline static void lo(register port_ptr_t port) __attribute__ ((always_inline)) { lo(); }
  inline static void fastset(register port_ptr_t port, register port_t val) __attribute__ ((always_inline)) { *port = val; }

  inline static port_t hival() __attribute__ ((always_inline)) { return GPIO_GROUP::r()->PDOR | _MASK; }
  inline static port_t loval() __attribute__ ((always_inline)) { return GPIO_GROUP::r()->PDOR & ~_MASK; }
  inline static port_ptr_t port() __attribute__ ((always_inline)) { return &(GPIO_GROUP::r()->PDOR); }
  inline static port_ptr_t sport() __attribute__ ((always_inline)) { return &(GPIO_GROUP::r()->PSOR); }
  inline static port_ptr_t cport() __attribute__ ((always_inline)) { return &(GPIO_GROUP::r()->PCOR); }
  inline static port_t mask() __attribute__ ((always_inline)) { return _MASK; }
};

#define _R(T) struct __gen_struct_ ## T
#define _RD32(T) struct __gen_struct_ ## T { static __attribute__((always_inline)) inline volatile GPIO_Type * r() { return T; } };
#define _PD32(T) struct __gen_struct_ ## T { static __attribute__((always_inline)) inline volatile PORT_Type * r() { return T; } };

#define _IO32(L) _RD32(GPIO ## L); _PD32(PORT ## L)

#define _DEFPIN_ARM(PIN, L, BIT) template<> class FastPin<PIN> : public _ARMPIN<PIN, BIT, 1 << BIT, _R(GPIO ## L), _R(PORT ## L)> {};

// Actual pin definitions

_IO32(A); _IO32(B); _IO32(C); _IO32(D); _IO32(E);

#define MAX_PIN 8
//_DEFPIN_ARM(1, C, 1); _DEFPIN_ARM(2, C, 2); _DEFPIN_ARM(3, D, 3); _DEFPIN_ARM(4, D, 4); _DEFPIN_ARM(5, D, 5);
//_DEFPIN_ARM(6, B, 18); _DEFPIN_ARM(7, B, 19); _DEFPIN_ARM(8, A, 13);

_DEFPIN_ARM(1, C, 5); _DEFPIN_ARM(2, C, 6);

// R G and B pins on KFRDM-L27

//PTD4 -> J1-9
//PTD5 -> J1-11

//#define SPI_DATA 24
//#define SPI_CLOCK 23

#define HAS_HARDWARE_PIN_SUPPORT 1

#endif // FASTLED_FORCE_SOFTWARE_PINS

FASTLED_NAMESPACE_END


#endif // __INC_FASTPIN_ARM_KL27
