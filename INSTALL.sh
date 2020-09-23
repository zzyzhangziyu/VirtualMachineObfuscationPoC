#!/bin/bash

cat << "EOF"
 __   ____  __ ___ ___  ___ _____ ___ ___ _____                                                 
 \ \ / /  \/  | _ \ _ \/ _ \_   _| __/ __|_   _|                                                
  \ V /| |\/| |  _/   / (_) || | | _| (__  | |                                                  
   \_/ |_|  |_|_| |_|_\\___/ |_| |___\___| |_|                _                            _    
  __| |_____ _____| |___ _ __ _ __  ___ _ _| |_   ___ _ ___ _(_)_ _ ___ _ _  _ __  ___ _ _| |_  
 / _` / -_) V / -_) / _ \ '_ \ '  \/ -_) ' \  _| / -_) ' \ V / | '_/ _ \ ' \| '  \/ -_) ' \  _| 
 \__,_\___|\_/\___|_\___/ .__/_|_|_\___|_||_\__| \___|_||_\_/|_|_| \___/_||_|_|_|_\___|_||_\__| 
          _             |_|         _        _ _                                                
  ___ ___| |_ _  _ _ __  (_)_ _  __| |_ __ _| | |___ _ _                                        
 (_-</ -_)  _| || | '_ \ | | ' \(_-<  _/ _` | | / -_) '_|                                       
 /__/\___|\__|\_,_| .__/ |_|_||_/__/\__\__,_|_|_\___|_|                                         
                  |_|                                                                           
EOF
echo "version 0.2.200921.2026"
echo "#####################################"

echo ""
echo -n "Write path to deploy: "
read pathToInstall

# #####################################
# ############## STAGE 1 ##############
echo "STAGE 1 - check if require programs exist"
if ! [ -x "$(command -v python3)" ];
then
        echo "  \e[1;31mWARNING: python3 could not be found\e[0m"
else
        echo "  python3 installed - \e[96myes\e[0m"
fi

if ! [ -x "$(command -v make)" ];
then
        echo "  \e[1;31mWARNING: make could not be found\e[0m"
else
        echo "  make installed - \e[96myes\e[0m"
fi

if ! [ -x "$(command -v g++)" ];
then
        echo "  \e[1;31mWARNING: g++ could not be found\e[0m"
else
        echo "  g++ installed - \e[96myes\e[0m"
fi

if ! [ -x "$(command -v nasm)" ];
then
        echo "  \e[1;33mWARNING: nasm could not be found\e[0m"
else
        echo "  nasm installed - \e[96myes\e[0m"
fi
# #####################################


echo "\e[1;31m!!!! NOT READY !!!!\e[0m"

# e.g.
# make -C ./Debugger build
# make -C ./Debugger clean
