@echo off

rem cM generated script

rem target_os_uoa: 7a95e0754c37610a

rem Set global parameters
set CM_OS_FAMILY=windows
set CM_OS_LIB_DIR=lib
set CM_OS_VERSION=
set CM_OS_BITS=64

rem Prepare code dependencies
set CM_CODE_DEP_COMPILER=2c8e90e7e3475680
call cm_code_env_2c8e90e7e3475680.bat
set CM_CODE_DEP_COMPILER=2c8e90e7e3475680
set CM_CODE_DEP_VTUNE=861478904448c876
call cm_code_env_861478904448c876.bat
set CM_CODE_DEP_VTUNE=861478904448c876

rem Set execution parameters
set CT_REPEAT_MAIN=1

rem Executable
amplxe-runsa -event-based-counts --  a.exe  1>tmp-output1.tmp 2>tmp-output2.tmp
