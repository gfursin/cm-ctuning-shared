@echo off

rem cM generated script

rem target_os_uoa: 7a95e0754c37610a

rem Set global parameters
set CM_OS_LIB_DIR=lib
set CM_OS_VERSION=
set CM_OS_BITS=64
set CM_OS_FAMILY=windows
set CM_PROCESSOR_FAMILY=x86-64
set CM_PROCESSOR_BITS=64

rem Prepare code dependencies
set CM_CODE_DEP_COMPILER=2c8e90e7e3475680
call cm_code_env_2c8e90e7e3475680.bat
set CM_CODE_DEP_COMPILER=2c8e90e7e3475680

rem Set execution parameters
set CM_COMPILER_FLAGS_MISC= /ID:\Work1\CM\cm-repos\ctuning-setup\.cmr\code\65cbb74946919aab\include /DPOLYBENCH_PADDING_FACTOR=0 /DN=4054 /DDATA_TYPE=double /DPOLYBENCH_DUMP_ARRAYS=YES
set CM_SOURCE_FILES_WITHOUT_EXT= ludcmp polybench
set CM_SOURCE_FILES= ludcmp.c polybench.c
set CM_LD_FLAGS_MISC= D:\Work1\CM\cm-repos\ctuning-setup\.cmr\code\65cbb74946919aab\lib\libcm-ce4e448e64ca58b5.lib
set CM_COMPILER_FLAGS_CC_OPTS= /fast
set CM_TARGET_FILE=a.exe

rem Executable
D:\Work1\CM\cm-1.0\repos\default\.cmr\os.script\build-generic\cm_build_dynamic_bin_c.bat 1>tmp-build-output1.tmp 2>tmp-build-output2.tmp
