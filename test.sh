#!/bin/bash
if [ $1 == "-v" ]
then
	for test in $3/*.in
	do
		first_part=${test%.*}
		first_part=${first_part#*/}
		./$2 -v < $3/$first_part.in > $3/my_result_$first_part.out 2> $3/my_result_$first_part.err
		if [ "$(diff $3/$first_part.out $3/my_result_$first_part.out)" != "" ]
			then echo "Your standard output on test: $first_part is uncorrect"
		else
			echo "Correct output on test: $first_part"
		fi
		if [ "$(diff $3/$first_part.err $3/my_result_$first_part.err)" != "" ]
			then echo "Your diagnostic error output on test: $first_part is uncorrect"
		else
			echo "Correct diagnostic error output on test: $first_part"
		fi
		rm -f $3/my_result_$first_part.out
		rm -f $3/my_result_$first_part.err
	done
else
	for test in $2/*.in
	do
		first_part=${test%.*}
		first_part=${first_part#*/}
		./$1 < $2/$first_part.in > $2/my_result_$first_part.out
		if [ "$(diff $2/$first_part.out $2/my_result_$first_part.out)" != "" ]
			then echo "Your standard output on test: $first_part is uncorrect"
		else
			echo "Correct output on test: $first_part"
		fi
		rm -f $2/my_result_$first_part.out
	done
fi
