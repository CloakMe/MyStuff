##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## debug_multithreading
ProjectName            :=LearnAndDevelop
ConfigurationName      :=debug_multithreading
WorkspaceConfiguration :=debug_MultiThreading
WorkspacePath          :=/home/admin/d_virtual/who/MyStuff/LearnAndDevelop
ProjectPath            :=/home/admin/d_virtual/who/MyStuff/LearnAndDevelop
IntermediateDirectory  :=build-$(WorkspaceConfiguration)
OutDir                 :=$(IntermediateDirectory)
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=
Date                   :=20/03/26
CodeLitePath           :=/home/admin/.codelite
MakeDirCommand         :=mkdir -p
LinkerName             :=/usr/bin/g++
SharedObjectLinkerName :=/usr/bin/g++ -shared -fPIC
ObjectSuffix           :=.o
DependSuffix           :=.o.d
PreprocessSuffix       :=.i
DebugSwitch            :=-g 
IncludeSwitch          :=-I
LibrarySwitch          :=-l
OutputSwitch           :=-o 
LibraryPathSwitch      :=-L
PreprocessorSwitch     :=-D
SourceSwitch           :=-c 
OutputDirectory        :=/home/admin/d_virtual/who/MyStuff/LearnAndDevelop/build-$(WorkspaceConfiguration)/bin
OutputFile             :=build-$(WorkspaceConfiguration)/bin/$(ProjectName)
Preprocessors          :=
ObjectSwitch           :=-o 
ArchiveOutputSwitch    := 
PreprocessOnlySwitch   :=-E
ObjectsFileList        :=$(IntermediateDirectory)/ObjectsList.txt
PCHCompileFlags        :=
LinkOptions            :=  -O0
IncludePath            :=  $(IncludeSwitch). $(IncludeSwitch). 
IncludePCH             := 
RcIncludePath          := 
Libs                   := 
ArLibs                 :=  
LibPath                := $(LibraryPathSwitch). $(LibraryPathSwitch). $(LibraryPathSwitch)Debug 

##
## Common variables
## AR, CXX, CC, AS, CXXFLAGS and CFLAGS can be overridden using an environment variable
##
AR       := /usr/bin/ar rcu
CXX      := /usr/bin/g++
CC       := /usr/bin/gcc
CXXFLAGS :=  -g -Wall $(Preprocessors)
CFLAGS   :=   $(Preprocessors)
ASFLAGS  := 
AS       := /usr/bin/as


##
## User defined environment variables
##
CodeLiteDir:=/usr/share/codelite
Objects0=$(IntermediateDirectory)/UdemyDP_ImageProxy_main.cpp$(ObjectSuffix) $(IntermediateDirectory)/UdemyDP_ImageProxy_Image.cpp$(ObjectSuffix) $(IntermediateDirectory)/UdemyDP_ImageProxy_BitmapProxy.cpp$(ObjectSuffix) $(IntermediateDirectory)/Udemy_ExercisesMain.cpp$(ObjectSuffix) $(IntermediateDirectory)/Parallelism_main.cpp$(ObjectSuffix) $(IntermediateDirectory)/MultiThreading_MultiThreading.cpp$(ObjectSuffix) $(IntermediateDirectory)/MultiThreading_MutexUsage.cpp$(ObjectSuffix) $(IntermediateDirectory)/Udemy_ConcurentStructuresModifier.cpp$(ObjectSuffix) $(IntermediateDirectory)/Udemy_ThreadBenchmark.cpp$(ObjectSuffix) $(IntermediateDirectory)/MultiThreading_BarrierUsage.cpp$(ObjectSuffix) \
	$(IntermediateDirectory)/MultiThreading_LatchUsage.cpp$(ObjectSuffix) $(IntermediateDirectory)/MultiThreading_FutureUsage.cpp$(ObjectSuffix) $(IntermediateDirectory)/MultiThreading_CondVariable.cpp$(ObjectSuffix) $(IntermediateDirectory)/Udemy_FizzBuzz.cpp$(ObjectSuffix) $(IntermediateDirectory)/Udemy_Monitor.cpp$(ObjectSuffix) $(IntermediateDirectory)/Basics_Basics.cpp$(ObjectSuffix) $(IntermediateDirectory)/Udemy_Worker.cpp$(ObjectSuffix) $(IntermediateDirectory)/Udemy_ThreadPool.cpp$(ObjectSuffix) $(IntermediateDirectory)/Udemy_ThreadQueue.cpp$(ObjectSuffix) $(IntermediateDirectory)/UdemyDP_ImageProxy_Bitmap.cpp$(ObjectSuffix) \
	



