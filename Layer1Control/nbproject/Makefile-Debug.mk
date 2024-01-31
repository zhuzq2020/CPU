#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
GREP=grep
NM=nm
CCADMIN=CCadmin
RANLIB=ranlib
CC=aarch64-fsl-linux-gcc
CCC=aarch64-fsl-linux-g++
CXX=aarch64-fsl-linux-g++
FC=gfortran
AS=aarch64-fsl-linux-as

# Macros
CND_PLATFORM=aarch64-fsl-Linux
CND_DLIB_EXT=so
CND_CONF=Debug
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/ctrlplane/l1c_ctrlplane.o \
	${OBJECTDIR}/ctrlplane/rrc_phy_ifc/rrc_phy_ifc.o \
	${OBJECTDIR}/dataplane/l1c_dataplane.o \
	${OBJECTDIR}/inferface/l1c_phy_ifc.o \
	${OBJECTDIR}/init/l1c_init.o \
	${OBJECTDIR}/main.o \
	${OBJECTDIR}/util/ctimer/ctimer.o \
	${OBJECTDIR}/util/msg/l1c_msg.o


# C Compiler Flags
CFLAGS=--sysroot=/opt/fsl-qoriq/2.5/sysroots/aarch64-fsl-linux

# CC Compiler Flags
CCFLAGS=--sysroot=/opt/fsl-qoriq/2.5/sysroots/aarch64-fsl-linux
CXXFLAGS=--sysroot=/opt/fsl-qoriq/2.5/sysroots/aarch64-fsl-linux

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/layer1control

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/layer1control: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.c} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/layer1control ${OBJECTFILES} ${LDLIBSOPTIONS} -lrt -lpthread -lm

${OBJECTDIR}/ctrlplane/l1c_ctrlplane.o: ctrlplane/l1c_ctrlplane.c
	${MKDIR} -p ${OBJECTDIR}/ctrlplane
	${RM} "$@.d"
	$(COMPILE.c) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/ctrlplane/l1c_ctrlplane.o ctrlplane/l1c_ctrlplane.c

${OBJECTDIR}/ctrlplane/rrc_phy_ifc/rrc_phy_ifc.o: ctrlplane/rrc_phy_ifc/rrc_phy_ifc.c
	${MKDIR} -p ${OBJECTDIR}/ctrlplane/rrc_phy_ifc
	${RM} "$@.d"
	$(COMPILE.c) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/ctrlplane/rrc_phy_ifc/rrc_phy_ifc.o ctrlplane/rrc_phy_ifc/rrc_phy_ifc.c

${OBJECTDIR}/dataplane/l1c_dataplane.o: dataplane/l1c_dataplane.c
	${MKDIR} -p ${OBJECTDIR}/dataplane
	${RM} "$@.d"
	$(COMPILE.c) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/dataplane/l1c_dataplane.o dataplane/l1c_dataplane.c

${OBJECTDIR}/inferface/l1c_phy_ifc.o: inferface/l1c_phy_ifc.c
	${MKDIR} -p ${OBJECTDIR}/inferface
	${RM} "$@.d"
	$(COMPILE.c) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/inferface/l1c_phy_ifc.o inferface/l1c_phy_ifc.c

${OBJECTDIR}/init/l1c_init.o: init/l1c_init.c
	${MKDIR} -p ${OBJECTDIR}/init
	${RM} "$@.d"
	$(COMPILE.c) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/init/l1c_init.o init/l1c_init.c

${OBJECTDIR}/main.o: main.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/main.o main.c

${OBJECTDIR}/util/ctimer/ctimer.o: util/ctimer/ctimer.c
	${MKDIR} -p ${OBJECTDIR}/util/ctimer
	${RM} "$@.d"
	$(COMPILE.c) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/util/ctimer/ctimer.o util/ctimer/ctimer.c

${OBJECTDIR}/util/msg/l1c_msg.o: util/msg/l1c_msg.c
	${MKDIR} -p ${OBJECTDIR}/util/msg
	${RM} "$@.d"
	$(COMPILE.c) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/util/msg/l1c_msg.o util/msg/l1c_msg.c

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
