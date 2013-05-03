/*
 * ManRiX microkernel
 * Copyright (C) 2004, 2005
 * 	Manish Regmi (regmi dot manish at gmail dot com) and
 * 	Rajesh R.C   (rajesh dot rc at gmail dot com)
 *
 * This Program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2, or (at your option)
 * any later version.
 *
 * This Program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 */
/*	file: spinlock.h
 *		Architecture Specfic Spin Lock implementation.
 */


#ifndef __ASM_SPINLOCK_H
#define __ASM_SPINLOCK_H

#ifdef MANRIX_SMP
/* Lock the spinlock object */
static inline void spin_lock(spinlock_t *sp)
{
	asm volatile (
		"lock decl %0\n\t"
		"jge 2f\n\t"
		"1: \n\t"
		"cmpl $0, %0\n\t"
		"jle 1b\n\t"
		"2:"
		:"=m"(sp->lock)
		:
		:"memory"
	);

}

/* Lock the spinlock object, but fail if already locked */
static inline int spin_trylock(spinlock_t *sp)
{
	int ret = 0;
	asm volatile (
		"lock decl %0\n\t"
		"jge 2f\n\t"
		"cmpl $0, %0\n\t"
		"jle 1f\n\t"
		"jmp 2f\n\t"
		"1: \n\t"
		"movl $-1, %1\n\t"
		"2: \n\t"
		:"=m"(sp->lock),"=r"(ret)
		:
		:"memory"
	);

	return ret;
}

static inline void spin_unlock(spinlock_t *sp)
{
	asm volatile (
		"lock incl %0\n\t"
		:"=m"(sp->lock)
		:
		:"memory"
	);
}
#endif
#endif /* __KERNEL_SPINLOCK_H */