Objects=$(Objects0) 

##
## Main Build Targets 
##
.PHONY: all clean PreBuild PrePreBuild PostBuild MakeIntermediateDirs
all: MakeIntermediateDirs $(OutputFile)

$(OutputFile): $(IntermediateDirectory)/.d $(Objects) 
	@$(MakeDirCommand) "$(IntermediateDirectory)"
	@echo "" > $(IntermediateDirectory)/.d
	@echo $(Objects0)  > $(ObjectsFileList)
	$(LinkerName) $(OutputSwitch)$(OutputFile) @$(ObjectsFileList) $(LibPath) $(Libs) $(LinkOptions)

MakeIntermediateDirs:
	@$(MakeDirCommand) "$(IntermediateDirectory)"
	@$(MakeDirCommand) "$(OutputDirectory)"

$(IntermediateDirectory)/.d:
	@$(MakeDirCommand) "$(IntermediateDirectory)"

PreBuild:


##
## Objects
##
$(IntermediateDirectory)/UdemyDP_ImageProxy_main.cpp$(ObjectSuffix): UdemyDP/ImageProxy/main.cpp $(IntermediateDirectory)/UdemyDP_ImageProxy_main.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/admin/d_virtual/who/MyStuff/LearnAndDevelop/UdemyDP/ImageProxy/main.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/UdemyDP_ImageProxy_main.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/UdemyDP_ImageProxy_main.cpp$(DependSuffix): UdemyDP/ImageProxy/main.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/UdemyDP_ImageProxy_main.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/UdemyDP_ImageProxy_main.cpp$(DependSuffix) -MM UdemyDP/ImageProxy/main.cpp

$(IntermediateDirectory)/UdemyDP_ImageProxy_main.cpp$(PreprocessSuffix): UdemyDP/ImageProxy/main.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/UdemyDP_ImageProxy_main.cpp$(PreprocessSuffix) UdemyDP/ImageProxy/main.cpp

$(IntermediateDirectory)/UdemyDP_ImageProxy_Image.cpp$(ObjectSuffix): UdemyDP/ImageProxy/Image.cpp $(IntermediateDirectory)/UdemyDP_ImageProxy_Image.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/admin/d_virtual/who/MyStuff/LearnAndDevelop/UdemyDP/ImageProxy/Image.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/UdemyDP_ImageProxy_Image.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/UdemyDP_ImageProxy_Image.cpp$(DependSuffix): UdemyDP/ImageProxy/Image.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/UdemyDP_ImageProxy_Image.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/UdemyDP_ImageProxy_Image.cpp$(DependSuffix) -MM UdemyDP/ImageProxy/Image.cpp

$(IntermediateDirectory)/UdemyDP_ImageProxy_Image.cpp$(PreprocessSuffix): UdemyDP/ImageProxy/Image.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/UdemyDP_ImageProxy_Image.cpp$(PreprocessSuffix) UdemyDP/ImageProxy/Image.cpp

