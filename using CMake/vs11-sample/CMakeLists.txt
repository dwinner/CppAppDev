#    Filename : CMakeLists.txt
# Description : project definition for CMake -> MSVC conversion
#				syntax highlighting of CMake files in MSVC 2010++:
#				http://code.google.com/p/vissemee/
#      Author : Jan Helbig
#    MSVCpart : common                
#     Release : 
#   Copyright : (c) 2007-2012 Continental Automotive GmbH
#    Revision : $Revision:$
# ------------------------------------------------------------------------------------------------
#     History : $Log:$
# ================================================================================================

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/tool/cmake/adapt)
include(compiler)

project(NEC_V850_proj)

include(strategy)

cmake_minimum_required(VERSION 2.8.12)
message(STATUS "CMake version: ${CMAKE_VERSION}")      

# name of main vcproj
set(this_target     NEC_V850_proj)					# name of vcproj
set(this_target_dir ${CMAKE_CURRENT_LIST_DIR})		# path of vcproj / CMakeLists.txt
set(this_root_dir   ${CMAKE_HOME_DIRECTORY})		# path of master vcproj / master CMakeLists.txt


include(${this_root_dir}/adapt/gen/arbor/ArborCfg.cmake OPTIONAL RESULT_VARIABLE _arbor_config)
if(NOT _arbor_config)
  message (FATAL_ERROR "ArborCfg missing")
endif()


######################## include common definitions ########################
include(${this_root_dir}/tool/cmake/adapt/common.cmake)


######################## sub projects ######################################
# get sub project once out of oroginal sln file with:
# grep .vcproj ARMx_proj.sln | sed -e 's,.*\(pkg.*prj\).*,\1,'

add_custom_target(ALL_BUILD)
add_custom_target(ZERO_CHECK)

######################## solution structure ###################################
SET_PROPERTY(GLOBAL PROPERTY USE_FOLDERS ON)

SET_PROPERTY(TARGET ALL_BUILD			PROPERTY FOLDER "CMakePredefinedTargets")
SET_PROPERTY(TARGET ZERO_CHECK			PROPERTY FOLDER "CMakePredefinedTargets")


##################################################################################
## section: template / build configuration


include(${this_root_dir}/tool/cmake/adapt/build_configuration.cmk)
include(${this_root_dir}/tool/cmake/adapt/ide_tpl.cmk)

#===Do not put module cmk before this line===#

include(${this_root_dir}/tool/arbor/adapt/arbor.cmk)



# pkg/artemmis
include(${this_root_dir}/pkg/artemmis/adapt/artemmis.cmk)
include(${this_root_dir}/pkg/hmi/epf/pkg/was/adapt/was.cmk)
include(${this_root_dir}/pkg/hmi/epf/pkg/wcs/adapt/wcs.cmk)
include(${this_root_dir}/pkg/hmi/epf/pkg/wds/adapt/wds.cmk)
include(${this_root_dir}/pkg/hmi/epf/pkg/wes/adapt/wes.cmk)
include(${this_root_dir}/pkg/hmi/epf/pkg/wfc/adapt/wfc.cmk)
include(${this_root_dir}/pkg/hmi/epf/pkg/wmms/adapt/wmms.cmk)
include(${this_root_dir}/pkg/hmi/epf/pkg/wrs/adapt/wrs.cmk)
include(${this_root_dir}/pkg/hmi/epf/pkg/wsis/adapt/wsis.cmk)
include(${this_root_dir}/pkg/hmi/epf/pkg/wsms/adapt/wsms.cmk)
include(${this_root_dir}/pkg/hmi/epf/pkg/wws/adapt/wws.cmk)
include(${this_root_dir}/pkg/hmi/epf/pkg/apim/adapt/apim.cmk)
include(${this_root_dir}/pkg/hmi/iaa/pkg/cia/adapt/cia.cmk)
include(${this_root_dir}/pkg/artemmis/prv/samples/pkg/wsms/adapt/wsms.cmk)
if (JCP2016_CPU STREQUAL "1412")  
  include(${this_root_dir}/pkg/application/dcd/adapt/dcd.cmk)
  include(${this_root_dir}/pkg/hmi/iaa/pkg/ace/adapt/ace.cmk)
endif() #if (JCP2016_CPU STREQUAL "1412")
  
# pkg/basedef
include(${this_root_dir}/pkg/basedef/pkg/sysconst/adapt/sysconst.cmk)

# pkg/baseutil
include(${this_root_dir}/pkg/baseutil/pkg/alga/adapt/alga.cmk)
if(DEFINED ARBOR_SUBSYS_MCOM)
  if(ARBOR_SUBSYS_MCOM STREQUAL "ON")
    include(${this_root_dir}/pkg/baseutil/pkg/algae/adapt/algae.cmk)
  endif(ARBOR_SUBSYS_MCOM STREQUAL "ON")
endif(DEFINED ARBOR_SUBSYS_MCOM)
include(${this_root_dir}/pkg/baseutil/pkg/corest/adapt/corest.cmk)
include(${this_root_dir}/pkg/baseutil/pkg/math/adapt/math.cmk)
include(${this_root_dir}/pkg/baseutil/pkg/stlib/adapt/stlib.cmk)

