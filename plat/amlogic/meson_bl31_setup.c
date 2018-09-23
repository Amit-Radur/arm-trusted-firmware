/*
 * Copyright (c) 2017-2018, ARM Limited and Contributors. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <arch.h>
#include <assert.h>
#include <console.h>
#include <debug.h>
#include <generic_delay_timer.h>
#include <gicv2.h>
#include <platform.h>
#include <plat_arm.h>
#include <platform_def.h>
#include <meson_def.h>
#include <meson_mmap.h>
#include <meson_private.h>
#include <drivers/meson/meson_uart.h>

static console_meson_t console;

static entry_point_info_t bl33_image_ep_info;

uintptr_t plat_get_ns_image_entrypoint(void)
{
        return PLAT_MESON_NS_IMAGE_OFFSET;
}

/* For now map whole Device address space, we would refine it later */
static mmap_region_t meson_mmap[PLATFORM_MMAP_REGIONS + 1] = {
        MAP_REGION_FLAT(0xc0000000, 0x20000000, MT_DEVICE | MT_SECURE | MT_RW),
        {},
};

static const gicv2_driver_data_t meson_gic_data = {
	.gicd_base = AML_GICD_BASE,
	.gicc_base = AML_GICC_BASE,
};

void bl31_early_platform_setup2(u_register_t arg0, u_register_t arg1,
				u_register_t arg2, u_register_t arg3)
{
       (void)console_meson_register(AML_UART0_BASE,
                     AML_UART0_CLK_IN_HZ,
                     AML_UART0_BAUDRATE, &console);

       console_set_scope(&console.console, CONSOLE_FLAG_BOOT |
                          CONSOLE_FLAG_RUNTIME);

        /* Populate entry point information for BL33 */
        SET_PARAM_HEAD(&bl33_image_ep_info, PARAM_EP, VERSION_1, 0);
        /*
         * Tell BL31 where the non-trusted software image
         * is located and the entry state information
         */
        bl33_image_ep_info.pc = plat_get_ns_image_entrypoint();
        bl33_image_ep_info.spsr = SPSR_64(MODE_EL2, MODE_SP_ELX,
                                          DISABLE_ALL_EXCEPTIONS);
        SET_SECURITY_STATE(bl33_image_ep_info.h.attr, NON_SECURE);
}

void bl31_plat_arch_setup(void)
{
        mmap_add_region(BL31_BASE, BL31_BASE,
                        BL31_LIMIT - BL31_BASE,
                        MT_MEMORY | MT_RW | MT_SECURE);

        mmap_add_region(BL_CODE_BASE, BL_CODE_BASE,
                        BL_CODE_END - BL_CODE_BASE,
                        MT_CODE | MT_SECURE);
        mmap_add_region(BL_RO_DATA_BASE, BL_RO_DATA_BASE,
                        BL_RO_DATA_END - BL_RO_DATA_BASE,
                        MT_RO_DATA | MT_SECURE);
        mmap_add_region(BL_COHERENT_RAM_BASE, BL_COHERENT_RAM_BASE,
                        BL_COHERENT_RAM_END - BL_COHERENT_RAM_BASE,
                        MT_DEVICE | MT_RW | MT_SECURE);

    
        mmap_add(meson_mmap);
        init_xlat_tables();
        enable_mmu_el3(0);
}

void bl31_platform_setup(void)
{
	generic_delay_timer_init();

	/* Configure the interrupt controller */
	gicv2_driver_init(&meson_gic_data);
	gicv2_distif_init();
	gicv2_pcpu_distif_init();
	gicv2_cpuif_enable();
        
	INFO("BL31: Platform setup done\n");
}

unsigned int plat_get_syscnt_freq2(void)
{
        return 200000000;
}

entry_point_info_t *bl31_plat_get_next_image_ep_info(uint32_t type)
{
	assert(sec_state_is_valid(type) != 0);

         if (type == NON_SECURE)
                return &bl33_image_ep_info;

	return NULL;
}