$(IntermediateDirectory)/UdemyDP_ImageProxy_BitmapProxy.cpp$(ObjectSuffix): UdemyDP/ImageProxy/BitmapProxy.cpp $(IntermediateDirectory)/UdemyDP_ImageProxy_BitmapProxy.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/admin/d_virtual/who/MyStuff/LearnAndDevelop/UdemyDP/ImageProxy/BitmapProxy.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/UdemyDP_ImageProxy_BitmapProxy.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/UdemyDP_ImageProxy_BitmapProxy.cpp$(DependSuffix): UdemyDP/ImageProxy/BitmapProxy.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/UdemyDP_ImageProxy_BitmapProxy.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/UdemyDP_ImageProxy_BitmapProxy.cpp$(DependSuffix) -MM UdemyDP/ImageProxy/BitmapProxy.cpp

$(IntermediateDirectory)/UdemyDP_ImageProxy_BitmapProxy.cpp$(PreprocessSuffix): UdemyDP/ImageProxy/BitmapProxy.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/UdemyDP_ImageProxy_BitmapProxy.cpp$(PreprocessSuffix) UdemyDP/ImageProxy/BitmapProxy.cpp

$(IntermediateDirectory)/Udemy_ExercisesMain.cpp$(ObjectSuffix): Udemy/ExercisesMain.cpp $(IntermediateDirectory)/Udemy_ExercisesMain.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/admin/d_virtual/who/MyStuff/LearnAndDevelop/Udemy/ExercisesMain.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Udemy_ExercisesMain.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Udemy_ExercisesMain.cpp$(DependSuffix): Udemy/ExercisesMain.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Udemy_ExercisesMain.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/Udemy_ExercisesMain.cpp$(DependSuffix) -MM Udemy/ExercisesMain.cpp

$(IntermediateDirectory)/Udemy_ExercisesMain.cpp$(PreprocessSuffix): Udemy/ExercisesMain.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Udemy_ExercisesMain.cpp$(PreprocessSuffix) Udemy/ExercisesMain.cpp

$(IntermediateDirectory)/Parallelism_main.cpp$(ObjectSuffix): Parallelism/main.cpp $(IntermediateDirectory)/Parallelism_main.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/admin/d_virtual/who/MyStuff/LearnAndDevelop/Parallelism/main.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Parallelism_main.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Parallelism_main.cpp$(DependSuffix): Parallelism/main.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Parallelism_main.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/Parallelism_main.cpp$(DependSuffix) -MM Parallelism/main.cpp

$(IntermediateDirectory)/Parallelism_main.cpp$(PreprocessSuffix): Parallelism/main.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Parallelism_main.cpp$(PreprocessSuffix) Parallelism/main.cpp

$(IntermediateDirectory)/MultiThreading_MultiThreading.cpp$(ObjectSuffix): MultiThreading/MultiThreading.cpp $(IntermediateDirectory)/MultiThreading_MultiThreading.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/admin/d_virtual/who/MyStuff/LearnAndDevelop/MultiThreading/MultiThreading.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/MultiThreading_MultiThreading.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/MultiThreading_MultiThreading.cpp$(DependSuffix): MultiThreading/MultiThreading.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/MultiThreading_MultiThreading.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/MultiThreading_MultiThreading.cpp$(DependSuffix) -MM MultiThreading/MultiThreading.cpp

$(IntermediateDirectory)/MultiThreading_MultiThreading.cpp$(PreprocessSuffix): MultiThreading/MultiThreading.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/MultiThreading_MultiThreading.cpp$(PreprocessSuffix) MultiThreading/MultiThreading.cpp

$(IntermediateDirectory)/MultiThreading_MutexUsage.cpp$(ObjectSuffix): MultiThreading/MutexUsage.cpp $(IntermediateDirectory)/MultiThreading_MutexUsage.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/admin/d_virtual/who/MyStuff/LearnAndDevelop/MultiThreading/MutexUsage.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/MultiThreading_MutexUsage.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/MultiThreading_MutexUsage.cpp$(DependSuffix): MultiThreading/MutexUsage.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/MultiThreading_MutexUsage.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/MultiThreading_MutexUsage.cpp$(DependSuffix) -MM MultiThreading/MutexUsage.cpp

