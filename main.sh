#!/bin/bash
simple_readlink(){
  TARGET_FILE=$1

  cd `dirname $TARGET_FILE`
  TARGET_FILE=`basename $TARGET_FILE`

  # Iterate down a (possible) chain of symlinks
  while [ -L "$TARGET_FILE" ]
  do
      TARGET_FILE=`readlink $TARGET_FILE`
      cd `dirname $TARGET_FILE`
      TARGET_FILE=`basename $TARGET_FILE`
  done

  # Compute the canonicalized name by finding the physical path 
  # for the directory we're in and appending the target file.
  PHYS_DIR=`pwd -P`
  RESULT=$PHYS_DIR/$TARGET_FILE

  if [ $# -gt 1 ]; then
    eval ${@: -1}=$RESEULT
  else
     echo $RESULT
  fi
}


select_prompt(){
  ret=$1
  shift
  title=$1
  prompt="Pick an option:"
  shift
  options=($@)

  echo "$title"
  PS3="$prompt "

  select opt in "${options[@]}" "Quit"; do 

      case "$REPLY" in

      1 ) break ;;
      2 ) break ;;
      3 ) break ;;

      $(( ${#options[@]}+1 )) ) echo "Goodbye!"; exit;;
      *) echo "Invalid option. Try another one.";continue;;

      esac
  done
  eval $ret=$opt
}

yn_prompt(){
  ret=$1
  while true; do
    echo -n $2
    read yn
    case $yn in
        [Yy]* ) break;;
        [Nn]* ) break;;
        * ) echo "Please answer yes or no.";;
    esac
  done
  eval $ret=$yn
}

main(){
  confirm='n'
  while [[ ! $confirm == [Yy] ]]
  do
    echo "Please enter the name of the copy right holders:"
    read holdersName
    select_prompt license "Select a license" "MIT" "GPLv3" "WTFPL" 
    echo "Please enter the years of releases (2016):"
    read years
    if [[ $years == '' ]];then
      years='2016'
    fi

    echo ""
    echo "Your $license license will be copyrighted as"
    echo "Copyright (C)  $years  $holdersName"
    yn_prompt confirm "Are these information correct? (Y/n)  "
  done


  # Get path and copy
  # Absolute path to this script, e.g. /home/user/bin/foo.sh
  SCRIPT=$(simple_readlink "$0")
  # Absolute path this script is in, thus /home/user/bin
  SCRIPTPATH=$(dirname "$SCRIPT")
  cp $SCRIPTPATH/licenses/$license.txt $PWD
  

  # Replace the year and copyright holder names
  sed -e "s|\<years>|${years}|g" $PWD/$license.txt > $PWD/.temp.txt
  sed -e "s|\<copyright holders>|${holdersName}|g" $PWD/.temp.txt  > $PWD/$license.txt

  rm $PWD/.temp.txt
  mv $PWD/$license.txt $PWD/$license
  echo "Done: license file created at $PWD/$license"
  
}

main