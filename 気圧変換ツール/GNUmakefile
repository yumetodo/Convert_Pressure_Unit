# Makefile for Multidimensional_array.cpp
# Multidimensional_array.exe: Multidimensional_array.cpp
# 	g++ ./Multidimensional_array/Multidimensional_array.cpp --input-charset=utf-8 -fexec-charset=CP932 -std=c++11 -O2 -Wall -o Multidimensional_array.exe -lws2_32 -lwinmm -lwsock32

TARGET 	= Convert_Pressure_Unit2.exe
SRCS 	= ./気圧変換ツール/Source.cpp ./気圧変換ツール/mystring.cpp

# 基本コマンド
RM 		:= rm
CXX 	:= g++
CC 		:= g++

# デバッグ時とリリース時の微調整
CXX_DEBUG_FLAGS		=	-g -O0
CXX_RELEASE_FLAGS	=	-O2

# 基本オプション
CPPFLAGS = --input-charset=utf-8 -fexec-charset=CP932 -Wall -std=c++11

# make
# debug
.PHONY	: Debug
Debug 	: CXXFLAGS+=$(CXX_DEBUG_FLAGS)
Debug 	: all
# release
.PHONY	: Release
Release	: CXXFLAGS+=$(CXX_RELEASE_FLAGS)
Release	: all

all : $(TARGET)
$(TARGET) : $(SRCS)
		$(CXX) $^ -o $@ $(CXXFLAGS) $(CPPFLAGS)

# make clean
.PHONY: clean
clean:
	rm -f *.o