$(IntermediateDirectory)/MultiThreading_MutexUsage.cpp$(PreprocessSuffix): MultiThreading/MutexUsage.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/MultiThreading_MutexUsage.cpp$(PreprocessSuffix) MultiThreading/MutexUsage.cpp

$(IntermediateDirectory)/Udemy_ConcurentStructuresModifier.cpp$(ObjectSuffix): Udemy/ConcurentStructuresModifier.cpp $(IntermediateDirectory)/Udemy_ConcurentStructuresModifier.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/admin/d_virtual/who/MyStuff/LearnAndDevelop/Udemy/ConcurentStructuresModifier.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Udemy_ConcurentStructuresModifier.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Udemy_ConcurentStructuresModifier.cpp$(DependSuffix): Udemy/ConcurentStructuresModifier.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Udemy_ConcurentStructuresModifier.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/Udemy_ConcurentStructuresModifier.cpp$(DependSuffix) -MM Udemy/ConcurentStructuresModifier.cpp

$(IntermediateDirectory)/Udemy_ConcurentStructuresModifier.cpp$(PreprocessSuffix): Udemy/ConcurentStructuresModifier.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Udemy_ConcurentStructuresModifier.cpp$(PreprocessSuffix) Udemy/ConcurentStructuresModifier.cpp

$(IntermediateDirectory)/Udemy_ThreadBenchmark.cpp$(ObjectSuffix): Udemy/ThreadBenchmark.cpp $(IntermediateDirectory)/Udemy_ThreadBenchmark.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/admin/d_virtual/who/MyStuff/LearnAndDevelop/Udemy/ThreadBenchmark.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Udemy_ThreadBenchmark.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Udemy_ThreadBenchmark.cpp$(DependSuffix): Udemy/ThreadBenchmark.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Udemy_ThreadBenchmark.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/Udemy_ThreadBenchmark.cpp$(DependSuffix) -MM Udemy/ThreadBenchmark.cpp

$(IntermediateDirectory)/Udemy_ThreadBenchmark.cpp$(PreprocessSuffix): Udemy/ThreadBenchmark.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Udemy_ThreadBenchmark.cpp$(PreprocessSuffix) Udemy/ThreadBenchmark.cpp

$(IntermediateDirectory)/MultiThreading_BarrierUsage.cpp$(ObjectSuffix): MultiThreading/BarrierUsage.cpp $(IntermediateDirectory)/MultiThreading_BarrierUsage.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/admin/d_virtual/who/MyStuff/LearnAndDevelop/MultiThreading/BarrierUsage.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/MultiThreading_BarrierUsage.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/MultiThreading_BarrierUsage.cpp$(DependSuffix): MultiThreading/BarrierUsage.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/MultiThreading_BarrierUsage.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/MultiThreading_BarrierUsage.cpp$(DependSuffix) -MM MultiThreading/BarrierUsage.cpp

$(IntermediateDirectory)/MultiThreading_BarrierUsage.cpp$(PreprocessSuffix): MultiThreading/BarrierUsage.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/MultiThreading_BarrierUsage.cpp$(PreprocessSuffix) MultiThreading/BarrierUsage.cpp

$(IntermediateDirectory)/MultiThreading_LatchUsage.cpp$(ObjectSuffix): MultiThreading/LatchUsage.cpp $(IntermediateDirectory)/MultiThreading_LatchUsage.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/admin/d_virtual/who/MyStuff/LearnAndDevelop/MultiThreading/LatchUsage.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/MultiThreading_LatchUsage.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/MultiThreading_LatchUsage.cpp$(DependSuffix): MultiThreading/LatchUsage.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/MultiThreading_LatchUsage.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/MultiThreading_LatchUsage.cpp$(DependSuffix) -MM MultiThreading/LatchUsage.cpp

