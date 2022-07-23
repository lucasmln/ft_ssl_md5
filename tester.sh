#!/bin/bash

clean() {
	echo "Removed all files in tester directory" 
	if [ "$(ls -A ./tester)" ]; then
		rm tester/*
	else
		echo "No files to delete"
	fi
}


check_algo() {
	if [[ $1 != "MD5" && $1 != "SHA256" && $1 != "SHA224" && $1 != "SHA512" && $1 != "SHA384" ]];then
		echo "error: bad argument for -a option"
		exit 0
	fi
}

print_usage() {
	echo -e "usage: bash tester.sh [bonus] [clean] [-h --help] [--list] [-n total_test] [-a --algo algo_name]"
	echo -e "\t[bonus] to test bonus part (sha224 sha512 sha384)"
	echo -e "\t[clean] to delete all files in tester directory"
	echo -e "\t[-h --help] to display this message"
	echo -e "\t[-n total_test] to set the number of tests"
	echo -e "\t[-a --algo algo_name] select a specific algorithm"
	echo -e "\t[--list] displays the list of available algorithm to test"
}

parse() {
	for (( i=1; i<=$#; i++)); do
		if [ ${!i} == "clean" ]; then
			clean
			exit 0
		fi
		if [ ${!i} == "bonus" ]; then
			if [ ! ${#algo[@]} -eq 0 ]; then
				echo "error: incompatible option bonus and -a"
				exit 1
			fi
			algo=("MD5" "SHA256" "SHA224" "SHA512" "SHA384")
		fi
		if [ ${!i} = "-n" ]; then
			j=$((i + 1))
			if [[ ( $j > "$#" ) ]]; then
				echo "Missing argument for ${!i} option"
				exit 1
			fi
			total_test=$((${!j}))
		fi
		if [[ ${!i} = "-h" || ${!i} = "--help" ]]; then
			print_usage
			exit 0
		fi
		if [ ${!i} = "--list" ]; then
			echo -e "algorithm list :"
			echo -e "\tmd5\n\tsha256\n\tsha224\n\tsha512\n\tsha384"
			exit 0
		fi
		if [[ ${!i} = "-a" || ${!i} == "--algo" ]]; then
			if [ ! ${#algo[@]} -eq 0 ]; then
				echo "error: incompatible option bonus and -a"
				exit 1
			fi
			j=$((i + 1))
			if [[ ( $j > "$#" ) ]]; then
				echo "Missing argument for ${!i} option"
				exit 1
			fi
			selected_algo=${!j^^}
			check_algo $selected_algo
			algo=( $selected_algo )
		fi
	done
}

total_test=100

if [ "$#" > 0 ]; then
	parse $*
fi

if [ ${#algo[@]} -eq 0 ]; then
	algo=("MD5" "SHA256")
fi

if [ ! -d "./tester" ]; then
	mkdir ./tester
fi

ft_ssl_res=./tester/ft_ssl_res.
openssl_res=./tester/openssl_res.
openssl_trunc=./tester/openssl_res_trunc.
ft_ssl_trunc=./tester/ft_ssl_res_trunc.

declare color=("\033[1;35m" "\033[1;32m" "\033[1;33m" "\033[1;36m" "\033[1;34m")

RED="\033[1;31m"
PURPLE="\033[1;35m"
GREEN="\033[1;32m"
YELLOW="\033[1;33m"
CYAN="\033[1;36m"
BLUE="\033[1;34m"
NC="\033[0m"

clean

echo -n -e "$RED$total_test$NC tests for : "
for (( x = 0; x < ${#algo[@]}; x++ ))
do
	echo -n -e "${color[$x]} ${algo[$x]}${NC}"
done
echo -e "\n"

for (( x = 0; x < ${#algo[@]}; x++ ))
do
	echo -e "\t\t\t${color[$x]} ${algo[$x]} TEST ${NC}"
	for (( i=0; i < $(( total_test )); i++ ))
	do
		nb=`shuf -i 1-1000000 -n 1`
		echo -e $RED "\ntest $i with $nb characters" ${NC}>> tester/log.txt
		LC_ALL=C tr -dc 'A-Za-z0-9!"#$%&'\''()*+,-./:;<=>?@[\]^_`{|}~' </dev/urandom | head -c $nb > tester/tmp.txt
		cat tester/tmp.txt >> tester/log.txt
		openssl ${algo[$x]} tester/tmp.txt >> $openssl_res${algo[$x]}
		./ft_ssl ${algo[$x]} tester/tmp.txt >> $ft_ssl_res${algo[$x]}
	done
	cat $ft_ssl_res${algo[$x]} | cut -d'=' -f2- | cut -d' ' -f2- > $ft_ssl_trunc${algo[$x]}
	cat $openssl_res${algo[$x]} | cut -d'=' -f2- | cut -d' ' -f2- > $openssl_trunc${algo[$x]}
	diff $openssl_trunc${algo[$x]} $ft_ssl_trunc${algo[$x]} &>/dev/null
	if [ $? -ne 0 ]; then
		perl -C -e 'print "\x{274c}"'
		echo -e " The directory was modified";
	else
		perl -C -e 'print "\x{2705}"'
		echo -e " No difference between ft_ssl and openssl";
	fi
done


