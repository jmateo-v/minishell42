#!/bin/bash

MINISHELL=./minishell

CASES=(
  "exit 9223372036854775807"
  "exit something somethingv2"
  "exit 0 0"
  "exit"
  "exit \"\""
  "exit \"+100\""
  "exit \"-100\""
  "exit -9223372036854775805"
  "exit 0"
  "exit 10"
  "exit 42"
  "exit 1"
  "exit +++++"
  "exit ++++++"
  "exit +1"
  "exit ++1"
  "exit ++12560"
  "exit -----"
  "exit ------"
  "exit -1"
  "exit --1"
  "exit -12560"
  "exit --12560"
  "exit 255"
  "exit 1 2"
  "exit 1 2 3"
  "exit A"
  "exit A 2 3"
  "exit \"A\""
  "exit \"+++\""
  "exit ++++3193912939"
  "exit 01"
  "exit 001"
  "exit 0001"
  "exit +++000"
  "exit ++++000"
  "exit ---000"
  "exit ----000"
  "exit \"something\""
  "exit x"
  "exit echo"
  "exit cd .."
  "exit exit"
  "exit 42 42 42 42 42"
)

echo "=== EXIT TESTS ==="
for cmd in "${CASES[@]}"; do
    echo
    echo ">>> $cmd"

    # Run in Bash
    bash -c "$cmd" >bash_out.txt 2>&1
    bash_status=$?
    echo "[bash] status=$bash_status"
    if [ -s bash_out.txt ]; then
        echo "[bash] stderr/stdout:"
        cat bash_out.txt
    fi

    # Run in minishell
    echo "$cmd" | $MINISHELL >mini_out.txt 2>&1
    mini_status=$?
    echo "[mini] status=$mini_status"
    if [ -s mini_out.txt ]; then
        echo "[mini] stderr/stdout:"
        cat mini_out.txt
    fi
done

rm -f bash_out.txt mini_out.txt
