CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -pedantic -Iinclude
SOURCES = src/main.cpp src/cau_truc_sach.cpp src/bang_bam_doc_gia.cpp src/lich_su_muon_tra.cpp src/quan_ly_tap_tin.cpp
TARGET = library.exe
all:
	$(CXX) $(CXXFLAGS) $(SOURCES) -o $(TARGET)
clean:
	rm -f $(TARGET)