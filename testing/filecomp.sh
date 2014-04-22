cmp ./testing/correctPS.ps ./testing/cps.cpp 
    if [ $? -eq 0 ] 
    then 
		echo -en "\033[1mPS File DOES match\033[0m\n"
		tput sgr0
    else 
		echo -en "\033[1mPS file does NOT match\033[0m\n" 
		tput sgr0
    fi
