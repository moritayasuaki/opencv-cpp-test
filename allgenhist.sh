#!/bin/zsh

REFR=argen-o-000/1R.jpg
REFT=argen-o-000/1T.jpg

mkdir histograms
rm -rf histograms/*

./genhist.sh $REFR $REFT vocab.yml argen-o-000 histograms 000_
./genhist.sh $REFR $REFT vocab.yml argen-o-500 histograms 500_
./genhist.sh $REFR $REFT vocab.yml argen-o-900-1 histograms 900_1_
./genhist.sh $REFR $REFT vocab.yml argen-o-900-2 histograms 900_2_
./genhist.sh $REFR $REFT vocab.yml argen-o-1150 histograms 1150_
./genhist.sh $REFR $REFT vocab.yml argen-o-1700 histograms 1700_
./genhist.sh $REFR $REFT vocab.yml argen-o-2500 histograms 2500_
./genhist.sh $REFR $REFT vocab.yml argen-o-3200 histograms 3200_
./genhist.sh $REFR $REFT vocab.yml argen-o-4000 histograms 4000_
./genhist.sh $REFR $REFT vocab.yml argen-o-4700 histograms 4700_
