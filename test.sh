#!/bin/zsh

if [ $# -ne 5 ]; then
  echo "please input 5 arguments"
  exit 1
fi

REF_R=$1
REF_T=$2
SRCDIR=$3
DESTDIR=$4
PREFIX=$5

for file in `ls $SRCDIR/*R.jpg`
do 
  FILENAME=`basename $file`
  echo $file
  ./align $file $REF_R $DESTDIR/${PREFIX}${FILENAME%.jpg}.yml
done

for file in `ls $SRCDIR/*T.jpg`
do 
  FILENAME=`basename $file`
  echo $file
  ./align $file $REF_T $DESTDIR/${PREFIX}${FILENAME%.jpg}.yml
done

