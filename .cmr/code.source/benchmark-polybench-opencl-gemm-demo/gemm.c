/**
 * gemm.c: This file is part of the PolyBench/GPU 1.0 test suite.
 *
 *
 * Contact: Scott Grauer-Gray <sgrauerg@gmail.com>
 * Louis-Noel Pouchet <pouchet@cse.ohio-state.edu>
 * Web address: http://www.cse.ohio-state.edu/~pouchet/software/polybench/GPU
 *
 * Updated by Grigori Fursin (http://cTuning.org/lab/people/gfursin)
 * to work with Collective Mind Framework and OpenME interfqce for automatic 
 * and collective tuning and data mining: http://cTuning.org
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#ifdef __APPLE__
#include <OpenCL/opencl.h>
#else
#include <CL/cl.h>
#endif

#include "polybench.h"

#ifdef OPENME
#include <openme.h>
#endif

//define the error threshold for the results "not matching"
#define PERCENT_DIFF_ERROR_THRESHOLD 0.05

#define MAX_SOURCE_SIZE (0x100000)

/* Problem size */
#define NI 512
#define NJ 512
#define NK 512

/* Thread block dimensions */
#define DIM_LOCAL_WORK_GROUP_X 32
#define DIM_LOCAL_WORK_GROUP_Y 8

#if defined(cl_khr_fp64)  // Khronos extension available?
#pragma OPENCL EXTENSION cl_khr_fp64 : enable
#elif defined(cl_amd_fp64)  // AMD extension available?
#pragma OPENCL EXTENSION cl_amd_fp64 : enable
#endif

/* Declared constant values for ALPHA and BETA (same as values in PolyBench 2.0) */
#define ALPHA 32412
#define BETA 2123

/* Can switch DATA_TYPE between float and double */
# ifndef DATA_TYPE
#  define DATA_TYPE float
# endif

char str_temp[1024];

cl_platform_id platform_id;
cl_device_id device_id;   
cl_uint num_devices;
cl_uint num_platforms;
cl_int err_code;
cl_context clGPUContext;
cl_kernel clKernel;
cl_command_queue clCommandQue;
cl_program clProgram;
cl_mem a_mem_obj;
cl_mem b_mem_obj;
cl_mem c_mem_obj;
FILE *fp;
char *source_str;
size_t source_size;



void compareResults(DATA_TYPE* C, DATA_TYPE* C_outputFromGpu)
{
	int i, j, fail;
	fail = 0;
	
	// Compare C1 and C2
	for (i=0; i < NI; i++) 
	{
		for (j=0; j < NJ; j++) 
		{
			if (percentDiff(C[i*NJ + j], C_outputFromGpu[i*NJ + j]) > PERCENT_DIFF_ERROR_THRESHOLD) 
			{
				fail++;
			}
		}
	}
	
	// Print results
	printf("Non-Matching CPU-GPU Outputs Beyond Error Threshold of %4.2f Percent: %d\n", PERCENT_DIFF_ERROR_THRESHOLD, fail);

}


void read_cl_file()
{
	// Load the kernel source code into the array source_str
	fp = fopen("gemm.cl", "r");
	if (!fp) {
		fprintf(stderr, "Failed to load kernel.\n");
		exit(1);
	}
	source_str = (char*)malloc(MAX_SOURCE_SIZE);
	source_size = fread( source_str, 1, MAX_SOURCE_SIZE, fp);
	fclose( fp );
}


void init(DATA_TYPE *A, DATA_TYPE *B, DATA_TYPE *C)
{
	int i, j;

  	for (i = 0; i < NI; i++)
	{
    	for (j = 0; j < NK; j++)
		{
      		A[i*NK + j] = ((DATA_TYPE) i*j) / NI;
		}
	}

  	for (i = 0; i < NK; i++)
	{
    	for (j = 0; j < NJ; j++)
		{
      		B[i*NJ + j] = ((DATA_TYPE) i*j + 1) / NJ;
		}
	}

  	for (i = 0; i < NI; i++)
	{
    	for (j = 0; j < NJ; j++)
		{
      		C[i*NJ + j] = ((DATA_TYPE) i*j + 2) / NJ;
		}
	}
}