# pkg/vector
include(${this_root_dir}/pkg/vector/BswM/adapt/bswm.cmk)
include(${this_root_dir}/pkg/vector/Can/adapt/can.cmk)
include(${this_root_dir}/pkg/vector/Cani/adapt/cani.cmk)
include(${this_root_dir}/pkg/vector/CanIf/adapt/canif.cmk)
include(${this_root_dir}/pkg/vector/CanNm/adapt/cannm.cmk)
include(${this_root_dir}/pkg/vector/CanSM/adapt/cansm.cmk)
include(${this_root_dir}/pkg/vector/CanTp/adapt/cantp.cmk)
include(${this_root_dir}/pkg/vector/CanTrcv/adapt/CanTrcv.cmk)
include(${this_root_dir}/pkg/vector/Com/adapt/com.cmk)
include(${this_root_dir}/pkg/vector/comm/adapt/comm.cmk)
include(${this_root_dir}/pkg/vector/common/common.cmk)
include(${this_root_dir}/pkg/vector/crc/adapt/crc.cmk)
include(${this_root_dir}/pkg/vector/dcm/adapt/dcm.cmk)
include(${this_root_dir}/pkg/vector/dcmfbl/adapt/dcmfbl.cmk)
include(${this_root_dir}/pkg/vector/dem/adapt/dem.cmk)
include(${this_root_dir}/pkg/vector/demsc/adapt/demsc.cmk)
include(${this_root_dir}/pkg/vector/det/adapt/det.cmk)
include(${this_root_dir}/pkg/vector/ipdum/adapt/ipdum.cmk)
include(${this_root_dir}/pkg/vector/nm/adapt/nm.cmk)
include(${this_root_dir}/pkg/vector/pdur/adapt/pdur.cmk)
include(${this_root_dir}/pkg/vector/roelite/adapt/roelite.cmk)
include(${this_root_dir}/pkg/vector/vstdlib/adapt/vstdlib.cmk)
include(${this_root_dir}/pkg/vector/wem/adapt/wem.cmk)

#pkg/autosar
include(${this_root_dir}/pkg/autosar/pkg/ecum/adapt/ECUM.cmk)
include(${this_root_dir}/pkg/autosar/pkg/gpt/adapt/GPT.cmk)
include(${this_root_dir}/pkg/autosar/pkg/memif/adapt/memif.cmk)
include(${this_root_dir}/pkg/autosar/pkg/nvia/adapt/nvia.cmk)
include(${this_root_dir}/pkg/autosar/pkg/nvm/adapt/nvm.cmk)
include(${this_root_dir}/pkg/autosar/pkg/schm/adapt/SCHM.cmk)
include(${this_root_dir}/pkg/autosar/pkg/wdif/adapt/WDGIF.cmk)
include(${this_root_dir}/pkg/autosar/pkg/wdgm/adapt/WDGM.cmk)
include(${this_root_dir}/pkg/autosar/pkg/stubs/STUBS.cmk)
include(${this_root_dir}/pkg/autosar/pkg/rte/adapt/rte.cmk)
include(${this_root_dir}/pkg/autosar/pkg/e2e/adapt/e2e.cmk)
include(${this_root_dir}/pkg/autosar/pkg/e2emg/adapt/e2emg.cmk)
include(${this_root_dir}/pkg/autosar/pkg/scrc/adapt/scrc.cmk)


# pkg/driver
include(${this_root_dir}/pkg/driver/pkg/adc/adapt/adc.cmk)
include(${this_root_dir}/pkg/driver/pkg/clock/adapt/clock.cmk)
include(${this_root_dir}/pkg/driver/pkg/dio/adapt/dio.cmk)
include(${this_root_dir}/pkg/driver/pkg/dma/adapt/dma.cmk)
include(${this_root_dir}/pkg/driver/pkg/hwheader/pkg/dr7f70${JCP2016_CPU}/adapt/hwheader.cmk)
include(${this_root_dir}/pkg/driver/pkg/pwm/adapt/pwm.cmk)
include(${this_root_dir}/pkg/driver/pkg/sfma/adapt/sfma.cmk)
include(${this_root_dir}/pkg/driver/pkg/shrc/adapt/shrc.cmk)
include(${this_root_dir}/pkg/driver/pkg/spi/adapt/spi.cmk)
include(${this_root_dir}/pkg/driver/pkg/timd/adapt/timd.cmk)
include(${this_root_dir}/pkg/driver/pkg/irt/adapt/irt.cmk)
include(${this_root_dir}/pkg/driver/pkg/movs/adapt/movs.cmk)
include(${this_root_dir}/pkg/driver/pkg/she/adapt/she.cmk)

# pkg/anim
if(JCP2016_CPU STREQUAL "1412")
  include(${this_root_dir}/pkg/anim/antf/adapt/antf.cmk)              
  include(${this_root_dir}/pkg/anim/bca/adapt/bca.cmk)  
  include(${this_root_dir}/pkg/anim/ccsa/adapt/ccsa.cmk)
  include(${this_root_dir}/pkg/anim/dra/adapt/dra.cmk)     
  include(${this_root_dir}/pkg/anim/foa/adapt/foa.cmk)    
  include(${this_root_dir}/pkg/anim/gea/adapt/gea.cmk)
  include(${this_root_dir}/pkg/anim/inan/adapt/inan.cmk)
  include(${this_root_dir}/pkg/anim/lisa/adapt/lisa.cmk)  
  include(${this_root_dir}/pkg/anim/loa/adapt/loa.cmk)  
  include(${this_root_dir}/pkg/anim/mta/adapt/mta.cmk)
  include(${this_root_dir}/pkg/anim/slaa/adapt/slaa.cmk)   
  include(${this_root_dir}/pkg/anim/sua/adapt/sua.cmk)  
  include(${this_root_dir}/pkg/anim/tsaa/adapt/tsaa.cmk)  
  include(${this_root_dir}/pkg/anim/wmapp/adapt/wmapp.cmk)
  include(${this_root_dir}/pkg/anim/xcsa/adapt/xcsa.cmk)
