gcc organization.c
x=1

while [ $x -le 1000 ]
do
	python3 binary.c > input_$x.txt
	(./a.out < input_$x.txt) > output_$x.txt
	$(( x++ ))
done	
