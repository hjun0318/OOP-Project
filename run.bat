@echo off
g++ driver.cpp People.cpp Room.cpp SingleRoom.cpp DoubleRoom.cpp Customer.cpp Manager.cpp -o driver
if %errorlevel% neq 0 exit /b %errorlevel%
driver.exe