/*
 * Copyright (c) 2017-2018, ARM Limited and Contributors. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <debug.h>
#include <mmio.h>
#include <platform_def.h>
#include <meson_mmap.h>
#include <utils_def.h>
#include <delay_timer.h>
#include <arch_helpers.h>



#include "meson_private.h"

void meson_cpu_on(unsigned int cluster, unsigned int core)
{
    unsigned int val;    
    #define CPU1_CTRL_MASK 0xc0000
    #define CPU1_RAM_DOWN  0xfff00000
    #define HHI_SYS_CPU_RESET_CNTL 0xc883c160
    #define ISOLATION_A53 0xc81000e0
    #define RAM_PWR_CTRL 0xc81000f4
    #define RAM_PWR_CTRL_1 0xc81000f8
    #define PWR_A53      0xc81000e4 


    
    INFO("PSCI#######: Powering on cluster %d core %d\n", cluster, core);

    val = mmio_read_32(0xda83c160);
    val |= 0x22;
    mmio_write_32(0xda83c160, val);
    
    val = mmio_read_32(0xda1000e4);
    val &= ~0x30;
    mmio_write_32(0xda1000e4, val);

//    da1000e0

    INFO("MESSSS ON %x\n",  mmio_read_32(0xda1000e0));

    val = mmio_read_32(0xda1000e0);
    val &= ~0xc0222;
    mmio_write_32(0xda1000e0, val);

    INFO("MESSSS ON after%x\n",  mmio_read_32(0xda1000e0));


    val = mmio_read_32(0xda83c160);
    val &= ~0x22;
    mmio_write_32(0xda83c160, val);




    



/*    INFO("value of reset %x\n", mmio_read_32(0xC883C160));
    val = mmio_read_32(0xC883C160);
    val |= 0x22;
    mmio_write_32(0xC883C160, val);
    dsb();
    INFO("value of reset %x\n", mmio_read_32(0xC883C160));



    INFO("value of reset_! %x\n", mmio_read_32(0xc1104484));
    val = mmio_read_32(0xc1104484);
    val |= 0x220000;
    mmio_write_32(0xc1104484, val);
    dmb();





    mmio_write_32(0xc110440c, 0x2000);
    dsb();
    INFO("value of reset %x\n", mmio_read_32(0xc110440c));
    
    mmio_write_32(0xc110440c, 0x000);
    dsb();
    INFO("value of reset %x\n", mmio_read_32(0xc110440c));




    INFO("Before_value of ISOLATION_A53 = %x\n", mmio_read_32(0xc81000e0));
    val = mmio_read_32(ISOLATION_A53);
    val &= ~CPU1_CTRL_MASK;
    mmio_write_32(ISOLATION_A53, val);
    INFO("After_value of ISOLATION_A53 = %x\n", mmio_read_32(0xc81000e0));



    val = mmio_read_32(PWR_A53);
    val &= ~0x30;
    mmio_write_32(PWR_A53, val);
    dsb();

    val = mmio_read_32(RAM_PWR_CTRL);
    val &= ~CPU1_RAM_DOWN;
    mmio_write_32(RAM_PWR_CTRL, val);
    udelay(10);
  //  dsb();
    INFO("value ofram %x\n", mmio_read_32(0xc81000f4));

    val = mmio_read_32(RAM_PWR_CTRL_1);
    val &= ~0xf;
    mmio_write_32(RAM_PWR_CTRL_1, val);


    INFO("value of reset_1 %x\n", mmio_read_32(0xc1104484));
    val = mmio_read_32(0xc1104484);
    val &= ~0x220000;
    mmio_write_32(0xc1104484, val);
    //dsb();


    INFO("value of reset %x\n", mmio_read_32(0xC883C160));
    val = mmio_read_32(0xC883C160);
    val &= ~0x22;
    mmio_write_32(0xC883C160, val);
//    dsb();
    INFO("value of reset %x\n", mmio_read_32(0xC883C160));


     val = mmio_read_32(ISOLATION_A53);
    val &= ~0xc0222;
    mmio_write_32(ISOLATION_A53, val);


  //   INFO("Before_value of PWR_A53 = %x\n", mmio_read_32(PWR_A53));
//    val = mmio_read_32(PWR_A53);
  //  val &= ~0x3c;
    //mmio_write_32(PWR_A53, val);
//    INFO("After_value of PWR_A53 = %x\n", mmio_read_32(PWR_A53));

  //INFO("Before_value of RAM_PW_CTRL = %x\n", mmio_read_32(RAM_PWR_CTRL));
//    val = mmio_read_32(RAM_PWR_CTRL);
  //  val &= ~CPU1_RAM_DOWN;
    //mmio_write_32(RAM_PWR_CTRL, val);
    //INFO("After_value of RAM_PW_CTRL = %x\n", mmio_read_32(RAM_PWR_CTRL));




    val =  mmio_read_32(0xC1104408);
    val |= 0x220000;
    mmio_write_32(0xc1104408, val);
    //INFO("value of reset %x\n", mmio_read_32(0xc1104408));



   
  //      INFO("Before_value of ISOLATION_A53 = %x\n", mmio_read_32(ISOLATION_A53));
    val = mmio_read_32(ISOLATION_A53);
    val &=  ~0xc;
    mmio_write_32(ISOLATION_A53, val);
    INFO("After_value of ISOLATION_A53 = %x\n", mmio_read_32(ISOLATION_A53));

  val = mmio_read_32(RAM_PWR_CTRL);
    val &= ~CPU1_RAM_DOWN;
    mmio_write_32(RAM_PWR_CTRL, val);


     val = mmio_read_32(PWR_A53);
    val &= ~0x3c;
    mmio_write_32(PWR_A53, val);

     INFO("After_value of PWR_A53 = %x\n", mmio_read_32(PWR_A53));

 

      INFO("Before_value of HHI_SYS_CPU_RESET_CNTL = %x\n", mmio_read_32(HHI_SYS_CPU_RESET_CNTL));
    val = mmio_read_32(HHI_SYS_CPU_RESET_CNTL);
    val &= ~0x22;
    mmio_write_32(HHI_SYS_CPU_RESET_CNTL, val);
    INFO("After_value of HHI_SYS_CPU_RESET_CNTL = %x\n", mmio_read_32(HHI_SYS_CPU_RESET_CNTL));

    val =  mmio_read_32(0xC1104408);
    val &= ~0x220000;
    mmio_write_32(0xc1104408, val);
    INFO("value of reset %x\n", mmio_read_32(0xc1104408));


                                                                     

    INFO("Before_value of ISOLATION_A53 = %x\n", mmio_read_32(ISOLATION_A53));
    val = mmio_read_32(ISOLATION_A53);
    val &= ~(0xccf | CPU1_CTRL_MASK);
    mmio_write_32(ISOLATION_A53, val);
    udelay(10);
    INFO("After_value of ISOLATION_A53 = %x\n", mmio_read_32(ISOLATION_A53));



    INFO("Before_value of RAM_PW_CTRL = %x\n", mmio_read_32(RAM_PWR_CTRL));
    val = mmio_read_32(RAM_PWR_CTRL);
    val &= ~CPU1_RAM_DOWN;
    mmio_write_32(RAM_PWR_CTRL, val);
    INFO("After_value of RAM_PW_CTRL = %x\n", mmio_read_32(RAM_PWR_CTRL));


    INFO("Before_value of ISOLATION_A53 = %x\n", mmio_read_32(0xc81000e0));
    val = mmio_read_32(ISOLATION_A53);
    val &= ~CPU1_CTRL_MASK;
    mmio_write_32(ISOLATION_A53, val);
    udelay(10);
    INFO("After_value of ISOLATION_A53 = %x\n", mmio_read_32(0xc81000e0));


   val =  mmio_read_32(0xC1104408);
    val &= ~0x330000;
    mmio_write_32(0xc1104408, val);
    udelay(10);
    INFO("value of reset %x\n", mmio_read_32(0xc1104408));



    INFO("Before_value of PWR_A53 = %x\n", mmio_read_32(PWR_A53));
    val = mmio_read_32(PWR_A53);
    val &= ~0x30;
    mmio_write_32(PWR_A53, val);
    udelay(10);
    INFO("After_value of PWR_A53 = %x\n", mmio_read_32(PWR_A53));*/
  //  dsb();
}

