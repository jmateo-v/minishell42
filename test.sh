#!/bin/bash

# Ensure outfiles directory exists
mkdir -p ./outfiles

# Create dummy input files for redirection test
echo "input from 123" > 123
echo "input from 456" > 456

# --- Test 1 ---
echo "Running: /bin/echo hi >./outfiles/outfile01 | /bin/echo bye"

# Run in minishell using heredoc
./minishell > minishell_out1.txt 2> minishell_err1.txt <<EOF
/bin/echo hi >./outfiles/outfile01 | /bin/echo bye
EOF
MINISHELL_CODE=$?

# Run in bash
bash > bash_out1.txt 2> bash_err1.txt <<EOF
/bin/echo hi >./outfiles/outfile01 | /bin/echo bye
EOF
BASH_CODE=$?

# Compare outputs
echo "Minishell STDOUT:"
cat minishell_out1.txt
echo "Bash STDOUT:"
cat bash_out1.txt
echo "Minishell STDERR:"
cat minishell_err1.txt
echo "Bash STDERR:"
cat bash_err1.txt
echo "Exit codes: minishell=$MINISHELL_CODE, bash=$BASH_CODE"

#echo "----------------------------------------"

# --- Test 2 ---
#echo "Running: /bin/echo <123 <456 hi | /bin/echo 42"

#./minishell > minishell_out2.txt 2> minishell_err2.txt <<EOF
#/bin/echo <123 <456 hi | /bin/echo 42
#EOF
#MINISHELL_CODE2=$?

#bash > bash_out2.txt 2> bash_err2.txt <<EOF
#/bin/echo <123 <456 hi | /bin/echo 42
#EOF
#BASH_CODE2=$?

#echo "Minishell STDOUT:"
#cat minishell_out2.txt
#echo "Bash STDOUT:"
#cat bash_out2.txt
#echo "Minishell STDERR:"
#cat minishell_err2.txt
#echo "Bash STDERR:"
#cat bash_err2.txt
#echo "Exit codes: minishell=$MINISHELL_CODE2, bash=$BASH_CODE2"



