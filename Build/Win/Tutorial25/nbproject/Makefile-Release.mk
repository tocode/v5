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
CND_CONF=Release
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/lighting_technique.o \
	${OBJECTDIR}/tutorial25.o \
	${OBJECTDIR}/skybox_technique.o \
	${OBJECTDIR}/skybox.o \
	${OBJECTDIR}/glut_backend.o \
	${OBJECTDIR}/mesh.o \
	${OBJECTDIR}/pipeline.o \
	${OBJECTDIR}/math_3d.o \
	${OBJECTDIR}/camera.o \
	${OBJECTDIR}/cubemap_texture.o \
	${OBJECTDIR}/technique.o \
	${OBJECTDIR}/texture.o


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
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/tutorial25

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/tutorial25: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/tutorial25 ${OBJECTFILES} ${LDLIBSOPTIONS} 

${OBJECTDIR}/lighting_technique.o: nbproject/Makefile-${CND_CONF}.mk lighting_technique.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/lighting_technique.o lighting_technique.cpp

${OBJECTDIR}/tutorial25.o: nbproject/Makefile-${CND_CONF}.mk tutorial25.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/tutorial25.o tutorial25.cpp

${OBJECTDIR}/skybox_technique.o: nbproject/Makefile-${CND_CONF}.mk skybox_technique.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/skybox_technique.o skybox_technique.cpp

${OBJECTDIR}/skybox.o: nbproject/Makefile-${CND_CONF}.mk skybox.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/skybox.o skybox.cpp

${OBJECTDIR}/glut_backend.o: nbproject/Makefile-${CND_CONF}.mk glut_backend.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/glut_backend.o glut_backend.cpp

${OBJECTDIR}/mesh.o: nbproject/Makefile-${CND_CONF}.mk mesh.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/mesh.o mesh.cpp

${OBJECTDIR}/pipeline.o: nbproject/Makefile-${CND_CONF}.mk pipeline.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/pipeline.o pipeline.cpp

${OBJECTDIR}/math_3d.o: nbproject/Makefile-${CND_CONF}.mk math_3d.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/math_3d.o math_3d.cpp

${OBJECTDIR}/camera.o: nbproject/Makefile-${CND_CONF}.mk camera.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/camera.o camera.cpp

${OBJECTDIR}/cubemap_texture.o: nbproject/Makefile-${CND_CONF}.mk cubemap_texture.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/cubemap_texture.o cubemap_texture.cpp

${OBJECTDIR}/technique.o: nbproject/Makefile-${CND_CONF}.mk technique.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/technique.o technique.cpp

${OBJECTDIR}/texture.o: nbproject/Makefile-${CND_CONF}.mk texture.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/texture.o texture.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/tutorial25

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
