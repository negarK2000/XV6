#include "types.h"
#include "x86.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"

int
sys_fork(void)
{
  return fork();
}

int
sys_exit(void)
{
  exit();
  return 0;  // not reached
}

int
sys_wait(void)
{
  return wait();
}

int
sys_kill(void)
{
  int pid;

  if(argint(0, &pid) < 0)
    return -1;
  return kill(pid);
}

int
sys_getpid(void)
{
  return myproc()->pid;
}

int
sys_sbrk(void)
{
  int addr;
  int n;

  if(argint(0, &n) < 0)
    return -1;
  addr = myproc()->sz;
  if(growproc(n) < 0)
    return -1;
  return addr;
}

int
sys_sleep(void)
{
  int n;
  uint ticks0;

  if(argint(0, &n) < 0)
    return -1;
  acquire(&tickslock);
  ticks0 = ticks;
  while(ticks - ticks0 < n){
    if(myproc()->killed){
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

// return how many clock tick interrupts have occurred
// since start.
int
sys_uptime(void)
{
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}

// My System calls for OS Project - Phase 1
int 
sys_getProcCount(void)
{
  return getProcCount();
}

// return the how many times the read system call was called
int 
sys_getReadCount(void)
{
  return myproc()->readCounter;
}

// My System calls for OS Project - Phase 2

int
sys_unit0_operation(void)
{
  return unit0_operation();
}

int
sys_unit1_operation(void)
{
  return unit1_operation();
}

int
sys_unit2_operation(void)
{
  return unit2_operation();
}

int
sys_unit3_operation(void)
{
  return unit3_operation();
}

int
sys_thread_clone(void)
{
  char* stack;
  
  int temp = argptr(0, &stack, sizeof stack);
  if(temp < 0)
    return -1;

  return thread_clone((void*) stack);
}

int
sys_thread_join(void)
{
  return thread_join();
}
