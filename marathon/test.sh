#!/bin/bash
for f in $2/*.in
do
	valgrind --log-file="/dev/null" --error-exitcode=11 ./$1 < $f > my.out 2>my.err
	if [ "$?" -ne "0" ]
	then
		if [ "$?" -eq "1" ]
		then
			echo "${f%.in} malloc error"
		else
			echo "${f%.in} valgrind error"
		fi
	else if diff ${f%in}err my.err >/dev/null 2>&1 && diff ${f%in}out my.out >/dev/null 2>&1
	then
		echo "${f%.in} powiodło się"
	else
		echo "${f%.in} nie powiodło się"
	fi
fi

done
rm my.out
rm my.err