void cl_initialization()
{	
	// Get platform and device information
	err_code = clGetPlatformIDs(1, &platform_id, &num_platforms);
	if(err_code == CL_SUCCESS) printf("number of platforms is %d\n",num_platforms);
	else printf("Error getting platform IDs\n");

	err_code = clGetPlatformInfo(platform_id,CL_PLATFORM_NAME, sizeof(str_temp), str_temp,NULL);
	if(err_code == CL_SUCCESS) printf("platform name is %s\n",str_temp);
	else printf("Error getting platform name\n");

	err_code = clGetPlatformInfo(platform_id, CL_PLATFORM_VERSION, sizeof(str_temp), str_temp,NULL);
	if(err_code == CL_SUCCESS) printf("platform version is %s\n",str_temp);
	else printf("Error getting platform version\n");

	err_code = clGetDeviceIDs( platform_id, CL_DEVICE_TYPE_GPU, 1, &device_id, &num_devices);
	if(err_code == CL_SUCCESS) printf("number of devices is %d\n", num_devices);
	else printf("Error getting device IDs\n");

	err_code = clGetDeviceInfo(device_id,CL_DEVICE_NAME, sizeof(str_temp), str_temp,NULL);
	if(err_code == CL_SUCCESS) printf("device name is %s\n",str_temp);
	else printf("Error getting device name\n");
	
	// Create an OpenCL context
	clGPUContext = clCreateContext( NULL, 1, &device_id, NULL, NULL, &err_code);
	if(err_code != CL_SUCCESS) printf("Error in creating context\n");
 
	//Create a command-queue
	clCommandQue = clCreateCommandQueue(clGPUContext, device_id, 0, &err_code);
	if(err_code != CL_SUCCESS) printf("Error in creating command queue\n");
}


void cl_mem_init(DATA_TYPE* A, DATA_TYPE* B, DATA_TYPE* C)
{
	a_mem_obj = clCreateBuffer(clGPUContext, CL_MEM_READ_WRITE, sizeof(DATA_TYPE) * NI * NK, NULL, &err_code);
	b_mem_obj = clCreateBuffer(clGPUContext, CL_MEM_READ_WRITE, sizeof(DATA_TYPE) * NK * NJ, NULL, &err_code);
	c_mem_obj = clCreateBuffer(clGPUContext, CL_MEM_READ_WRITE, sizeof(DATA_TYPE) * NI * NJ, NULL, &err_code);
		
	if(err_code != CL_SUCCESS) printf("Error in creating buffers\n");

	err_code = clEnqueueWriteBuffer(clCommandQue, a_mem_obj, CL_TRUE, 0, sizeof(DATA_TYPE) * NI * NK, A, 0, NULL, NULL);
	err_code = clEnqueueWriteBuffer(clCommandQue, b_mem_obj, CL_TRUE, 0, sizeof(DATA_TYPE) * NK * NJ, B, 0, NULL, NULL);
	err_code = clEnqueueWriteBuffer(clCommandQue, c_mem_obj, CL_TRUE, 0, sizeof(DATA_TYPE) * NI * NJ, C, 0, NULL, NULL);
	if(err_code != CL_SUCCESS)printf("Error in writing buffers\n");
}


void cl_load_prog()
{
#ifdef MAC
	char *flags = "-DMAC";
#else
	char *flags = "";
#endif
        char buffer[16384];
        size_t length;

	// Create a program from the kernel source
	clProgram = clCreateProgramWithSource(clGPUContext, 1, (const char **)&source_str, (const size_t *)&source_size, &err_code);
	if(err_code != CL_SUCCESS)
        {
          printf("Error in creating program\n");
          exit(1);
        }

	// Build the program
	err_code = clBuildProgram(clProgram, 1, &device_id, flags, NULL, NULL);
	if(err_code != CL_SUCCESS) 
        {
          printf("Error in building program (%d)\n", err_code);
          clGetProgramBuildInfo(clProgram, device_id, CL_PROGRAM_BUILD_LOG, sizeof(buffer), buffer, &length);
          printf("Error output:\n%s\n", buffer);
          exit(1);
        }
		
	// Create the OpenCL kernel
	clKernel = clCreateKernel(clProgram, "gemm", &err_code);
	if(err_code != CL_SUCCESS) 
        {
          printf("Error in creating kernel\n");
          exit(1);
        }

	clFinish(clCommandQue);
}

