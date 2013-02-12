#!/bin/zsh

REFR=argen-o-000/1R.jpg
REFT=argen-o-000/1T.jpg

mkdir histograms
rm -rf histograms/*

./genhist.sh $REFR $REFT vocab.yml argen-o-000 histograms 000-
./genhist.sh $REFR $REFT vocab.yml argen-o-500 histograms 500-
./genhist.sh $REFR $REFT vocab.yml argen-o-900-1 histograms 900-1-
./genhist.sh $REFR $REFT vocab.yml argen-o-900-2 histograms 900-2-
./genhist.sh $REFR $REFT vocab.yml argen-o-1150 histograms 1150-
./genhist.sh $REFR $REFT vocab.yml argen-o-1700 histograms 1700-
./genhist.sh $REFR $REFT vocab.yml argen-o-2500 histograms 2500-
./genhist.sh $REFR $REFT vocab.yml argen-o-3200 histograms 3200-
./genhist.sh $REFR $REFT vocab.yml argen-o-4000 histograms 4000-
./genhist.sh $REFR $REFT vocab.yml argen-o-4700 histograms 4700-