endif() #if(JCP2016_CPU STREQUAL "1412")

# pkg/gs4
if(JCP2016_CPU STREQUAL "1412")
  include(${this_root_dir}/pkg/gs4/pkg/grgl/adapt/grgl.cmk)
  include(${this_root_dir}/pkg/gs4/pkg/grlcd/adapt/grlcd.cmk)
elseif(JCP2016_CPU STREQUAL "1403" OR JCP2016_CPU STREQUAL "1414")
  include(${this_root_dir}/pkg/gs4/pkg/plcd/adapt/plcd.cmk)
  include(${this_root_dir}/pkg/gs4/pkg/plcds/adapt/plcds.cmk)
endif() #if(JCP2016_CPU STREQUAL "1412")
include(${this_root_dir}/pkg/gs4/pkg/fnrft/adapt/fnrft.cmk)
include(${this_root_dir}/pkg/gs4/pkg/fnteg/adapt/fnteg.cmk)
include(${this_root_dir}/pkg/gs4/pkg/gauxl/adapt/gauxl.cmk)
include(${this_root_dir}/pkg/gs4/pkg/gbt/adapt/gbt.cmk)
include(${this_root_dir}/pkg/gs4/pkg/gosw/adapt/gosw.cmk)
include(${this_root_dir}/pkg/gs4/pkg/grlc/adapt/grlc.cmk)
include(${this_root_dir}/pkg/gs4/pkg/gses/adapt/gses.cmk)
include(${this_root_dir}/pkg/gs4/pkg/gtrl/adapt/gtrl.cmk)
include(${this_root_dir}/pkg/gs4/pkg/roch/adapt/roch.cmk)
include(${this_root_dir}/pkg/gs4/pkg/rscache/adapt/rscache.cmk)
include(${this_root_dir}/pkg/gs4/pkg/rsdm/adapt/rsdm.cmk)
include(${this_root_dir}/pkg/gs4/pkg/rsmg/adapt/rsmg.cmk)
include(${this_root_dir}/pkg/gs4/pkg/rsst/adapt/rsst.cmk)
include(${this_root_dir}/pkg/gs4/pkg/tlsf/adapt/tlsf.cmk)

# pkg/ipl
include(${this_root_dir}/pkg/ipl/pkg/cache/adapt/cache.cmk)
include(${this_root_dir}/pkg/ipl/pkg/ivjmp/adapt/ivjmp.cmk)
include(${this_root_dir}/pkg/ipl/pkg/lnkfiles/adapt/Inkfiles.cmk)
include(${this_root_dir}/pkg/ipl/pkg/pman/adapt/pman.cmk)
include(${this_root_dir}/pkg/ipl/pkg/start/adapt/start.cmk)

# pkg/midware
include(${this_root_dir}/pkg/midware/pkg/ace/adapt/ace.cmk)
include(${this_root_dir}/pkg/midware/pkg/asrl/adapt/asrl.cmk)
include(${this_root_dir}/pkg/midware/pkg/cam/adapt/CAM.cmk)
include(${this_root_dir}/pkg/midware/pkg/cont/adapt/CONT.cmk)
include(${this_root_dir}/pkg/midware/pkg/cpcont/adapt/cpcont.cmk)
include(${this_root_dir}/pkg/midware/pkg/crhdl/adapt/CRHDL.cmk)
include(${this_root_dir}/pkg/midware/pkg/cthdl/adapt/CTHDL.cmk)
include(${this_root_dir}/pkg/midware/pkg/dmm/adapt/dmm.cmk)
include(${this_root_dir}/pkg/midware/pkg/dpool/adapt/DPOOL.cmk)
include(${this_root_dir}/pkg/midware/pkg/evhd/adapt/EVHD.cmk)
include(${this_root_dir}/pkg/midware/pkg/exea/adapt/exea.cmk)
include(${this_root_dir}/pkg/midware/pkg/exsto/adapt/exsto.cmk)
include(${this_root_dir}/pkg/midware/pkg/frt/adapt/FRT.cmk)
include(${this_root_dir}/pkg/midware/pkg/idle/adapt/idle.cmk)
include(${this_root_dir}/pkg/midware/pkg/ipc/adapt/ipc.cmk)
include(${this_root_dir}/pkg/midware/pkg/irext/adapt/irext.cmk)
include(${this_root_dir}/pkg/midware/pkg/main/adapt/main.cmk)
include(${this_root_dir}/pkg/midware/pkg/sini/adapt/SINI.cmk)
include(${this_root_dir}/pkg/midware/pkg/timer/adapt/TIMER.cmk)
include(${this_root_dir}/pkg/midware/pkg/wdog/adapt/wdog.cmk)

# pkg/nvms
include(${this_root_dir}/pkg/nvms/pkg/dfda/adapt/dfda.cmk)
include(${this_root_dir}/pkg/nvms/pkg/eed/adapt/eed.cmk)
include(${this_root_dir}/pkg/nvms/pkg/eel/adapt/eel.cmk)
include(${this_root_dir}/pkg/nvms/pkg/fdl/adapt/fdl.cmk)
include(${this_root_dir}/pkg/nvms/pkg/fee/adapt/fee.cmk)
include(${this_root_dir}/pkg/nvms/pkg/nvaa/adapt/nvaa.cmk)
include(${this_root_dir}/pkg/nvms/pkg/nvdia/adapt/nvdia.cmk)
include(${this_root_dir}/pkg/nvms/pkg/nvstub/adapt/nvstub.cmk)
include(${this_root_dir}/pkg/nvms/pkg/nvtst/adapt/nvtst.cmk)

# pkg/sysid
include(${this_root_dir}/pkg/sysid/adapt/sysid.cmk)
include(${this_root_dir}/tool/flg/adapt/flg.cmk)

