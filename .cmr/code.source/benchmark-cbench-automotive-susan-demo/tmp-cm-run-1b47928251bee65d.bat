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

rem Set execution parameters
set CM_SOURCE_FILES_WITHOUT_EXT= ctuning-rtl susan
set CM_COMPILER_FLAGS_CC_OPTS=  -fsched-stalled-insns-dep=27 -falign-jumps=8 -falign-labels=37 -falign-loops=26 -finline-limit=8 --param min-crossjump-insns=9 --param max-goto-duplication-insns=4 --param max-inline-insns-single=789 --param max-inline-insns-auto=149 --param large-function-insns=3679 --param large-function-growth=152 --param large-unit-insns=19788 --param max-inline-insns-recursive=850 --param max-inline-insns-recursive-auto=908 --param max-unrolled-insns=1773 --param max-unroll-times=5 --param omega-max-vars=196 --param omega-max-geqs=276 --param omega-eliminate-redundant-constraints=0 --param tracer-min-branch-ratio=11 --param max-cse-insns=1674 --param max-reload-search-insns=196 --param max-cselib-memory-locations=751 --param max-pipeline-region-blocks=8 --param max-sched-region-insns=236 --param max-pipeline-region-insns=181 --param min-spec-prob=47 --param max-sched-extend-regions-iters=0 --param sched-spec-prob-cutoff=39 --param sched-mem-true-dep-cost=1 --param max-last-value-rtl=24883 --param virtual-mappings-ratio=8 --param max-fields-for-field-sensitive=215 --param ira-max-loops-num=94 --param ira-max-conflict-table-size=1443 -fbranch-count-reg -fbranch-target-load-optimize -fbranch-target-load-optimize2 -fbtr-bb-exclusive -fcaller-saves -fconserve-stack -fcse-follow-jumps -fdefer-pop -fdelete-null-pointer-checks -fearly-inlining -fforward-propagate -ffunction-cse -fgcse-las -fgcse-lm -fif-conversion2 -finline-functions-called-once -fipa-matrix-reorg -fipa-pure-const -fipa-reference -fipa-struct-reorg -fira-share-save-slots -fivopts -fomit-frame-pointer -foptimize-sibling-calls -fpeephole2 -fpredictive-commoning -fprefetch-loop-arrays -fregmove -frename-registers -freorder-blocks-and-partition -freorder-functions -fsched-interblock -fsched-spec-load -fsel-sched-pipelining -fselective-scheduling -fsignaling-nans -fsplit-ivs-in-unroller -ftracer -ftree-builtin-call-dce -ftree-copyrename -ftree-dse -ftree-fre -ftree-loop-distribution -ftree-loop-im -ftree-loop-ivcanon -ftree-loop-optimize -ftree-pre -ftree-reassoc -ftree-sink -ftree-ter -funroll-all-loops -fvariable-expansion-in-unroller -fvect-cost-model -fweb
set CM_SOURCE_FILES= ctuning-rtl.c susan.c
set CM_TARGET_FILE=a.exe

rem Executable
D:\Work1\CM\cm-1.0\repos\default\.cmr\os.script\build-generic\cm_build_dynamic_bin_c.bat