void cl_launch_kernel()
{
	double t_start, t_end;

	int ni=NI;
	int nj=NJ;
	int nk=NK;

	DATA_TYPE alpha = ALPHA;
	DATA_TYPE beta = BETA;

	size_t localWorkSize[2], globalWorkSize[2];
	localWorkSize[0] = DIM_LOCAL_WORK_GROUP_X;
	localWorkSize[1] = DIM_LOCAL_WORK_GROUP_Y;
	globalWorkSize[0] = (size_t)ceil(((float)NJ) / ((float)DIM_LOCAL_WORK_GROUP_X)) * DIM_LOCAL_WORK_GROUP_X;
	globalWorkSize[1] = (size_t)ceil(((float)NI) / ((float)DIM_LOCAL_WORK_GROUP_Y)) * DIM_LOCAL_WORK_GROUP_Y;

//	t_start = rtclock();
	
	// Set the arguments of the kernel
	err_code =  clSetKernelArg(clKernel, 0, sizeof(cl_mem), (void *)&a_mem_obj);
	err_code |= clSetKernelArg(clKernel, 1, sizeof(cl_mem), (void *)&b_mem_obj);
	err_code |= clSetKernelArg(clKernel, 2, sizeof(cl_mem), (void *)&c_mem_obj);
	err_code |= clSetKernelArg(clKernel, 3, sizeof(DATA_TYPE), (void *)&alpha);
	err_code |= clSetKernelArg(clKernel, 4, sizeof(DATA_TYPE), (void *)&beta);
	err_code |= clSetKernelArg(clKernel, 5, sizeof(int), (void *)&ni);
	err_code |= clSetKernelArg(clKernel, 6, sizeof(int), (void *)&nj);
	err_code |= clSetKernelArg(clKernel, 7, sizeof(int), (void *)&nk);
	
	if(err_code != CL_SUCCESS)
        {
          printf("Error in seting arguments\n");
          exit(1);
        }

	// Execute the OpenCL kernel
	err_code = clEnqueueNDRangeKernel(clCommandQue, clKernel, 2, NULL, globalWorkSize, localWorkSize, 0, NULL, NULL);
	if(err_code != CL_SUCCESS)
        {
          printf("Error in launching kernel\n");
          exit(1);
        }

	clFinish(clCommandQue);

//	t_end = rtclock();
//	fprintf(stdout, "GPU Runtime: %0.6lfs\n", t_end - t_start);
}


void cl_clean_up()
{
	// Clean up
	err_code = clFlush(clCommandQue);
	err_code = clFinish(clCommandQue);
	err_code = clReleaseKernel(clKernel);
	err_code = clReleaseProgram(clProgram);
	err_code = clReleaseMemObject(a_mem_obj);
	err_code = clReleaseMemObject(b_mem_obj);
	err_code = clReleaseMemObject(c_mem_obj);
	err_code = clReleaseCommandQueue(clCommandQue);
	err_code = clReleaseContext(clGPUContext);
	if(err_code != CL_SUCCESS) printf("Error in cleanup\n");
}


void gemm(DATA_TYPE *A, DATA_TYPE *B, DATA_TYPE *C)
{
	int i,j,k;
	
	for (i = 0; i < NI; i++)
	{
    		for (j = 0; j < NJ; j++)
    		{
			C[i*NJ + j] *= BETA;
	
			for (k = 0; k < NK; ++k)
			{
	  			C[i*NJ + j] += ALPHA * A[i*NK + k] * B[k*NJ + j];
			}
      		}
	}
}


int main(void) 
{
  /* Prepare ctuning vars */
  long ct_repeat=0;
  long ct_repeat_max=1;

  DATA_TYPE* A;
  DATA_TYPE* B;  
  DATA_TYPE* C;  
  DATA_TYPE* C_outputFromGpu; 

#ifdef OPENME
  openme_init(NULL,NULL,NULL,0);
  openme_callback("PROGRAM_START", NULL);
#endif

  /* Run kernel. */
  if (getenv("CT_REPEAT_MAIN")!=NULL) ct_repeat_max=atol(getenv("CT_REPEAT_MAIN"));

  A = (DATA_TYPE*)malloc(NI*NK*sizeof(DATA_TYPE)); 
  B = (DATA_TYPE*)malloc(NK*NJ*sizeof(DATA_TYPE));   
  C = (DATA_TYPE*)malloc(NI*NJ*sizeof(DATA_TYPE)); 
  C_outputFromGpu = (DATA_TYPE*)malloc(NI*NJ*sizeof(DATA_TYPE)); 

  srand(1);
  init(A, B, C);
  read_cl_file();
  cl_initialization();
  cl_mem_init(A, B, C);
  cl_load_prog();

#ifdef OPENME
  openme_callback("ACC_KERNEL_START", NULL);
#endif
  for (ct_repeat=0; ct_repeat<ct_repeat_max; ct_repeat++)
  {
    cl_launch_kernel();

    err_code = clEnqueueReadBuffer(clCommandQue, c_mem_obj, CL_TRUE, 0, NI*NJ*sizeof(DATA_TYPE), C_outputFromGpu, 0, NULL, NULL);
    if(err_code != CL_SUCCESS)
    {
      printf("Error in reading GPU mem\n");
      exit(1);
    }
  }
#ifdef OPENME
  openme_callback("ACC_KERNEL_END", NULL);
#endif

  srand(1);
  init(A, B, C);

#ifdef OPENME
  openme_callback("KERNEL_START", NULL);
#endif
  for (ct_repeat=0; ct_repeat<ct_repeat_max; ct_repeat++)
  {
    gemm(A, B, C);
  }
#ifdef OPENME
  openme_callback("KERNEL_END", NULL);
#endif

  compareResults(C, C_outputFromGpu);
  cl_clean_up();

  free(A);
  free(B);  
  free(C);  
  free(C_outputFromGpu); 

#ifdef OPENME
  openme_callback("PROGRAM_END", NULL);
#endif

  return 0;
}

