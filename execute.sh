gcc organization.c
x=1

while [ $x -le 10 ]
do
	(./a.out < input_$x.txt) > output_$x.txt
	$(( x++ ))
done	
