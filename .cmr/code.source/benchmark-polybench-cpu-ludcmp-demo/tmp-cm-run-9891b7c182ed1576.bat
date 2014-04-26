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
set CM_CODE_DEP_VTUNE=861478904448c876
call cm_code_env_861478904448c876.bat
set CM_CODE_DEP_VTUNE=861478904448c876

rem Executable
amplxe-cl -report hw-events -r r000 -report-output=tmp-vtune-stat-0c78f734c4f4f841.csv -format csv -csv-delimiter=comma -filter module=a.exe
