#!/bin/bash
# Omer Eckstein 312350192
if test $1 = system
then
    for arg in "$@"
    do
        case $arg in
            --name)
            echo 1
            shift # Remove --initialize from processing
            ;;
            --version)
            echo 2
            shift # Remove --cache= from processing
            ;;
            --pretty_name)
            echo 1
            shift # Remove --initialize from processing
            ;;
            --home_url)
            echo 2
            shift # Remove --cache= from processing
            ;;
            --support_url)
            echo 1
            shift # Remove --initialize from processing
            ;;
        esac
    done
else 
    if test $1 = host
    then
        for arg in "$@"
    do
        case $arg in
            --support_url)
            echo 1
            shift # Remove --initialize from processing
            ;;
            --static_hostname)
            echo 2
            shift # Remove --cache= from processing
            ;;
            --icon_name)
            echo 1
            shift # Remove --initialize from processing
            ;;
            --machine_id)
            echo 2
            shift # Remove --cache= from processing
            ;;
            --boot_id)
            echo 1
            shift # Remove --initialize from processing
            ;;
            --virtualization)
            echo 2
            shift # Remove --cache= from processing
            ;;
            --kernel)
            echo 1
            shift # Remove --initialize from processing
            ;;
            --architecture)
            echo 2
            shift # Remove --cache= from processing
            ;;
        esac
    done
    else
        echo Invalid input
    fi
fi

for arg in "$@"
do
    case $arg in
        --name)
        echo 1
        shift # Remove --initialize from processing
        ;;
        --version)
        echo 2
        shift # Remove --cache= from processing
        ;;
    esac
done