# pkg/safegraphics
if(JCP2016_CPU STREQUAL "1412")
include(${this_root_dir}/pkg/safegraphics/pkg/gvom/adapt/gvom.cmk)
endif() #if(JCP2016_CPU STREQUAL "1412")

# pkg/application
include(${this_root_dir}/pkg/application/aspdi/adapt/aspdi.cmk)
include(${this_root_dir}/pkg/application/aspee/adapt/aspee.cmk)
include(${this_root_dir}/pkg/application/aspke/adapt/aspke.cmk)
include(${this_root_dir}/pkg/application/sms/adapt/sms.cmk)
include(${this_root_dir}/pkg/application/sok/adapt/sok.cmk)
include(${this_root_dir}/pkg/application/esed/adapt/esed.cmk)
include(${this_root_dir}/pkg/application/ecos/adapt/ecos.cmk)
include(${this_root_dir}/pkg/application/sdf/adapt/sdf.cmk)
include(${this_root_dir}/pkg/application/tthdl/adapt/tthdl.cmk)
include(${this_root_dir}/pkg/application/cst/adapt/cst.cmk)
include(${this_root_dir}/pkg/application/vel/adapt/vel.cmk)
include(${this_root_dir}/pkg/application/units/adapt/units.cmk)
include(${this_root_dir}/pkg/application/rev/adapt/rev.cmk)
include(${this_root_dir}/pkg/application/wtp/adapt/wtp.cmk)
include(${this_root_dir}/pkg/application/flg/adapt/flg.cmk)
include(${this_root_dir}/pkg/application/dim/adapt/dim.cmk)
include(${this_root_dir}/pkg/application/vms/adapt/vms.cmk)
include(${this_root_dir}/pkg/application/rms/adapt/rms.cmk)
include(${this_root_dir}/pkg/application/odo/adapt/odo.cmk)
include(${this_root_dir}/pkg/application/dlib/adapt/dlib.cmk)
include(${this_root_dir}/pkg/application/ind/adapt/ind.cmk)
include(${this_root_dir}/pkg/application/otemp/adapt/otemp.cmk)
include(${this_root_dir}/pkg/application/kbd/adapt/kbd.cmk)
if(JCP2016_CPU STREQUAL "1412")
include(${this_root_dir}/pkg/application/bootmgr/adapt/bootmgr.cmk)
endif() #if(JCP2016_CPU STREQUAL "1412")
include(${this_root_dir}/pkg/application/adjrtc/adapt/adjrtc.cmk)
include(${this_root_dir}/pkg/application/wim/adapt/wim.cmk)
include(${this_root_dir}/pkg/application/tpm/adapt/tpm.cmk)
include(${this_root_dir}/pkg/application/scs/adapt/scs.cmk)
include(${this_root_dir}/pkg/application/fcw/adapt/fcw.cmk)
include(${this_root_dir}/pkg/application/dsr/adapt/dsr.cmk)
include(${this_root_dir}/pkg/application/trc/adapt/trc.cmk)
include(${this_root_dir}/pkg/application/mbseg/adapt/mbseg.cmk)
include(${this_root_dir}/pkg/application/lpanim/adapt/lpanim.cmk)
include(${this_root_dir}/pkg/application/hilac/adapt/hilac.cmk)
include(${this_root_dir}/pkg/application/sbw/adapt/sbw.cmk)
include(${this_root_dir}/pkg/application/gear/adapt/gear.cmk)
include(${this_root_dir}/pkg/application/tetac/adapt/tetac.cmk)
include(${this_root_dir}/pkg/application/sfg/adapt/sfg.cmk)
include(${this_root_dir}/pkg/application/sam/adapt/sam.cmk)
include(${this_root_dir}/pkg/application/som/adapt/som.cmk)
include(${this_root_dir}/pkg/application/syman/adapt/syman.cmk)
include(${this_root_dir}/pkg/application/tpol/adapt/tpol.cmk)
include(${this_root_dir}/pkg/application/cfgac/adapt/cfgac.cmk)
include(${this_root_dir}/pkg/application/tsa/adapt/tsa.cmk)
include(${this_root_dir}/pkg/application/ofn/adapt/ofn.cmk)
include(${this_root_dir}/pkg/application/wmn/adapt/wmn.cmk)
include(${this_root_dir}/pkg/application/dsfa/adapt/dsfa.cmk)
include(${this_root_dir}/pkg/application/gar/adapt/gar.cmk)
include(${this_root_dir}/pkg/application/csp/adapt/csp.cmk)
include(${this_root_dir}/pkg/chw/adapt/chw.cmk)
include(${this_root_dir}/pkg/application/syval/adapt/syval.cmk)
include(${this_root_dir}/pkg/application/avol/adapt/avol.cmk)
include(${this_root_dir}/pkg/application/mpsd/adapt/mpsd.cmk)
include(${this_root_dir}/pkg/application/pktac/adapt/pktac1.cmk)
include(${this_root_dir}/pkg/application/pktgc/adapt/pktgc1.cmk)
include(${this_root_dir}/pkg/application/docg/adapt/docg.cmk)
include(${this_root_dir}/pkg/application/tdp/adapt/tdp.cmk)
include(${this_root_dir}/pkg/application/key/adapt/key.cmk)
include(${this_root_dir}/pkg/application/sec/adapt/sec.cmk)
if(JCP2016_CPU STREQUAL "1412")
include(${this_root_dir}/pkg/application/notl/adapt/NOTL1.cmk)
endif() #if(JCP2016_CPU STREQUAL "1412")
include(${this_root_dir}/pkg/application/sbc/adapt/sbc.cmk)
include(${this_root_dir}/pkg/application/fsm/adapt/fsm.cmk)
include(${this_root_dir}/pkg/application/dum/adapt/dum.cmk)
include(${this_root_dir}/pkg/application/hy/adapt/hy.cmk)
include(${this_root_dir}/pkg/application/cmon/adapt/cmon.cmk)
include(${this_root_dir}/pkg/application/ahs/adapt/ahs.cmk) 
include(${this_root_dir}/pkg/application/dcapp/adapt/dcapp.cmk)
include(${this_root_dir}/pkg/application/dcpl/adapt/dcpl.cmk)
include(${this_root_dir}/pkg/application/excom/adapt/excom.cmk)
include(${this_root_dir}/pkg/application/heatm/adapt/heatm.cmk)
include(${this_root_dir}/pkg/application/wlchk/adapt/wlchk.cmk)
include(${this_root_dir}/pkg/application/pfhdl/adapt/pfhdl.cmk)
include(${this_root_dir}/pkg/application/apc/adapt/apc.cmk)
include(${this_root_dir}/pkg/application/taehdl/adapt/taehdl.cmk)