$(IntermediateDirectory)/MultiThreading_LatchUsage.cpp$(PreprocessSuffix): MultiThreading/LatchUsage.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/MultiThreading_LatchUsage.cpp$(PreprocessSuffix) MultiThreading/LatchUsage.cpp

$(IntermediateDirectory)/MultiThreading_FutureUsage.cpp$(ObjectSuffix): MultiThreading/FutureUsage.cpp $(IntermediateDirectory)/MultiThreading_FutureUsage.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/admin/d_virtual/who/MyStuff/LearnAndDevelop/MultiThreading/FutureUsage.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/MultiThreading_FutureUsage.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/MultiThreading_FutureUsage.cpp$(DependSuffix): MultiThreading/FutureUsage.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/MultiThreading_FutureUsage.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/MultiThreading_FutureUsage.cpp$(DependSuffix) -MM MultiThreading/FutureUsage.cpp

$(IntermediateDirectory)/MultiThreading_FutureUsage.cpp$(PreprocessSuffix): MultiThreading/FutureUsage.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/MultiThreading_FutureUsage.cpp$(PreprocessSuffix) MultiThreading/FutureUsage.cpp

$(IntermediateDirectory)/MultiThreading_CondVariable.cpp$(ObjectSuffix): MultiThreading/CondVariable.cpp $(IntermediateDirectory)/MultiThreading_CondVariable.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/admin/d_virtual/who/MyStuff/LearnAndDevelop/MultiThreading/CondVariable.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/MultiThreading_CondVariable.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/MultiThreading_CondVariable.cpp$(DependSuffix): MultiThreading/CondVariable.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/MultiThreading_CondVariable.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/MultiThreading_CondVariable.cpp$(DependSuffix) -MM MultiThreading/CondVariable.cpp

$(IntermediateDirectory)/MultiThreading_CondVariable.cpp$(PreprocessSuffix): MultiThreading/CondVariable.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/MultiThreading_CondVariable.cpp$(PreprocessSuffix) MultiThreading/CondVariable.cpp

$(IntermediateDirectory)/Udemy_FizzBuzz.cpp$(ObjectSuffix): Udemy/FizzBuzz.cpp $(IntermediateDirectory)/Udemy_FizzBuzz.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/admin/d_virtual/who/MyStuff/LearnAndDevelop/Udemy/FizzBuzz.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Udemy_FizzBuzz.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Udemy_FizzBuzz.cpp$(DependSuffix): Udemy/FizzBuzz.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Udemy_FizzBuzz.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/Udemy_FizzBuzz.cpp$(DependSuffix) -MM Udemy/FizzBuzz.cpp

$(IntermediateDirectory)/Udemy_FizzBuzz.cpp$(PreprocessSuffix): Udemy/FizzBuzz.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Udemy_FizzBuzz.cpp$(PreprocessSuffix) Udemy/FizzBuzz.cpp

$(IntermediateDirectory)/Udemy_Monitor.cpp$(ObjectSuffix): Udemy/Monitor.cpp $(IntermediateDirectory)/Udemy_Monitor.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/admin/d_virtual/who/MyStuff/LearnAndDevelop/Udemy/Monitor.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Udemy_Monitor.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Udemy_Monitor.cpp$(DependSuffix): Udemy/Monitor.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Udemy_Monitor.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/Udemy_Monitor.cpp$(DependSuffix) -MM Udemy/Monitor.cpp

$(IntermediateDirectory)/Udemy_Monitor.cpp$(PreprocessSuffix): Udemy/Monitor.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Udemy_Monitor.cpp$(PreprocessSuffix) Udemy/Monitor.cpp

$(IntermediateDirectory)/Basics_Basics.cpp$(ObjectSuffix): Basics/Basics.cpp $(IntermediateDirectory)/Basics_Basics.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/admin/d_virtual/who/MyStuff/LearnAndDevelop/Basics/Basics.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Basics_Basics.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Basics_Basics.cpp$(DependSuffix): Basics/Basics.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Basics_Basics.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/Basics_Basics.cpp$(DependSuffix) -MM Basics/Basics.cpp

