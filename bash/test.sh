#!/bin/bash


# give perms to the file first 
#firsat line for specifying default shell interpreter 
#ls -l to view perms 

#NOTE: echo ${1,,} , ",," operator means it converts 1st positional arg to lowercase 

# 1
# echo hello world

#2
# echo whats ur first name
# read FIRST_NAME
# echo $FIRST_NAME is my first name

# 3 
# positional args ==>> run ./test.sh arg1Value arg2Value
# echo hello $1 $2

#4 
#append/ add outputs of a command to a file
# echo manas > hello.txt
# echo manas >> hello.txt

#5
#input from a file to a command <<,<,<<<

#6
# exit code 0 means command returned no error 
#eg [1 = 0] run then run echo $? gives op as 1 because they're not equal instead of = we can use -eq 

#7
# IF-ELIF-ELSE
# if [ ${1,,} = "manas" ]; then
#     echo "You are logged in"
# elif [ ${1,,} = "not manas" ]; then
#     echo "You are not logged in"
# else
#     echo "nothing" 
# fi

#8
#switch case
# case ${1,,} in 
#     manas | admin)
#         echo "i am allowed"
#         ;;
#     help)
#         echo "i am asking for help"
#         ;;
#     *)
#         echo "i am rest all cases"
# esac

#9
#arrays
LIST=(1 2 3 4 5)
echo $LIST # TO GET 1ST ELEMENT
echo ${LIST[@]} # TO GET ALL ITEMS SPACE SEPERATED, @ CAN BE 0 TO N-1 

#ADDITION
# #!/bin/bash

# # Prompt the user to enter the first number
# echo "Enter the first number:"
# read num1

# # Prompt the user to enter the second number
# echo "Enter the second number:"
# read num2

# # Calculate the sum
# sum=$((num1 + num2))

# # Display the result
# echo "The sum of $num1 and $num2 is: $sum"



#PRIME NO 
#!/bin/bash

# Prompt the user to enter a number
echo "Enter a number:"
read num

# Check if the number is less than 2
if [ "$num" -lt 2 ]; then
    echo "$num is not a prime number."
    exit 0
fi

# Check for factors from 2 to the square root of the number
for (( i=2; i*i<=num; i++ )); do
    if [ $((num % i)) -eq 0 ]; then
        echo "$num is not a prime number."
        exit 0
    fi
done

# # If no factors were found, it is prime
# echo "$num is a prime number."


#PALINDROME
# #!/bin/bash

# # Prompt the user to enter a string
# echo "Enter a string:"
# read str

# # Reverse the string
# reversed_str=$(echo "$str" | rev)

# # Check if the original string is the same as the reversed string
# if [ "$str" = "$reversed_str" ]; then
#     echo "$str is a palindrome."
# else
#     echo "$str is not a palindrome."
# fi


#FACTORIAL
#!/bin/bash

# Prompt the user to enter a number
echo "Enter a number:"
read num

# Initialize factorial result
factorial=1

# Check if the number is negative
if [ "$num" -lt 0 ]; then
    echo "Factorial is not defined for negative numbers."
    exit 1
fi

# Calculate the factorial
for (( i=1; i<=num; i++ )); do
    factorial=$((factorial * i))
done

# Display the result
echo "The factorial of $num is: $factorial"
