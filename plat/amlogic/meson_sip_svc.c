/*
 *
 * SPDX-License-Identifier:     BSD-3-Clause
 * https://spdx.org/licenses
*/

#include <debug.h>
#include <runtime_svc.h>
#include <smcc.h>
#include <mmio.h>

#define GET_SHARE_MEM_INPUT_BASE	0x82000020
#define GET_SHARE_MEM_OUTPUT_BASE	0x82000021
#define GET_REBOOT_REASON		0x82000022
#define GET_SHARE_STORAGE_IN_BASE	0x82000023
#define GET_SHARE_STORAGE_OUT_BASE	0x82000024
#define GET_SHARE_STORAGE_BLOCK_BASE	0x82000025
#define GET_SHARE_STORAGE_MESSAGE_BASE	0x82000026
#define GET_SHARE_STORAGE_BLOCK_SIZE	0x82000027
#define SET_STORAGE_INFO		0x82000028
#define FN_EFUSE_READ                   0x82000030       

uintptr_t sip_smc_handler(uint32_t smc_fid,
			       u_register_t x1,
			       u_register_t x2,
			       u_register_t x3,
			       u_register_t x4,
			       void *cookie,
			       void *handle,
			       u_register_t flags)
{
        uint32_t ns;
        uint32_t ret;
        uint32_t offset;
        INFO("called me\n");
	INFO("%s: got SMC (0x%x) x1 0x%lx, x2 0x%lx, x3 0x%lx\n",
						 __func__, smc_fid, x1, x2, x3);

         /* Determine which security state this SMC originated from */
        ns = is_caller_non_secure(flags);
        if (!ns)
                SMC_RET1(handle, SMC_UNK);

        switch (smc_fid) {
        case GET_SHARE_MEM_INPUT_BASE:
            ret = 0x100fe000;
            SMC_RET1(handle, ret);
        case GET_SHARE_MEM_OUTPUT_BASE:
            ret = 0x100ff000;
            SMC_RET1(handle, ret);
        case FN_EFUSE_READ:
            offset = x1; /* Just a dummy efuse read to make U-boot Happy */
            ret = mmio_read_32(0xc8830000 + offset);
            SMC_RET1(handle, ret);
        default:
             ERROR("%s: unhandled SMC (0x%x)\n", __func__, smc_fid);
             SMC_RET1(handle, SMC_UNK);
        }
        
        return 0x0;
}

/* Define a runtime service descriptor for fast SMC calls */
DECLARE_RT_SVC(
	meson_sip_svc,
	OEN_SIP_START,
	OEN_SIP_END,
	SMC_TYPE_FAST,
	NULL,
	sip_smc_handler
);