# pkg/hmi
include(${this_root_dir}/pkg/hmi/chrgmdl/adapt/chrgmdl.cmk)
include(${this_root_dir}/pkg/hmi/tools/adapt/tools.cmk)
include(${this_root_dir}/pkg/hmi/dfw/adapt/dfw.cmk)
include(${this_root_dir}/pkg/hmi/wfcext/adapt/wfcext.cmk)
include(${this_root_dir}/pkg/hmi/dsm/adapt/dsm.cmk)
include(${this_root_dir}/pkg/hmi/apif/adapt/apif.cmk)
include(${this_root_dir}/pkg/hmi/abluemdl/adapt/abluemdl.cmk)
include(${this_root_dir}/pkg/hmi/fasmdl/adapt/fasmdl.cmk)
include(${this_root_dir}/pkg/hmi/gearmdl/adapt/gearmdl.cmk)
include(${this_root_dir}/pkg/hmi/garmdl/adapt/garmdl.cmk)
include(${this_root_dir}/pkg/hmi/statmdl/adapt/statmdl.cmk)
include(${this_root_dir}/pkg/hmi/icbwmdl/adapt/icbwmdl.cmk)
include(${this_root_dir}/pkg/hmi/sacmdl/adapt/sacmdl.cmk)
include(${this_root_dir}/pkg/hmi/tpmmdl/adapt/tpmmdl.cmk)
include(${this_root_dir}/pkg/hmi/trcmdl/adapt/trcmdl.cmk)
include(${this_root_dir}/pkg/hmi/cwmdl/adapt/cwmdl.cmk)
include(${this_root_dir}/pkg/hmi/aad/adapt/aad.cmk)
include(${this_root_dir}/pkg/hmi/apcmdl/adapt/apcmdl.cmk)
include(${this_root_dir}/pkg/hmi/sbwmdl/adapt/sbwmdl.cmk)
if(JCP2016_CPU STREQUAL "1412")
include(${this_root_dir}/pkg/hmi/list/adapt/list.cmk)

endif() #if(JCP2016_CPU STREQUAL "1412")
include(${this_root_dir}/pkg/hmi/fman/adapt/fman.cmk)
include(${this_root_dir}/pkg/hmi/slis/adapt/slis.cmk)
include(${this_root_dir}/pkg/hmi/barw/adapt/barw.cmk)
include(${this_root_dir}/pkg/hmi/aspmdl/adapt/aspmdl.cmk)
include(${this_root_dir}/pkg/hmi/diagmdl/adapt/diagmdl.cmk)
include(${this_root_dir}/pkg/hmi/spin/adapt/spin.cmk)
include(${this_root_dir}/pkg/hmi/cfgmdl/adapt/cfgmdl.cmk)
include(${this_root_dir}/pkg/hmi/tglc/adapt/tglc.cmk)
include(${this_root_dir}/pkg/hmi/lrw/adapt/lrw.cmk)
include(${this_root_dir}/pkg/hmi/nines/adapt/nines.cmk)
include(${this_root_dir}/pkg/hmi/pusw/adapt/pusw.cmk)
include(${this_root_dir}/pkg/hmi/trsw/adapt/trsw.cmk)
include(${this_root_dir}/pkg/hmi/tsamdl/adapt/tsamdl.cmk)
include(${this_root_dir}/pkg/hmi/coolmdl/adapt/coolmdl.cmk)
include(${this_root_dir}/pkg/hmi/atamdl/adapt/atamdl.cmk)
include(${this_root_dir}/pkg/hmi/adcmdl/adapt/adcmdl.cmk)
include(${this_root_dir}/pkg/hmi/dhi/adapt/dhi.cmk)

# pkg/sema
if (JCP2016_CPU STREQUAL "1412") 
include(${this_root_dir}/pkg/hmi/sema/adapt/sema.cmk)
endif() #if (JCP2016_CPU STREQUAL "1412")

# pkg/os
include(${this_root_dir}/pkg/os/pkg/aros/adapt/aros.cmk)
include(${this_root_dir}/pkg/os/pkg/hooks/adapt/hooks.cmk)

# pkg/pcmsub
include(${this_root_dir}/pkg/pcmsub/pkg/pcmpl/adapt/pcmpl.cmk)
include(${this_root_dir}/pkg/pcmsub/pkg/pcmr/adapt/pcmr.cmk)

