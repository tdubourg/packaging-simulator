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
CC=gcc
CCC=g++
CXX=g++
FC=gfortran
AS=as

# Macros
CND_PLATFORM=GNU-Linux-x86
CND_DLIB_EXT=so
CND_CONF=Release
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/_ext/1738881925/partsPackager.o \
	${OBJECTDIR}/doWarehouse.o \
	${OBJECTDIR}/simu/newpart.o \
	${OBJECTDIR}/doLog.o \
	${OBJECTDIR}/doPrint.o \
	${OBJECTDIR}/doPalette.o \
	${OBJECTDIR}/main.o \
	${OBJECTDIR}/doControl.o \
	${OBJECTDIR}/doCommunication.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/server

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/server: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.c} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/server ${OBJECTFILES} ${LDLIBSOPTIONS} 

${OBJECTDIR}/_ext/1738881925/partsPackager.o: ../../../../../../Dropbox/Documents/TP-IF/4IF/ciai/code/server/server/partsPackager.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/1738881925
	${RM} $@.d
	$(COMPILE.c) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1738881925/partsPackager.o ../../../../../../Dropbox/Documents/TP-IF/4IF/ciai/code/server/server/partsPackager.c

${OBJECTDIR}/doWarehouse.o: doWarehouse.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.c) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/doWarehouse.o doWarehouse.c

${OBJECTDIR}/simu/newpart.o: simu/newpart.c 
	${MKDIR} -p ${OBJECTDIR}/simu
	${RM} $@.d
	$(COMPILE.c) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/simu/newpart.o simu/newpart.c

${OBJECTDIR}/doLog.o: doLog.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.c) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/doLog.o doLog.c

${OBJECTDIR}/doPrint.o: doPrint.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.c) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/doPrint.o doPrint.c

${OBJECTDIR}/doPalette.o: doPalette.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.c) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/doPalette.o doPalette.c

${OBJECTDIR}/main.o: main.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.c) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/main.o main.c

${OBJECTDIR}/doControl.o: doControl.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.c) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/doControl.o doControl.c

${OBJECTDIR}/doCommunication.o: doCommunication.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.c) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/doCommunication.o doCommunication.c

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/server

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
