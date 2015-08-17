#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* These are bits that are OR’d together */

#define DRNG_NO_SUPPORT	0x0	/* For clarity */
#define DRNG_HAS_RDRAND	0x1
#define DRNG_HAS_RDSEED	0x2

typedef struct cpuid_struct 
{
	unsigned int eax;
	unsigned int ebx;
	unsigned int ecx;
	unsigned int edx;
} cpuid_t;


void cpuid (cpuid_t *info, unsigned int leaf, unsigned int subleaf)
{
#if defined(__GNUC__)
	asm volatile("cpuid"
	: "=a" (info->eax), "=b" (info->ebx), "=c" (info->ecx), "=d" (info->edx)
	: "a" (leaf), "c" (subleaf)
	);
#endif

}


int _is_intel_cpu ()
{
	static int intel_cpu= -1;
	cpuid_t info;

	if ( intel_cpu == -1 ) 
	{
		cpuid(&info, 0, 0);

		if (
			memcmp((char *) &info.ebx, "Genu", 4) ||
			memcmp((char *) &info.edx, "ineI", 4) ||
			memcmp((char *) &info.ecx, "ntel", 4)
		) 
		{
			intel_cpu= 0;
		} 
		else 
		{
			intel_cpu= 1;
		}
	}

	return intel_cpu;
}


int get_drng_support ()
{
	static int drng_features= -1;

	/* So we don't call cpuid multiple times for 
	 * the same information */

	if ( drng_features == -1 ) 
	{
		drng_features= DRNG_NO_SUPPORT;

		if ( _is_intel_cpu() ) 
		{
			cpuid_t info;

			cpuid(&info, 1, 0);

			if ( (info.ecx & 0x40000000) == 0x40000000 ) 
			{
				drng_features|= DRNG_HAS_RDRAND;
			}

			cpuid(&info, 7, 0);

			if ( (info.ebx & 0x40000) == 0x40000 ) 
			{
				drng_features|= DRNG_HAS_RDSEED;
			}
		} 
	}

	return drng_features;
}


typedef unsigned short uint16_t;
typedef unsigned int uint32_t;
#if defined(_WIN32)
typedef unsigned __int64 uint64_t;
#else
typedef unsigned long long uint64_t;
#endif

int rdrand16_step (uint16_t *rand)
{
	unsigned char ok;

#if defined(__GNUC__)
	asm volatile ("rdrand %0; setc %1"
		: "=r" (*rand), "=qm" (ok));
#endif

	return (int) ok;
}

int rdrand32_step (uint32_t *rand)
{
	unsigned char ok;

#if defined(__GNUC__)
	asm volatile ("rdrand %0; setc %1"
		: "=r" (*rand), "=qm" (ok));
#endif

	return (int) ok;
}

int rdrand64_step (uint64_t *rand)
{
	unsigned char ok;

#if defined(__GNUC__)
	asm volatile ("rdrand %0; setc %1"
		: "=r" (*rand), "=qm" (ok));
#endif

	return (int) ok;
}

uint32_t RDRandom(void) 
{
	uint32_t _rand = 0L;

	unsigned int count= 100;

	while(--count)
	{
		unsigned char ret = rdrand32_step(&_rand);
		if ( (int) ret == 1)
			break;
	}
	return _rand;
}


// 将以字符串形式存储在s地址中的二进制数字转换为对应的十进制数字
long int btd(char *s) 
{
	long int rt=0;

	int i,n=0;

	while (s[n]) n++;

	for (--n,i=n; i>=0; i--)
	{
		rt|=(s[i]-48)<<n-i;
	}

	return rt;
}

/******* Random Interface ********/
BOOL is_support_drng()
{
	if ( !( get_drng_support() & DRNG_HAS_RDRAND ) ) 
	{
		fprintf(stderr, "No RDRAND support\n");
		return FALSE;
	}
	return TRUE;
}

uint32_t GetRandom()
{
	return RDRandom();
}


