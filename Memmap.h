#ifndef MEMMAP_H
#define MEMMAP_H

#include "Gpio.h"
#include "Gpio_Isr.h"
#include "Softimer.h"

	/*__GPIO__*/
#ifdef GPIO_START_SECT_DATA
	#undef GPIO_START_SECT_DATA
	#pragma clang section data = ".gpio_driver_data"
#endif

#ifdef GPIO_STOP_SECT_DATA
	#undef GPIO_STOP_SECT_DATA
	#pragma clang section data = ""
#endif

#ifdef GPIO_START_SECT_CONST
	#undef GPIO_START_SECT_CONST
	#pragma clang section rodata = ".gpio_driver_rodata"
#endif

#ifdef GPIO_STOP_SECT_CONST
	#undef GPIO_STOP_SECT_CONST
	#pragma clang section rodata = ""
#endif

#ifdef GPIO_START_SECT_DATA_UNINIT
	#undef GPIO_START_SECT_DATA_UNINIT
	#pragma clang section data = ".gpio_driver_bss"
#endif

#ifdef GPIO_STOP_SECT_DATA_UNINIT
	#undef GPIO_STOP_SECT_DATA_UNINIT
	#pragma clang section data = ""
#endif

#ifdef GPIO_START_SECT_CODE
	#undef GPIO_START_SECT_CODE
	#pragme clang section text = ".gpio_driver_code"
#endif

#ifdef GPIO_STOP_SECT_CODE
	#undef GPIO_STOP_SECT_CODE
	#pragme clang section text = ""
#endif


	/*__IRS__*/

#ifdef IRS_START_SECT_DATA
	#undef IRS_START_SECT_DATA
	#pragma clang section data = ".irs_driver_data"
#endif

#ifdef IRS_STOP_SECT_DATA
	#undef IRS_STOP_SECT_DATA
	#pragma clang section data = ""
#endif

#ifdef IRS_START_SECT_CONST
	#undef IRS_START_SECT_CONST
	#pragma clang section rodata = ".irs_driver_rodata"
#endif

#ifdef IRS_STOP_SECT_CONST
	#undef IRS_STOP_SECT_CONST
	#pragma clang section rodata = ""
#endif

#ifdef IRS_START_SECT_DATA_UNINIT
	#undef IRS_START_SECT_DATA_UNINIT
	#pragma clang section data = ".irs_driver_bss"
#endif

#ifdef IRS_STOP_SECT_DATA_UNINIT
	#undef IRS_STOP_SECT_DATA_UNINIT
	#pragma clang section data = ""
#endif

#ifdef IRS_START_SECT_CODE
	#undef IRS_START_SECT_CODE
	#pragma clang section text = ".irs_driver_code"
#endif

#ifdef IRS_STOP_SECT_CODE
	#undef IRS_STOP_SECT_CODE
	#pragma clang section text = ""
#endif


	/*__SOFTTIMER__*/

#ifdef SOFTTIMER_START_SECT_DATA
	#undef SOFTTIMER_START_SECT_DATA
	#pragma clang section data = ".softtimer_driver_data"
#endif

#ifdef SOFTTIMER_STOP_SECT_DATA
	#undef SOFTTIMER_STOP_SECT_DATA
	#pragma clang section data = ""
#endif

#ifdef SOFTTIMER_START_SECT_CONST
	#undef SOFTTIMER_START_SECT_CONST
	#pragma clang section rodata = ".softtimer_driver_rodata"
#endif

#ifdef SOFTTIMER_STOP_SECT_CONST
	#undef SOFTTIMER_STOP_SECT_CONST
	#pragma clang section rodata = ""
#endif

#ifdef SOFTTIMER_START_SECT_DATA_UNINIT
	#undef SOFTTIMER_START_SECT_DATA_UNINIT
	#pragma clang section data = ".softtimer_driver_bss"
#endif

#ifdef SOFTTIMER_STOP_SECT_DATA_UNINIT
	#undef SOFTTIMER_STOP_SECT_DATA_UNINIT
	#pragma clang section data = ""
#endif

#ifdef SOFTTIMER_START_SECT_CODE
	#undef SOFTTIMER_STOP_SECT_CODE
	#pragma clang section text = ".softtimer_driver_code"
#endif

#ifdef SOFTTIMER_STOP_SECT_CODE
	#undef SOFTTIMER_STOP_SECT_CODE
	#pragma clang section text = ""
#endif


#endif
