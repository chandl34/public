/*
 *  MemCheck.mm
 *  Tactics
 *
 *  Created by Jonathan Chandler on 11/5/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#include "MemCheck.h"


natural_t  freeMemory(void)
{
    mach_port_t           host_port = mach_host_self();
    mach_msg_type_number_t   host_size = sizeof(vm_statistics_data_t) / sizeof(integer_t);
    vm_size_t               pagesize;
    vm_statistics_data_t     vm_stat;
	
    host_page_size(host_port, &pagesize);
	
    if (host_statistics(host_port, HOST_VM_INFO, (host_info_t)&vm_stat, &host_size) != KERN_SUCCESS) NSLog(@"Failed to fetch vm statistics");
	
	natural_t   mem_used = (vm_stat.active_count + vm_stat.inactive_count + vm_stat.wire_count) * pagesize;
	natural_t   mem_free = vm_stat.free_count * pagesize;
	natural_t   mem_total = mem_used + mem_free;
	
	cout << endl << "mem_used: " << mem_used << endl;
	cout << "mem_free: " << mem_free << endl;
	cout << "mem_total: " << mem_total << endl << endl;
	
	return mem_free;
}
