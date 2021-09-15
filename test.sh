#!/bin/bash

./ft 1 2>fterror.log > ft.log
./stl 1 2> stlerror.log > stl.log
diff --color fterror.log stlerror.log
diff --color ft.log stl.log
rm ft.log stl.log fterror.log stlerror.log