# pkg/simenv
include(${this_root_dir}/pkg/simenv/adapt/simenv.cmk)
include(${this_root_dir}/pkg/simenv/pkg/hwsimu/adapt/hwsimu.cmk)
include(${this_root_dir}/pkg/simenv/pkg/Utilities/adapt/Utilities.cmk)
include(${this_root_dir}/pkg/simenv/pkg/sgen/adapt/sgen.cmk)
include(${this_root_dir}/pkg/simenv/pkg/wosek/adapt/wosek.cmk)
include(${this_root_dir}/pkg/simenv/pkg/sgfx/adapt/sgfx.cmk)

# pkg/trace
if(DEFINED ARBOR_SUBSYS_TRACE)
  if(ARBOR_SUBSYS_TRACE STREQUAL "ON")
    include(${this_root_dir}/pkg/trace/adapt/TRACE.cmk)
    include(${this_root_dir}/pkg/trace/adapt/trace_printf.cmk)
  endif(ARBOR_SUBSYS_TRACE STREQUAL "ON")
endif(DEFINED ARBOR_SUBSYS_TRACE)



unset(this_package)	# clear package name


##################################################################################
## section: sources
## Add your source files here (one file per line), please SORT in alphabetical order for future maintenance
set(SYS_FILES
  ${this_target_dir}/pkg/admin/adapt/${VARIANT}/${VARIANT}.sdi
  ${this_target_dir}/adapt/japs_nec850_simu.tcs
  ${this_target_dir}/adapt/japs_nec850_tgt.tcs

# pkg/basedef
  ${this_target_dir}/pkg/basedef/pkg/cdef/core/cdef.h
  ${this_target_dir}/pkg/basedef/pkg/cdef/core/cdef_common.h
  ${this_target_dir}/pkg/basedef/pkg/cdef/core/cdef_deprecated.h
  ${this_target_dir}/pkg/basedef/pkg/commons/core/commons.h
  ${this_target_dir}/pkg/basedef/pkg/dbgsw/adapt/Dbgswi.h
  ${this_target_dir}/pkg/basedef/pkg/iodef/adapt/Iodef.h
  ${this_target_dir}/pkg/basedef/pkg/iodef/adapt/iodef.sdh
  ${this_target_dir}/pkg/basedef/pkg/sysconst/core/Sysconst.h

# pkg/ipl
  ${this_target_dir}/pkg/ipl/pkg/lnkfiles/core/sect_ids.h

# arbor
  ${this_target_dir}/adapt/gen/arbor/ArborCfg.h
)

staticFileList(
  ${this_root_dir}/adapt/japs_nec850_simu.tcs
  ${this_root_dir}/adapt/japs_nec850_tgt.tcs
  ${this_root_dir}/adapt/gen/arbor/ArborCfg.h
  ${this_root_dir}/adapt/jenkins/jenkinsid.h
  ${this_root_dir}/adapt/aims/aims1ce.h
  ${this_root_dir}/adapt/aims/gitid1ce.h
  ${SYS_FILES}
)

generatedFileList(
)


###############################################################################
# add files which should be excluded from build:
excludeFromBuild(
)
excludeFromBuildSimulation(
)
excludeFromBuildTarget(
)


###############################################################################
# write file list of excluded files (needed by cmake post processing scipt)
writeExcludeListFile()


