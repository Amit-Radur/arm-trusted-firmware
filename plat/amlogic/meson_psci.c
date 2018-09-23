/*
 * Copyright (c) 2017-2018, ARM Limited and Contributors. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <arch_helpers.h>
#include <assert.h>
#include <debug.h>
#include <psci.h>
#include <stdbool.h>
#include <meson_private.h>

#define STUB() ERROR("stub %s called\n", __func__)

uintptr_t meson_sec_entrypoint;

static void meson_cpu_standby(plat_local_state_t cpu_state)
{
/* TODO: Proper cpu standby */
}

static int meson_pwr_domain_on(u_register_t mpidr)
{
        /*
         * SCP takes care of powering up parent power domains so we
         * only need to care about level 0,  
        
        scpi_set_meson_power_state(mpidr, scpi_power_on, scpi_power_on,
                                 scpi_power_on);
        */

	return PSCI_E_SUCCESS;
}

void meson_pwr_domain_off(const psci_power_state_t *target_state)
{
	/* Prevent interrupts from spuriously waking up this cpu */

	/* TODO: Indicate to System firmware about powering down */
}

void meson_pwr_domain_on_finish(const psci_power_state_t *target_state)
{
	/* TODO: Indicate to System firmware about completion */

}

static void __dead2 meson_system_reset(void)
{
	/* TODO: Indicate to System firmware about system reset */
	STUB();

	while (true)
		wfi();
}

static int meson_validate_power_state(unsigned int power_state,
				   psci_power_state_t *req_state)
{
	/* TODO: perform the proper validation */

	return PSCI_E_SUCCESS;
}

static int meson_validate_ns_entrypoint(uintptr_t entrypoint)
{
	/* TODO: perform the proper validation */

	return PSCI_E_SUCCESS;
}

static const plat_psci_ops_t meson_plat_psci_ops = {
	.cpu_standby = meson_cpu_standby,
	.pwr_domain_on = meson_pwr_domain_on,
	.pwr_domain_off = meson_pwr_domain_off,
	.pwr_domain_on_finish = meson_pwr_domain_on_finish,
	.system_reset = meson_system_reset,
	.validate_power_state = meson_validate_power_state,
	.validate_ns_entrypoint = meson_validate_ns_entrypoint
};

int plat_setup_psci_ops(uintptr_t sec_entrypoint,
			const plat_psci_ops_t **psci_ops)
{
	meson_sec_entrypoint = sec_entrypoint;

        flush_dcache_range((uint64_t)&meson_sec_entrypoint,
                           sizeof(meson_sec_entrypoint));


	*psci_ops = &meson_plat_psci_ops;

	return 0;
}