$(IntermediateDirectory)/Basics_Basics.cpp$(PreprocessSuffix): Basics/Basics.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Basics_Basics.cpp$(PreprocessSuffix) Basics/Basics.cpp

$(IntermediateDirectory)/Udemy_Worker.cpp$(ObjectSuffix): Udemy/Worker.cpp $(IntermediateDirectory)/Udemy_Worker.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/admin/d_virtual/who/MyStuff/LearnAndDevelop/Udemy/Worker.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Udemy_Worker.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Udemy_Worker.cpp$(DependSuffix): Udemy/Worker.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Udemy_Worker.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/Udemy_Worker.cpp$(DependSuffix) -MM Udemy/Worker.cpp

$(IntermediateDirectory)/Udemy_Worker.cpp$(PreprocessSuffix): Udemy/Worker.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Udemy_Worker.cpp$(PreprocessSuffix) Udemy/Worker.cpp

$(IntermediateDirectory)/Udemy_ThreadPool.cpp$(ObjectSuffix): Udemy/ThreadPool.cpp $(IntermediateDirectory)/Udemy_ThreadPool.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/admin/d_virtual/who/MyStuff/LearnAndDevelop/Udemy/ThreadPool.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Udemy_ThreadPool.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Udemy_ThreadPool.cpp$(DependSuffix): Udemy/ThreadPool.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Udemy_ThreadPool.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/Udemy_ThreadPool.cpp$(DependSuffix) -MM Udemy/ThreadPool.cpp

$(IntermediateDirectory)/Udemy_ThreadPool.cpp$(PreprocessSuffix): Udemy/ThreadPool.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Udemy_ThreadPool.cpp$(PreprocessSuffix) Udemy/ThreadPool.cpp

$(IntermediateDirectory)/Udemy_ThreadQueue.cpp$(ObjectSuffix): Udemy/ThreadQueue.cpp $(IntermediateDirectory)/Udemy_ThreadQueue.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/admin/d_virtual/who/MyStuff/LearnAndDevelop/Udemy/ThreadQueue.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Udemy_ThreadQueue.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Udemy_ThreadQueue.cpp$(DependSuffix): Udemy/ThreadQueue.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Udemy_ThreadQueue.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/Udemy_ThreadQueue.cpp$(DependSuffix) -MM Udemy/ThreadQueue.cpp

$(IntermediateDirectory)/Udemy_ThreadQueue.cpp$(PreprocessSuffix): Udemy/ThreadQueue.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Udemy_ThreadQueue.cpp$(PreprocessSuffix) Udemy/ThreadQueue.cpp

$(IntermediateDirectory)/UdemyDP_ImageProxy_Bitmap.cpp$(ObjectSuffix): UdemyDP/ImageProxy/Bitmap.cpp $(IntermediateDirectory)/UdemyDP_ImageProxy_Bitmap.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/admin/d_virtual/who/MyStuff/LearnAndDevelop/UdemyDP/ImageProxy/Bitmap.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/UdemyDP_ImageProxy_Bitmap.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/UdemyDP_ImageProxy_Bitmap.cpp$(DependSuffix): UdemyDP/ImageProxy/Bitmap.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/UdemyDP_ImageProxy_Bitmap.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/UdemyDP_ImageProxy_Bitmap.cpp$(DependSuffix) -MM UdemyDP/ImageProxy/Bitmap.cpp

$(IntermediateDirectory)/UdemyDP_ImageProxy_Bitmap.cpp$(PreprocessSuffix): UdemyDP/ImageProxy/Bitmap.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/UdemyDP_ImageProxy_Bitmap.cpp$(PreprocessSuffix) UdemyDP/ImageProxy/Bitmap.cpp


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) -r $(IntermediateDirectory)


