#!/bin/bash
# Omer Eckstein 312350192

#check if not have args
if test $# -eq 0
then
    echo Invalid input
    exit 1
fi
#if arg is system
if test $1 = system
then
    for arg in "$@"
    do
        case $arg in
            --name)
            A=$(awk -F= -v x="NAME" '$1==x{print $2}' os-release | tr -d \")
            shift # Remove --name from processing
            ;;
            --version)
            B=$(awk -F= -v x="VERSION" '$1==x{print $2}' os-release | tr -d \")
            shift # Remove --version= from processing
            ;;
            --pretty_name)
            C=$(awk -F= -v x="PRETTY_NAME" '$1==x{print $2}' os-release | tr -d \")
            shift # Remove --pretty_name from processing
            ;;
            --home_url)
            D=$(awk -F= -v x="HOME_URL" '$1==x{print $2}' os-release | tr -d \")
            shift # Remove --home_url= from processing
            ;;
            --support_url)
            E=$(awk -F= -v x="SUPPORT_URL" '$1==x{print $2}' os-release | tr -d \")
            shift # Remove --support_url from processing
            ;;
        esac
    done
    #printing flags
    if [ -n "$A" ]; then echo $A; fi
    if [ -n "$B" ]; then echo $B; fi
    if [ -n "$C" ]; then echo $C; fi
    if [ -n "$D" ]; then echo $D; fi
    if [ -n "$E" ]; then echo $E; fi
    if [ -z "$E" ] && [ -z "$D" ]&& [ -z "$C" ]&& [ -z "$B" ]&& [ -z "$A" ]; then cat os-release; fi

else 
    #if arg is system
    if test $1 = host
    then
        for arg in "$@"
    do
        case $arg in
            --static_hostname)
            A=$(awk -F": " -v x="   Static hostname" '$1==x{print $2}' hostnamectl)
            shift # Remove --static_hostname= from processing
            ;;
            --icon_name)
            B=$(awk -F": " -v x="         Icon name" '$1==x{print $2}' hostnamectl)
            shift # Remove --icon_name from processing
            ;;
            --machine_id)
            C=$(awk -F": " -v x="        Machine ID" '$1==x{print $2}' hostnamectl)
            shift # Remove --machine_id= from processing
            ;;
            --boot_id)
            D=$(awk -F": " -v x="           Boot ID" '$1==x{print $2}' hostnamectl)
            shift # Remove --boot_id from processing
            ;;
            --virtualization)
            E=$(awk -F": " -v x="    Virtualization" '$1==x{print $2}' hostnamectl)
            shift # Remove --virtualization= from processing
            ;;
            --kernel)
            F=$(awk -F": " -v x="            Kernel" '$1==x{print $2}' hostnamectl)
            shift # Remove --kernel from processing
            ;;
            --architecture)
            G=$(awk -F": " -v x="      Architecture" '$1==x{print $2}' hostnamectl)
            shift # Remove --architecture= from processing
            ;;
        esac
    done
    #printing flags
    if [ -n "$A" ]; then echo $A; fi
    if [ -n "$B" ]; then echo $B; fi
    if [ -n "$C" ]; then echo $C; fi
    if [ -n "$D" ]; then echo $D; fi
    if [ -n "$E" ]; then echo $E; fi
    if [ -n "$F" ]; then echo $F; fi
    if [ -n "$G" ]; then echo $G; fi
    if [ -z "$G" ] && [ -z "$F" ] && [ -z "$E" ] && [ -z "$D" ]&& [ -z "$C" ]&& [ -z "$B" ]&& [ -z "$A" ]; then cat hostnamectl; fi
    else
        echo Invalid input
    fi
fi