### Ignore specific libraries for HL simulation
if(NOT CMAKE_CROSSCOMPILING)
  SET(CMAKE_EXE_LINKER_FLAGS /NODEFAULTLIB:\"LIBCMT;MSVCRT\")    
endif()


##################################################################################
## section: target
## MSVC vcproj mapping ConfigurationType="?" 
## 1 Application (.exe)
## 2 Dynamic Library (.dll)
## 4 Static  Library (.lib)
if(CMAKE_CROSSCOMPILING)
  LIST(REMOVE_ITEM ${this_target}_SOURCE_FILES ${${this_target}_FILES_EXCLUDED} ${${this_target}_FILES_EXCLUDED_TARGET})
endif()

cds_process_strategy(option_files ${${this_target}_SOURCE_FILES})
list(APPEND ${this_target}_SOURCE_FILES ${option_files})

ADD_EXECUTABLE (${this_target} ${${this_target}_SOURCE_FILES})
### Copy dll for HL simulation
add_custom_command(TARGET ${this_target} POST_BUILD
  COMMAND xcopy /Y /I pkg\\gs4\\pkg\\grgl\\core\\davehd\\softdave\\bin\\*.dll ide\\out\\hex\\DEBUG\\
  COMMAND xcopy /Y /I pkg\\gs4\\pkg\\grgl\\core\\vlib\\device\\win_x86\\src\\d1hxsim\\src\\powervr\\build\\Release\\*.dll ide\\out\\hex\\DEBUG\\
  COMMAND xcopy /Y /I pkg\\gs4\\pkg\\grgl\\core\\vlib\\device\\win_x86\\src\\d1hxsim\\src\\gfxcache\\build\\Release\\*.dll ide\\out\\hex\\DEBUG\\
  WORKING_DIRECTORY ${this_target_dir}
  COMMENT "[CMake] Copy davehd_[f]sd.dll files to the exe directory"
)
### underscore headers before compilation, for simu only
add_custom_command(TARGET ${this_target} PRE_BUILD
  COMMAND make.bat -sr uh_all IDE_BUILD_CFG=Debug
  COMMENT "Underscore headers befor compilation for Simu"
)

SET_TARGET_PROPERTIES(${this_target} PROPERTIES LINKER_LANGUAGE CXX)
# c file should be compiled with c compiler instead of cpp compiler
# therefor find all c files from the source file list to set the compiler flag
setCCompilerFlag( "${${this_target}_SOURCE_FILES}" )
write_target_filelists()

# exclude projects from build solution in visual studio
SET_TARGET_PROPERTIES(ZERO_CHECK 										PROPERTIES EXCLUDE_FROM_DEFAULT_BUILD 1)


###############################################################################
# Additional Include Directories
add_target_includeDirs(
  ide/tmp/inc/ph
  ide/tmp/inc/uh
  .

  pkg/midware/pkg/ace/core
  pkg/midware/pkg/ace/adapt
#  pkg/tool/sysconf/tool/ace2aros/adapt/tcb
  pkg/midware/pkg/ace/core/ace/os_include


  # Boost
  pkg/baseutil/pkg/boost/core

  # Ace
#  pkg/dsosal/tool
#  pkg/dsosal/tool/ace/os_include
#  pkg/dsosal/tool/ace2aros/adapt/tcb

  # Graphics font related
  ./pkg/gs4/pkg/fnrft/core
  ./pkg/gs4/pkg/fnrft/core/core
  ./pkg/gs4/pkg/fnrft/core/include
  ./pkg/gs4/pkg/fnrft/core/freetype
)

add_simulation_includeDirs(
  ide/tmp/inc/ph
  ide/tmp/inc/uh
  .

  pkg/midware/pkg/ace/core
  pkg/midware/pkg/ace/adapt
#  pkg/tool/ace2aros/adapt/tcb
  pkg/midware/pkg/ace/core/ace/os_include

  # Graphics font related
  pkg/gs4/pkg/fnrft/core
  pkg/gs4/pkg/fnrft/core/core
  pkg/gs4/pkg/fnrft/core/include
  pkg/gs4/pkg/fnrft/core/freetype  

  # Boost
  pkg/baseutil/pkg/boost/core

  # Ace
#  pkg/dsosal/tool
#  pkg/dsosal/tool/ace/os_include
#  pkg/dsosal/tool/ace2aros/adapt/tcb
)


###############################################################################
# preprocessor definitions
add_target_definitions(
  EMBEDDED
  osdRenameOsSections
  osdUserStackSection
  osdAlarmHandlingControl
  osdFlashProgrammerSupport
  OS_SUPPRESS_CALLEESTUB
  OSAL_ACE_AROS

  # ATST
  OS_TYPE_SCHA=0
  OS_TYPE_NOOS=1
  OS_TYPE_OSEK=2
  OS_TYPE=OS_TYPE_OSEK
  # Example: Enable ADC ATST
  DSINT_nTestConfiguration=16 

  # Boost
  BOOST_NO_EXCEPTIONS
  BOOST_EXCEPTION_DISABLE
  BOOST_DISABLE_ASSERTS
  #cdef
  CDEF_DEPRECATED_INCLUDESTDINT
  CDEF_DEPRECATED_NONPREFIXSTYPES
  CDEF_DEPRECATED_NONPREFIXUTYPES
  CDEF_DEPRECATED_NONPREFIXONOFF
  CDEF_DEPRECATED_NONPREFIXOKNOK
  CDEF_DEPRECATED_NONPREFIXYESNO
  CDEF_DEPRECATED_NONPREFIXTRUEFALSE
  CDEF_DEPRECATED_TYPES
  CDEF_DEPRECATED_MEDIUMCONST
  CDEF_DEPRECATED_BITMASKS
  CDEF_DEPRECATED_BINARYCONVERTERS
  CDEF_FLOAT_SYNONYMS
  CDEF_DEPRECATED_NONPREFIXTYPES
  CDEF_DEPRECATED_NONPREFIXBITFIELDS
  CDEF_DEPRECATED_NONPREFIXRECORDS
  CDEF_DEPRECATED_NONPREFIXBITTYPES
  CDEF_DEPRECATED_NONPREFIXBOOLTYPE
  CDEF_DEPRECATED_NONPREFIXFP
  CDEF_DEPRECATED_NONPREFIXLIMITU8
  CDEF_DEPRECATED_NONPREFIXLIMITU16
  CDEF_DEPRECATED_NONPREFIXLIMITU32
  CDEF_DEPRECATED_NONPREFIXLIMITU64
  CDEF_DEPRECATED_INTERNALLIMITU64
  CDEF_DEPRECATED_NONPREFIXLIMITSS8
  CDEF_DEPRECATED_NONPREFIXLIMITSS16
  CDEF_DEPRECATED_NONPREFIXLIMITSS32
  CDEF_DEPRECATED_INTERNALLIMITSS64
  CDEF_FLOAT_SUPPORT

  R_INLINE=inline

  # Altia
  ALTIA_USE_GRGL
  ALTIAGL
  DEEPSCREEN
  #ALTIA_ALIGN=__attribute__((aligned(128)))
  ALTIA_DRV_LOADASSET
  ALTIA_ALPHA_BLENDING=0
  NO_DAO_DLL
  RUNGLDATA
  # CFTEST_DEBUG
  RENESAS_D1X
)

add_simulation_definitions(
  WIN32
  _WINDOWS
  _PC_SIMULATION_
  inline=__inline
  IDE_nProcess=SYSCONST_nProcessBaseSystem
  ACE_AS_STATIC_LIBS
  HWH_Simulation
  OS_SUPPRESS_CALLEESTUB
  _AFXDLL
  _MKS_STRUCTURE_
  DPOOL_PANEL
  NEW_CIA_ACE
  _UNICODE 
  _XKEYCHECK_H 
  R_INLINE=_forceinline
  OSAL_ACE_AROS

  # Altia
  _CRT_NON_CONFORMING_SWPRINTFS
  _CRT_SECURE_NO_DEPRECATE
  _CRT_SECURE_NO_WARNINGS
  ALTIA_USE_GRGL
  ALTIAGL
  DEEPSCREEN
  #ALTIA_ALIGN=__attribute__((aligned(128)))
  ALTIA_DRV_LOADASSET
  ALTIA_ALPHA_BLENDING=0
  NO_DAO_DLL
  RUNGLDATA

  DSINT_nTestConfiguration=16
  # Boost
  BOOST_NO_EXCEPTIONS
  BOOST_EXCEPTION_DISABLE
  BOOST_DISABLE_ASSERTS
  
  #cdef
  CDEF_DEPRECATED_NONPREFIXSTYPES
  CDEF_DEPRECATED_NONPREFIXUTYPES
  CDEF_DEPRECATED_NONPREFIXONOFF
  CDEF_DEPRECATED_NONPREFIXOKNOK
  CDEF_DEPRECATED_NONPREFIXYESNO
  CDEF_DEPRECATED_NONPREFIXTRUEFALSE
  CDEF_DEPRECATED_TYPES
  CDEF_DEPRECATED_MEDIUMCONST
  CDEF_DEPRECATED_BITMASKS
  CDEF_DEPRECATED_BINARYCONVERTERS
  CDEF_FLOAT_SYNONYMS
  CDEF_DEPRECATED_NONPREFIXTYPES
  CDEF_DEPRECATED_NONPREFIXBITFIELDS
  CDEF_DEPRECATED_NONPREFIXRECORDS
  CDEF_DEPRECATED_NONPREFIXBITTYPES
  CDEF_DEPRECATED_NONPREFIXBOOLTYPE
  CDEF_DEPRECATED_NONPREFIXFP
  CDEF_DEPRECATED_NONPREFIXLIMITU8
  CDEF_DEPRECATED_NONPREFIXLIMITU16
  CDEF_DEPRECATED_NONPREFIXLIMITU32
  CDEF_DEPRECATED_NONPREFIXLIMITU64
  CDEF_DEPRECATED_INTERNALLIMITU64
  CDEF_DEPRECATED_NONPREFIXLIMITSS8
  CDEF_DEPRECATED_NONPREFIXLIMITSS16
  CDEF_DEPRECATED_NONPREFIXLIMITSS32
  CDEF_DEPRECATED_INTERNALLIMITSS64
  CDEF_FLOAT_SUPPORT
)

if(ARBOR_SUBSYS_GS_DHD STREQUAL "ON")
  add_simulation_definitions(
    R_DRW2D_OS_WIN32
    R_USE_FASTSOFTDAVE
    SOFTDAVE_WIN32  
  )
endif()

###############################################################################
# add additional libraries needed to build the project
if(DEFINED ARBOR_SUBSYS_SIMENV)
  if(ARBOR_SUBSYS_SIMENV STREQUAL "ON")
    add_simulation_libraries(
      # Ws2_32.lib is used by COMPT winsock.h
      Ws2_32.lib
      # User32.lib is used by SGFX SGFX_Window::WndProc
      User32.lib
    )
  endif(ARBOR_SUBSYS_SIMENV STREQUAL "ON")
endif(DEFINED ARBOR_SUBSYS_SIMENV)

add_simulation_libraries(
  winmm.lib
  opengl32.lib
  gdiplus.lib
  ./pkg/gs4/pkg/grgl/core/lib/d1mx_sim
  ./pkg/gs4/pkg/grgl/core/lib/turbojpeg-static
  ./pkg/gs4/pkg/grgl/core/lib/drw2d
  ./pkg/gs4/pkg/grgl/core/lib/wm
  #./pkg/gs4/pkg/grgl/core/lib/d1hx_sim
  #./pkg/gs4/pkg/grgl/core/lib/d1hx_platform_win32_fsd
  #./pkg/gs4/pkg/grgl/core/vlib/device/win_x86/src/d1hxsim/src/powervr/bin/libEGL
  #./pkg/gs4/pkg/grgl/core/vlib/device/win_x86/src/d1hxsim/src/powervr/bin/libGLESv2
  #./pkg/gs4/pkg/grgl/core/vlib/device/win_x86/src/d1hxsim/src/powervr/build/Release/powervr
  #./pkg/gs4/pkg/grgl/core/vlib/device/win_x86/src/d1hxsim/src/gfxcache/build/Release/gfxcache
  ./pkg/gs4/pkg/grgl/core/davehd/build/win32/msvc/Release/dhd_kernel
  ./pkg/gs4/pkg/grgl/core/davehd/build/win32/msvc/Release/dhd_user
  ./pkg/gs4/pkg/grgl/core/davehd/softdave/bin/davehd_fsd
  #./pkg/gs4/pkg/grgl/core/davehd/softdave/bin/davehd_sd
  ./pkg/simenv/pkg/hwsimu/core/vxlapi
)

add_target_libraries(
# <project>_Multi2000_libs_gen
./tool/cmake/out/NEC_V850_proj_Multi2000_libs_gen
)

##################################################################################
# writes a makefile containing the System Configuration
FILE(WRITE "CMake_reGen.bat" "@echo off\nrem This file is generated by CMake\nrem Use it to re-generate your project after changing CMake files.\nif exist make.bat ( call make.bat -s tool TOOL=cmake TARGET=clean && call make.bat -s tool TOOL=cmake TARGET=run ) else ( echo make.bat not found! )\npause\n")


##################################################################################
if(CMAKE_VERBOSE_MAKEFILE)
  include(CMakePrintSystemInformation)
  
  ## print out all CMAKE variables for debugging
  get_cmake_property(_variableNames VARIABLES)
  foreach (_variableName ${_variableNames})
    message(STATUS "${_variableName}=${${_variableName}}")
  endforeach()
endif()
