#!/bin/bash

#
# Installation script for cM packages.
# Part of Collective Mind Infrastructure (cM).
#
# See cM LICENSE.txt for licensing details.
# See cM Copyright.txt for copyright details.
#
# Developer(s): Grigori Fursin, started on 2011.09
#

# ${CM_LOCAL_SRC_DIR}  - src directory
# ${CM_INSTALL_OBJ_DIR}  - obj directory
# ${CM_INSTALL_DIR}  - install dir
# ${CM_CODE_ENV_FILE}  - file that sets environment
# ${CM_CODE_UID}  - cM code UID
# ${CM_PROCESSOR_BITS}  - number of bits for the OS (32 or 64)
# ${CM_OS_LIB_DIR} - lib extension for this OS
# ${CM_PARALLEL_JOB_NUMBER} - parallel jobs if supported

# Prepare environment
echo ""
read -p "Enter installation directory of Intel Composer XE 2011: " install_dir

echo >> ${CM_CODE_ENV_FILE}
echo export CM_${CM_CODE_UID}_INSTALL=${CM_LOCAL_SRC_DIR} >> ${CM_CODE_ENV_FILE}
echo >> ${CM_CODE_ENV_FILE}
echo . "${install_dir}/bin/compilervars.sh ia32" >> ${CM_CODE_ENV_FILE}

echo "" >> ${CM_CODE_ENV_FILE}
echo "export CM_CXX=icc" >> ${CM_CODE_ENV_FILE}
echo "export CM_OBJ_EXT=.o" >> ${CM_CODE_ENV_FILE}
echo "export CM_CC=\"icc -Qstd=c99\"" >> ${CM_CODE_ENV_FILE}
echo "export CM_FC=\"ifort -fpp\"" >> ${CM_CODE_ENV_FILE}
echo "export CM_FC90=\"ifort -fpp\"" >> ${CM_CODE_ENV_FILE}
echo "export CM_FC95=\"ifort -fpp\"" >> ${CM_CODE_ENV_FILE}
echo "export CM_FLAGS_DLL=\"-shared -fPIC\"" >> ${CM_CODE_ENV_FILE}
echo "export CM_FLAGS_DLL_EXTRA=-ldl" >> ${CM_CODE_ENV_FILE}
echo "export CM_FLAGS_OUTPUT=\"-o \"" >> ${CM_CODE_ENV_FILE}
echo "export CM_DLL_EXT=.so" >> ${CM_CODE_ENV_FILE}
echo "export CM_LIB_EXT=.a" >> ${CM_CODE_ENV_FILE}
echo "export CM_FLAGS_CREATE_OBJ=-c" >> ${CM_CODE_ENV_FILE}
echo "export CM_LB=\"ar rcs\"" >> ${CM_CODE_ENV_FILE}
echo "export CM_AR=ar" >> ${CM_CODE_ENV_FILE}
echo "export CM_LB_OUTPUT=" >> ${CM_CODE_ENV_FILE}
echo "export CM_EXE_EXT=.out" >> ${CM_CODE_ENV_FILE}
echo "export CM_FLAGS_STATIC_BIN=\"-static -fPIC\"" >> ${CM_CODE_ENV_FILE}
echo "export CM_FLAGS_STATIC_LIB=\"-static -fPIC\"" >> ${CM_CODE_ENV_FILE}
echo "export CM_FLAGS_DYNAMIC_BIN=" >> ${CM_CODE_ENV_FILE}
echo "export CM_FLAGS_CREATE_ASM=-S" >> ${CM_CODE_ENV_FILE}
echo "export CM_ASM_EXT=.s" >> ${CM_CODE_ENV_FILE}

echo "" >> ${CM_CODE_ENV_FILE}
echo "export CM_MAKE=make" >> ${CM_CODE_ENV_FILE%}
echo "export CM_OBJDUMP=\"objdump -d\"" >> ${CM_CODE_ENV_FILE}

# Cleaning directories if needed
echo ""
echo "Cleaning directories if needed ..."
echo ""

if [ "${CM_INSTALL_DELETE_SRC_DIR}" == "yes" ] ; then rm -rf ${CM_LOCAL_SRC_DIR}; fi
if [ "${CM_INSTALL_DELETE_OBJ_DIR}" == "yes" ] ; then rm -rf ${CM_INSTALL_OBJ_DIR}; fi
