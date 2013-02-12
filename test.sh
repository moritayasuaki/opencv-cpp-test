#!/bin/zsh

if [ $# -ne 4 ]; then
  echo "please input 4 arguments"
  exit 1
fi

REF_R=$1
REF_T=$2
SRCDIR=$3
DESTDIR=$4

for file in `ls $SRCDIR/*R.jpg`
do 
  FILENAME=`basename $file`
  echo $file
  ./align $REF_R $file $DESTDIR/${FILENAME%.jpg}.yml
done

for file in `ls $SRCDIR/*T.jpg`
do 
  FILENAME=`basename $file`
  echo $file
  ./align $REF_T $file $DESTDIR/${FILENAME%.jpg}.yml
done

