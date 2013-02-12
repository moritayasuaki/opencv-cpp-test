#!/bin/zsh

REFR=argen-o-000/1R.jpg
REFT=argen-o-000/1T.jpg

./test.sh REFR REFT argen-o-000 argen-o-000-freak
./test.sh REFR REFT argen-o-500 argen-o-500-freak
./test.sh REFR REFT argen-o-900-1 argen-o-900-1-freak
./test.sh REFR REFT argen-o-900-2 argen-o-900-2-freak
./test.sh REFR REFT argen-o-1150 argen-o-1150-freak
./test.sh REFR REFT argen-o-1700 argen-o-1700-freak
./test.sh REFR REFT argen-o-2500 argen-o-2500-freak
./test.sh REFR REFT argen-o-3200 argen-o-3200-freak
./test.sh REFR REFT argen-o-4000 argen-o-4000-freak
./test.sh REFR REFT argen-o-4700 argen-o-4000-freak

