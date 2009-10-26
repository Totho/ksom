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
CCADMIN=CCadmin
RANLIB=ranlib
CC=mingw32-gcc.exe
CCC=g++.exe
CXX=g++.exe
FC=
AS=as.exe

# Macros
CND_PLATFORM=MinGW-Windows
CND_CONF=Release
CND_DISTDIR=dist

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=build/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/ksom_map.o \
	${OBJECTDIR}/ksom_error.o \
	${OBJECTDIR}/ksom_node.o \
	${OBJECTDIR}/ksom.o

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
	${MAKE}  -f nbproject/Makefile-Release.mk dist/Release/MinGW-Windows/liblibksom.a

dist/Release/MinGW-Windows/liblibksom.a: ${OBJECTFILES}
	${MKDIR} -p dist/Release/MinGW-Windows
	${RM} dist/Release/MinGW-Windows/liblibksom.a
	${AR} rv ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/liblibksom.a ${OBJECTFILES} 
	$(RANLIB) dist/Release/MinGW-Windows/liblibksom.a

${OBJECTDIR}/ksom_map.o: nbproject/Makefile-${CND_CONF}.mk ksom_map.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.c) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/ksom_map.o ksom_map.c

${OBJECTDIR}/ksom_error.o: nbproject/Makefile-${CND_CONF}.mk ksom_error.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.c) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/ksom_error.o ksom_error.c

${OBJECTDIR}/ksom_node.o: nbproject/Makefile-${CND_CONF}.mk ksom_node.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.c) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/ksom_node.o ksom_node.c

${OBJECTDIR}/ksom.o: nbproject/Makefile-${CND_CONF}.mk ksom.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.c) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/ksom.o ksom.c

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf:
	${RM} -r build/Release
	${RM} dist/Release/MinGW-Windows/liblibksom.a

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
