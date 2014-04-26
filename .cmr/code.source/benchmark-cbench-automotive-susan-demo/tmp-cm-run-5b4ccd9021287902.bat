@echo off

rem cM generated script

rem target_os_uoa: 7a95e0754c37610a

rem Set global parameters
set CM_OS_LIB_DIR=lib
set CM_OS_VERSION=
set CM_OS_BITS=64
set CM_OS_FAMILY=windows
set CM_PROCESSOR_FAMILY=x86
set CM_PROCESSOR_BITS=32

rem Prepare code dependencies
set CM_CODE_DEP_COMPILER=37a62874f4bda86b
call cm_code_env_37a62874f4bda86b.bat
set CM_CODE_DEP_COMPILER=37a62874f4bda86b

rem Executable
objdump -d a.exe > tmp-objdump-output-96f90847bf996f00.dat
