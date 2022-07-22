#!/bin/bash

clean() {
	echo "Removed all files in tester directory" 
	if [ "$(ls -A ./tester)" ]; then
		rm tester/*.txt
	else
		echo "No files to delete"
	fi
}

if [[ ! -d "./tester" ]]
then
	mkdir ./tester
fi

if [ "$1" == "clean" ]; then
	clean
	exit 0
fi

ft_ssl_res=./tester/ft_ssl_res.txt
openssl_res=./tester/openssl_res.txt
openssl_trunc=./tester/openssl_res_trunc.txt
ft_ssl_trunc=./tester/ft_ssl_res_trunc.txt

declare color=( "\033[0;35m" "\033[0;32m" "\033[1;33m" "\033[1;36m" "\033[1;34m" )

RED="\033[0;31m"
PURPLE="\033[0;35m"
GREEN="\033[0;32m"
YELLOW="\033[1;33m"
CYAN="\033[1;36m"
BLUE="\033[1;34m"
NC="\033[0m"

clean

if [ "$1" == "bonus" ]; then
	algo=("MD5" "SHA256" "SHA224" "SHA512" "SHA384")
else
	algo=("MD5" "SHA256")
fi

for (( x = 0; x < ${#algo[@]}; x++ ))
do
	echo "\t\t\t${color[$x]} ${algo[$x]} TEST $NC"
	for (( i=0; i < 100; i++ ))
	do
		nb=`shuf -i 1-1000000 -n 1`
		echo $RED "\ntest $i with $nb characters" $NC>> tester/log.txt
		LC_ALL=C tr -dc 'A-Za-z0-9!"#$%&'\''()*+,-./:;<=>?@[\]^_`{|}~' </dev/urandom | head -c $nb > tester/tmp.txt
		cat tester/tmp.txt >> tester/log.txt
		openssl ${algo[$x]} tester/tmp.txt >> $openssl_res
		./ft_ssl ${algo[$x]} tester/tmp.txt >> $ft_ssl_res
	done
	cat $ft_ssl_res | cut -d'=' -f2- | cut -d' ' -f2- > $ft_ssl_trunc
	cat $openssl_res | cut -d'=' -f2- | cut -d' ' -f2- >$openssl_trunc
	diff $openssl_trunc $ft_ssl_trunc
	diff $openssl_trunc $ft_ssl_trunc
	if [ $? -ne 0 ]; then
		echo "The directory was modified";
	else
		echo "No difference between ft_ssl and openssl";
	fi
done


