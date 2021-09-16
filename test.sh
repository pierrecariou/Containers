#!/bin/bash

echo;echo;echo "----------------------------------------"
echo -e "\e[1m
              TESTER FT_CONTAINERS
	          FT versus STL
 \e[0m"
			

echo "          FT" > ft.log; echo; echo "-FT stats-"; time ./ft 1 2>fterror.log >> ft.log
echo "          STL" > stl.log; echo; echo "-STL stats-"; time ./stl 1 2> stlerror.log >> stl.log
echo;echo;

diff --color fterror.log stlerror.log
diff --color ft.log stl.log
rm ft.log stl.log fterror.log stlerror.log
