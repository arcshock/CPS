cmp ./testing/correctPS.ps ./testing/filecomp.sh
    if [ $? -eq 0 ] 
    then 
		echo -en "\033[1mPS File DOES match\033[0m\n"
		tput sgr0
    else 
		red='\e[0;31m'
		NC='\e[0m' #No Color
		echo -en "${red}PS file does NOT match${NC}\n" 
		tput sgr0
    fi
