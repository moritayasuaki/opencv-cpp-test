#!/bin/zsh

if [ $# -ne 6 ]; then
  echo "please input 6 arguments"
  exit 1
fi

REF_R=$1
REF_T=$2
VOCAB=$3
SRCDIR=$4
DESTDIR=$5
PREFIX=$6

for file in `ls $SRCDIR/*R.jpg`
do 
  FILENAME=`basename $file`
  echo $file
  ./hist $file $REF_R $VOCAB $DESTDIR/${PREFIX}${FILENAME%.jpg}.yml
done

for file in `ls $SRCDIR/*T.jpg`
do 
  FILENAME=`basename $file`
  echo $file
  ./hist $file $REF_T $VOCAB $DESTDIR/${PREFIX}${FILENAME%.jpg}.yml
done

