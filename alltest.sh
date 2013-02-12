#!/bin/zsh

REFR=argen-o-000/1R.jpg
REFT=argen-o-000/1T.jpg

mkdir argen-o-freak
rm -rf argen-o-freak/*

./test.sh $REFR $REFT argen-o-000 argen-o-freak 000-
./test.sh $REFR $REFT argen-o-500 argen-o-freak 500-
./test.sh $REFR $REFT argen-o-900-1 argen-o-freak 900-1-
./test.sh $REFR $REFT argen-o-900-2 argen-o-freak 900-2-
./test.sh $REFR $REFT argen-o-1150 argen-o-freak 1150-
./test.sh $REFR $REFT argen-o-1700 argen-o-freak 1700-
./test.sh $REFR $REFT argen-o-2500 argen-o-freak 2500-
./test.sh $REFR $REFT argen-o-3200 argen-o-freak 3200-
./test.sh $REFR $REFT argen-o-4000 argen-o-freak 4000-
./test.sh $REFR $REFT argen-o-4700 argen-o-freak 4700-
