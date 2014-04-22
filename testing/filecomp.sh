red='\033[0;31m'
green='\033[0;32m'
NC='\033[0m' #No Color

cmp ./testing/correctPS.ps ./testing/testing.ps
    if [ $? -eq 0 ] 
    then 
		echo "${green}PS File DOES match${NC}\n"
		tput sgr0
    else 
		echo "${red}PS file does NOT match${NC}\n" 
		tput sgr0
    fi
